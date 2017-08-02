#ifndef _GFX8_BLOCKTABLE_H_
#define _GFX8_BLOCKTABLE_H_

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const CounterRegInfo SqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER0_LO__CI__VI, mmSQ_PERFCOUNTER0_HI__CI__VI},
    {mmSQ_PERFCOUNTER1_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER1_LO__CI__VI, mmSQ_PERFCOUNTER1_HI__CI__VI},
    {mmSQ_PERFCOUNTER2_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER2_LO__CI__VI, mmSQ_PERFCOUNTER2_HI__CI__VI},
    {mmSQ_PERFCOUNTER3_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER3_LO__CI__VI, mmSQ_PERFCOUNTER3_HI__CI__VI},
    {mmSQ_PERFCOUNTER4_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER4_LO__CI__VI, mmSQ_PERFCOUNTER4_HI__CI__VI},
    {mmSQ_PERFCOUNTER5_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER5_LO__CI__VI, mmSQ_PERFCOUNTER5_HI__CI__VI},
    {mmSQ_PERFCOUNTER6_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER6_LO__CI__VI, mmSQ_PERFCOUNTER6_HI__CI__VI},
    {mmSQ_PERFCOUNTER7_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER7_LO__CI__VI, mmSQ_PERFCOUNTER7_HI__CI__VI},
    {mmSQ_PERFCOUNTER8_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER8_LO__CI__VI, mmSQ_PERFCOUNTER8_HI__CI__VI},
    {mmSQ_PERFCOUNTER9_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER9_LO__CI__VI, mmSQ_PERFCOUNTER9_HI__CI__VI},
    {mmSQ_PERFCOUNTER10_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER10_LO__CI__VI, mmSQ_PERFCOUNTER10_HI__CI__VI},
    {mmSQ_PERFCOUNTER11_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER11_LO__CI__VI, mmSQ_PERFCOUNTER11_HI__CI__VI},
    {mmSQ_PERFCOUNTER12_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER12_LO__CI__VI, mmSQ_PERFCOUNTER12_HI__CI__VI},
    {mmSQ_PERFCOUNTER13_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER13_LO__CI__VI, mmSQ_PERFCOUNTER13_HI__CI__VI},
    {mmSQ_PERFCOUNTER14_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER14_LO__CI__VI, mmSQ_PERFCOUNTER14_HI__CI__VI},
    {mmSQ_PERFCOUNTER15_SELECT__CI__VI, mmSQ_PERFCOUNTER_CTRL__CI__VI, mmSQ_PERFCOUNTER15_LO__CI__VI, mmSQ_PERFCOUNTER15_HI__CI__VI}};

/*
 * DRMDMA
 */
static const CounterRegInfo DrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA0_PERFMON_CNTL__VI, 0, mmSDMA0_PERFCOUNTER1_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER0_RESULT__VI, 0},
    {mmSDMA1_PERFMON_CNTL__VI, 0, mmSDMA1_PERFCOUNTER1_RESULT__VI, 0}};

/*
 * IH
 */
static const CounterRegInfo IhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER0_RESULT__VI, 0},
    {mmIH_PERFMON_CNTL__VI, 0, mmIH_PERFCOUNTER1_RESULT__VI, 0}};

/*
 * CPF
 */
static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER0_LO__CI__VI, mmCPF_PERFCOUNTER0_HI__CI__VI},
    {mmCPF_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPF_PERFCOUNTER1_LO__CI__VI, mmCPF_PERFCOUNTER1_HI__CI__VI}};

/*
 * DRM
 */
static const CounterRegInfo DrmCounterRegAddr[] = {
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}};

/*
 * GRBM
 */
static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER0_LO__CI__VI, mmGRBM_PERFCOUNTER0_HI__CI__VI},
    {mmGRBM_PERFCOUNTER1_SELECT__CI__VI, 0, mmGRBM_PERFCOUNTER1_LO__CI__VI, mmGRBM_PERFCOUNTER1_HI__CI__VI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo GrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE0_PERFCOUNTER_LO__CI__VI, mmGRBM_SE0_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE1_PERFCOUNTER_LO__CI__VI, mmGRBM_SE1_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE2_PERFCOUNTER_LO__CI__VI, mmGRBM_SE2_PERFCOUNTER_HI__CI__VI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT__CI__VI, 0, mmGRBM_SE3_PERFCOUNTER_LO__CI__VI, mmGRBM_SE3_PERFCOUNTER_HI__CI__VI}};

