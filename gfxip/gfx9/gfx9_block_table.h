#ifndef _BLOCKTABLE_H_
#define _BLOCKTABLE_H_

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
 * DRMDMA
 */
static const CounterRegInfo DrmdmaCounterRegAddr[] = {
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER0_RESULT, 0},
    {mmSDMA0_PERFMON_CNTL, 0, mmSDMA0_PERFCOUNTER1_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER0_RESULT, 0},
    {mmSDMA1_PERFMON_CNTL, 0, mmSDMA1_PERFCOUNTER1_RESULT, 0},
};

/*
 * IH
 */
static const CounterRegInfo IhCounterRegAddr[] = {
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER0_RESULT, 0},
    {mmIH_PERFMON_CNTL, 0, mmIH_PERFCOUNTER1_RESULT, 0}};

/*
 * CPF
 */
static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

/*
 * DRM
 */
static const CounterRegInfo DrmCounterRegAddr[] = {
    /*
    {mmDRM_PERFCOUNTER1_SELECT, 0, mmDRM_PERFCOUNTER1_LO, mmDRM_PERFCOUNTER1_HI},
    {mmDRM_PERFCOUNTER2_SELECT, 0, mmDRM_PERFCOUNTER2_LO, mmDRM_PERFCOUNTER2_HI}
    */
};

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
 * SRBM
 */
static const CounterRegInfo SrbmCounterRegAddr[] = {
    /*
    {mmSRBM_PERFCOUNTER0_SELECT, 0, mmSRBM_PERFCOUNTER0_LO, mmSRBM_PERFCOUNTER0_HI},
    {mmSRBM_PERFCOUNTER1_SELECT, 0, mmSRBM_PERFCOUNTER1_LO, mmSRBM_PERFCOUNTER1_HI}
     */
};

/*
 * WD
 */
static const CounterRegInfo WdCounterRegAddr[] = {
    {mmWD_PERFCOUNTER0_SELECT, 0, mmWD_PERFCOUNTER0_LO, mmWD_PERFCOUNTER0_HI},
    {mmWD_PERFCOUNTER1_SELECT, 0, mmWD_PERFCOUNTER1_LO, mmWD_PERFCOUNTER1_HI},
    {mmWD_PERFCOUNTER2_SELECT, 0, mmWD_PERFCOUNTER2_LO, mmWD_PERFCOUNTER2_HI},
    {mmWD_PERFCOUNTER3_SELECT, 0, mmWD_PERFCOUNTER3_LO, mmWD_PERFCOUNTER3_HI}};

/*
 * CPG
 */
static const CounterRegInfo CpgCounterRegAddr[] = {
    {mmCPG_PERFCOUNTER0_SELECT, 0, mmCPG_PERFCOUNTER0_LO, mmCPG_PERFCOUNTER0_HI},
    {mmCPG_PERFCOUNTER1_SELECT, 0, mmCPG_PERFCOUNTER1_LO, mmCPG_PERFCOUNTER1_HI}};

/*
 * CPC
 */
static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

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

// RMI
static const CounterRegInfo RmiCounterRegAddr[] = {
    {mmRMI_PERFCOUNTER0_SELECT, 0, mmRMI_PERFCOUNTER0_LO, mmRMI_PERFCOUNTER0_HI},
    {mmRMI_PERFCOUNTER1_SELECT, 0, mmRMI_PERFCOUNTER1_LO, mmRMI_PERFCOUNTER1_HI},
    {mmRMI_PERFCOUNTER2_SELECT, 0, mmRMI_PERFCOUNTER2_LO, mmRMI_PERFCOUNTER2_HI},
    {mmRMI_PERFCOUNTER3_SELECT, 0, mmRMI_PERFCOUNTER3_LO, mmRMI_PERFCOUNTER3_HI}};

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

/**
 * Table containing CounterGroups which represent AI hardware blocks
 * as defined by \ref GpuBlockInfo structure
 */
