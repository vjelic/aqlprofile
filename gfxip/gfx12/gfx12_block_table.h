// Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.

#ifndef _GFX12_BLOCKTABLE_H_
#define _GFX12_BLOCKTABLE_H_

#define REG_INFO_WITH_CTRL(BLOCK, CTRL, INDEX) \
 {mm##BLOCK##_PERFCOUNTER##INDEX##_SELECT, CTRL, mm##BLOCK##_PERFCOUNTER##INDEX##_LO, mm##BLOCK##_PERFCOUNTER##INDEX##_HI}
#define REG_INFO_WITH_CTRL_1(BLOCK, CTRL) REG_INFO_WITH_CTRL(BLOCK, CTRL, 0)
#define REG_INFO_WITH_CTRL_2(BLOCK, CTRL) REG_INFO_WITH_CTRL_1(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 1)
#define REG_INFO_WITH_CTRL_3(BLOCK, CTRL) REG_INFO_WITH_CTRL_2(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 2)
#define REG_INFO_WITH_CTRL_4(BLOCK, CTRL) REG_INFO_WITH_CTRL_3(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 3)
#define REG_INFO_WITH_CTRL_5(BLOCK, CTRL) REG_INFO_WITH_CTRL_4(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 4)
#define REG_INFO_WITH_CTRL_6(BLOCK, CTRL) REG_INFO_WITH_CTRL_5(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 5)
#define REG_INFO_WITH_CTRL_7(BLOCK, CTRL) REG_INFO_WITH_CTRL_6(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 6)
#define REG_INFO_WITH_CTRL_8(BLOCK, CTRL) REG_INFO_WITH_CTRL_7(BLOCK, CTRL), REG_INFO_WITH_CTRL(BLOCK, CTRL, 7)
#define REG_INFO_1(BLOCK) REG_INFO_WITH_CTRL_1(BLOCK, 0)
#define REG_INFO_2(BLOCK) REG_INFO_WITH_CTRL_2(BLOCK, 0)
#define REG_INFO_3(BLOCK) REG_INFO_WITH_CTRL_3(BLOCK, 0)
#define REG_INFO_4(BLOCK) REG_INFO_WITH_CTRL_4(BLOCK, 0)
#define REG_INFO_5(BLOCK) REG_INFO_WITH_CTRL_5(BLOCK, 0)
#define REG_INFO_6(BLOCK) REG_INFO_WITH_CTRL_6(BLOCK, 0)
#define REG_INFO_7(BLOCK) REG_INFO_WITH_CTRL_7(BLOCK, 0)
#define REG_INFO_8(BLOCK) REG_INFO_WITH_CTRL_8(BLOCK, 0)

namespace gfxip {
namespace gfx12 {
// Counter register info - Auto-generated from chip_offset_byte.h, edit with extra caution
static const CounterRegInfo GrbmCounterRegAddr[] = {REG_INFO_2(GRBM)};
static const CounterRegInfo RlcCounterRegAddr[] = {REG_INFO_2(RLC)};
static const CounterRegInfo CpgCounterRegAddr[] = {REG_INFO_2(CPG)};
static const CounterRegInfo CpcCounterRegAddr[] = {REG_INFO_2(CPC)};
static const CounterRegInfo CpfCounterRegAddr[] = {REG_INFO_2(CPF)};
static const CounterRegInfo GcrCounterRegAddr[] = {REG_INFO_WITH_CTRL_2(GCR, mmGCR_GENERAL_CNTL)};
static const CounterRegInfo PaPhCounterRegAddr[] = {REG_INFO_8(PA_PH)};
static const CounterRegInfo Ge1CounterRegAddr[] = {REG_INFO_4(GE1)};
static const CounterRegInfo Gl2aCounterRegAddr[] = {REG_INFO_4(GL2A)};
static const CounterRegInfo Gl2cCounterRegAddr[] = {REG_INFO_4(GL2C)};
static const CounterRegInfo GceaCounterRegAddr[] = {REG_INFO_2(GC_EA_CPWD)};
static const CounterRegInfo ChaCounterRegAddr[] = {REG_INFO_4(CHA)};
static const CounterRegInfo ChcCounterRegAddr[] = {REG_INFO_4(CHC)};
static const CounterRegInfo Ge2CounterRegAddr[] = {REG_INFO_4(GE2_DIST)};
static const CounterRegInfo Sdma0CounterRegAddr[] = {REG_INFO_2(SDMA0)};
static const CounterRegInfo Sdma1CounterRegAddr[] = {REG_INFO_2(SDMA1)};
//static const CounterRegInfo GcVml2CounterRegAddr[] = {REG_INFO_2(GCVML2)};
//static const CounterRegInfo GcMcVml2CounterRegAddr[] = {REG_INFO_1(GCMC_VM_L2)};
//static const CounterRegInfo GcUtcl2CounterRegAddr[] = {REG_INFO_1(GCUTCL2)};
static const CounterRegInfo GrbmhCounterRegAddr[] = {REG_INFO_2(GRBMH)};
static const CounterRegInfo CbCounterRegAddr[] = {REG_INFO_4(CB)};
static const CounterRegInfo DbCounterRegAddr[] = {REG_INFO_4(DB)};
static const CounterRegInfo PaSuCounterRegAddr[] = {REG_INFO_4(PA_SU)};
static const CounterRegInfo SxCounterRegAddr[] = {REG_INFO_4(SX)};
static const CounterRegInfo PaScCounterRegAddr[] = {REG_INFO_8(PA_SC)};
static const CounterRegInfo TaCounterRegAddr[] = {REG_INFO_2(TA)};
static const CounterRegInfo TdCounterRegAddr[] = {REG_INFO_2(TD)};
static const CounterRegInfo TcpCounterRegAddr[] = {REG_INFO_4(TCP)};
static const CounterRegInfo SpiCounterRegAddr[] = {REG_INFO_6(SPI)};
static const CounterRegInfo SqgCounterRegAddr[] = {REG_INFO_WITH_CTRL_8(SQG, mmSQG_PERFCOUNTER_CTRL)};
static const CounterRegInfo Gl1aCounterRegAddr[] = {REG_INFO_4(GL1A)};
static const CounterRegInfo RmiCounterRegAddr[] = {REG_INFO_4(RMI)};
static const CounterRegInfo Gl1cCounterRegAddr[] = {REG_INFO_4(GL1C)};
//static const CounterRegInfo SqcCounterRegAddr[] = {REG_INFO_WITH_CTRL_16(SQ, mmSQ_PERFCOUNTER_CTRL)};
static const CounterRegInfo PcCounterRegAddr[] = {REG_INFO_4(PC)};
static const CounterRegInfo GeCounterRegAddr[] = {REG_INFO_4(GE2_SE)};
static const CounterRegInfo GceaSeCounterRegAddr[] = {REG_INFO_2(GC_EA_SE)};
static const CounterRegInfo WgsCounterRegAddr[] = {REG_INFO_2(WGS)};
static const CounterRegInfo Gl1xaCounterRegAddr[] = {REG_INFO_4(GL1XA)};
static const CounterRegInfo Gl1xcCounterRegAddr[] = {REG_INFO_4(GL1XC)};
static const CounterRegInfo Utcl1CounterRegAddr[] = {REG_INFO_4(UTCL1)};

// Special handling of SQC:
//   SQC only supports 32bit PMC, only mmSQ_PERFCOUNTER#even_number#_SELECT is
//   used by PMC. mmSQ_PERFCOUNTER#odd_number#_SELECT is used only by SPM
static const CounterRegInfo SqcCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER0_LO, 0},
    {mmSQ_PERFCOUNTER2_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER1_LO, 0},
    {mmSQ_PERFCOUNTER4_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER2_LO, 0},
    {mmSQ_PERFCOUNTER6_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER3_LO, 0},
    {mmSQ_PERFCOUNTER8_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER4_LO, 0},
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER5_LO, 0},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER6_LO, 0},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER7_LO, 0}};

