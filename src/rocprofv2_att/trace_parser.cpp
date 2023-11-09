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
#include <mutex>
#include "gfx9/gfx9wave.h"
#include "gfx9/gfx9token.h"
#include "gfx10/gfx10wave.h"
#include "gfx10/gfx10token.h"
#include "gfx11/gfx11wave.h"
#include "gfx11/gfx11token.h"
#include "tracebranch.hpp"

std::shared_mutex WaveDataInternal::mutex;
std::unordered_map<uint64_t, size_t> WaveDataInternal::kernelID{{0,0}};
std::atomic<size_t> WaveDataInternal::current_kernel_unique_id{1};

template<typename WaveArrayType> FlattenTree getAggregatedData(WaveArrayType& wavearray);

template<> FlattenTree getAggregatedData(gfx10wave_t::WaveArray& wavearray)
{
    InstBranch branch;

    for (uint64_t wave_id = 0; wave_id < gfx10wave_t::SQTT_CFG_WAVES; wave_id++)
        for (gfx10wave_t& wave : wavearray[wave_id])
            if (wave.instructions.size() > 1)
                wave.traceID = branch.insert(wave);

    return branch.get();
}

template<> FlattenTree getAggregatedData(gfx9wave_t::WaveArray& wavearray)
{
    InstBranch branch;

    for (uint64_t simd = 0; simd < gfx9wave_t::SQTT_CFG_SIMDS; simd++)
        for (uint64_t wave_id = 0; wave_id < gfx9wave_t::SQTT_CFG_WAVES; wave_id++)
            for (gfx9wave_t& wave : wavearray[simd][wave_id])
                if (wave.instructions.size() > 1)
                    wave.traceID = branch.insert(wave);

    return branch.get();
}

union att_header_packet_t {
  struct {
    uint64_t reserved : 14;
    uint64_t navi : 1;
    uint64_t enable : 1;
    uint64_t DSIMDM : 4;
    uint64_t DCU : 5;
    uint64_t DSA : 1;
    uint64_t SEID : 6;
    uint64_t reserved2 : 32;
  };
  uint64_t raw;
};

std::unique_ptr<CppReturnInfo>
AnalyseBinary_GFX9_internal(const uint8_t* tokendata, int buffersize, int target_cu)
{
    auto info = std::make_unique<CppReturnInfo>();
    std::vector<gfx9Token> tokens = gfx9Token::parse(tokendata, buffersize);
    gfx9Token::patch_time(tokens);

    gfx9wave_t::WaveArray wavearray;
    std::tie(
        wavearray,
        info->perfevents,
        info->occupancy,
        info->kernel_ids_addr
    ) = gfx9wave_t::sqtt_simd_analysis(tokens, target_cu);

    info->flags.isNavi = false;
    std::tie(info->traceIDs, info->traces) = getAggregatedData(wavearray);

#ifdef AMD_AQLPROFILE_SQTT_NPI
    int num_waves = 0;
    for (auto& Wave_j : wavearray)
        for (auto& Wave_ij : Wave_j)
            num_waves += Wave_ij.size();

    info->waves = std::vector<WaveDataNPI>(num_waves);
    num_waves = 0;

    for (uint64_t simd = 0; simd < gfx9wave_t::SQTT_CFG_SIMDS; simd++)
    for (uint64_t wave_id = 0; wave_id < gfx9wave_t::SQTT_CFG_WAVES; wave_id++)
    for (gfx9wave_t& wave : wavearray[simd][wave_id])
    {
        info->waves[num_waves].Copy(wave);
        num_waves += 1;
    }
#endif
    return info;
}


