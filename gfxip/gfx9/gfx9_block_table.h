#ifndef _GFX9_BLOCKTABLE_H_
#define _GFX9_BLOCKTABLE_H_

namespace gfxip {
namespace gfx9 {

/*
 * The following tables contain register addresses of the SQ counter registers
 */

/*
 * SQ
 */
static const CounterRegInfo SqCounterRegAddr[] = {
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
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER10_LO, mmSQ_PERFCOUNTER10_HI},
    {mmSQ_PERFCOUNTER11_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER11_LO, mmSQ_PERFCOUNTER11_HI},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER12_LO, mmSQ_PERFCOUNTER12_HI},
    {mmSQ_PERFCOUNTER13_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER13_LO, mmSQ_PERFCOUNTER13_HI},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER14_LO, mmSQ_PERFCOUNTER14_HI},
    {mmSQ_PERFCOUNTER15_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER15_LO, mmSQ_PERFCOUNTER15_HI}};

/*
 * IH
 */
static const CounterRegInfo IhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER0_RESULT, 0},
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER1_RESULT, 0}};

/*
 * GRBM
 */
static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT, 0, mmGRBM_PERFCOUNTER0_LO, mmGRBM_PERFCOUNTER0_HI},
    {mmGRBM_PERFCOUNTER1_SELECT, 0, mmGRBM_PERFCOUNTER1_LO, mmGRBM_PERFCOUNTER1_HI}};

/*
 * GRBM_SE
 */
static const CounterRegInfo GrbmSeCounterRegAddr[] = {
    {mmGRBM_SE0_PERFCOUNTER_SELECT, 0, mmGRBM_SE0_PERFCOUNTER_LO, mmGRBM_SE0_PERFCOUNTER_HI},
    {mmGRBM_SE1_PERFCOUNTER_SELECT, 0, mmGRBM_SE1_PERFCOUNTER_LO, mmGRBM_SE1_PERFCOUNTER_HI},
    {mmGRBM_SE2_PERFCOUNTER_SELECT, 0, mmGRBM_SE2_PERFCOUNTER_LO, mmGRBM_SE2_PERFCOUNTER_HI},
    {mmGRBM_SE3_PERFCOUNTER_SELECT, 0, mmGRBM_SE3_PERFCOUNTER_LO, mmGRBM_SE3_PERFCOUNTER_HI}};

/*
 * PA_SU
 */
static const CounterRegInfo PaSuCounterRegAddr[] = {
    {mmPA_SU_PERFCOUNTER0_SELECT, 0, mmPA_SU_PERFCOUNTER0_LO, mmPA_SU_PERFCOUNTER0_HI},
    {mmPA_SU_PERFCOUNTER1_SELECT, 0, mmPA_SU_PERFCOUNTER1_LO, mmPA_SU_PERFCOUNTER1_HI},
    {mmPA_SU_PERFCOUNTER2_SELECT, 0, mmPA_SU_PERFCOUNTER2_LO, mmPA_SU_PERFCOUNTER2_HI},
    {mmPA_SU_PERFCOUNTER3_SELECT, 0, mmPA_SU_PERFCOUNTER3_LO, mmPA_SU_PERFCOUNTER3_HI}};

/*
 * PA_SC
 */
static const CounterRegInfo PaScCounterRegAddr[] = {
    {mmPA_SC_PERFCOUNTER0_SELECT, 0, mmPA_SC_PERFCOUNTER0_LO, mmPA_SC_PERFCOUNTER0_HI},
    {mmPA_SC_PERFCOUNTER1_SELECT, 0, mmPA_SC_PERFCOUNTER1_LO, mmPA_SC_PERFCOUNTER1_HI},
    {mmPA_SC_PERFCOUNTER2_SELECT, 0, mmPA_SC_PERFCOUNTER2_LO, mmPA_SC_PERFCOUNTER2_HI},
    {mmPA_SC_PERFCOUNTER3_SELECT, 0, mmPA_SC_PERFCOUNTER3_LO, mmPA_SC_PERFCOUNTER3_HI},
    {mmPA_SC_PERFCOUNTER4_SELECT, 0, mmPA_SC_PERFCOUNTER4_LO, mmPA_SC_PERFCOUNTER4_HI},
    {mmPA_SC_PERFCOUNTER5_SELECT, 0, mmPA_SC_PERFCOUNTER5_LO, mmPA_SC_PERFCOUNTER5_HI},
    {mmPA_SC_PERFCOUNTER6_SELECT, 0, mmPA_SC_PERFCOUNTER6_LO, mmPA_SC_PERFCOUNTER6_HI},
    {mmPA_SC_PERFCOUNTER7_SELECT, 0, mmPA_SC_PERFCOUNTER7_LO, mmPA_SC_PERFCOUNTER7_HI}};


