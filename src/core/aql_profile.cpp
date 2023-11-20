#include "core/aql_profile.h"

#include <cstdint>
#include <future>
#include <map>
#include <string>
#include <vector>

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

// Getting SPM data using driver API
namespace spm_kfd_namespace {
hsa_status_t spm_iterate_data(const hsa_ven_amd_aqlprofile_profile_t* profile,
                              hsa_ven_amd_aqlprofile_data_callback_t callback, void* data);
}

// PC sampling callback data
struct pcsmp_callback_data_t {
  const char* kernel_name;  // sampled kernel name
  void* data_buffer;        // host buffer for tracing data
  uint64_t id;              // sample id
  uint64_t cycle;           // sample cycle
  uint64_t pc;              // sample PC
};

std::atomic<int> ATT_TARGET_CU{0};

namespace aql_profile {
// Command buffer partitioning manager
// Supports Pre/Post commands partitioning
// and prefix control partition

static inline pm4_builder::counters_vector CountersVec(const profile_t* profile,
                                                       const Pm4Factory* pm4_factory) {
  pm4_builder::counters_vector vec;
  std::map<block_des_t, uint32_t, lt_block_des> index_map;
  for (const hsa_ven_amd_aqlprofile_event_t* p = profile->events;
       p < profile->events + profile->event_count; ++p) {
    const GpuBlockInfo* block_info = pm4_factory->GetBlockInfo(p);
    const block_des_t block_des = {pm4_factory->GetBlockInfo(p)->id, p->block_index};
    // Counting counter register index per block
    const auto ret = index_map.insert({block_des, 0});
    uint32_t& reg_index = ret.first->second;

    if (reg_index >= block_info->counter_count) {
      throw event_exception("Event is out of block counter registers number limit, ", *p);
    }

    vec.push_back({p->counter_id, reg_index, block_des, block_info});

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

hsa_status_t DefaultPmcdataCallback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                    hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                    void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  hsa_ven_amd_aqlprofile_info_data_t* passed_data =
      reinterpret_cast<hsa_ven_amd_aqlprofile_info_data_t*>(callback_data);

  if (info_type == HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA) {
    if (IsEventMatch(info_data->pmc_data.event, passed_data->pmc_data.event)) {
      if (passed_data->sample_id == UINT32_MAX) {
        passed_data->pmc_data.result += info_data->pmc_data.result;
      } else if (passed_data->sample_id == info_data->sample_id) {
        passed_data->pmc_data.result = info_data->pmc_data.result;
        status = HSA_STATUS_INFO_BREAK;
      }
    }
  }

  return status;
}

hsa_status_t DefaultTracedataCallback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                      hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                      void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  hsa_ven_amd_aqlprofile_info_data_t* passed_data =
      reinterpret_cast<hsa_ven_amd_aqlprofile_info_data_t*>(callback_data);

  if (info_type == HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA) {
    if (info_data->sample_id == passed_data->sample_id) {
      passed_data->trace_data = info_data->trace_data;
      status = HSA_STATUS_INFO_BREAK;
    }
  }

  return status;
}

Logger::mutex_t Logger::mutex_;
Logger* Logger::instance_ = NULL;
bool Pm4Factory::concurrent_create_mode_ = false;
bool Pm4Factory::spm_kfd_mode_ = false;
Pm4Factory::mutex_t Pm4Factory::mutex_;
Pm4Factory::instances_t* Pm4Factory::instances_ = NULL;
bool read_api_enabled = true;

CONSTRUCTOR_API void constructor() {
  const char* read_api_enabled_str = getenv("AQLPROFILE_READ_API");
  if (read_api_enabled_str != NULL) {
    if (atoi(read_api_enabled_str) == 0) read_api_enabled = false;
  }
}

DESTRUCTOR_API void destructor() {
  Logger::Destroy();
  Pm4Factory::Destroy();
}

}  // namespace aql_profile

