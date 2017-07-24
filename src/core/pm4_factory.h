#ifndef _PM4_FACTORY_H_
#define _PM4_FACTORY_H_

#include <string.h>
#include <assert.h>
#include <stdint.h>

#include <climits>
#include <map>
#include <mutex>
#include <string>

#include "core/aql_profile.h"
#include "core/aql_profile_exception.h"
#include "gfxip/gpu_block_info.h"

namespace pm4_builder {
class CmdBuilder;
class PmcBuilder;
class SqttBuilder;
}

namespace aql_profile {
using namespace gfxip;

class BlockMap {
 public:
  typedef std::map<uint32_t, const GpuBlockInfo*> map_t;
  typedef map_t::const_iterator iter_t;

  BlockMap(uint32_t* id_table, const GpuBlockInfo* info_table, const uint32_t& info_count) {
    map_t info_map;
    for (uint32_t i = 0; i < info_count; ++i) {
      const GpuBlockInfo& entry = info_table[i];
      info_map[entry.counterGroupId] = &entry;
    }
    for (uint32_t i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
      iter_t it = info_map.find(id_table[i]);
      if (it != info_map.end()) block_map[i] = it->second;
    }
  }

  const GpuBlockInfo* get(const uint32_t& id) const {
    iter_t it = block_map.find(id);
    return (it != block_map.end()) ? it->second : NULL;
  }

 private:
  map_t block_map;
};

class Pm4Factory {
 public:
  enum { kBadBlockId = UINT_MAX };

  static Pm4Factory* Create(const hsa_agent_t agent);
  static Pm4Factory* Create(const profile_t* profile) { return Create(profile->agent); }
  static Pm4Factory* Gfx8Create();
  static Pm4Factory* Gfx9Create();
  static void Destroy();

  virtual pm4_builder::CmdBuilder* getCmdBuilder() = 0;
  virtual pm4_builder::PmcBuilder* getPmcBuilder() = 0;
  virtual pm4_builder::SqttBuilder* getSqttBuilder() = 0;

  const uint32_t getShaderEnginesNumber() { return 4; }

  const GpuBlockInfo* getBlockInfo(const event_t* event) const {
    const GpuBlockInfo* info = block_map.get(event->block_name);
    if (info == NULL) throw event_exception(std::string("Bad block, "), *event);
    if (event->block_index >= info->maxInstanceCount)
      throw event_exception(std::string("Bad block index, "), *event);
    if (event->counter_id > info->maxEventId)
      throw event_exception(std::string("Bad event ID, "), *event);
    return info;
  }

  uint32_t getBlockId(const event_t* event) const { return getBlockInfo(event)->counterGroupId; }

 protected:
  explicit Pm4Factory(const BlockMap& map) : block_map(map) {}
  virtual ~Pm4Factory() {}

 private:
  typedef std::map<std::string, Pm4Factory*> instances_t;

  static std::mutex mutex;
  static instances_t instances;
  const BlockMap& block_map;
};

inline Pm4Factory* Pm4Factory::Create(const hsa_agent_t agent) {
  std::lock_guard<std::mutex> lck(mutex);

  char agent_name[64];
  hsa_agent_get_info(agent, HSA_AGENT_INFO_NAME, agent_name);
  instances_t::iterator it = instances.find(agent_name);

  if (it == instances.end()) {
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
  std::lock_guard<std::mutex> lck(mutex);
  for (auto it : instances) delete it.second;
  instances.clear();
}

}  // namespace aql_profile

#endif  // _PM4_FACTORY_H_