/*
 * PA_SU
 */
static const CounterRegInfo PaSuCounterRegAddr[] = {
    {mmPA_SU_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER0_LO__CI__VI, mmPA_SU_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER1_LO__CI__VI, mmPA_SU_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER2_LO__CI__VI, mmPA_SU_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SU_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SU_PERFCOUNTER3_LO__CI__VI, mmPA_SU_PERFCOUNTER3_HI__CI__VI}};

/*
 * PA_SC
 */
static const CounterRegInfo PaScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI, mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI, mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI, mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI, mmPA_SC_PERFCOUNTER3_HI__CI__VI}};

/*
 * SPI
 */
static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER0_LO__CI__VI, mmSPI_PERFCOUNTER0_HI__CI__VI},
    {mmSPI_PERFCOUNTER1_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER1_LO__CI__VI, mmSPI_PERFCOUNTER1_HI__CI__VI},
    {mmSPI_PERFCOUNTER2_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER2_LO__CI__VI, mmSPI_PERFCOUNTER2_HI__CI__VI},
    {mmSPI_PERFCOUNTER3_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER3_LO__CI__VI, mmSPI_PERFCOUNTER3_HI__CI__VI},
    {mmSPI_PERFCOUNTER4_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER4_LO__CI__VI, mmSPI_PERFCOUNTER4_HI__CI__VI},
    {mmSPI_PERFCOUNTER5_SELECT__CI__VI, 0, mmSPI_PERFCOUNTER5_LO__CI__VI, mmSPI_PERFCOUNTER5_HI__CI__VI}};

/*
 * TCA
 */
static const CounterRegInfo TcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER0_LO__CI__VI, mmTCA_PERFCOUNTER0_HI__CI__VI},
    {mmTCA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER1_LO__CI__VI, mmTCA_PERFCOUNTER1_HI__CI__VI},
    {mmTCA_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER2_LO__CI__VI, mmTCA_PERFCOUNTER2_HI__CI__VI},
    {mmTCA_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCA_PERFCOUNTER3_LO__CI__VI, mmTCA_PERFCOUNTER3_HI__CI__VI}};

/*
 * TCC
 */
static const CounterRegInfo TccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER0_LO__CI__VI, mmTCC_PERFCOUNTER0_HI__CI__VI},
    {mmTCC_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER1_LO__CI__VI, mmTCC_PERFCOUNTER1_HI__CI__VI},
    {mmTCC_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER2_LO__CI__VI, mmTCC_PERFCOUNTER2_HI__CI__VI},
    {mmTCC_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCC_PERFCOUNTER3_LO__CI__VI, mmTCC_PERFCOUNTER3_HI__CI__VI}};

/*
 * TCP
 */
static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER0_LO__CI__VI, mmTCP_PERFCOUNTER0_HI__CI__VI},
    {mmTCP_PERFCOUNTER1_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER1_LO__CI__VI, mmTCP_PERFCOUNTER1_HI__CI__VI},
    {mmTCP_PERFCOUNTER2_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER2_LO__CI__VI, mmTCP_PERFCOUNTER2_HI__CI__VI},
    {mmTCP_PERFCOUNTER3_SELECT__CI__VI, 0, mmTCP_PERFCOUNTER3_LO__CI__VI, mmTCP_PERFCOUNTER3_HI__CI__VI}};

/*
 * CB
 */
static const CounterRegInfo CbCounterRegAddr[] = {
    {mmCB_PERFCOUNTER0_SELECT__CI__VI, 0, mmCB_PERFCOUNTER0_LO__CI__VI, mmCB_PERFCOUNTER0_HI__CI__VI},
    {mmCB_PERFCOUNTER1_SELECT__CI__VI, 0, mmCB_PERFCOUNTER1_LO__CI__VI, mmCB_PERFCOUNTER1_HI__CI__VI},
    {mmCB_PERFCOUNTER2_SELECT__CI__VI, 0, mmCB_PERFCOUNTER2_LO__CI__VI, mmCB_PERFCOUNTER2_HI__CI__VI},
    {mmCB_PERFCOUNTER3_SELECT__CI__VI, 0, mmCB_PERFCOUNTER3_LO__CI__VI, mmCB_PERFCOUNTER3_HI__CI__VI}};