extern "C" {

// Return library major/minor version
PUBLIC_API uint32_t hsa_ven_amd_aqlprofile_version_major() { return HSA_AQLPROFILE_VERSION_MAJOR; }
PUBLIC_API uint32_t hsa_ven_amd_aqlprofile_version_minor() { return HSA_AQLPROFILE_VERSION_MINOR; }

// Returns the last error message
PUBLIC_API hsa_status_t hsa_ven_amd_aqlprofile_error_string(const char** str) {
  *str = aql_profile::Logger::LastMessage().c_str();
  return HSA_STATUS_SUCCESS;
}

// Check if event is valid for the specific GPU
PUBLIC_API hsa_status_t hsa_ven_amd_aqlprofile_validate_event(
    hsa_agent_t agent, const hsa_ven_amd_aqlprofile_event_t* event, bool* result) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  *result = false;

  try {
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(agent);
    if (pm4_factory->GetBlockInfo(event) != NULL) *result = true;
  } catch (aql_profile::event_exception& e) {
    INFO_LOGGING << e.what();
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    status = HSA_STATUS_ERROR;
  }

  return status;
}

// Method to populate the provided AQL packet with profiling start commands
PUBLIC_API hsa_status_t hsa_ven_amd_aqlprofile_start(hsa_ven_amd_aqlprofile_profile_t* profile,
                                                     aql_profile::packet_t* aql_start_packet) {
  try {
    pm4_builder::CmdBuffer commands;
    aql_profile::CommandBufferMgr cmd_buffer_mgr(profile->command_buffer.ptr, UINT_MAX);

    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
    const bool is_concurrent = pm4_factory->IsConcurrent();
    const pm4_builder::counters_vector countersVec = CountersVec(profile, pm4_factory);

    if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_PMC) {
      pm4_builder::PmcBuilder* pmc_builder = pm4_factory->GetPmcBuilder();

      if (aql_profile::read_api_enabled) {
        // Generate read commands
        pmc_builder->Read(&commands, countersVec, profile->output_buffer.ptr);
        cmd_buffer_mgr.SetRdSize(commands.Size());

        // Copy generated read commands
        if (profile->command_buffer.ptr != NULL) {
          const aql_profile::descriptor_t rd_descr = cmd_buffer_mgr.GetRdDescr();
          memcpy(rd_descr.ptr, commands.Data(), commands.Size());
          commands.Clear();
        }

        if (is_concurrent) {
          // Generate read commands
          pmc_builder->Read(
              &commands, countersVec,
              (char*)(profile->output_buffer.ptr) + (profile->output_buffer.size / 2));
          cmd_buffer_mgr.SetRd2Size(commands.Size());

          // Copy generated read commands
          if (profile->command_buffer.ptr != NULL) {
            const aql_profile::descriptor_t rd_descr = cmd_buffer_mgr.GetRdDescr();
            memcpy((char*)rd_descr.ptr + (rd_descr.size / 2), commands.Data(), commands.Size());
            commands.Clear();
          }
        }
      }

      // Generate start commands
      pmc_builder->Start(&commands, countersVec);
      cmd_buffer_mgr.SetPreSize(commands.Size());

      // Generate stop commands
      const uint32_t data_size =
          pmc_builder->Stop(&commands, countersVec, profile->output_buffer.ptr);
      ERR_CHECK(data_size == 0, HSA_STATUS_ERROR, "PMC Builder Stop(): data size set to zero");
      if (profile->output_buffer.size < data_size) {
        profile->output_buffer.size = data_size;
        if (profile->output_buffer.ptr != NULL) {
          ERR_LOGGING << "Bad profile output_buffer size (" << profile->output_buffer.size
                      << "), required size(" << data_size << ")";
          return HSA_STATUS_ERROR_INVALID_ARGUMENT;
        }
      }
      assert(data_size <= profile->output_buffer.size);

    } else if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE) {
      pm4_builder::TraceConfig trace_config{};
      memset((char*)&trace_config, 0, sizeof(pm4_builder::TraceConfig));
      trace_config.vmIdMask = 0xF;
      trace_config.simd_sel = 0xF;
      trace_config.perfMASK = (1 << 16) - 1;
      trace_config.se_mask = 0x11111111;

      const uint64_t se_number_total = pm4_factory->GetShaderEnginesNumber();

      if (profile->parameters) {
        for (const hsa_ven_amd_aqlprofile_parameter_t* p = profile->parameters;
             p < (profile->parameters + profile->parameter_count); ++p) {
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
              ATT_TARGET_CU.store(p->value);
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
              ATT_TARGET_CU.store(trace_config.targetCu);
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
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER_MASK:
              trace_config.perfMASK = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_PERFCOUNTER_CTRL:
              trace_config.perfCTRL = (p->value & 0x31) | 0x7F;
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
        }
      }

      const uint32_t tnumber = se_number_total;

      const uint32_t control_size =
          pm4_builder::TT_STATUS_IDX_MAX * sizeof(pm4_builder::ControlType) * tnumber;
      char* prefix_ptr = cmd_buffer_mgr.AddPrefix(control_size + sizeof(uint32_t));
      pm4_builder::ControlType* const control_ptr =
          reinterpret_cast<pm4_builder::ControlType*>(prefix_ptr + sizeof(uint32_t));

      trace_config.spm_sq_32bit_mode = true;
      trace_config.se_number_total = se_number_total;
      trace_config.sampleRate = 10000;  // tbd
      trace_config.control_buffer_ptr = control_ptr;
      trace_config.data_buffer_ptr = profile->output_buffer.ptr;
      trace_config.data_buffer_size = profile->output_buffer.size;

      if (prefix_ptr != NULL) {
        *reinterpret_cast<uint32_t*>(prefix_ptr) = tnumber;
        uint32_t i = 0;
        uint32_t se_per_xcc = pm4_factory->GetShaderEnginesNumber() / pm4_factory->GetXccNumber();
        for (uint32_t t = 0; t < se_number_total; t++) {
          if (true) {
            const uint32_t se_id_ind =
                (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_ID;
            control_ptr[se_id_ind] = t % se_per_xcc;
            i += 1;
          }
        }
      }

      if (countersVec.size() == 0) {
        pm4_builder::SqttBuilder* sqtt_builder = pm4_factory->GetSqttBuilder();

        // Generate start commands
        sqtt_builder->Begin(&commands, &trace_config);
        cmd_buffer_mgr.SetPreSize(commands.Size());
        // Generate stop commands
        sqtt_builder->End(&commands, &trace_config);
      } else {
        pm4_builder::SpmBuilder* spm_builder = pm4_factory->GetSpmBuilder();

        trace_config.spm_sq_32bit_mode = true;
        trace_config.spm_kfd_mode = true;
        trace_config.sampleRate = 625;
        trace_config.mi100 = (pm4_factory->GetGpuId() == aql_profile::MI100_GPU_ID);

        // Generate start commands
        spm_builder->Begin(&commands, &trace_config, countersVec);
        cmd_buffer_mgr.SetPreSize(commands.Size());
        // Generate stop commands
        spm_builder->End(&commands, &trace_config);
      }
    } else {
      ERR_LOGGING << "Bad profile type (" << profile->type << ")";
      return HSA_STATUS_ERROR_INVALID_ARGUMENT;
    }

    cmd_buffer_mgr.Finalize(commands.Size());
    const uint32_t cmd_size = cmd_buffer_mgr.GetSize();
    if (profile->command_buffer.size < cmd_size) {
      profile->command_buffer.size = cmd_size;
      if (profile->command_buffer.ptr != NULL) {
        ERR_LOGGING << "Bad profile command_buffer size (" << profile->command_buffer.size
                    << "), required size(" << cmd_size << ")";
        return HSA_STATUS_ERROR_INVALID_ARGUMENT;
      }
    }
    assert(cmd_size <= profile->command_buffer.size);

    if (profile->command_buffer.ptr != NULL) {
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
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    return HSA_STATUS_ERROR;
  }

  return HSA_STATUS_SUCCESS;
}

