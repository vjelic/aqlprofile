#ifndef _GFX8_BLOCKINFO_H_
#define _GFX8_BLOCKINFO_H_

// MAX Number of block instances for VOLCANIC ISLANDS (From Fiji)
// Values are found here //gfxip/gfx8/main/src/meta/features/variant/Fiji/album.dj

// @brief Number of block instances.

// We index per SE and instance
#define VI_NUM_CB 4  // CB has 4 instances per SE
#define VI_NUM_DB 4  // DB has 4 instances per SE

// For TA, TD and TCP, the values below are the same as the number of CUs
// per SH. We index per SE and instance
#define VI_NUM_TA 16   // TA has 11 instances
#define VI_NUM_TD 16   // TD has 11 instances
#define VI_NUM_TCP 16  // TCP has 11 instances

// These values are per chip, we index directly per instance
#define VI_NUM_TCA 2   // TCA has 2 instances per chip
#define VI_NUM_TCC 16  // TCC has 16 instances per chip
#define VI_NUM_SDMA 2  // There are two SDMA blocks on VI, exposed as 2
                       // instances here

// Number of counter registers per block for volcanic islands
#define VI_COUNTER_NUM_PER_DRM 2
#define VI_COUNTER_NUM_PER_DRMDMA 2
#define VI_COUNTER_NUM_PER_IH 2
#define VI_COUNTER_NUM_PER_SRBM 2
#define VI_COUNTER_NUM_PER_CB 4
#define VI_COUNTER_NUM_PER_CPF 2
#define VI_COUNTER_NUM_PER_DB 4
#define VI_COUNTER_NUM_PER_GRBM 2
#define VI_COUNTER_NUM_PER_GRBMSE 4
#define VI_COUNTER_NUM_PER_PA_SU 4
#define VI_COUNTER_NUM_PER_RLC 2
#define VI_COUNTER_NUM_PER_PA_SC 8
#define VI_COUNTER_NUM_PER_SPI 6  // [Shucai: To do: double check the value]
#define VI_COUNTER_NUM_PER_SQ 16
#define VI_COUNTER_NUM_PER_SX 4
#define VI_COUNTER_NUM_PER_TA 2
#define VI_COUNTER_NUM_PER_TCA 4
#define VI_COUNTER_NUM_PER_TCC 4
#define VI_COUNTER_NUM_PER_TD 2  // [Shucai: To do: double check the value]
#define VI_COUNTER_NUM_PER_TCP 4
#define VI_COUNTER_NUM_PER_GDS 4
#define VI_COUNTER_NUM_PER_VGT 4
#define VI_COUNTER_NUM_PER_IA 4
#define VI_COUNTER_NUM_PER_MC 4
#define VI_COUNTER_NUM_PER_TCS 4
#define VI_COUNTER_NUM_PER_WD 4
#define VI_COUNTER_NUM_PER_CPG 2
#define VI_COUNTER_NUM_PER_CPC 2
#define VI_COUNTER_NUM_PER_VM 1
#define VI_COUNTER_NUM_PER_VM_MD 1
#define VI_COUNTER_NUM_PER_PIPESTATS 12

#define VI_MAX_NUM_SHADER_ENGINES 1

// Enumeration of VI hardware counter blocks
typedef enum HsaViCounterBlockId {
  kHsaViCounterBlockIdCb = 0,
  kHsaViCounterBlockIdCpf,
  kHsaViCounterBlockIdDb,
  kHsaViCounterBlockIdGrbm,
  kHsaViCounterBlockIdGrbmSe,
  kHsaViCounterBlockIdPaSu,
  kHsaViCounterBlockIdPaSc,
  kHsaViCounterBlockIdSpi,
  kHsaViCounterBlockIdSq,
  kHsaViCounterBlockIdSqEs,
  kHsaViCounterBlockIdSqGs,
  kHsaViCounterBlockIdSqVs,
  kHsaViCounterBlockIdSqPs,
  kHsaViCounterBlockIdSqLs,
  kHsaViCounterBlockIdSqHs,
  kHsaViCounterBlockIdSqCs,
  kHsaViCounterBlockIdSx,
  kHsaViCounterBlockIdTa,
  kHsaViCounterBlockIdTca,
  kHsaViCounterBlockIdTcc,
  kHsaViCounterBlockIdTd,
  kHsaViCounterBlockIdTcp,
  kHsaViCounterBlockIdGds,
  kHsaViCounterBlockIdVgt,
  kHsaViCounterBlockIdIa,
  kHsaViCounterBlockIdMc,
  kHsaViCounterBlockIdSrbm,
  kHsaViCounterBlockIdTcs,
  kHsaViCounterBlockIdWd,
  kHsaViCounterBlockIdCpg,
  kHsaViCounterBlockIdCpc,

  // Counters retrieved by KFD
  kHsaViCounterBlockIdIommuV2,
  kHsaViCounterBlockIdKernelDriver,

  kHsaViCounterBlockIdCpPipeStats,
  kHsaViCounterBlockIdHwInfo,
  kHsaViCounterBlockIdBlocksFirst = kHsaViCounterBlockIdCb,
  kHsaViCounterBlockIdBlocksLast = kHsaViCounterBlockIdHwInfo
} HsaViCounterBlockId;

#endif  // _GFX8_BLOCKINFO_H_