/*
 * SPI
 */
static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT, 0, mmSPI_PERFCOUNTER0_LO, mmSPI_PERFCOUNTER0_HI},
    {mmSPI_PERFCOUNTER1_SELECT, 0, mmSPI_PERFCOUNTER1_LO, mmSPI_PERFCOUNTER1_HI},
    {mmSPI_PERFCOUNTER2_SELECT, 0, mmSPI_PERFCOUNTER2_LO, mmSPI_PERFCOUNTER2_HI},
    {mmSPI_PERFCOUNTER3_SELECT, 0, mmSPI_PERFCOUNTER3_LO, mmSPI_PERFCOUNTER3_HI},
    {mmSPI_PERFCOUNTER4_SELECT, 0, mmSPI_PERFCOUNTER4_LO, mmSPI_PERFCOUNTER4_HI},
    {mmSPI_PERFCOUNTER5_SELECT, 0, mmSPI_PERFCOUNTER5_LO, mmSPI_PERFCOUNTER5_HI}};

/*
 * TCA
 */
static const CounterRegInfo TcaCounterRegAddr[] = {
    {mmTCA_PERFCOUNTER0_SELECT, 0, mmTCA_PERFCOUNTER0_LO, mmTCA_PERFCOUNTER0_HI},
    {mmTCA_PERFCOUNTER1_SELECT, 0, mmTCA_PERFCOUNTER1_LO, mmTCA_PERFCOUNTER1_HI},
    {mmTCA_PERFCOUNTER2_SELECT, 0, mmTCA_PERFCOUNTER2_LO, mmTCA_PERFCOUNTER2_HI},
    {mmTCA_PERFCOUNTER3_SELECT, 0, mmTCA_PERFCOUNTER3_LO, mmTCA_PERFCOUNTER3_HI}};

/*
 * TCC
 */
static const CounterRegInfo TccCounterRegAddr[] = {
    {mmTCC_PERFCOUNTER0_SELECT, 0, mmTCC_PERFCOUNTER0_LO, mmTCC_PERFCOUNTER0_HI},
    {mmTCC_PERFCOUNTER1_SELECT, 0, mmTCC_PERFCOUNTER1_LO, mmTCC_PERFCOUNTER1_HI},
    {mmTCC_PERFCOUNTER2_SELECT, 0, mmTCC_PERFCOUNTER2_LO, mmTCC_PERFCOUNTER2_HI},
    {mmTCC_PERFCOUNTER3_SELECT, 0, mmTCC_PERFCOUNTER3_LO, mmTCC_PERFCOUNTER3_HI}};

/*
 * TCP
 */
static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT, 0, mmTCP_PERFCOUNTER0_LO, mmTCP_PERFCOUNTER0_HI},
    {mmTCP_PERFCOUNTER1_SELECT, 0, mmTCP_PERFCOUNTER1_LO, mmTCP_PERFCOUNTER1_HI},
    {mmTCP_PERFCOUNTER2_SELECT, 0, mmTCP_PERFCOUNTER2_LO, mmTCP_PERFCOUNTER2_HI},
    {mmTCP_PERFCOUNTER3_SELECT, 0, mmTCP_PERFCOUNTER3_LO, mmTCP_PERFCOUNTER3_HI}};

/*
 * CB
 */
static const CounterRegInfo CbCounterRegAddr[] = {
    {mmCB_PERFCOUNTER0_SELECT, 0, mmCB_PERFCOUNTER0_LO, mmCB_PERFCOUNTER0_HI},
    {mmCB_PERFCOUNTER1_SELECT, 0, mmCB_PERFCOUNTER1_LO, mmCB_PERFCOUNTER1_HI},
    {mmCB_PERFCOUNTER2_SELECT, 0, mmCB_PERFCOUNTER2_LO, mmCB_PERFCOUNTER2_HI},
    {mmCB_PERFCOUNTER3_SELECT, 0, mmCB_PERFCOUNTER3_LO, mmCB_PERFCOUNTER3_HI}};

/*
 * DB
 */
