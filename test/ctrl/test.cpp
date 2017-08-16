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

#include "run_kernel.h"
#include "simple_convolution.h"
#include "test_pgen_pmc.h"
#include "test_pgen_sqtt.h"

int main(int argc, char* argv[]) {
  bool ret_val = false;
  const bool pmc_enable = (getenv("AQLPROFILE_PMC") != NULL);
  const bool sqtt_enable = (getenv("AQLPROFILE_SQTT") != NULL);
  const bool scan_enable = (getenv("AQLPROFILE_SCAN") != NULL);
  const bool trace_enable = (getenv("AQLPROFILE_TRACE") != NULL);

  if (!trace_enable) {
    clog.rdbuf(NULL);
  }
  if (scan_enable) {
    cerr.rdbuf(NULL);
  }

  // Run simple convolution test
  if (pmc_enable) {
    if (!scan_enable) {
      ret_val = run_kernel<SimpleConvolution, TestPGenPMC>(argc, argv);
    } else {
      const int block_index_max = 0; // 15;
      const int event_id_max = 128;
      const int argc_pmc = 4;
      const int argv_pmc_size = 5;
      char* argv_pmc[argc_pmc];
      argv_pmc[0] = argv[0];
      for (int i = 1; i < argc_pmc; ++i) {
        argv_pmc[i] = new char[argv_pmc_size];
      }
      for (int i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SRBM;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SPI;
  //      i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MC;
        for (int j = 0; j <= block_index_max; ++j) {
          for (int k = 0; k <= event_id_max; ++k) {
            fflush(stdout);
            fprintf(stderr, " %d %d %d                 \r", i, j, k);
            fflush(stderr);
            snprintf(argv_pmc[1], argv_pmc_size, "%d", i);
            snprintf(argv_pmc[2], argv_pmc_size, "%d", j);
            snprintf(argv_pmc[3], argv_pmc_size, "%d", k);
            if (!run_kernel<SimpleConvolution, TestPGenPMC>(argc_pmc, argv_pmc)) {
              if (k == 0) {
                k = event_id_max + 1;
                if (j == 0) j = block_index_max + 1;
              }
              continue;
            }
          }
        }
      }
    }
  } else if (sqtt_enable) {
    ret_val = run_kernel<SimpleConvolution, TestPGenSQTT>(argc, argv);
  } else {
    ret_val = run_kernel<SimpleConvolution, TestAql>(argc, argv);
  }

  return (ret_val) ? 0 : 1;
}
