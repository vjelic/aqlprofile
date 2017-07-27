#ifndef _DEF_GFX9_BLOCKINFO_H_
#define _DEF_GFX9_BLOCKINFO_H_

// MAX Number of block instances for ARCTIC ISLANDS (From Vega10)
// Values are found here //gfxip/gfx8/main/src/meta/features/variant/Fiji/album.dj

// @brief Number of block instances.

// Number of CB block instances per SE
// and number of Perf Cntrs per CB block
#define AI_NUM_CB 4
#define AI_COUNTER_NUM_PER_CB 4

// Number of DB block instances per SE
// and number of Perf Cntrs per DB block
#define AI_NUM_DB 4
#define AI_COUNTER_NUM_PER_DB 4

// Number of TA block instances per SE
// and number of Perf Cntrs per TA block
#define AI_NUM_TA 16
#define AI_COUNTER_NUM_PER_TA 2

// Number of TD block instances per SE
// and number of Perf Cntrs per TD block
#define AI_NUM_TD 16
#define AI_COUNTER_NUM_PER_TD 2

// Number of TCP block instances per SE
// and number of Perf Cntrs per TCP block
#define AI_NUM_TCP 16
#define AI_COUNTER_NUM_PER_TCP 4

// Number of TCA block instances per chip
// and number of Perf Cntrs per TCA block
#define AI_NUM_TCA 2
#define AI_COUNTER_NUM_PER_TCA 4

// Number of TCC block instances per chip
// and number of Perf Cntrs per TCC block
#define AI_NUM_TCC 16
#define AI_COUNTER_NUM_PER_TCC 4

// Number of SDMA block instances per chip
// and number of Perf Cntrs per SDMA block
#define AI_NUM_SDMA 2

// Number of counter registers per block for arctic islands
#define AI_COUNTER_NUM_PER_DRM 2
#define AI_COUNTER_NUM_PER_DRMDMA 2
#define AI_COUNTER_NUM_PER_IH 2
#define AI_COUNTER_NUM_PER_SRBM 2
#define AI_COUNTER_NUM_PER_CPF 2
#define AI_COUNTER_NUM_PER_GRBM 2
#define AI_COUNTER_NUM_PER_GRBMSE 4
#define AI_COUNTER_NUM_PER_PA_SU 4
#define AI_COUNTER_NUM_PER_RLC 2
#define AI_COUNTER_NUM_PER_PA_SC 8
#define AI_COUNTER_NUM_PER_SPI 6  // [Shucai: To do: double check the value]
#define AI_COUNTER_NUM_PER_SQ 16
#define AI_COUNTER_NUM_PER_SX 4
#define AI_COUNTER_NUM_PER_GDS 4
#define AI_COUNTER_NUM_PER_VGT 4
#define AI_COUNTER_NUM_PER_IA 4
#define AI_COUNTER_NUM_PER_MC 4
#define AI_COUNTER_NUM_PER_TCS 4
#define AI_COUNTER_NUM_PER_WD 4
#define AI_COUNTER_NUM_PER_CPG 2
#define AI_COUNTER_NUM_PER_CPC 2
#define AI_COUNTER_NUM_PER_VM 1
#define AI_COUNTER_NUM_PER_VM_MD 1
#define AI_COUNTER_NUM_PER_PIPESTATS 12

#define AI_MAX_NUM_SHADER_ENGINES 1

// Enumeration of AI hardware counter blocks
typedef enum HsaAiCounterBlockId {
  kHsaAiCounterBlockIdCb = 0,
  // Temp commented out for Vega10
  // kHsaAiCounterBlockIdCpf,
  kHsaAiCounterBlockIdDb,
  kHsaAiCounterBlockIdGrbm,
  kHsaAiCounterBlockIdGrbmSe,
  kHsaAiCounterBlockIdPaSu,
  kHsaAiCounterBlockIdPaSc,
  kHsaAiCounterBlockIdSpi,
  kHsaAiCounterBlockIdSq,
  kHsaAiCounterBlockIdSqGs,
  kHsaAiCounterBlockIdSqVs,
  kHsaAiCounterBlockIdSqPs,
  kHsaAiCounterBlockIdSqHs,
  kHsaAiCounterBlockIdSqCs,
  kHsaAiCounterBlockIdSx,
  kHsaAiCounterBlockIdTa,
  kHsaAiCounterBlockIdTca,
  kHsaAiCounterBlockIdTcc,
  kHsaAiCounterBlockIdTd,
  kHsaAiCounterBlockIdTcp,
  kHsaAiCounterBlockIdGds,
  kHsaAiCounterBlockIdVgt,
  kHsaAiCounterBlockIdIa,
  kHsaAiCounterBlockIdMc,
  // Temp commented out for Vega10
  // kHsaAiCounterBlockIdSrbm,
  kHsaAiCounterBlockIdTcs,
  kHsaAiCounterBlockIdWd,
  // Temp commented out for Vega10
  // kHsaAiCounterBlockIdCpg,
  kHsaAiCounterBlockIdCpc,

  // Counters retrieved by KFD
  kHsaAiCounterBlockIdIommuV2,
  kHsaAiCounterBlockIdKernelDriver,

  kHsaAiCounterBlockIdCpPipeStats,
  kHsaAiCounterBlockIdHwInfo,
  kHsaAiCounterBlockIdBlocksFirst = kHsaAiCounterBlockIdCb,
  kHsaAiCounterBlockIdBlocksLast = kHsaAiCounterBlockIdHwInfo
} HsaAiCounterBlockId;

#endif  //  _DEF_GFX9_BLOCKINFO_H_
