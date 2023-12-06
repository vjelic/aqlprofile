#include <iostream>
#include <memory>
#include <cstring>
#include <vector>
#include <fstream>
#include <string_view>

#include "parser_test.hpp"

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

    std::cout << "info.flags.raw: " << info.flags.raw << std::endl;
    std::cout << "info.num_kernel_ids: " << info.num_kernel_ids << std::endl;
    std::cout << "info.num_traces: " << info.num_traces << std::endl;
    std::cout << "info.num_events: " << info.num_events << std::endl;
    std::cout << "info.num_occupancy: " << info.num_occupancy << std::endl;

    ret->kernel_ids_addr = std::vector<uint64_t>(info.num_kernel_ids);
    READ_INC(ret->kernel_ids_addr.data(), sizeof(uint64_t), info.num_kernel_ids);
    
    ret->tracesizes = std::vector<uint64_t>(info.num_traces);
    READ_INC(ret->tracesizes.data(), sizeof(uint64_t), info.num_traces);

    std::cout << "Trace sizes: ";
    for (size_t tsize : ret->tracesizes)
        std::cout << tsize << ',';
    std::cout << std::endl;

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

#ifndef AMD_AQLPROFILE_SQTT_NPI

[[nodiscard]] bool test_buffer(const char* buffer, size_t buf_size)
{
    auto info = CppReturnInfo::UnSerialize(buffer, buf_size);

    if (info->occupancy.size() == 0)
        throw "Occupancy is zero!";

    size_t maxtrace = 0;
    for (size_t size : info->tracesizes)
        maxtrace = std::max(maxtrace, size);

    if (maxtrace == 0)
        return false;

    bool bValidAddr = false;
    for (uint64_t addr : info->kernel_ids_addr)
        if (addr != 0) bValidAddr = true;

    if (!bValidAddr)
        throw "Could not find kernel addr!";

    if (maxtrace < 64)
        throw "Tracesize is too short: " + std::to_string(maxtrace);

    for (auto& trace : info->traces)
    {
        size_t vmem_ops = 0;
        size_t pcinfos = 0;
        size_t salus = 0;
        size_t valus = 0;
        size_t smems = 0;
        if (trace.size() != maxtrace) continue; // Get largest trace only

        for (auto& inst : trace)
        {
            auto inst_type = static_cast<WaveInstCategory>(inst.value);
            if (inst_type == WaveInstCategory::VMEM || inst_type == WaveInstCategory::FLAT)
                vmem_ops ++;
            else if (inst_type == WaveInstCategory::SALU)
                salus ++;
            else if (inst_type == WaveInstCategory::VALU)
                valus ++;
            else if (inst_type == WaveInstCategory::PCINFO)
                pcinfos ++;
            else if (inst_type == WaveInstCategory::SMEM)
                smems ++;
        }

        if (pcinfos == 0 || pcinfos > 20)
            throw "Invalid number of PCINFOs: " + std::to_string(pcinfos);
        if (smems < 2 || smems > 9)
            throw "Invalid number of SMEMs: " + std::to_string(smems);
        if (vmem_ops < 10 || vmem_ops > 19)
            throw "Invalid number of VMEMs: " + std::to_string(vmem_ops);
        if (salus < 2*smems || salus > 256)
            throw "Invalid number of SALUs: " + std::to_string(salus);
        if (valus < 30 || valus > 2048)
            throw "Invalid number of VALUs: " + std::to_string(valus);

        std::cout << "Nums: " << valus << ' ' << salus << ' ' << vmem_ops << ' ' << smems << ' ' << pcinfos << ' ' << std::endl;
    }
    return true;
}

#else

[[nodiscard]] bool test_buffer(const char* buffer, size_t buf_size) { return true; }

#endif

bool test_fromfile(std::string_view filename)
{
    std::vector<char> buffer;
    {
        std::ifstream file(filename.data(), std::ios::in | std::ios::binary);

        if (!file.is_open())
        {
            std::cerr << "Could not find .att file " + std::string(filename) << std::endl;
            return false;
        }

        file.seekg(0, file.end);
        buffer.resize(file.tellg());
        file.seekg(0, file.beg);
        file.read(buffer.data(), buffer.size());
    }

    try {
        return test_buffer(buffer.data(), buffer.size());
    } catch(std::string& s) {
        std::cerr << "SQTT Parser for " << filename << " string test error: " << s << std::endl;
    } catch(const char* s) {
        std::cerr << "SQTT Parser for " << filename << " string test error: " << s << std::endl;
    } catch(std::exception& e) {
        std::cerr << "SQTT Parser for " << filename << " generic test error. " << e.what() << std::endl;
    }

    return false;
}
