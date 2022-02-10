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

#include "pgen/test_pmgr.h"

#include <atomic>

#include "util/test_assert.h"

bool TestPMgr::AddPacket(const packet_t* packet) {
  GetRsrcFactory()->Submit(GetQueue(), packet);
  return true;
}

bool TestPMgr::AddWaitPacket(packet_t* packet, hsa_signal_t signal) {
  // Set packet completion signal
  packet->completion_signal = signal;

  // Submit Dispatch Aql packet
  bool result = AddPacket(packet);

  // Wait for Dispatch packet to complete
  hsa_signal_wait_acquire(signal, HSA_SIGNAL_CONDITION_LT, 1, (uint64_t)-1, HSA_WAIT_STATE_BLOCKED);

  hsa_signal_store_relaxed(signal, 1);

  return result;
}

bool TestPMgr::Setup() {
  // Build Aql Pkts
  const int mode = GetMode();
  if (mode == SETUP_MODE) {
    // Submit Pre-Dispatch Aql packet
    AddWaitPacket(&pre_packet_, packet_signal_);
  }

  Test()->Setup();

  if (mode == SETUP_MODE) {
    // Submit Post-Dispatch Aql packet
    AddWaitPacket(&post_packet_, packet_signal_);

    // Dumping profiling data
    DumpData();
  }

  return true;
}

bool TestPMgr::Run() {
  // Build Aql Pkts
  const int mode = GetMode();
  if (mode == RUN_MODE) {
    // Submit Pre-Dispatch Aql packet
    AddWaitPacket(&pre_packet_, packet_signal_);
  }

  Test()->Run();

  if (mode == RUN_MODE) {
    // Submit Post-Dispatch Aql packet
    AddWaitPacket(&post_packet_, packet_signal_);

    // Dumping profiling data
    DumpData();
  }

  return true;
}

bool TestPMgr::Initialize(int argc, char** argv) {
  TestAql::Initialize(argc, argv);

  hsa_status_t status = hsa_signal_create(1, 0, NULL, &packet_signal_);
  TEST_ASSERT(status == HSA_STATUS_SUCCESS);
  api_ = HsaRsrcFactory::Instance().AqlProfileApi();

  return true;
}

TestPMgr::TestPMgr(TestAql* t) : TestAql(t), api_(NULL) {
  memset(&pre_packet_, 0, sizeof(pre_packet_));
  memset(&post_packet_, 0, sizeof(post_packet_));
  dummy_signal_.handle = 0;
  packet_signal_ = dummy_signal_;
}

TestPMgr::~TestPMgr() {
  if (packet_signal_.handle != 0) {
    hsa_status_t status = hsa_signal_destroy(packet_signal_);
    TEST_ASSERT(status == HSA_STATUS_SUCCESS);
  }
}
