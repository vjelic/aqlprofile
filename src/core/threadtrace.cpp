#include "core/aql_profile.hpp"
#include "core/include/aql_profile_v2.h"

#include <cstdint>
#include <future>
#include <map>
#include <string>
#include <vector>

#include "core/logger.h"
#include "core/pm4_factory.h"
#include "pm4/cmd_builder.h"
#include "pm4/sqtt_builder.h"

#include "core/commandbuffermgr.hpp"
#include "memorymanager.hpp"
#include "../rocprofv2_att/trace_parser.hpp"

#define THREAD_TRACE_PREFIX_SIZE 0x100
#define DEFAULT_TRACE_BUFFER_SIZE (3<<26)

inline att_header_packet_t getHeaderPacket(int SE, int CU, int SIMD)
{
    att_header_packet_t header{.raw = 0};
    header.legacy_version = 0;
    header.gfx9_version2 = 4;
    header.SEID = SE;
    header.DCU = CU;
    header.DSIMDM = SIMD;
    header.DSA = 0;
    return header;
}

namespace aql_profile_v2
{

hsa_status_t _internal_aqlprofile_att_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_att_data_callback_t callback,
    void* userdata
) {
    hsa_status_t status = HSA_STATUS_SUCCESS;

    auto shared_memorymgr = MemoryManager::GetManager(handle.handle);
    TraceMemoryManager* memorymgr = dynamic_cast<TraceMemoryManager*>(shared_memorymgr.get());
    if (!memorymgr)
        return HSA_STATUS_ERROR_INVALID_ARGUMENT;

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(memorymgr->GetAgent());
    pm4_builder::SqttBuilder* sqttbuilder = pm4_factory->GetSqttBuilder();
    const size_t se_number_total = pm4_factory->GetShaderEnginesNumber();
    auto* control_ptr = memorymgr->GetTraceControlBuf<pm4_builder::TraceControl>();

    // Check if SQTT buffer was wrapped
    for (size_t se = 0; se < se_number_total; se++)
    {
        if (control_ptr[se].status & sqttbuilder->GetUTCErrorMask())
        {
            ERR_LOGGING << "SQTT memory error received, SE(" << se << ")";
            status = HSA_STATUS_ERROR_EXCEPTION;
        }
        else if (control_ptr[se].status & sqttbuilder->GetBufferFullMask())
        {
            ERR2_LOGGING << "SQTT data buffer full, SE(" << se << ")";
            if (status == HSA_STATUS_SUCCESS) status = HSA_STATUS_ERROR_OUT_OF_RESOURCES;
        }
    }

    std::vector<size_t> sample_sizes(se_number_total, 0);
    size_t max_sample_size = 0;

    // The samples sizes are returned in the control buffer
    for (uint64_t se_index = 0; se_index < se_number_total; se_index++)
    {
        bool bMaskedIn = sqttbuilder->GetTargetCU(se_index) >= 0;
        uint64_t sample_capacity = sqttbuilder->GetCapacity(se_index);
        void* sample_ptr = reinterpret_cast<void*>(sqttbuilder->GetSEBaseAddr(se_index));

        // WPTR specifies the index in thread trace buffer where next token will be
        // written by hardware. The index is incremented by size of 32 bytes.
        size_t wptr_mask = sqttbuilder->GetWritePtrMask();
        size_t sample_size = (control_ptr[se_index].wptr & wptr_mask) * sqttbuilder->GetWritePtrBlk();

        // GFX11 hardware bug workaround
        if (pm4_factory->GetGpuId() == aql_profile::GFX11_GPU_ID)
        {
            sample_size = sample_size - reinterpret_cast<uint64_t>(sample_ptr);
            sample_size &= (1ull << 29) - 1;
        }

        if (sample_size >= sample_capacity)
        {
            ERR_LOGGING << "SQTT data out of bounds, sample_id(" << se_index << ") size(" << sample_size
                        << "/" << sample_capacity << ")";
            sample_size = sample_capacity;
            if (status == HSA_STATUS_SUCCESS)
                status = HSA_STATUS_ERROR_OUT_OF_RESOURCES;
        }

        sample_sizes.at(se_index) = sample_size;
        max_sample_size = std::max(sample_size, max_sample_size);
    }

    std::vector<size_t> cpu_sample(max_sample_size/sizeof(size_t)+sizeof(att_header_packet_t), 0);

    // The samples sizes are returned in the control buffer
    for (uint64_t se_index = 0; se_index < se_number_total; se_index++)
    {
        int target_cu = sqttbuilder->GetTargetCU(se_index);
        if (target_cu < 0)
            continue;

        void* sample_ptr = reinterpret_cast<void*>(sqttbuilder->GetSEBaseAddr(se_index));
        size_t sample_size = sample_sizes.at(se_index);
        size_t sample_size_plus_header = sample_size;

        char* sample_data_ptr = (char*)cpu_sample.data();
        if (pm4_factory->GetGpuId() != aql_profile::GFX10_GPU_ID && pm4_factory->GetGpuId() != aql_profile::GFX11_GPU_ID)
        {
            auto* header = reinterpret_cast<att_header_packet_t*>(cpu_sample.data());
            *header = getHeaderPacket(se_index, target_cu, 0xF);
            sample_data_ptr += sizeof(att_header_packet_t);
            sample_size_plus_header = sample_size + sizeof(att_header_packet_t);
        }

        memorymgr->CopyMemory((void*)sample_data_ptr, sample_ptr, sample_size);
#ifdef AMD_AQLPROFILE_SQTT_NDA
        callback(se_index, (void*)cpu_sample.data(), sample_size_plus_header, userdata);
#else
        auto return_info = AnalyseBinary_internal((uint8_t*)cpu_sample.data(), sample_size_plus_header, false);
        std::vector<uint8_t> mem;
        mem.resize(return_info->GetMemoryNeededForSerialization());
        return_info->Serialize(mem.data(), mem.size());
        callback(se_index, (void*)mem.data(), mem.size(), userdata);
#endif
    }

    return status;
}

