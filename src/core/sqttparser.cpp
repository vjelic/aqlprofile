#include "core/aql_profile.hpp"
#include "core/include/aql_profile_v2.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "../rocprofv2_att/tracebranch.hpp"
#include "../rocprofv2_att/trace_parser.hpp"
#include "../rocprofv2_att/stitch/stitch.hpp"

class CodeService: public ICodeServicer
{
public:
    CodeService() = delete;
    CodeService(aqlprofile_att_isa_callback_t isa_str, void* _userdata): 
        isa_cb(isa_str), userdata(_userdata)
    {
        isa_memory_copy.resize(64);
        source_memory_copy.resize(64);
    };

    virtual assemblyLine GetInstruction(pcinfo_t pc) override
    {
        size_t isa_len = isa_memory_copy.size();
        size_t source_len = source_memory_copy.size();
        uint64_t memsize = 0;

        auto status = isa_cb(isa_memory_copy.data(), source_memory_copy.data(), &memsize, &isa_len, &source_len, pc.marker_id, pc.addr, userdata);
        if (status == HSA_STATUS_ERROR_OUT_OF_RESOURCES)
        {
            if (isa_memory_copy.size() < isa_len)
                isa_memory_copy.resize(isa_len);
            if (source_memory_copy.size() < source_len)
                source_memory_copy.resize(source_len);

            status = isa_cb(isa_memory_copy.data(), source_memory_copy.data(), &memsize, &isa_len, &source_len, pc.marker_id, pc.addr, userdata);
        }

        if (status != HSA_STATUS_SUCCESS)
            throw "ISA Callback returned error " + std::to_string(status);

        assemblyLine isa;
        isa.addr = pc;
        isa.line = isa_memory_copy.substr(0, isa_len);
        isa.loc = source_memory_copy.substr(0, source_len);
        isa.next = {isa.addr.addr + memsize, isa.addr.marker_id};
        isa.cat = Trie::inst_type(isa.line);
        return isa;
    };

private:
    aqlprofile_att_isa_callback_t const isa_cb;
    void* const userdata;
    std::string isa_memory_copy;
    std::string source_memory_copy;
};


/*
att_output_flags_t flags;
    std::vector<uint64_t> kernel_ids_addr;
    std::vector<int64_t> traceIDs;
    std::vector<uint64_t> tracesizes;
    std::vector<InstructionExt*> tracedata;
    std::vector<std::vector<InstructionExt>> traces;
    std::vector<occupancy_info_t> occupancy;
    std::vector<att_perfevent_t> perfevents;
#ifdef AMD_AQLPROFILE_SQTT_NPI
    std::vector<WaveDataNPI> waves;
#endif

    python_return_info_t fromCppReturn() const;
    size_t GetMemoryNeededForSerialization() const;
    size_t Serialize(char* buffer, size_t buffersize) const;
    static std::unique_ptr<CppReturnInfo> UnSerialize(const char* buffer, size_t buffersize);


    typedef hsa_status_t(*aqlprofile_att_trace_callback_t)(
    int trace_type_id,
    int correlation_id,
    void* trace_events,
    uint64_t trace_size,
    void* userdata
);

*/

std::unordered_map<std::string, int> trace_type_ids = {
    {"kernel_ids_addr",  1},
    {"traceIDs",         2},
    {"tracedata",        3},
    {"occupancy",        4},
    {"perfevents",       5},
    {"waves",            6},
    {"wave_instruction", 7},
    {"wave_timeline",    8},
};

__attribute__((visibility("default"))) hsa_status_t aqlprofile_att_parse_data(
    aqlprofile_att_se_data_callback_t se_data_callback,
    aqlprofile_att_trace_callback_t trace_callback,
    aqlprofile_att_isa_callback_t isa_callback,
    void* userdata
) {
    std::shared_ptr<ICodeServicer> service = std::make_shared<CodeService>(isa_callback, userdata);
    std::unique_ptr<Stitcher> stitcher{nullptr};

    int shader = 0;
    uint8_t* buffer = nullptr;
    uint64_t buffer_size = 0;
    size_t remaining = se_data_callback(&shader, &buffer, &buffer_size, userdata);

    while (remaining && buffer_size)
    {
        auto ret = AnalyseBinary_internal(buffer, buffer_size, 1);

        trace_callback(trace_type_ids["occupancy"], 0, (void*)ret->occupancy.data(), ret->occupancy.size(), userdata);
        trace_callback(trace_type_ids["kernel_ids_addr"], 0, (void*)ret->kernel_ids_addr.data(), ret->kernel_ids_addr.size(), userdata);

        if (!stitcher)
            stitcher = std::make_unique<Stitcher>(service, !ret->flags.isNavi);

        for (size_t t=0; t<ret->traces.size(); t++) if (ret->traces[t].size() > 1)
        {
            stitcher->stitch(ret->traces[t]);
            trace_callback(trace_type_ids["tracedata"], t, (void*)ret->traces[t].data(), ret->traces[t].size(), userdata);
        }

        remaining = se_data_callback(&shader, &buffer, &buffer_size, userdata);
    }

    return HSA_STATUS_SUCCESS;
};