static const CounterRegInfo DbCounterRegAddr[] = {
    {mmDB_PERFCOUNTER0_SELECT, 0, mmDB_PERFCOUNTER0_LO, mmDB_PERFCOUNTER0_HI},
    {mmDB_PERFCOUNTER1_SELECT, 0, mmDB_PERFCOUNTER1_LO, mmDB_PERFCOUNTER1_HI},
    {mmDB_PERFCOUNTER2_SELECT, 0, mmDB_PERFCOUNTER2_LO, mmDB_PERFCOUNTER2_HI},
    {mmDB_PERFCOUNTER3_SELECT, 0, mmDB_PERFCOUNTER3_LO, mmDB_PERFCOUNTER3_HI}};

/*
 * RLC
 */
static const CounterRegInfo RlcCounterRegAddr[] = {
    {mmRLC_PERFCOUNTER0_SELECT, 0, mmRLC_PERFCOUNTER0_LO, mmRLC_PERFCOUNTER0_HI},
    {mmRLC_PERFCOUNTER1_SELECT, 0, mmRLC_PERFCOUNTER1_LO, mmRLC_PERFCOUNTER1_HI}};

/*
 * SX
 */
static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

/*
 * TA
 */
static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

/*
 * TD
 */
static const CounterRegInfo TdCounterRegAddr[] = {
    {mmTD_PERFCOUNTER0_SELECT, 0, mmTD_PERFCOUNTER0_LO, mmTD_PERFCOUNTER0_HI},
    {mmTD_PERFCOUNTER1_SELECT, 0, mmTD_PERFCOUNTER1_LO, mmTD_PERFCOUNTER1_HI}};

/*
 * GDS
 */
static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT, 0, mmGDS_PERFCOUNTER0_LO, mmGDS_PERFCOUNTER0_HI},
    {mmGDS_PERFCOUNTER1_SELECT, 0, mmGDS_PERFCOUNTER1_LO, mmGDS_PERFCOUNTER1_HI},
    {mmGDS_PERFCOUNTER2_SELECT, 0, mmGDS_PERFCOUNTER2_LO, mmGDS_PERFCOUNTER2_HI},
    {mmGDS_PERFCOUNTER3_SELECT, 0, mmGDS_PERFCOUNTER3_LO, mmGDS_PERFCOUNTER3_HI}};

/*
 * VGT
 */
static const CounterRegInfo VgtCounterRegAddr[] = {
    {mmVGT_PERFCOUNTER0_SELECT, 0, mmVGT_PERFCOUNTER0_LO, mmVGT_PERFCOUNTER0_HI},
    {mmVGT_PERFCOUNTER1_SELECT, 0, mmVGT_PERFCOUNTER1_LO, mmVGT_PERFCOUNTER1_HI},
    {mmVGT_PERFCOUNTER2_SELECT, 0, mmVGT_PERFCOUNTER2_LO, mmVGT_PERFCOUNTER2_HI},
    {mmVGT_PERFCOUNTER3_SELECT, 0, mmVGT_PERFCOUNTER3_LO, mmVGT_PERFCOUNTER3_HI}};

/*
 * IA
 */
static const CounterRegInfo IaCounterRegAddr[] = {
    {mmIA_PERFCOUNTER0_SELECT, 0, mmIA_PERFCOUNTER0_LO, mmIA_PERFCOUNTER0_HI},
    {mmIA_PERFCOUNTER1_SELECT, 0, mmIA_PERFCOUNTER1_LO, mmIA_PERFCOUNTER1_HI},
    {mmIA_PERFCOUNTER2_SELECT, 0, mmIA_PERFCOUNTER2_LO, mmIA_PERFCOUNTER2_HI},
    {mmIA_PERFCOUNTER3_SELECT, 0, mmIA_PERFCOUNTER3_LO, mmIA_PERFCOUNTER3_HI}};

/*
 * WD
 */
static const CounterRegInfo WdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT, 0, mmWD_PERFCOUNTER0_LO, mmWD_PERFCOUNTER0_HI},
    {mmWD_PERFCOUNTER1_SELECT, 0, mmWD_PERFCOUNTER1_LO, mmWD_PERFCOUNTER1_HI},
    {mmWD_PERFCOUNTER2_SELECT, 0, mmWD_PERFCOUNTER2_LO, mmWD_PERFCOUNTER2_HI},
    {mmWD_PERFCOUNTER3_SELECT, 0, mmWD_PERFCOUNTER3_LO, mmWD_PERFCOUNTER3_HI}};

