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

#include <hsakmt.h>
#include <stdlib.h>
#include <string>
#include <thread>

#include "ctrl/run_kernel.h"
#include "pgen/test_pgen_pcsmp.h"
#include "pgen/test_pgen_pmc.h"
#include "pgen/test_pgen_sqtt.h"
#include "pgen/test_pgen_spm.h"
#include "simple_convolution/simple_convolution.h"

const int argv_pmc_size = 32;
unsigned argc_pmc = 0;
char* argv_arr = NULL;
char** argv_pmc = NULL;

int get_gpu_node_id() {
  int gpu_node = - 1;

#if 0
  // find a valid gpu node from /sys/class/kfd/kfd/topology/nodes
  std::string path = "/sys/class/kfd/kfd/topology/nodes";
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(path.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string dir = ent->d_name;

      if (dir.find_first_not_of("0123456789") == std::string::npos) {
        std::string file = path + "/" + ent->d_name + "/gpu_id";
        std::ifstream infile(file);
        int id;

        infile >> id;
        if (id != 0) {
          gpu_node = atoi(ent->d_name);
          break;
        }
      }
    }
    closedir(dir);
  }
#else
  HsaSystemProperties m_SystemProperties;
  memset(&m_SystemProperties, 0, sizeof(m_SystemProperties));

  HSAKMT_STATUS status = hsaKmtAcquireSystemProperties(&m_SystemProperties);
  if (status != HSAKMT_STATUS_SUCCESS) {
    std::cerr << "Error in hsaKmtAcquireSystemProperties"<< std::endl;
    return 1;
  }

  // tranverse all CPU and GPU nodes and break when a GPU node is found
  for (unsigned i = 0; i < m_SystemProperties.NumNodes; ++i) {
    HsaNodeProperties nodeProperties;
    memset(&nodeProperties, 0, sizeof(HsaNodeProperties));

    status = hsaKmtGetNodeProperties(i, &nodeProperties);
    if (status != HSAKMT_STATUS_SUCCESS) {
      std::cerr << "Error in hsaKmtAcquireSystemProperties"<< std::endl;
      break;
    } else if (nodeProperties.NumFComputeCores) {
      gpu_node = i;
      break;
    }
  }
#endif

  printf("GPU node id(%d)\n", gpu_node);
  return gpu_node;
}

char** pmc_argv(unsigned argc, const hsa_ven_amd_aqlprofile_event_t* events) {
  if (argc > argc_pmc) {
    argc_pmc = argc;
    argv_arr = reinterpret_cast<char*>(realloc(argv_arr, argc_pmc * argv_pmc_size));
    if (argv_pmc) delete argv_pmc;
    argv_pmc = new char*[argc + 1];
  }
  for (unsigned i = 0; i < argc; ++i) {
    char* argv_ptr = argv_arr + (i * argv_pmc_size);
    snprintf(argv_ptr, argv_pmc_size, "%d:%d:%d", events[i].block_name, events[i].block_index,
             events[i].counter_id);
    argv_pmc[i] = argv_ptr;
  }
  argv_pmc[argc] = NULL;
  return argv_pmc;
}

typedef char** pf_pmc_argv(unsigned argc, const hsa_ven_amd_aqlprofile_event_t* events);

void thread_kernel(bool* ret_val, pf_pmc_argv pmc_argv, int events_count, const hsa_ven_amd_aqlprofile_event_t* events) {
  *ret_val = RunKernel<SimpleConvolution, TestPGenSpm>(events_count,
                                                       pmc_argv(events_count, events));
}

void thread_data() {
  // call ioctl to get sample data from SPM
  uint16_t sample_data[256];
  for (int i = 0; i < 256; ++ i)
    sample_data[i] = i;

  int len = 256; // ioctl(int fd, int request, ...);

  // check for possible errors

  // save sample data to a binary file
  FILE * file = fopen("example.txt","wb");
  fwrite(sample_data, 1, len, file);
  fclose(file);
}

