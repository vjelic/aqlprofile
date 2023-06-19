#ifndef SRC_CORE_PM4_FACTORY_H_
#define SRC_CORE_PM4_FACTORY_H_

#include <assert.h>
#include <hsa/hsa_ext_amd.h>
#include <stdint.h>
#include <string.h>

#include <climits>
#include <map>
#include <mutex>
#include <sstream>
#include <string>

#include "core/aql_profile.h"
#include "core/aql_profile_exception.h"
#include "def/gpu_block_info.h"
#include "pm4/cmd_builder.h"
#include "pm4/pmc_builder.h"
#include "pm4/spm_builder.h"
#include "pm4/sqtt_builder.h"
#include "util/hsa_rsrc_factory.h"

namespace aql_profile {

// GPU enumeration
enum gpu_id_t {
  INVAL_GPU_ID,  // invalid GPU id
  GFX9_GPU_ID,   // generic Gfx9 id
  MI100_GPU_ID,  // Mi100 GPU id
  MI200_GPU_ID,   // Mi200 GPU id
  MI300_GPU_ID,   // Mi300 GPU id
  GFX10_GPU_ID,  // generic Gfx10 id
  GFX11_GPU_ID   // generic Gfx11 id
};

// Block info map class
class BlockInfoMap {
 public:
  BlockInfoMap(const GpuBlockInfo** table, const uint32_t& size)
      : block_table_(table), block_count_(size / sizeof(uintptr_t)) {}
  BlockInfoMap(const BlockInfoMap& map)
      : block_table_(map.block_table_), block_count_(map.block_count_) {}

  // Get block info for a given block id
  const GpuBlockInfo* Get(const uint32_t& block_id) const {
    return (block_id < block_count_) ? block_table_[block_id] : NULL;
  }

  // Find block by name
  // Return block id or UINT32_MAX if not found
  uint32_t Find(const char* name) const {
    uint32_t index = 0;
    while (index < block_count_) {
      const GpuBlockInfo* entry = block_table_[index];
      if (entry) {
        if (strcmp(name, entry->name) == 0) break;
      }
      ++index;
    }
    return (index == block_count_) ? UINT32_MAX : index;
  }

 private:
  // Block info table
  const GpuBlockInfo** const block_table_;
  // Number of elements in the block info table
  const uint32_t block_count_;
};

// Factory of PM4 builders
class Pm4Factory {
 public:
  typedef std::mutex mutex_t;

  // Create factory for a given agent
  static Pm4Factory* Create(const hsa_agent_t agent, const bool concurrent = false);
  // Create factory for a given profile
  static Pm4Factory* Create(const profile_t* profile) {
    // First check and save the mode
    return Create(profile->agent, CheckConcurrent(profile));
  }
  // Destroy factory
  static void Destroy();

  // Return gpu id
  gpu_id_t GetGpuId() const { return gpu_id_; }
  // Is pmc to be profiled concurrently?
  bool IsConcurrent() const { return concurrent_mode_; }
  // Is getting SPM data using driver public API?
  bool SpmKfdMode() const { return spm_kfd_mode_; }

  // Return PM4 command builder
  pm4_builder::CmdBuilder* GetCmdBuilder() const { return cmd_builder_; }
  // Return PMC PM4 packets builder
  pm4_builder::PmcBuilder* GetPmcBuilder() const { return pmc_builder_; }
  // Return SPM PM4 packets builder
  pm4_builder::SpmBuilder* GetSpmBuilder() const { return spm_builder_; }
  // Return SQTT PM4 packets builder
  pm4_builder::SqttBuilder* GetSqttBuilder() const { return sqtt_builder_; }

  // Return Shader Engines number
  uint32_t GetShaderEnginesNumber() const { return agent_info_->se_num; }
  // Return SQTT buffer alignment
  uint32_t GetSQTTBufferAlignment() const { return 0x1000; }
  const char* GetGFX() const { return agent_info_->name; }
  virtual bool IsGFX10() const { return false; } //return strncmp("gfx103", GetGFX(), 6); }
  // Return number of XCC on the GPU
  uint32_t GetXccNumber() const { return agent_info_->xcc_num; }

