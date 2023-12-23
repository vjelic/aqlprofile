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

#define AMD_AQLPROFILE_SQTT_NPI
#define SQTT_PARSER_VERSION 4
#define OCCUPANCY_RESOLUTION 8
#define PCINFO_OFFSET_BITS 34
#define PCINFO_ID_BITS 28

struct occupancy_info_t : public att_occupancy_info_t
{
    occupancy_info_t() = default;
    occupancy_info_t(
        uint64_t kid, uint64_t simd, uint64_t slot,
        uint64_t enable, uint64_t cu, int64_t time)
    {
        this->kernel_id = kid;
        this->simd = simd;
        this->slot = slot;
        this->enable = enable;
        this->cu = cu;
        this->time = time;
#ifndef AMD_AQLPROFILE_SQTT_NPI
        this->time &= ~0x7ul; // Makes the time information have a granularity of 64 cycles
        this->simd = 0;
        this->slot = 0;
#endif
    }
};

struct Instruction
{
    Instruction() = default;
    Instruction(int64_t time, WaveInstCategory value, uint64_t issue2inst, int64_t last)
            : time(time), value((int64_t)value), issue2inst(issue2inst), last(last) {}

    wave_instruction_t getTiming() const { return {time, std::max(issue2inst, last)}; }

    int64_t time;
    int64_t value;
    int64_t issue2inst;
    int64_t last;
};

struct InstructionExt
{
    InstructionExt() = default;
    InstructionExt(WaveInstCategory value, uint64_t num_waves, uint64_t cycles)
            : num_waves(num_waves), value((uint64_t)value), cycles(cycles) {}
    InstructionExt(const Instruction& inst):
        num_waves(1), value(inst.value), cycles(std::max(inst.last, inst.issue2inst)) {};

    int64_t num_waves = 0;
    int64_t value = 0;
    int64_t cycles = 0;

    // TODO: Compare PCs
    inline bool operator==(const Instruction& other) const { return !(*this != other); };
    inline bool operator!=(const Instruction& other) const {
        return this->value != other.value ||
            (value == WaveInstCategory::PCINFO && cycles != other.issue2inst);
    };
    InstructionExt& operator+=(const Instruction& other) {
        num_waves += 1;
        if (value != WaveInstCategory::PCINFO)
            cycles += std::max(other.last, other.issue2inst);
        return *this;
    };
};

struct WaveDataInternal : public wave_data_t
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
    std::vector<uint64_t> kernel_ids_addr;
    std::vector<int64_t> traceIDs;
    std::vector<uint64_t> tracesizes;
    std::vector<InstructionExt*> tracedata;
    std::vector<std::vector<InstructionExt>> traces;
    std::vector<occupancy_info_t> occupancy;
    std::vector<att_perfevent_t> perfevents;
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
    att_output_flags_t flags;
    uint64_t id;

    uint64_t num_kernel_ids;
    uint64_t num_traces;
    uint64_t num_events;
    uint64_t num_occupancy;
};

std::unique_ptr<CppReturnInfo>
AnalyseBinary_internal(const uint8_t* buffer, int BUFFER_SIZE, int target_cu);

typedef union {
    uint64_t raw;
    struct {
        uint64_t addr : 62;
        uint64_t header : 2;
    } addr;
    struct {
        uint64_t offset : PCINFO_OFFSET_BITS;
        uint64_t id : PCINFO_ID_BITS;
        uint64_t header : 2;
    } codeobj;
} pcinfo_t;

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

enum CSRegisterHandlerState
{
    CSRegisterID = 0,
    CSRegisterSizeLo = 1,
    CSRegisterAddrLo = 2,
    CSRegisterAddrHi = 3,
    CSRegisterSizeHi = 4,
    CSRegisterWaitForHeader = 32
};

class CSRegisterHandler
{
public:
    CodeobjTableTranslator table{};
    CodeobjTableTranslator table_from_start{};

    std::unordered_map<uint32_t, uint64_t> active_codeobj_id{};

    PipeArray64 wave_start_addr{};
    PipeArray64 current_codeobj_size{};
    PipeArray64 current_codeobj_addr{};

    bool bIsTTVFormat = false;
    CSRegisterHandlerState userdata_state = CSRegisterWaitForHeader;

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
        if (!IsUserdata(token.regaddr))
            return;
        else if (bIsTTVFormat && !IsUserdata2(token.regaddr))
            return;

        if (IsUserdata2(token.regaddr) && isTTVUserdataHeader(token))
        {
            bIsTTVFormat = true;
            userdata_state = CSRegisterWaitForHeader;
            return;
        }

        if (bIsTTVFormat)
        {
            if (userdata_state == CSRegisterWaitForHeader)
            {
                if (isTTVUserdataState(token))
                    userdata_state = static_cast<CSRegisterHandlerState>(TTVUserdataF(token).type);
                return;
            }
        }
        else
        {
            if (IsUserdata0(token.regaddr))
                userdata_state = CSRegisterID;
            else if (IsUserdata1(token.regaddr))
                userdata_state = CSRegisterSizeLo;
            else if (IsUserdata2(token.regaddr))
                userdata_state = CSRegisterAddrLo;
            else if (IsUserdata3(token.regaddr))
                userdata_state = CSRegisterAddrHi;
            else
                return;
        }


        if (userdata_state == CSRegisterID)
        {
            uint32_t id = token.regdata >> 2;
            uint32_t bFromStart = (token.regdata >> 1) & 0x1;
            uint32_t type = token.regdata & 0x1;

            auto it = active_codeobj_id.find(id);
            if (type == 0 && it == active_codeobj_id.end())
            {
                uint64_t base_addr = current_codeobj_addr.at_reg(token);
                active_codeobj_id.emplace(id, base_addr);
                address_range_t arange = {base_addr, current_codeobj_size.at_reg(token), id};
                table.insert(arange);
                if (bFromStart)
                    table_from_start.insert(arange);
            }
            else if (bIsTTVFormat && type == 1 && it != active_codeobj_id.end())
            {
                try {
                    table.remove(active_codeobj_id.at(id));
                    active_codeobj_id.erase(id);
                } catch(...) {}
            }
        }
        else if (userdata_state == CSRegisterSizeLo)
            current_codeobj_size.setlo(token, token.regdata);
        else if (userdata_state == CSRegisterSizeHi)
            current_codeobj_size.sethi(token, token.regdata);
        else if (userdata_state == CSRegisterAddrLo)
            current_codeobj_addr.setlo(token, token.regdata);
        else if (userdata_state == CSRegisterAddrHi)
            current_codeobj_addr.sethi(token, token.regdata);

        userdata_state = CSRegisterWaitForHeader;
    }

    template<typename TokenType>
    uint64_t get_wave_start(const TokenType& token) {
        return table.ToPcV2((wave_start_addr.at_reg(token) << 8) & ((1ul<<48)-1));
    }

    uint64_t get_wave_start_delayed(uint64_t addr) {
        return table_from_start.ToPcV2(addr);
    }
};