/*
 * DB
 */
static const CounterRegInfo DbCounterRegAddr[] = {
    {mmDB_PERFCOUNTER0_SELECT__CI__VI, 0, mmDB_PERFCOUNTER0_LO__CI__VI, mmDB_PERFCOUNTER0_HI__CI__VI},
    {mmDB_PERFCOUNTER1_SELECT__CI__VI, 0, mmDB_PERFCOUNTER1_LO__CI__VI, mmDB_PERFCOUNTER1_HI__CI__VI},
    {mmDB_PERFCOUNTER2_SELECT__CI__VI, 0, mmDB_PERFCOUNTER2_LO__CI__VI, mmDB_PERFCOUNTER2_HI__CI__VI},
    {mmDB_PERFCOUNTER3_SELECT__CI__VI, 0, mmDB_PERFCOUNTER3_LO__CI__VI, mmDB_PERFCOUNTER3_HI__CI__VI}};

/*
 * RLC
 */
static const CounterRegInfo RlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER0_LO__CI__VI, mmRLC_PERFCOUNTER0_HI__CI__VI},
    {mmRLC_PERFCOUNTER1_SELECT__CI__VI, 0, mmRLC_PERFCOUNTER1_LO__CI__VI, mmRLC_PERFCOUNTER1_HI__CI__VI}};

/*
 * SC
 */
static const CounterRegInfo ScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER0_LO__CI__VI, mmPA_SC_PERFCOUNTER0_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER1_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER1_LO__CI__VI, mmPA_SC_PERFCOUNTER1_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER2_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER2_LO__CI__VI, mmPA_SC_PERFCOUNTER2_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER3_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER3_LO__CI__VI, mmPA_SC_PERFCOUNTER3_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER4_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER4_LO__CI__VI, mmPA_SC_PERFCOUNTER4_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER5_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER5_LO__CI__VI, mmPA_SC_PERFCOUNTER5_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER6_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER6_LO__CI__VI, mmPA_SC_PERFCOUNTER6_HI__CI__VI},
    {mmPA_SC_PERFCOUNTER7_SELECT__CI__VI, 0, mmPA_SC_PERFCOUNTER7_LO__CI__VI, mmPA_SC_PERFCOUNTER7_HI__CI__VI}};

/*
 * SX
 */
static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT__CI__VI, 0, mmSX_PERFCOUNTER0_LO__CI__VI, mmSX_PERFCOUNTER0_HI__CI__VI},
    {mmSX_PERFCOUNTER1_SELECT__CI__VI, 0, mmSX_PERFCOUNTER1_LO__CI__VI, mmSX_PERFCOUNTER1_HI__CI__VI},
    {mmSX_PERFCOUNTER2_SELECT__CI__VI, 0, mmSX_PERFCOUNTER2_LO__CI__VI, mmSX_PERFCOUNTER2_HI__CI__VI},
    {mmSX_PERFCOUNTER3_SELECT__CI__VI, 0, mmSX_PERFCOUNTER3_LO__CI__VI, mmSX_PERFCOUNTER3_HI__CI__VI}};

/*
 * TA
 */
static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT__CI__VI, 0, mmTA_PERFCOUNTER0_LO__CI__VI, mmTA_PERFCOUNTER0_HI__CI__VI},
    {mmTA_PERFCOUNTER1_SELECT__CI__VI, 0, mmTA_PERFCOUNTER1_LO__CI__VI, mmTA_PERFCOUNTER1_HI__CI__VI}};

/*
 * TD
 */
static const CounterRegInfo TdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT__CI__VI, 0, mmTD_PERFCOUNTER0_LO__CI__VI, mmTD_PERFCOUNTER0_HI__CI__VI},
    {mmTD_PERFCOUNTER1_SELECT__CI__VI, 0, mmTD_PERFCOUNTER1_LO__CI__VI, mmTD_PERFCOUNTER1_HI__CI__VI}};

/*
 * GDS
 */
