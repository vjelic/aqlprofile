#include "core/aql_profile.hpp"
#include "core/include/aql_profile_v2.h"

#include <cstdint>
#include <future>
#include <map>
#include <string>
#include <vector>

#include "core/counter_dimensions.hpp"

#include "core/logger.h"
#include "core/pm4_factory.h"
#include "pm4/cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/spm_builder.h"
#include "pm4/sqtt_builder.h"

#include "core/commandbuffermgr.hpp"
#include "memorymanager.hpp"

#define PUBLIC_API __attribute__((visibility("default")))
#define CONSTRUCTOR_API __attribute__((constructor))
#define DESTRUCTOR_API __attribute__((destructor))
#define ERR_CHECK(cond, err, msg) \
    {                               \
        if (cond) {                   \
            ERR_LOGGING << msg;         \
            return err;                 \
        }                             \
    }


#define HSA_TRY_WRAP try{
#define HSA_CATCH_WRAP } catch(std::exception& e) { return HSA_STATUS_ERROR; }

std::vector<std::string> EventDimension::dimension_list;
std::unordered_map<std::string, size_t> EventDimension::dimension_table;

namespace aql_profile_v2 {
// Command buffer partitioning manager
// Supports Pre/Post commands partitioning
// and prefix control partition

using ::aql_profile::Pm4Factory;
using aql_profile::event_exception;
using aql_profile::event_t;

static inline pm4_builder::counters_vector CountersVec(
    aqlprofile_pmc_profile_t profile,
    const Pm4Factory* pm4_factory
) {
    pm4_builder::counters_vector vec;
    std::map<block_des_t, uint32_t, lt_block_des> index_map;
    for (const auto* p = profile.events; p < profile.events + profile.event_count; p++)
    {
        const GpuBlockInfo* block_info = pm4_factory->GetBlockInfo(p->block_name);
        const block_des_t block_des = {block_info->id, p->block_index};
        // Counting counter register index per block
        const auto ret = index_map.insert({block_des, 0});
        uint32_t& reg_index = ret.first->second;

        if (reg_index >= block_info->counter_count) {
            throw std::string("Event is out of block counter registers number limit");
        }

        vec.push_back({p->event_id, reg_index, block_des, block_info});

        ++reg_index;
    }

    if (pm4_factory->IsGFX10() && (vec.get_attr() & CounterBlockSqAttr) != 0 &&
            (vec.get_attr() & CounterBlockGRBMAttr) == 0) {
        event_t grbm_event{
                .block_name = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GRBM, .block_index = 0, .counter_id = 0};
        const GpuBlockInfo* block_info = pm4_factory->GetBlockInfo(&grbm_event);
        if (block_info == nullptr) return vec;
        const block_des_t block_des = {block_info->id, 0};
        const auto ret = index_map.insert({block_des, 0});
        uint32_t& reg_index = ret.first->second;
        vec.push_back({0, reg_index, block_des, block_info});
        reg_index++;
    }
    return vec;
}

static inline bool IsEventMatch(const event_t& event1, const event_t& event2) {
    return (event1.block_name == event2.block_name) && (event1.block_index == event2.block_index) &&
         (event1.counter_id == event2.counter_id);
}

// Method for iterating the events output data
hsa_status_t
_internal_aqlprofile_pmc_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_pmc_data_callback_t callback,
    void* userdata
) {
    hsa_status_t status = HSA_STATUS_SUCCESS;

    auto memorymgr = MemoryManager::GetManager(handle.handle);

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(memorymgr->GetAgent());
    const uint32_t xcc_num = pm4_factory->GetXccNumber();

    uint64_t* samples = reinterpret_cast<uint64_t*>(memorymgr->GetOutputBuf());
    uint64_t* buffer_end_location = samples + memorymgr->GetOutputBufSize()/sizeof(uint64_t);
    auto& events = memorymgr->GetEvents();

    size_t umc_sample_id = 0;
    if (xcc_num > 1) for (auto& event : events)
    {
        if (samples >= buffer_end_location)
            return HSA_STATUS_ERROR;

        if (!(pm4_factory->GetBlockInfo(event.block_name)->attr & CounterBlockUmcAttr))
            continue;

#if DEBUG_TRACE == 2
        printf("DATA: sample index(%u) id(%u) bloc id(%u) index(%u) counter id(%u) res(%lu)\n",
                sample_index, sample_id, p->block_name, p->block_index, p->counter_id, *samples);
#endif

        status = callback(event, event.block_index, *samples, userdata);
        if (status == HSA_STATUS_INFO_BREAK) {
            status = HSA_STATUS_SUCCESS;
            break;
        }
        if (status != HSA_STATUS_SUCCESS)
            break;
        samples ++;
        umc_sample_id ++;
    }

    size_t xcc_sample_count = 0;
    for (uint32_t xcc_index = 0; xcc_index < xcc_num; xcc_index++) for (auto& event : events)
    {
        if (samples >= buffer_end_location)
            return HSA_STATUS_ERROR;

        if (pm4_factory->GetBlockInfo(event.block_name)->attr & CounterBlockUmcAttr)
            continue;

        // non-MI300A-AID counter event.
        uint32_t block_samples_count = pm4_factory->GetNumEvents(event.block_name);
        for (uint32_t blk = 0; blk < block_samples_count; ++blk)
        {
#if DEBUG_TRACE == 2
              printf("DATA: xcc(%u) blk(%u) bloc id(%u) index(%u) counter id(%u) res(%lu)\n",
                  xcc_index, blk, event.block_name, event.block_index, event.event_id, *samples);
#endif
            xcc_sample_count += xcc_index == 0;
            size_t xcc_sample_id = xcc_sample_count * xcc_index + blk;
            status = callback(event, xcc_sample_id, *samples, userdata);
            if (status == HSA_STATUS_INFO_BREAK) {
              status = HSA_STATUS_SUCCESS;
              break;
            }
            if (status != HSA_STATUS_SUCCESS)
              break;
            samples ++;
        }
    }

    return status;
}