// Special handling of GCVML2:
static const CounterRegInfo GcVml2CounterRegAddr[] = {
    {mmGCVML2_PERFCOUNTER2_0_SELECT, 0, mmGCVML2_PERFCOUNTER2_0_LO, mmGCVML2_PERFCOUNTER2_0_HI},
    {mmGCVML2_PERFCOUNTER2_1_SELECT, 0, mmGCVML2_PERFCOUNTER2_1_LO, mmGCVML2_PERFCOUNTER2_1_HI}};

// Special handling of GCMC_VM_L2:
static const CounterRegInfo GcMcVml2CounterRegAddr[] = {
    {mmGCMC_VM_L2_PERFCOUNTER0_CFG, mmGCMC_VM_L2_PERFCOUNTER_RSLT_CNTL, mmGCMC_VM_L2_PERFCOUNTER_LO, mmGCMC_VM_L2_PERFCOUNTER_HI}};

// Special handling of GCUTCL2: Not sure if this is SPM-only
static const CounterRegInfo GcUtcl2CounterRegAddr[] = {
    {mmGCUTCL2_PERFCOUNTER0_CFG, mmGCUTCL2_PERFCOUNTER_RSLT_CNTL, mmGCUTCL2_PERFCOUNTER_LO, mmGCUTCL2_PERFCOUNTER_HI}};

