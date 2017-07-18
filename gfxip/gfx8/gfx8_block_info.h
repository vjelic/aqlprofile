#ifndef _VI_BLOCKINFO_H_
#define _VI_BLOCKINFO_H_

namespace gfxip {
namespace gfx8 {

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

/**
 * Table containing CounterGroups which represent VI hardware blocks
 * as defined by \ref GpuBlockInfo structure
 */
static const GpuBlockInfo Gfx8HwBlocks[] = {
    // Counter block CB
    {"VI_CB", kHsaViCounterBlockIdCb, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_CB,
     CntlMethodBySeAndInstance, 395, VI_COUNTER_NUM_PER_CB, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block CPF
    {"VI_CPF", kHsaViCounterBlockIdCpf, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 19,
     VI_COUNTER_NUM_PER_CPF, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block DB
    {"VI_DB", kHsaViCounterBlockIdDb, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_DB,
     CntlMethodBySeAndInstance, 256, VI_COUNTER_NUM_PER_DB, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block GRBM
    {"VI_GRBM", kHsaViCounterBlockIdGrbm, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 33,
     VI_COUNTER_NUM_PER_GRBM, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block GRBMSE
    {"VI_GRBMSE", kHsaViCounterBlockIdGrbmSe, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 14,
     VI_COUNTER_NUM_PER_GRBMSE, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block PA_SU
    {"VI_PA_SU", kHsaViCounterBlockIdPaSu, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 152,
     VI_COUNTER_NUM_PER_PA_SU, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block PA_SC
    {"VI_PA_SC", kHsaViCounterBlockIdPaSc, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 396,
     VI_COUNTER_NUM_PER_PA_SC, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block SPI
    {"VI_SPI", kHsaViCounterBlockIdSpi, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 196,
     VI_COUNTER_NUM_PER_SPI, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block SQ
    {"VI_SQ", kHsaViCounterBlockIdSq, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_ES", kHsaViCounterBlockIdSqEs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_GS", kHsaViCounterBlockIdSqGs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_VS", kHsaViCounterBlockIdSqVs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_PS", kHsaViCounterBlockIdSqPs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_LS", kHsaViCounterBlockIdSqLs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_HS", kHsaViCounterBlockIdSqHs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    {"VI_SQ_CS", kHsaViCounterBlockIdSqCs, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 298,
     VI_COUNTER_NUM_PER_SQ, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block SX
    {"VI_SX", kHsaViCounterBlockIdSx, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 33,
     VI_COUNTER_NUM_PER_SX, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block TA
    {"VI_TA", kHsaViCounterBlockIdTa, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_TA,
     CntlMethodBySeAndInstance, 118, VI_COUNTER_NUM_PER_TA, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block TCA
    {"VI_TCA", kHsaViCounterBlockIdTca, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_TCA,
     CntlMethodByInstance, 34, VI_COUNTER_NUM_PER_TCA, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block TCC
    {"VI_TCC", kHsaViCounterBlockIdTcc, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_TCC,
     CntlMethodByInstance, 191, VI_COUNTER_NUM_PER_TCC, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block TD
    {"VI_TD", kHsaViCounterBlockIdTd, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_TD,
     CntlMethodBySeAndInstance, 54, VI_COUNTER_NUM_PER_TD, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block TCP
    {"VI_TCP", kHsaViCounterBlockIdTcp, VI_MAX_NUM_SHADER_ENGINES, 2, VI_NUM_TCP,
     CntlMethodBySeAndInstance, 182, VI_COUNTER_NUM_PER_TCP, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block GDS
    {"VI_GDS", kHsaViCounterBlockIdGds, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 120,
     VI_COUNTER_NUM_PER_GDS, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block VGT
    {"VI_VGT", kHsaViCounterBlockIdVgt, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 145,
     VI_COUNTER_NUM_PER_VGT, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block IA
    {"VI_IA", kHsaViCounterBlockIdIa, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodBySe, 23,
     VI_COUNTER_NUM_PER_IA, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block MC
    {"VI_MC", kHsaViCounterBlockIdMc, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 22,
     VI_COUNTER_NUM_PER_MC, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block SRBM
    {"VI_SRBM", kHsaViCounterBlockIdSrbm, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 19,
     VI_COUNTER_NUM_PER_SRBM, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block WD
    {"VI_WD", kHsaViCounterBlockIdWd, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 36,
     VI_COUNTER_NUM_PER_WD, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block CPG
    {"VI_CPG", kHsaViCounterBlockIdCpg, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 48,
     VI_COUNTER_NUM_PER_CPG, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block CPC
    {"VI_CPC", kHsaViCounterBlockIdCpc, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 24,
     VI_COUNTER_NUM_PER_CPC, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block IOMMUV2
    {"VI_IOMMUV2", kHsaViCounterBlockIdIommuV2, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 25,
     8, 0, 0, true, 0, 0, false, 0, 0},
    // Counter block KernelDriver
    {"VI_KD", kHsaViCounterBlockIdKernelDriver, VI_MAX_NUM_SHADER_ENGINES, 2, 1, CntlMethodNone, 0,
     0, 0, 0, true, 0, 0, false, 0, 0},
    // Name of the last line should be empty to indicate end of all counter groups
    {"", kHsaViCounterBlockIdBlocksLast, 0, 0, 0, CntlMethodNone, 0, 0, 0, 0, false, 0, 0, false, 0,
     0}};

static const uint32_t Gfx8HwBlockCount = sizeof(Gfx8HwBlocks) / sizeof(GpuBlockInfo);

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const GpuCounterRegInfo ViSqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER0_LO__CI__VI,
     mmSQ_PERFCOUNTER0_HI__CI__VI},
    {mmSQ_PERFCOUNTER1_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER1_LO__CI__VI,
     mmSQ_PERFCOUNTER1_HI__CI__VI},
    {mmSQ_PERFCOUNTER2_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER2_LO__CI__VI,
     mmSQ_PERFCOUNTER2_HI__CI__VI},
    {mmSQ_PERFCOUNTER3_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER3_LO__CI__VI,
     mmSQ_PERFCOUNTER3_HI__CI__VI},
    {mmSQ_PERFCOUNTER4_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER4_LO__CI__VI,
     mmSQ_PERFCOUNTER4_HI__CI__VI},
    {mmSQ_PERFCOUNTER5_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER5_LO__CI__VI,
     mmSQ_PERFCOUNTER5_HI__CI__VI},
    {mmSQ_PERFCOUNTER6_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER6_LO__CI__VI,
     mmSQ_PERFCOUNTER6_HI__CI__VI},
    {mmSQ_PERFCOUNTER7_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER7_LO__CI__VI,
     mmSQ_PERFCOUNTER7_HI__CI__VI},
    {mmSQ_PERFCOUNTER8_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER8_LO__CI__VI,
     mmSQ_PERFCOUNTER8_HI__CI__VI},
    {mmSQ_PERFCOUNTER9_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER9_LO__CI__VI,
     mmSQ_PERFCOUNTER9_HI__CI__VI},
    {mmSQ_PERFCOUNTER10_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER10_LO__CI__VI, mmSQ_PERFCOUNTER10_HI__CI__VI},
    {mmSQ_PERFCOUNTER11_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER11_LO__CI__VI, mmSQ_PERFCOUNTER11_HI__CI__VI},
    {mmSQ_PERFCOUNTER12_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER12_LO__CI__VI, mmSQ_PERFCOUNTER12_HI__CI__VI},
    {mmSQ_PERFCOUNTER13_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER13_LO__CI__VI, mmSQ_PERFCOUNTER13_HI__CI__VI},
    {mmSQ_PERFCOUNTER14_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER14_LO__CI__VI, mmSQ_PERFCOUNTER14_HI__CI__VI},
    {mmSQ_PERFCOUNTER15_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI,
     mmSQ_PERFCOUNTER15_LO__CI__VI, mmSQ_PERFCOUNTER15_HI__CI__VI}};

/*
 * DRMDMA
 */
static const GpuCounterRegInfo ViDrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER1_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER1_RESULT__VI, 0},
};

/*
 * IH
 */
static const GpuCounterRegInfo ViIhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER0_RESULT__VI, 0},
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER1_RESULT__VI, 0}};

/*
 * CPF
 */
static const GpuCounterRegInfo ViCpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER0_LO__CI__VI,
     mmCPF_PERFCOUNTER0_HI__CI__VI},
    {mmCPF_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER1_LO__CI__VI,
     mmCPF_PERFCOUNTER1_HI__CI__VI}};

/*
 * DRM
 */
static const GpuCounterRegInfo ViDrmCounterRegAddr[] = {
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}};

/*
 * GRBM
 */
static const GpuCounterRegInfo ViGrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER0_LO__CI__VI,
     mmGRBM_PERFCOUNTER0_HI__CI__VI},
    {mmGRBM_PERFCOUNTER1_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER1_LO__CI__VI,
     mmGRBM_PERFCOUNTER1_HI__CI__VI}};

/*
 * GRBM_SE
 */
static const GpuCounterRegInfo ViGrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE0_PERFCOUNTER_LO__CI__VI,
     mmGRBM_SE0_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE1_PERFCOUNTER_LO__CI__VI,
     mmGRBM_SE1_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE2_PERFCOUNTER_LO__CI__VI,
     mmGRBM_SE2_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE3_PERFCOUNTER_LO__CI__VI,
     mmGRBM_SE3_PERFCOUNTER_HI__CI__VI}};

/*
 * PA_SU
 */
static const GpuCounterRegInfo ViPaSuCounterRegAddr[] = {
    {mmPA_SU_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER0_LO__CI__VI,
     mmPA_SU_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER1_LO__CI__VI,
     mmPA_SU_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER2_LO__CI__VI,
     mmPA_SU_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER3_LO__CI__VI,
     mmPA_SU_PERFCOUNTER3_HI__CI__VI}};

/*
 * PA_SC
 */
static const GpuCounterRegInfo ViPaScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI,
     mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI,
     mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI,
     mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI,
     mmPA_SC_PERFCOUNTER3_HI__CI__VI}};

/*
 * SPI
 */
static const GpuCounterRegInfo ViSpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER0_LO__CI__VI,
     mmSPI_PERFCOUNTER0_HI__CI__VI},
    {mmSPI_PERFCOUNTER1_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER1_LO__CI__VI,
     mmSPI_PERFCOUNTER1_HI__CI__VI},
    {mmSPI_PERFCOUNTER2_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER2_LO__CI__VI,
     mmSPI_PERFCOUNTER2_HI__CI__VI},
    {mmSPI_PERFCOUNTER3_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER3_LO__CI__VI,
     mmSPI_PERFCOUNTER3_HI__CI__VI},
    {mmSPI_PERFCOUNTER4_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER4_LO__CI__VI,
     mmSPI_PERFCOUNTER4_HI__CI__VI},
    {mmSPI_PERFCOUNTER5_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER5_LO__CI__VI,
     mmSPI_PERFCOUNTER5_HI__CI__VI}};

/*
 * TCA
 */
static const GpuCounterRegInfo ViTcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER0_LO__CI__VI,
     mmTCA_PERFCOUNTER0_HI__CI__VI},
    {mmTCA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER1_LO__CI__VI,
     mmTCA_PERFCOUNTER1_HI__CI__VI},
    {mmTCA_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER2_LO__CI__VI,
     mmTCA_PERFCOUNTER2_HI__CI__VI},
    {mmTCA_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER3_LO__CI__VI,
     mmTCA_PERFCOUNTER3_HI__CI__VI}};

/*
 * TCC
 */
static const GpuCounterRegInfo ViTccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER0_LO__CI__VI,
     mmTCC_PERFCOUNTER0_HI__CI__VI},
    {mmTCC_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER1_LO__CI__VI,
     mmTCC_PERFCOUNTER1_HI__CI__VI},
    {mmTCC_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER2_LO__CI__VI,
     mmTCC_PERFCOUNTER2_HI__CI__VI},
    {mmTCC_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER3_LO__CI__VI,
     mmTCC_PERFCOUNTER3_HI__CI__VI}};

/*
 * TCP
 */
static const GpuCounterRegInfo ViTcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER0_LO__CI__VI,
     mmTCP_PERFCOUNTER0_HI__CI__VI},
    {mmTCP_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER1_LO__CI__VI,
     mmTCP_PERFCOUNTER1_HI__CI__VI},
    {mmTCP_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER2_LO__CI__VI,
     mmTCP_PERFCOUNTER2_HI__CI__VI},
    {mmTCP_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER3_LO__CI__VI,
     mmTCP_PERFCOUNTER3_HI__CI__VI}};

/*
 * CB
 */
static const GpuCounterRegInfo ViCbCounterRegAddr[] = {
    {mmCB_PERFCOUNTER0_SELECT__CI__VI, 0, mmCB_PERFCOUNTER0_LO__CI__VI,
     mmCB_PERFCOUNTER0_HI__CI__VI},
    {mmCB_PERFCOUNTER1_SELECT__CI__VI, 0, mmCB_PERFCOUNTER1_LO__CI__VI,
     mmCB_PERFCOUNTER1_HI__CI__VI},
    {mmCB_PERFCOUNTER2_SELECT__CI__VI, 0, mmCB_PERFCOUNTER2_LO__CI__VI,
     mmCB_PERFCOUNTER2_HI__CI__VI},
    {mmCB_PERFCOUNTER3_SELECT__CI__VI, 0, mmCB_PERFCOUNTER3_LO__CI__VI,
     mmCB_PERFCOUNTER3_HI__CI__VI}};

/*
 * DB
 */
static const GpuCounterRegInfo ViDbCounterRegAddr[] = {
    {mmDB_PERFCOUNTER0_SELECT__CI__VI, 0, mmDB_PERFCOUNTER0_LO__CI__VI,
     mmDB_PERFCOUNTER0_HI__CI__VI},
    {mmDB_PERFCOUNTER1_SELECT__CI__VI, 0, mmDB_PERFCOUNTER1_LO__CI__VI,
     mmDB_PERFCOUNTER1_HI__CI__VI},
    {mmDB_PERFCOUNTER2_SELECT__CI__VI, 0, mmDB_PERFCOUNTER2_LO__CI__VI,
     mmDB_PERFCOUNTER2_HI__CI__VI},
    {mmDB_PERFCOUNTER3_SELECT__CI__VI, 0, mmDB_PERFCOUNTER3_LO__CI__VI,
     mmDB_PERFCOUNTER3_HI__CI__VI}};

/*
 * RLC
 */
static const GpuCounterRegInfo ViRlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER0_LO__CI__VI,
     mmRLC_PERFCOUNTER0_HI__CI__VI},
    {mmRLC_PERFCOUNTER1_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER1_LO__CI__VI,
     mmRLC_PERFCOUNTER1_HI__CI__VI}};