// Method to populate the provided AQL packet with profiling stop commands
PUBLIC_API hsa_status_t hsa_ven_amd_aqlprofile_stop(const hsa_ven_amd_aqlprofile_profile_t* profile,
                                                    aql_profile::packet_t* aql_stop_packet) {
  try {
    // Populate stop aql packet
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
    pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
    aql_profile::CommandBufferMgr cmd_buffer_mgr(profile);
    const aql_profile::descriptor_t post_descr = cmd_buffer_mgr.GetPostDescr();
    aql_profile::PopulateAql(post_descr.ptr, post_descr.size, cmd_writer, aql_stop_packet);
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    return HSA_STATUS_ERROR;
  }

  return HSA_STATUS_SUCCESS;
}

// Method to populate the provided AQL packet with profiling read commands
PUBLIC_API hsa_status_t hsa_ven_amd_aqlprofile_read(const hsa_ven_amd_aqlprofile_profile_t* profile,
                                                    aql_profile::packet_t* aql_read_packet) {
  if (aql_profile::read_api_enabled) {
    try {
      // Populate read aql packet
      aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
      const bool is_concurrent = pm4_factory->IsConcurrent();
      pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
      aql_profile::CommandBufferMgr cmd_buffer_mgr(profile);

      const aql_profile::descriptor_t rd_descr =
          (is_concurrent == false) ? cmd_buffer_mgr.GetRdDescr() : cmd_buffer_mgr.FetchRdDescr();
      aql_profile::PopulateAql(rd_descr.ptr, rd_descr.size, cmd_writer, aql_read_packet);
    } catch (std::exception& e) {
      ERR_LOGGING << e.what();
      return HSA_STATUS_ERROR;
    }
  } else {
    ERR_LOGGING << "Read API disabled";
    return HSA_STATUS_ERROR;
  }
  return HSA_STATUS_SUCCESS;
}

