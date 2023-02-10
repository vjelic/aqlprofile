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
#include "token.h"

const uint64_t WAVESLOT_STATE_EMPTY = 0;  // no wave dispatched to this slot yet
const uint64_t WAVESLOT_STATE_IDLE =
    1;  // between (wave_start, 1st instr) or (last instr, wave_end)
const uint64_t WAVESLOT_STATE_EXEC = 2;   // Wave in normal issue/exec loop
const uint64_t WAVESLOT_STATE_WAIT = 3;   // Wave in waitcnt model, waiting for mem data return
const uint64_t WAVESLOT_STATE_STALL = 4;  // Wave in stall state, waiting for issue arbitration
const uint64_t WAVESLOT_STATE_UNKNOWN = 5;  // Wave in stall state, waiting for issue arbitration

const uint64_t SQTT_ISSUE_NULL = 0;
const uint64_t SQTT_ISSUE_STALL = 1;
const uint64_t SQTT_ISSUE_INST = 2;
const uint64_t SQTT_ISSUE_IMMED = 3;

// SQTT Tokens
const uint64_t SQTT_TOKEN_WAVE_START = 3;
const uint64_t SQTT_TOKEN_WAVE_END = 6;
const uint64_t SQTT_TOKEN_INST = 10;
const uint64_t SQTT_TOKEN_ISSUE = 13;

// CU configuration (fixed)
const uint64_t SQTT_CFG_SIMDS = 4;
const uint64_t SQTT_CFG_WAVES = 10;


enum class WaveInstCategory {
  SMEM = 1,
  SALU = 2,
  VMEM = 3,
  FLAT = 4,
  LDS = 5,
  VALU = 6,
  JUMP = 7,
  NEXT = 8,
  IMMED = 9
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

struct instruction_t {
  instruction_t(uint64_t time, WaveInstCategory value, uint64_t issue2inst, uint64_t last)
      : time(time), issue2inst(issue2inst), last(last), value(value) {}

  uint64_t time;
  uint64_t issue2inst;
  uint64_t last;
  WaveInstCategory value;
};

typedef struct {
  uint64_t simd;
  uint64_t wave_id;
  uint64_t begin_time = 0;  // Begin and end cycle
  uint64_t end_time = 0;

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

  char* timeline_string = 0;
  char* instructions_string = 0;
} wavedata_t;

struct wave_t : public wavedata_t {
  wave_t() = default;

  std::vector<std::pair<uint64_t, uint64_t>> timeline;  // wave state in each cycle
  std::vector<instruction_t> instructions;              // (time, instruction_category)*

  uint64_t cur_state = 0;           // EMPTY, IDLE, EXEC, WAIT, STALL, initial state: EMPTY
  uint64_t state_start_cycle = 0;   // record the time of state transition
  uint64_t state_update_cycle = 0;  // record last cycle state is updated in EXEC (issue->inst loop)

  // Internal state: Stalled, Mem access started, instr issue started
  uint64_t stall_started = 0;  // [Internal] indicating STALL starts, get stall cycles
  // [Internal] mem instruction issued. paired with IMMED to get latency
  uint64_t mem_access_started = 0;
  uint64_t issue_time = 0;  // use to calculate instruction cycles
  uint64_t inst_time = 0;   // use to calculate instruction cycles

  typedef std::array<std::array<std::vector<wave_t>, SQTT_CFG_WAVES>, SQTT_CFG_SIMDS> WaveArray;
  static std::pair<WaveArray, std::vector<perfevent_t>> sqtt_simd_analysis(
                                                      std::vector<Token>& tokens,
                                                      uint64_t target_cu = 0);

  static std::unordered_map<int, std::string> inst_type_dict;
  static std::unordered_map<int, std::string> token_name_dict;
  static std::unordered_map<int, std::string> misc_token_type_dict;
};

using WaveArray = wave_t::WaveArray;
