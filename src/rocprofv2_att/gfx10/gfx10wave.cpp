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

/// TODO(gbaraldi): timing from branch == immediate
/// TODO(gbaraldi): waitcnt only waits for load, waitcnt_vscnt waits for stores

#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include "gfx10wave.h"
#include "../gfx11/gfx11wave.h"

int gfx10wave_t::dp_cycles = 1;
int gfx10wave_t::dp_derate = 1;

struct alu_user_inst_t {
  uint8_t bValid;
  uint16_t slot;
  uint16_t wid;
  uint64_t inst;
  uint64_t time;
};

/*
std::unordered_map<int, const char*> gfx10wave_t::INST_NAMES = {
    {0, "salu"},
    {1, "smem_rd"},
    {2, "smem_wr"},
    {3, "branch_taken"},
    {4, "branch_not_taken"},
    {5, "jump"},
    {6, "trap"},
    {7, "salu_no_exec"},
    {8, "fatal_halt"},
    {9, "message"},
    {10, "valu_1"},
    {11, "valut_4"},
    {12, "valub_1"},
    {13, "valub_2"},
    {14, "valub_4"},
    {15, "valub_16"},
    {18, "vinterp"},
    {19, "barrier"},
    {20, "expreq_gds"},
    {21, "expreq_gfx"},
    {30, "flat_rd"},
    {31, "flat_wr_2"},
    {32, "flat_wr_3"},
    {33, "flat_wr_4"},
    {34, "flat_wr_5"},
    {35, "sgmem_rd"},
    {36, "sgmem_wr_1"},
    {37, "sgmem_wr_2"},
    {38, "sgmem_wr_3"},
    {39, "sgmem_wr_4"},
    {40, "sgmem_wr_5"},
    {41, "lds_rd"},
    {42, "lds_wr_1"},
    {43, "lds_wr_2"},
    {44, "lds_wr_3"},
    {45, "lds_wr_4"},
    {46, "lds_wr_5"},
    {47, "buf_rd_1"},
    {48, "buf_rd_2"},
    {49, "buf_wr_1"},
    {50, "buf_wr_2"},
    {51, "buf_wr_3"},
    {52, "buf_wr_4"},
    {53, "buf_wr_5"},
    {54, "buf_wr_6"},
    {80, "lds_other_1"},
    {90, "vmem_other_1"},
    {91, "vmem_other_2"},
    {92, "vmem_other_3"},
    {93, "vmem_other_4"},
    {94, "vmem_other_5"},
    {95, "vmem_other_6"},
    {96, "vmem_other_7"},
    {97, "vmem_other_8"},
    {98, "vmem_other_9"},
    {99, "vmem_other_10"},
    {100, "vmem_other_11"},
    {101, "vmem_other_12"},
};
*/

using WaveArray = gfx10wave_t::WaveArray;
typedef gfx10wave_t wave_t;
typedef gfx10Token Token;

enum EINST {
    salu=0,
    smem_rd,
    smem_wr,
    branch_taken,
    branch_not_taken,
    jump,
    trap,
    salu_no_exec,
    fatal_halt,
    message,
    valu_1,
    valut_4,
    valub_1,
    valub_2,
    valub_4,
    valub_16,
    valub_dfdp,
    valub_dfdp_derate,
    vinterp=18,
    barrier,
    expreq_gds,
    expreq_gfx,
    flat_rd=30,
    flat_wr_2,
    flat_wr_3,
    flat_wr_4,
    flat_wr_5,
    sgmem_rd=35,
    sgmem_wr_1,
    sgmem_wr_2,
    sgmem_wr_3,
    sgmem_wr_4,
    sgmem_wr_5,
    lds_rd,
    lds_wr_1,
    lds_wr_2,
    lds_wr_3,
    lds_wr_4,
    lds_wr_5,
    buf_rd_1,
    buf_rd_2,
    buf_wr_1,
    buf_wr_2,
    buf_wr_3,
    buf_wr_4,
    buf_wr_5,
    buf_wr_6,
    img_sample_1,
    img_sample_2,
    img_sample_3,
    img_sample_4,
    img_sample_5,
    img_sample_6,
    img_sample_7,
    img_sample_8,
    img_sample_9,
    img_sample_10,
    img_sample_11,
    img_sample_12,
    img_sample_reserved=67,
    img_rd_1,
    img_rd_2,
    img_rd_3,
    img_rd_4,
    img_wr_2,
    img_wr_3,
    img_wr_4,
    img_wr_5,
    img_wr_6,
    img_wr_7,
    img_wr_8,
    img_sample_end=78,
    einst_final
};

