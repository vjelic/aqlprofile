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
#include <array>
#include "segment.hpp"
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include "thread_trace_viewer_def.h"
#include "../core/include/aql_profile_v2.h"

//#define AMD_AQLPROFILE_SQTT_NDA
#define SQTT_PARSER_VERSION 5
#define OCCUPANCY_RESOLUTION 8

struct occupancy_info_t : public att_occupancy_info_t
{
    occupancy_info_t() = default;
    occupancy_info_t(
        uint64_t kid, uint64_t simd, uint64_t slot,
        uint64_t enable, uint64_t cu, int64_t time
    ) {
        this->kernel_id = kid;
        this->simd = simd;
        this->slot = slot;
        this->enable = enable;
        this->cu = cu;
        this->time = time/OCCUPANCY_RESOLUTION;
#ifndef AMD_AQLPROFILE_SQTT_NDA
        this->time &= ~0x7ul; // Makes the time information have a granularity of 64 cycles
        this->simd = 0;
        this->slot = 0;
#endif
    }
};

static_assert(sizeof(occupancy_info_t)==sizeof(att_occupancy_info_t), "Occ cannot share layout!");

struct Instruction
{
    Instruction() = default;
    Instruction(pcinfo_t _pc): category(WaveInstCategory::PCINFO), pc(_pc) {}
    Instruction(int64_t _time, WaveInstCategory _category, int64_t _cycles, int _stall)
            : time(_time), category(_category), cycles(_cycles), stall_time(_stall) {}

    wave_instruction_t getTiming() const { return {time, std::max(cycles, stall_time)}; }

    union {
        struct __attribute__((packed)) {
            int64_t time;
            int cycles;
            int stall_time;
        };
        pcinfo_t pc;
    };
    int8_t category;
};

struct InstructionExt: public att_trace_event_t
{
    InstructionExt(): InstructionExt(WaveInstCategory::NONE, 0, 0) {}
    InstructionExt(WaveInstCategory _category, uint64_t num_waves, uint64_t cycles)
    {
        this->hitcount = num_waves;
        this->latency = cycles;
        this->pc = {0,0};
        this->category = _category;
    }
    InstructionExt(const Instruction& inst): InstructionExt()
    {
        this->category = inst.category;
        if (inst.category != WaveInstCategory::PCINFO)
        {
            this->latency = std::max(inst.cycles, inst.stall_time);
            this->hitcount = 1;
        }
        else
            this->pc = inst.pc;
    }

    inline bool operator==(const Instruction& other) const { return !(*this != other); };
    inline bool operator!=(const Instruction& other) const
    {
        if (this->category != other.category)
            return true;
        else if (other.category == WaveInstCategory::PCINFO)
            return pc != other.pc;
        return false;
    };
    InstructionExt& operator+=(const Instruction& other)
    {
        if (other.category != WaveInstCategory::PCINFO)
        {
            hitcount += 1;
            latency += std::max(other.cycles, other.stall_time);
        }
        return *this;
    };
};
static_assert(sizeof(att_trace_event_t)==sizeof(InstructionExt), "Structs cannot share layout!");

struct WaveDataInternal : public wave_data_t
{
    WaveDataInternal() { memset(static_cast<wave_data_t*>(this), 0, sizeof(wave_data_t)); }
    std::vector<Instruction> instructions;
    std::vector<std::pair<int32_t, int32_t>> timeline;  // wave state in each cycle

    // kernel_addr -> kernel_ID
    static std::unordered_map<pcinfo_t, size_t> kernelID;
    static std::atomic<size_t> current_kernel_unique_id;
    static std::shared_mutex mutex;

    static size_t get_addr_unique_id(pcinfo_t wave_addr)
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


struct WaveDataNPI : public wave_data_t
{
    WaveDataNPI() = default;
    WaveDataNPI(WaveDataNPI&) = delete;
    WaveDataNPI(wave_data_t&) = delete;
    WaveDataNPI(WaveDataInternal&) = delete;
    WaveDataNPI(const WaveDataNPI&) = delete;
    WaveDataNPI(const wave_data_t&) = delete;
    WaveDataNPI(const WaveDataInternal&) = delete;

