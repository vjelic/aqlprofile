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

    {
        uint64_t header; // Remove 0xF headers
        READ_INC(&header, sizeof(header), 1);
    }

    fileoffset_info_t info;
    size_t numinfo = 1;
    READ_INC(&info, sizeof(fileoffset_info_t), numinfo);
    ret->flags = info.flags;

    ret->kernel_ids_addr = std::vector<pcinfo_t>(info.num_kernel_ids);
    READ_INC(ret->kernel_ids_addr.data(), sizeof(pcinfo_t), info.num_kernel_ids);

    ret->tracesizes = std::vector<uint64_t>(info.num_traces);
    READ_INC(ret->tracesizes.data(), sizeof(uint64_t), info.num_traces);

    ret->traceIDs = std::vector<int64_t>(info.num_traces);
    READ_INC(ret->traceIDs.data(), sizeof(uint64_t), info.num_traces);

    return ret;
}

#ifndef AMD_AQLPROFILE_SQTT_NDA

[[nodiscard]] bool test_buffer(const char* buffer, size_t buf_size)
{
    auto info = CppReturnInfo::UnSerialize(buffer, buf_size);

    size_t maxtrace = 0;
    for (size_t size : info->tracesizes)
        maxtrace = std::max(maxtrace, size);

    if (maxtrace == 0)
        return false;

    bool bValidAddr = false;
    for (pcinfo_t pc : info->kernel_ids_addr)
        if (pc.addr != 0) bValidAddr = true;

    if (!bValidAddr)
        throw "Could not find kernel addr!";

    if (maxtrace < 64)
        throw "Tracesize is too short: " + std::to_string(maxtrace);

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