static std::unordered_map<EINST, std::pair<WaveInstCategory, uint16_t>> table_inst_map_to_gfx9 {
    {EINST::salu, {WaveInstCategory::SALU, 1}},
    {EINST::smem_rd, {WaveInstCategory::SMEM, 1}},
    {EINST::smem_wr, {WaveInstCategory::SMEM, 1}},
    {EINST::branch_taken, {WaveInstCategory::JUMP, 1}},
    {EINST::branch_not_taken, {WaveInstCategory::NEXT, 1}},
    {EINST::jump, {WaveInstCategory::JUMP, 1}},
    {EINST::trap, {WaveInstCategory::TRAP, 1}},
    {EINST::salu_no_exec, {WaveInstCategory::SALU, 1}},
    {EINST::fatal_halt, {WaveInstCategory::TRAP, 1}},
    {EINST::message, {WaveInstCategory::NONE, 1}},
    {EINST::valu_1, {WaveInstCategory::VALU, 1}},
    {EINST::valut_4, {WaveInstCategory::VALU, 4}},
    {EINST::valub_1, {WaveInstCategory::VALU, 1}},
    {EINST::valub_2, {WaveInstCategory::VALU, 2}},
    {EINST::valub_4, {WaveInstCategory::VALU, 4}},
    {EINST::valub_16, {WaveInstCategory::VALU, 16}},
    {EINST::valub_dfdp, {WaveInstCategory::VALU, 1}},
    {EINST::valub_dfdp_derate, {WaveInstCategory::VALU, 1}},
    {EINST::vinterp, {WaveInstCategory::VALU, 1}},
    {EINST::barrier, {WaveInstCategory::IMMED, 1}},
    {EINST::flat_rd, {WaveInstCategory::FLAT, 1}},
    {EINST::flat_wr_2, {WaveInstCategory::FLAT, 2}},
    {EINST::flat_wr_3, {WaveInstCategory::FLAT, 3}},
    {EINST::flat_wr_4, {WaveInstCategory::FLAT, 4}},
    {EINST::flat_wr_5, {WaveInstCategory::FLAT, 5}},
    {EINST::sgmem_rd, {WaveInstCategory::FLAT, 1}},
    {EINST::sgmem_wr_1, {WaveInstCategory::FLAT, 1}},
    {EINST::sgmem_wr_2, {WaveInstCategory::FLAT, 2}},
    {EINST::sgmem_wr_3, {WaveInstCategory::FLAT, 3}},
    {EINST::sgmem_wr_4, {WaveInstCategory::FLAT, 4}},
    {EINST::sgmem_wr_5, {WaveInstCategory::FLAT, 5}},
    {EINST::lds_rd, {WaveInstCategory::LDS, 1}},
    {EINST::lds_wr_1, {WaveInstCategory::LDS, 1}},
    {EINST::lds_wr_2, {WaveInstCategory::LDS, 2}},
    {EINST::lds_wr_3, {WaveInstCategory::LDS, 3}},
    {EINST::lds_wr_4, {WaveInstCategory::LDS, 4}},
    {EINST::lds_wr_5, {WaveInstCategory::LDS, 5}},
    {EINST::buf_rd_1, {WaveInstCategory::VMEM, 1}},
    {EINST::buf_rd_2, {WaveInstCategory::VMEM, 2}},
    {EINST::buf_wr_1, {WaveInstCategory::VMEM, 1}},
    {EINST::buf_wr_2, {WaveInstCategory::VMEM, 2}},
    {EINST::buf_wr_3, {WaveInstCategory::VMEM, 3}},
    {EINST::buf_wr_4, {WaveInstCategory::VMEM, 4}},
    {EINST::buf_wr_5, {WaveInstCategory::VMEM, 5}},
    {EINST::buf_wr_6, {WaveInstCategory::VMEM, 6}},
    {EINST::img_rd_1, {WaveInstCategory::VMEM, 1}},
    {EINST::img_rd_2, {WaveInstCategory::VMEM, 2}},
    {EINST::img_rd_3, {WaveInstCategory::VMEM, 3}},
    {EINST::img_rd_4, {WaveInstCategory::VMEM, 4}},
    {EINST::img_wr_2, {WaveInstCategory::VMEM, 2}},
    {EINST::img_wr_3, {WaveInstCategory::VMEM, 3}},
    {EINST::img_wr_4, {WaveInstCategory::VMEM, 4}},
    {EINST::img_wr_5, {WaveInstCategory::VMEM, 5}},
    {EINST::img_wr_6, {WaveInstCategory::VMEM, 6}},
    {EINST::img_wr_7, {WaveInstCategory::VMEM, 7}},
    {EINST::img_wr_8, {WaveInstCategory::VMEM, 8}},
    {EINST::img_sample_1, {WaveInstCategory::VMEM, 1}},
    {EINST::img_sample_2, {WaveInstCategory::VMEM, 2}},
    {EINST::img_sample_3, {WaveInstCategory::VMEM, 3}},
    {EINST::img_sample_4, {WaveInstCategory::VMEM, 4}},
    {EINST::img_sample_5, {WaveInstCategory::VMEM, 5}},
    {EINST::img_sample_6, {WaveInstCategory::VMEM, 6}},
    {EINST::img_sample_7, {WaveInstCategory::VMEM, 7}},
    {EINST::img_sample_8, {WaveInstCategory::VMEM, 8}},
    {EINST::img_sample_9, {WaveInstCategory::VMEM, 9}},
    {EINST::img_sample_10, {WaveInstCategory::VMEM, 10}},
    {EINST::img_sample_11, {WaveInstCategory::VMEM, 11}},
    {EINST::img_sample_12, {WaveInstCategory::VMEM, 12}},
};