std::unique_ptr<CppReturnInfo>
AnalyseBinary_GFX10_internal(const uint8_t* tokendata, int buffersize)
{
    auto info = std::make_unique<CppReturnInfo>();
    std::vector<gfx10Token> tokens = gfx10Token::parse(tokendata, buffersize);
    gfx10wave_t::WaveArray wavearray;
    std::tie(
        wavearray,
        info->perfevents,
        info->occupancy,
        info->kernel_ids_addr
    ) = gfx10wave_t::sqtt_simd_analysis(tokens);

    info->flags.isNavi = true;
    std::tie(info->traceIDs, info->traces) = getAggregatedData(wavearray);

#ifdef AMD_AQLPROFILE_SQTT_NPI
    int num_waves = 0;
    for (auto& Wave_ij : wavearray)
        num_waves += Wave_ij.size();

    info->waves = std::vector<WaveDataNPI>(num_waves);
    num_waves = 0;

    for (uint64_t wave_id = 0; wave_id < gfx10wave_t::SQTT_CFG_WAVES; wave_id++)
    for (gfx10wave_t& wave : wavearray[wave_id])
    {
        info->waves[num_waves].Copy(wave);
        num_waves += 1;
    }
#endif
    return info;
}

std::unique_ptr<CppReturnInfo>
AnalyseBinary_GFX11_internal(const uint8_t* tokendata, int buffersize)
{
    auto info = std::make_unique<CppReturnInfo>();
    std::vector<gfx10Token> tokens = gfx11Token::parse(tokendata, buffersize);
    gfx10wave_t::WaveArray wavearray;
    std::tie(
        wavearray,
        info->perfevents,
        info->occupancy,
        info->kernel_ids_addr
    ) = gfx11wave_t::sqtt_simd_analysis(tokens);

    info->flags.isNavi = true;
    std::tie(info->traceIDs, info->traces) = getAggregatedData(wavearray);

#ifdef AMD_AQLPROFILE_SQTT_NPI
    int num_waves = 0;
    for (auto& Wave_ij : wavearray)
        num_waves += Wave_ij.size();

    info->waves = std::vector<WaveDataNPI>(num_waves);
    num_waves = 0;

    for (uint64_t wave_id = 0; wave_id < gfx11wave_t::SQTT_CFG_WAVES; wave_id++)
    for (gfx10wave_t& wave : wavearray[wave_id])
    {
        info->waves[num_waves].Copy(wave);
        num_waves += 1;
    }
#endif
    return info;
}

// If target_cu < 0, find target_cu from software header
std::unique_ptr<CppReturnInfo>
AnalyseBinary_internal(const uint8_t* buffer, int BUFFER_SIZE, int target_cu)
{
    std::unique_ptr<CppReturnInfo> info{};

    if (target_cu < 0) {
        auto sw_header = *reinterpret_cast<const att_header_packet_t*>(buffer);
        target_cu = sw_header.DCU;
        buffer += sizeof(att_header_packet_t);
    }
    auto hw_header = *reinterpret_cast<const header_type*>(buffer);

    if (hw_header.version == 3)
        info = AnalyseBinary_GFX11_internal(buffer, BUFFER_SIZE);
    else if (hw_header.version == 2 || hw_header.version == 1)
        info = AnalyseBinary_GFX10_internal(buffer, BUFFER_SIZE);
    else
        info = AnalyseBinary_GFX9_internal(buffer, BUFFER_SIZE, target_cu);

    if (info.get() == nullptr) {
        std::cerr << "Invalid ATT data!" << std::endl;
        exit(1);
    }

    info->tracesizes = std::vector<uint64_t>(info->traceIDs.size());
    for (size_t i=0; i<info->traces.size(); i++)
        info->tracesizes[i] = info->traces[i].size();

    info->tracedata = std::vector<InstructionExt*>(info->traceIDs.size());
    for (size_t i=0; i<info->traces.size(); i++)
        info->tracedata[i] = info->traces[i].data();

    info->flags.isValid = true;
    info->flags.version = SQTT_PARSER_VERSION;
#ifdef AMD_AQLPROFILE_SQTT_NPI
    info->flags.npiWaveData = true;
#endif
    return info;
}

