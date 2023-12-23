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
    aqlprofile_pmc_profile_t profile,
    aqlprofile_pmc_data_callback_t callback,
    void* userdata
) {
    hsa_status_t status = HSA_STATUS_SUCCESS;

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    const uint32_t xcc_num = pm4_factory->GetXccNumber();
    const uint32_t se_number = pm4_factory->GetShaderEnginesNumber() / xcc_num;

    uint64_t* samples = reinterpret_cast<uint64_t*>(profile.output_buffer.ptr);

    uint32_t umc_sample_count = 0;
    if (xcc_num > 1)
    {
        // We count the UMC samples - per sample per event since we are exposing all 128 UMCCHs
        for (const auto* p = profile.events; p < profile.events + profile.event_count; p++)
            umc_sample_count += p->block_name == HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_UMC;
    }

    // per xcc sample count
    uint32_t umc_bytes = umc_sample_count * pm4_builder::UMC_SAMPLE_BYTE_SIZE;
    uint32_t xcc_sample_count = (profile.output_buffer.size - umc_bytes) / (sizeof(uint64_t) * xcc_num);

    for (uint32_t xcc_index = 0; xcc_index < xcc_num; xcc_index++)
    {
        const uint32_t sample_count = (xcc_index == 0) ? (umc_sample_count + xcc_sample_count) : xcc_sample_count;
        uint32_t sample_index = 0;

        for (const auto* p = profile.events; p < profile.events + profile.event_count; p++)
        {
            if ((xcc_num > 1) && (pm4_factory->GetBlockInfo(p->block_name)->attr & CounterBlockUmcAttr))
            {
                // MI300A-AID counter event
                if (xcc_index == 0)
                {
                    // Process an MI300 UMC event for XCC 0 ONLY
                    auto sample_id = p->block_index; // sample id is the event block_index or the UMCCH id
#if DEBUG_TRACE == 2
                    printf(
                                    "DATA: sample index(%u) id(%u) bloc id(%u) index(%u) counter id(%u) "
                                    "res(%lu)\n",
                                    sample_index, sample_id, p->block_name, p->block_index, p->counter_id,
                                    samples[sample_index]);
#endif

                    status = callback(*p, sample_id, samples[sample_index], userdata);
                    if (status == HSA_STATUS_INFO_BREAK) {
                        status = HSA_STATUS_SUCCESS;
                        break;
                    }
                    if (status != HSA_STATUS_SUCCESS) {
                        ERR_LOGGING << "PMC data callback error, sample_id(" << sample_id << ") status(" << status
                                                << ")";
                        break;
                    }
                    ++sample_index;
                }
            }
            else
            {
                // non-MI300A-AID counter event.
                uint32_t block_samples_count = 1;
                if (pm4_factory->GetBlockInfo(p->block_name)->attr & CounterBlockSeAttr)
                    block_samples_count *= se_number;
                if (pm4_factory->GetBlockInfo(p->block_name)->attr & CounterBlockSaAttr)
                    block_samples_count *= 2;
                if (pm4_factory->GetBlockInfo(p->block_name)->attr & CounterBlockSqAttr)
                    block_samples_count *= pm4_factory->GetNumWGPs();

                for (uint32_t blk = 0; blk < block_samples_count; ++blk)
                {
                    if (sample_index >= sample_count) {
                        ERR_LOGGING << "Bad sample index (" << sample_index << "/" << sample_count << ")";
                        return HSA_STATUS_ERROR;
                    }
                    assert(sample_index < sample_count);
#if DEBUG_TRACE == 2
                        printf(
                                "DATA: xcc(%u) sample index(%u) id(%u) bloc id(%u) index(%u) counter id(%u) "
                                "res(%lu)\n",
                                xcc_index, sample_index, blk, p->block_name, p->block_index, p->counter_id, samples[sample_index]);
#endif
                    size_t xcc_sample_id = sample_count * xcc_index + blk;
                    status = callback(*p, xcc_sample_id, samples[sample_index], userdata);
                    if (status == HSA_STATUS_INFO_BREAK) {
                        status = HSA_STATUS_SUCCESS;
                        break;
                    }
                    if (status != HSA_STATUS_SUCCESS) {
                        ERR_LOGGING << "PMC data callback error, sample_id(" << blk << ") status(" << status << ")";
                        break;
                    }
                    ++sample_index;
                }
            }
        }
        samples += sample_count;
    }

    return status;
}

