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

enum WAVESLOT_STATE {
  WS_EMPTY = 0,
  WS_IDLE = 1,
  WS_EXEC = 2,
  WS_WAIT = 3,
  WS_STALL = 4,
  WS_UNKNOWN = 5,
};

enum class WaveInstCategory {
  NONE = 0,
  SMEM = 1,
  SALU = 2,
  VMEM = 3,
  FLAT = 4,
  LDS = 5,
  VALU = 6,
  JUMP = 7,
  NEXT = 8,
  IMMED = 9,
  TRAP = 10,
  WAVE_END,
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
  instruction_t() = default;
  instruction_t(uint64_t time, WaveInstCategory value, uint64_t issue2inst, uint64_t last)
      : time(time), issue2inst(issue2inst), last(last), value((uint64_t)value) {}

  uint64_t time;
  uint64_t value;
  uint64_t issue2inst;
  uint64_t last;
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

  std::pair<int64_t, int64_t>* timeline_alloc = nullptr;  // wave state in each cycle
  instruction_t* instructions_alloc = nullptr;              // (time, instruction_category)*
  size_t timeline_size = 0;
  size_t instructions_size = 0;
} wavedata_t;

typedef struct {
  uint64_t cu : 8;
  uint64_t value : 8;
  uint64_t time : 48;
} occupancy_info_t;

typedef union {
  uint64_t flags;
  struct {
    uint64_t isNavi : 1;
  };
} _output_flags_t;

typedef struct {
  uint64_t num_waves;
  void* wavedata;
  uint64_t num_events;
  perfevent_t* perfevents;
  void* occupancy;
  uint64_t num_occupancy;
  _output_flags_t flags;
} return_info_t;
