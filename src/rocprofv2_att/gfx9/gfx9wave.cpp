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

#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include "gfx9wave.h"

typedef gfx9Token Token;

#define empty_wave_check(waveslot_size) if (waveslot_size == 0) { continue; }

using WaveArray = gfx9wave_t::WaveArray;
typedef gfx9wave_t wave_t;

// const std::string waveslot_state[] = {"EMPTY", "IDLE", "EXEC", "WAIT", "STALL"};
// const std::string issue_state[] = {"NULL", "STALL", "INST", "IMMED"};

/*
std::unordered_map<int, std::string> wave_t::inst_type_dict = {
  {0, "INST_SMEM_RD"},          {1, "INST_SALU_32"},          {2, "INST_VMEM_RD"},
  {3, "INST_VMEM_WR"},          {4, "INST_FLAT_WR"},          {5, "INST_VALU_32"},
  {6, "INST_LDS"},              {7, "INST_PC"},               {8, "INST_EXPREQ_GDS"},
  {9, "INST_EXPREQ_GFX"},       {10, "INST_EXPGNT_PAR_COL"},  {11, "INST_EXPGNT_POS_GDS"},
  {12, "INST_JUMP"},            {13, "INST_NEXT"},            {14, "INST_FLAT_RD"}, 
  {15, "INST_OTHER_MSG"},       {16, "INST_SMEM_WR"},         {17, "INST_SALU_64"},
  {18, "INST_VALU_64"},         {19, "INST_SMEM_RD_REPLAY"},  {20, "INST_SMEM_WR_REPLAY"},
  {21, "INST_VMEM_RD_REPLAY"},  {22, "INST_VMEM_WR_REPLAY"},  {23, "INST_FLAT_WR_REPLAY"},
  {24, "INST_FLAT_RD_REPLAY"},  {25, "INST_FATAL_HALT"},      {26, "INST_DIDT_STALL_START"},
  {27, "INST_DIDT_STALL_END"},  {28, "INST_VALU_MAI"},        {-1, "IMMED"}, {-2, "STALL"}
};

std::unordered_map<int, std::string> wave_t::token_name_dict = {
  {0, "TOKEN_MISC"},           {1, "TOKEN_TIMESTAMP"},  {2, "TOKEN_REG"},
  {3, "TOKEN_WAVE_START"},     {4, "TOKEN_WAVE_ALLOC"}, {5, "TOKEN_REG_CSPRIV"},
  {6, "TOKEN_WAVE_END"},       {7, "TOKEN_EVENT"},      {8, "TOKEN_EVENT_CS"},
  {9, "TOKEN_EVENT_GFX1"},     {10, "TOKEN_INST"},      {11, "TOKEN_INST_PC"},
  {12, "TOKEN_INST_USERDATA"}, {13, "TOKEN_ISSUE"},     {14, "TOKEN_PERF"},
  {15, "TOKEN_REG_CS"},
};

std::unordered_map<int, std::string> wave_t::misc_token_type_dict = {
    {0, "TIME"},      {1, "TIME_RESET"},         {2, "PACKET_LOST"},
    {3, "SURF_SYNC"}, {4, "TTRACE_STALL_BEGIN"}, {5, "TTRACE_STALL_END"}
}; 
void print_token(Token& token) {
  std::cout << wave_t::token_name_dict[token.type];
  if (token.type==0) std::cout << " misc:" << wave_t::misc_token_type_dict[token.misc_type] << std::endl;
  if (token.type==3) std::cout << " start: " << token.cu << " " << token.simd << " " << token.wave << std::endl;
}
//*/

const uint64_t SQTT_ISSUE_NULL = 0;
const uint64_t SQTT_ISSUE_STALL = 1;
const uint64_t SQTT_ISSUE_INST = 2;
const uint64_t SQTT_ISSUE_IMMED = 3;

// SQTT Tokens
const uint64_t SQTT_TOKEN_WAVE_START = 3;
const uint64_t SQTT_TOKEN_WAVE_END = 6;
const uint64_t SQTT_TOKEN_INST = 10;
const uint64_t SQTT_TOKEN_ISSUE = 13;
const uint64_t SQTT_PERFCOUNTER_TOKEN = 14;