std::pair<WaveInstCategory, uint16_t> gfx10wave_t::inst_map_to_gfx9(int einst) {
  try {
    return table_inst_map_to_gfx9.at((EINST)einst);
  } catch (...) {
    return {WaveInstCategory::NONE, 0};
  }
}

#define empty_wave_check(waveslot_size) if (waveslot_size == 0) { continue; }

wave_t::gfx10wave_t(Token& token, int64_t last_completed_wave_cycle, int tg_simd) {
  this->begin_time = token.time;
  this->last_state_cycle = token.time;
  this->target_simd = tg_simd;

  //timeline.push_back(std::make_pair(WAVESLOT_STATE::WS_EMPTY, token.time));
  //int64_t num_cycles = token.time - last_completed_wave_cycle;
  //if (num_cycles > 0)
  //  timeline.push_back(std::make_pair(WAVESLOT_STATE::WS_EMPTY, num_cycles));
}

void wave_t::complete_wave(Token& token) {
  int64_t num_cycles = std::max(token.time - last_state_cycle, last_state_duration);
  if (num_cycles > 0)
    timeline.push_back(std::make_pair(WAVESLOT_STATE::WS_EXEC, num_cycles));

  this->end_time = std::max(token.time, last_state_cycle+last_state_duration);
  num_mem_instrs = num_lds_instrs + num_smem_instrs + num_vmem_instrs + num_flat_instrs;
}