  // Return block info foor a given event
  const GpuBlockInfo* GetBlockInfo(const event_t* event) const {
    const GpuBlockInfo* info = block_map_.Get(event->block_name);
    if (info == NULL) throw event_exception(std::string("Bad block, "), *event);
    // Checking that the block index is in proper range
    if (event->block_index >= info->instance_count)
      throw event_exception(std::string("Bad block index, "), *event);
      // Checking that the counter event index is in proper range
#if 0
    if (event->counter_id > info->event_id_max)
      throw event_exception(std::string("Bad event ID, "), *event);
#endif
    return info;
  }

  // Return block info for a given block id
  const GpuBlockInfo* GetBlockInfo(const uint32_t& block_id) const {
    return block_map_.Get(block_id);
  }

  // Return block id for a given block name string
  uint32_t FindBlock(const char* name) const { return block_map_.Find(name); }

  /// Workaround for GFX11. PMC Builder overrides this.
  virtual int GetSQ_PMC_samples_per_SE() {
    if (pmc_builder_)
      return pmc_builder_->GetSQ_PMC_samples_per_SE();
    return 1;
  };

 protected:
  explicit Pm4Factory(const BlockInfoMap& map)
      : cmd_builder_(NULL),
        pmc_builder_(NULL),
        spm_builder_(NULL),
        sqtt_builder_(NULL),
        agent_info_(NULL),
        concurrent_mode_(concurrent_create_mode_),
        block_map_(map) {}

  virtual ~Pm4Factory() {
    delete cmd_builder_;
    delete pmc_builder_;
    delete spm_builder_;
    delete sqtt_builder_;
  }

  // PM4 command builder
  pm4_builder::CmdBuilder* cmd_builder_;
  // PMC PM4 packets builder
  pm4_builder::PmcBuilder* pmc_builder_;
  // SPM PM4 packets builder
  pm4_builder::SpmBuilder* spm_builder_;
  // SQTT PM4 packets builder
  pm4_builder::SqttBuilder* sqtt_builder_;
  // agent info
  const AgentInfo* agent_info_;
  gpu_id_t gpu_id_;
  // Concurrent mode
  static bool concurrent_create_mode_;
  static bool spm_kfd_mode_;
  bool concurrent_mode_;

 private:
  // PM4 factory instance map type
  typedef std::pair<gpu_id_t, int> instances_key_t;
  struct instances_fncomp_t {
    bool operator()(const instances_key_t& a, const instances_key_t& b) const {
      return (a.first < b.first) || ((a.first == b.first) && (a.second < b.second));
    }
  };
  typedef std::map<instances_key_t, Pm4Factory*, instances_fncomp_t> instances_t;

  // Create GFX9 generic factory
  static Pm4Factory* Gfx9Create(const AgentInfo* agent_info);
  // Create GFX10 generic factory
  static Pm4Factory* Gfx10Create(const AgentInfo* agent_info);
  // Create GFX11 generic factory
  static Pm4Factory* Gfx11Create(const AgentInfo* agent_info);
  // Create MI100 factory
  static Pm4Factory* Mi100Create(const AgentInfo* agent_info);
  // Create MI200 factory
  static Pm4Factory* Mi200Create(const AgentInfo* agent_info);
  // Create MI300 factory
  static Pm4Factory* Mi300Create(const AgentInfo* agent_info);
  // Return GPU id for a given agent
  static gpu_id_t GetGpuId(const hsa_agent_t agent);

  static bool CheckConcurrent(const profile_t* profile);

