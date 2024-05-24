/* Copyright (c) 2022-2023 Advanced Micro Devices, Inc.

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
#include <memory>
#include <cstring>
#include <atomic>
#include <mutex>
#include <shared_mutex>

typedef union
{
    uint64_t raw;
    struct {
        uint64_t isValid : 1;
        uint64_t isNavi : 1;
        uint64_t npiWaveData : 1;
        uint64_t version : 13;
        uint64_t gfxip : 8;
        uint64_t reserved : 40;
    };
} _output_flags_t;

typedef struct {
    size_t addr;
    size_t marker_id;
} pcinfo_t;

struct CppReturnInfo
{
    _output_flags_t flags;
    std::vector<pcinfo_t> kernel_ids_addr;
    std::vector<int64_t> traceIDs;
    std::vector<uint64_t> tracesizes;
    static std::unique_ptr<CppReturnInfo> UnSerialize(const char* buffer, size_t buffersize);
};

struct fileoffset_info_t
{
    _output_flags_t flags;
    uint64_t id;

    uint64_t num_kernel_ids;
    uint64_t num_traces;
    uint64_t num_events;
    uint64_t num_occupancy;
};

[[nodiscard]] bool test_buffer(const char* buffer, size_t buf_size);