std::tuple<WaveArray, std::vector<perfevent_t>, std::vector<occupancy_info_t>>
wave_t::sqtt_simd_analysis(std::vector<Token>& tokens, int target_cu) {
  bool bHasLostPackets = false;
  WaveArray SIMD;
  int64_t total_num_issue_cycles = 0;
  int num_waves_started = 0;
  int num_waves_completed = 0;
  bool bInitBeginTime = false;
  std::array<int64_t, SQTT_CFG_WAVES> last_completed_wave_cycle{};
  std::vector<perfevent_t> perfEvents{};
  std::vector<occupancy_info_t> occupancy = {};
  std::array<int, 16> current_occupancy = {};
  std::vector<alu_user_inst_t> alu_stack = {};
  int alu_exec_count = 0;

  int target_wgp = 0;
  int target_simd = 0;
  int tt_version = 0;


  for (size_t t = 0; t<tokens.size(); t++) {
    Token& token = tokens[t];

    switch (token.type) {
      case gfx10type::MISC_GFX10: {
        if (miscgfx10_type{ .raw = token.contents }.packetlost)
          bHasLostPackets = true;
        break;
      }
      case gfx10type::HEADER: {
        header_type header { .raw = token.contents };
        target_wgp = header.DWGP;
        target_simd = header.DSIMD;
        dp_cycles = header.DPRate & ((tt_version == 3) ? 0x7 : 0xF);
        dp_cycles = (1<<dp_cycles)/2;
        dp_derate = (tt_version == 3) ? (1<<header.dp_derate)/2 : 1;
        tt_version = header.version;
        //header.print();
        break;
      }
      case gfx10type::WAVE_START: {
        if (!bInitBeginTime) {
          bInitBeginTime = true;
          for (int i=0; i<SQTT_CFG_WAVES; i++)
            last_completed_wave_cycle[i] = token.time;
        }
        wstart_type start { .raw = token.contents };
        if (start.wgp == target_wgp && start.simd == target_simd && start.sa == 0)
          SIMD[start.wid].push_back(wave_t(token, last_completed_wave_cycle[start.wid], start.simd));
        current_occupancy[(start.wgp & 0x7)*2 + start.sa] += 1;
        occupancy.push_back(occupancy_info_t{
          (uint64_t)start.wgp,
          (uint64_t)current_occupancy[(start.wgp & 0x7)*2 + start.sa],
          (uint64_t)token.time
        });
        num_waves_started += 1;
        break;
      }
      case gfx10type::WAVE_END: {
        wend_type end { .raw = token.contents };
        if (end.wgp == target_wgp && end.simd == target_simd && end.sa == 0) {
          empty_wave_check(SIMD[end.wid].size());
          SIMD[end.wid].back().complete_wave(token);
          last_completed_wave_cycle[end.wid] = token.time;
        }
        current_occupancy[(end.wgp & 0x7)*2 + end.sa] -= 1;
        occupancy.push_back(occupancy_info_t{
          (uint64_t)end.wgp,
          (uint64_t)current_occupancy[(end.wgp & 0x7)*2 + end.sa],
          (uint64_t)token.time
        });
        num_waves_completed += 1;
        break;
      }
      case gfx10type::INST: {
        inst_type inst { .raw = token.contents };
        auto& simd = SIMD[inst.wid];
        empty_wave_check(simd.size());
        simd.back().apply_inst(token, inst, tt_version);
        break;
      }
      case gfx10type::VALU_INST: {
        valu_inst_type vinst { .raw = token.contents };
        auto& simd = SIMD[vinst.wid];
        empty_wave_check(simd.size());
        alu_stack.push_back(alu_user_inst_t{
          true, (uint16_t)vinst.wid, uint16_t(simd.size()-1), simd.back().instructions.size()
        });
        simd.back().apply_valu_inst(token, vinst);
        break;
      }
      case gfx10type::IMM_ONE: {
        immed_one_type immed_one { .raw = token.contents };
        empty_wave_check(SIMD[immed_one.wid].size());
        SIMD[immed_one.wid].back().apply_immediate(token);
        break;
      }
      case gfx10type::IMMEDIATE: {
        immediate_type immed { .raw = token.contents };
        for (int i=0; i<16; i++)
          if (SIMD[i].size() && (immed.waves & (1<<i)))
            SIMD[i].back().apply_immediate(token);
        break;
      }
      case gfx10type::ALU_EXEC: {
        alu_exec_type alux;
        if (alu_exec_count >= alu_stack.size()) {
          alu_exec_count = alu_stack.size();
          alu_stack.push_back(alu_stack.size() ? alu_stack.back() : alu_user_inst_t{false});
        }
        alu_stack[alu_exec_count].time = token.time;
        alu_exec_count += 1;
        break;
      }
      /*
      case gfx10type::UTIL_COUNTER: {
        util_ctr_gfx10_type util { .raw = token.contents };
        if (util.cID == 0) {
          perfEvents.push_back( perfevent_t{
            uint64_t(token.time),
            uint16_t(util.spi_busy_or_lds1),
            uint16_t(util.vdata0+util.vdata1),
            uint16_t(util.sdata0+util.sdata1),
            uint16_t(2*util.lds0),
          } );
        }
        break;
      }
      case gfx10type::UTIL_COUNTER_GFX11: {
        util_ctr_gfx11_type util { .raw = token.contents };
        if (util.cID == 0) {
          perfEvents.push_back( perfevent_t{
            uint64_t(token.time),
            uint16_t(util.spi_busy),
            uint16_t(util.vdata0+util.vdata1),
            uint16_t(util.sdata0+util.sdata1),
            uint16_t(util.lds0+util.lds1),
          } );
        }
        break;
      } */
      /*
      case gfx10type::VMEM_EXEC: {
        break;
      }
      case gfx10type::WAVE_READY: {
        break;
      }
      case gfx10type::NEW_PC: {
        new_pc_type pc { .raw = token.contents };
        //pc.print();
        if (pc.wave >= SIMD.size() || !SIMD[pc.wave].size())
          std::cout << "Invalid wave: " << pc.wave << std::endl;
        else if(!SIMD[pc.wave].back().last_jump_inst)
          std::cout << "Wave not registered a jump: " << pc.wave << std::endl;
        break;
      }
      */
      default:
        break;
    }
  }

  if (alu_stack.size() == alu_exec_count)
  for (int a=0; a<alu_stack.size(); a++) {
    auto& alu = alu_stack[a];
    if (
      !alu.bValid ||
      alu.slot >= SIMD.size() ||
      alu.wid >= SIMD[alu.slot].size() ||
      alu.inst >= SIMD[alu.slot][alu.wid].instructions.size()
    ) continue;

    auto& inst_vector = SIMD[alu.slot][alu.wid].instructions;
    auto& inst = inst_vector[alu.inst];
    int64_t inst_time = inst.time;
    int64_t delay_time = inst.last + (int64_t)alu.time - inst_time;

    if (alu.inst < inst_vector.size()-1)
      delay_time = std::min(delay_time, (int64_t)inst_vector[alu.inst+1].time - inst_time);
    inst.last = delay_time;
  }

  if (bHasLostPackets)
    std::cout << "Warning: Packet lost!" << std::endl;

  return std::make_tuple(SIMD, perfEvents, occupancy);
}

