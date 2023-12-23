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

#ifndef TEST_PGEN_TEST_PGEN_SQTT_H_
#define TEST_PGEN_TEST_PGEN_SQTT_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "pgen/test_pgen.h"
#include "util/test_assert.h"
#include "parser_test.hpp"

typedef std::vector<hsa_ven_amd_aqlprofile_info_data_t> callback_data_t;

hsa_status_t TestPGenSqttCallback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                  hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                  void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  reinterpret_cast<callback_data_t*>(callback_data)->push_back(*info_data);
  return status;
}

// Class implements SQTT profiling
class TestPGenSqtt : public TestPGen {
 public:
  explicit TestPGenSqtt(TestAql* t) : TestPGen(t) {
    std::clog << "Test: PGen SQTT" << std::endl;
    profile_ = hsa_ven_amd_aqlprofile_profile_t{};
  }

  bool Initialize(int arg_cnt, char** arg_list) {
    if (!TestPMgr::Initialize(arg_cnt, arg_list)) return false;

    hsa_status_t status;
    hsa_agent_t agent;
    uint32_t command_buffer_size;

    // GPU identificator
    agent = GetAgentInfo()->dev_id;

    // Initialization of the profile
    memset(&profile_, 0, sizeof(profile_));
    profile_.agent = agent;
    profile_.type = HSA_VEN_AMD_AQLPROFILE_EVENT_TYPE_TRACE;

    // Profile buffers attributes
    status = api_->hsa_ven_amd_aqlprofile_get_info(
        &profile_, HSA_VEN_AMD_AQLPROFILE_INFO_COMMAND_BUFFER_SIZE, &command_buffer_size);
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);

    // Application is allocating the command buffer
    // AllocateSystem(buffer_alignment_, command_buffer_size,
    //                MODE_HOST_ACC|MODE_DEV_ACC|MODE_EXEC_DATA)
    profile_.command_buffer.ptr =
        GetRsrcFactory()->AllocateCmdMemory(GetAgentInfo(), command_buffer_size);
    TEST_ASSERT(profile_.command_buffer.ptr != NULL);
    profile_.command_buffer.size = command_buffer_size;
    TEST_ASSERT((reinterpret_cast<uintptr_t>(profile_.command_buffer.ptr) & buffer_bitmask) == 0);

    this->parameters = {
      {HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_COMPUTE_UNIT_TARGET, 1},
      {HSA_VEN_AMD_AQLPROFILE_PARAMETER_NAME_SE_MASK, 0x55555555},
      {static_cast<hsa_ven_amd_aqlprofile_parameter_name_t>(8), 0x1},
    };
    profile_.parameters = parameters.data();
    profile_.parameter_count = parameters.size();

    // Application is allocating the output buffer
    // AllocateLocal(buffer_alignment_, buffer_size_, MODE_DEV_ACC)
    profile_.output_buffer.ptr = GetRsrcFactory()->AllocateLocalMemory(GetAgentInfo(), buffer_size_);
    profile_.output_buffer.size = buffer_size_;

    TEST_ASSERT(profile_.output_buffer.ptr != NULL);
    TEST_ASSERT((reinterpret_cast<uintptr_t>(profile_.output_buffer.ptr) & buffer_bitmask) == 0);

    // Populating the AQL start packet
    status = api_->hsa_ven_amd_aqlprofile_start(&profile_, PrePacket());
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);
    if (status != HSA_STATUS_SUCCESS) return false;

    // Populating the AQL stop packet
    status = api_->hsa_ven_amd_aqlprofile_stop(&profile_, PostPacket());
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);

    return (status == HSA_STATUS_SUCCESS);
  }

  int GetMode() { return RUN_MODE; }
  bool BuildPackets() { return true; }

  bool DumpData() {
#ifndef AMD_AQLPROFILE_SQTT_NPI
    TEST_ASSERT(true);
    return true;
#endif

    std::clog << "TestPGenSqtt::DumpData :" << std::endl;

    bool bSomeSECollected = false;
    bool bSomeSEFailed = false;
    callback_data_t data;
    api_->hsa_ven_amd_aqlprofile_iterate_data(&profile_, TestPGenSqttCallback, &data);
    for (callback_data_t::iterator it = data.begin(); it != data.end(); ++it) {
      std::cout << "sample(" << std::dec << it->sample_id << ") size(" << std::dec
                << it->trace_data.size << ") ptr(" << std::hex << it->trace_data.ptr << ")"
                << std::dec << std::endl;

      if (it->trace_data.size == 0) continue;
      void* sys_buf = GetRsrcFactory()->AllocateSysMemory(GetAgentInfo(), it->trace_data.size);
      TEST_ASSERT(sys_buf != NULL);
      if (sys_buf == NULL) return false;

      hsa_status_t status = hsa_memory_copy(sys_buf, it->trace_data.ptr, it->trace_data.size);
      TEST_ASSERT(status == HSA_STATUS_SUCCESS);
      if (status != HSA_STATUS_SUCCESS) return false;

      {
        std::ofstream out_file("sqtt_dump_" + std::to_string(it->sample_id) + ".txt");
        if (out_file.is_open())
        {
          out_file << std::hex;

          // Write the buffer in terms of shorts (16 bits)
          uint16_t* trace_data = (uint16_t*)sys_buf;
          for (unsigned i = 0; i < (it->trace_data.size / sizeof(uint16_t)); ++i)
            out_file << std::setw(4) << std::setfill('0') << trace_data[i] << "\n";
          out_file << std::dec;
        }
      }
      {
        std::ofstream out_file("sqtt_dump_" + std::to_string(it->sample_id) + ".bin", std::ios::binary);
        if (out_file.is_open())
          out_file.write(static_cast<const char*>(sys_buf), it->trace_data.size);
      }

      try {
        bSomeSECollected |= test_buffer(static_cast<const char*>(sys_buf), it->trace_data.size);
      } catch(std::string& s) {
          std::cerr << "SQTT Parser for " << it->sample_id << " string test error: " << s << std::endl;
          bSomeSEFailed = true;
      } catch(const char* s) {
          std::cerr << "SQTT Parser for " << it->sample_id << " string test error: " << s << std::endl;
          bSomeSEFailed = true;
      } catch(std::exception& e) {
          std::cerr << "SQTT Parser for " << it->sample_id << " generic test error. " << e.what() << std::endl;
          bSomeSEFailed = true;
      }
    }
    TEST_ASSERT(bSomeSECollected == true);
    TEST_ASSERT(bSomeSEFailed == false);

    return true;
  }

  static const uint32_t buffer_alignment_ = 0x1000;  // 4K
  static const uint32_t buffer_bitmask = buffer_alignment_ - 1;  // 0xFFF
  static const uint32_t buffer_size_ = 0x2000000;    // 32M

  std::vector<hsa_ven_amd_aqlprofile_parameter_t> parameters;
  hsa_ven_amd_aqlprofile_profile_t profile_;
};

#endif  // TEST_PGEN_TEST_PGEN_SQTT_H_
