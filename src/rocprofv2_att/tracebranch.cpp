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
 
#include "tracebranch.hpp"

std::atomic<int64_t> InstBranch::current_unique_id{0};

size_t InstBranch::sequenceLengthMatch(const Instruction* insts, size_t num_insts) const
{
    size_t i=0; // TODO: Solve different sequence of PC values
    size_t maxiter = std::min(sequence.size(), num_insts);
    for (; i<maxiter; i++)
    {
        if (sequence[i].value == insts[i].value)
            continue;
        else if (i+2 < maxiter
            && sequence[i+1].value == insts[i].value
            && sequence[i].value == insts[i+1].value
            && sequence[i+2].value == insts[i+2].value)
            i += 1;
        else
            break;
    }
    return i;
}

FlattenTree InstBranch::get()
{
    if (branches.size() == 0)
        return {{unique_id}, {sequence}};

    FlattenTree ret{{unique_id}, {sequence}};
    for (auto& v : sequence) if (v.value != WaveInstCategory::PCINFO)
    {
        v.latency = 0;
        v.hitcount = 0;
    }

    for (auto& branch : branches)
    {
        auto temp = branch->get();
        for (auto& id : temp.first)
            ret.first.emplace_back(id);
        for (auto& seq : temp.second)
        {
            seq.insert(seq.begin(), sequence.begin(), sequence.end());
            ret.second.emplace_back(std::move(seq));
        }
    }
    return ret;
}

int64_t InstBranch::recursive_insert(
    const Instruction* insts,
    size_t num_insts
) {
    const size_t match_len = sequenceLengthMatch(insts, num_insts);

    for (size_t i=0; i<match_len; i++)
        sequence[i] += insts[i];

    if (match_len >= num_insts)
    {
        return this->unique_id;
    }
    else if (match_len == sequence.size() && branches.size() == 0)
    {
        for (size_t i=match_len; i<num_insts; i++)
            sequence.push_back(insts[i]);
        return this->unique_id;
    }

    uint64_t insttype = insts[match_len].value;
    if (match_len == sequence.size())
        for (auto& branch : branches)
            if (branch->category == insttype)
                return branch->recursive_insert(insts+match_len, num_insts-match_len);

    InstBranch* newbranch = new InstBranch(insttype, insts+match_len, num_insts-match_len);
    if (match_len >= sequence.size())
    {
        branches.emplace_back(newbranch);
        return newbranch->unique_id;
    }

    InstBranch* oldbranch = new InstBranch(*this, match_len);
    sequence.resize(match_len);

    branches.clear();
    branches.emplace_back(oldbranch);
    branches.emplace_back(newbranch);
    return newbranch->unique_id;
}

InstBranch::InstBranch(InstBranch& other, size_t match_len)
    : category(other.sequence[match_len].value), unique_id(other.unique_id)
{
    other.unique_id = get_unique_id();
    sequence = std::vector<InstructionExt>(other.sequence.begin()+match_len, other.sequence.end());
    branches = std::move(other.branches);
}
