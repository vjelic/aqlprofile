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
#include <map>

typedef gfx9Token Token;
std::atomic<int> gfx9wave_t::global_target_cu{0};

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
  if (token.type==0) std::cout << " misc:" << wave_t::misc_token_type_dict[token.misc_type] << stgfx9wave_td::endl;
  if (token.type==3) std::cout << " start: " << token.cu << " " << token.simd << " " << token.wave << std::endl;
}
//*/

const uint64_t SQTT_ISSUE_NULL = 0;
const uint64_t SQTT_ISSUE_STALL = 1;
const uint64_t SQTT_ISSUE_INST = 2;
const uint64_t SQTT_ISSUE_IMMED = 3;

// SQTT Tokens
const uint64_t SQTT_TOKEN_REG = 2;
const uint64_t SQTT_TOKEN_WAVE_START = 3;
const uint64_t SQTT_TOKEN_REG_CS = 5;
const uint64_t SQTT_TOKEN_WAVE_END = 6;
const uint64_t SQTT_TOKEN_INST = 10;
const uint64_t SQTT_INST_PC = 11;
const uint64_t SQTT_TOKEN_ISSUE = 13;
const uint64_t SQTT_PERFCOUNTER_TOKEN = 14;
const uint64_t SQTT_TOKEN_REG_CS_PRIV = 15;

wave_t::gfx9wave_t(Token& token) {
  this->begin_time = token.time;
  this->cur_state = WAVESLOT_STATE::WS_IDLE;
  this->state_start_cycle = token.time;
  this->simd = token.simd;
  this->wave_id = token.wave;
  this->end_time = 0;
}


void wave_t::complete_wave(Token& token) {
  // State: EXEC -> IDLE -> EMPTY
  if (state_start_cycle < token.time)
    timeline.push_back(std::make_pair(WAVESLOT_STATE::WS_IDLE, token.time - state_start_cycle));

  this->cur_state = WAVESLOT_STATE::WS_EMPTY;
  this->state_start_cycle = token.time;

  // update CU time, the last completed wave
  this->end_time = token.time;
}