/*
 * SC
 */
static const GpuCounterRegInfo ViScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI,
     mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI,
     mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI,
     mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI,
     mmPA_SC_PERFCOUNTER3_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER4_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER4_LO__CI__VI,
     mmPA_SC_PERFCOUNTER4_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER5_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER5_LO__CI__VI,
     mmPA_SC_PERFCOUNTER5_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER6_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER6_LO__CI__VI,
     mmPA_SC_PERFCOUNTER6_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER7_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER7_LO__CI__VI,
     mmPA_SC_PERFCOUNTER7_HI__CI__VI}};

/*
 * SX
 */
static const GpuCounterRegInfo ViSxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT__CI__VI, 0, mmSX_PERFCOUNTER0_LO__CI__VI,
     mmSX_PERFCOUNTER0_HI__CI__VI},
    {mmSX_PERFCOUNTER1_SELECT__CI__VI, 0, mmSX_PERFCOUNTER1_LO__CI__VI,
     mmSX_PERFCOUNTER1_HI__CI__VI},
    {mmSX_PERFCOUNTER2_SELECT__CI__VI, 0, mmSX_PERFCOUNTER2_LO__CI__VI,
     mmSX_PERFCOUNTER2_HI__CI__VI},
    {mmSX_PERFCOUNTER3_SELECT__CI__VI, 0, mmSX_PERFCOUNTER3_LO__CI__VI,
     mmSX_PERFCOUNTER3_HI__CI__VI}};

