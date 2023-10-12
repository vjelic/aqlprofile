/* Copyright (c) 2022-2023 Advanced Micro Devices, Inc.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE. */

#pragma once
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <cstring>
#include <atomic>
#include <mutex>
#include <shared_mutex>

//#define AMD_AQLPROFILE_SQTT_NPI
#define SQTT_PARSER_VERSION 2

enum WAVESLOT_STATE
{
    WS_EMPTY = 0,
    WS_IDLE = 1,
    WS_EXEC = 2,
    WS_WAIT = 3,
    WS_STALL = 4,
    WS_UNKNOWN = 5,
};

enum class WaveInstCategory
{
    NONE = 0,
    SMEM = 1,
    SALU = 2,
    VMEM = 3,
    FLAT = 4,
    LDS = 5,
    VALU = 6,
    JUMP = 7,
    NEXT = 8,
    IMMED = 9,
    TRAP = 10,
    PCINFO = 15,
    WAVE_END,
};

typedef struct {
    uint64_t time;
    uint16_t events0;
    uint16_t events1;
    uint16_t events2;
    uint16_t events3;
    uint8_t CU;
    uint8_t bank;
} perfevent_t;

typedef struct {
    uint64_t kernel_id : 12;
    uint64_t value : 7;
    uint64_t cu : 4;
    uint64_t time : 41; // Time_value/16
} occupancy_info_t;

typedef union {
    uint64_t raw;
    struct {
        uint64_t isValid : 1;
        uint64_t isNavi : 1;
        uint64_t npiWaveData : 1;
        uint64_t version : 13;
    };
} _output_flags_t;

struct Instruction
{
    Instruction() = default;
    Instruction(uint64_t time, WaveInstCategory value, uint64_t issue2inst, uint64_t last)
            : time(time), issue2inst(issue2inst), last(last), value((uint64_t)value) {}

    std::pair<uint64_t, uint64_t> getTiming() const { return {time, std::max(issue2inst, last)}; }

    uint64_t time;
    uint64_t value;
    uint64_t issue2inst;
    uint64_t last;
};

struct InstructionExt
{
    InstructionExt() = default;
    InstructionExt(WaveInstCategory value, uint64_t num_waves, uint64_t cycles)
            : num_waves(num_waves), value((uint64_t)value), cycles(cycles) {}
    InstructionExt(const Instruction& inst):
        num_waves(1), value(inst.value), cycles(std::max(inst.last, inst.issue2inst)) {};

    uint64_t num_waves;
    uint64_t value;
    uint64_t cycles;

    // TODO: Compare PCs
    bool operator==(const Instruction& other) const { return this->value == other.value; };
    bool operator!=(const Instruction& other) const { return this->value != other.value; };
    InstructionExt& operator+=(const Instruction& other) {
        num_waves += 1;
        if (value != (uint64_t)WaveInstCategory::PCINFO)
            cycles += std::max(other.last, other.issue2inst);
        return *this;
    };
};

struct WaveDataBase
{
    uint64_t simd;
    uint64_t wave_id;
    uint64_t begin_time = 0;  // Begin and end cycle
    uint64_t end_time = 0;
    int64_t traceID = -1;

    // total VMEM/FLAT/LDS/SMEM instructions issued
    uint64_t num_mem_instrs = 0;     // total issued memory instructions
    uint64_t num_issued_instrs = 0;  // total issued instructions (compute + memory)
    uint64_t num_valu_instrs = 0;
    uint64_t num_valu_stalls = 0;
    // VMEM Pipeline: instrs and stalls
    uint64_t num_vmem_instrs = 0;
    uint64_t num_vmem_stalls = 0;
    // FLAT instrs and stalls
    uint64_t num_flat_instrs = 0;
    uint64_t num_flat_stalls = 0;

    // LDS instr and stalls
    uint64_t num_lds_instrs = 0;
    uint64_t num_lds_stalls = 0;

    // SCA instrs stalls
    uint64_t num_salu_instrs = 0;
    uint64_t num_smem_instrs = 0;
    uint64_t num_salu_stalls = 0;
    uint64_t num_smem_stalls = 0;

    // Branch
    uint64_t num_branch_instrs = 0;
    uint64_t num_branch_taken_instrs = 0;
    uint64_t num_branch_stalls = 0;

    uint64_t timeline_size = 0;
    uint64_t instructions_size = 0;
    std::pair<int32_t, int32_t>* timeline_alloc = nullptr;
    std::pair<uint64_t, uint64_t>* instructions_alloc = nullptr;
};

