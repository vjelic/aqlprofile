#ifndef _GFX9_FACTORY_H_
#define _GFX9_FACTORY_H_
#include "core/pm4_factory.h"

namespace aql_profile {

// Gfx9 factory class
class Gfx9Factory : public Pm4Factory {
 public:
  explicit Gfx9Factory(const AgentInfo* agent_info)
      : Pm4Factory(BlockInfoMap(block_table_, sizeof(block_table_))) {
    Init(agent_info);
  }
  Gfx9Factory(const GpuBlockInfo** table, const uint32_t& size, const AgentInfo* agent_info)
      : Pm4Factory(BlockInfoMap(table, size)) {
    Init(agent_info);
  }

  bool IsGFX9() const override { return true; }

 protected:
  void Init(const AgentInfo* agent_info);
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];

  static void Print(const GpuBlockInfo* block_info);
};

// Mi100 factory class
class Mi100Factory : public Gfx9Factory {
 public:
  explicit Mi100Factory(const AgentInfo* agent_info);

 protected:
  static const GpuBlockInfo* block_table_[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
};

}

#endif  // _GFX9_FACTORY_H_
