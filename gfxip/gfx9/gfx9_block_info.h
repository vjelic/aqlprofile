#ifndef _GFX9_BLOCKINFO_H_
#define _GFX9_BLOCKINFO_H_

namespace gfxip {
namespace gfx9 {

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

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const CounterRegInfo AiSqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER0_LO, mmSQ_PERFCOUNTER0_HI},
    {mmSQ_PERFCOUNTER1_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER1_LO, mmSQ_PERFCOUNTER1_HI},
    {mmSQ_PERFCOUNTER2_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER2_LO, mmSQ_PERFCOUNTER2_HI},
    {mmSQ_PERFCOUNTER3_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER3_LO, mmSQ_PERFCOUNTER3_HI},
    {mmSQ_PERFCOUNTER4_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER4_LO, mmSQ_PERFCOUNTER4_HI},
    {mmSQ_PERFCOUNTER5_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER5_LO, mmSQ_PERFCOUNTER5_HI},
    {mmSQ_PERFCOUNTER6_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER6_LO, mmSQ_PERFCOUNTER6_HI},
    {mmSQ_PERFCOUNTER7_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER7_LO, mmSQ_PERFCOUNTER7_HI},
    {mmSQ_PERFCOUNTER8_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER8_LO, mmSQ_PERFCOUNTER8_HI},
    {mmSQ_PERFCOUNTER9_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER9_LO, mmSQ_PERFCOUNTER9_HI},
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER10_LO,
     mmSQ_PERFCOUNTER10_HI},
    {mmSQ_PERFCOUNTER11_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER11_LO,
     mmSQ_PERFCOUNTER11_HI},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER12_LO,
     mmSQ_PERFCOUNTER12_HI},
    {mmSQ_PERFCOUNTER13_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER13_LO,
     mmSQ_PERFCOUNTER13_HI},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER14_LO,
     mmSQ_PERFCOUNTER14_HI},
    {mmSQ_PERFCOUNTER15_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER15_LO,
     mmSQ_PERFCOUNTER15_HI}};

/*
 * DRMDMA
 */
static const CounterRegInfo AiDrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER0_RESULT, 0},
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER1_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER0_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER1_RESULT, 0},
};

/*
 * IH
 */
static const CounterRegInfo AiIhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER0_RESULT, 0},
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER1_RESULT, 0}};

/*
 * CPF
 */
static const CounterRegInfo AiCpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

/*
 * DRM
 */
static const CounterRegInfo AiDrmCounterRegAddr[] = {
    /*
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}
    */
};

/*
 * GRBM
 */
static const CounterRegInfo AiGrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT, 0, mmGRBM_PERFCOUNTER0_LO, mmGRBM_PERFCOUNTER0_HI},
    {mmGRBM_PERFCOUNTER1_SELECT, 0, mmGRBM_PERFCOUNTER1_LO, mmGRBM_PERFCOUNTER1_HI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo AiGrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT, 0, mmGRBM_SE0_PERFCOUNTER_LO, mmGRBM_SE0_PERFCOUNTER_HI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT, 0, mmGRBM_SE1_PERFCOUNTER_LO, mmGRBM_SE1_PERFCOUNTER_HI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT, 0, mmGRBM_SE2_PERFCOUNTER_LO, mmGRBM_SE2_PERFCOUNTER_HI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT, 0, mmGRBM_SE3_PERFCOUNTER_LO, mmGRBM_SE3_PERFCOUNTER_HI}};

/*
 * PA_SU
 */
