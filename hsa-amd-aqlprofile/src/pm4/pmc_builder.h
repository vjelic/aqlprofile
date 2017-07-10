#ifndef _HSA_PERF_H_
#define _HSA_PERF_H_

#include <stdint.h>

#include <vector>
#include <map>
#include <string>

namespace pm4_builder {
class CmdBuffer;
class CmdBuilder;

typedef std::vector<uint32_t> CountersVec;
typedef std::map<uint32_t, CountersVec> CountersMap;

class PmcBuilder {
 public:
  virtual ~PmcBuilder() {}

  // Generate start profiling commands.
  virtual void begin(CmdBuffer* cmdBuff, const CountersMap& countersMap) = 0;

  // Generate stop profiling commands.
  // Return actual required data buffer size.
  virtual uint32_t end(CmdBuffer* cmdBuff, const CountersMap& countersMap, void* dataBuff) = 0;

  // A flag to indicate the current packet is for copy register value
  constexpr static uint32_t COPY_DATA_FLAG = 0xFFFFFFFF;
  // Maximum number of programmed registers
  constexpr static uint32_t MAX_REG_NUM = 100;
  // Shader Engines number on the GPU
  constexpr static uint32_t se_number_ = 4;
};
}  // namespace pm4_builder
#endif  // _HSA_PERF_H_