python_return_info_t CppReturnInfo::fromCppReturn() const
{
    python_return_info_t info;
    std::memset(&info, 0, sizeof(python_return_info_t));

    info.num_traces = traceIDs.size();
    info.traceIDs = const_cast<int64_t*>(traceIDs.data());
    info.tracesizes = const_cast<uint64_t*>(tracesizes.data());
    info.tracedata = const_cast<InstructionExt**>(tracedata.data());

    info.perfevents = const_cast<perfevent_t*>(perfevents.data());
    info.num_events = perfevents.size();
    info.occupancy = const_cast<occupancy_info_t*>(occupancy.data());
    info.num_occupancy = occupancy.size();
    info.kernel_id_addr = (void*)kernel_ids_addr.data();
    info.num_kernel_ids = kernel_ids_addr.size();

#ifdef AMD_AQLPROFILE_SQTT_NPI
    info.wavenpi = (void*)waves.data();
    info.num_waves = waves.size();
#endif
    info.flags = flags;
    return info;
}

static int filesize(const char* filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return (rc != -1) ? stat_buf.st_size : -1;
}

size_t CppReturnInfo::GetMemoryNeededForSerialization() const
{
    size_t needed_data = sizeof(fileoffset_info_t)
    + traces.size()*(sizeof(uint64_t)+sizeof(int64_t))
    + perfevents.size()*sizeof(perfevent_t)
    + occupancy.size()*sizeof(occupancy_info_t)
    + kernel_ids_addr.size()*sizeof(void*);

    for (auto& trace : traces)
        needed_data += trace.size()*sizeof(InstructionExt);

    return needed_data;
}

#define WRITE_INC(datacopyptr, sizeofdata) {                                          \
    std::memcpy(buffer+offset, datacopyptr, std::min<int64_t>(sizeofdata, spaceleft));\
    offset += std::min<int64_t>(sizeofdata, spaceleft);                               \
    spaceleft -= sizeofdata;                                                          \
    if (spaceleft <= 0) return offset;                                                \
}

size_t CppReturnInfo::Serialize(char* const buffer, size_t buffersize) const
{
    size_t offset = 0;
    int64_t spaceleft = buffersize;
    fileoffset_info_t info{};

    info.flags = flags;
    info.id = 0;
    info.num_kernel_ids = kernel_ids_addr.size();
    info.num_traces = traces.size();
    info.num_events = perfevents.size();
    info.num_occupancy = occupancy.size();

    WRITE_INC(&info, sizeof(info));
    WRITE_INC(kernel_ids_addr.data(), kernel_ids_addr.size()*sizeof(uint64_t));
    WRITE_INC(tracesizes.data(), tracesizes.size()*sizeof(uint64_t));
    WRITE_INC(traceIDs.data(), traceIDs.size()*sizeof(uint64_t));

    for (auto& trace : traces)
        WRITE_INC(trace.data(), trace.size()*sizeof(InstructionExt));

    WRITE_INC(perfevents.data(), perfevents.size()*sizeof(uint64_t));
    WRITE_INC(occupancy.data(), occupancy.size()*sizeof(uint64_t));

    return offset;
}

#define READ_INC(datacopyptr, sizeofdata, numelements) {                              \
    auto avail_elem = std::min<uint64_t>(numelements, spaceleft / sizeofdata);        \
    std::memcpy(datacopyptr, buffer+offset, avail_elem*sizeofdata);                   \
    offset += numelements*sizeofdata;                                                 \
    spaceleft -= numelements*sizeofdata;                                              \
    if (spaceleft <= 0) return ret;                                                   \
}