// Legacy devices, converting of the profiling AQL packet to PM4 packet blob
PUBLIC_API hsa_status_t
hsa_ven_amd_aqlprofile_legacy_get_pm4(const aql_profile::packet_t* aql_packet, void* data) {
  return HSA_STATUS_ERROR;
}

// Method for getting the profile info
PUBLIC_API hsa_status_t
hsa_ven_amd_aqlprofile_get_info(const hsa_ven_amd_aqlprofile_profile_t* profile,
                                hsa_ven_amd_aqlprofile_info_type_t attribute, void* value) {
  hsa_status_t status = HSA_STATUS_SUCCESS;

  const uint32_t attr_op = (uint32_t)attribute;
  const uint32_t begin_op = (uint32_t)HSA_VEN_AMD_AQLPROFILE_INFO_ENABLE_CMD;
  if (attr_op >= begin_op) attribute = (hsa_ven_amd_aqlprofile_info_type_t)begin_op;

  if (profile == NULL) {
    ERR_LOGGING << "NULL argument 'profile'";
    return HSA_STATUS_ERROR;
  }
  if (attribute != HSA_VEN_AMD_AQLPROFILE_INFO_ENABLE_CMD) {
    if (value == NULL) {
      ERR_LOGGING << "NULL argument 'value'";
      return HSA_STATUS_ERROR;
    }
  }

  try {
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
    switch (attribute) {
      case HSA_VEN_AMD_AQLPROFILE_INFO_COMMAND_BUFFER_SIZE:
        *(uint32_t*)value = 0x1000;  // a current approximation as 4K is big enough
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA_SIZE:
        *(uint32_t*)value = 0x1000;  // a current approximation as 4K is big enough
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA:
        reinterpret_cast<hsa_ven_amd_aqlprofile_info_data_t*>(value)->pmc_data.result = 0;
        status = hsa_ven_amd_aqlprofile_iterate_data(profile, aql_profile::DefaultPmcdataCallback,
                                                     value);
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA:
        status = hsa_ven_amd_aqlprofile_iterate_data(profile, aql_profile::DefaultTracedataCallback,
                                                     value);
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_BLOCK_COUNTERS:
        *reinterpret_cast<uint32_t*>(value) =
            pm4_factory->GetBlockInfo(&(profile->events[0]))->counter_count;
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_BLOCK_ID: {
        hsa_ven_amd_aqlprofile_id_query_t* query =
            reinterpret_cast<hsa_ven_amd_aqlprofile_id_query_t*>(value);
        const uint32_t block = pm4_factory->FindBlock(query->name);
        const GpuBlockInfo* info = pm4_factory->GetBlockInfo(block);
        status = (info == NULL) ? HSA_STATUS_ERROR : HSA_STATUS_SUCCESS;
        if (status == HSA_STATUS_SUCCESS) {
          query->id = block;
          query->instance_count = info->instance_count;
        }
        break;
      }
      case HSA_VEN_AMD_AQLPROFILE_INFO_ENABLE_CMD: {
        aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
        pm4_builder::PmcBuilder* pmc_builder = pm4_factory->GetPmcBuilder();
        pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
        pm4_builder::CmdBuffer commands;

        const uint32_t op = attr_op - begin_op;
        switch (op) {
          case 0:
            pmc_builder->Enable(&commands);
            break;
          case 1:
            pmc_builder->Disable(&commands);
            break;
          case 2:
            pmc_builder->WaitIdle(&commands);
            break;
          default:
            ERR_LOGGING << "get_info, not supported op (" << op << ")";
            status = HSA_STATUS_ERROR;
        }

        if (profile->command_buffer.ptr == NULL) {
          const_cast<hsa_ven_amd_aqlprofile_profile_t*>(profile)->command_buffer.size =
              commands.Size();
          break;
        }

        if (profile->command_buffer.size != commands.Size()) {
          ERR_LOGGING << "get_info, wrong profile cmd size";
          status = HSA_STATUS_ERROR;
          break;
        }
        if (value == NULL) {
          ERR_LOGGING << "NULL argument 'value'";
          status = HSA_STATUS_ERROR;
          break;
        }

        memcpy(profile->command_buffer.ptr, commands.Data(), profile->command_buffer.size);
        aql_profile::PopulateAql(profile->command_buffer.ptr, profile->command_buffer.size,
                                 cmd_writer, reinterpret_cast<aql_profile::packet_t*>(value));

        break;
      }
      default:
        status = HSA_STATUS_ERROR_INVALID_ARGUMENT;
        ERR_LOGGING << "Invalid attribute (" << attribute << ")";
    }
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    return HSA_STATUS_ERROR;
  }

  return status;
}

