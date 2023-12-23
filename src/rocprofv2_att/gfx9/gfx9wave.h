/* Copyright (c) 2022 Advanced Micro Devices, Inc.

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
#include "gfx9token.h"
#include <set>
#include "../trace_parser.hpp"

struct gfx9wave_t : public WaveDataInternal {
    gfx9wave_t() = default;
    gfx9wave_t(class gfx9Token&);

    static constexpr uint64_t SQTT_CFG_SIMDS = 4;
    static constexpr uint64_t SQTT_CFG_WAVES = 10;

    uint64_t cur_state = 0;           // EMPTY, IDLE, EXEC, WAIT, STALL, initial state: EMPTY
    int64_t state_start_cycle = 0;   // record the time of state transition
    int64_t state_update_cycle = 0;  // record last cycle state is updated in EXEC (issue->inst loop)

    // Internal state: Stalled, Mem access started, instr issue started
    bool stall_started = false;  // [Internal] indicating STALL starts, get stall cycles
    // [Internal] mem instruction issued. paired with IMMED to get latency
    uint64_t mem_access_started = 0;
    uint64_t issue_time = 0;  // use to calculate instruction cycles
    uint64_t inst_time = 0;   // use to calculate instruction cycles
    int last_jump_inst = -1;
    int64_t last_message_time = 0;
    int64_t stall_start_time;
    std::set<size_t> issued_instructions{};

    typedef std::array<std::array<std::vector<gfx9wave_t>, SQTT_CFG_WAVES>, SQTT_CFG_SIMDS> WaveArray;
    static std::tuple<
    WaveArray,
    std::vector<att_perfevent_t>,
    std::vector<occupancy_info_t>,
    std::vector<uint64_t>
    > sqtt_simd_analysis(std::vector<gfx9Token>& tokens, int target_cu = 1);

    static std::unordered_map<int, std::string> inst_type_dict;
    static std::unordered_map<int, std::string> token_name_dict;
    static std::unordered_map<int, std::string> misc_token_type_dict;

    void complete_wave(gfx9Token& token);
    void apply_inst(gfx9Token& token);
    void apply_pc(gfx9Token& token, CodeobjTableTranslator& table);
    int64_t apply_issue(uint64_t wave_status, int64_t token_time);
    static int64_t array_apply_issue(gfx9Token& token, WaveArray& SIMD);

    static std::atomic<int> global_target_cu;
};

class CSRegisterHandlerGFX9: public CSRegisterHandler
{
    static constexpr size_t SQTT_TOKEN_REG = 2;
    static constexpr size_t SQTT_TOKEN_REG_CS = 5;
    static constexpr size_t SQTT_TOKEN_REG_CS_PRIV = 15;

    static constexpr size_t COMPUTE_PGM_LO = 0xC;
    static constexpr size_t COMPUTE_PGM_HI = 0xD;
    static constexpr size_t USERDATA_ADDR_0 = 0xC340;
    static constexpr size_t USERDATA_ADDR_1 = 0xC341;
    static constexpr size_t USERDATA_ADDR_2 = 0xC342;
    static constexpr size_t USERDATA_ADDR_3 = 0xC343;
public:
    bool IsRegCS(size_t type) { return type == SQTT_TOKEN_REG_CS || type == SQTT_TOKEN_REG_CS_PRIV; };
    bool IsRegNoCS(size_t type) { return type == SQTT_TOKEN_REG; };

    virtual bool IsPgmLo(size_t addr) override { return addr == COMPUTE_PGM_LO; };
    virtual bool IsPgmHi(size_t addr) override { return addr == COMPUTE_PGM_HI; };

    virtual bool IsUserdata(size_t addr) override {
        return addr >= USERDATA_ADDR_0 && addr <= USERDATA_ADDR_3;
    };
    virtual bool IsUserdata0(size_t addr) override { return addr == USERDATA_ADDR_0; };
    virtual bool IsUserdata1(size_t addr) override { return addr == USERDATA_ADDR_1; };
    virtual bool IsUserdata2(size_t addr) override { return addr == USERDATA_ADDR_2; };
    virtual bool IsUserdata3(size_t addr) override { return addr == USERDATA_ADDR_3; };
};