std::unique_ptr<CppReturnInfo> CppReturnInfo::UnSerialize(const char* buffer, size_t buffersize)
{
    size_t offset = 0;
    int64_t spaceleft = buffersize;
    auto ret = std::make_unique<CppReturnInfo>();

    fileoffset_info_t info;
    size_t numinfo = 1;
    READ_INC(&info, sizeof(fileoffset_info_t), numinfo);
    ret->flags = info.flags;

    ret->kernel_ids_addr = std::vector<uint64_t>(info.num_kernel_ids);
    READ_INC(ret->kernel_ids_addr.data(), sizeof(uint64_t), info.num_kernel_ids);
    
    ret->tracesizes = std::vector<uint64_t>(info.num_traces);
    READ_INC(ret->tracesizes.data(), sizeof(uint64_t), info.num_traces);

    ret->traceIDs = std::vector<int64_t>(info.num_traces);
    READ_INC(ret->traceIDs.data(), sizeof(uint64_t), info.num_traces);

    for (size_t tsize : ret->tracesizes)
    {
        ret->traces.push_back(std::vector<InstructionExt>(tsize, {WaveInstCategory::NONE,0,0}));
        ret->tracedata.push_back(ret->traces.back().data());
        READ_INC(ret->tracedata.back(), sizeof(InstructionExt), tsize);
    }

    ret->perfevents = std::vector<perfevent_t>(info.num_events);
    READ_INC(ret->perfevents.data(), sizeof(perfevent_t), info.num_events);

    ret->occupancy = std::vector<occupancy_info_t>(info.num_occupancy);
    READ_INC(ret->occupancy.data(), sizeof(occupancy_info_t), info.num_occupancy);

    return ret;
}

std::unordered_map<uint64_t, std::unique_ptr<CppReturnInfo>> map_globalstate{};
uint64_t globalstate_unique_id = 0;
std::mutex globalstate_lock;

extern "C"
{
#ifdef AMD_AQLPROFILE_SQTT_NPI
    __attribute__((visibility("default")))
    python_return_info_t AnalyseBinary(const char* filename)
    {
        const int BUFFER_SIZE = filesize(filename);

        if (BUFFER_SIZE < 16) {
            std::cout << "Invalid filename: " << filename << std::endl;
            return {};
        }

        std::ifstream file(filename, std::ios::binary);
        assert(file.good());

        std::vector<uint64_t> buffer(BUFFER_SIZE/8+2, 0);
        file.read((char*)buffer.data(), BUFFER_SIZE);

        auto globalstate = AnalyseBinary_internal((const uint8_t*)buffer.data(), BUFFER_SIZE, -1);
        python_return_info_t info = globalstate->fromCppReturn();

        {
            std::lock_guard<std::mutex> maplock(globalstate_lock);
            map_globalstate[globalstate_unique_id] = std::move(globalstate);
            info.id = globalstate_unique_id;
            globalstate_unique_id += 1;
        }
        return info;
    }
#else
    __attribute__((visibility("default")))
    python_return_info_t AnalyseBinary(const char* filename)
    {
        const int BUFFER_SIZE = filesize(filename);

        if (BUFFER_SIZE < 16) {
            std::cout << "Invalid filename: " << filename << std::endl;
            return {};
        }

        std::ifstream file(filename, std::ios::binary);
        assert(file.good());

        std::vector<char> buffer(BUFFER_SIZE+8, 0);
        file.read(buffer.data(), BUFFER_SIZE);

        auto globalstate = CppReturnInfo::UnSerialize(buffer.data()+8, BUFFER_SIZE-8);
        python_return_info_t info = globalstate->fromCppReturn();

        {
            std::lock_guard<std::mutex> maplock(globalstate_lock);
            map_globalstate[globalstate_unique_id] = std::move(globalstate);
            info.id = globalstate_unique_id;
            globalstate_unique_id += 1;
        }
        return info;
    }
#endif

    __attribute__((visibility("default")))
    void FreeBinary(uint64_t id)
    {
        std::lock_guard<std::mutex> maplock(globalstate_lock);
        map_globalstate.erase(id);
    }
}