// Method for iterating the events output data
PUBLIC_API hsa_status_t
hsa_ven_amd_aqlprofile_iterate_data(const hsa_ven_amd_aqlprofile_profile_t* profile,
                                    hsa_ven_amd_aqlprofile_data_callback_t callback, void* data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;

  try {
    aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
    const bool is_concurrent = pm4_factory->IsConcurrent();
    const uint32_t xcc_num = pm4_factory->GetXccNumber();
    const uint32_t se_number = pm4_factory->GetShaderEnginesNumber() / xcc_num;

    if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_PMC) {
      uint64_t* samples = reinterpret_cast<uint64_t*>(profile->output_buffer.ptr);

      uint32_t umc_sample_count = 0;
      if (xcc_num > 1) {
        // We count the UMC samples - per sample per event since we are exposing all 128 UMCCHs
        for (const hsa_ven_amd_aqlprofile_event_t* p = profile->events;
            p < profile->events + profile->event_count; ++p) {
          if (p->block_name == HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_UMC)
              ++ umc_sample_count;
        }
      }

      // per xcc sample count
      uint32_t xcc_sample_count = (profile->output_buffer.size - umc_sample_count *  pm4_builder::UMC_SAMPLE_BYTE_SIZE) /
        (sizeof(uint64_t) * xcc_num);

      for (uint32_t xcc_index = 0; xcc_index < xcc_num; xcc_index++) {
        const uint32_t sample_count = (xcc_index == 0) ? (umc_sample_count + xcc_sample_count) : xcc_sample_count;
        uint32_t sample_index = 0;
        uint32_t sample_location = 0;
        for (const hsa_ven_amd_aqlprofile_event_t* p = profile->events;
             p < profile->events + profile->event_count; ++p) {
          if ((xcc_num > 1) && (pm4_factory->GetBlockInfo(p)->attr & CounterBlockUmcAttr)) {
            // MI300A-AID counter event
            if (xcc_index == 0) {
              // Process an MI300 UMC event for XCC 0 ONLY
              auto sample_id = p->block_index; // sample id is the event block_index or the UMCCH id
              hsa_ven_amd_aqlprofile_info_data_t sample_info;
              sample_info.sample_id = sample_id;
              sample_info.pmc_data.event = *p;
              sample_info.pmc_data.result = samples[sample_location];
#if DEBUG_TRACE == 2
              printf(
                     "DATA: sample index(%u) loc(%u) id(%u) bloc id(%u) index(%u) counter id(%u) "
                     "res(%lu)\n",
                     sample_index, sample_location, sample_id, p->block_name, p->block_index, p->counter_id,
                     samples[sample_location]);
#endif
              ++ sample_location;

              status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA, &sample_info, data);
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
          } else {
            // non-MI300A-AID counter event
            // A perfcounter data sample per ShaderEngine
            const uint32_t block_samples_count =
              (pm4_factory->GetBlockInfo(p)->attr & CounterBlockSeAttr) ? se_number : 1;
            const bool IsSqCounter = bool(pm4_factory->GetBlockInfo(p)->attr & CounterBlockSqAttr);
            const uint32_t samples_per_sq = IsSqCounter ? pm4_factory->GetSQ_PMC_samples_per_SE() : 1;

            for (uint32_t i = 0; i < block_samples_count; ++i) {
              assert(sample_index < sample_count);
              if (sample_index >= sample_count) {
                ERR_LOGGING << "Bad sample index (" << sample_index << "/" << sample_count << ")";
                return HSA_STATUS_ERROR;
              }

              hsa_ven_amd_aqlprofile_info_data_t sample_info;
              sample_info.sample_id = i;
              sample_info.pmc_data.event = *p;
              uint64_t val = 0;
              for (int wgp = 0; wgp < samples_per_sq; wgp++) {
                if (sample_location >= sample_count) break;
                val += samples[sample_location];
#if DEBUG_TRACE == 2
                printf(
                       "DATA: sample index(%u) loc(%u) id(%u) bloc id(%u) index(%u) counter id(%u) "
                       "res(%lu)\n",
                       sample_index, sample_location, i, p->block_name, p->block_index, p->counter_id,
                       samples[sample_location]);
#endif
                sample_location++;
              }

              if (is_concurrent) {
                uint64_t start_val = samples[sample_index + sample_count / 2];
                if (val < start_val) {
                  ERR_LOGGING << "Bad values (end=" << val << " < start=" << start_val
                              << ") of sample index (" << sample_index << ") bloc id ("
                              << p->block_index << ") counter id (" << p->counter_id << ")";
                  return HSA_STATUS_ERROR;
                }
                val -= start_val;
              }

              sample_info.pmc_data.result = val;
              status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA, &sample_info, data);
              if (status == HSA_STATUS_INFO_BREAK) {
                status = HSA_STATUS_SUCCESS;
                break;
              }
              if (status != HSA_STATUS_SUCCESS) {
                ERR_LOGGING << "PMC data callback error, sample_id(" << i << ") status(" << status
                            << ")";
                break;
              }
              ++sample_index;
            }
          }
        }
        samples += sample_count;
      }
    } else if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE) {
      uint32_t mode = 2;
      switch (profile->event_count) {
        case 0:
          mode = 0;
          break;
        case UINT32_MAX:
          const_cast<hsa_ven_amd_aqlprofile_profile_t*>(profile)->event_count = 0;
          mode = 1;
          break;
      }

      if (mode != 2) {  // SQTT trace data, or SQTT pc sampling
        pm4_builder::SqttBuilder* sqttbuilder = pm4_factory->GetSqttBuilder();
        // Control buffer was allocated as the CmdBuffer prefix partition
        aql_profile::CommandBufferMgr cmd_buffer_mgr(profile);
        const char* const prefix_ptr = cmd_buffer_mgr.GetPrefix1();
        const uint32_t tnumber = *reinterpret_cast<const uint32_t*>(prefix_ptr);
        const pm4_builder::ControlType* const control_ptr =
            reinterpret_cast<const pm4_builder::ControlType*>(prefix_ptr + sizeof(uint32_t));
        // Check if SQTT buffer was wrapped
        for (unsigned i = 0; i < tnumber; ++i) {
          const uint32_t status_ind =
              (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_STATUS;
          if (control_ptr[status_ind] & sqttbuilder->GetUTCErrorMask()) {
            ERR_LOGGING << "SQTT memory error received, SE(" << i << ")";
            status = HSA_STATUS_ERROR_EXCEPTION;
          } else if (control_ptr[status_ind] & sqttbuilder->GetBufferFullMask()) {
            ERR2_LOGGING << "SQTT data buffer full, SE(" << i << ")";
            if (status == HSA_STATUS_SUCCESS) status = HSA_STATUS_ERROR_OUT_OF_RESOURCES;
          }
        }

        // SQTT output buffer and capacity per ShaderEngine
        std::vector<std::future<hsa_ven_amd_aqlprofile_info_data_t>> sample_data_vector;

        // The samples sizes are returned in the control buffer
        for (uint64_t se_index = 0; se_index < tnumber; se_index++)
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

          if (pm4_factory->GetGpuId() == aql_profile::GFX11_GPU_ID) {
            sample_size = sample_size - reinterpret_cast<uint64_t>(sample_ptr);
            sample_size &= (1ull << 29) - 1;
          }

          if (sample_size >= sample_capacity) {
            ERR_LOGGING << "SQTT data out of bounds, sample_id(" << se_index << ") size(" << sample_size
                        << "/" << sample_capacity << ")";
            sample_size = sample_capacity;
            if (status == HSA_STATUS_SUCCESS) status = HSA_STATUS_ERROR_OUT_OF_RESOURCES;
          }
          hsa_status_t call_status;
          if (mode == 0)
          {  // SQTT trace
            if (bMaskedIn)
            {
              sample_data_vector.push_back(std::async(
                  std::launch::async,
                  aql_profile::aqlprofile_sqttfilter_iterate_data,
                  sample_ptr,
                  sample_capacity,
                  sample_size,
                  se_index,
                  ATT_TARGET_CU.load()
              ));
            }
          } else {  // PC sampling
            pcsmp_callback_data_t* pcsmp_data = reinterpret_cast<pcsmp_callback_data_t*>(data);
            pcsmp_data->id = se_index;
            pcsmp_data->cycle = 333;
            pcsmp_data->pc = 0x333;
            call_status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA, NULL, data);
          }
        }
        for (auto& future : sample_data_vector) {
          auto sample_info = future.get();
          status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA, &sample_info, data);
          if (status != HSA_STATUS_SUCCESS) break;
        }
      } else {  // SPM trace data
        if (pm4_factory->SpmKfdMode() == false) {
          const uint32_t tnumber = 1;
          void* sample_ptr = profile->output_buffer.ptr;
          const uint32_t sample_size = profile->output_buffer.size;
          const uint32_t sample_capacity = (profile->output_buffer.size / tnumber);

          for (unsigned i = 0; i < tnumber; ++i) {
            hsa_ven_amd_aqlprofile_info_data_t sample_info;
            sample_info.sample_id = i;
            sample_info.trace_data.ptr = sample_ptr;
            sample_info.trace_data.size = sample_size;
            status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA, &sample_info, data);
            if (status == HSA_STATUS_INFO_BREAK) {
              status = HSA_STATUS_SUCCESS;
              break;
            }
            if (status != HSA_STATUS_SUCCESS) {
              ERR_LOGGING << "SQTT data callback error, sample_id(" << i << ") status(" << status
                          << ")";
              break;
            }
            sample_ptr = reinterpret_cast<char*>(sample_ptr) + sample_capacity;
          }
        } else {
          status = spm_kfd_namespace::spm_iterate_data(profile, callback, data);
        }
      }
    } else {
      ERR_LOGGING << "Bad profile type (" << profile->type << ")";
      status = HSA_STATUS_ERROR_INVALID_ARGUMENT;
    }
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    return HSA_STATUS_ERROR;
  }

  return status;
}

}  // extern "C"
