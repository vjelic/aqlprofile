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
#include <unordered_map>
#include <vector>
#include "gfx10token.h"

struct encoding_t {
    gfx10type type;
    std::vector<uint8_t> bits;
};

class gfx10TokenLookupTable : public std::array<uint8_t, 256> {
public:
    gfx10TokenLookupTable();
    void AddEncoding(const encoding_t& encoding);

    uint8_t lookup(uint8_t u) const { return data()[u]; };
    uint8_t lookup(uint64_t u) const { return lookup(((uint8_t*)&u)[0]); };

    int64_t getDelta(gfx10type type, uint64_t contents) {
        auto res = time_bits[type];
        uint64_t beg = res.first;
        uint64_t end = res.second;
        return (contents >> beg) & ((1ull << (end-beg)) - 1);
    };

    int64_t getTime(gfx10type type, uint64_t contents, int64_t cur_time) {
        if (type == gfx10type::TIMESTAMP) {
            timestamp_gfx10_type stamp { .raw = contents };
            if (stamp.type == 1)
                return stamp.time + cur_time;
            /*else if (stamp.type == 2 && stamp.time >= cur_time)
                return stamp.time; */
            return cur_time;
        }
        return getDelta(type, contents) + cur_time;
    };

    private:
        static std::unordered_map<int, std::pair<int16_t,int16_t>> time_bits;
        static std::vector<encoding_t> bit_encodings;
};