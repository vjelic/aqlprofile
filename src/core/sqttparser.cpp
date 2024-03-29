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

enum trace_type_ids_t
{
    KERNEL_ID_ADDR = 1,
    TRACE_IDS,
    TRACE_DATA,
    OCCUPANCY,
    PERFEVENT,
    WAVES,
    SHADER_NPI_DATA,
};

std::unordered_map<int, std::string> trace_type_ids = {
    {KERNEL_ID_ADDR, "kernel_ids_addr"},
    {TRACE_IDS, "traceids",},
    {TRACE_DATA, "tracedata"},
    {OCCUPANCY, "occupancy"},
#ifdef AMD_AQLPROFILE_SQTT_NPI
    {PERFEVENT, "perfevent"},
    {WAVES, "waves"},
    {SHADER_NPI_DATA, "generic_data"},
#endif
};

PUBLIC_API void aqlprofile_att_parser_iterate_event_list(
    aqlprofile_att_parser_iterate_event_cb_t callback,
    void* userdata
) {
    for (auto& [id, metadata] : trace_type_ids)
        callback(id, metadata.c_str(), userdata);
}


PUBLIC_API hsa_status_t aqlprofile_att_parse_data(
    aqlprofile_att_se_data_callback_t se_data_callback,
    aqlprofile_att_trace_callback_t trace_callback,
    aqlprofile_att_isa_callback_t isa_callback,
    void* cbdata
) {
    std::shared_ptr<ICodeServicer> service = std::make_shared<CodeService>(isa_callback, cbdata);
    std::unique_ptr<Stitcher> stitcher{nullptr};

    int shader = 0;
    uint8_t* buffer = nullptr;
    uint64_t buffer_size = 0;
    size_t remaining = se_data_callback(&shader, &buffer, &buffer_size, cbdata);

    while (remaining && buffer_size)
    {
        auto ret = AnalyseBinary_internal(buffer, buffer_size, 1);

        auto& traceids = ret->traceIDs;
        trace_callback(TRACE_IDS, shader, (void*)traceids.data(), traceids.size(), cbdata);
        auto& kernels = ret->kernel_ids_addr;
        trace_callback(KERNEL_ID_ADDR, shader, (void*)kernels.data(), kernels.size(), cbdata);
        auto& occ = ret->occupancy;
        trace_callback(OCCUPANCY, shader, (void*)occ.data(), occ.size(), cbdata);

        if (!stitcher)
            stitcher = std::make_unique<Stitcher>(service, !ret->flags.isNavi);

        for (size_t t=0; t<ret->traces.size(); t++) if (ret->traces[t].size() > 1)
        {
            stitcher->stitch(ret->traces.at(t));
            std::vector<InstructionExt>& trace = ret->traces.at(t);
            trace_callback(TRACE_DATA, traceids.at(t), (void*)trace.data(), trace.size(), cbdata);
        }

#ifdef AMD_AQLPROFILE_SQTT_NPI
        for (size_t t=0; t<ret->waves.size(); t++)
            trace_callback(WAVES, t, (void*)ret->waves.data(), ret->waves.size(), cbdata);
#endif

        remaining = se_data_callback(&shader, &buffer, &buffer_size, cbdata);
    }

    return HSA_STATUS_SUCCESS;
};