wave_t::gfx9wave_t(Token& token) {
  this->begin_time = token.time;
  // State: EMPTY -> IDLE
  this->cur_state = WAVESLOT_STATE::WS_IDLE;
  this->state_start_cycle = token.time;
}

void wave_t::complete_wave(Token& token) {
  uint64_t state_update_cycle = std::min(this->state_update_cycle, token.time);
  uint64_t state_start_cycle = std::min(state_update_cycle, this->state_start_cycle);

  // State: EXEC -> IDLE -> EMPTY
  timeline.push_back(
      std::make_pair(WAVESLOT_STATE::WS_EXEC, state_update_cycle - state_start_cycle));
  timeline.push_back(
      std::make_pair(WAVESLOT_STATE::WS_IDLE, token.time - state_update_cycle));

  this->cur_state = WAVESLOT_STATE::WS_EMPTY;
  this->state_start_cycle = token.time;

  // update CU time, the last completed wave
  this->end_time = token.time;
}


void wave_t::apply_inst(Token& token) {
  this->end_time = token.time;
  this->inst_time = token.time;

  this->state_update_cycle = token.time;
  uint64_t issue2inst = token.time - std::min(this->issue_time, token.time);

  // ISSUE stall type cannot be known until issue complete
  // SMEM RD/WR
  if (token.inst_type == 0 || token.inst_type == 16) {
    if (this->stall_started == 1) {
      this->num_smem_stalls += 1;
      this->stall_started = 0;
    }

    this->num_smem_instrs += 1;
    this->num_mem_instrs += 1;

    // start of mem transaction
    this->mem_access_started = 1;
    this->instructions.push_back({token.time, WaveInstCategory::SMEM, issue2inst, 0});
  } else if (token.inst_type == 1 || token.inst_type == 17) {  // SALU32/64 instr
    if (this->stall_started == 1) {
      this->num_salu_stalls += 1;
      this->stall_started = 0;
    }

    this->num_salu_instrs += 1;
    this->instructions.push_back({token.time, WaveInstCategory::SALU, issue2inst, 0});
  } else if (token.inst_type == 2 || token.inst_type == 3) {  // VMEM RD/WR
    if (this->stall_started == 1) {
      this->num_vmem_stalls += 1;
      this->stall_started = 0;
    }

    this->num_vmem_instrs += 1;
    this->num_mem_instrs += 1;

    // start of mem transaction
    this->mem_access_started = 1;
    this->instructions.push_back({token.time, WaveInstCategory::VMEM, issue2inst, 0});
  } else if (token.inst_type == 4 || token.inst_type == 14) {  // FLAT RD/WR
    if (this->stall_started == 1) {
      this->num_flat_stalls += 1;
      this->stall_started = 0;
    }

    this->num_flat_instrs += 1;
    this->num_mem_instrs += 1;

    this->mem_access_started = 1;
    this->instructions.push_back({token.time, WaveInstCategory::FLAT, issue2inst, 0});
  } else if (token.inst_type == 6) {  // LDS
    if (this->stall_started == 1) {
      this->num_lds_stalls += 1;
      this->stall_started = 0;
    }

    this->num_lds_instrs += 1;
    this->num_mem_instrs += 1;

    this->mem_access_started = 1;
    this->instructions.push_back({token.time, WaveInstCategory::LDS, issue2inst, 0});
  } else if (token.inst_type == 5 || token.inst_type == 18 || token.inst_type == 28) {  // VALU32/64 instr
    if (this->stall_started == 1) {
      this->num_valu_stalls += 1;
      this->stall_started = 0;
    }

    this->num_valu_instrs += 1;
    this->instructions.push_back({token.time, WaveInstCategory::VALU, issue2inst, 0});
  } else if (token.inst_type == 12 || token.inst_type == 13) {  // Branch
    if (this->stall_started == 1) {
      this->num_branch_stalls += 1;
      this->stall_started = 0;
    }

    this->num_branch_instrs += 1;
    if (token.inst_type == 13) {
      this->num_branch_taken_instrs += 1;
      this->instructions.push_back({token.time, WaveInstCategory::NEXT, issue2inst, 0});
    } else {
      this->instructions.push_back({token.time, WaveInstCategory::JUMP, issue2inst, 0});
    }
  }
}