    void Copy(WaveDataInternal& data)
    {
        using T = wave_data_t;
        Delete();
        std::memcpy(static_cast<T*>(this), static_cast<T*>(&data), sizeof(T));

        timeline_size = data.timeline.size();
        timeline_array = new wave_state_t[timeline_size+4];
        memcpy(timeline_array, data.timeline.data(), sizeof(timeline_array[0])*timeline_size);
        timeline_array[timeline_size] = {-1, -1};

        instructions_size = data.instructions.size();
        instructions_array = new wave_instruction_t[instructions_size+4];
        for (uint64_t i=0; i<instructions_size; i++)
            instructions_array[i] = data.instructions[i].getTiming();
        instructions_array[instructions_size] = {0, 0};
    }

    void Delete()
    {
        if (this->timeline_array) delete[] this->timeline_array;
        this->timeline_array = nullptr;

        if (this->instructions_array) delete[] this->instructions_array;
        this->instructions_array = nullptr;
    }

    ~WaveDataNPI() { Delete(); }
};

typedef union
{
    uint64_t raw;
    struct {
        uint64_t isValid : 1;
        uint64_t isNavi : 1;
        uint64_t npiWaveData : 1;
        uint64_t version : 13;
    };
} att_output_flags_t;

struct python_return_info_t
{
    att_output_flags_t flags;
    uint64_t id;

    uint64_t num_traces;
    uint64_t* tracesizes;
    int64_t* traceIDs;
    InstructionExt** tracedata;

    uint64_t num_events;
    att_perfevent_t* perfevents;
    occupancy_info_t* occupancy;
    uint64_t num_occupancy;
    void* kernel_id_addr;
    uint64_t num_kernel_ids;

    void* wavenpi;
    uint64_t num_waves;
};

struct CppReturnInfo
{
    att_output_flags_t flags;
    std::vector<pcinfo_t> kernel_ids_addr;
    std::vector<int64_t> traceIDs;
    std::vector<uint64_t> tracesizes;
    std::vector<InstructionExt*> tracedata;
    std::vector<std::vector<InstructionExt>> traces;
    std::vector<occupancy_info_t> occupancy;
    std::vector<att_perfevent_t> perfevents;
#ifdef AMD_AQLPROFILE_SQTT_NDA
    std::vector<WaveDataNPI> waves;
#endif

    python_return_info_t fromCppReturn() const;
    size_t GetMemoryNeededForSerialization() const;
    size_t Serialize(uint8_t* buffer, size_t buffersize, bool v2gfx9) const;
    static std::unique_ptr<CppReturnInfo> UnSerialize(const uint8_t* buffer, size_t buffersize);
};

struct fileoffset_info_t
{
    att_output_flags_t flags;
    uint64_t id;

    uint64_t num_kernel_ids;
    uint64_t num_traces;
    uint64_t num_events;
    uint64_t num_occupancy;
};

std::unique_ptr<CppReturnInfo>
AnalyseBinary_internal(const uint8_t* buffer, int BUFFER_SIZE, int gfx9_target_cu);

template<typename Type>
class PipeArray : public std::array<std::array<Type, 4>, 2>
{
public:
  template<typename T2>
  Type& at_reg(const T2& token) { return this->at(token.me&0x1).at(token.pipe); }
};

typedef PipeArray<uint32_t> PipeArray32;

class PipeArray64 : public PipeArray<uint64_t>
{
public:
  template<typename T2>
  void setlo(const T2& token, uint64_t lo) {
    uint64_t& elem = at_reg(token);
    elem = (elem & ~((1ul<<32)-1)) | lo;
  }
  template<typename T2>
  void sethi(const T2& token, uint64_t hi) {
    uint64_t& elem = at_reg(token);
    elem = (elem & ((1ul<<32)-1)) | (hi<<32);
  }
};

class CSRegisterHandler
{
public:
    CodeobjTableTranslator table{};
    CodeobjTableTranslator table_from_start{};

    std::unordered_map<size_t, uint64_t> active_codeobj_id{};

    PipeArray64 wave_start_addr{};
    PipeArray64 current_codeobj_size{};
    PipeArray64 current_codeobj_addr{};
    PipeArray64 current_codeobj_id{};

    bool bIsTTVFormat = false;
    MarkerState userdata_state = ATT_MARKER_WAIT_FOR_HEADER;

    template<typename TokenType>
    uint32_t get_regaddr(const TokenType& token) { return token.regaddr; }

    template<typename TokenType>
    uint32_t get_regdata(const TokenType& token) { return token.regdata; }

