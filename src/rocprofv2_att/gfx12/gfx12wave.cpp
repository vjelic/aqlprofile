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

/// TODO(gbaraldi): num_insts statistics
/// TODO(gbaraldi): skipped insts spam IMMED tokens

#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include "gfx12wave.h"

/*
std::unordered_map<int, const char*> gfx12wave_t::INST_NAMES = {
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
    {28, "flat_rd_2"},
    {29, "flat_wr_2"},
    {30, "flat_wr_3"},
    {31, "flat_wr_4"},
    {32, "flat_wr_5"},
    {33, "sgmem_rd_1"},
    {34, "sgmem_rd_2"},
    {35, "sgmem_wr_1"},
    {36, "sgmem_wr_2"},
    {37, "sgmem_wr_3"},
    {38, "sgmem_wr_4"},
    {39, "sgmem_wr_5"},
    {40, "sgmem_wr_6"},
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
}; */

using WaveArray = gfx12wave_t::WaveArray;
typedef gfx12wave_t wave_t;
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
    vinterp=18,
    barrier,
    expreq_gds,
    expreq_gfx,
    flat_rd_2=28,
    flat_wr_2,
    flat_wr_3,
    flat_wr_4,
    flat_wr_5,
    sgmem_rd_1,
    sgmem_rd_2,
    sgmem_wr_1,
    sgmem_wr_2,
    sgmem_wr_3,
    sgmem_wr_4,
    sgmem_wr_5,
    sgmem_wr_6,
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

    other_simd_start = 79,
    other_simd_end = 102,
    raytrace8,
    raytrace9,
    raytrace11,
    raytrace12,
    lds_dir_load=110,
    lds_param_load,
    salu_wr_exec=114,
    valu1_wr_exec,
    valu_b2_wr_exec,
    rfe,
    lds_bvh_6,
    lds_bvh_10=121,
    barrier_signal,
    dyn_vgpr=135,
    try_lock,
    unlock,
    barrier_join,
    wmma8=140,
    wmma16,
    wmma32,
    wmma64,
    valu_dfdp=146,
    valu_derate,
    icpref=150,
    kcpref,
    salu_float3,
    valu_scl_trans,
    salu2=155,
    salu5,
    vmem_other_simd_start=188,  
    block_store=222,
    einst_final
};