static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER0_LO__CI__VI, mmGDS_PERFCOUNTER0_HI__CI__VI},
    {mmGDS_PERFCOUNTER1_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER1_LO__CI__VI, mmGDS_PERFCOUNTER1_HI__CI__VI},
    {mmGDS_PERFCOUNTER2_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER2_LO__CI__VI, mmGDS_PERFCOUNTER2_HI__CI__VI},
    {mmGDS_PERFCOUNTER3_SELECT__CI__VI, 0, mmGDS_PERFCOUNTER3_LO__CI__VI, mmGDS_PERFCOUNTER3_HI__CI__VI}};

/*
 * VGT
 */
static const CounterRegInfo VgtCounterRegAddr[] = {
    {mmVGT_PERFCOUNTER0_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER0_LO__CI__VI, mmVGT_PERFCOUNTER0_HI__CI__VI},
    {mmVGT_PERFCOUNTER1_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER1_LO__CI__VI, mmVGT_PERFCOUNTER1_HI__CI__VI},
    {mmVGT_PERFCOUNTER2_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER2_LO__CI__VI, mmVGT_PERFCOUNTER2_HI__CI__VI},
    {mmVGT_PERFCOUNTER3_SELECT__CI__VI, 0, mmVGT_PERFCOUNTER3_LO__CI__VI, mmVGT_PERFCOUNTER3_HI__CI__VI}};

/*
 * IA
 */
static const CounterRegInfo IaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT__CI__VI, 0, mmIA_PERFCOUNTER0_LO__CI__VI, mmIA_PERFCOUNTER0_HI__CI__VI},
    {mmIA_PERFCOUNTER1_SELECT__CI__VI, 0, mmIA_PERFCOUNTER1_LO__CI__VI, mmIA_PERFCOUNTER1_HI__CI__VI},
    {mmIA_PERFCOUNTER2_SELECT__CI__VI, 0, mmIA_PERFCOUNTER2_LO__CI__VI, mmIA_PERFCOUNTER2_HI__CI__VI},
    {mmIA_PERFCOUNTER3_SELECT__CI__VI, 0, mmIA_PERFCOUNTER3_LO__CI__VI, mmIA_PERFCOUNTER3_HI__CI__VI}};

/*
 * MC_SEQ
 */
static const CounterRegInfo McSeqCounterRegAddr[] = {
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_A_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_A_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_B_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_B_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_C_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_C_I1__VI},
    {mmMC_SEQ_PERF_SEQ_CTL__SI__VI, mmMC_CONFIG_MCD, mmMC_SEQ_PERF_SEQ_CNT_D_I0__VI, mmMC_SEQ_PERF_SEQ_CNT_D_I1__VI}};

/*
 * SRBM
 */
static const CounterRegInfo SrbmCounterRegAddr[] = {
    {mmSRBM_PERFCOUNTER0_SELECT__VI, 0, mmSRBM_PERFCOUNTER0_LO__VI, mmSRBM_PERFCOUNTER0_HI__VI},
    {mmSRBM_PERFCOUNTER1_SELECT__VI, 0, mmSRBM_PERFCOUNTER1_LO__VI, mmSRBM_PERFCOUNTER1_HI__VI}};

/*
 * WD
 */
static const CounterRegInfo WdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT__CI__VI, 0, mmWD_PERFCOUNTER0_LO__CI__VI, mmWD_PERFCOUNTER0_HI__CI__VI},
    {mmWD_PERFCOUNTER1_SELECT__CI__VI, 0, mmWD_PERFCOUNTER1_LO__CI__VI, mmWD_PERFCOUNTER1_HI__CI__VI},
    {mmWD_PERFCOUNTER2_SELECT__CI__VI, 0, mmWD_PERFCOUNTER2_LO__CI__VI, mmWD_PERFCOUNTER2_HI__CI__VI},
    {mmWD_PERFCOUNTER3_SELECT__CI__VI, 0, mmWD_PERFCOUNTER3_LO__CI__VI, mmWD_PERFCOUNTER3_HI__CI__VI}};

/*
 * CPG
 */
static const CounterRegInfo CpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER0_LO__CI__VI, mmCPG_PERFCOUNTER0_HI__CI__VI},
    {mmCPG_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPG_PERFCOUNTER1_LO__CI__VI, mmCPG_PERFCOUNTER1_HI__CI__VI}};

