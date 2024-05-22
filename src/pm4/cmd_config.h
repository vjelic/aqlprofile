
#ifndef SRC_PM4_CMD_CONFIG_H_
#define SRC_PM4_CMD_CONFIG_H_

#include <stdint.h>
#include "pm4/trace_config.h"

namespace pm4_builder {
// Counters vector class
class counters_vector : public std::vector<counter_des_t> {
 public:
  typedef std::vector<counter_des_t> Parent;

  counters_vector() : Parent(), attr_(0) {}

  void push_back(const counter_des_t& des) {
    Parent::push_back(des);
    attr_ |= des.block_info->attr;
  }

  uint32_t get_attr() const { return attr_; }

 private:
  uint32_t attr_;
};

}  // namespace pm4_builder

#endif  // SRC_PM4_CMD_CONFIG_H_
