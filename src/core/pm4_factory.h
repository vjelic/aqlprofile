#ifndef SRC_CORE_PM4_FACTORY_H_
#define SRC_CORE_PM4_FACTORY_H_

#include <string.h>
#include <assert.h>
#include <stdint.h>

#include <climits>
#include <map>
#include <mutex>
#include <string>

#include "core/aql_profile.h"
#include "core/aql_profile_exception.h"
#include "def/gpu_block_info.h"

namespace pm4_builder {
class CmdBuilder;
class PmcBuilder;
class SqttBuilder;
}

namespace aql_profile {

class BlockMap {
 public:
  BlockMap(const GpuBlockInfo** table, const uint32_t& size)
      : block_table_(table), block_count_(size / sizeof(uintptr_t)) {}
  BlockMap(const BlockMap& map) : block_table_(map.block_table_), block_count_(map.block_count_) {}

  const GpuBlockInfo* Get(const uint32_t& id) const {
    return (id < block_count_) ? block_table_[id] : NULL;
  }

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
  const GpuBlockInfo** const block_table_;
  const uint32_t block_count_;
};

class Pm4Factory {
 public:
  typedef std::mutex mutex_t;

  static Pm4Factory* Create(const hsa_agent_t agent);
  static Pm4Factory* Create(const profile_t* profile) { return Create(profile->agent); }
  static Pm4Factory* Gfx8Create();
  static Pm4Factory* Gfx9Create();
  static void Destroy();

  virtual pm4_builder::CmdBuilder* GetCmdBuilder() = 0;
  virtual pm4_builder::PmcBuilder* GetPmcBuilder() = 0;
  virtual pm4_builder::SqttBuilder* GetSqttBuilder() = 0;

  const uint32_t GetShaderEnginesNumber() { return 4; }

  const GpuBlockInfo* GetBlockInfo(const event_t* event) const {
    const GpuBlockInfo* info = block_map_.Get(event->block_name);
    if (info == NULL) throw event_exception(std::string("Bad block, "), *event);
    if (event->block_index >= info->instance_count)
      throw event_exception(std::string("Bad block index, "), *event);
    if (event->counter_id > info->event_id_max)
      throw event_exception(std::string("Bad event ID, "), *event);
    return info;
  }

  const GpuBlockInfo* GetBlockInfo(const uint32_t& block) const {
    return block_map_.Get(block);
  }

  uint32_t FindBlock(const char* name) const {
    return block_map_.Find(name);
  }

  uint32_t GetBlockId(const event_t* event) const { return GetBlockInfo(event)->id; }

 protected:
  explicit Pm4Factory(const BlockMap& map) : block_map_(map) {}
  virtual ~Pm4Factory() {}

 private:
  typedef std::map<std::string, Pm4Factory*> instances_t;

  static mutex_t mutex_;
  static instances_t instances_;
  const BlockMap block_map_;
};

inline Pm4Factory* Pm4Factory::Create(const hsa_agent_t agent) {
  std::lock_guard<mutex_t> lck(mutex_);

  char agent_name[64];
  hsa_agent_get_info(agent, HSA_AGENT_INFO_NAME, agent_name);
  instances_t::iterator it = instances_.find(agent_name);

  if (it == instances_.end()) {
    if (strncmp(agent_name, "gfx801", 6) == 0) {
      throw aql_profile_exc_val<std::string>(std::string("GFX8 Carrizo is not supported "),
                                             agent_name);
    } else if (strncmp(agent_name, "gfx8", 4) == 0) {
      it->second = Gfx8Create();
    } else if (strncmp(agent_name, "gfx9", 4) == 0) {
      it->second = Gfx9Create();
    } else {
      throw aql_profile_exc_val<std::string>("Unsupported GFXIP", agent_name);
    }
  }

  if (it->second == NULL) throw aql_profile_exc_msg("Pm4Factory allocation failed");
  return it->second;
}

inline void Pm4Factory::Destroy() {
  std::lock_guard<mutex_t> lck(mutex_);
  for (auto& item : instances_) delete item.second;
  instances_.clear();
}

}  // namespace aql_profile

#endif  // SRC_CORE_PM4_FACTORY_H_
