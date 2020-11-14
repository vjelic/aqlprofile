#include "core/aql_profile.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "core/logger.h"
#include "core/pm4_factory.h"
#include "pm4/cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/spm_builder.h"
#include "pm4/sqtt_builder.h"

#define PUBLIC_API __attribute__((visibility("default")))
#define CONSTRUCTOR_API __attribute__((constructor))
#define DESTRUCTOR_API __attribute__((destructor))
#define ERR_CHECK(cond, err, msg)                                                                  \
  {                                                                                                \
    if (cond) {                                                                                    \
      ERR_LOGGING << msg;                                                                          \
      return err;                                                                                  \
    }                                                                                              \
  }

// Getting SPM data using driver API
extern hsa_status_t spm_iterate_data(const hsa_ven_amd_aqlprofile_profile_t* profile,
                                    hsa_ven_amd_aqlprofile_data_callback_t callback, void* data);

// PC sampling callback data
struct pcsmp_callback_data_t {
  const char* kernel_name;     // sampled kernel name
  void* data_buffer;           // host buffer for tracing data
  uint64_t id;                 // sample id
  uint64_t cycle;              // sample cycle
  uint64_t pc;                 // sample PC
};

namespace aql_profile {

// Command buffer partitioning manager
// Supports Pre/Post commands partitioning
// and prefix control partition
class CommandBufferMgr {
 public:
  struct info_t {
    uint32_t prefix_size;
    uint32_t rdcmds_size;
    uint32_t rd2cmds_size;
    uint32_t is_rd_fetch2;
    uint32_t precmds_size;
    uint32_t postcmds_size;
  };

  CommandBufferMgr(void* ptr, const uint32_t& size) { Init(descriptor_t{ptr, size}, false); }
  explicit CommandBufferMgr(const profile_t* profile) { Init(profile->command_buffer, true); }

  char* GetPrefix() { return reinterpret_cast<char*>(buffer_.ptr); }
  char* GetPrefix1() { return reinterpret_cast<char*>(buffer_.ptr) + sizeof(info_t); }
  char* AddPrefix(const uint32_t& delta) {
    const uint32_t size = Align(delta);
    char* ptr = (buffer_.ptr != NULL) ? GetPrefix() + info_.prefix_size : NULL;
    info_.prefix_size += delta;
    buffer_.size -= (size < buffer_.size) ? size : buffer_.size;
    if (buffer_.size == 0)
      throw aql_profile_exc_msg("CommandBufferMgr::AddPrefix(): buffer size set to zero");
    return (buffer_.size != 0) ? ptr : NULL;
  }

  bool SetRdSize(const uint32_t& rd_data_size) {
    const uint32_t size = Align(rd_data_size);
    const bool suc = (size <= buffer_.size);
    if (suc) {
      info_.rdcmds_size = rd_data_size;
      buffer_.size -= size;
    }
    if (!suc)
      throw aql_profile_exc_msg("CommandBufferMgr::SetRdSize(): size set out of the buffer");
    return suc;
  }

  bool SetRd2Size(const uint32_t& rd_data_size) {
    const uint32_t size = Align(rd_data_size);
    const bool suc = SetRdSize(Align(size));
    if (suc) {
      info_.rd2cmds_size = rd_data_size;
      info_.rdcmds_size = 2 * size;
    }
    if (!suc)
      throw aql_profile_exc_msg("CommandBufferMgr::SetRd2Size(): size set out of the buffer");
    return suc;
  }

  bool SetPreSize(const uint32_t& pre_data_size) {
    const uint32_t size = Align(pre_data_size);
    const bool suc = (size <= buffer_.size);
    if (suc) {
      info_.precmds_size = pre_data_size;
      buffer_.size -= size;
    }
    if (!suc)
      throw aql_profile_exc_msg("CommandBufferMgr::SetPreSize(): size set out of the buffer");
    return suc;
  }