// Global blocks: GRBM RLC ATCL2 CHA CHC CHCG CPC CPF CPG EA FFBM GCR GDS GE1 GE2_DIST GL2A GL2C GUS PH SDMA VML2 UTCL2
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", __BLOCK_ID(GRBM), GrbmCounterBlockNumInstances, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockGRBMAttr};
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", __BLOCK_ID(CPC), CpcCounterBlockNumInstances, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpcBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPC};
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", __BLOCK_ID(CPF), CpfCounterBlockNumInstances, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpfBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPF};
static const GpuBlockInfo GcrCounterBlockInfo = {"GCR", __BLOCK_ID(GCR), GcrCounterBlockNumInstances, GcrCounterBlockMaxEvent, GcrCounterBlockNumCounters, GcrCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockTcAttr};
static const GpuBlockInfo Gl2aCounterBlockInfo = {"GL2A", __BLOCK_ID(GL2A), Gl2aCounterBlockNumInstances, Gl2aCounterBlockMaxEvent, Gl2aCounterBlockNumCounters, Gl2aCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockTcAttr};
static const GpuBlockInfo Gl2cCounterBlockInfo = {"GL2C", __BLOCK_ID(GL2C), Gl2cCounterBlockNumInstances, Gl2cCounterBlockMaxEvent, Gl2cCounterBlockNumCounters, Gl2cCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockTcAttr};
static const GpuBlockInfo ChaCounterBlockInfo = {"CHA", __BLOCK_ID(CHA), ChaCounterBlockNumInstances, ChaCounterBlockMaxEvent, ChaCounterBlockNumCounters, ChaCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockTcAttr};
static const GpuBlockInfo ChcCounterBlockInfo = {"CHC", __BLOCK_ID(CHC), ChcCounterBlockNumInstances, ChcCounterBlockMaxEvent, ChcCounterBlockNumCounters, ChcCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockDfltAttr|CounterBlockTcAttr};
// SE blocks: GRBMH EA_SE GE GL1XA GL1XC GL2A GL2C PA PC SPI SQG WGS
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", __BLOCK_ID(SPI), SpiCounterBlockNumInstances, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSPIAttr, NULL /*SpiBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SPI};
static const GpuBlockInfo SqgCounterBlockInfo = {"SQ", __BLOCK_ID(SQ), SqgCounterBlockNumInstances, SqgCounterBlockMaxEvent, SqgCounterBlockNumCounters, SqgCounterRegAddr, gfx12_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr, NULL, SPM_SE_BLOCK_NAME_SQG};
// SA blocks: CB DB GL1A GL1C GL1CG SC SX
static const GpuBlockInfo Gl1aCounterBlockInfo = {"GL1A", __BLOCK_ID(GL1A), Gl1aCounterBlockNumInstances, Gl1aCounterBlockMaxEvent, Gl1aCounterBlockNumCounters, Gl1aCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockDfltAttr|CounterBlockTcAttr};
static const GpuBlockInfo Gl1cCounterBlockInfo = {"GL1C", __BLOCK_ID(GL1C), Gl1cCounterBlockNumInstances, Gl1cCounterBlockMaxEvent, Gl1cCounterBlockNumCounters, Gl1cCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockDfltAttr|CounterBlockTcAttr};
static const GpuBlockInfo SxCounterBlockInfo = {"SX", __BLOCK_ID(SX), SxCounterBlockNumInstances, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockCleanAttr, NULL /*SxBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SX};
// WGP blocks: SQC TA TCP TD
static const GpuBlockInfo SqcCounterBlockInfo = {"SQC", __BLOCK_ID(SQC), SqcCounterBlockNumInstances, SqcCounterBlockMaxEvent, SqcCounterBlockNumCounters, SqcCounterRegAddr, gfx12_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockWgpAttr|CounterBlockSqAttr, NULL, SPM_SE_BLOCK_NAME_SQC};
static const GpuBlockInfo TaCounterBlockInfo = {"TA", __BLOCK_ID(TA), TaCounterBlockNumInstances, TaCounterBlockMaxEvent, TaCounterBlockNumCounters, TaCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockWgpAttr|CounterBlockTcAttr, NULL/*TaBlockDelayInfo*/, SPM_SE_BLOCK_NAME_TA};
static const GpuBlockInfo TdCounterBlockInfo = {"TD", __BLOCK_ID(TD), TdCounterBlockNumInstances, TdCounterBlockMaxEvent, TdCounterBlockNumCounters, TdCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockWgpAttr|CounterBlockTcAttr, NULL/*TdBlockDelayInfo*/, SPM_SE_BLOCK_NAME_TD};
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", __BLOCK_ID(TCP), TcpCounterBlockNumInstances, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx12_cntx_prim::select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockWgpAttr|CounterBlockTcAttr, NULL/*TdBlockDelayInfo*/, SPM_SE_BLOCK_NAME_TCP};
}  // namespace gfx12
}  // namespace gfxip

#endif  // _GFX12_BLOCKTABLE_H_
