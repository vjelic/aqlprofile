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

#include <sys/stat.h>
#include <sstream>
#include <cstring>
#include <cassert>
#include <atomic>
#include <unordered_set>

#include "trace_parser.hpp"
#include "gfx9/gfx9wave.h"
#include "gfx9/gfx9token.h"
#include "gfx10/gfx10wave.h"
#include "gfx10/gfx10token.h"
#include "gfx11/gfx11wave.h"
#include "gfx11/gfx11token.h"

typedef std::pair<
    std::vector<int64_t>,
    std::vector<std::vector<InstructionExt>>
> FlattenTree;

struct InstBranch
{
    InstBranch(): category(100), unique_id(get_unique_id()) {}
    explicit InstBranch(
        uint64_t category,
        const Instruction* seq,
        size_t seq_size
    ): category(category), unique_id(get_unique_id())
    {
        sequence = std::vector<InstructionExt>(seq_size);
        for (size_t i=0; i<seq_size; i++) sequence[i] = seq[i];
    };
    // Makes leaf, moves type_sequence
    explicit InstBranch(InstBranch& other, size_t match_len);

    size_t sequenceLengthMatch(const Instruction* insts, size_t num_insts) const;

    // Returns the traceID of matching trace
    [[nodiscard]] int64_t insert(const WaveDataInternal& wave)
    {
        auto& insts = wave.instructions;
        if (!insts.size() || insts[0].value != (uint64_t)WaveInstCategory::PCINFO)
            return -1;

        for (auto& b : branches)
            if (insts[0].issue2inst == b->pcvalue)
                return b->recursive_insert(insts.data(), insts.size());

        InstBranch* newbranch = new InstBranch(insts[0].value, insts.data(), insts.size());
        newbranch->pcvalue = insts[0].issue2inst;
        branches.emplace_back(newbranch);
        return newbranch->unique_id;
    }

    void printtree(int N) const
    {
        std::string s = std::to_string(unique_id) + "--" + std::to_string(sequence.size()) + "--";
        std::cout << s << std::string(N, ' ');

        size_t psize = std::min<size_t>(32, sequence.size());
        for (size_t p=0; p<psize; p++)
            std::cout << sequence[p].value << ' ';
        std::cout << std::endl;

        for (auto& b : branches)
            b->printtree(N+2*psize);
    }

    FlattenTree get();
    uint64_t pcvalue = 0;

private:
    static std::atomic<int64_t> current_unique_id;
    static int64_t get_unique_id() { return current_unique_id.fetch_add(1); };

    int64_t unique_id;
    std::vector<InstructionExt> sequence;
    std::vector<std::unique_ptr<InstBranch>> branches;
    const uint64_t category;

    int64_t recursive_insert(const Instruction* inst, size_t ninsts);
};