  bool Finalize(const uint32_t& data_size) {
    bool suc = (data_size > info_.precmds_size);
    if (suc) {
      const uint32_t post_data_size = data_size - info_.precmds_size;
      const uint32_t size = Align(post_data_size);
      suc = (size <= buffer_.size);
      if (suc) {
        info_.postcmds_size = post_data_size;
        buffer_.size -= size;
      }
      if (!suc)
        throw aql_profile_exc_msg("CommandBufferMgr::Finalize(): postcmd size is out of cmdbuffer");
    }
    if (!suc) throw aql_profile_exc_msg("CommandBufferMgr::Finalize(): postcmd size is zero");

    if (info_slot_) *info_slot_ = info_;

    return suc;
  }

  uint32_t GetSize() const { return GetEndOffset(); }

  descriptor_t GetRdDescr() const {
    descriptor_t descr;
    descr.ptr = reinterpret_cast<char*>(buffer_.ptr) + GetRdOffset();
    descr.size = info_.rdcmds_size;
    return descr;
  }

  descriptor_t FetchRdDescr() {
    descriptor_t descr;
    if (info_.is_rd_fetch2 == 0) {
      info_.is_rd_fetch2 = 1;
      descr.ptr = reinterpret_cast<char*>(buffer_.ptr) + GetRdOffset();
    } else {
      descr.ptr = reinterpret_cast<char*>(buffer_.ptr) + GetRdOffset() + (info_.rdcmds_size / 2);
    }
    descr.size = info_.rd2cmds_size;
    return descr;
  }

  descriptor_t GetPreDescr() const {
    descriptor_t descr;
    descr.ptr = reinterpret_cast<char*>(buffer_.ptr) + GetPreOffset();
    descr.size = info_.precmds_size;
    return descr;
  }

  descriptor_t GetPostDescr() const {
    descriptor_t descr;
    descr.ptr = reinterpret_cast<char*>(buffer_.ptr) + GetPostOffset();
    descr.size = info_.postcmds_size;
    return descr;
  }

 private:
  void Init(const descriptor_t& buffer, const bool& import) {
    buffer_ = buffer;
    info_ = {};
    info_slot_ = NULL;

    uint32_t prefix_size = sizeof(info_t);
    if (buffer_.ptr != NULL) {
      info_slot_ = reinterpret_cast<info_t*>(GetPrefix());
      if (import) {
        prefix_size = info_slot_->prefix_size;
        info_ = *info_slot_;
        info_.prefix_size = 0;
      }
    } else {
      buffer_.size = UINT_MAX;
    }
    AddPrefix(prefix_size);
  }

  uint32_t GetRdOffset() const { return Align(info_.prefix_size); }
  uint32_t GetPreOffset() const { return GetRdOffset() + Align(info_.rdcmds_size); }
  uint32_t GetPostOffset() const { return GetPreOffset() + Align(info_.precmds_size); }
  uint32_t GetEndOffset() const { return GetPostOffset() + Align(info_.postcmds_size); }

  static uint32_t Align(const uint32_t& size) { return (size + align_mask_) & ~align_mask_; }

  static const uint32_t align_size_ = 0x100;
  static const uint32_t align_mask_ = align_size_ - 1;