/*
 * CPC
 */
static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER0_LO__CI__VI, mmCPC_PERFCOUNTER0_HI__CI__VI},
    {mmCPC_PERFCOUNTER1_SELECT__CI__VI, 0, mmCPC_PERFCOUNTER1_LO__CI__VI, mmCPC_PERFCOUNTER1_HI__CI__VI}};

// Counter block info table
// Counter block CB
static const GpuBlockInfo CbCounterBlockInfo = {"CB", CbCounterBlockId, CbCounterBlockNumInstances, CbCounterBlockMaxEvent, CbCounterBlockNumCounters, CbCounterRegAddr, gfx8_cntx_prim::select_value<regCB_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr};
// Counter block CPF
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx8_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block DB
static const GpuBlockInfo DbCounterBlockInfo = {"DB", DbCounterBlockId, DbCounterBlockNumInstances, DbCounterBlockMaxEvent, DbCounterBlockNumCounters, DbCounterRegAddr, gfx8_cntx_prim::select_value<regDB_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block GRBMSE
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBMSE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx8_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
// Counter block PA_SU
static const GpuBlockInfo PaSuCounterBlockInfo = {"PA_SU", PaSuCounterBlockId, 1, PaSuCounterBlockMaxEvent, PaSuCounterBlockNumCounters, PaSuCounterRegAddr, gfx8_cntx_prim::select_value<regPA_SU_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block PA_SC
static const GpuBlockInfo PaScCounterBlockInfo = {"PA_SC", PaScCounterBlockId, 1, PaScCounterBlockMaxEvent, PaScCounterBlockNumCounters, PaScCounterRegAddr, gfx8_cntx_prim::select_value<regPA_SC_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx8_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqEsCounterBlockInfo = {"SQ_ES", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqGsCounterBlockInfo = {"SQ_GS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqVsCounterBlockInfo = {"SQ_VS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqPsCounterBlockInfo = {"SQ_PS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqLsCounterBlockInfo = {"SQ_LS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqHsCounterBlockInfo = {"SQ_HS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx8_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx8_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx8_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block TCA
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, TcaCounterRegAddr, gfx8_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block TCC
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, TccCounterRegAddr, gfx8_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block TD
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx8_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block TCP
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx8_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr};
// Counter block GDS
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx8_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block VGT
static const GpuBlockInfo VgtCounterBlockInfo = {"VGT", VgtCounterBlockId, 1, VgtCounterBlockMaxEvent, VgtCounterBlockNumCounters, VgtCounterRegAddr, gfx8_cntx_prim::select_value<regVGT_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr};
// Counter block IA
static const GpuBlockInfo IaCounterBlockInfo = {"IA", IaCounterBlockId, 1, IaCounterBlockMaxEvent, IaCounterBlockNumCounters, IaCounterRegAddr, gfx8_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockSeAttr};
// Counter block SRBM
static const GpuBlockInfo SrbmCounterBlockInfo = {"SRBM", SrbmCounterBlockId, 1, SrbmCounterBlockMaxEvent, SrbmCounterBlockNumCounters, SrbmCounterRegAddr, gfx8_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block WD
static const GpuBlockInfo WdCounterBlockInfo = {"WD", WdCounterBlockId, 1, WdCounterBlockMaxEvent, WdCounterBlockNumCounters, WdCounterRegAddr, gfx8_cntx_prim::select_value<regWD_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block CPG
static const GpuBlockInfo CpgCounterBlockInfo = {"CPG", CpgCounterBlockId, 1, CpgCounterBlockMaxEvent, CpgCounterBlockNumCounters, CpgCounterRegAddr, gfx8_cntx_prim::select_value<regCPG_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx8_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT__CI__VI>, CounterBlockDfltAttr};
static const GpuBlockInfo McSeqCounterBlockInfo = {"MC_SEQ", McCounterBlockId, McCounterBlockNumInstances, McSeqCounterBlockMaxEvent, McCounterBlockNumCounters, McSeqCounterRegAddr, gfx8_cntx_prim::mc_select_value, CounterBlockMcAttr};

#endif  // _GFX8_BLOCKTABLE_H_