/*
 * TA
 */
static const GpuCounterRegInfo ViTaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTA_PERFCOUNTER0_LO__CI__VI,
     mmTA_PERFCOUNTER0_HI__CI__VI},
    {mmTA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTA_PERFCOUNTER1_LO__CI__VI,
     mmTA_PERFCOUNTER1_HI__CI__VI}};

/*
 * TD
 */
static const GpuCounterRegInfo ViTdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT__CI__VI, 0, mmTD_PERFCOUNTER0_LO__CI__VI,
     mmTD_PERFCOUNTER0_HI__CI__VI},
    {mmTD_PERFCOUNTER1_SELECT__CI__VI, 0, mmTD_PERFCOUNTER1_LO__CI__VI,
     mmTD_PERFCOUNTER1_HI__CI__VI}};

/*
 * GDS
 */
static const GpuCounterRegInfo ViGdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER0_LO__CI__VI,
     mmGDS_PERFCOUNTER0_HI__CI__VI},
    {mmGDS_PERFCOUNTER1_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER1_LO__CI__VI,
     mmGDS_PERFCOUNTER1_HI__CI__VI},
    {mmGDS_PERFCOUNTER2_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER2_LO__CI__VI,
     mmGDS_PERFCOUNTER2_HI__CI__VI},
    {mmGDS_PERFCOUNTER3_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER3_LO__CI__VI,
     mmGDS_PERFCOUNTER3_HI__CI__VI}};