hsa_status_t _internal_aqlprofile_att_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_att_control_aql_packets_t* packets,
    aqlprofile_att_profile_t profile,
    aqlprofile_memory_alloc_callback_t alloc_cb,
    aqlprofile_memory_dealloc_callback_t dealloc_cb,
    aqlprofile_memory_copy_t copy_fn,
    void* userdata
) {
    pm4_builder::CmdBuffer start_cmd;
    pm4_builder::CmdBuffer stop_cmd;

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    pm4_builder::TraceConfig trace_config{};

    memset((char*)&trace_config, 0, sizeof(pm4_builder::TraceConfig));
    trace_config.vmIdMask = 0xF;
    trace_config.simd_sel = 0xF;
    trace_config.perfMASK = (1ul << 32) - 1;
    trace_config.se_mask = 0x11111111;

    const size_t se_number_total = pm4_factory->GetShaderEnginesNumber();
    size_t buffer_size = DEFAULT_TRACE_BUFFER_SIZE;

    if (profile.parameters)
    for (const auto* p = profile.parameters; p < profile.parameters + profile.parameter_count; p++)
    switch (p->parameter_name)
    {
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SE_MASK:
            trace_config.se_mask = p->value & ((1ull << se_number_total) - 1);
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_COMPUTE_UNIT_TARGET:
            if (p->value > 15)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: CuId must be between 0 and 15, TargetCu", p->value);
            trace_config.targetCu = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_VM_ID_MASK:
            trace_config.vmIdMask = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_MASK:
            if ((p->value & 0x50) != 0)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: Mask should have bits [4,6] set to Zero, Mask", p->value);
            trace_config.deprecated_mask = p->value;
            trace_config.targetCu = p->value & 0xF;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK:
            if ((p->value & 0xFF000000) != 0)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: TokenMask should have bits [31:25] set to Zero, TokenMask",
                    p->value);
            trace_config.deprecated_tokenMask = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK2:
            trace_config.deprecated_tokenMask2 = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SAMPLE_RATE:
            trace_config.sampleRate = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_K_CONCURRENT:
            trace_config.concurrent = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SIMD_SELECTION:
            trace_config.simd_sel = p->value & 0xF;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_OCCUPANCY_MODE:
            trace_config.occupancy_mode = p->value ? 1 : 0;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_ATT_BUFFER_SIZE:
            buffer_size = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER_MASK:
            trace_config.perfMASK = p->value;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER_CTRL:
            trace_config.perfCTRL = ((p->value & 0x1F) << 8) | 0xFFFF007F;
            break;
        case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER_NAME:
            if (trace_config.n_perfcounters < 8) {
                trace_config.perfcounters[trace_config.n_perfcounters] = p->value;
                trace_config.n_perfcounters++;
            }
            break;
        default:
            ERR_LOGGING << "Bad trace parameter name (" << p->parameter_name << ")";
            return HSA_STATUS_ERROR_INVALID_ARGUMENT;
    }

    const size_t control_size = sizeof(pm4_builder::TraceControl) * se_number_total;

    auto memorymgr = std::make_shared<TraceMemoryManager>(
        profile.agent,
        alloc_cb,
        dealloc_cb,
        copy_fn,
        userdata
    );
    memorymgr->CreateTraceControlBuf(control_size + THREAD_TRACE_PREFIX_SIZE);
    memorymgr->CreateOutputBuf(buffer_size);
    MemoryManager::RegisterManager(memorymgr);

    auto* control_ptr = memorymgr->GetTraceControlBuf<pm4_builder::TraceControl>();

    trace_config.control_buffer_ptr = control_ptr;
    trace_config.control_buffer_size = control_size;
    trace_config.data_buffer_ptr = memorymgr->GetOutputBuf();
    trace_config.data_buffer_size = memorymgr->GetOutputBufSize();

    uint32_t se_per_xcc = pm4_factory->GetShaderEnginesNumber() / pm4_factory->GetXccNumber();
    pm4_builder::SqttBuilder* sqtt_builder = pm4_factory->GetSqttBuilder();

    // Generate start commands
    sqtt_builder->Begin(&start_cmd, &trace_config);
    // Generate stop commands
    sqtt_builder->End(&stop_cmd, &trace_config);

    // Copy generated commands
    const size_t start_size = aql_profile::CommandBufferMgr::Align(start_cmd.Size());
    const size_t stop_size = aql_profile::CommandBufferMgr::Align(stop_cmd.Size());
    memorymgr->CreateCmdBuf(start_size + stop_size);

    handle->handle = memorymgr->GetHandler();
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    uint8_t* cmdbuf = reinterpret_cast<uint8_t*>(memorymgr->GetCmdBuf());

    copy_fn(cmdbuf, start_cmd.Data(), start_cmd.Size(), userdata);
    aql_profile::PopulateAql(cmdbuf, start_cmd.Size(), cmd_writer, &packets->start_packet);
    cmdbuf += start_size;
    copy_fn(cmdbuf, stop_cmd.Data(), stop_cmd.Size(), userdata);
    aql_profile::PopulateAql(cmdbuf, stop_cmd.Size(), cmd_writer, &packets->stop_packet);

    return HSA_STATUS_SUCCESS;
}