void wave_t::set_state_exec(int64_t time, int64_t duration) {
  int64_t num_cycles = time - last_state_cycle;
  if (num_cycles <= 0) return;

  last_state_duration = std::max(duration, last_state_duration-num_cycles);
  last_state_cycle = time;
  if (timeline.size() && cur_state == WAVESLOT_STATE::WS_EXEC && cur_state == timeline.back().first) {
    timeline.back().second += num_cycles;
    return;
  }

  if (cur_state == WAVESLOT_STATE::WS_EMPTY)
    cur_state = WAVESLOT_STATE::WS_IDLE;
  timeline.push_back(std::make_pair(cur_state, num_cycles));
  cur_state = WAVESLOT_STATE::WS_EXEC;
}

void wave_t::apply_valu_inst(Token token, valu_inst_type inst) {
  update_immediate(token.time);
  set_state_exec(token.time, 1);

  this->instructions.push_back({(uint64_t)token.time, WaveInstCategory::VALU, 0, 1});
  num_issued_instrs += 1;
  num_valu_instrs += 1;
}

// Fix for Immediate token bug
void wave_t::update_immediate(int64_t token_time) {
  if (!this->instructions.size()) return;

  auto& inst = this->instructions.back();
  if (inst.value != (uint64_t)WaveInstCategory::IMMED) return;
  inst.last = std::max(inst.last, std::max(token_time-inst.time,1ul)-1);

  if (!this->timeline.size()) return;
  this->timeline.back().second += std::max(token_time-last_state_cycle,1l)-1;
  last_state_cycle = token_time - 1;
}

