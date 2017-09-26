#ifndef _GFX8_BLOCKINFO_H_
#define _GFX8_BLOCKINFO_H_

// Enumeration of Gfx8 hardware counter blocks
enum CounterBlockId {
  CbCounterBlockId,
  CpfCounterBlockId,
  DbCounterBlockId,
  GrbmCounterBlockId,
  GrbmSeCounterBlockId,
  PaSuCounterBlockId,
  PaScCounterBlockId,
  SpiCounterBlockId,
  SqCounterBlockId,
  SqEsCounterBlockId,
  SqGsCounterBlockId,
  SqVsCounterBlockId,
  SqPsCounterBlockId,
  SqLsCounterBlockId,
  SqHsCounterBlockId,
  SqCsCounterBlockId,
  SxCounterBlockId,
  TaCounterBlockId,
  TcaCounterBlockId,
  TccCounterBlockId,
  TdCounterBlockId,
  TcpCounterBlockId,
  GdsCounterBlockId,
  VgtCounterBlockId,
  IaCounterBlockId,
  SrbmCounterBlockId,
  TcsCounterBlockId,
  WdCounterBlockId,
  CpgCounterBlockId,
  CpcCounterBlockId,

  McArbCounterBlockId,
  McHubCounterBlockId,
  McMcbvmCounterBlockId,
  McSeqCounterBlockId,
  McVmL2CounterBlockId,
  McXbarCounterBlockId,

  // Counters retrieved by KFD
  IommuV2CounterBlockId,
  KernelDriverCounterBlockId,

  CpPipeStatsCounterBlockId,
  HwInfoCounterBlockId,
  FirstCounterBlockId = CbCounterBlockId,
  LastCounterBlockId = HwInfoCounterBlockId,
};

// MAX Number of block instances for VOLCANIC ISLANDS (From Fiji)
// Values are found here //gfxip/gfx8/main/src/meta/features/variant/Fiji/album.dj

// @brief Number of block instances.
// Number of block instances per SE
// Counters are indexed per SE and instance
static const uint32_t CbCounterBlockNumInstances    = 4;
static const uint32_t DbCounterBlockNumInstances    = 4;
// The values below are the same as the number of CUs per SH.
// Counters are indexed per SE and instance
static const uint32_t TaCounterBlockNumInstances    = 16;
static const uint32_t TdCounterBlockNumInstances    = 16;
static const uint32_t TcpCounterBlockNumInstances   = 16;
// These values are per chip
// Counters are indexed per instance
static const uint32_t TcaCounterBlockNumInstances   = 2;
static const uint32_t TccCounterBlockNumInstances   = 16;
static const uint32_t SdmaCounterBlockNumInstances  = 2;
// MC instances
static const uint32_t McCounterBlockNumInstances    = 8; // Fiji, 2 channels

// Number of block counter registers
static const uint32_t CbCounterBlockNumCounters     = 4;
static const uint32_t CpcCounterBlockNumCounters    = 2;
static const uint32_t CpfCounterBlockNumCounters    = 2;
static const uint32_t CpgCounterBlockNumCounters    = 2;
static const uint32_t DbCounterBlockNumCounters     = 4;
static const uint32_t GdsCounterBlockNumCounters    = 4;
static const uint32_t GrbmCounterBlockNumCounters   = 2;
static const uint32_t GrbmSeCounterBlockNumCounters = 1;
static const uint32_t IaCounterBlockNumCounters     = 4;
static const uint32_t RlcCounterBlockNumCounters    = 2;
static const uint32_t PaSuCounterBlockNumCounters   = 4;
static const uint32_t PaScCounterBlockNumCounters   = 8;
static const uint32_t SdmaCounterBlockNumCounters   = 2;
static const uint32_t SpiCounterBlockNumCounters    = 6;
static const uint32_t SqCounterBlockNumCounters     = 16;
static const uint32_t SrbmCounterBlockNumCounters   = 2;
static const uint32_t SxCounterBlockNumCounters     = 4;
static const uint32_t TaCounterBlockNumCounters     = 2;
static const uint32_t TcaCounterBlockNumCounters    = 4;
static const uint32_t TccCounterBlockNumCounters    = 4;
static const uint32_t TcpCounterBlockNumCounters    = 4;
static const uint32_t TdCounterBlockNumCounters     = 2;
static const uint32_t VgtCounterBlockNumCounters    = 4;
static const uint32_t WdCounterBlockNumCounters     = 4;
static const uint32_t McArbCounterBlockNumCounters  = 4;
static const uint32_t McHubCounterBlockNumCounters  = 4;
static const uint32_t McMcbvmCounterBlockNumCounters = 4;
static const uint32_t McSeqCounterBlockNumCounters  = 4;
static const uint32_t McVmL2CounterBlockNumCounters = 2;
static const uint32_t McXbarCounterBlockNumCounters = 4;

// Block counters max event value
static const uint32_t CpfCounterBlockMaxEvent       = 18;
static const uint32_t CpgCounterBlockMaxEvent       = 47;
static const uint32_t CpcCounterBlockMaxEvent       = 23;
static const uint32_t CbCounterBlockMaxEvent        = 395;
static const uint32_t DbCounterBlockMaxEvent        = 256;
static const uint32_t GrbmCounterBlockMaxEvent      = 33;
static const uint32_t GrbmSeCounterBlockMaxEvent    = 14;
static const uint32_t SrbmCounterBlockMaxEvent      = 27;
static const uint32_t RlcCounterBlockMaxEvent       = 6;
static const uint32_t PaSuCounterBlockMaxEvent      = 152;
static const uint32_t PaScCounterBlockMaxEvent      = 396;
static const uint32_t SpiCounterBlockMaxEvent       = 196;
static const uint32_t SqCounterBlockMaxEvent        = 297; // Fiji
static const uint32_t TaCounterBlockMaxEvent        = 118;
static const uint32_t TdCounterBlockMaxEvent        = 54;
static const uint32_t TcpCounterBlockMaxEvent       = 179;
static const uint32_t TccCounterBlockMaxEvent       = 191;
static const uint32_t TcaCounterBlockMaxEvent       = 34;
static const uint32_t GdsCounterBlockMaxEvent       = 120;
static const uint32_t SdmaCounterBlockMaxEvent      = 61;
static const uint32_t SxCounterBlockMaxEvent        = 32;
static const uint32_t VgtCounterBlockMaxEvent       = 145;
static const uint32_t IaCounterBlockMaxEvent        = 21;
static const uint32_t WdCounterBlockMaxEvent        = 36;
static const uint32_t McArbCounterBlockMaxEvent     = 162;
static const uint32_t McHubCounterBlockMaxEvent     = 208;
static const uint32_t McMcbvmCounterBlockMaxEvent   = 48;
static const uint32_t McSeqCounterBlockMaxEvent     = 21;
static const uint32_t McVmL2CounterBlockMaxEvent    = 20;
static const uint32_t McXbarCounterBlockMaxEvent    = 115;

#endif  // _GFX8_BLOCKINFO_H_