/*
 * VGT
 */
static const GpuCounterRegInfo ViVgtCounterRegAddr[] = {
    {mmVGT_PERFCOUNTER0_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER0_LO__CI__VI,
     mmVGT_PERFCOUNTER0_HI__CI__VI},
    {mmVGT_PERFCOUNTER1_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER1_LO__CI__VI,
     mmVGT_PERFCOUNTER1_HI__CI__VI},
    {mmVGT_PERFCOUNTER2_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER2_LO__CI__VI,
     mmVGT_PERFCOUNTER2_HI__CI__VI},
    {mmVGT_PERFCOUNTER3_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER3_LO__CI__VI,
     mmVGT_PERFCOUNTER3_HI__CI__VI}};

/*
 * IA
 */
static const GpuCounterRegInfo ViIaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT__CI__VI, 0, mmIA_PERFCOUNTER0_LO__CI__VI,
     mmIA_PERFCOUNTER0_HI__CI__VI},
    {mmIA_PERFCOUNTER1_SELECT__CI__VI, 0, mmIA_PERFCOUNTER1_LO__CI__VI,
     mmIA_PERFCOUNTER1_HI__CI__VI},
    {mmIA_PERFCOUNTER2_SELECT__CI__VI, 0, mmIA_PERFCOUNTER2_LO__CI__VI,
     mmIA_PERFCOUNTER2_HI__CI__VI},
    {mmIA_PERFCOUNTER3_SELECT__CI__VI, 0, mmIA_PERFCOUNTER3_LO__CI__VI,
     mmIA_PERFCOUNTER3_HI__CI__VI}};

