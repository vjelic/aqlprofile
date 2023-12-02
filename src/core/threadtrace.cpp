#include "core/aql_profile.h"

#include <cstdint>
#include <future>
#include <map>
#include <string>
#include <vector>

#include "core/logger.h"
#include "core/pm4_factory.h"
#include "pm4/cmd_builder.h"
#include "pm4/sqtt_builder.h"

#include "core/commandbuffermgr.hpp"

#define PUBLIC_API __attribute__((visibility("default")))

extern "C" {

// Method to populate the provided AQL packet with ATT Markers
PUBLIC_API hsa_status_t
hsa_ven_amd_aqlprofile_att_marker(
  hsa_ven_amd_aqlprofile_profile_t* profile,
  aql_profile::packet_t* aql_marker_packet,
  uint32_t data,
  hsa_ven_amd_aqlprofile_att_marker_channel_t channel
) {
  assert(profile->type == HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE);

  aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(profile);
  pm4_builder::SqttBuilder* sqtt_builder = pm4_factory->GetSqttBuilder();
  pm4_builder::CmdBuilder* cmd_writer = pm4_factory->GetCmdBuilder();
  pm4_builder::CmdBuffer commands;

  // Generate start commands
  auto status = sqtt_builder->InsertMarker(&commands, data, channel);
  if (status != HSA_STATUS_SUCCESS) return status;
  aql_profile::descriptor_t& cmdbuffer = profile->command_buffer;

  size_t cmd_size = cmdbuffer.size;
  cmdbuffer.size = commands.Size();

  if (cmdbuffer.ptr == NULL) return HSA_STATUS_SUCCESS;
  if (cmd_size < commands.Size()) return HSA_STATUS_ERROR_OUT_OF_RESOURCES;

  // Populate stop aql packet
  memcpy(cmdbuffer.ptr, commands.Data(), commands.Size());
  aql_profile::PopulateAql(cmdbuffer.ptr, commands.Size(), cmd_writer, aql_marker_packet);

  return HSA_STATUS_SUCCESS;
}

}  // extern "C"
