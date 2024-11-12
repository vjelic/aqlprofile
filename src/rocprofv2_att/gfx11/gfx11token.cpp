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

#include <string>
#include <array>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <chrono>

#include "gfx11token.h"
#include "gfx11parser.h"
#include "../trace_parser.hpp"

typedef gfx11Token Token;

std::unordered_map<int, std::pair<int,int>> gfx11TokenLookupTable::time_bits = {
    {gfx10type::INST, {4,7}},
    {gfx10type::VALU_INST, {3,6}},
    {gfx10type::VMEM_EXEC, {4,6}},
    {gfx10type::ALU_EXEC, {4,6}},
    {gfx10type::IMM_ONE, {4,7}},
    {gfx10type::IMMEDIATE, {5,8}},
    {gfx10type::WAVE_READY, {5,8}},
    {gfx10type::NEW_PC_GFX10, {8,11}},
    {gfx10type::WAVE_START, {5,7}},
    {gfx10type::WAVE_START_EXT, {5,7}},
    {gfx10type::WAVE_ALLOC, {5,8}},
    {gfx10type::WAVE_END, {5,8}},
    {gfx10type::SHADER_DATA, {5,8}},
    {gfx10type::SHADER_DATA_SHORT, {5,8}},
    {gfx10type::UTIL_COUNTER, {9,11}},
    {gfx10type::TIME, {4,8}},
    {gfx10type::NOP, {0,0}},
    {gfx10type::MISC_GFX10, {7,16}},
    {gfx10type::MISC_GFX11, {7,16}},
    {gfx10type::EVENT, {8,11}},
    {gfx10type::EVENT_SYNC, {8,11}},
    {gfx10type::REG, {4,7}},
    {gfx10type::REG_INIT, {7,10}},
    {gfx10type::TIMESTAMP, {12,48}},
    {gfx10type::HEADER, {0,0}},
    {gfx10type::PERFCTR, {7,10}}
};

std::array<uint8_t, 64> gfx11Token::TOKEN_LEN = {
    /*UNKNOWN*/ 8,
    /*VALU_INST*/ 12,
    /*VMEM_EXEC*/ 8,
    /*ALU_EXEC*/ 8,
    /*IMM_ONE*/ 12,
    /*IMMEDIATE*/ 24,
    /*WAVE_READY*/ 24,
    /*NEW_PC*/ 64,
    /*WAVE_END*/ 20,
    /*WAVE_START*/ 32,
    /*WAVE_START_EXT*/ 48,
    /*WAVE_ALLOC*/ 20,
    /*SHADER_DATA*/ 52,
    /*SHADER_DATA_SHORT*/ 28,
    /*UTIL_COUNTER*/ 48,
    /*TIME*/ 8,
    /*NOP*/ 4,
    /*MISC_GFX10*/ 24,
    /*EVENT*/ 24,
    /*EVENT_SYNC*/ 32,
    /*REG*/ 64,
    /*REG_INIT*/ 64,
    /*TIMESTAMP*/ 48,
    /*HEADER*/ 64,
    /*INST*/ 20,
    /*PERF*/ 4,
    /*MISC_GFX11*/ 24,
    /*UTIL_COUNTER*/ 48,
};

std::vector<gfx10Token> Token::parse(const uint8_t* buffer, const int BUFFER_SIZE) {
    gfx11TokenLookupTable lookupbits;

    for (size_t i=GFX10_TYPE_LAST; i<TOKEN_LEN.size(); i++)
        TOKEN_LEN[i] = 4;

    uint64_t current = 0;
    int bits_toread = 64;
    size_t bit_ptr = 0;

    std::vector<gfx10Token> tokens;
    tokens.reserve(BUFFER_SIZE);

    int num_waves = 0;
    int64_t globaltime = 0;
    while ((bit_ptr/8) < BUFFER_SIZE) {
        while (bits_toread>0) {
            uint64_t bmask = buffer[(bit_ptr/8)] >> (bit_ptr&0x4);
            current = (current>>4) | ((bmask<<60) & ~0xFull);
            bit_ptr += 4;
            bits_toread -= 4;
        }
        gfx10type type = (gfx10type)lookupbits.lookup(current);
        int token_len = TOKEN_LEN[type & 0x1F];
        bits_toread = token_len;

        globaltime = lookupbits.getTime(type, current, globaltime);
        tokens.emplace_back( Token{globaltime, current, type} );
    }

    return tokens;
}