static const CounterRegInfo AiPaSuCounterRegAddr[] = {
    {mmPA_SU_PERFCOUNTER0_SELECT, 0, mmPA_SU_PERFCOUNTER0_LO, mmPA_SU_PERFCOUNTER0_HI},
    {mmPA_SU_PERFCOUNTER1_SELECT, 0, mmPA_SU_PERFCOUNTER1_LO, mmPA_SU_PERFCOUNTER1_HI},
    {mmPA_SU_PERFCOUNTER2_SELECT, 0, mmPA_SU_PERFCOUNTER2_LO, mmPA_SU_PERFCOUNTER2_HI},
    {mmPA_SU_PERFCOUNTER3_SELECT, 0, mmPA_SU_PERFCOUNTER3_LO, mmPA_SU_PERFCOUNTER3_HI}};

/*
 * PA_SC
 */
static const CounterRegInfo AiPaScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT, 0, mmPA_SC_PERFCOUNTER0_LO, mmPA_SC_PERFCOUNTER0_HI},
    {mmPA_SC_PERFCOUNTER1_SELECT, 0, mmPA_SC_PERFCOUNTER1_LO, mmPA_SC_PERFCOUNTER1_HI},
    {mmPA_SC_PERFCOUNTER2_SELECT, 0, mmPA_SC_PERFCOUNTER2_LO, mmPA_SC_PERFCOUNTER2_HI},
    {mmPA_SC_PERFCOUNTER3_SELECT, 0, mmPA_SC_PERFCOUNTER3_LO, mmPA_SC_PERFCOUNTER3_HI}};

/*
 * SPI
 */
static const CounterRegInfo AiSpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT, 0, mmSPI_PERFCOUNTER0_LO, mmSPI_PERFCOUNTER0_HI},
    {mmSPI_PERFCOUNTER1_SELECT, 0, mmSPI_PERFCOUNTER1_LO, mmSPI_PERFCOUNTER1_HI},
    {mmSPI_PERFCOUNTER2_SELECT, 0, mmSPI_PERFCOUNTER2_LO, mmSPI_PERFCOUNTER2_HI},
    {mmSPI_PERFCOUNTER3_SELECT, 0, mmSPI_PERFCOUNTER3_LO, mmSPI_PERFCOUNTER3_HI},
    {mmSPI_PERFCOUNTER4_SELECT, 0, mmSPI_PERFCOUNTER4_LO, mmSPI_PERFCOUNTER4_HI},
    {mmSPI_PERFCOUNTER5_SELECT, 0, mmSPI_PERFCOUNTER5_LO, mmSPI_PERFCOUNTER5_HI}};

/*
 * TCA
 */
static const CounterRegInfo AiTcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT, 0, mmTCA_PERFCOUNTER0_LO, mmTCA_PERFCOUNTER0_HI},
    {mmTCA_PERFCOUNTER1_SELECT, 0, mmTCA_PERFCOUNTER1_LO, mmTCA_PERFCOUNTER1_HI},
    {mmTCA_PERFCOUNTER2_SELECT, 0, mmTCA_PERFCOUNTER2_LO, mmTCA_PERFCOUNTER2_HI},
    {mmTCA_PERFCOUNTER3_SELECT, 0, mmTCA_PERFCOUNTER3_LO, mmTCA_PERFCOUNTER3_HI}};

/*
 * TCC
 */
static const CounterRegInfo AiTccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT, 0, mmTCC_PERFCOUNTER0_LO, mmTCC_PERFCOUNTER0_HI},
    {mmTCC_PERFCOUNTER1_SELECT, 0, mmTCC_PERFCOUNTER1_LO, mmTCC_PERFCOUNTER1_HI},
    {mmTCC_PERFCOUNTER2_SELECT, 0, mmTCC_PERFCOUNTER2_LO, mmTCC_PERFCOUNTER2_HI},
    {mmTCC_PERFCOUNTER3_SELECT, 0, mmTCC_PERFCOUNTER3_LO, mmTCC_PERFCOUNTER3_HI}};

/*
 * TCP
 */
