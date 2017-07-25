#ifndef _HSA_PERF_H_
#define _HSA_PERF_H_

#include <stdint.h>

#include <vector>
#include <map>
#include <string>

#include "gfxip/gpu_block_info.h"

namespace pm4_builder {
using namespace gfxip;
class CmdBuffer;
class CmdBuilder;

typedef std::vector<counter_des_t> counters_vector;

class PmcBuilder {
 public:
  virtual ~PmcBuilder() {}
  // Generate start profiling commands.
  virtual void begin(CmdBuffer* cmdBuff, const counters_vector& countersVec) = 0;
  // Generate stop profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t end(CmdBuffer* cmdBuff, const counters_vector& countersVec, void* dataBuff) = 0;
  // Shader Engines number on the GPU
  constexpr static uint32_t se_number_ = 4;
};
}  // namespace pm4_builder
#endif  // _HSA_PERF_H_
