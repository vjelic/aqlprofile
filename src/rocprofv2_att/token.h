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
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

class Token {
 public:
  Token(uint64_t type, uint64_t val) : val(val), type(type) { build(); }
  uint64_t val, type;

  inline uint64_t get_bits(uint64_t low, uint64_t high) const {
    return (val >> low) & ((uint64_t(1) << (high - low + uint64_t(1))) - uint64_t(1));
  }

  void build() {
    if (type == 0) misc();
    else if (type == 1) timestamp();
    else if (type == 2) msg_reg();
    else if (type == 3) wave_start();
    else if (type == 4 || type == 6) get_wave();
    else if (type == 5 || type == 15) msg_reg_cs();
    else if (type == 7 || type == 8 || type == 9) event();
    else if (type == 10) msg_inst();
    else if (type == 11) msg_inst_pc();
    else if (type == 12) user_data();
    else if (type == 13) issue();
    else if (type == 14) msg_perf();
  }

  void timestamp() { time = get_bits(16, 63); }  // std::cout << time << std::endl; exit(0); }
  uint64_t time;

  void misc() {
    delta = get_bits(4, 11);
    sh = get_bits(12, 12);
    misc_type = get_bits(13, 15);
  }
  uint64_t delta, sh, misc_type;

  void _group_id() {
    cu = get_bits(6, 9);
    sh = get_bits(5, 5);
    wave = get_bits(10, 13);
    simd = get_bits(14, 15);
  }
  uint64_t cu, wave, simd;

  void get_wave() {
    delta = get_bits(4, 4);
    _group_id();
  }

  void event() {
    delta = get_bits(4, 4);
    sh = get_bits(5, 5);
    stage = get_bits(6, 8);
    eventype = get_bits(10, 15);
  }
  uint64_t stage, eventype;

  void wave_start() {
    delta = get_bits(4, 4);
    _group_id();
    dispatcher = get_bits(16, 20);
    na = get_bits(21, 21);
    count = get_bits(22, 28);
    tg = get_bits(29, 31);
  }
  uint64_t dispatcher, na, count, tg;

  void msg_reg() {
    delta = get_bits(4, 4);
    pip = get_bits(5, 6);
    me = get_bits(7, 8);
    reg_dropped_prev = get_bits(9, 9);
    reg_type = get_bits(10, 12);
    reg_priv = get_bits(14, 14);
    reg_op = get_bits(15, 15);
    regaddr = get_bits(16, 31);
    regdata = get_bits(32, 63);
  }
  uint64_t pip, me, reg_dropped_prev, reg_type, reg_priv, reg_op, regaddr, regdata;

  void msg_reg_cs() {
    delta = get_bits(4, 4);
    pip = get_bits(5, 6);
    me = get_bits(7, 8);
    regaddr = get_bits(9, 15);
    regdata = get_bits(16, 47);
  }

  void msg_inst() {
    delta = get_bits(4, 4);
    wave = get_bits(5, 8);
    simd = get_bits(9, 10);
    inst_type = get_bits(11, 15);
  }
  uint64_t inst_type;

  void msg_inst_pc() {
    delta = get_bits(4, 4);
    wave = get_bits(5, 8);
    simd = get_bits(9, 10);
    err = get_bits(15, 15);
    pc = get_bits(16, 63);
  }
  uint64_t err, pc;

  void user_data() {
    delta = get_bits(4, 4);
    _group_id();
    data = get_bits(16, 47);
  }
  uint64_t data;

  void issue() {
    delta = get_bits(4, 4);
    simd = get_bits(5, 6);
    inst = std::vector<uint64_t>(10);
    for (int i = 0; i <= 9; i ++)
      inst[i] = get_bits(2*i+8, 2*i+9);
  }
  std::vector<uint64_t> inst;

  void msg_perf() {
    delta = get_bits(4, 4);
    sh = get_bits(5, 5);
    cu = get_bits(6, 9);
    cntr_bank = (uint8_t)get_bits(10, 11);
    cntr[0] = (uint16_t)get_bits(12, 24);
    cntr[1] = (uint16_t)get_bits(25, 37);
    cntr[2] = (uint16_t)get_bits(38, 50);
    cntr[3] = (uint16_t)get_bits(51, 63);
  }
  uint8_t cntr_bank;
  uint16_t cntr[4];

  static std::vector<Token> parse(const std::string& filename);
  static void patch_time(std::vector<Token>& tokens);
};