static const CounterRegInfo AiTcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT, 0, mmTCP_PERFCOUNTER0_LO, mmTCP_PERFCOUNTER0_HI},
    {mmTCP_PERFCOUNTER1_SELECT, 0, mmTCP_PERFCOUNTER1_LO, mmTCP_PERFCOUNTER1_HI},
    {mmTCP_PERFCOUNTER2_SELECT, 0, mmTCP_PERFCOUNTER2_LO, mmTCP_PERFCOUNTER2_HI},
    {mmTCP_PERFCOUNTER3_SELECT, 0, mmTCP_PERFCOUNTER3_LO, mmTCP_PERFCOUNTER3_HI}};

/*
 * CB
 */
static const CounterRegInfo AiCbCounterRegAddr[] = {
    {mmCB_PERFCOUNTER0_SELECT, 0, mmCB_PERFCOUNTER0_LO, mmCB_PERFCOUNTER0_HI},
    {mmCB_PERFCOUNTER1_SELECT, 0, mmCB_PERFCOUNTER1_LO, mmCB_PERFCOUNTER1_HI},
    {mmCB_PERFCOUNTER2_SELECT, 0, mmCB_PERFCOUNTER2_LO, mmCB_PERFCOUNTER2_HI},
    {mmCB_PERFCOUNTER3_SELECT, 0, mmCB_PERFCOUNTER3_LO, mmCB_PERFCOUNTER3_HI}};

/*
 * DB
 */
static const CounterRegInfo AiDbCounterRegAddr[] = {
    {mmDB_PERFCOUNTER0_SELECT, 0, mmDB_PERFCOUNTER0_LO, mmDB_PERFCOUNTER0_HI},
    {mmDB_PERFCOUNTER1_SELECT, 0, mmDB_PERFCOUNTER1_LO, mmDB_PERFCOUNTER1_HI},
    {mmDB_PERFCOUNTER2_SELECT, 0, mmDB_PERFCOUNTER2_LO, mmDB_PERFCOUNTER2_HI},
    {mmDB_PERFCOUNTER3_SELECT, 0, mmDB_PERFCOUNTER3_LO, mmDB_PERFCOUNTER3_HI}};

/*
 * RLC
 */
static const CounterRegInfo AiRlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT, 0, mmRLC_PERFCOUNTER0_LO, mmRLC_PERFCOUNTER0_HI},
    {mmRLC_PERFCOUNTER1_SELECT, 0, mmRLC_PERFCOUNTER1_LO, mmRLC_PERFCOUNTER1_HI}};

/*
 * SC
 */
static const CounterRegInfo AiScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT, 0, mmPA_SC_PERFCOUNTER0_LO, mmPA_SC_PERFCOUNTER0_HI},
    {mmPA_SC_PERFCOUNTER1_SELECT, 0, mmPA_SC_PERFCOUNTER1_LO, mmPA_SC_PERFCOUNTER1_HI},
    {mmPA_SC_PERFCOUNTER2_SELECT, 0, mmPA_SC_PERFCOUNTER2_LO, mmPA_SC_PERFCOUNTER2_HI},
    {mmPA_SC_PERFCOUNTER3_SELECT, 0, mmPA_SC_PERFCOUNTER3_LO, mmPA_SC_PERFCOUNTER3_HI},
    {mmPA_SC_PERFCOUNTER4_SELECT, 0, mmPA_SC_PERFCOUNTER4_LO, mmPA_SC_PERFCOUNTER4_HI},
    {mmPA_SC_PERFCOUNTER5_SELECT, 0, mmPA_SC_PERFCOUNTER5_LO, mmPA_SC_PERFCOUNTER5_HI},
    {mmPA_SC_PERFCOUNTER6_SELECT, 0, mmPA_SC_PERFCOUNTER6_LO, mmPA_SC_PERFCOUNTER6_HI},
    {mmPA_SC_PERFCOUNTER7_SELECT, 0, mmPA_SC_PERFCOUNTER7_LO, mmPA_SC_PERFCOUNTER7_HI}};

/*
 * SX
 */
static const CounterRegInfo AiSxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

/*
 * TA
 */
static const CounterRegInfo AiTaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