int64_t wave_t::array_apply_issue(Token& token, WaveArray& SIMD) {
  int64_t active_issue_cycle = 0;
  for (uint64_t wave_id = 0; wave_id < token.inst.size(); wave_id++) {
    uint64_t wave_status = token.inst[wave_id];
    if (wave_status == SQTT_ISSUE_NULL)
      continue;

    empty_wave_check(SIMD[token.simd][wave_id].size());
    wave_t& waveid_token = SIMD[token.simd][wave_id].back();

    active_issue_cycle += waveid_token.apply_issue(wave_status, token.time);
  }
  // number of cycles with instructions issued
  return active_issue_cycle;
}

std::tuple<WaveArray, std::vector<perfevent_t>, std::vector<occupancy_info_t>>
wave_t::sqtt_simd_analysis(std::vector<Token>& tokens, int target_cu) {
  bool bHasLostPackets = false;
  WaveArray SIMD;
  int64_t total_num_issue_cycles = 0;
  int num_waves_started = 0;
  int num_waves_completed = 0;
  std::vector<perfevent_t> perfEvents{};
  std::vector<occupancy_info_t> occupancy = {};
  std::array<int, 16> current_occupancy = {};

  for (size_t t = 0; t<tokens.size(); t++) {
    Token& token = tokens[t];

    if (token.type == 0 && token.misc_type == 2) {// Packet lost
      bHasLostPackets = true;
    } else if (token.type == SQTT_TOKEN_WAVE_START) {  // Wave start
      if ((int)token.cu == target_cu)
        SIMD[token.simd][token.wave].push_back(wave_t(token));
      current_occupancy[token.cu & 0xF] += 1;
      occupancy.push_back(occupancy_info_t{
        (uint64_t)token.cu,
        (uint64_t)current_occupancy[token.cu & 0xF],
        (uint64_t)token.time
      });
      num_waves_started += 1;
    } else if (token.type == SQTT_TOKEN_WAVE_END) {  // Wave stop
      if ((int)token.cu == target_cu) {
        empty_wave_check(SIMD[token.simd][token.wave].size());
        SIMD[token.simd][token.wave].back().complete_wave(token);
      }
      current_occupancy[token.cu & 0xF] -= 1;
      occupancy.push_back(occupancy_info_t{
        (uint64_t)token.cu,
        (uint64_t)current_occupancy[token.cu & 0xF],
        (uint64_t)token.time}
      );
      num_waves_completed += 1;
    } else if (token.type == SQTT_TOKEN_INST) {  // Update timestamp for executed inst
      empty_wave_check(SIMD[token.simd][token.wave].size());
      SIMD[token.simd][token.wave].back().apply_inst(token);
    } else if (token.type == SQTT_TOKEN_ISSUE) {
      int64_t active_cycles = array_apply_issue(token, SIMD);
      total_num_issue_cycles += active_cycles;
    } else if (token.type == SQTT_PERFCOUNTER_TOKEN)
      perfEvents.push_back(perfevent_t{
        token.time - 4*token.cu,
        (uint16_t)token.cntr[0],
        (uint16_t)token.cntr[1],
        (uint16_t)token.cntr[2],
        (uint16_t)token.cntr[3],
        (uint8_t)token.cu,
        (uint8_t)token.cntr_bank
      });
  }

  if (bHasLostPackets)
    std::cout << "Warning: Packet lost!" << std::endl;

  return std::make_tuple(SIMD, perfEvents, occupancy);
}

