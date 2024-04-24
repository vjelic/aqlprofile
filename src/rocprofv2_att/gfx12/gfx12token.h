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
#include <vector>
#include <cstdint>
#include <iostream>
#include "../gfx11/gfx11token.h"
#include "../gfx11/gfx11parser.h"

union timestamp_gfx12_type {
    struct {
        uint64_t header : 7;
        uint64_t rt : 1;
        uint64_t pl : 1;
        uint64_t tl : 1;
        uint64_t unused : 2;
        uint64_t time : 52;
    };
    uint64_t raw;
};

union inst_type_gfx12 {
    struct {
        uint64_t header : 3;
        uint64_t tm : 3;
        uint64_t tp : 1;
        uint64_t wid : 5;
        uint64_t inst : 8;
    };
    uint64_t raw;

    inst_type_common get() const {
        return inst_type_common{.header = header, .tm = tm, .w64h = 0, .wid = wid, .inst = inst, .bGFX12 = 1};
    }
};

union wend_type_gfx12 {
    struct {
        uint64_t header : 5;
        uint64_t tm : 3;
        uint64_t sa : 1;
        uint64_t simd : 2;
        uint64_t wgp : 4;
        uint64_t wid : 5;
    };
    uint64_t raw;

    wend_type_common get() const {
        return wend_type_common{.header = header, .tm = tm, .sa = sa, .simd = simd, .wgp = wgp, .wid = wid};
    }
};

union wstart_type_gfx12 {
    struct {
        uint64_t header : 5;
        uint64_t tm : 2;
        uint64_t sa : 1;
        uint64_t simd : 2;
        uint64_t wgp : 4;
        uint64_t reserved : 1;
        uint64_t wid : 5;
        uint64_t dispatcher : 5;
        uint64_t count : 7;
    };
    uint64_t raw;

    wstart_type_common get() const {
        return wstart_type_common{.header = header, .tm = tm, .sa = sa, .simd = simd, .wgp = wgp,
            .wid = wid, .pipe = dispatcher & 0x3ul, .me = (dispatcher >> 2ul) & 1ul};
    }
};

union new_pc_type_gfx12 {
    struct {
        uint64_t tm : 3;
        uint64_t wave : 5;
        uint64_t pc : 55;
        uint64_t err : 1;
    };
    uint64_t raw;

    void print() const { /*std::cout << "NEW PC: w" << wave << " 0x" << std::hex << pc << " 0x" << (pc<<2) << std::dec << std::endl;*/ }
};


class gfx12Token : public gfx11Token {
public:
    gfx12Token() = default;
    gfx12Token(int64_t globaltime, uint64_t _contents, gfx10type _type):
        gfx11Token(globaltime, _contents, _type) {}

    static std::vector<gfx10Token> parse(const uint8_t* buffer, const int BUFFER_SIZE);
    static std::array<uint8_t, 64> TOKEN_LEN;
};
