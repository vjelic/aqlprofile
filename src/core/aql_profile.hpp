#ifndef SRC_CORE_AQL_PROFILE_H_
#define SRC_CORE_AQL_PROFILE_H_

#define AMD_AQLPROFILE_SQTT_NPI
#include <hsa/hsa_ven_amd_aqlprofile.h>

#include <iostream>
#include <string>
#include "include/aql_profile_v2.h"

#include "core/aql_profile_exception.h"

namespace pm4_builder {
class CmdBuilder;
}

namespace aql_profile {
typedef hsa_ven_amd_aqlprofile_descriptor_t descriptor_t;
typedef hsa_ven_amd_aqlprofile_profile_t profile_t;
typedef hsa_ven_amd_aqlprofile_info_type_t info_type_t;
typedef hsa_ven_amd_aqlprofile_data_callback_t data_callback_t;
typedef hsa_ext_amd_aql_pm4_packet_t packet_t;
typedef hsa_ven_amd_aqlprofile_event_t event_t;

void PopulateAql(const void* cmd_buffer, uint32_t cmd_size, pm4_builder::CmdBuilder* cmd_writer,
                 packet_t* aql_packet);
void* LegacyAqlAcquire(const packet_t* aql_packet, void* data);
void* LegacyAqlRelease(const packet_t* aql_packet, void* data);
void* LegacyPm4(const packet_t* aql_packet, void* data);

class event_exception : public aql_profile_exc_val<event_t> {
 public:
  event_exception(const std::string& m, const event_t& ev) : aql_profile_exc_val(m, ev) {}
};

}  // namespace aql_profile

namespace aql_profile_v2 {

hsa_status_t _internal_aqlprofile_pmc_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_pmc_data_callback_t callback,
    void* userdata
);

hsa_status_t _internal_aqlprofile_pmc_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_pmc_aql_packets_t* packets,
    aqlprofile_pmc_profile_t profile,
    aqlprofile_memory_alloc_callback_t callback,
    void* userdata
);

hsa_status_t _internal_aqlprofile_att_iterate_data(
    aqlprofile_handle_t handle,
    aqlprofile_att_data_callback_t callback,
    void* data
);

hsa_status_t _internal_aqlprofile_att_create_packets(
    aqlprofile_handle_t* handle,
    aqlprofile_att_control_aql_packets_t packets,
    aqlprofile_att_profile_t profile,
    aqlprofile_memory_alloc_callback_t callback,
    void* userdata
);

}  // namespace aql_profile_v2

static std::ostream& operator<<(std::ostream& os, const aql_profile::event_t& ev) {
    os << "event( block(" << ev.block_name << "." << ev.block_index << "), Id(" << ev.counter_id
      << "))";
    return os;
}

#endif  // SRC_CORE_AQL_PROFILE_H_
