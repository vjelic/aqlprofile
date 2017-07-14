#ifndef _HSA_PERF_H_
#define _HSA_PERF_H_

#include <stdint.h>

#include <vector>
#include <map>
#include <string>

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

typedef struct {
  uint32_t id;
  uint32_t index;
} block_des_t;

struct lt_block_des {
  bool operator()(const block_des_t& a1, const block_des_t& a2) const {
    return (a1.id < a2.id) || ((a1.id == a2.id) && (a1.index < a2.index));
  }
};

typedef std::vector<std::pair<block_des_t, uint32_t> > counters_vector;

class PmcBuilder {
 public:
  virtual ~PmcBuilder() {}

  // Generate start profiling commands.
  virtual void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) = 0;

  // Generate stop profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) = 0;

  // A flag to indicate the current packet is for copy register value
  constexpr static uint32_t COPY_DATA_FLAG = 0xFFFFFFFF;
  // Maximum number of programmed registers
  constexpr static uint32_t MAX_REG_NUM = 128;
  // Shader Engines number on the GPU
  constexpr static uint32_t se_number_ = 4;
};
}  // namespace pm4_builder
#endif  // _HSA_PERF_H_
