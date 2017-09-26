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

#include <stdlib.h>

#include "ctrl/run_kernel.h"
#include "ctrl/test_pgen_pmc.h"
#include "ctrl/test_pgen_sqtt.h"
#include "simple_convolution/simple_convolution.h"

const int argv_pmc_size = 32;
unsigned argc_pmc = 0;
char* argv_arr = NULL;
char** argv_pmc = NULL;

char** pmc_argv(unsigned argc, const hsa_ven_amd_aqlprofile_event_t *events) {
  if (argc > argc_pmc) {
    argc_pmc = argc;
    argv_arr = reinterpret_cast<char*>(realloc(argv_arr, argc_pmc * argv_pmc_size));
    if (argv_pmc) delete argv_pmc;
    argv_pmc = new char*[argc + 1];
  }
  for (unsigned i = 0; i < argc; ++i) {
    char* argv_ptr = argv_arr + (i * argv_pmc_size);
    snprintf(argv_ptr, argv_pmc_size, "%d:%d:%d", events[i].block_name, events[i].block_index, events[i].counter_id);
    argv_pmc[i] = argv_ptr;
  }
  argv_pmc[argc] = NULL;
  return argv_pmc;
}

int main(int argc, char* argv[]) {
  bool ret_val = false;
  const bool pmc_enable = (getenv("AQLPROFILE_PMC") != NULL);
  const bool sqtt_enable = (getenv("AQLPROFILE_SQTT") != NULL);
  const bool scan_enable = (getenv("AQLPROFILE_SCAN") != NULL);
  const bool trace_enable = (getenv("AQLPROFILE_TRACE") != NULL);

  if (!trace_enable) {
    std::clog.rdbuf(NULL);
  }
  if (scan_enable) {
    std::cerr.rdbuf(NULL);
  }

  // Run simple convolution test
  if (pmc_enable) {
    if (argc > 1) {
      ret_val = RunKernel<SimpleConvolution, TestPGenPmc>(argc - 1, argv + 1);
    } else if (!scan_enable) {
      int events_count = 0;
      const hsa_ven_amd_aqlprofile_event_t events_arr1[] = {
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 4 /*WAVES*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 14 /*ITEMS*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 47 /*WAVE_READY*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 1 /*CYCLE*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 3 /*REQ*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 22 /*WRITEBACK*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 0 /*ALWAYS_COUNT*/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 8 /*ME1_STALL_WAIT_ON_RCIU_READ*/},
      };
      events_count = sizeof(events_arr1) / sizeof(hsa_ven_amd_aqlprofile_event_t);
      ret_val = RunKernel<SimpleConvolution, TestPGenPmc>(events_count, pmc_argv(events_count, events_arr1));
#if 0
      const hsa_ven_amd_aqlprofile_event_t events_arr2[] = {
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 0 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 1 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 2 /**/},
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 3 /**/},
      };
      events_count = sizeof(events_arr2) / sizeof(hsa_ven_amd_aqlprofile_event_t);
      ret_val = RunKernel<SimpleConvolution, TestPGenPmc>(events_count, pmc_argv(events_count, events_arr2));
#endif
    } else {
      const int block_index_max = 0;  // 15;
      const int event_id_max = 128;
      for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
        i = HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2;
        for (unsigned j = 0; j <= block_index_max; ++j) {
          for (unsigned k = 0; k <= event_id_max; ++k) {
            fflush(stdout);
            fprintf(stderr, " %d %d %d                 \r", i, j, k);
            fflush(stderr);
            hsa_ven_amd_aqlprofile_event_t event = {(hsa_ven_amd_aqlprofile_block_name_t)i, j, k};
            if (!RunKernel<SimpleConvolution, TestPGenPmc>(1, pmc_argv(1, &event))) {
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
    ret_val = RunKernel<SimpleConvolution, TestPGenSqtt>(argc, argv);
  } else {
    ret_val = RunKernel<SimpleConvolution, TestAql>(argc, argv);
  }

  return (ret_val) ? 0 : 1;
}
