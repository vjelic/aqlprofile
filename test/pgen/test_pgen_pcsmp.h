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

#ifndef TEST_PGEN_TEST_PGEN_PCSMP_H_
#define TEST_PGEN_TEST_PGEN_PCSMP_H_

#include <cstdint>
#include <iostream>

#include "util/test_assert.h"
#include "pgen/test_pgen.h"

// PC sampling callback data
struct pcsmp_callback_data_t {
  const char* kernel_name;     // sampled kernel name
  void* data_buffer;           // host buffer for tracing data
  uint64_t id;                 // sample id
  uint64_t cycle;              // sample cycle
  uint64_t pc;                 // sample PC
};

hsa_status_t TestPGenPcsmpCallback(hsa_ven_amd_aqlprofile_info_type_t info_type,
                                  hsa_ven_amd_aqlprofile_info_data_t* info_data,
                                  void* callback_data) {
  hsa_status_t status = HSA_STATUS_SUCCESS;
  pcsmp_callback_data_t* pcsmp_data =
    reinterpret_cast<pcsmp_callback_data_t*>(callback_data);
  std::cout <<
    "id(" << std::dec << pcsmp_data->id <<
    ") cycle(" << std::dec << pcsmp_data->cycle <<
    ") pc(0x" << std::hex << pcsmp_data->pc <<
    ") name(\"" << pcsmp_data->kernel_name <<
    "\")" << std::dec << std::endl << std::flush;
  return status;
}

// Class implements SQTT profiling
class TestPGenPcsmp : public TestPGenSqtt {
 public:
  explicit TestPGenPcsmp(TestAql* t) : TestPGenSqtt(t) {
    std::clog << "Test: PGen PC sampling" << std::endl;
  }

  bool DumpData() {
    std::clog << "TestPGenPcsmp::DumpData :" << std::endl;

    TEST_ASSERT(profile_.event_count == 0);
    profile_.event_count = UINT32_MAX;
    pcsmp_callback_data_t data{};
    data.kernel_name = Name();

    // allocate host space
    void* sys_buf = GetRsrcFactory()->AllocateSysMemory(GetAgentInfo(), TestPGenSqtt::buffer_size_);
    TEST_ASSERT(sys_buf != NULL);
    if (sys_buf == NULL) return false;
    data.data_buffer = sys_buf;

    api_->hsa_ven_amd_aqlprofile_iterate_data(&profile_, TestPGenPcsmpCallback, &data);

    return true;
  }
};

#endif  // TEST_PGEN_TEST_PGEN_PCSMP_H_
