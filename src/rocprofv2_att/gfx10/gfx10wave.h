/* Copyright (c) 2023 Advanced Micro Devices, Inc.

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
#include "../wave.h"
#include "gfx10parser.h"

struct gfx10wave_t : public wavedata_t {
  gfx10wave_t() = default;
  gfx10wave_t(class gfx10Token&, int64_t last_completed_wave_cycle, int tg_simd);

  std::vector<std::pair<uint64_t, uint64_t>> timeline;  // wave state in each cycle
  std::vector<instruction_t> instructions;              // (time, instruction_category)*

  int64_t last_state_cycle = 0;   //  record the time of state transition
  int64_t last_state_duration = 0; // record minimum how long the state should last
  WAVESLOT_STATE cur_state = WAVESLOT_STATE::WS_EMPTY;

  /*
  int64_t cur_state = 0;           // EMPTY, IDLE, EXEC, WAIT, STALL, initial state: EMPTY
  int64_t state_update_cycle = 0;  // record last cycle state is updated in EXEC (issue->inst loop)
  int64_t mem_access_started = 0;

  // Internal state: Stalled, Mem access started, instr issue started
  int64_t stall_started = 0;  // [Internal] indicating STALL starts, get stall cycles
  // [Internal] mem instruction issued. paired with IMMED to get latency
  int64_t issue_time = 0;  // use to calculate instruction cycles
  int64_t inst_time = 0;   // use to calculate instruction cycles */

  uint64_t last_jump_inst = 0;
  int target_simd = 0;
  bool ImmFromBranch = false;

  void complete_wave(gfx10Token& token);
  void apply_inst(gfx10Token token, inst_type inst, int tt_version);
  void apply_valu_inst(gfx10Token token, valu_inst_type inst);
  void apply_immediate(gfx10Token token);
  void update_immediate(int64_t token_time);
  void set_state_exec(int64_t time, int64_t duration);
  operator bool() const { return true; } // TODO: Change based on cur_state

  static constexpr uint64_t SQTT_CFG_WAVES = 32;
  static int dp_cycles;
  static int dp_derate;

  typedef std::array<std::vector<gfx10wave_t>, SQTT_CFG_WAVES> WaveArray;
  static std::tuple<WaveArray, std::vector<perfevent_t>, std::vector<occupancy_info_t>>
                    sqtt_simd_analysis(std::vector<gfx10Token>& tokens, int target_cu = 1);

  //static std::unordered_map<int, const char*> INST_NAMES;
  static std::pair<WaveInstCategory, uint16_t> inst_map_to_gfx9(int einst);
};