  // Mutex for inter thread synchronization for the instances create/destroy
  static mutex_t mutex_;
  // Factory instances container
  static instances_t* instances_;
  // Block info container
  const BlockInfoMap block_map_;
};

// Create PM4 factory
inline Pm4Factory* Pm4Factory::Create(const hsa_agent_t agent, bool concurrent) {
  std::lock_guard<mutex_t> lck(mutex_);
  const AgentInfo* agent_info = HsaRsrcFactory::Instance().GetAgentInfo(agent);
  // Get GPU id for a given agent
  const gpu_id_t gpu_id = GetGpuId(agent);
  // Check if we have the instance already created
  if (instances_ == NULL) instances_ = new instances_t;
  const auto ret = instances_->insert({instances_key_t{gpu_id, concurrent}, NULL});
  instances_t::iterator it = ret.first;

  concurrent_create_mode_ = concurrent;
  spm_kfd_mode_ = (getenv("ROCP_SPM_KFD_MODE") != NULL);

  // Create a factory implementation for the GPU id
  if (ret.second) {
    switch (gpu_id) {
      // Create Gfx9 generic factory
      case GFX9_GPU_ID:
        it->second = Gfx9Create(agent_info);
        break;
      // Create Gfx10 generic factory
      case GFX10_GPU_ID:
        it->second = Gfx10Create(agent_info);
        break;
      // Create Gfx11 generic factory
      case GFX11_GPU_ID:
        it->second = Gfx11Create(agent_info);
        break;
      // Create MI100 generic factory
      case MI100_GPU_ID:
        it->second = Mi100Create(agent_info);
        break;
      case MI200_GPU_ID:
        it->second = Mi200Create(agent_info);
        break;
      case MI300_GPU_ID:
        it->second = Mi300Create(agent_info);
        break;
      default:
        throw aql_profile_exc_val<gpu_id_t>("GPU id error", gpu_id);
    }
  }

  if (it->second == NULL) throw aql_profile_exc_msg("Pm4Factory::Create() failed");
  it->second->gpu_id_ = gpu_id;
  return it->second;
}

// Destroy PM4 factory
inline void Pm4Factory::Destroy() {
  std::lock_guard<mutex_t> lck(mutex_);

  if (instances_ != NULL) {
    for (auto& item : *instances_) delete item.second;
    delete instances_;
    instances_ = NULL;
  }
}

// Check the setting of pmc profiling mode
inline bool Pm4Factory::CheckConcurrent(const profile_t* profile) {
  for (const hsa_ven_amd_aqlprofile_parameter_t* p = profile->parameters;
       p < (profile->parameters + profile->parameter_count); ++p) {
    if (p->parameter_name == HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_K_CONCURRENT) return true;
  }

  return false;
}

// Return GPU id for a given agent
inline gpu_id_t Pm4Factory::GetGpuId(const hsa_agent_t agent) {
  hsa_status_t status = HSA_STATUS_ERROR;
  char agent_name[64];
  char agent_gfxip[64];
  uint32_t device_id = 0;

  // Getting GfxIP name
  status = hsa_agent_get_info(agent, HSA_AGENT_INFO_NAME, agent_name);
  if (status == HSA_STATUS_SUCCESS) {
    // Getting DeviceId
    hsa_agent_info_t attribute = static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_CHIP_ID);
    status = hsa_agent_get_info(agent, attribute, &device_id);
  }
  if (status != HSA_STATUS_SUCCESS) {
    throw aql_profile_exc_msg("Pm4Factory::Create() bad agent");
  }

  const char* override_id = getenv("HSA_VEN_AMD_AQLPROFILE_DID");
  if (override_id != NULL) {
    device_id = atoi(override_id);
  }

  // Obtaining GPU id
  gpu_id_t gpu_id = INVAL_GPU_ID;

  const int gfxip_label_len = strlen(agent_name) - 2;
  memcpy(agent_gfxip, agent_name, gfxip_label_len);
  agent_gfxip[gfxip_label_len] = '\0';

  if (strcmp(agent_gfxip, "gfx11") == 0){
    gpu_id = GFX11_GPU_ID;
  } else if (strcmp(agent_gfxip, "gfx10") == 0){
    gpu_id = GFX10_GPU_ID;
  } else if (strncmp(agent_name, "gfx908", 6) == 0) {  // MI100
    gpu_id = MI100_GPU_ID;
  } else if (strncmp(agent_name, "gfx90a", 6) == 0) {
    gpu_id = MI200_GPU_ID;
  } else if (strncmp(agent_name, "gfx940", 6) == 0) {
    gpu_id = MI300_GPU_ID;
  } else if ((strncmp(agent_name, "gfx900", 6) == 0)
      || (strncmp(agent_name, "gfx902", 6) == 0)
      || (strncmp(agent_name, "gfx906", 6) == 0)
  ) {
    gpu_id = GFX9_GPU_ID;
  } else {
    throw aql_profile_exc_val<std::string>("GFXIP is not supported", agent_name);
  }

  return gpu_id;
}

}  // namespace aql_profile

#endif  // SRC_CORE_PM4_FACTORY_H_