/*
 * MC
 */
static const GpuCounterRegInfo ViMcCounterRegAddr[] = {
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, 0, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI,
     mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}};

/*
 * SRBM
 */
static const GpuCounterRegInfo ViSrbmCounterRegAddr[] = {
    {mmSRBM_PERFCOUNTER0_SELECT__VI, 0, mmSRBM_PERFCOUNTER0_LO__VI, mmSRBM_PERFCOUNTER0_HI__VI},
    {mmSRBM_PERFCOUNTER1_SELECT__VI, 0, mmSRBM_PERFCOUNTER1_LO__VI, mmSRBM_PERFCOUNTER1_HI__VI}};

/*
 * WD
 */
static const GpuCounterRegInfo ViWdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT__CI__VI, 0, mmWD_PERFCOUNTER0_LO__CI__VI,
     mmWD_PERFCOUNTER0_HI__CI__VI},
    {mmWD_PERFCOUNTER1_SELECT__CI__VI, 0, mmWD_PERFCOUNTER1_LO__CI__VI,
     mmWD_PERFCOUNTER1_HI__CI__VI},
    {mmWD_PERFCOUNTER2_SELECT__CI__VI, 0, mmWD_PERFCOUNTER2_LO__CI__VI,
     mmWD_PERFCOUNTER2_HI__CI__VI},
    {mmWD_PERFCOUNTER3_SELECT__CI__VI, 0, mmWD_PERFCOUNTER3_LO__CI__VI,
     mmWD_PERFCOUNTER3_HI__CI__VI}};

/*
 * CPG
 */
static const GpuCounterRegInfo ViCpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER0_LO__CI__VI,
     mmCPG_PERFCOUNTER0_HI__CI__VI},
    {mmCPG_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER1_LO__CI__VI,
     mmCPG_PERFCOUNTER1_HI__CI__VI}};

/*
 * CPC
 */
static const GpuCounterRegInfo ViCpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER0_LO__CI__VI,
     mmCPC_PERFCOUNTER0_HI__CI__VI},
    {mmCPC_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER1_LO__CI__VI,
     mmCPC_PERFCOUNTER1_HI__CI__VI}};

}  // namespace gfx8
}  // namespace gfxip

#endif  // _VI_BLOCKINFO_H_
