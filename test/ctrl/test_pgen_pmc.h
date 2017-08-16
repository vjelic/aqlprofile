/******************************************************************************

Copyright ©2013 Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef _TEST_PGEN_PMC_H_
#define _TEST_PGEN_PMC_H_

#include "test_assert.h"
#include "test_pgen.h"

#include <list>
#include <vector>

hsa_status_t TestPGenPMC_Callback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                  hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                  void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  typedef std::vector<hsa_ven_amd_aqlprofile_info_data_t> passed_data_t;
  reinterpret_cast<passed_data_t*>(callback_data)->push_back(*info_data);
  return status;
}

// Class implements PMC profiling
class TestPGenPMC : public TestPGen {
  const static uint32_t buffer_alignment = 0x1000;  // 4K

  hsa_agent_t agent;
  hsa_ven_amd_aqlprofile_profile_t profile;
  hsa_ven_amd_aqlprofile_event_t* events;

  bool buildPackets() { return true; }

  bool dumpData() {
    std::clog << "TestPGenPMC::dumpData :" << std::endl;

    typedef std::vector<hsa_ven_amd_aqlprofile_info_data_t> callback_data_t;

    callback_data_t data;
    api.hsa_ven_amd_aqlprofile_iterate_data(&profile, TestPGenPMC_Callback, &data);
    for (callback_data_t::iterator it = data.begin(); it != data.end(); ++it) {
      if (it->pmc_data.result)
        std::cout << dec << "event(block(" << it->pmc_data.event.block_name << "_"
                << it->pmc_data.event.block_index << "), id(" << it->pmc_data.event.counter_id
                << ")), sample(" << it->sample_id << "), result(" << it->pmc_data.result << ")"
                << std::endl;
    }

    return true;
  }

 public:
  explicit TestPGenPMC(TestAql* t) : TestPGen(t) { std::clog << "Test: PGen PMC" << std::endl; }

  bool initialize(int arg_cnt, char** arg_list) {
    std::vector<hsa_ven_amd_aqlprofile_event_t> event_vec;

    if (arg_cnt == 4) {
      const hsa_ven_amd_aqlprofile_event_t event = {
        static_cast<hsa_ven_amd_aqlprofile_block_name_t>(atoi(arg_list[1])), atoi(arg_list[2]), atoi(arg_list[3])};
      event_vec.push_back(event);
      arg_cnt -= 3;
      arg_list += 3;
    }
    else
    {
      // Set the events list
      const hsa_ven_amd_aqlprofile_event_t events_arr[] = {
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 4 /*WAVES*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 14 /*ITEMS*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 47 /*WAVE_READY*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 1 /*CYCLE*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 3 /*REQ*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 22 /*WRITEBACK*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 0 /*ALWAYS_COUNT*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 8 /*ME1_STALL_WAIT_ON_RCIU_READ*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 1 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SPI, 0, 20},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 0 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 1 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 2 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA, 0, 0 /**/},
//      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 0 /**/},
      };
      event_vec.insert(event_vec.end(), events_arr,
                       events_arr + (sizeof(events_arr) / sizeof(hsa_ven_amd_aqlprofile_event_t)));
    }

    if (!TestPMgr::initialize(arg_cnt, arg_list)) return false;

    hsa_status_t status;
    hsa_agent_t agent;
    uint32_t command_buffer_alignment;
    uint32_t command_buffer_size;
    uint32_t output_buffer_alignment;
    uint32_t output_buffer_size;

    // GPU identificator
    agent = getAgentInfo()->dev_id;

    // Preparing events vector
    std::vector<hsa_ven_amd_aqlprofile_event_t> event_vec_filtered;
    for (auto it = event_vec.begin(); it != event_vec.end(); ++it) {
      bool result = false;
      api.hsa_ven_amd_aqlprofile_validate_event(agent, &(*it), &result);
      if (!result) {
        std::cerr << "Bad event: block (" << it->block_name << "_" << it->block_index << ") id (" << it->counter_id << ")" << std::endl;
      } else {
        event_vec_filtered.push_back(*it);
      }
    }
    const size_t event_count = event_vec_filtered.size();
    events = new hsa_ven_amd_aqlprofile_event_t[event_count];
    for (uint32_t i = 0; i < event_count; ++i) {
      events[i] = event_vec_filtered.at(i);
    }

    if (!event_count) return false;

    // Initialization the profile
    memset(&profile, 0, sizeof(profile));
    profile.agent = agent;
    profile.type = HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_PMC;

    // Set enabled events list
    profile.events = events;
    profile.event_count = event_count;

    // Profile buffers attributes
    command_buffer_alignment = buffer_alignment;
    status = api.hsa_ven_amd_aqlprofile_get_info(
        &profile, HSA_VEN_AMD_AQLPROFILE_INFO_COMMAND_BUFFER_SIZE, &command_buffer_size);
    if (status != HSA_STATUS_SUCCESS) {
      const char* str = "";
      api.hsa_ven_amd_aqlprofile_error_string(&str);
      std::cerr << "aqlprofile err: " << str << std::endl;
    }
    test_assert(status == HSA_STATUS_SUCCESS);

    output_buffer_alignment = buffer_alignment;
    status = api.hsa_ven_amd_aqlprofile_get_info(
        &profile, HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA_SIZE, &output_buffer_size);
    test_assert(status == HSA_STATUS_SUCCESS);

    // Application is allocating the command buffer
    // Allocate(command_buffer_alignment, command_buffer_size,
    //          MODE_HOST_ACC|MODE_DEV_ACC|MODE_EXEC_DATA)
    profile.command_buffer.ptr =
        getRsrcFactory()->AllocateSysMemory(getAgentInfo(), command_buffer_size);
    profile.command_buffer.size = command_buffer_size;

    // Application is allocating the output buffer
    // Allocate(output_buffer_alignment, output_buffer_size,
    //          MODE_HOST_ACC|MODE_DEV_ACC)
    profile.output_buffer.ptr =
        getRsrcFactory()->AllocateSysMemory(getAgentInfo(), output_buffer_size);
    profile.output_buffer.size = output_buffer_size;
    memset(profile.output_buffer.ptr, 0x77, output_buffer_size);

    // Populating the AQL start packet
    status = api.hsa_ven_amd_aqlprofile_start(&profile, PrePacket());
    if (status != HSA_STATUS_SUCCESS) {
      const char* str;
      api.hsa_ven_amd_aqlprofile_error_string(&str);
      std::cerr << "aqlprofile err: " << str << std::endl;
    }
    test_assert(status == HSA_STATUS_SUCCESS);
    if (status != HSA_STATUS_SUCCESS) return false;

    // Populating the AQL stop packet
    status = api.hsa_ven_amd_aqlprofile_stop(&profile, PostPacket());
    test_assert(status == HSA_STATUS_SUCCESS);

    return (status == HSA_STATUS_SUCCESS);
  }
};

#endif  // _TEST_PGEN_PMC_H_
