#ifndef _GFX8_BLOCKTABLE_H_
#define _GFX8_BLOCKTABLE_H_

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const CounterRegInfo ViSqCounterRegAddr[] = {
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
static const CounterRegInfo ViDrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER1_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER1_RESULT__VI, 0},
};

/*
 * IH
 */
static const CounterRegInfo ViIhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER0_RESULT__VI, 0},
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER1_RESULT__VI, 0}};

/*
 * CPF
 */
static const CounterRegInfo ViCpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER0_LO__CI__VI,
     mmCPF_PERFCOUNTER0_HI__CI__VI},
    {mmCPF_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER1_LO__CI__VI,
     mmCPF_PERFCOUNTER1_HI__CI__VI}};

/*
 * DRM
 */
static const CounterRegInfo ViDrmCounterRegAddr[] = {
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}};

/*
 * GRBM
 */
static const CounterRegInfo ViGrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER0_LO__CI__VI,
     mmGRBM_PERFCOUNTER0_HI__CI__VI},
    {mmGRBM_PERFCOUNTER1_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER1_LO__CI__VI,
     mmGRBM_PERFCOUNTER1_HI__CI__VI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo ViGrbmSeCounterRegAddr[] = {
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
static const CounterRegInfo ViPaSuCounterRegAddr[] = {
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
static const CounterRegInfo ViPaScCounterRegAddr[] = {
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
static const CounterRegInfo ViSpiCounterRegAddr[] = {
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
static const CounterRegInfo ViTcaCounterRegAddr[] = {
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
static const CounterRegInfo ViTccCounterRegAddr[] = {
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
static const CounterRegInfo ViTcpCounterRegAddr[] = {
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
static const CounterRegInfo ViCbCounterRegAddr[] = {
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
static const CounterRegInfo ViDbCounterRegAddr[] = {
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
static const CounterRegInfo ViRlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER0_LO__CI__VI,
     mmRLC_PERFCOUNTER0_HI__CI__VI},
    {mmRLC_PERFCOUNTER1_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER1_LO__CI__VI,
     mmRLC_PERFCOUNTER1_HI__CI__VI}};

/*
 * SC
 */
static const CounterRegInfo ViScCounterRegAddr[] = {
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
static const CounterRegInfo ViSxCounterRegAddr[] = {
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
static const CounterRegInfo ViTaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTA_PERFCOUNTER0_LO__CI__VI,
     mmTA_PERFCOUNTER0_HI__CI__VI},
    {mmTA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTA_PERFCOUNTER1_LO__CI__VI,
     mmTA_PERFCOUNTER1_HI__CI__VI}};

/*
 * TD
 */
static const CounterRegInfo ViTdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT__CI__VI, 0, mmTD_PERFCOUNTER0_LO__CI__VI,
     mmTD_PERFCOUNTER0_HI__CI__VI},
    {mmTD_PERFCOUNTER1_SELECT__CI__VI, 0, mmTD_PERFCOUNTER1_LO__CI__VI,
     mmTD_PERFCOUNTER1_HI__CI__VI}};

/*
 * GDS
 */
static const CounterRegInfo ViGdsCounterRegAddr[] = {
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
static const CounterRegInfo ViVgtCounterRegAddr[] = {
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
static const CounterRegInfo ViIaCounterRegAddr[] = {
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
static const CounterRegInfo ViMcCounterRegAddr[] = {
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
static const CounterRegInfo ViSrbmCounterRegAddr[] = {
    {mmSRBM_PERFCOUNTER0_SELECT__VI, 0, mmSRBM_PERFCOUNTER0_LO__VI, mmSRBM_PERFCOUNTER0_HI__VI},
    {mmSRBM_PERFCOUNTER1_SELECT__VI, 0, mmSRBM_PERFCOUNTER1_LO__VI, mmSRBM_PERFCOUNTER1_HI__VI}};

/*
 * WD
 */
static const CounterRegInfo ViWdCounterRegAddr[] = {
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
static const CounterRegInfo ViCpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER0_LO__CI__VI,
     mmCPG_PERFCOUNTER0_HI__CI__VI},
    {mmCPG_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER1_LO__CI__VI,
     mmCPG_PERFCOUNTER1_HI__CI__VI}};

/*
 * CPC
 */
static const CounterRegInfo ViCpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER0_LO__CI__VI,
     mmCPC_PERFCOUNTER0_HI__CI__VI},
    {mmCPC_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER1_LO__CI__VI,
     mmCPC_PERFCOUNTER1_HI__CI__VI}};

/**
 * Table containing CounterGroups which represent VI hardware blocks
 * as defined by \ref GpuBlockInfo structure
 */
// Counter block CB
static GpuBlockInfo ViCbCounterBlockInfo = {
    "VI_CB",   kHsaViCounterBlockIdCb,
    VI_NUM_CB, CntlMethodBySeAndInstance,
    395,       VI_COUNTER_NUM_PER_CB,
    0,         0,
    true,      ViCbCounterRegAddr,
    true,      gfx8_cntx_prim::select_value<regCB_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block CPF
static GpuBlockInfo ViCpfCounterBlockInfo = {
    "VI_CPF", kHsaViCounterBlockIdCpf,
    1,        CntlMethodNone,
    19,       VI_COUNTER_NUM_PER_CPF,
    0,        0,
    true,     ViCpfCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block DB
static GpuBlockInfo ViDbCounterBlockInfo = {
    "VI_DB",   kHsaViCounterBlockIdDb,
    VI_NUM_DB, CntlMethodBySeAndInstance,
    256,       VI_COUNTER_NUM_PER_DB,
    0,         0,
    true,      ViDbCounterRegAddr,
    true,      gfx8_cntx_prim::select_value<regDB_PERFCOUNTER0_SELECT>,
    false};
// Counter block GRBM
static GpuBlockInfo ViGrbmCounterBlockInfo = {
    "VI_GRBM", kHsaViCounterBlockIdGrbm,
    1,         CntlMethodNone,
    33,        VI_COUNTER_NUM_PER_GRBM,
    0,         0,
    true,      ViGrbmCounterRegAddr,
    false,     gfx8_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>,
    false};
// Counter block GRBMSE
static GpuBlockInfo ViGrbmSeCounterBlockInfo = {
    "VI_GRBMSE", kHsaViCounterBlockIdGrbmSe,
    1,           CntlMethodNone,
    14,          VI_COUNTER_NUM_PER_GRBMSE,
    0,           0,
    true,        ViGrbmSeCounterRegAddr,
    false,       gfx8_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>,
    false};
// Counter block PA_SU
static GpuBlockInfo ViPaSuCounterBlockInfo = {
    "VI_PA_SU", kHsaViCounterBlockIdPaSu,
    1,          CntlMethodBySe,
    152,        VI_COUNTER_NUM_PER_PA_SU,
    0,          0,
    true,       ViPaSuCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regPA_SU_PERFCOUNTER0_SELECT>,
    false};
// Counter block PA_SC
static GpuBlockInfo ViPaScCounterBlockInfo = {
    "VI_PA_SC", kHsaViCounterBlockIdPaSc,
    1,          CntlMethodBySe,
    396,        VI_COUNTER_NUM_PER_PA_SC,
    0,          0,
    true,       ViPaScCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regPA_SC_PERFCOUNTER0_SELECT>,
    false};
// Counter block SPI
static GpuBlockInfo ViSpiCounterBlockInfo = {
    "VI_SPI", kHsaViCounterBlockIdSpi,
    1,        CntlMethodBySe,
    196,      VI_COUNTER_NUM_PER_SPI,
    0,        0,
    true,     ViSpiCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>,
    false};
// Counter block SQ
static GpuBlockInfo ViSqCounterBlockInfo = {
    "VI_SQ", kHsaViCounterBlockIdSq,
    1,       CntlMethodBySe,
    298,     VI_COUNTER_NUM_PER_SQ,
    0,       0,
    true,    ViSqCounterRegAddr,
    false,   gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqEsCounterBlockInfo = {
    "VI_SQ_ES", kHsaViCounterBlockIdSqEs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqGsCounterBlockInfo = {
    "VI_SQ_GS", kHsaViCounterBlockIdSqGs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqVsCounterBlockInfo = {
    "VI_SQ_VS", kHsaViCounterBlockIdSqVs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqPsCounterBlockInfo = {
    "VI_SQ_PS", kHsaViCounterBlockIdSqPs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqLsCounterBlockInfo = {
    "VI_SQ_LS", kHsaViCounterBlockIdSqLs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqHsCounterBlockInfo = {
    "VI_SQ_HS", kHsaViCounterBlockIdSqHs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
static GpuBlockInfo ViSqCsCounterBlockInfo = {
    "VI_SQ_CS", kHsaViCounterBlockIdSqCs,
    1,          CntlMethodBySe,
    298,        VI_COUNTER_NUM_PER_SQ,
    0,          0,
    true,       ViSqCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT__CI__VI>,
    true};
// Counter block SX
static GpuBlockInfo ViSxCounterBlockInfo = {
    "VI_SX", kHsaViCounterBlockIdSx, 1,    CntlMethodBySe,
    33,      VI_COUNTER_NUM_PER_SX,  0,    0,
    true,    ViSxCounterRegAddr,     true, gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>,
    false};
// Counter block TA
static GpuBlockInfo ViTaCounterBlockInfo = {
    "VI_TA",   kHsaViCounterBlockIdTa,
    VI_NUM_TA, CntlMethodBySeAndInstance,
    118,       VI_COUNTER_NUM_PER_TA,
    0,         0,
    true,      ViTaCounterRegAddr,
    false,     gfx8_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>,
    false};
// Counter block TCA
static GpuBlockInfo ViTcaCounterBlockInfo = {
    "VI_TCA",   kHsaViCounterBlockIdTca,
    VI_NUM_TCA, CntlMethodByInstance,
    34,         VI_COUNTER_NUM_PER_TCA,
    0,          0,
    true,       ViTcaCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block TCC
static GpuBlockInfo ViTccCounterBlockInfo = {
    "VI_TCC",   kHsaViCounterBlockIdTcc,
    VI_NUM_TCC, CntlMethodByInstance,
    191,        VI_COUNTER_NUM_PER_TCC,
    0,          0,
    true,       ViTccCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block TD
static GpuBlockInfo ViTdCounterBlockInfo = {
    "VI_TD",   kHsaViCounterBlockIdTd,
    VI_NUM_TD, CntlMethodBySeAndInstance,
    54,        VI_COUNTER_NUM_PER_TD,
    0,         0,
    true,      ViTdCounterRegAddr,
    false,     gfx8_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>,
    false};
// Counter block TCP
static GpuBlockInfo ViTcpCounterBlockInfo = {
    "VI_TCP",   kHsaViCounterBlockIdTcp,
    VI_NUM_TCP, CntlMethodBySeAndInstance,
    182,        VI_COUNTER_NUM_PER_TCP,
    0,          0,
    true,       ViTcpCounterRegAddr,
    false,      gfx8_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block GDS
static GpuBlockInfo ViGdsCounterBlockInfo = {
    "VI_GDS", kHsaViCounterBlockIdGds,
    1,        CntlMethodNone,
    120,      VI_COUNTER_NUM_PER_GDS,
    0,        0,
    true,     ViGdsCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>,
    false};
// Counter block VGT
static GpuBlockInfo ViVgtCounterBlockInfo = {
    "VI_VGT", kHsaViCounterBlockIdVgt,
    1,        CntlMethodBySe,
    145,      VI_COUNTER_NUM_PER_VGT,
    0,        0,
    true,     ViVgtCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regVGT_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block IA
static GpuBlockInfo ViIaCounterBlockInfo = {
    "VI_IA", kHsaViCounterBlockIdIa,
    1,       CntlMethodBySe,
    23,      VI_COUNTER_NUM_PER_IA,
    0,       0,
    true,    ViIaCounterRegAddr,
    false,   gfx8_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block MC
static GpuBlockInfo ViMcCounterBlockInfo = {
    "VI_MC", kHsaViCounterBlockIdMc, 1,     CntlMethodNone, 22,   VI_COUNTER_NUM_PER_MC, 0, 0,
    true,    ViMcCounterRegAddr,     false, NULL,           false};
// Counter block SRBM
static GpuBlockInfo ViSrbmCounterBlockInfo = {
    "VI_SRBM", kHsaViCounterBlockIdSrbm,
    1,         CntlMethodNone,
    19,        VI_COUNTER_NUM_PER_SRBM,
    0,         0,
    true,      ViSrbmCounterRegAddr,
    false,     gfx8_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>,
    false};
// Counter block WD
static GpuBlockInfo ViWdCounterBlockInfo = {
    "VI_WD", kHsaViCounterBlockIdWd,
    1,       CntlMethodNone,
    36,      VI_COUNTER_NUM_PER_WD,
    0,       0,
    true,    ViWdCounterRegAddr,
    false,   gfx8_cntx_prim::select_value<regWD_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block CPG
static GpuBlockInfo ViCpgCounterBlockInfo = {
    "VI_CPG", kHsaViCounterBlockIdCpg,
    1,        CntlMethodNone,
    48,       VI_COUNTER_NUM_PER_CPG,
    0,        0,
    true,     ViCpgCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regCPG_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block CPC
static GpuBlockInfo ViCpcCounterBlockInfo = {
    "VI_CPC", kHsaViCounterBlockIdCpc,
    1,        CntlMethodNone,
    24,       VI_COUNTER_NUM_PER_CPC,
    0,        0,
    true,     ViCpcCounterRegAddr,
    false,    gfx8_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT__CI__VI>,
    false};
// Counter block IOMMUV2
static GpuBlockInfo ViCounterBlockIommuV2Info = {"VI_IOMMUV2",
                                                 kHsaViCounterBlockIdIommuV2,
                                                 1,
                                                 CntlMethodNone,
                                                 25,
                                                 8,
                                                 0,
                                                 0,
                                                 true,
                                                 NULL,
                                                 false,
                                                 NULL,
                                                 false};
// Counter block KernelDriver
static GpuBlockInfo ViKernelDriverCounterBlockInfo = {"VI_KD", kHsaViCounterBlockIdKernelDriver,
                                                      1,       CntlMethodNone,
                                                      0,       0,
                                                      0,       0,
                                                      true,    NULL,
                                                      false,   NULL,
                                                      false};

#endif  // _GFX8_BLOCKTABLE_H_