hsa_status_t
_internal_aqlprofile_pmc_start(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_start_packet
) {
    pm4_builder::CmdBuffer commands;
    aql_profile::CommandBufferMgr cmd_buffer_mgr(profile.command_buffer.ptr, UINT_MAX);

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    const pm4_builder::counters_vector countersVec = CountersVec(profile, pm4_factory);

    pm4_builder::PmcBuilder* pmc_builder = pm4_factory->GetPmcBuilder();

    // Generate read commands
    pmc_builder->Read(&commands, countersVec, profile.output_buffer.ptr);
    cmd_buffer_mgr.SetRdSize(commands.Size());

    // Copy generated read commands
    if (profile.command_buffer.ptr != NULL) {
        const aql_profile::descriptor_t rd_descr = cmd_buffer_mgr.GetRdDescr();
        memcpy(rd_descr.ptr, commands.Data(), commands.Size());
        commands.Clear();
    }

    // Generate start commands
    pmc_builder->Start(&commands, countersVec);
    cmd_buffer_mgr.SetPreSize(commands.Size());

    // Generate stop commands
    const uint32_t data_size =
        pmc_builder->Stop(&commands, countersVec, profile.output_buffer.ptr);
    ERR_CHECK(data_size == 0, HSA_STATUS_ERROR, "PMC Builder Stop(): data size set to zero");
    if (profile.output_buffer.size < data_size) {
        profile.output_buffer.size = data_size;
        if (profile.output_buffer.ptr != NULL) {
            ERR_LOGGING << "Bad profile output_buffer size (" << profile.output_buffer.size
                        << "), required size(" << data_size << ")";
            return HSA_STATUS_ERROR_INVALID_ARGUMENT;
        }
    }
    assert(data_size <= profile.output_buffer.size);

    cmd_buffer_mgr.Finalize(commands.Size());
    const uint32_t cmd_size = cmd_buffer_mgr.GetSize();
    if (profile.command_buffer.size < cmd_size) {
        profile.command_buffer.size = cmd_size;
        if (profile.command_buffer.ptr != NULL) {
            ERR_LOGGING << "Bad profile command_buffer size (" << profile.command_buffer.size
                        << "), required size(" << cmd_size << ")";
            return HSA_STATUS_ERROR_INVALID_ARGUMENT;
        }
    }
    assert(cmd_size <= profile.command_buffer.size);

    if (profile.command_buffer.ptr != NULL) {
        // Copy generated commands
        const aql_profile::descriptor_t pre_descr = cmd_buffer_mgr.GetPreDescr();
        const aql_profile::descriptor_t post_descr = cmd_buffer_mgr.GetPostDescr();
        memcpy(pre_descr.ptr, commands.Data(), pre_descr.size);
        memcpy(post_descr.ptr, reinterpret_cast<const char*>(commands.Data()) + pre_descr.size,
                post_descr.size);
        // Populate start aql packet
        pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
        aql_profile::PopulateAql(pre_descr.ptr, pre_descr.size, cmd_writer, aql_start_packet);
    }

    return HSA_STATUS_SUCCESS;
}

hsa_status_t
_internal_aqlprofile_pmc_stop(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_stop_packet
) {
    // Populate stop aql packet
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    aql_profile::CommandBufferMgr cmd_buffer_mgr(profile.command_buffer);
    const aql_profile::descriptor_t post_descr = cmd_buffer_mgr.GetPostDescr();
    aql_profile::PopulateAql(post_descr.ptr, post_descr.size, cmd_writer, aql_stop_packet);
    return HSA_STATUS_SUCCESS;
}

// Method to populate the provided AQL packet with profiling read commands
hsa_status_t _internal_aqlprofile_read(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_read_packet
) {
    // Populate read aql packet
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile.agent);
    const bool is_concurrent = pm4_factory->IsConcurrent();
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    aql_profile::CommandBufferMgr cmd_buffer_mgr(profile.command_buffer);

    const aql_profile::descriptor_t rd_descr =
        (is_concurrent == false) ? cmd_buffer_mgr.GetRdDescr() : cmd_buffer_mgr.FetchRdDescr();
    aql_profile::PopulateAql(rd_descr.ptr, rd_descr.size, cmd_writer, aql_read_packet);
    return HSA_STATUS_SUCCESS;
}

}  // namespace aql_profile

extern "C" {

PUBLIC_API hsa_status_t aqlprofile_pmc_start(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_start_packet
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_pmc_start(profile, aql_start_packet);
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API hsa_status_t aqlprofile_pmc_stop(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_stop_packet
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_pmc_stop(profile, aql_stop_packet);
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API hsa_status_t aqlprofile_pmc_read(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_read_packet
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_read(profile, aql_read_packet);
    } catch (std::exception& e) {
        ERR_LOGGING << e.what();
        return HSA_STATUS_ERROR;
    } catch (...) {
        return HSA_STATUS_ERROR;
    }
}

PUBLIC_API hsa_status_t
aqlprofile_pmc_iterate_data(
    aqlprofile_pmc_profile_t profile,
    aqlprofile_pmc_data_callback_t callback,
    void* data
) {
    try {
        return aql_profile_v2::_internal_aqlprofile_pmc_iterate_data(profile, callback, data);
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