int main(int argc, char* argv[]) {
  bool ret_val = false;
  const bool pmc_enable = (getenv("AQLPROFILE_PMC") != NULL);
  const bool pmc_priv_enable = (getenv("AQLPROFILE_PMC_PRIV") != NULL);
  const bool sdma_enable = (getenv("AQLPROFILE_SDMA") != NULL);
  const bool sqtt_enable = (getenv("AQLPROFILE_SQTT") != NULL);
  const bool pcsmp_enable = (getenv("AQLPROFILE_PCSMP") != NULL);
  const bool scan_enable = (getenv("AQLPROFILE_SCAN") != NULL);
  const bool trace_enable = (getenv("AQLPROFILE_TRACE") != NULL);
  const bool spm_enable = (getenv("AQLPROFILE_SPM") != NULL);
  int gpu_node_id = -1;

  int scan_step = 1;
  const char* step_env = getenv("AQLPROFILE_SCAN_STEP");
  if (step_env!= NULL) {
    int step = atoi(step_env);
    if (step <= 0) {
      std::cerr << "Error in setting environment variable AQLPROFILE_SCAN_STEP=" << step_env
                << ", it should be greater than or equal to 1."<< std::endl;
      return 1;
    }
    scan_step = step;
  }

  if (!trace_enable) {
    std::clog.rdbuf(NULL);
  }
  if (scan_enable) {
    std::cerr.rdbuf(NULL);
  }

  //{
  //  hsa_status_t status = hsa_init();
  //  CHECK_STATUS("Error in hsa_init", status);
  //}

  if (spm_enable) {
    {
      hsa_status_t status = hsa_init();
      CHECK_STATUS("Error in hsa_init", status);
    }
    gpu_node_id = get_gpu_node_id();
    if (gpu_node_id == -1) {
      std::cerr << "Error in get_gpu_node_id()" << std::endl;
      return 1;
    }
    HSAKMT_STATUS status = hsaKmtEnableDebugTrap(gpu_node_id, INVALID_QUEUEID);
    if (status != HSAKMT_STATUS_SUCCESS) {
      std::cerr << "Error in enabling debug trap for NodeId 32"<< std::endl;
      return 1;
    }
  }

  TestHsa::HsaInstantiate();

  const hsa_ven_amd_aqlprofile_event_t * events_arr;

  // Run simple convolution test
  if (pmc_enable) {
    if (argc > 1) {
      ret_val = RunKernel<SimpleConvolution, TestPGenPmc<RUN_MODE> >(argc - 1, argv + 1);
    } else if (!scan_enable) {
      int events_count = 0;
      if (TestHsa::HsaAgentName() == "gfx9") {
        const hsa_ven_amd_aqlprofile_event_t events_arr1[] = {
          //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 2 /*CYCLES*/},
          //{HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 3 /*BUSY_CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 4 /*WAVES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 14 /*ITEMS*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 47 /*WAVE_READY*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 1 /*CYCLE*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 3 /*REQ*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 22 /*WRITEBACK*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCP, 1, 2 /*CORE_REG_SCLK_VLD*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 0 /*ALWAYS_COUNT*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 8 /*ME1_STALL_WAIT_ON_RCIU_READ*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPF, 0, 0 /*ALWAYS_COUNT*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GDS, 0, 0 /*DS_ADDR_CONFL*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GRBM, 0, 0 /*COUNT*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GRBMSE, 0, 0 /*COUNT*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SPI, 0, 47 /*CSN_WINDOW_VALID*/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQCS, 0, 0 /*???*/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SRBM, 0, 0 /*???*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SX, 0, 0 /*PA_IDLE_CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TA, 0, 1 /*SH_FIFO_BUSY*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TA, 0, 2 /*SH_FIFO_CMD_BUSY*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCA, 0, 1 /*CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 0, 1 /*CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCP, 0, 2 /*CORE_REG_SCLK_VLD*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TD, 0, 1 /*TD_BUSY*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TD, 0, 2 /*INPUT_BUSY*/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCARB, 0, 0 /**/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCHUB, 0, 0 /**/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCMCBVM, 0, 0 /**/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCSEQ, 0, 0 /**/},
          // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 0 /**/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0 /*CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA, 0, 0 /*CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 0 /*???CYCLES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0}, /*CYCLE*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 2}, /*BANK0_PTE_CACHE_HITS*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 7}, /*PDE0_CACHE_REQS*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 8}, /*PDE0_CACHE_HITS*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 13}, /*BANK0_4K_PTE_CACHE_MISSES*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 14}, /*BANK0_BIGK_PTE_CACHE_HITS*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 15}, /*BANK0_BIGK_PTE_CACHE_MISSES*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0}, /*CYCLE*/
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 2}, /*BANK0_REQUESTS*/
        };
        events_count = sizeof(events_arr1) / sizeof(hsa_ven_amd_aqlprofile_event_t);
        events_arr = events_arr1;
      } else {
        const hsa_ven_amd_aqlprofile_event_t events_arr1[] = {
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 4 /*WAVES*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 14 /*ITEMS*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 47 /*WAVE_READY*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 1 /*CYCLE*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 3 /*REQS*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 22 /*WRITEBACK*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 0 /*ALWAYS_COUNT*/},
          {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 8 /*ME1_STALL_WAIT_ON_RCIU_READ*/},
        };
        events_count = sizeof(events_arr1) / sizeof(hsa_ven_amd_aqlprofile_event_t);
        events_arr = events_arr1;
      }
      ret_val = RunKernel<SimpleConvolution, TestPGenPmc<RUN_MODE> >(events_count,
                                                          pmc_argv(events_count, events_arr));
    } else {
      const int block_index_max = 16;
      const int event_id_max = 128;
      for (unsigned i = 0; i < HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER; ++i) {
        for (unsigned j = 0; j < block_index_max; ++j) {
          for (unsigned k = 0; k <= event_id_max; k += scan_step) {
            fflush(stdout);
            fprintf(stderr, " %d %d %d                 \r", i, j, k);
            fflush(stderr);
            hsa_ven_amd_aqlprofile_event_t event = {(hsa_ven_amd_aqlprofile_block_name_t)i, j, k};
            if (!RunKernel<SimpleConvolution, TestPGenPmc<RUN_MODE> >(1, pmc_argv(1, &event))) {
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
  } else if (sdma_enable) {
    int events_count = 0;
    const hsa_ven_amd_aqlprofile_event_t events_sdma[] = {
      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SDMA, 0, 17 /*MC_WR_COUNT*/},
      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SDMA, 0, 19 /*MC_RD_COUNT*/},
      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SDMA, 1, 17 /*MC_WR_COUNT*/},
      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SDMA, 1, 19 /*MC_RD_COUNT*/},
    };
    events_count = sizeof(events_sdma) / sizeof(hsa_ven_amd_aqlprofile_event_t);
    ret_val = RunKernel<SimpleConvolution, TestPGenPmc<SETUP_MODE> >(events_count,
                                                                     pmc_argv(events_count, events_sdma));
  } else if (pmc_priv_enable) {
    int events_count = 0;
    if (TestHsa::HsaAgentName() == "gfx9") {
      const hsa_ven_amd_aqlprofile_event_t events_arr1[] = {
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 2}, /*BANK0_PTE_CACHE_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 7}, /*PDE0_CACHE_REQS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 8}, /*PDE0_CACHE_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 13}, /*BANK0_4K_PTE_CACHE_MISSES*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 14}, /*BANK0_BIGK_PTE_CACHE_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 15}, /*BANK0_BIGK_PTE_CACHE_MISSES*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATCL2, 0, 2}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 2}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 7}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 8}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GCEA, 0, 2}, /*REQS_PER_CLIENT_GROUP*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 2}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 7}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 8}, /**/
      };
      events_count = sizeof(events_arr1) / sizeof(hsa_ven_amd_aqlprofile_event_t);
      events_arr = events_arr1;
    } else {
      const hsa_ven_amd_aqlprofile_event_t events_arr1[] = {
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCVML2, 0, 2}, /*BANK0_PTE_CACHE_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCARB, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCARB, 0, 1}, /*CORRECTABLE_GECC_ERR_CNT_CHAN0*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCARB, 0, 2}, /*CORRECTABLE_GECC_ERR_CNT_CHAN1*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCARB, 0, 3}, /*UNCORRECTABLE_GECC_ERR_CNT_CHAN0*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCHUB, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCHUB, 0, 1}, /*ACPG_WRRET_VLD*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCHUB, 0, 2}, /*ACPO_WRRET_VLD*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCHUB, 0, 3}, /*IH_WRRET_VLD*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 1}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 2}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCXBAR, 0, 3}, /**/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCMCBVM, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCMCBVM, 0, 1}, /*TLB0_REQS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCMCBVM, 0, 2}, /*TLB0_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_MCMCBVM, 0, 3}, /*TLB0_MISSES*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 24}, /*ATCL2_L1_REQAS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 25}, /*ATCL2_BANK0_REQS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_ATC, 0, 26}, /*ATCL2_BANK0_HITS*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 0}, /*CYCLE*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 2}, /*RD_REQS_IN*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 7}, /*WR_REQ_QUEUE2_IN*/
        {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_RPB, 0, 8}, /*WR_REQ_QUEUE3_IN*/
      };
      events_count = sizeof(events_arr1) / sizeof(hsa_ven_amd_aqlprofile_event_t);
      events_arr = events_arr1;
    }
    ret_val = RunKernel<SimpleConvolution, TestPGenPmc<RUN_MODE> >(events_count,
                                                                   pmc_argv(events_count, events_arr));
  } else if (sqtt_enable) {
    ret_val = RunKernel<SimpleConvolution, TestPGenSqtt>(argc, argv);
  } else if (pcsmp_enable) {
    ret_val = RunKernel<SimpleConvolution, TestPGenPcsmp>(argc, argv);
  } else if (spm_enable) {
    int events_count = 0;
    const hsa_ven_amd_aqlprofile_event_t events_spm[] = {
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 0 /*NONE*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 2 /*CYCLES*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 3 /*BUSY_CYCLES*/},
      {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 4  /*WAVES*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 14 /*ITEMS*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SQ, 0, 47 /*WAVE_READY*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_SPI, 0, 47 /*CSN_WINDOW_VALID*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TA, 0, 1 /*SH_FIFO_BUSY*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TD, 0, 1 /*TD_BUSY*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 3 /*REQ*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 22 /*WRITEBACK*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCC, 2, 1 /*CYCLE*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_TCP, 1, 2 /*CORE_REG_SCLK_VLD*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPC, 0, 0 /*ALWAYS_COUNT*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_CPF, 0, 0 /*ALWAYS_COUNT*/},
      // {HSA_VEN_AMD_AQLPROFILE_BLOCK_NAME_GDS, 0, 0 /*DS_ADDR_CONFL*/},
    };
    events_count = sizeof(events_spm) / sizeof(hsa_ven_amd_aqlprofile_event_t);
    //ret_val = RunKernel<SimpleConvolution, TestPGenSpm>(events_count,
    //                                                    pmc_argv(events_count, events_spm));
    std::thread k_thread(thread_kernel, &ret_val, pmc_argv, events_count, events_spm);

    // buffer setup
    std::thread d_thread(thread_data);

    k_thread.join();
    d_thread.join();

    HSAKMT_STATUS status = hsaKmtDisableDebugTrap(gpu_node_id);
    if (status != HSAKMT_STATUS_SUCCESS) {
      std::cerr << "Error in disabling debug trap for NodeId 0"<< std::endl;
      return 1;
    }

    // SPM data analysis: need to change command dependent on binary vs text sample files
    // The 'da_16b.py' script is checking the first SPM counter data to match expected value provided by the option '-e'
    std::string command = "python3 da_16b.py -e 16 spm_dump_0.txt";

    int command_status = system(command.c_str());

    if (command_status == -1)
      std::cerr << "Cannot run \"" << command << "\"" << std::endl;
    else if (command_status == 0)
      std::cout << "SPM test passed!" << std::endl;
    else
      std::cerr << "SPM test failed!" << std::endl;
  } else {
    ret_val = RunKernel<SimpleConvolution, TestAql>(argc, argv);
  }
  TestHsa::HsaShutdown();

  return (ret_val) ? 0 : 1;
}
