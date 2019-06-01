#ifndef SRC_CORE_PM4_FACTORY_H_
#define SRC_CORE_PM4_FACTORY_H_

#include <assert.h>
#include <hsa_ext_amd.h>
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

namespace aql_profile {

// GPU enumeration
enum gpu_id_t {
  INVAL_GPU_ID,  // invalid GPU id
  GFX8_GPU_ID,   // generic Gfx8 id
  FIJI_GPU_ID,   // Fiji GPU id
  GFX9_GPU_ID,   // generic Gfx9 id
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
  static Pm4Factory* Create(const hsa_agent_t agent);
  // Create factory for a given profile
  static Pm4Factory* Create(const profile_t* profile) { return Create(profile->agent); }
  // Destroy factory
  static void Destroy();

  // Return PM4 command builder
  pm4_builder::CmdBuilder* GetCmdBuilder() { return cmd_builder_; }
  // Return PMC PM4 packets builder
  pm4_builder::PmcBuilder* GetPmcBuilder() { return pmc_builder_; }
  // Return SPM PM4 packets builder
  pm4_builder::SpmBuilder* GetSpmBuilder() { return spm_builder_; }
  // Return SQTT PM4 packets builder
  pm4_builder::SqttBuilder* GetSqttBuilder() { return sqtt_builder_; }

  // Return Shader Engines number
  const uint32_t GetShaderEnginesNumber() { return 4; }
  // Return SQTT buffer alignment
  const uint32_t GetSQTTBufferAlignment() { return 0x1000; }

  // Return block info foor a given event
  const GpuBlockInfo* GetBlockInfo(const event_t* event) const {
    const GpuBlockInfo* info = block_map_.Get(event->block_name);
    if (info == NULL) throw event_exception(std::string("Bad block, "), *event);
    // Checking that the block index is in proper range
    if (event->block_index >= info->instance_count)
      throw event_exception(std::string("Bad block index, "), *event);
    // Checking that the counter event index is in proper range
    if (event->counter_id > info->event_id_max)
      throw event_exception(std::string("Bad event ID, "), *event);
    return info;
  }

  // Return block info for a given block id
  const GpuBlockInfo* GetBlockInfo(const uint32_t& block_id) const {
    return block_map_.Get(block_id);
  }

  // Return block id for a given block name string
  uint32_t FindBlock(const char* name) const { return block_map_.Find(name); }

 protected:
  explicit Pm4Factory(const BlockInfoMap& map) :
    cmd_builder_(NULL),
    pmc_builder_(NULL),
    spm_builder_(NULL),
    sqtt_builder_(NULL),
    block_map_(map)
  {}

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

 private:
  // PM4 factory instance map type
  typedef std::map<gpu_id_t, Pm4Factory*> instances_t;

  // Create Fiji factory
  static Pm4Factory* FijiCreate();
  // Create GFX8 generic factory
  static Pm4Factory* Gfx8Create();
  // Create GFX9 generic factory
  static Pm4Factory* Gfx9Create();
  // Return GPU id for a given agent
  static gpu_id_t GetGpuId(const hsa_agent_t agent);

  // Mutex for inter thread synchronization for the instances create/destroy
  static mutex_t mutex_;
  // Factory instances container
  static instances_t* instances_;
  // Block info container
  const BlockInfoMap block_map_;
};

// Create PM4 factory
inline Pm4Factory* Pm4Factory::Create(const hsa_agent_t agent) {
  std::lock_guard<mutex_t> lck(mutex_);

  // Get GPU id for a given agent
  const gpu_id_t gpu_id = GetGpuId(agent);
  // Check if we have the instance already created
  if (instances_ == NULL) instances_ = new instances_t;
  const auto ret = instances_->insert({gpu_id, NULL});
  instances_t::iterator it = ret.first;
  // Create a factory implementation for the GPU id
  if (ret.second) {
    switch (gpu_id) {
      // Create Gfx8 generaic factory
      case GFX8_GPU_ID:
        it->second = Gfx8Create();
        break;
      // Create Fiji specific factory
      case FIJI_GPU_ID:
        it->second = FijiCreate();
        break;
      // Create Gfx9 generic factory
      case GFX9_GPU_ID:
        it->second = Gfx9Create();
        break;
      default:
        throw aql_profile_exc_val<gpu_id_t>("GPU id error", gpu_id);
    }
  }

  if (it->second == NULL) throw aql_profile_exc_msg("Pm4Factory::Create() failed");
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

// Return GPU id for a given agent
inline gpu_id_t Pm4Factory::GetGpuId(const hsa_agent_t agent) {
  hsa_status_t status = HSA_STATUS_ERROR;
  char agent_name[64];
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
  if (strncmp(agent_name, "gfx801", 6) == 0) {
    throw aql_profile_exc_val<std::string>("GPU Carrizo is not supported", agent_name);
  } else if (strncmp(agent_name, "gfx8", 4) == 0) {
    switch (device_id) {
      // Ellesmere
      case 0x67C0:  // EllesmereM GL XT
      case 0x67C1:  // EllesmereM GL PRO
      case 0x67C2:  // Ellesmere Server XT, EllesmereM Server XT
      case 0x67C4:  // Ellesmere GL XT
      case 0x67C7:  // Ellesmere GL PRO
      case 0x67DF:  // Ellesmere consumer, EllesmereM; Polaris20; Polaris20M
      case 0x67D0:  // Ellesmere VF
      // Ellesmere Kickers
      case 0x67C8:  // EllesmereM GL XT Kicker
      case 0x67C9:  // EllesmereM GL PRO  Kicker
      case 0x67CA:  // Ellesmere Server XT Kicker
      case 0x67CC:  // Ellesmere GL XT Kicker
      case 0x67CF:  // Ellesmere GL PRO Kicker
      // Buffin
      case 0x67E0:  // BaffinM GL XT
      case 0x67E3:  // Baffin Desktop GL XT
      case 0x67E8:  // BaffinM GL Pro
      case 0x67EB:  // BaffinM Server
      case 0x67EF:  // BaffinM, Baffin Desktop; Polaris21; Polaris21M
      case 0x67FF:  // BaffinM XPA; Polaris21; Polaris21M
      // Baffin Kickers
      case 0x67E1:  // BaffinM GL XT Kicker
      case 0x67E7:  // Baffin Desktop GL XT Kicker
      case 0x67E9:  // BaffinM GL Pro Kicker
        gpu_id = GFX8_GPU_ID;
        break;
      // Fiji
      case 0x7300:  // Fiji
      case 0x730f:  // Fiji VF
        gpu_id = FIJI_GPU_ID;
        break;
      default: {
        std::ostringstream oss;
        oss << "GPU device_id(" << std::hex << device_id << ") is not supported";
        throw aql_profile_exc_msg(oss.str());
      }
    }
  } else if ((strncmp(agent_name, "gfx900", 6) == 0) || (strncmp(agent_name, "gfx902", 6) == 0) ||
             (strncmp(agent_name, "gfx906", 6) == 0)) {
    gpu_id = GFX9_GPU_ID;
  } else {
    throw aql_profile_exc_val<std::string>("GFXIP is not supported", agent_name);
  }

  return gpu_id;
}

}  // namespace aql_profile

#endif  // SRC_CORE_PM4_FACTORY_H_