/*
 * CPC
 */
static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

/*
 * CPF
 */
static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

/*
 * CPG
 */
static const CounterRegInfo CpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT, 0, mmCPG_PERFCOUNTER0_LO, mmCPG_PERFCOUNTER0_HI},
    {mmCPG_PERFCOUNTER1_SELECT, 0, mmCPG_PERFCOUNTER1_LO, mmCPG_PERFCOUNTER1_HI}};

// RMI
static const CounterRegInfo RmiCounterRegAddr[] = {
    {mmRMI_PERFCOUNTER0_SELECT, mmRMI_PERF_COUNTER_CNTL, mmRMI_PERFCOUNTER0_LO, mmRMI_PERFCOUNTER0_HI},
    {mmRMI_PERFCOUNTER1_SELECT, mmRMI_PERF_COUNTER_CNTL, mmRMI_PERFCOUNTER1_LO, mmRMI_PERFCOUNTER1_HI},
    {mmRMI_PERFCOUNTER2_SELECT, mmRMI_PERF_COUNTER_CNTL, mmRMI_PERFCOUNTER2_LO, mmRMI_PERFCOUNTER2_HI},
    {mmRMI_PERFCOUNTER3_SELECT, mmRMI_PERF_COUNTER_CNTL, mmRMI_PERFCOUNTER3_LO, mmRMI_PERFCOUNTER3_HI}};

// GCEA
static const CounterRegInfo GceaCounterRegAddr[] = {
    {mmGCEA_PERFCOUNTER0_CFG, mmGCEA_PERFCOUNTER_RSLT_CNTL, mmGCEA_PERFCOUNTER_LO, mmGCEA_PERFCOUNTER_HI},
    {mmGCEA_PERFCOUNTER1_CFG, mmGCEA_PERFCOUNTER_RSLT_CNTL, mmGCEA_PERFCOUNTER_LO, mmGCEA_PERFCOUNTER_HI}};

// ATC
static const CounterRegInfo AtcCounterRegAddr[] = {
    {mmATC_PERFCOUNTER0_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER1_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER2_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI},
    {mmATC_PERFCOUNTER3_CFG, mmATC_PERFCOUNTER_RSLT_CNTL, mmATC_PERFCOUNTER_LO, mmATC_PERFCOUNTER_HI}};

// ATC L2
static const CounterRegInfo AtcL2CounterRegAddr[] = {
    {mmATC_L2_PERFCOUNTER0_CFG, mmATC_L2_PERFCOUNTER_RSLT_CNTL, mmATC_L2_PERFCOUNTER_LO, mmATC_L2_PERFCOUNTER_HI},
    {mmATC_L2_PERFCOUNTER1_CFG, mmATC_L2_PERFCOUNTER_RSLT_CNTL, mmATC_L2_PERFCOUNTER_LO, mmATC_L2_PERFCOUNTER_HI}};

// RPB
static const CounterRegInfo RpbCounterRegAddr[] = {
    {mmRPB_PERFCOUNTER0_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER1_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER2_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI},
    {mmRPB_PERFCOUNTER3_CFG, mmRPB_PERFCOUNTER_RSLT_CNTL, mmRPB_PERFCOUNTER_LO, mmRPB_PERFCOUNTER_HI}};

// MC VM L2
static const CounterRegInfo McVmL2CounterRegAddr[] = {
    {mmMC_VM_L2_PERFCOUNTER0_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER1_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER2_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER3_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER4_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER5_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER6_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI},
    {mmMC_VM_L2_PERFCOUNTER7_CFG, mmMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmMC_VM_L2_PERFCOUNTER_LO, mmMC_VM_L2_PERFCOUNTER_HI}};