/*
 * TD
 */
static const CounterRegInfo AiTdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT, 0, mmTD_PERFCOUNTER0_LO, mmTD_PERFCOUNTER0_HI},
    {mmTD_PERFCOUNTER1_SELECT, 0, mmTD_PERFCOUNTER1_LO, mmTD_PERFCOUNTER1_HI}};

/*
 * GDS
 */
static const CounterRegInfo AiGdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT, 0, mmGDS_PERFCOUNTER0_LO, mmGDS_PERFCOUNTER0_HI},
    {mmGDS_PERFCOUNTER1_SELECT, 0, mmGDS_PERFCOUNTER1_LO, mmGDS_PERFCOUNTER1_HI},
    {mmGDS_PERFCOUNTER2_SELECT, 0, mmGDS_PERFCOUNTER2_LO, mmGDS_PERFCOUNTER2_HI},
    {mmGDS_PERFCOUNTER3_SELECT, 0, mmGDS_PERFCOUNTER3_LO, mmGDS_PERFCOUNTER3_HI}};

/*
 * VGT
 */
static const CounterRegInfo AiVgtCounterRegAddr[] = {
    {mmVGT_PERFCOUNTER0_SELECT, 0, mmVGT_PERFCOUNTER0_LO, mmVGT_PERFCOUNTER0_HI},
    {mmVGT_PERFCOUNTER1_SELECT, 0, mmVGT_PERFCOUNTER1_LO, mmVGT_PERFCOUNTER1_HI},
    {mmVGT_PERFCOUNTER2_SELECT, 0, mmVGT_PERFCOUNTER2_LO, mmVGT_PERFCOUNTER2_HI},
    {mmVGT_PERFCOUNTER3_SELECT, 0, mmVGT_PERFCOUNTER3_LO, mmVGT_PERFCOUNTER3_HI}};

/*
 * IA
 */
static const CounterRegInfo AiIaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT, 0, mmIA_PERFCOUNTER0_LO, mmIA_PERFCOUNTER0_HI},
    {mmIA_PERFCOUNTER1_SELECT, 0, mmIA_PERFCOUNTER1_LO, mmIA_PERFCOUNTER1_HI},
    {mmIA_PERFCOUNTER2_SELECT, 0, mmIA_PERFCOUNTER2_LO, mmIA_PERFCOUNTER2_HI},
    {mmIA_PERFCOUNTER3_SELECT, 0, mmIA_PERFCOUNTER3_LO, mmIA_PERFCOUNTER3_HI}};

/*
 * MC
 */
static const CounterRegInfo AiMcCounterRegAddr[] = {
    /*

    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}

     */
};

/*
 * SRBM
 */
static const CounterRegInfo AiSrbmCounterRegAddr[] = {
    /*
    {mmSRBM_PERFCOUNTER0_SELECT, 0, mmSRBM_PERFCOUNTER0_LO,
     mmSRBM_PERFCOUNTER0_HI},
    {mmSRBM_PERFCOUNTER1_SELECT, 0, mmSRBM_PERFCOUNTER1_LO,
     mmSRBM_PERFCOUNTER1_HI}
     */
};

/*
 * WD
 */
static const CounterRegInfo AiWdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT, 0, mmWD_PERFCOUNTER0_LO, mmWD_PERFCOUNTER0_HI},
    {mmWD_PERFCOUNTER1_SELECT, 0, mmWD_PERFCOUNTER1_LO, mmWD_PERFCOUNTER1_HI},
    {mmWD_PERFCOUNTER2_SELECT, 0, mmWD_PERFCOUNTER2_LO, mmWD_PERFCOUNTER2_HI},
    {mmWD_PERFCOUNTER3_SELECT, 0, mmWD_PERFCOUNTER3_LO, mmWD_PERFCOUNTER3_HI}};

/*
 * CPG
 */
