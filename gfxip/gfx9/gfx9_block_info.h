#ifndef _GFX9_BLOCKINFO_H_
#define _GFX9_BLOCKINFO_H_

namespace gfxip {
namespace gfx9 {

// Enumeration of Gfx9 hardware counter blocks
enum CounterBlockId {
  CbCounterBlockId,
  CpcCounterBlockId,
  CpfCounterBlockId,
  CpgCounterBlockId,
  DbCounterBlockId,
  GdsCounterBlockId,
  GrbmCounterBlockId,
  GrbmSeCounterBlockId,
  IaCounterBlockId,
  PaScCounterBlockId,
  PaSuCounterBlockId,
  SpiCounterBlockId,
  SqCounterBlockId,
  SqGsCounterBlockId,
  SqVsCounterBlockId,
  SqPsCounterBlockId,
  SqHsCounterBlockId,
  SqCsCounterBlockId,
  SxCounterBlockId,
  TaCounterBlockId,
  TcaCounterBlockId,
  TccCounterBlockId,
  TcpCounterBlockId,
  TcsCounterBlockId,
  TdCounterBlockId,
  VgtCounterBlockId,
  WdCounterBlockId,

  // MC blocks
  GceaCounterBlockId,
  AtcCounterBlockId,
  AtcL2CounterBlockId,
  McVmL2CounterBlockId,
  RpbCounterBlockId,
  RmiCounterBlockId,

  // Counters retrieved by KFD
  IommuV2CounterBlockId,
  KernelDriverCounterBlockId,

  CpPipeStatsCounterBlockId,
  HwInfoCounterBlockId,

