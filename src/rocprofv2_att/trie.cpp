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

#include "trie.h"

std::unordered_map<std::string, InstCategory> Trie::type_dict = {
    {"s_waitcnt", InstCategory::IMMED},
    {"s_nop", InstCategory::IMMED},
    {"s_sleep", InstCategory::IMMED},
    {"s_wakeup", InstCategory::IMMED},
    {"s_sendmsg", InstCategory::IMMED},
    {"s_setprio", InstCategory::IMMED},
    {"s_trap", InstCategory::IMMED},
    {"s_barrier", InstCategory::IMMED},
    {"s_endpgm", InstCategory::IMMED},
    {"s_icache_inv", InstCategory::IMMED},
    {"s_dcache_inv", InstCategory::IMMED},
    {"s_incperflvl", InstCategory::IMMED},
    {"s_sethalt", InstCategory::IMMED},
    {"s_decperflvl", InstCategory::IMMED},
    {"s_setvskip", InstCategory::IMMED},
    {"s_ttracedata", InstCategory::IMMED},

    {"s_load", InstCategory::SMEM},
    {"s_buffer", InstCategory::SMEM},
    {"s_atomic", InstCategory::SMEM},
    {"s_scratch", InstCategory::SMEM},
    {"s_store", InstCategory::SMEM},
    {"s_dcache", InstCategory::SMEM},
    // {"s_getpc", InstCategory::SMEM},
    // {"s_getreg", InstCategory::SMEM},
    {"s_getreg", InstCategory::SALU}, // Check!
    {"s_setreg", InstCategory::SMEM},
    {"s_memrealtime", InstCategory::SMEM},

    {"v_load", InstCategory::VMEM},
    {"v_store", InstCategory::VMEM},
    {"buffer_load", InstCategory::VMEM},
    {"buffer_store", InstCategory::VMEM},
    {"buffer_wbin", InstCategory::VMEM},

    {"flat_load", InstCategory::FLAT},
    {"global_load", InstCategory::FLAT},
    {"flat_store", InstCategory::FLAT},
    {"global_store", InstCategory::FLAT},

    {"ds_", InstCategory::LDS},
    {"s_add", InstCategory::SALU},
    {"s_sub", InstCategory::SALU},
    {"s_and", InstCategory::SALU},
    {"s_or", InstCategory::SALU},
    {"s_pack", InstCategory::SALU},
    {"s_bitreplicate", InstCategory::SALU},

    {"s_cmp", InstCategory::SALU},
    {"s_bitcmp", InstCategory::SALU},
    {"s_set_gpr", InstCategory::SALU},
    {"s_mov", InstCategory::SALU},
    {"s_mul", InstCategory::SALU},
    {"s_ash", InstCategory::SALU},
    {"s_bf", InstCategory::SALU},
    {"s_lsh", InstCategory::SALU},
    {"s_min", InstCategory::SALU},
    {"s_max", InstCategory::SALU},
    {"s_abs", InstCategory::SALU},
    {"s_cmov", InstCategory::SALU},
    {"s_not", InstCategory::SALU},
    {"s_wqm", InstCategory::SALU},
    {"s_quadmask", InstCategory::SALU},
    {"s_brev", InstCategory::SALU},
    {"s_bcnt", InstCategory::SALU},
    {"s_ff", InstCategory::SALU},
    {"s_flbit", InstCategory::SALU},
    {"s_sext", InstCategory::SALU},
    {"s_bitset", InstCategory::SALU},
    {"s_cselect", InstCategory::SALU},

    {"v_add", InstCategory::VALU},
    {"v_sub", InstCategory::VALU},
    {"v_mul", InstCategory::VALU},
    {"v_div", InstCategory::VALU},
    {"v_sat", InstCategory::VALU},
    {"v_xad", InstCategory::VALU},
    {"v_pack", InstCategory::VALU},
    {"v_swap", InstCategory::VALU},
    {"v_cvt", InstCategory::VALU},
    {"v_and", InstCategory::VALU},
    {"v_or", InstCategory::VALU},
    {"s_xor", InstCategory::SALU},
    {"s_nand", InstCategory::SALU},
    {"v_cmp", InstCategory::VALU},
    {"v_mov", InstCategory::VALU},
    {"v_lsh", InstCategory::VALU},
    {"v_ash", InstCategory::VALU},
    {"v_ceil", InstCategory::VALU},
    {"v_floor", InstCategory::VALU},
    {"v_fract", InstCategory::VALU},
    {"v_frexp", InstCategory::VALU},
    {"v_rnd", InstCategory::VALU},
    {"v_trunc", InstCategory::VALU},
    {"v_ldexp", InstCategory::VALU},
    {"v_cos", InstCategory::VALU},
    {"v_exp", InstCategory::VALU},
    {"v_log", InstCategory::VALU},
    {"v_mqsad", InstCategory::VALU},
    {"v_qsad", InstCategory::VALU},
    {"v_rcp", InstCategory::VALU},
    {"v_rsq", InstCategory::VALU},
    {"v_sin", InstCategory::VALU},
    {"v_sqrt", InstCategory::VALU},
    {"v_trig", InstCategory::VALU},
    {"v_min", InstCategory::VALU},
    {"v_max", InstCategory::VALU},
    {"v_fma", InstCategory::VALU},
    {"v_bfe", InstCategory::VALU},
    {"v_mad", InstCategory::VALU},
    {"v_pk", InstCategory::VALU},
    {"v_dot", InstCategory::VALU},
    {"v_mfma", InstCategory::VALU},
    {"v_align", InstCategory::VALU},
    {"v_cndmask", InstCategory::VALU},
    {"v_readfirstlane", InstCategory::VALU},
    {"v_xor", InstCategory::VALU},
    {"v_not", InstCategory::VALU},
    // {"s_swappc", InstCategory::SMEM},
    {"v_readlane", InstCategory::LANE},
    {"v_writelane", InstCategory::LANE},
    {"s_getpc", InstCategory::GETPC},
    {"s_setpc", InstCategory::SETPC},
    {"s_swappc", InstCategory::SWAPPC},
    {"v_mac_f32", InstCategory::VALU},
    {"v_accvgpr", InstCategory::VALU},
};

InstCategory Trie::type_from_trie(const std::string& inst) {
  assert(this == &root_trie);
  if (!bInit) {
    bInit = true;
    for (auto& p : type_dict) add_type(p.first, p.second);
  }

  Trie* trie = this;
  for (char c : inst) {
    if (trie->paths.find(c) != trie->paths.end()) {
      trie = trie->paths[c];
      assert(trie != nullptr);
    }
    if (trie->type != InstCategory::NEGATIVE) return trie->type;
  }

  // if (inst.size() > 0 && inst[0] != '_')
  //  std::cout << ">>> Type not found for " << inst << std::endl;

  return InstCategory::DONT_KNOW;
}

void Trie::add_type(const std::string& inst_header, InstCategory type) {
  Trie* trie = this;
  for (char c : inst_header) {
    if (trie->paths.find(c) == trie->paths.end()) {
      Trie* new_trie = new Trie();
      trie->paths[c] = new_trie;
      trie = new_trie;
    } else {
      trie = trie->paths[c];
    }
    assert(trie != nullptr);
  }
  trie->type = type;
}

Trie::~Trie() {
  for (auto& p : paths) {
    if (p.second != nullptr) delete p.second;
    p.second = nullptr;
  }
}