static std::unordered_map<EINST, std::pair<WaveInstCategory, uint16_t>> table_inst_map_to_gfx9 {
    {EINST::salu, {WaveInstCategory::SALU, 1}},
    {EINST::smem_rd, {WaveInstCategory::SMEM, 1}},
    {EINST::smem_wr, {WaveInstCategory::SMEM, 1}},
    {EINST::branch_taken, {WaveInstCategory::JUMP, 1}},
    {EINST::branch_not_taken, {WaveInstCategory::NEXT, 1}},
    {EINST::jump, {WaveInstCategory::SALU, 1}},
    {EINST::trap, {WaveInstCategory::TRAP, 1}},
    {EINST::salu_no_exec, {WaveInstCategory::SALU, 1}},
    {EINST::fatal_halt, {WaveInstCategory::TRAP, 1}},
    {EINST::message, {WaveInstCategory::IMMED, 1}},
    {EINST::valu_1, {WaveInstCategory::VALU, 1}},
    {EINST::valut_4, {WaveInstCategory::VALU, 4}},
    {EINST::valub_1, {WaveInstCategory::VALU, 1}},
    {EINST::valub_2, {WaveInstCategory::VALU, 2}},
    {EINST::valub_4, {WaveInstCategory::VALU, 4}},
    {EINST::valub_16, {WaveInstCategory::VALU, 16}},
    {EINST::vinterp, {WaveInstCategory::VALU, 1}},
    {EINST::barrier, {WaveInstCategory::IMMED, 1}},
    {EINST::flat_rd_2, {WaveInstCategory::FLAT, 2}},
    {EINST::flat_wr_2, {WaveInstCategory::FLAT, 2}},
    {EINST::flat_wr_3, {WaveInstCategory::FLAT, 3}},
    {EINST::flat_wr_4, {WaveInstCategory::FLAT, 4}},
    {EINST::flat_wr_5, {WaveInstCategory::FLAT, 5}},
    {EINST::sgmem_rd_1, {WaveInstCategory::FLAT, 1}},
    {EINST::sgmem_rd_2, {WaveInstCategory::FLAT, 2}},
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

    // TODO: Add raytrace category
    {EINST::raytrace8, {WaveInstCategory::VMEM, 8}},
    {EINST::raytrace9, {WaveInstCategory::VMEM, 9}},
    {EINST::raytrace11, {WaveInstCategory::VMEM, 11}},
    {EINST::raytrace12, {WaveInstCategory::VMEM, 12}},

    {EINST::lds_dir_load, {WaveInstCategory::LDS, 1}},
    {EINST::lds_param_load, {WaveInstCategory::LDS, 1}},
    {EINST::salu_wr_exec, {WaveInstCategory::SALU, 1}},
    {EINST::valu1_wr_exec, {WaveInstCategory::VALU, 1}},
    {EINST::valu_b2_wr_exec, {WaveInstCategory::VALU, 2}},

    {EINST::rfe, {WaveInstCategory::SALU, 1}},
    {EINST::lds_bvh_6, {WaveInstCategory::LDS, 6}},
    {EINST::lds_bvh_10, {WaveInstCategory::LDS, 10}},
    {EINST::barrier_signal, {WaveInstCategory::IMMED, 1}},
    {EINST::dyn_vgpr, {WaveInstCategory::SALU, 1}},
    {EINST::try_lock, {WaveInstCategory::SALU, 1}},
    {EINST::unlock, {WaveInstCategory::SALU, 1}},
    {EINST::barrier_join, {WaveInstCategory::IMMED, 1}},

    {EINST::wmma8, {WaveInstCategory::VALU, 8}},
    {EINST::wmma16, {WaveInstCategory::VALU, 16}},
    {EINST::wmma32, {WaveInstCategory::VALU, 32}},
    {EINST::wmma64, {WaveInstCategory::VALU, 64}},
    {EINST::valu_dfdp, {WaveInstCategory::VALU, 1}},
    {EINST::valu_derate, {WaveInstCategory::VALU, 1}},

    {EINST::icpref, {WaveInstCategory::SALU, 1}},
    {EINST::kcpref, {WaveInstCategory::SALU, 1}},
    {EINST::salu_float3, {WaveInstCategory::SALU, 3}},

    // TODO: Get cycles
    {EINST::valu_scl_trans, {WaveInstCategory::VALU, 1}},
    {EINST::salu2, {WaveInstCategory::SALU, 2}},
    {EINST::salu5, {WaveInstCategory::SALU, 5}},
    {EINST::valu_scl_trans, {WaveInstCategory::VALU, 1}},
};

void gfx12wave_t::set_double_rate(size_t contents)
{
  header_type header { .raw = contents };
  int dprate = 1<<(header.DPRate-1);
  table_inst_map_to_gfx9.at(EINST::valu_dfdp).second = dprate;
  table_inst_map_to_gfx9.at(EINST::valu_derate).second = dprate*(1<<(header.dp_derate));
}

std::pair<WaveInstCategory, uint16_t> gfx12wave_t::inst_map_to_gfx9(int einst)
{
  static thread_local auto empty = std::pair<WaveInstCategory, uint16_t>{WaveInstCategory::NONE, 0};

  if (einst >= EINST::other_simd_start && einst <= EINST::other_simd_end)
  {
    return empty;
  }
  else if (einst >= (int)EINST::vmem_other_simd_start)
  {
    if (einst < (int)EINST::block_store) return empty;
    return {WaveInstCategory::VMEM, einst + 1 - (int)EINST::block_store};
  }

  try {
    return table_inst_map_to_gfx9.at((EINST)einst);
  } catch (...) {
    return empty;
  }
}

wave_t::gfx12wave_t(Token& token) {}
