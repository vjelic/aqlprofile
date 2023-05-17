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
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>

#include "gfx10token.h"
#include "gfx10parser.h"
#include "../wave.h"

typedef gfx10Token Token;

std::unordered_map<int, std::pair<int16_t,int16_t>> gfx10TokenLookupTable::time_bits = {
    {gfx10type::INST, {4,7}},
    {gfx10type::VALU_INST, {3,6}},
    {gfx10type::VMEM_EXEC, {4,6}},
    {gfx10type::ALU_EXEC, {4,6}},
    {gfx10type::IMM_ONE, {4,7}},
    {gfx10type::IMMEDIATE, {5,8}},
    {gfx10type::WAVE_READY, {5,8}},
    {gfx10type::NEW_PC, {8,11}},
    {gfx10type::WAVE_START, {5,7}},
    {gfx10type::WAVE_START_EXT, {5,7}},
    {gfx10type::WAVE_ALLOC, {5,8}},
    {gfx10type::WAVE_END, {5,8}},
    {gfx10type::SHADER_DATA, {5,8}},
    {gfx10type::SHADER_DATA_SHORT, {5,8}},
    {gfx10type::UTIL_COUNTER, {7,9}},
    {gfx10type::TIME, {4,8}},
    {gfx10type::NOP, {0,0}},
    {gfx10type::MISC_GFX10, {7,16}},
    {gfx10type::MISC_GFX11, {7,16}},
    {gfx10type::EVENT, {8,11}},
    {gfx10type::EVENT_SYNC, {8,11}},
    {gfx10type::REG, {4,7}},
    {gfx10type::REG_INIT, {7,10}},
    {gfx10type::TIMESTAMP, {16,64}},
    {gfx10type::HEADER, {0,0}},
    {gfx10type::PERFCTR, {7,10}}
};

std::vector<encoding_t> gfx10TokenLookupTable::bit_encodings = {
    // Target
    {gfx10type::INST, {0,1,0}},
    {gfx10type::VALU_INST, {1,1,0}},
    {gfx10type::VMEM_EXEC, {1,1,1,1}},
    {gfx10type::ALU_EXEC, {0,1,1,1}},
    {gfx10type::IMM_ONE, {1,0,1,1}},
    {gfx10type::IMMEDIATE, {0,0,1,0,0}},
    {gfx10type::WAVE_READY, {0,0,1,0,1}},
    {gfx10type::NEW_PC, {1,0,0,0,0,1,0}},
    // global
    {gfx10type::WAVE_START, {0,0,1,1,0}},
    {gfx10type::WAVE_START_EXT, {0,0,1,1,1}},
    {gfx10type::WAVE_ALLOC, {1,0,1,0,0}},
    {gfx10type::WAVE_END, {1,0,1,0,1}},
    {gfx10type::SHADER_DATA, {0,1,1,0,0}},
    {gfx10type::SHADER_DATA_SHORT, {0,1,1,0,1}},
    {gfx10type::UTIL_COUNTER, {1,0,0,0,1,1,0}},
    // reference
    {gfx10type::TIME, {0,0,0,1}},
    {gfx10type::NOP, {0,0,0,0}},
    {gfx10type::MISC_GFX10, {1,0,0,0,1,0,1}},
    {gfx10type::EVENT, {1,0,0,0,0,1,1,0}},
    {gfx10type::EVENT_SYNC, {1,0,0,0,0,1,1,1}},
    //{gfx10type::EVENT, {1,0,0,0,0,1,1}},
    {gfx10type::REG, {1,0,0,1}},
    {gfx10type::REG_INIT, {1,0,0,0,1,1,1}},
    {gfx10type::TIMESTAMP, {1,0,0,0,0,0,0}},
    {gfx10type::HEADER, {1,0,0,0,1,0,0}}
};

/*
std::unordered_map<uint8_t, std::string> TOKEN_NAMES = {
    {gfx10type::UNKNOWN,"UNKNOWN"},
    // Target
    {gfx10type::INST,"inst"},
    {gfx10type::VALU_INST,"valu_inst"},
    {gfx10type::VMEM_EXEC,"vmem_exec"},
    {gfx10type::ALU_EXEC,"alu_exec"},
    {gfx10type::IMM_ONE,"imm_one"},
    {gfx10type::IMMEDIATE,"immediate"},
    {gfx10type::WAVE_READY,"wave_ready"},
    {gfx10type::NEW_PC,"new_pc"},
    // global
    {gfx10type::WAVE_START,"wave_start"},
    {gfx10type::WAVE_START_EXT,"wave_start_ext"},
    {gfx10type::WAVE_ALLOC,"wave_alloc"},
    {gfx10type::WAVE_END,"wave_end"},
    {gfx10type::SHADER_DATA,"shader_data"},
    {gfx10type::SHADER_DATA_SHORT,"shader_data_short"},
    {gfx10type::UTIL_COUNTER,"util_counter"},
    // reference
    {gfx10type::TIME,"time"},
    {gfx10type::NOP,"nop"},
    {gfx10type::MISC_GFX10,"misc_gfx10"},
    {gfx10type::MISC_GFX11,"misc_gfx11"},
    {gfx10type::EVENT,"event"},
    {gfx10type::EVENT_SYNC,"event_sync"},
    {gfx10type::REG,"reg"},
    {gfx10type::REG_INIT,"reg_init"},
    {gfx10type::TIMESTAMP,"timestamp"},
    {gfx10type::HEADER,"header"},
}; //*/

std::array<uint8_t, 32> gfx10Token::TOKEN_LEN = {
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
    /*UTIL_COUNTER*/ 64,
    /*TIME*/ 8,
    /*NOP*/ 4,
    /*MISC*/ 24,
    /*EVENT*/ 24,
    /*EVENT_SYNC*/ 32,
    /*REG*/ 64,
    /*REG_INIT*/ 64,
    /*TIMESTAMP*/ 64,
    /*HEADER*/ 64,
    /*INST*/ 20,
    /*PERF*/ 4,
    /*MISC_GFX11*/ 24,
    /*UTIL_COUNTER*/ 64,
    /*28*/ 4,
    /*29*/ 4,
    /*30*/ 4,
    /*31*/ 4,
};

gfx10TokenLookupTable::gfx10TokenLookupTable(): std::array<uint8_t, 256>({}) {
    for (const auto& encoding : bit_encodings)
        AddEncoding(encoding);
}

void gfx10TokenLookupTable::AddEncoding(const encoding_t& encoding) {
    int begin = frombits(encoding.bits);
    int stepsize = 1<<encoding.bits.size();
    //std::cout << TOKEN_NAMES[encoding.type] << " " << stepsize << " " << begin << std::endl;
    for (int i=begin; i<256; i += stepsize)
        data()[i] = encoding.type;
}

std::vector<Token> Token::parse(const uint8_t* buffer, const int BUFFER_SIZE) {
    gfx10TokenLookupTable lookupbits;

    auto t0 = std::chrono::system_clock::now();
    uint64_t current = 0;
    int bits_toread = 64;
    int bit_ptr = 0;

    auto t1 = std::chrono::system_clock::now();
    std::vector<Token> tokens;
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
        tokens.push_back( Token{globaltime, current, type} );
    }

    auto t2 = std::chrono::system_clock::now();

    /*std::cout << "Read: " << (t1-t0).count()/1000.0f << std::endl;
    std::cout << "Parsed: " << (t2-t1).count()/1000.0f << std::endl;
    std::cout << "Num waves: " << num_waves << std::endl; */
    delete[] buffer;
    return tokens;
}
