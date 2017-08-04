#ifndef _GPU_BLOCKINFO_H_
#define _GPU_BLOCKINFO_H_

#include <stdint.h>

namespace gfxip {

// Counter Block attributes
enum CounterBlockAttr {
  // Default block attribute
  CounterBlockDfltAttr = 0,
  // Per ShaderEngine blocks
  CounterBlockSeAttr = 1,
  // SQ blocks
  CounterBlockSqAttr = 2,
  // Need to clean counter registers
  CounterBlockCleanAttr = 4,
  // MC Block
  CounterBlockMcAttr = 8,
};

// Register address corresponding to each counter
struct CounterRegInfo {
  // counter select register address
  uint32_t select_addr;
  // counter control register address
  uint32_t control_addr;
  // counter register address low
  uint32_t register_addr_lo;
  // counter register address high
  uint32_t register_addr_hi;
};

struct counter_des_t;

// GPU Block info definition
struct GpuBlockInfo {
  // Unique string identifier of the block.
  const char* name;
  // Block ID
  uint32_t id;
  // Maximum number of block instances in the group per shader array
  uint32_t instance_count;
  // Maximum counter event ID
  uint32_t event_id_max;
  // Maximum number of counters that can be enabled at once
  uint32_t counter_count;
  // Counter registers addresses
  const CounterRegInfo* counter_reg_info;
  // Counter select value function
  uint32_t (*select_value)(const counter_des_t&);
  // Block attributes mask
  uint32_t attr;
};

// Block descriptor
struct block_des_t {
  uint32_t id;
  uint32_t index;
};

// block_des_t less then functor
struct lt_block_des {
  bool operator()(const block_des_t& a1, const block_des_t& a2) const {
    return (a1.id < a2.id) || ((a1.id == a2.id) && (a1.index < a2.index));
  }
};

// Counter descriptor
struct counter_des_t {
  uint32_t id;
  uint32_t index;
  block_des_t block_des;
  const GpuBlockInfo* block_info;
};

}  // namespace gfxip

#endif  // _GPU_BLOCKINFO_H_