hsa_status_t _internal_aqlprofile_pmc_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_pmc_aql_packets_t* packets,
    aqlprofile_pmc_profile_t profile,
    aqlprofile_memory_alloc_callback_t alloc_cb,
    aqlprofile_memory_dealloc_callback_t dealloc_cb,
    void* userdata
) {
    pm4_builder::CmdBuffer commands;
    auto memorymgr = MemoryManager::CreateManager(
        profile.agent,
        alloc_cb,
        dealloc_cb,
        userdata
    );
    memorymgr->CopyEvents(profile.events, profile.event_count);

    pm4_builder::CmdBuffer read_cmd;
    pm4_builder::CmdBuffer start_cmd;
    pm4_builder::CmdBuffer stop_cmd;

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    const pm4_builder::counters_vector countersVec = CountersVec(profile, pm4_factory);

    pm4_builder::PmcBuilder* pmc_builder = pm4_factory->GetPmcBuilder();

    // Start outputbuf ptr
    size_t output_bytes = 0;
    for (auto& event : memorymgr->GetEvents())
        output_bytes += pm4_factory->GetBytesNeeded(event.block_name);
    memorymgr->CreateOutputBuf(output_bytes);
    // Generate read commands
    size_t data_size = pmc_builder->Read(&read_cmd, countersVec, memorymgr->GetOutputBuf());
    // Generate start commands
    pmc_builder->Start(&start_cmd, countersVec);
    // Generate stop commands
    pmc_builder->Stop(&stop_cmd, countersVec);

    ERR_CHECK(data_size == 0, HSA_STATUS_ERROR, "PMC Builder Stop(): data size set to zero");
    if (memorymgr->GetOutputBufSize() < data_size)
        return HSA_STATUS_ERROR_OUT_OF_RESOURCES;

    // Copy generated commands
    size_t start_size = aql_profile::CommandBufferMgr::Align(start_cmd.Size());
    size_t stop_size = aql_profile::CommandBufferMgr::Align(stop_cmd.Size());
    size_t read_size = aql_profile::CommandBufferMgr::Align(read_cmd.Size());
    memorymgr->CreateCmdBuf(start_size+stop_size+read_size);

    handle->handle = memorymgr->GetHandler();
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    uint8_t* cmdbuf = reinterpret_cast<uint8_t*>(memorymgr->GetCmdBuf());

    memcpy(cmdbuf, read_cmd.Data(), read_cmd.Size());
    aql_profile::PopulateAql(cmdbuf, read_cmd.Size(), cmd_writer, &packets->read_packet);
    cmdbuf += read_size;
    memcpy(cmdbuf, start_cmd.Data(), start_cmd.Size());
    aql_profile::PopulateAql(cmdbuf, start_cmd.Size(), cmd_writer, &packets->start_packet);
    cmdbuf += start_size;
    memcpy(cmdbuf, stop_cmd.Data(), stop_cmd.Size());
    aql_profile::PopulateAql(cmdbuf, stop_cmd.Size(), cmd_writer, &packets->stop_packet);

    return HSA_STATUS_SUCCESS;
}

}  // namespace aql_profile

extern "C" {

PUBLIC_API hsa_status_t aqlprofile_pmc_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_pmc_aql_packets_t* packets,
    aqlprofile_pmc_profile_t profile,
    aqlprofile_memory_alloc_callback_t alloc_cb,
    aqlprofile_memory_dealloc_callback_t dealloc_cb,
    void* userdata
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_pmc_create_packets(
            handle, packets, profile, alloc_cb, dealloc_cb, userdata
        );
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API void aqlprofile_pmc_delete_packets(aqlprofile_handle_t handle)
{
    try {
        MemoryManager::DeleteManager(handle.handle);
    } catch (std::exception& e) {
        return;
    } catch (...) {
        return;
    }
}

PUBLIC_API hsa_status_t
aqlprofile_pmc_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_pmc_data_callback_t callback,
    void* userdata
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_pmc_iterate_data(handle, callback, userdata);
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API hsa_status_t aqlprofile_iterate_event_ids(
    aqlprofile_eventname_callback_t callback,
    void* user_data
) {
    try {
        EventDimension::init();
        for (auto& [name, id] : EventDimension::dimension_table) {
            if (auto ret = callback(id, name.c_str(), user_data); ret != HSA_STATUS_SUCCESS) {
                return ret;
            }
        }
    } catch(...) {
        return HSA_STATUS_ERROR;
    }
    return HSA_STATUS_SUCCESS;
}

PUBLIC_API hsa_status_t aqlprofile_iterate_event_coord(
  hsa_agent_t agent,
  aqlprofile_pmc_event_t event,
  uint64_t counter_id,
  aqlprofile_coordinate_callback_t callback,
  void* userdata
) {
    try
    {
        const EventAttribDimension& attrib = EventAttribDimension::get(agent, event);

        if (!attrib.get_num()) return HSA_STATUS_ERROR;

        std::vector<uint8_t> coord;
        coord.resize(attrib.get_num());
        attrib.get_coordinates(coord.data(), counter_id & (1ul<<32));

        for (size_t i=0; i<attrib.get_num(); i++)
        {
            EventDimension dim = attrib.get_dim(i);
            callback(i, dim.id, dim.extent, coord[i], dim.name.data(), userdata);
        }
    }
    catch(...) {
        return HSA_STATUS_ERROR;
    }
    return HSA_STATUS_SUCCESS;
}

}  // extern "C"