// Counter block info table
// Counter block CB
static const GpuBlockInfo CbCounterBlockInfo = {"CB", CbCounterBlockId, CbCounterBlockNumInstances, CbCounterBlockMaxEvent, CbCounterBlockNumCounters, CbCounterRegAddr, gfx9_cntx_prim::select_value<regCB_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr};
// Counter block DB
static const GpuBlockInfo DbCounterBlockInfo = {"DB", DbCounterBlockId, DbCounterBlockNumInstances, DbCounterBlockMaxEvent, DbCounterBlockNumCounters, DbCounterRegAddr, gfx9_cntx_prim::select_value<regDB_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr};
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx9_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block GRBMSE
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBMSE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx9_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
// Counter block PA_SU
static const GpuBlockInfo PaSuCounterBlockInfo = {"PA_SU", PaSuCounterBlockId, 1, PaSuCounterBlockMaxEvent, PaSuCounterBlockNumCounters, PaSuCounterRegAddr, gfx9_cntx_prim::select_value<regPA_SU_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block PA_SC
static const GpuBlockInfo PaScCounterBlockInfo = {"PA_SC", PaScCounterBlockId, 1, PaScCounterBlockMaxEvent, PaScCounterBlockNumCounters, PaScCounterRegAddr, gfx9_cntx_prim::select_value<regPA_SC_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx9_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqGsCounterBlockInfo = {"SQ_GS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqVsCounterBlockInfo = {"SQ_VS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqPsCounterBlockInfo = {"SQ_PS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqHsCounterBlockInfo = {"SQ_HS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx9_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr};
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx9_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr};
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx9_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block TCA
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, TcaCounterRegAddr, gfx9_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block TCC
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, TccCounterRegAddr, gfx9_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block TD
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx9_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block TCP
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx9_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block GDS
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx9_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block VGT
static const GpuBlockInfo VgtCounterBlockInfo = {"VGT", VgtCounterBlockId, 1, VgtCounterBlockMaxEvent, VgtCounterBlockNumCounters, VgtCounterRegAddr, gfx9_cntx_prim::select_value<regVGT_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block IA
static const GpuBlockInfo IaCounterBlockInfo = {"IA", IaCounterBlockId, 1, IaCounterBlockMaxEvent, IaCounterBlockNumCounters, IaCounterRegAddr, gfx9_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr};
// Counter block WD
static const GpuBlockInfo WdCounterBlockInfo = {"WD", WdCounterBlockId, 1, WdCounterBlockMaxEvent, WdCounterBlockNumCounters, WdCounterRegAddr, gfx9_cntx_prim::select_value<regWD_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx9_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block CPF
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx9_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block RMI
static const GpuBlockInfo RmiCounterBlockInfo = {"RMI", RmiCounterBlockId, RmiCounterBlockNumInstances, RmiCounterBlockMaxEvent, RmiCounterBlockNumCounters, RmiCounterRegAddr, gfx9_cntx_prim::select_value<regRMI_PERFCOUNTER0_SELECT>, CounterBlockRmiAttr};
// Counter block ATC
static const GpuBlockInfo AtcCounterBlockInfo = {"ATC", AtcCounterBlockId, AtcCounterBlockNumInstances, AtcCounterBlockMaxEvent, AtcCounterBlockNumCounters, AtcCounterRegAddr, gfx9_cntx_prim::mc_select_value<regATC_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
// Counter block ATC L2
static const GpuBlockInfo AtcL2CounterBlockInfo = {"ATC_L2", AtcL2CounterBlockId, AtcL2CounterBlockNumInstances, AtcL2CounterBlockMaxEvent, AtcL2CounterBlockNumCounters, AtcL2CounterRegAddr, gfx9_cntx_prim::mc_select_value<regATC_L2_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
// Counter block GCEA
static const GpuBlockInfo GceaCounterBlockInfo = {"GCEA", GceaCounterBlockId, GceaCounterBlockNumInstances, GceaCounterBlockMaxEvent, GceaCounterBlockNumCounters, GceaCounterRegAddr, gfx9_cntx_prim::mc_select_value<regGCEA_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
// Counter block MC VM L2
static const GpuBlockInfo McVmL2CounterBlockInfo = {"MC_VM_L2", McVmL2CounterBlockId, McVmL2CounterBlockNumInstances, McVmL2CounterBlockMaxEvent, McVmL2CounterBlockNumCounters, McVmL2CounterRegAddr, gfx9_cntx_prim::mc_select_value<regMC_VM_L2_PERFCOUNTER0_CFG>, CounterBlockMcAttr};
// Counter block RPB
static const GpuBlockInfo RpbCounterBlockInfo = {"RPB", RpbCounterBlockId, RpbCounterBlockNumInstances, RpbCounterBlockMaxEvent, RpbCounterBlockNumCounters, RpbCounterRegAddr, gfx9_cntx_prim::mc_select_value<regRPB_PERFCOUNTER0_CFG>, CounterBlockMcAttr};

}  // namespace gfx9
}  // namespace gfxip

#endif  //  _GFX9_BLOCKTABLE_H_