static const CounterRegInfo AiCpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT, 0, mmCPG_PERFCOUNTER0_LO, mmCPG_PERFCOUNTER0_HI},
    {mmCPG_PERFCOUNTER1_SELECT, 0, mmCPG_PERFCOUNTER1_LO, mmCPG_PERFCOUNTER1_HI}};

/*
 * CPC
 */
static const CounterRegInfo AiCpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

/**
 * Table containing CounterGroups which represent AI hardware blocks
 * as defined by \ref GpuBlockInfo structure
 */
static const GpuBlockInfo Gfx9HwBlocks[] = {
    // Counter block CB
    {"AI_CB", kHsaAiCounterBlockIdCb, AI_NUM_CB, CntlMethodBySeAndInstance, 395, AI_COUNTER_NUM_PER_CB, 0, 0, true, AiCbCounterRegAddr}, 
    // Temp commented for Vega10
    // Counter block CPF
    /*
    {"AI_CPF", kHsaAiCounterBlockIdCpf, 1, CntlMethodNone, 19, AI_COUNTER_NUM_PER_CPF, 0, 0, true, AiCpfCounterRegAddr}, 
    */
    // Counter block DB
    {"AI_DB", kHsaAiCounterBlockIdDb, AI_NUM_DB, CntlMethodBySeAndInstance, 256, AI_COUNTER_NUM_PER_DB, 0, 0, true, AiDbCounterRegAddr}, 
    // Counter block GRBM
    {"AI_GRBM", kHsaAiCounterBlockIdGrbm, 1, CntlMethodNone, 33, AI_COUNTER_NUM_PER_GRBM, 0, 0, true, AiGrbmCounterRegAddr}, 
    // Counter block GRBMSE
    {"AI_GRBMSE", kHsaAiCounterBlockIdGrbmSe, 1, CntlMethodNone, 14, AI_COUNTER_NUM_PER_GRBMSE, 0, 0, true, AiGrbmSeCounterRegAddr}, 
    // Counter block PA_SU
    {"AI_PA_SU", kHsaAiCounterBlockIdPaSu, 1, CntlMethodBySe, 152, AI_COUNTER_NUM_PER_PA_SU, 0, 0, true, AiPaSuCounterRegAddr}, 
    // Counter block PA_SC
    {"AI_PA_SC", kHsaAiCounterBlockIdPaSc, 1, CntlMethodBySe, 396, AI_COUNTER_NUM_PER_PA_SC, 0, 0, true, AiPaScCounterRegAddr}, 
    // Counter block SPI
    {"AI_SPI", kHsaAiCounterBlockIdSpi, 1, CntlMethodBySe, 196, AI_COUNTER_NUM_PER_SPI, 0, 0, true, AiSpiCounterRegAddr}, 
    // Counter block SQ
    {"AI_SQ", kHsaAiCounterBlockIdSq, 1, CntlMethodBySe, 171, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    {"AI_SQ_GS", kHsaAiCounterBlockIdSqGs, 1, CntlMethodBySe, 298, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    {"AI_SQ_VS", kHsaAiCounterBlockIdSqVs, 1, CntlMethodBySe, 298, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    {"AI_SQ_PS", kHsaAiCounterBlockIdSqPs, 1, CntlMethodBySe, 298, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    {"AI_SQ_HS", kHsaAiCounterBlockIdSqHs, 1, CntlMethodBySe, 298, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    {"AI_SQ_CS", kHsaAiCounterBlockIdSqCs, 1, CntlMethodBySe, 298, AI_COUNTER_NUM_PER_SQ, 0, 0, true, AiSqCounterRegAddr}, 
    // Counter block SX
    {"AI_SX", kHsaAiCounterBlockIdSx, 1, CntlMethodBySe, 33, AI_COUNTER_NUM_PER_SX, 0, 0, true, AiSxCounterRegAddr}, 
    // Counter block TA
    {"AI_TA", kHsaAiCounterBlockIdTa, AI_NUM_TA, CntlMethodBySeAndInstance, 118, AI_COUNTER_NUM_PER_TA, 0, 0, true, AiTaCounterRegAddr}, 
    // Counter block TCA
    {"AI_TCA", kHsaAiCounterBlockIdTca, AI_NUM_TCA, CntlMethodByInstance, 34, AI_COUNTER_NUM_PER_TCA, 0, 0, true, AiTcaCounterRegAddr}, 
    // Counter block TCC
    {"AI_TCC", kHsaAiCounterBlockIdTcc, AI_NUM_TCC, CntlMethodByInstance, 191, AI_COUNTER_NUM_PER_TCC, 0, 0, true, AiTccCounterRegAddr}, 
    // Counter block TD
    {"AI_TD", kHsaAiCounterBlockIdTd, AI_NUM_TD, CntlMethodBySeAndInstance, 54, AI_COUNTER_NUM_PER_TD, 0, 0, true, AiTdCounterRegAddr}, 
    // Counter block TCP
    {"AI_TCP", kHsaAiCounterBlockIdTcp, AI_NUM_TCP, CntlMethodBySeAndInstance, 182, AI_COUNTER_NUM_PER_TCP, 0, 0, true, AiTcpCounterRegAddr}, 
    // Counter block GDS
    {"AI_GDS", kHsaAiCounterBlockIdGds, 1, CntlMethodNone, 120, AI_COUNTER_NUM_PER_GDS, 0, 0, true, AiGdsCounterRegAddr}, 
    // Counter block VGT
    {"AI_VGT", kHsaAiCounterBlockIdVgt, 1, CntlMethodBySe, 145, AI_COUNTER_NUM_PER_VGT, 0, 0, true, AiVgtCounterRegAddr}, 
    // Counter block IA
    {"AI_IA", kHsaAiCounterBlockIdIa, 1, CntlMethodBySe, 23, AI_COUNTER_NUM_PER_IA, 0, 0, true, AiIaCounterRegAddr}, 
    // Counter block MC
    {"AI_MC", kHsaAiCounterBlockIdMc, 1, CntlMethodNone, 22, AI_COUNTER_NUM_PER_MC, 0, 0, true, AiMcCounterRegAddr}, 
    // Temp commented out for Vega10
    // Counter block SRBM
    /*
    {"AI_SRBM", kHsaAiCounterBlockIdSrbm, 1, CntlMethodNone, 19, AI_COUNTER_NUM_PER_SRBM, 0, 0, true, AiSrbmCounterRegAddr}, 
    */
    // Counter block WD
    {"AI_WD", kHsaAiCounterBlockIdWd, 1, CntlMethodNone, 36, AI_COUNTER_NUM_PER_WD, 0, 0, true, AiWdCounterRegAddr}, 
    // Counter block CPG
    // Temp commented for Vega10
    /*
    {"AI_CPG", kHsaAiCounterBlockIdCpg, 1, CntlMethodNone, 48, AI_COUNTER_NUM_PER_CPG, 0, 0, true, AiCpgCounterRegAddr}, 
    */
    // Counter block CPC
    {"AI_CPC", kHsaAiCounterBlockIdCpc, 1, CntlMethodNone, 34, AI_COUNTER_NUM_PER_CPC, 0, 0, true, AiCpcCounterRegAddr}, 
    // Counter block IOMMUV2
    {"AI_IOMMUV2", kHsaAiCounterBlockIdIommuV2, 1, CntlMethodNone, 25, 8, 0, 0, true, NULL}, 
    // Counter block KernelDriver
    {"AI_KD", kHsaAiCounterBlockIdKernelDriver, 1, CntlMethodNone, 0, 0, 0, 0, true, NULL}, 
};

static const uint32_t Gfx9HwBlockCount = sizeof(Gfx9HwBlocks) / sizeof(GpuBlockInfo);

}  // namespace gfx9
}  // namespace gfxip

#endif  //  _GFX9_BLOCKINFO_H_
