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
#include "../gfx10/gfx10token.h"
#include "../gfx10/gfx10parser.h"


union timestamp_gfx11_type {
    struct {
        uint64_t header : 7;
        uint64_t _unused1 : 1;
        uint64_t type : 2;
        uint64_t _unused2 : 2;
        uint64_t time : 36;
    };
    uint64_t raw;

    void print() const {
        //std::cout << "TIMESTAMP - type:" << type << " time:" << time << std::endl;
    }
};

union util_ctr_gfx11_type {
    struct {
        uint64_t header : 7;
        uint64_t tm : 2;
        uint64_t cID : 2;
        uint64_t spi_busy : 4;
        uint64_t vdata0 : 4;
        uint64_t vdata1 : 4;
        uint64_t sdata0 : 4;
        uint64_t sdata1 : 4;
        uint64_t lds0 : 4;
        uint64_t lds1 : 4;
        uint64_t exp0 : 4;
        uint64_t exp1 : 4;
        uint64_t SA : 1;
    };
    uint64_t raw;

    static const int ctr_size = 4;
    void print() const {}
};

class gfx11Token : public gfx10Token {
public:
    gfx11Token() = default;
    gfx11Token(int64_t globaltime, uint64_t _contents, gfx10type _type):
        gfx10Token(globaltime, _contents, _type) {}

    static std::vector<gfx10Token> parse(const uint8_t* buffer, const int BUFFER_SIZE);
    static std::array<uint8_t, 64> TOKEN_LEN;
};