// Method to populate the provided AQL packet with ATT Markers
hsa_status_t _internal_aqlprofile_att_codeobj_load_marker(
    hsa_ext_amd_aql_pm4_packet_t* packets,
    aqlprofile_handle_t handle,
    aqlprofile_att_header_marker_t header,
    uint64_t id,
    uint64_t addr,
    uint64_t size
) {
    auto shared_memorymgr = MemoryManager::GetManager(handle.handle);
    TraceMemoryManager* memorymgr = dynamic_cast<TraceMemoryManager*>(shared_memorymgr.get());
    if (!memorymgr)
        return HSA_STATUS_ERROR_INVALID_ARGUMENT;

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(memorymgr->GetAgent());
    pm4_builder::SqttBuilder* sqttbuilder = pm4_factory->GetSqttBuilder();
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    pm4_builder::CmdBuffer commands;

    if (!header.isUnload)
    {
        sqttbuilder->InsertMarker(&commands, uint32_t(addr), ATT_MARKER_ADDR_LO_CHANNEL);
        sqttbuilder->InsertMarker(&commands, addr >> 32,     ATT_MARKER_ADDR_HI_CHANNEL);
        sqttbuilder->InsertMarker(&commands, uint32_t(size), ATT_MARKER_SIZE_LO_CHANNEL);
        sqttbuilder->InsertMarker(&commands, size >> 32,     ATT_MARKER_SIZE_HI_CHANNEL);
    }
    if (!header.legacy_id)
    {
        sqttbuilder->InsertMarker(&commands, uint32_t(id), ATT_MARKER_ID_LO_CHANNEL);
        sqttbuilder->InsertMarker(&commands, id >> 32,     ATT_MARKER_ID_HI_CHANNEL);
    }
    sqttbuilder->InsertMarker(&commands, header.raw, ATT_MARKER_HEADER_CHANNEL);

    void* cmdbuffer = memorymgr->AddMarkerCmdBuffer(commands.Size());

    memcpy(cmdbuffer, commands.Data(), commands.Size());
    aql_profile::PopulateAql(cmdbuffer, commands.Size(), cmd_writer, packets);

    return HSA_STATUS_SUCCESS;
}

} // namespace aql_profile_v2

extern "C" {

// Method to populate the provided AQL packet with ATT Markers
PUBLIC_API hsa_status_t
aqlprofile_att_codeobj_load_marker(
    hsa_ext_amd_aql_pm4_packet_t* packets,
    aqlprofile_handle_t handle,
    aqlprofile_att_header_marker_t header,
    uint64_t id,
    uint64_t addr,
    uint64_t size
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_att_codeobj_load_marker(packets, handle, header, id, addr, size);
    } catch (hsa_status_t err) {
        ERR_LOGGING << err;
        return err;
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
    return HSA_STATUS_SUCCESS;
}

PUBLIC_API hsa_status_t
aqlprofile_att_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_att_data_callback_t callback,
    void* userdata
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_att_iterate_data(handle, callback, userdata);
    } catch (hsa_status_t err) {
        ERR_LOGGING << err;
        return err;
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API hsa_status_t aqlprofile_att_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_att_control_aql_packets_t* packets,
    aqlprofile_att_profile_t profile,
    aqlprofile_memory_alloc_callback_t alloc_cb,
    aqlprofile_memory_dealloc_callback_t dealloc_cb,
    aqlprofile_memory_copy_t copy_fn,
    void* userdata
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_att_create_packets(
            handle, packets, profile, alloc_cb, dealloc_cb, copy_fn, userdata);
    } catch (hsa_status_t err) {
        ERR_LOGGING << err;
        return err;
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
};

PUBLIC_API void aqlprofile_att_delete_packets(aqlprofile_handle_t handle)
{
    try {
        MemoryManager::DeleteManager(handle.handle);
    } catch (std::exception& e) {
        return;
    } catch (...) {
        return;
    }
}

}  // extern "C"
