#include "core/aql_profile.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "../rocprofv2_att/tracebranch.hpp"
#include "../rocprofv2_att/trace_parser.hpp"

// Method for iterating the events output data

#ifdef AMD_AQLPROFILE_SQTT_NPI

hsa_ven_amd_aqlprofile_info_data_t aql_profile::aqlprofile_sqttfilter_iterate_data(
  void* sample_ptr,
  uint64_t sample_capacity,
  uint64_t sample_size,
  uint32_t se_id,
  int att_target_cu
) {
  hsa_ven_amd_aqlprofile_info_data_t sample_info;
  sample_info.sample_id = se_id;
  sample_info.trace_data.ptr = sample_ptr;
  sample_info.trace_data.size = sample_size;
  return sample_info;
}

#else

hsa_ven_amd_aqlprofile_info_data_t aql_profile::aqlprofile_sqttfilter_iterate_data(
  void* sample_ptr,
  uint64_t sample_capacity,
  uint64_t sample_size,
  uint32_t se_id,
  int att_target_cu
) {
  void* newdata = calloc(sample_size/8+4, 8);
  hsa_memory_copy(newdata, sample_ptr, sample_size);
  auto ret = AnalyseBinary_internal((uint8_t*)newdata, sample_size, att_target_cu);
  free(newdata);

  size_t needed_data = ret->GetMemoryNeededForSerialization();
  needed_data = std::max(needed_data, sample_size);

  char* dataptr = (char*)calloc(needed_data/8+1, 8);
  size_t size_used = ret->Serialize(dataptr, needed_data);

  size_t data_size = std::min(needed_data, sample_capacity);
  hsa_memory_copy(sample_ptr, dataptr, data_size);
  free(dataptr);

  hsa_ven_amd_aqlprofile_info_data_t info;
  info.sample_id = se_id;
  info.trace_data.ptr = sample_ptr;
  info.trace_data.size = data_size;

  return info;
}

#endif