void wave_t::apply_immediate(Token token) {
  if (ImmFromBranch) {
    ImmFromBranch = false;
    return;
  }

  int64_t time = std::min(token.time, last_state_cycle+last_state_duration);
  uint64_t delta_time = std::max(1l, token.time-time);
  this->instructions.push_back({(uint64_t)time, WaveInstCategory::IMMED, 0, delta_time});

  set_state_exec(time, 0);
  cur_state = WAVESLOT_STATE::WS_WAIT;
  set_state_exec(token.time, 0);
}

void wave_t::apply_inst(Token token, inst_type inst, int tt_version) {
  bool bGFX11 = tt_version >= 3;
  /*auto& names = bGFX11 ? gfx11wave_t::INST_NAMES : gfx10wave_t::INST_NAMES;
  if (names.find(inst.inst) == names.end())
    std::cout << tt_version << ": Unknown inst: " << inst.inst << std::endl; */

  this->end_time = token.time;
  //if (inst.inst == EINST::branch_not_taken)
  //  ImmFromBranch = true;

  auto mapped = bGFX11 ? gfx11wave_t::inst_map_to_gfx9(inst.inst)
                       : gfx10wave_t::inst_map_to_gfx9(inst.inst);
  if (mapped.first == WaveInstCategory::NONE)
    return;

  if (inst.inst == EINST::valub_dfdp_derate)
    mapped.second = dp_cycles*dp_derate;
  else if (inst.inst == EINST::valub_dfdp)
    mapped.second = dp_cycles;
  else if (inst.inst == EINST::valub_16)
    mapped.second *= dp_cycles;
  else if (inst.inst == EINST::jump)
    last_jump_inst = this->instructions.size();

  update_immediate(token.time);
  this->instructions.push_back({(uint64_t)token.time, mapped.first, 0, mapped.second});
  set_state_exec(token.time, mapped.second);
  num_issued_instrs += 1;

  switch (mapped.first) {
    case WaveInstCategory::LDS:
      num_lds_instrs += 1;
      break;
    case WaveInstCategory::SMEM:
      num_smem_instrs += 1;
      break;
    case WaveInstCategory::VMEM:
      num_vmem_instrs += 1;
      break;
    case WaveInstCategory::FLAT:
      num_flat_instrs += 1;
      break;
    case WaveInstCategory::JUMP:
      num_branch_taken_instrs += 1;
    case WaveInstCategory::NEXT:
      num_branch_instrs += 1;
      break;
    case WaveInstCategory::SALU:
      num_salu_instrs += 1;
      break;
    case WaveInstCategory::VALU:
      num_valu_instrs += 1;
      break;
    default:
      break;
  }
}