void wave_t::apply_inst(Token& token)
{
  if (this->trap_status != WaveTrapStatus::TRAP_RESTORED || !issued_instructions.size())
    return;

  this->inst_time = token.time;
  Instruction& the_inst = instructions.at(*issued_instructions.begin());
  the_inst.issue2inst = token.time - the_inst.time;
  int64_t phase = (16-global_target_cu.load()+simd)%4;

  // ISSUE stall type cannot be known until issue complete
  // SMEM RD/WR

  if (token.inst_type == 0 || token.inst_type == 16) {
    if (this->stall_started == 1)
      this->num_smem_stalls += 1;

    this->num_smem_instrs += 1;
    this->num_mem_instrs += 1;
    the_inst.value = WaveInstCategory::SMEM;
    // Phase correction
    the_inst.issue2inst = std::max(the_inst.issue2inst - 4*(phase==3), 4l);
  } else if (token.inst_type == 1 || token.inst_type == 17) {  // SALU32/64 instr
    if (this->stall_started == 1)
      this->num_salu_stalls += 1;

    this->num_salu_instrs += 1;
    the_inst.value = WaveInstCategory::SALU;
    // Phase correction
    the_inst.issue2inst = std::max(the_inst.issue2inst - 4*(phase==3), 4l);
  } else if (token.inst_type == 2 || token.inst_type == 3) {  // VMEM RD/WR
    if (this->stall_started == 1)
      this->num_vmem_stalls += 1;

    this->num_vmem_instrs += 1;
    this->num_mem_instrs += 1;
    the_inst.value = WaveInstCategory::VMEM;
  } else if (token.inst_type == 4 || token.inst_type == 14) {  // FLAT RD/WR
    if (this->stall_started == 1)
      this->num_flat_stalls += 1;

    this->num_flat_instrs += 1;
    this->num_mem_instrs += 1;
    the_inst.value = WaveInstCategory::FLAT;
  } else if (token.inst_type == 6) {  // LDS
    if (this->stall_started == 1)
      this->num_lds_stalls += 1;

    this->num_lds_instrs += 1;
    this->num_mem_instrs += 1;
    the_inst.value = WaveInstCategory::LDS;
  } else if (token.inst_type == 5 || token.inst_type == 18 || token.inst_type == 28) {  // VALU32/64 instr
    if (this->stall_started == 1)
      this->num_valu_stalls += 1;

    this->num_valu_instrs += 1;
    the_inst.value = WaveInstCategory::VALU;
    // Phase correction
    the_inst.issue2inst = std::max(the_inst.issue2inst, 4l*(phase>=2));
  } else if (token.inst_type == 12 || token.inst_type == 13) {  // Branch
    if (this->stall_started == 1)
      this->num_branch_stalls += 1;

    this->num_branch_instrs += 1;
    the_inst.value = WaveInstCategory::NEXT;
    if (token.inst_type == 12) {
      this->num_branch_taken_instrs += 1;
      the_inst.value = WaveInstCategory::JUMP;
    }
  } else if (token.inst_type == 7) {
    the_inst.value = WaveInstCategory::SALU;
    auto inst = Instruction{token.time, WaveInstCategory::PCINFO, 0, 0};
    this->last_jump_inst = instructions.size();
    instructions.push_back(inst);
  } else {
    if (token.inst_type == 15)
      last_message_time = token.time;
    instructions.erase(instructions.begin()+*issued_instructions.begin());
  }

  if (instructions.size() && stall_started)
  {
    int64_t min_stall_cycles = 4l;
    if (phase && the_inst.value == WaveInstCategory::LDS)
      min_stall_cycles = 8ul;

    the_inst.time = stall_start_time;
    the_inst.last = std::max(token.time - the_inst.time, min_stall_cycles);
    stall_started = false;
  }

  issued_instructions.erase(issued_instructions.begin());
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

static uint64_t getGPULocation(const Token& token) {
  return token.wave | (token.simd<<5) | (token.cu<<7);
}

std::tuple<
  WaveArray,
  std::vector<att_perfevent_t>,
  std::vector<occupancy_info_t>,
  std::vector<uint64_t>
>
wave_t::sqtt_simd_analysis(std::vector<Token>& tokens, int target_cu)
{
  global_target_cu.store(target_cu);
  bool bHasLostPackets = false;
  WaveArray SIMD;
  int64_t total_num_issue_cycles = 0;
  int num_waves_started = 0;
  int num_waves_completed = 0;
  std::vector<att_perfevent_t> perfEvents{};
  std::vector<occupancy_info_t> occupancy = {};

  // data from all waves
  auto running_waves = std::unordered_map<uint64_t, uint64_t>{};

  CSRegisterHandlerGFX9 csregister;

  for (size_t t = 0; t<tokens.size(); t++)
  {
    Token& token = tokens[t];

    if (token.type == 0)
    {
      if (token.misc_type == 2)
      {
        bHasLostPackets = true;
      }
      else if (token.misc_type == 6)
      {
        for (auto& simd : SIMD)
        for (auto& slot : simd)
        if (slot.size() && slot.back().end_time == 0)
          slot.back().trap_status = WaveTrapStatus::TRAP_REQUEST;
      }
    }
    else if (token.type == SQTT_TOKEN_WAVE_START) // Wave start
    {
      uint64_t wave_addr = csregister.get_wave_start(token);

      if ((int)token.cu == target_cu && token.sh == 0)
      {
        if (token.count > 64)
        {
          if (!SIMD[token.simd][token.wave].size()) continue;
          auto& wave = SIMD[token.simd][token.wave].back();

          if (wave.trap_status == WaveTrapStatus::TRAP_REQUEST || WaveTrapStatus::TRAP_SAVED)
            wave.trap_status = WaveTrapStatus::TRAP_STANDBY;
          else if(wave.trap_status == WaveTrapStatus::TRAP_STANDBY)
            wave.trap_status = WaveTrapStatus::TRAP_RESTORED;
          continue;
        }

        auto& wslot = SIMD[token.simd][token.wave];
        if (!wslot.size() || wslot.back().end_time != 0)
          wslot.push_back(wave_t(token));

        Instruction inst{wslot.back().begin_time, WaveInstCategory::PCINFO, wave_addr, 0};
        wslot.back().instructions.insert(wslot.back().instructions.begin(), inst);
      }

      size_t kid = get_addr_unique_id(wave_addr);
      running_waves[getGPULocation(token)] = kid;

      occupancy.push_back({kid, token.simd, token.wave, 1, token.cu, token.time});

      num_waves_started += 1;
    }
    else if (token.type == SQTT_TOKEN_WAVE_END)
    {  // Wave stop
      if ((int)token.cu == target_cu && token.sh == 0) {
        auto& wslot = SIMD[token.simd][token.wave];
        empty_wave_check(wslot.size());
        wslot.back().complete_wave(token);
      }

      size_t kid = 0;
      if (running_waves.find(getGPULocation(token)) != running_waves.end())
      {
        num_waves_completed += 1;
        kid = running_waves[getGPULocation(token)];
      }
      else
        occupancy.insert(occupancy.begin(), {kid, token.simd, token.wave, 1, token.cu, tokens[0].time});

      occupancy.push_back({kid, token.simd, token.wave, 0, token.cu, token.time});
      num_waves_completed += 1;
    }
    else if (token.type == SQTT_TOKEN_INST)
    {  // Update timestamp for executed inst
      auto& wslot = SIMD[token.simd][token.wave];
      if (!wslot.size() || wslot.back().end_time != 0)
        wslot.push_back(wave_t(token));
      wslot.back().apply_inst(token);
    }
    else if (token.type == SQTT_TOKEN_ISSUE)
    {
      int64_t active_cycles = array_apply_issue(token, SIMD);
      total_num_issue_cycles += active_cycles;
    }
#ifdef AMD_AQLPROFILE_SQTT_NPI
    else if (token.type == SQTT_PERFCOUNTER_TOKEN && token.sh == 0)
    {
      perfEvents.push_back(att_perfevent_t{
        token.time - 4*token.cu,
        (uint16_t)token.cntr[0],
        (uint16_t)token.cntr[1],
        (uint16_t)token.cntr[2],
        (uint16_t)token.cntr[3],
        (uint8_t)token.cu,
        (uint8_t)token.cntr_bank
      });
    }
#endif
    else if (token.type == SQTT_INST_PC)
    {
      empty_wave_check(SIMD[token.simd][token.wave].size());
      SIMD[token.simd][token.wave].back().apply_pc(token, csregister.table);
    }
    else if (csregister.IsRegCS(token.type))
    {
      csregister.UpdateRegCS(token);
    }
    else if (csregister.IsRegNoCS(token.type))
    {
      csregister.UpdateRegNoCS(token);
    }
  }

  for (auto& waveslot : SIMD) for (auto& slot : waveslot) for (auto& wave : slot)
  {
    if (!wave.instructions.size()) continue;
    auto& inst = wave.instructions.at(0);
    // If the wave has a invalid PC value, check if the codeobj information was not delayed relative to TTrace
    if (inst.value != WaveInstCategory::PCINFO) continue;
    if (inst.issue2inst >> 62) continue;

    inst.issue2inst = csregister.get_wave_start_delayed(inst.issue2inst);
  }

  std::unordered_map<uint64_t, uint64_t> retroactive_addr_map{};
  for (auto& [addr, id] : kernelID)
  {
    uint64_t v2pc = csregister.get_wave_start_delayed(addr);
    if (v2pc != addr && kernelID.find(v2pc) != kernelID.end())
      retroactive_addr_map[id] = kernelID.at(v2pc);
  }

  for (auto& occ : occupancy)
    if (retroactive_addr_map.find(occ.kernel_id) != retroactive_addr_map.end())
      occ.kernel_id = retroactive_addr_map.at(occ.kernel_id);

  if (bHasLostPackets)
    std::cout << "Warning: Packet lost!" << std::endl;

  std::map<uint64_t, uint64_t> rev_map;
  for (auto& kv : kernelID) rev_map.insert({kv.second, kv.first});

  std::vector<uint64_t> kid_map;
  for (int key = 0; key < rev_map.size(); key++) kid_map.push_back(rev_map[key]);

  return std::make_tuple(SIMD, perfEvents, occupancy, kid_map);
}

void wave_t::apply_pc(Token& token, CodeobjTableTranslator& table)
{
  if (trap_status != WaveTrapStatus::TRAP_RESTORED)
  {
    this->trap_status = WaveTrapStatus::TRAP_SAVED;
    return;
  }

  if (last_jump_inst >= 0 && last_jump_inst < instructions.size())
    instructions[last_jump_inst].issue2inst = table.ToPcV2(token.pc<<2);
  this->last_jump_inst = -1;
}

int64_t wave_t::apply_issue(uint64_t wave_status, int64_t token_time)
{
  if (this->trap_status != WaveTrapStatus::TRAP_RESTORED) return 0;

  auto previous_state = this->cur_state;
  int64_t active_issue_cycle = 0;

  if (wave_status == SQTT_ISSUE_IMMED)
  {
    int64_t immed_time = token_time;
    int64_t cycles_time = 4;

    if (instructions.back().value != WaveInstCategory::PCINFO &&
        instructions.back().value != WaveInstCategory::WAVE_NOT_FINISHED)
    {
      int64_t last_cycles = std::max(instructions.back().issue2inst, instructions.back().last);
      immed_time = std::max(last_message_time, instructions.back().time + last_cycles);
    }

    cycles_time = token_time - immed_time;
    instructions.push_back({immed_time, WaveInstCategory::IMMED, 0, std::max(cycles_time, 4l)});

    this->last_message_time = 0;
    this->inst_time = token_time;
    this->cur_state = WAVESLOT_STATE::WS_EXEC;

    if (cycles_time > 0)
    {
      if (state_start_cycle < immed_time)
        timeline.back().second += immed_time - state_start_cycle;

      timeline.push_back({WAVESLOT_STATE::WS_WAIT, cycles_time});
      state_start_cycle = immed_time + cycles_time;
    }
  }
  else
  {
    if (wave_status == SQTT_ISSUE_STALL)
    {
      this->stall_started = true;
      this->cur_state = WAVESLOT_STATE::WS_STALL;
      this->stall_start_time = token_time;
    }
    else if (wave_status == SQTT_ISSUE_INST)
    {
      active_issue_cycle = 1;
      this->issue_time = token_time;
      this->num_issued_instrs += 1;
      this->cur_state = WAVESLOT_STATE::WS_EXEC;
      issued_instructions.insert(instructions.size());
      instructions.push_back({token_time, WaveInstCategory::WAVE_NOT_FINISHED, 0, 4});
    }
  }

  int64_t state_duration = token_time - state_start_cycle;
  if (state_duration > 0)
  {
    if (timeline.size() && timeline.back().first == previous_state)
      timeline.back().second += state_duration;
    else
      this->timeline.push_back({previous_state, state_duration});
  }

  this->state_start_cycle = std::max(token_time, state_start_cycle);
  return active_issue_cycle;
}
