#ifndef INC_AQL_PROFILE_H_
#define INC_AQL_PROFILE_H_

#if 0
// Profiling parameters
// All parameters are generic and if not applicable for a specific
// profile configuration then error status will be returned.
typedef enum {
  // SQTT applicable parameters
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_COMPUTE_UNIT_TARGET = 0,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_VM_ID_MASK = 1,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_MASK = 2,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK = 3,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_TOKEN_MASK2 = 4,
  HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SE_MASK = 5
} hsa_ven_amd_aqlprofile_parameter_name_t;

// Profile attributes
typedef enum {
  HSA_VEN_AMD_AQLPROFILE_INFO_COMMAND_BUFFER_SIZE = 0,  // get_info returns uint32_t value
  HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA_SIZE = 1,        // get_info returns uint32_t value
  HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA = 2,             // get_info returns PMC uint64_t value
                                                        // in info_data object
  HSA_VEN_AMD_AQLPROFILE_INFO_SQTT_DATA = 3,            // get_info returns SQTT buffer ptr/size
                                                        // in info_data object
                                                        //
  HSA_VEN_AMD_AQLPROFILE_INFO_BLOCK_COUNTERS = 4,       // get_info returns number of block counter
  HSA_VEN_AMD_AQLPROFILE_INFO_BLOCK_ID = 5,             // get_info returns block id, instances
                                                        // by name string using _id_query_t
                                                        //
  HSA_VEN_AMD_AQLPROFILE_INFO_ENABLE_CMD = 6,           // get_info returns size/pointer for
                                                        // counters enable command buffer
} hsa_ven_amd_aqlprofile_info_type_t;
#endif

#endif  // INC_AQL_PROFILE_H_
