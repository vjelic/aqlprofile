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

#ifndef _RUN_KERNEL_H_
#define _RUN_KERNEL_H_

#include "test_assert.h"
#include "test_hsa.h"

template <class Kernel, class Test> bool run_kernel(int argc, char* argv[]) {
  bool ret_val = false;

  // Create test kernel object
  Kernel test_kernel;
  TestAql* test_aql = new TestHSA(&test_kernel);
  test_aql = new Test(test_aql);
  test_assert(test_aql != NULL);
  if (test_aql == NULL) return 1;

  // Initialization of Hsa Runtime
  ret_val = test_aql->initialize(argc, argv);
  if (ret_val == false) {
    std::cerr << "Error in the test initialization" << std::endl;
    //test_assert(ret_val);
    return false;
  }

  // Setup Hsa resources needed for execution
  ret_val = test_aql->setup();
  if (ret_val == false) {
    std::cerr << "Error in creating hsa resources" << std::endl;
    test_assert(ret_val);
    return false;
  }

  // Run test kernel
  ret_val = test_aql->run();
  if (ret_val == false) {
    std::cerr << "Error in running the test kernel" << std::endl;
    test_assert(ret_val);
    return false;
  }

  // Verify the results of the execution
  ret_val = test_aql->verify_results();
  if (ret_val) {
    std::clog << "Test : Passed" << std::endl;
  } else {
    std::clog << "Test : Failed" << std::endl;
  }

  // Print time taken by sample
  test_aql->print_time();

  test_aql->cleanup();
  delete test_aql;

  return ret_val;
}

#endif // _RUN_KERNEL_H_