  descriptor_t buffer_;
  info_t info_;
  info_t* info_slot_;
};


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
          pmc_builder->Read(&commands, countersVec, (char*)(profile->output_buffer.ptr) + (profile->output_buffer.size / 2));
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
          ERR_LOGGING << "Bad profile output_buffer size ("
            << profile->output_buffer.size << "), required size(" << data_size << ")";
          return HSA_STATUS_ERROR_INVALID_ARGUMENT;
        }
      }
      assert(data_size <= profile->output_buffer.size);
    } else if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE) {
      pm4_builder::TraceConfig trace_config{};

      const uint32_t se_number = pm4_factory->GetShaderEnginesNumber();
      uint32_t se_mask = (1 << se_number) - 1;

      if (profile->parameters) {
        for (const hsa_ven_amd_aqlprofile_parameter_t* p = profile->parameters;
             p < (profile->parameters + profile->parameter_count); ++p) {
          switch (p->parameter_name) {
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SE_MASK:
              se_mask = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_COMPUTE_UNIT_TARGET:
              if (p->value > 15)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: CuId must be between 0 and 15, TargetCu", p->value);
              trace_config.targetCu = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_VM_ID_MASK:
              if (p->value > 2)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: VmId must be between 0 and 2, VmIdMask", p->value);
              trace_config.vmIdMask = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_MASK:
              if ((p->value & 0x50) != 0)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: Mask should have bits [4,6] set to Zero, Mask", p->value);
              trace_config.mask = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK:
              if ((p->value & 0xFF000000) != 0)
                throw aql_profile::aql_profile_exc_val<uint32_t>(
                    "ThreadTraceConfig: TokenMask should have bits [31:25] set to Zero, TokenMask",
                    p->value);
              trace_config.tokenMask = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK2:
              trace_config.tokenMask2 = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SAMPLE_RATE:
              trace_config.sampleRate = p->value;
              break;
            case HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_K_CONCURRENT:
              trace_config.concurrent = p->value;
              break;
            default:
              ERR_LOGGING << "Bad trace parameter name (" << p->parameter_name << ")";
              return HSA_STATUS_ERROR_INVALID_ARGUMENT;
          }
        }
      }

      uint32_t tnumber = 0;
      uint32_t tvector = 0;
      for (unsigned i = 0; i < se_number; ++i, se_mask >>= 1) {
        if (se_mask & 1) {
          const uint32_t pos = (pm4_builder::SE_VECTOR_SHIFT * tnumber);
          const uint32_t val = i << pos;
          tvector |= val;
          ++tnumber;
        }
      }

      const uint32_t control_size =
          pm4_builder::TT_STATUS_IDX_MAX * sizeof(pm4_builder::ControlType) * tnumber;
      char* prefix_ptr = cmd_buffer_mgr.AddPrefix(control_size + sizeof(uint32_t));
      pm4_builder::ControlType* const control_ptr =
          reinterpret_cast<pm4_builder::ControlType*>(prefix_ptr + sizeof(uint32_t));

      trace_config.se_number = tnumber;
      trace_config.se_vector = tvector;
      trace_config.control_buffer_ptr = control_ptr;
      trace_config.data_buffer_ptr = profile->output_buffer.ptr;
      trace_config.data_buffer_size = profile->output_buffer.size;

      if (prefix_ptr != NULL) {
        *reinterpret_cast<uint32_t*>(prefix_ptr) = tnumber;
        for (unsigned i = 0; i < tnumber; ++i, tvector >>= pm4_builder::SE_VECTOR_SHIFT) {
          const uint32_t se_id_ind =
              (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_ID;
          control_ptr[se_id_ind] = tvector & pm4_builder::SE_VECTOR_MASK;
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
        trace_config.spm_kfd_mode = pm4_factory->SpmKfdMode();
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
        ERR_LOGGING << "Bad profile command_buffer size ("
          << profile->command_buffer.size << "), required size(" << cmd_size << ")";
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
  try {
    // Populate GFX8 pm4 packet blob
    // Adding HSA barrier acquire packet
    data = aql_profile::LegacyAqlAcquire(aql_packet, data);
    // Adding PM4 command packet
    data = aql_profile::LegacyPm4(aql_packet, data);
    // Adding HSA barrier release packet
    data = aql_profile::LegacyAqlRelease(aql_packet, data);
  } catch (std::exception& e) {
    ERR_LOGGING << e.what();
    return HSA_STATUS_ERROR;
  }

  return HSA_STATUS_SUCCESS;
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
        *(uint32_t*)value = 0x1000;  // a current approximation as 4K is big enaugh
        break;
      case HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA_SIZE:
        *(uint32_t*)value = 0x1000;  // a current approximation as 4K is big enaugh
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
          const_cast<hsa_ven_amd_aqlprofile_profile_t*>(profile)->command_buffer.size = commands.Size();
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
        aql_profile::PopulateAql(
          profile->command_buffer.ptr,
          profile->command_buffer.size,
          cmd_writer,
          reinterpret_cast<aql_profile::packet_t*>(value));

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
    const uint32_t se_number = pm4_factory->GetShaderEnginesNumber();

    if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_PMC) {
      uint64_t* samples = reinterpret_cast<uint64_t*>(profile->output_buffer.ptr);
      const uint32_t sample_count = profile->output_buffer.size / sizeof(uint64_t);
      uint32_t sample_index = 0;
      for (const hsa_ven_amd_aqlprofile_event_t* p = profile->events;
           p < profile->events + profile->event_count; ++p) {
        // A perfcounter data sample per ShaderEngine
        const uint32_t block_samples_count =
            (pm4_factory->GetBlockInfo(p)->attr & CounterBlockSeAttr) ? se_number : 1;
        for (uint32_t i = 0; i < block_samples_count; ++i) {
          assert(sample_index < sample_count);
          if (sample_index >= sample_count) {
            ERR_LOGGING << "Bad sample index (" << sample_index << "/" << sample_count << ")";
            return HSA_STATUS_ERROR;
          }

          hsa_ven_amd_aqlprofile_info_data_t sample_info;
          sample_info.sample_id = i;
          sample_info.pmc_data.event = *p;
          uint64_t val = samples[sample_index];
          // If in concurrent, get the value difference
          //  1st half are from kernel end, and 2nd half are from kernel start
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
#if DEBUG_TRACE == 2
          printf("DATA: sample index(%u) id(%u) bloc id(%u) index(%u) counter id(%u) res(%lu)\n",
            sample_index, i, p->block_name, p->block_index, p->counter_id,
            samples[sample_index]);
#endif
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
    } else if (profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE) {
      uint32_t mode = 2;
      switch (profile->event_count) {
        case 0: mode = 0; break;
        case UINT32_MAX:
          const_cast<hsa_ven_amd_aqlprofile_profile_t*>(profile)->event_count = 0;
          mode = 1;
          break;
      }

      if (mode != 2) {  // SQTT trace data, or SQTT pc sampling
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
          if (control_ptr[status_ind] & pm4_builder::TT_CONTROL_UTC_ERR_MASK) {
            ERR_LOGGING << "SQTT memory error received, SE(" << i << ")";
            return HSA_STATUS_ERROR;
          }
#if 0
          if (control_ptr[status_ind] & pm4_builder::TT_CONTROL_FULL_MASK) {
            ERR2_LOGGING << "SQTT data buffer full, SE(" << i << ")";
            return HSA_STATUS_ERROR;
          }
#endif
        }

        // SQTT output buffer and capacity per ShaderEngine
        void* sample_ptr = profile->output_buffer.ptr;
        const uint32_t sample_capacity =
            (profile->output_buffer.size / tnumber) & ~(pm4_factory->GetSQTTBufferAlignment() - 1);
        // The samples sizes are returned in the control buffer
        for (unsigned i = 0; i < tnumber; ++i) {
          const uint32_t se_id_ind =
              (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_ID;
          const uint32_t se_id = control_ptr[se_id_ind];
          // WPTR specifies the index in thread trace buffer where next token will be
          // written by hardware. The index is incremented by size of 32 bytes.
          const uint32_t wptr_ind =
              (pm4_builder::TT_STATUS_IDX_MAX * i) + pm4_builder::TT_STATUS_IDX_WPTR;
          const uint32_t sample_size = (control_ptr[wptr_ind] & pm4_builder::TT_WRITE_PTR_MASK) *
              pm4_builder::TT_WRITE_PTR_BLK;
          if (sample_size > sample_capacity) {
            ERR_LOGGING << "SQTT data out of bounds, sample_id(" << i << ") size(" << sample_size
                        << "/" << sample_capacity << ")";
            return HSA_STATUS_ERROR;
          }

          if (mode == 0) {  // SQTT trace
            hsa_ven_amd_aqlprofile_info_data_t sample_info;
            sample_info.sample_id = se_id;
            sample_info.trace_data.ptr = sample_ptr;
            sample_info.trace_data.size = sample_size;
            status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA, &sample_info, data);
          } else {  // PC sampling
            pcsmp_callback_data_t* pcsmp_data = reinterpret_cast<pcsmp_callback_data_t*>(data);
            pcsmp_data->id = se_id;
            pcsmp_data->cycle = 333;
            pcsmp_data->pc = 0x333;
            status = callback(HSA_VEN_AMD_AQLPROFILE_INFO_TRACE_DATA, NULL, data);
          }
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
          status = spm_iterate_data(profile, callback, data);
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