struct WaveDataInternal : public WaveDataBase
{
    std::vector<Instruction> instructions;
    std::vector<std::pair<int32_t, int32_t>> timeline;  // wave state in each cycle

    // kernel_addr -> kernel_ID
    static std::unordered_map<uint64_t, size_t> kernelID;
    static std::atomic<size_t> current_kernel_unique_id;
    static std::shared_mutex mutex;

    static size_t get_addr_unique_id(uint64_t wave_addr)
    {
        size_t kid;
        bool bSuccess = false;

        {
          std::shared_lock<std::shared_mutex> lock(mutex);
          if (kernelID.find(wave_addr) != kernelID.end())
          {
            bSuccess = true;
            kid = kernelID[wave_addr];
          }
        }
        if (!bSuccess)
        {
          std::unique_lock<std::shared_mutex> lock(mutex);
          kid = current_kernel_unique_id.fetch_add(1, std::memory_order::memory_order_relaxed);
          kernelID[wave_addr] = kid;
        }
        return kid;
    }
};


struct WaveDataNPI : public WaveDataBase
{
    WaveDataNPI() = default;
    WaveDataNPI(WaveDataNPI&) = delete;
    WaveDataNPI(WaveDataBase&) = delete;
    WaveDataNPI(WaveDataInternal&) = delete;
    WaveDataNPI(const WaveDataNPI&) = delete;
    WaveDataNPI(const WaveDataBase&) = delete;
    WaveDataNPI(const WaveDataInternal&) = delete;

    void Copy(WaveDataInternal& data)
    {
        using T = WaveDataBase;
        Delete();
        std::memcpy(static_cast<T*>(this), static_cast<T*>(&data), sizeof(T));

        timeline_size = data.timeline.size();
        timeline_alloc = new std::pair<int32_t, int32_t>[timeline_size+4];
        memcpy(timeline_alloc, data.timeline.data(), sizeof(timeline_alloc[0])*timeline_size);
        timeline_alloc[timeline_size] = {-1, -1};

        instructions_size = data.instructions.size();
        instructions_alloc = new std::pair<uint64_t, uint64_t>[instructions_size+4];
        for (uint64_t i=0; i<instructions_size; i++)
            instructions_alloc[i] = data.instructions[i].getTiming();
        instructions_alloc[instructions_size] = {0, 0};
    }

    void Delete()
    {
        if (this->timeline_alloc) delete[] this->timeline_alloc;
        this->timeline_alloc = nullptr;

        if (this->instructions_alloc) delete[] this->instructions_alloc;
        this->instructions_alloc = nullptr;
    }

    ~WaveDataNPI() { Delete(); }
};

struct python_return_info_t
{
    _output_flags_t flags;
    uint64_t id;

    uint64_t num_traces;
    uint64_t* tracesizes;
    int64_t* traceIDs;
    InstructionExt** tracedata;

    uint64_t num_events;
    perfevent_t* perfevents;
    occupancy_info_t* occupancy;
    uint64_t num_occupancy;
    void* kernel_id_addr;
    uint64_t num_kernel_ids;

    void* wavenpi;
    uint64_t num_waves;
};

struct CppReturnInfo
{
    _output_flags_t flags;
    std::vector<uint64_t> kernel_ids_addr;
    std::vector<int64_t> traceIDs;
    std::vector<uint64_t> tracesizes;
    std::vector<InstructionExt*> tracedata;
    std::vector<std::vector<InstructionExt>> traces;
    std::vector<occupancy_info_t> occupancy;
    std::vector<perfevent_t> perfevents;
#ifdef AMD_AQLPROFILE_SQTT_NPI
    std::vector<WaveDataNPI> waves;
#endif

    python_return_info_t fromCppReturn() const;
    size_t GetMemoryNeededForSerialization() const;
    size_t Serialize(char* buffer, size_t buffersize) const;
    static std::unique_ptr<CppReturnInfo> UnSerialize(const char* buffer, size_t buffersize);
};

struct fileoffset_info_t
{
    _output_flags_t flags;
    uint64_t id;

    uint64_t num_kernel_ids;
    uint64_t num_traces;
    uint64_t num_events;
    uint64_t num_occupancy;
};

std::unique_ptr<CppReturnInfo>
AnalyseBinary_internal(const uint8_t* buffer, int BUFFER_SIZE, int target_cu);