int64_t wave_t::apply_issue(uint64_t wave_status, uint64_t token_time) {
  int64_t active_issue_cycle = 0;
  uint64_t inst_issue_time = token_time - std::min(this->inst_time, token_time);

#if 0
  if (instructions.size())
      instructions.back().last = inst_issue_time;
#else
  if (instructions.size()) {
    if (instructions.back().value == (uint64_t)WaveInstCategory::IMMED)
      instructions.back().last += inst_issue_time;
    else
      instructions.back().last = inst_issue_time;  // v_mul_lo_u32 gets 2 tokens
  }
#endif
  if (wave_status == SQTT_ISSUE_IMMED) {
#if 0
    instructions.push_back({this->inst_time, WaveInstCategory::IMMED, 0, 0});
#else     // May not add up to correct number of cycles
    if (instructions.size()) {
      instructions.back().last -= inst_issue_time-4;
      inst_issue_time = (inst_issue_time > 4) ? (inst_issue_time-4) : 0;
    }
    instructions.push_back({this->inst_time + 4,
                          WaveInstCategory::IMMED, 0, inst_issue_time});
#endif
    this->inst_time = token_time;

    uint64_t cur_state = this->cur_state;
    uint64_t mem_access_started = this->mem_access_started;

    if (cur_state == WAVESLOT_STATE::WS_EXEC && mem_access_started == 1) {
      // Align by hand
      uint64_t state_update_cycle = std::min(token_time, this->state_update_cycle+4);
      uint64_t state_start_cycle = std::min(this->state_start_cycle, state_update_cycle);
      // EXEC -> WAIT -> EXEC
      this->timeline.push_back(
          std::make_pair(WAVESLOT_STATE::WS_EXEC, state_update_cycle - state_start_cycle));
      this->timeline.push_back(
          std::make_pair(WAVESLOT_STATE::WS_WAIT, token_time - state_update_cycle));

      this->cur_state = WAVESLOT_STATE::WS_EXEC;
      this->state_start_cycle = token_time;
      this->state_update_cycle = token_time;

      // reset the mem access transaction cycle
      this->mem_access_started = 0;
    }
  } else if (wave_status == SQTT_ISSUE_STALL) {
    this->stall_started = 1;

    // State: IDLE/EXEC -> STALL
    uint64_t cur_state = this->cur_state;
    uint64_t state_start_cycle = std::min(this->state_start_cycle, token_time);

    this->timeline.push_back(
        std::make_pair(cur_state, token_time - state_start_cycle));

    this->cur_state = WAVESLOT_STATE::WS_STALL;
    this->state_start_cycle = token_time;

  } else if (wave_status == SQTT_ISSUE_INST) {
    // there are normal instructions issued in this cycle
    active_issue_cycle = 1;  // INST issue to pipeline in this cycle

    this->issue_time = token_time;
    this->num_issued_instrs += 1;

    // state transitions, no explicit WAIT->EXEC
    uint64_t cur_state = this->cur_state;
    if (cur_state == WAVESLOT_STATE::WS_IDLE) {
      // Issue INST in EMPTY state is illegal, added to work around SQTT issue
      // fist instr in this wave, State: IDLE -> EXEC
      uint64_t state_start_cycle = std::min(this->state_start_cycle, token_time);
      this->timeline.push_back(
          std::make_pair(cur_state, token_time - state_start_cycle));
      this->state_start_cycle = token_time;
    } else if (cur_state == WAVESLOT_STATE::WS_STALL) {
      // State: STALL -> EXEC
      uint64_t state_start_cycle = std::min(this->state_start_cycle, token_time);
      this->timeline.push_back(
          std::make_pair(WAVESLOT_STATE::WS_STALL, token_time - state_start_cycle));
      this->state_start_cycle = token_time;
    } else if (cur_state == WAVESLOT_STATE::WS_EMPTY) {
      // this is exception, should not happen. observed in SQTT extend timeline
      uint64_t state_start_cycle = std::min(this->state_start_cycle, token_time);
      this->timeline.push_back(
          std::make_pair(cur_state, token_time - state_start_cycle));
      this->state_start_cycle = token_time;
    }
    this->cur_state = WAVESLOT_STATE::WS_EXEC;
    this->state_update_cycle = token_time;
  }
  return active_issue_cycle;
}
