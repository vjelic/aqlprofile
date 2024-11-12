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
#include "gfx12token.h"

class gfx12TokenLookupTable : public gfx11TokenLookupTable {
public:
    gfx12TokenLookupTable() {
        AddEncoding({gfx10type::INST, {0,1,0}});
        AddEncoding({gfx10type::SHADER_DATA, {0,1,1,0,0,0,0}});
        AddEncoding({gfx10type::SHADER_DATA_SHORT, {0,1,1,0,1,0,1}});
        AddEncoding({gfx10type::EXEC_POPCOUNT1, {0,1,1,0,0,1,1}});
        AddEncoding({gfx10type::EXEC_POPCOUNT3, {0,1,1,0,1,0}});
        AddEncoding({gfx10type::NEW_PC_GFX12, {1,0,0,0,0,1,0}});
    }
    int64_t getDelta(gfx10type type, uint64_t contents) {
        auto res = time_bits[type];
        uint64_t beg = res.first;
        uint64_t mask = (1ull << (res.second - beg)) - 1;
        return ((contents >> beg) & mask) + 4 * (type==gfx10type::TIME);
    };
    int64_t getTime(gfx10type type, uint64_t contents, int64_t cur_time) {
        if (type == gfx10type::TIMESTAMP) {
            timestamp_gfx12_type stamp { .raw = contents };
            if (stamp.rt == 0)
                return stamp.time + cur_time;
            return cur_time;
        }
        return getDelta(type, contents) + cur_time;
    };
    private:
        static std::unordered_map<int, std::pair<int,int>> time_bits;
        bool bInitTime = false;
};