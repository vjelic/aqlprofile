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

#ifndef TEST_CTRL_TEST_PGEN_PMC_H_
#define TEST_CTRL_TEST_PGEN_PMC_H_

#include <list>
#include <vector>

#include "ctrl/test_assert.h"
#include "ctrl/test_pgen.h"

hsa_status_t TestPGenPmcCallback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                 hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                 void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  typedef std::vector<hsa_ven_amd_aqlprofile_info_data_t> passed_data_t;
  reinterpret_cast<passed_data_t*>(callback_data)->push_back(*info_data);
  return status;
}

// Class implements PMC profiling
class TestPGenPmc : public TestPGen {
 public:
  explicit TestPGenPmc(TestAql* t) : TestPGen(t) { std::clog << "Test: PGen PMC" << std::endl; }

  bool Initialize(int arg_cnt, char** arg_list) {
    std::vector<hsa_ven_amd_aqlprofile_event_t> event_vec;

    if (arg_cnt == 4) {
      const uint32_t block_id = static_cast<uint32_t>(atoi(arg_list[1]));
      const uint32_t block_index = static_cast<uint32_t>(atoi(arg_list[2]));
      const uint32_t event_id = static_cast<uint32_t>(atoi(arg_list[3]));
      const hsa_ven_amd_aqlprofile_event_t event = {
          static_cast<hsa_ven_amd_aqlprofile_block_name_t>(block_id), block_index, event_id};
      event_vec.push_back(event);
      arg_cnt -= 3;
      arg_list += 3;
    } else {
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
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCSEQ, 1, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCSEQ, 1, 1 /**/},
#if 0
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 4 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 5 /**/},
        {(hsa_ven_amd_aqlprofile_block_name_t)16 /*MC_ARB*/, 0, 0 /**/},
        {(hsa_ven_amd_aqlprofile_block_name_t)22 /*ATC*/, 0, 0 /**/},
        {(hsa_ven_amd_aqlprofile_block_name_t)24 /*GCEA*/, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 1 /**/},
#endif
#if 0
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 0, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 0, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 1, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 1, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 1, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 1, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 2, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 2, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 2, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 2, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 3, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 3, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 3, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC_SEQ, 3, 3 /**/},
#endif
#if 0
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 1 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 1 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 1, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 1, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 1, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 1, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 2, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 2, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 2, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 2, 3 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 3, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 3, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 3, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 3, 3 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SPI, 0, 20},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 1 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RMI, 0, 2 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA, 0, 0 /**/},
        //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 0 /**/},