// Counter block CB
static const GpuBlockInfo CbCounterBlockInfo = {"CB", CbCounterBlockId, CbCounterBlockNumInstances, CntlMethodBySeAndInstance, CbCounterBlockMaxEvent, CbCounterBlockNumCounters, 0, 0, true, CbCounterRegAddr, true, gfx9_cntx_prim::select_value<regCB_PERFCOUNTER0_SELECT>, false}; 
// Temp commented for Vega10
// Counter block CPF
/*
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CntlMethodNone, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, 0, 0, true, CpfCounterRegAddr, false, gfx9_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, false}; 
*/
// Counter block DB
static const GpuBlockInfo DbCounterBlockInfo = {"DB", DbCounterBlockId, DbCounterBlockNumInstances, CntlMethodBySeAndInstance, DbCounterBlockMaxEvent, DbCounterBlockNumCounters, 0, 0, true, DbCounterRegAddr, true, gfx9_cntx_prim::select_value<regDB_PERFCOUNTER0_SELECT>, false}; 
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, CntlMethodNone, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, 0, 0, true, GrbmCounterRegAddr, false, gfx9_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, false}; 
// Counter block GRBMSE
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBMSE", GrbmSeCounterBlockId, 1, CntlMethodNone, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, 0, 0, true, GrbmSeCounterRegAddr, false, gfx9_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, false}; 
// Counter block PA_SU
static const GpuBlockInfo PaSuCounterBlockInfo = {"PA_SU", PaSuCounterBlockId, 1, CntlMethodBySe, PaSuCounterBlockMaxEvent, PaSuCounterBlockNumCounters, 0, 0, true, PaSuCounterRegAddr, false, gfx9_cntx_prim::select_value<regPA_SU_PERFCOUNTER0_SELECT>, false}; 
// Counter block PA_SC
static const GpuBlockInfo PaScCounterBlockInfo = {"PA_SC", PaScCounterBlockId, 1, CntlMethodBySe, PaScCounterBlockMaxEvent, PaScCounterBlockNumCounters, 0, 0, true, PaScCounterRegAddr, false, gfx9_cntx_prim::select_value<regPA_SC_PERFCOUNTER0_SELECT>, false}; 
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, CntlMethodBySe, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, 0, 0, true, SpiCounterRegAddr, false, gfx9_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, false}; 
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
static const GpuBlockInfo SqGsCounterBlockInfo = {"SQ_GS", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
static const GpuBlockInfo SqVsCounterBlockInfo = {"SQ_VS", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
static const GpuBlockInfo SqPsCounterBlockInfo = {"SQ_PS", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
static const GpuBlockInfo SqHsCounterBlockInfo = {"SQ_HS", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
static const GpuBlockInfo SqCsCounterBlockInfo = {"SQ_CS", SqCounterBlockId, 1, CntlMethodBySe, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, 0, 0, true, SqCounterRegAddr, false, gfx9_cntx_prim::select_value<regSQ_PERFCOUNTER0_SELECT>, true}; 
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, CntlMethodBySe, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, 0, 0, true, SxCounterRegAddr, true, gfx9_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, false}; 
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, CntlMethodBySeAndInstance, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, 0, 0, true, TaCounterRegAddr, false, gfx9_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, false}; 
// Counter block TCA
static const GpuBlockInfo TcaCounterBlockInfo = {"TCA", TcaCounterBlockId, TcaCounterBlockNumInstances, CntlMethodByInstance, TcaCounterBlockMaxEvent, TcaCounterBlockNumCounters, 0, 0, true, TcaCounterRegAddr, false, gfx9_cntx_prim::select_value<regTCA_PERFCOUNTER0_SELECT>, false}; 
// Counter block TCC
static const GpuBlockInfo TccCounterBlockInfo = {"TCC", TccCounterBlockId, TccCounterBlockNumInstances, CntlMethodByInstance, TccCounterBlockMaxEvent, TccCounterBlockNumCounters, 0, 0, true, TccCounterRegAddr, false, gfx9_cntx_prim::select_value<regTCC_PERFCOUNTER0_SELECT>, false}; 
// Counter block TD
static const GpuBlockInfo TdCounterBlockInfo = {"TD", TdCounterBlockId, TdCounterBlockNumInstances, CntlMethodBySeAndInstance, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, 0, 0, true, TdCounterRegAddr, false, gfx9_cntx_prim::select_value<regTD_PERFCOUNTER0_SELECT>, false}; 
// Counter block TCP
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, TcpCounterBlockNumInstances, CntlMethodBySeAndInstance, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, 0, 0, true, TcpCounterRegAddr, false, gfx9_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, false}; 
// Counter block GDS
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, CntlMethodNone, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, 0, 0, true, GdsCounterRegAddr, false, gfx9_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, false}; 
// Counter block VGT
static const GpuBlockInfo VgtCounterBlockInfo = {"VGT", VgtCounterBlockId, 1, CntlMethodBySe, VgtCounterBlockMaxEvent, VgtCounterBlockNumCounters, 0, 0, true, VgtCounterRegAddr, false, gfx9_cntx_prim::select_value<regVGT_PERFCOUNTER0_SELECT>, false}; 
// Counter block IA
static const GpuBlockInfo IaCounterBlockInfo = {"IA", IaCounterBlockId, 1, CntlMethodBySe, IaCounterBlockMaxEvent, IaCounterBlockNumCounters, 0, 0, true, IaCounterRegAddr, false, gfx9_cntx_prim::select_value<regIA_PERFCOUNTER0_SELECT>, false}; 
// Temp commented out for Vega10
// Counter block SRBM
/*
static const GpuBlockInfo SrbmCounterBlockInfo = {"SRBM", SrbmCounterBlockId, 1, CntlMethodNone, SrbmCounterBlockMaxEvent, SrbmCounterBlockNumCounters, 0, 0, true, SrbmCounterRegAddr, false, gfx9_cntx_prim::select_value<regSRBM_PERFCOUNTER0_SELECT>, false}; 
*/
// Counter block WD
static const GpuBlockInfo WdCounterBlockInfo = {"WD", WdCounterBlockId, 1, CntlMethodNone, WdCounterBlockMaxEvent, WdCounterBlockNumCounters, 0, 0, true, WdCounterRegAddr, false, gfx9_cntx_prim::select_value<regWD_PERFCOUNTER0_SELECT>, false}; 
// Counter block CPG
// Temp commented for Vega10
/*
static const GpuBlockInfo CpgCounterBlockInfo = {"CPG", CpgCounterBlockId, 1, CntlMethodNone, CpgCounterBlockMaxEvent, CpgCounterBlockNumCounters, 0, 0, true, CpgCounterRegAddr, false, gfx9_cntx_prim::select_value<regCPG_PERFCOUNTER0_SELECT>, false}; 
*/
// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CntlMethodNone, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, 0, 0, true, CpcCounterRegAddr, false, gfx9_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>, false}; 
// Counter block GCEA
static const GpuBlockInfo GceaCounterBlockInfo = {"GCEA", GceaCounterBlockId, 1, CntlMethodNone, GceaCounterBlockMaxEvent, GceaCounterBlockNumCounters, 0, 0, true, GceaCounterRegAddr, false, gfx9_cntx_prim::select_value<regGCEA_PERFCOUNTER0_CFG>, false};
// Counter block ATC
static const GpuBlockInfo AtcCounterBlockInfo = {"ATC", AtcCounterBlockId, 1, CntlMethodNone, AtcCounterBlockMaxEvent, AtcCounterBlockNumCounters, 0, 0, true, AtcCounterRegAddr, false, gfx9_cntx_prim::select_value<regATC_PERFCOUNTER0_CFG>, false};
// Counter block ATC L2
static const GpuBlockInfo AtcL2CounterBlockInfo = {"ATC_L2", AtcL2CounterBlockId, 1, CntlMethodNone, AtcL2CounterBlockMaxEvent, AtcL2CounterBlockNumCounters, 0, 0, true, AtcL2CounterRegAddr, false, gfx9_cntx_prim::select_value<regATC_L2_PERFCOUNTER0_CFG>, false};
// Counter block RPB
static const GpuBlockInfo RpbCounterBlockInfo = {"RPB", RpbCounterBlockId, 1, CntlMethodNone, RpbCounterBlockMaxEvent, RpbCounterBlockNumCounters, 0, 0, true, RpbCounterRegAddr, false, gfx9_cntx_prim::select_value<regRPB_PERFCOUNTER0_CFG>, false};
// Counter block RMI
static const GpuBlockInfo RmiCounterBlockInfo = {"RMI", RmiCounterBlockId, 1, CntlMethodNone, RmiCounterBlockMaxEvent, RmiCounterBlockNumCounters, 0, 0, true, RmiCounterRegAddr, false, gfx9_cntx_prim::select_value<regRMI_PERFCOUNTER0_SELECT>, false};
// Counter block MC VM L2
static const GpuBlockInfo McVmL2CounterBlockInfo = {"MC_VM_L2", McVmL2CounterBlockId, 1, CntlMethodNone, McVmL2CounterBlockMaxEvent, McVmL2CounterBlockNumCounters, 0, 0, true, McVmL2CounterRegAddr, false, gfx9_cntx_prim::select_value<regMC_VM_L2_PERFCOUNTER0_CFG>, false};

}  // namespace gfx9
}  // namespace gfxip

#endif  //  _BLOCKTABLE_H_