  FirstCounterBlockId = CbCounterBlockId,
  LastCounterBlockId = HwInfoCounterBlockId,
};

// Number of block instances
static const uint32_t CbCounterBlockNumInstances    = 4;
static const uint32_t DbCounterBlockNumInstances    = 4;
static const uint32_t TaCounterBlockNumInstances    = 16;
static const uint32_t TdCounterBlockNumInstances    = 16;
static const uint32_t TcpCounterBlockNumInstances   = 16;
static const uint32_t TcaCounterBlockNumInstances   = 2;
static const uint32_t TccCounterBlockNumInstances   = 16;
static const uint32_t SdmaCounterBlockNumInstances  = 2;
static const uint32_t RmiCounterBlockNumInstances   = 8;
static const uint32_t GceaCounterBlockNumInstances  = 16;
static const uint32_t AtcCounterBlockNumInstances   = 16;
static const uint32_t AtcL2CounterBlockNumInstances = 16;
static const uint32_t McVmL2CounterBlockNumInstances = 16;
static const uint32_t RpbCounterBlockNumInstances   = 16;

// Number of block counter registers
static const uint32_t CbCounterBlockNumCounters     = 4;
static const uint32_t CpcCounterBlockNumCounters    = 2;
static const uint32_t CpfCounterBlockNumCounters    = 2;
static const uint32_t CpgCounterBlockNumCounters    = 2;
static const uint32_t DbCounterBlockNumCounters     = 4;
static const uint32_t GdsCounterBlockNumCounters    = 4;
static const uint32_t GrbmCounterBlockNumCounters   = 2;
static const uint32_t GrbmSeCounterBlockNumCounters = 4;
static const uint32_t IaCounterBlockNumCounters     = 4;
static const uint32_t PaSuCounterBlockNumCounters   = 4;
static const uint32_t PaScCounterBlockNumCounters   = 8;
static const uint32_t RlcCounterBlockNumCounters    = 2;
static const uint32_t SdmaCounterBlockNumCounters   = 2;
static const uint32_t SpiCounterBlockNumCounters    = 6;
static const uint32_t SqCounterBlockNumCounters     = 16;
static const uint32_t SxCounterBlockNumCounters     = 4;
static const uint32_t TaCounterBlockNumCounters     = 2;
static const uint32_t TcaCounterBlockNumCounters    = 4;
static const uint32_t TccCounterBlockNumCounters    = 4;
static const uint32_t TcpCounterBlockNumCounters    = 4;
static const uint32_t TdCounterBlockNumCounters     = 2;
static const uint32_t VgtCounterBlockNumCounters    = 4;
static const uint32_t WdCounterBlockNumCounters     = 4;
static const uint32_t GceaCounterBlockNumCounters   = 2;
static const uint32_t AtcCounterBlockNumCounters    = 4;
static const uint32_t AtcL2CounterBlockNumCounters  = 2;
static const uint32_t McVmL2CounterBlockNumCounters = 8;
static const uint32_t RpbCounterBlockNumCounters    = 4;
static const uint32_t RmiCounterBlockNumCounters    = 4;

// Block counters max event value
static const uint32_t CbCounterBlockMaxEvent        = CB_PERF_SEL_CC_BB_BLEND_PIXEL_VLD;
static const uint32_t CpcCounterBlockMaxEvent       = CPC_PERF_SEL_ME2_DC1_SPI_BUSY;
static const uint32_t CpfCounterBlockMaxEvent       = CPF_PERF_SEL_CPF_UTCL2IU_STALL;
static const uint32_t CpgCounterBlockMaxEvent       = CPG_PERF_SEL_CPG_UTCL2IU_STALL;
static const uint32_t DbCounterBlockMaxEvent        = DB_PERF_SEL_DB_SC_quad_quads_with_4_pixels;
static const uint32_t GdsCounterBlockMaxEvent       = GDS_PERF_SEL_GWS_BYPASS;
static const uint32_t GrbmCounterBlockMaxEvent      = GRBM_PERF_SEL_CPAXI_BUSY;
static const uint32_t GrbmSeCounterBlockMaxEvent    = GRBM_PERF_SEL_CPAXI_BUSY;
static const uint32_t IaCounterBlockMaxEvent        = ia_perf_utcl1_stall_utcl2_event;
static const uint32_t PaSuCounterBlockMaxEvent      = PERF_CLIENT_UTCL1_INFLIGHT;
static const uint32_t PaScCounterBlockMaxEvent      = SC_DB1_TILE_INTERFACE_CREDIT_AT_MAX_WITH_NO_PENDING_SEND;
static const uint32_t RlcCounterBlockMaxEvent       = 7;
static const uint32_t SdmaCounterBlockMaxEvent      = SDMA_PERF_SEL_MMHUB_TAG_DELAY_COUNTER;
static const uint32_t SpiCounterBlockMaxEvent       = SPI_PERF_VWC_CSC_WR;
static const uint32_t SqCounterBlockMaxEvent        = SQC_PERF_SEL_DUMMY_LAST;
static const uint32_t SxCounterBlockMaxEvent        = SX_PERF_SEL_DB3_SIZE;
static const uint32_t TaCounterBlockMaxEvent        = TA_PERF_SEL_first_xnack_on_phase3;
static const uint32_t TcaCounterBlockMaxEvent       = TCA_PERF_SEL_CROSSBAR_STALL_TCC7;
static const uint32_t TccCounterBlockMaxEvent       = TCC_PERF_SEL_CLIENT127_REQ;
static const uint32_t TcpCounterBlockMaxEvent       = TCP_PERF_SEL_TCC_DCC_REQ;
static const uint32_t TdCounterBlockMaxEvent        = TD_PERF_SEL_texels_zeroed_out_by_blend_zero_prt;
static const uint32_t VgtCounterBlockMaxEvent       = vgt_perf_sclk_te11_vld;
static const uint32_t WdCounterBlockMaxEvent        = wd_perf_utcl1_stall_utcl2_event;
static const uint32_t GceaCounterBlockMaxEvent      = 76;
static const uint32_t AtcCounterBlockMaxEvent       = 23;
static const uint32_t AtcL2CounterBlockMaxEvent     = 7;
static const uint32_t RpbCounterBlockMaxEvent       = 62;
static const uint32_t McVmL2CounterBlockMaxEvent    = 20;
static const uint32_t RmiCounterBlockMaxEvent       = RMI_PERF_SEL_RMI_RB_EARLY_WRACK_NACK3;

}  // namespace gfx9
}  // namespace gfxip

#endif  //  _GFX9_BLOCKINFO_H_