#endif
      };
      event_vec.insert(event_vec.end(), events_arr,
                       events_arr + (sizeof(events_arr) / sizeof(hsa_ven_amd_aqlprofile_event_t)));
    }

    if (!TestPMgr::Initialize(arg_cnt, arg_list)) return false;

    hsa_status_t status;
    hsa_agent_t agent;
    uint32_t command_buffer_alignment;
    uint32_t command_buffer_size;
    uint32_t output_buffer_alignment;
    uint32_t output_buffer_size;

    // GPU identificator
    agent = GetAgentInfo()->dev_id;

    // Preparing events vector
    std::vector<hsa_ven_amd_aqlprofile_event_t> event_vec_filtered;
    for (auto it = event_vec.begin(); it != event_vec.end(); ++it) {
      bool result = false;
      api_.hsa_ven_amd_aqlprofile_validate_event(agent, &(*it), &result);
      if (!result) {
        std::cerr << "Bad event: block (" << it->block_name << "_" << it->block_index << ") id ("
                  << it->counter_id << ")" << std::endl;
      } else {
        event_vec_filtered.push_back(*it);
      }
    }
    const size_t event_count = event_vec_filtered.size();
    hsa_ven_amd_aqlprofile_event_t* events = new hsa_ven_amd_aqlprofile_event_t[event_count];
    for (uint32_t i = 0; i < event_count; ++i) {
      events[i] = event_vec_filtered.at(i);
    }

    if (!event_count) return false;

    // Initialization the profile
    memset(&profile_, 0, sizeof(profile_));
    profile_.agent = agent;
    profile_.type = HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_PMC;

    // Set enabled events list
    profile_.events = events;
    profile_.event_count = event_count;

    // Profile buffers attributes
    command_buffer_alignment = buffer_alignment_;
    status = api_.hsa_ven_amd_aqlprofile_get_info(
        &profile_, HSA_VEN_AMD_AQLPROFILE_INFO_COMMAND_BUFFER_SIZE, &command_buffer_size);
    if (status != HSA_STATUS_SUCCESS) {
      const char* str = "";
      api_.hsa_ven_amd_aqlprofile_error_string(&str);
      std::cerr << "aqlprofile err: " << str << std::endl;
    }
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);

    output_buffer_alignment = buffer_alignment_;
    status = api_.hsa_ven_amd_aqlprofile_get_info(
        &profile_, HSA_VEN_AMD_AQLPROFILE_INFO_PMC_DATA_SIZE, &output_buffer_size);
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);

    // Application is allocating the command buffer
    // Allocate(command_buffer_alignment, command_buffer_size,
    //          MODE_HOST_ACC|MODE_DEV_ACC|MODE_EXEC_DATA)
    profile_.command_buffer.ptr =
        GetRsrcFactory()->AllocateSysMemory(GetAgentInfo(), command_buffer_size);
    profile_.command_buffer.size = command_buffer_size;
    TEST_ASSERT((reinterpret_cast<uintptr_t>(profile_.command_buffer.ptr) &
                 (command_buffer_alignment - 1)) == 0);

    // Application is allocating the output buffer
    // Allocate(output_buffer_alignment, output_buffer_size,
    //          MODE_HOST_ACC|MODE_DEV_ACC)
    profile_.output_buffer.ptr =
        GetRsrcFactory()->AllocateSysMemory(GetAgentInfo(), output_buffer_size);
    profile_.output_buffer.size = output_buffer_size;
    memset(profile_.output_buffer.ptr, 0x77, output_buffer_size);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(profile_.output_buffer.ptr) &
                 (output_buffer_alignment - 1)) == 0);

    // Populating the AQL start packet
    status = api_.hsa_ven_amd_aqlprofile_start(&profile_, PrePacket());
    if (status != HSA_STATUS_SUCCESS) {
      const char* str;
      api_.hsa_ven_amd_aqlprofile_error_string(&str);
      std::cerr << "aqlprofile err: " << str << std::endl;
    }
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);
    if (status != HSA_STATUS_SUCCESS) return false;

    // Populating the AQL stop packet
    status = api_.hsa_ven_amd_aqlprofile_stop(&profile_, PostPacket());
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);

    return (status == HSA_STATUS_SUCCESS);
  }

 private:
  bool BuildPackets() { return true; }

  bool DumpData() {
    std::clog << "TestPGenPmc::DumpData :" << std::endl;

    typedef std::vector<hsa_ven_amd_aqlprofile_info_data_t> callback_data_t;

    callback_data_t data;
    api_.hsa_ven_amd_aqlprofile_iterate_data(&profile_, TestPGenPmcCallback, &data);
    for (callback_data_t::iterator it = data.begin(); it != data.end(); ++it) {
      //      if (it->pmc_data.result)
      std::cout << std::dec << "event(block(" << it->pmc_data.event.block_name << "_"
                << it->pmc_data.event.block_index << "), id(" << it->pmc_data.event.counter_id
                << ")), sample(" << it->sample_id << "), result(" << it->pmc_data.result << ")"
                << std::endl;
    }

    return true;
  }

  static const uint32_t buffer_alignment_ = 0x1000;  // 4K

  hsa_ven_amd_aqlprofile_profile_t profile_;
};

#endif  // TEST_CTRL_TEST_PGEN_PMC_H_