    template<typename TokenType>
    ttv_user_data_header_codeobj TTVUserdataF(const TokenType& token) {
        return ttv_user_data_header_codeobj{.u32All = static_cast<uint32_t>(token.regdata)};
    }

    template<typename TokenType> bool isTTVUserdataState(const TokenType& token) {
        auto data = TTVUserdataF(token);
        return data.opcode == thread_trace_viewer_user_data_opcode_codeobj && data.reserved == 0;
    }

    template<typename TokenType> bool isTTVUserdataHeader(const TokenType& token)
    {
        uint32_t regdata = static_cast<uint32_t>(token.regdata);
        thread_trace_viewer_user_data_header_fourcc data{.u32All = regdata};
        return  data.opcode == thread_trace_viewer_user_data_opcode_fourcc &&
                data.char2 == 'R' && data.char3 == 'O' && data.char4 == 'C';
    }

    virtual bool IsPgmLo(size_t addr) = 0;
    virtual bool IsPgmHi(size_t addr) = 0;
    virtual bool IsUserdata(size_t addr) = 0;
    virtual bool IsUserdata0(size_t addr) = 0;
    virtual bool IsUserdata1(size_t addr) = 0;
    virtual bool IsUserdata2(size_t addr) = 0;
    virtual bool IsUserdata3(size_t addr) = 0;
    virtual ~CSRegisterHandler() {}

    template<typename TokenType>
    void UpdateRegCS(const TokenType& token)
    {
        if (IsPgmLo(token.regaddr))
            wave_start_addr.setlo(token, token.regdata);
        else if (IsPgmHi(token.regaddr))
            wave_start_addr.sethi(token, token.regdata);
    }

    template<typename TokenType>
    void UpdateRegNoCS(const TokenType& token)
    {
        if (!IsUserdata2(token.regaddr))
            return;

        if (isTTVUserdataHeader(token))
        {
            userdata_state = ATT_MARKER_WAIT_FOR_HEADER;
            return;
        }
        else if (userdata_state == ATT_MARKER_WAIT_FOR_HEADER)
        {
            if (isTTVUserdataState(token))
                userdata_state = static_cast<MarkerState>(TTVUserdataF(token).type);
            return;
        }

        if (userdata_state == ATT_MARKER_HEADER_CHANNEL)
        {
            aqlprofile_att_header_marker_t header{.raw = uint32_t(token.regdata)};
            uint64_t id = header.legacy_id;
            if (id == 0) // If not using legacy code ID
                id = current_codeobj_id.at_reg(token);

            auto it = active_codeobj_id.find(id);
            if (!header.isUnload && it == active_codeobj_id.end())
            {
                uint64_t base_addr = current_codeobj_addr.at_reg(token);
                active_codeobj_id.emplace(id, base_addr);
                address_range_t arange = {base_addr, current_codeobj_size.at_reg(token), id};
                table.insert(arange);
                if (header.bFromStart)
                    table_from_start.insert(arange);
            }
            else if (bIsTTVFormat && header.isUnload && it != active_codeobj_id.end())
            {
                try {
                    table.remove(active_codeobj_id.at(id));
                    active_codeobj_id.erase(id);
                } catch(...) {}
            }
        }
        else if (userdata_state == ATT_MARKER_ID_LO_CHANNEL)
            current_codeobj_id.setlo(token, token.regdata);
        else if (userdata_state == ATT_MARKER_ID_HI_CHANNEL)
            current_codeobj_id.sethi(token, token.regdata);
        else if (userdata_state == ATT_MARKER_SIZE_LO_CHANNEL)
            current_codeobj_size.setlo(token, token.regdata);
        else if (userdata_state == ATT_MARKER_SIZE_HI_CHANNEL)
            current_codeobj_size.sethi(token, token.regdata);
        else if (userdata_state == ATT_MARKER_ADDR_LO_CHANNEL)
            current_codeobj_addr.setlo(token, token.regdata);
        else if (userdata_state == ATT_MARKER_ADDR_HI_CHANNEL)
            current_codeobj_addr.sethi(token, token.regdata);

        userdata_state = ATT_MARKER_WAIT_FOR_HEADER;
    }

    template<typename TokenType>
    pcinfo_t get_wave_start(const TokenType& token) {
        return table.ToPcV2((wave_start_addr.at_reg(token) << 8) & ((1ul<<48)-1));
    }

    pcinfo_t get_wave_start_delayed(uint64_t addr) {
        return table_from_start.ToPcV2(addr);
    }
};
