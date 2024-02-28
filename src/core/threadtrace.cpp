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

#define THREAD_TRACE_PREFIX_SIZE 0x1000
#define DEFAULT_TRACE_BUFFER_SIZE (3<<26)

#define PUBLIC_API __attribute__((visibility("default")))

namespace aql_profile_v2
{

hsa_status_t _internal_aqlprofile_att_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_att_data_callback_t callback,
    void* userdata
) {
    hsa_status_t status = HSA_STATUS_SUCCESS;

    auto memorymgr = MemoryManager::GetManager(handle.handle);
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(memorymgr->GetAgent());

    pm4_builder::SqttBuilder* sqttbuilder = pm4_factory->GetSqttBuilder();

    auto* prefix_ptr = reinterpret_cast<const uint32_t*>(memorymgr->GetCmdBuf());
    const uint32_t se_number_total = *prefix_ptr;
    auto* control_ptr = reinterpret_cast<const pm4_builder::ControlType*>(prefix_ptr+1);

    // Check if SQTT buffer was wrapped
    for (unsigned i = 0; i < se_number_total; ++i)
    {
        uint32_t status_ind = (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_STATUS;
        if (control_ptr[status_ind] & sqttbuilder->GetUTCErrorMask()) {
            ERR_LOGGING << "SQTT memory error received, SE(" << i << ")";
            status = HSA_STATUS_ERROR_EXCEPTION;
        } else if (control_ptr[status_ind] & sqttbuilder->GetBufferFullMask()) {
            ERR2_LOGGING << "SQTT data buffer full, SE(" << i << ")";
            if (status == HSA_STATUS_SUCCESS) status = HSA_STATUS_ERROR_OUT_OF_RESOURCES;
        }
    }

    // The samples sizes are returned in the control buffer
    for (uint64_t se_index = 0; se_index < se_number_total; se_index++)
    {
        bool bMaskedIn = sqttbuilder->GetTargetCU(se_index) >= 0;
        uint64_t sample_capacity = sqttbuilder->GetCapacity(se_index);
        void* sample_ptr = reinterpret_cast<void*>(sqttbuilder->GetSEBaseAddr(se_index));
        uint32_t se_id_ind = (pm4_builder::TT_STATUS_IDX_MAX * se_index) + pm4_builder::TT_STATUS_IDX_ID;

        const uint32_t se_id = control_ptr[se_id_ind];
        // WPTR specifies the index in thread trace buffer where next token will be
        // written by hardware. The index is incremented by size of 32 bytes.
        uint32_t wptr_ind = (pm4_builder::TT_STATUS_IDX_MAX * se_index) + pm4_builder::TT_STATUS_IDX_WPTR;

        uint64_t sample_size = (control_ptr[wptr_ind] & sqttbuilder->GetWritePtrMask()) *
                                sqttbuilder->GetWritePtrBlk();

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
        if (bMaskedIn)
            callback(se_index, sample_ptr, sample_size, userdata);
    }

    return status;
}

hsa_status_t _internal_aqlprofile_att_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_att_control_aql_packets_t* packets,
    aqlprofile_att_profile_t profile,
    aqlprofile_memory_alloc_callback_t alloc_cb,
    aqlprofile_memory_dealloc_callback_t dealloc_cb,
    void* userdata
) {
    pm4_builder::CmdBuffer start_cmd;
    pm4_builder::CmdBuffer stop_cmd;

    auto memorymgr = MemoryManager::CreateManager(
        profile.agent,
        alloc_cb,
        dealloc_cb,
        userdata
    );

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    pm4_builder::TraceConfig trace_config{};

    memset((char*)&trace_config, 0, sizeof(pm4_builder::TraceConfig));
    trace_config.vmIdMask = 0xF;
    trace_config.simd_sel = 0xF;
    trace_config.perfMASK = (1ul << 32) - 1;
    trace_config.se_mask = 0x11111111;

    const uint64_t se_number_total = pm4_factory->GetShaderEnginesNumber();
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

    memorymgr->CreateOutputBuf(buffer_size);
    memorymgr->CreateTraceControlBuf(THREAD_TRACE_PREFIX_SIZE);

    const size_t control_size = pm4_builder::TT_STATUS_IDX_MAX * sizeof(pm4_builder::ControlType) * se_number_total;
    auto* prefix_ptr = reinterpret_cast<uint32_t*>(memorymgr->GetTraceControlBuf());
    *prefix_ptr = se_number_total;
    auto* control_ptr = reinterpret_cast<pm4_builder::ControlType*>(prefix_ptr+1);

    trace_config.se_number_total = se_number_total;
    trace_config.control_buffer_ptr = control_ptr;
    trace_config.data_buffer_ptr = memorymgr->GetOutputBuf();
    trace_config.data_buffer_size = memorymgr->GetOutputBufSize();

    uint32_t se_per_xcc = pm4_factory->GetShaderEnginesNumber() / pm4_factory->GetXccNumber();
    for (uint32_t t = 0; t < se_number_total; t++)
    {
        uint32_t se_id_ind = (pm4_builder::TT_STATUS_IDX_MAX * t) + pm4_builder::TT_STATUS_IDX_ID;
        control_ptr[se_id_ind] = t % se_per_xcc;
    }

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

    memcpy(cmdbuf, start_cmd.Data(), start_cmd.Size());
    aql_profile::PopulateAql(cmdbuf, start_cmd.Size(), cmd_writer, &packets->start_packet);
    cmdbuf += start_size;
    memcpy(cmdbuf, stop_cmd.Data(), stop_cmd.Size());
    aql_profile::PopulateAql(cmdbuf, stop_cmd.Size(), cmd_writer, &packets->stop_packet);

    return HSA_STATUS_SUCCESS;
}

} // namespace aql_profile_v2

extern "C" {

// Method to populate the provided AQL packet with ATT Markers
PUBLIC_API hsa_status_t
hsa_ven_amd_aqlprofile_att_marker(
    hsa_ven_amd_aqlprofile_profile_t* profile,
    aql_profile::packet_t* aql_marker_packet,
    uint32_t data,
    hsa_ven_amd_aqlprofile_att_marker_channel_t channel
) {
    assert(profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE);

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
    pm4_builder::SqttBuilder* sqtt_builder = pm4_factory->GetSqttBuilder();
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    pm4_builder::CmdBuffer commands;

    // Generate start commands
    auto status = sqtt_builder->InsertMarker(&commands, data, channel);
    if (status != HSA_STATUS_SUCCESS) return status;
    aql_profile::descriptor_t& cmdbuffer = profile->command_buffer;

    size_t cmd_size = cmdbuffer.size;
    cmdbuffer.size = commands.Size();

    if (cmdbuffer.ptr == NULL) return HSA_STATUS_SUCCESS;
    if (cmd_size < commands.Size()) return HSA_STATUS_ERROR_OUT_OF_RESOURCES;

    // Populate stop aql packet
    memcpy(cmdbuffer.ptr, commands.Data(), commands.Size());
    aql_profile::PopulateAql(cmdbuffer.ptr, commands.Size(), cmd_writer, aql_marker_packet);

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
    void* userdata
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_att_create_packets(
            handle, packets, profile, alloc_cb, dealloc_cb, userdata);
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
