// Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.

#ifndef _GFX12_BLOCKTABLE_H_
#define _GFX12_BLOCKTABLE_H_

namespace gfxip {
namespace gfx12 {

/*
 * CPC    CORRECT
 */
static const CounterRegInfo CpcCounterRegAddr[] = {
    {mmCPC_PERFCOUNTER0_SELECT, 0, mmCPC_PERFCOUNTER0_LO, mmCPC_PERFCOUNTER0_HI},
    {mmCPC_PERFCOUNTER1_SELECT, 0, mmCPC_PERFCOUNTER1_LO, mmCPC_PERFCOUNTER1_HI}};

/*
 * CPF    CORRECT
 */
static const CounterRegInfo CpfCounterRegAddr[] = {
    {mmCPF_PERFCOUNTER0_SELECT, 0, mmCPF_PERFCOUNTER0_LO, mmCPF_PERFCOUNTER0_HI},
    {mmCPF_PERFCOUNTER1_SELECT, 0, mmCPF_PERFCOUNTER1_LO, mmCPF_PERFCOUNTER1_HI}};

/*
 * GRBM     CORRECT
 */
static const CounterRegInfo GrbmCounterRegAddr[] = {
    {mmGRBM_PERFCOUNTER0_SELECT, 0, mmGRBM_PERFCOUNTER0_LO, mmGRBM_PERFCOUNTER0_HI},
    {mmGRBM_PERFCOUNTER1_SELECT, 0, mmGRBM_PERFCOUNTER1_LO, mmGRBM_PERFCOUNTER1_HI}};

/*
 * SPI        CORRECT
 */
static const CounterRegInfo SpiCounterRegAddr[] = {
    {mmSPI_PERFCOUNTER0_SELECT, 0, mmSPI_PERFCOUNTER0_LO, mmSPI_PERFCOUNTER0_HI},
    {mmSPI_PERFCOUNTER1_SELECT, 0, mmSPI_PERFCOUNTER1_LO, mmSPI_PERFCOUNTER1_HI},
    {mmSPI_PERFCOUNTER2_SELECT, 0, mmSPI_PERFCOUNTER2_LO, mmSPI_PERFCOUNTER2_HI},
    {mmSPI_PERFCOUNTER3_SELECT, 0, mmSPI_PERFCOUNTER3_LO, mmSPI_PERFCOUNTER3_HI},
    {mmSPI_PERFCOUNTER4_SELECT, 0, mmSPI_PERFCOUNTER4_LO, mmSPI_PERFCOUNTER4_HI},
    {mmSPI_PERFCOUNTER5_SELECT, 0, mmSPI_PERFCOUNTER5_LO, mmSPI_PERFCOUNTER5_HI}};

/*
 * SQ        CORRECT
 */
static const CounterRegInfo SqCounterRegAddr[] = {
    {mmSQ_PERFCOUNTER0_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER0_LO, 0},
    {mmSQ_PERFCOUNTER2_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER1_LO, 0},
    {mmSQ_PERFCOUNTER4_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER2_LO, 0},
    {mmSQ_PERFCOUNTER6_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER3_LO, 0},
    {mmSQ_PERFCOUNTER8_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER4_LO, 0},
    {mmSQ_PERFCOUNTER10_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER5_LO, 0},
    {mmSQ_PERFCOUNTER12_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER6_LO, 0},
    {mmSQ_PERFCOUNTER14_SELECT, mmSQ_PERFCOUNTER_CTRL, mmSQ_PERFCOUNTER7_LO, 0}};

/*
 * SX       CORRECT
 */
static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

// Define GFX10 specific blocks table entries like GC caches blocks
/*
 * GCR    CORRECT
 */
static const CounterRegInfo GcrCounterRegAddr[] = {
    {mmGCR_PERFCOUNTER0_SELECT, mmGCR_GENERAL_CNTL, mmGCR_PERFCOUNTER0_LO, mmGCR_PERFCOUNTER0_HI},
    {mmGCR_PERFCOUNTER1_SELECT, mmGCR_GENERAL_CNTL, mmGCR_PERFCOUNTER1_LO, mmGCR_PERFCOUNTER1_HI},
};

/*
 * TCP
 */
static const CounterRegInfo TcpCounterRegAddr[] = {
    {mmTCP_PERFCOUNTER0_SELECT, 0, mmTCP_PERFCOUNTER0_LO, mmTCP_PERFCOUNTER0_HI},
    {mmTCP_PERFCOUNTER1_SELECT, 0, mmTCP_PERFCOUNTER1_LO, mmTCP_PERFCOUNTER1_HI},
    {mmTCP_PERFCOUNTER2_SELECT, 0, mmTCP_PERFCOUNTER2_LO, mmTCP_PERFCOUNTER2_HI},
    {mmTCP_PERFCOUNTER3_SELECT, 0, mmTCP_PERFCOUNTER3_LO, mmTCP_PERFCOUNTER3_HI},
};

/*
 * GL1A    CORRECT
 */
static const CounterRegInfo Gl1aCounterRegAddr[] = {
    {mmGL1A_PERFCOUNTER0_SELECT, 0, mmGL1A_PERFCOUNTER0_LO, mmGL1A_PERFCOUNTER0_HI},
    {mmGL1A_PERFCOUNTER1_SELECT, 0, mmGL1A_PERFCOUNTER1_LO, mmGL1A_PERFCOUNTER1_HI},
    {mmGL1A_PERFCOUNTER2_SELECT, 0, mmGL1A_PERFCOUNTER2_LO, mmGL1A_PERFCOUNTER2_HI},
    {mmGL1A_PERFCOUNTER3_SELECT, 0, mmGL1A_PERFCOUNTER3_LO, mmGL1A_PERFCOUNTER3_HI},
};

/*
 * GL1C    CORRECT
 */
static const CounterRegInfo Gl1cCounterRegAddr[] = {
    {mmGL1C_PERFCOUNTER0_SELECT, 0, mmGL1C_PERFCOUNTER0_LO, mmGL1C_PERFCOUNTER0_HI},
    {mmGL1C_PERFCOUNTER1_SELECT, 0, mmGL1C_PERFCOUNTER1_LO, mmGL1C_PERFCOUNTER1_HI},
    {mmGL1C_PERFCOUNTER2_SELECT, 0, mmGL1C_PERFCOUNTER2_LO, mmGL1C_PERFCOUNTER2_HI},
    {mmGL1C_PERFCOUNTER3_SELECT, 0, mmGL1C_PERFCOUNTER3_LO, mmGL1C_PERFCOUNTER3_HI},
};

/*
 * GL2A     CORRECT
 */
static const CounterRegInfo Gl2aCounterRegAddr[] = {
    {mmGL2A_PERFCOUNTER0_SELECT, 0, mmGL2A_PERFCOUNTER0_LO, mmGL2A_PERFCOUNTER0_HI},
    {mmGL2A_PERFCOUNTER1_SELECT, 0, mmGL2A_PERFCOUNTER1_LO, mmGL2A_PERFCOUNTER1_HI},
    {mmGL2A_PERFCOUNTER2_SELECT, 0, mmGL2A_PERFCOUNTER2_LO, mmGL2A_PERFCOUNTER2_HI},
    {mmGL2A_PERFCOUNTER3_SELECT, 0, mmGL2A_PERFCOUNTER3_LO, mmGL2A_PERFCOUNTER3_HI},
};

/*
 * GL2C     CORRECT
 */
static const CounterRegInfo Gl2cCounterRegAddr[] = {
    {mmGL2C_PERFCOUNTER0_SELECT, 0, mmGL2C_PERFCOUNTER0_LO, mmGL2C_PERFCOUNTER0_HI},
    {mmGL2C_PERFCOUNTER1_SELECT, 0, mmGL2C_PERFCOUNTER1_LO, mmGL2C_PERFCOUNTER1_HI},
    {mmGL2C_PERFCOUNTER2_SELECT, 0, mmGL2C_PERFCOUNTER2_LO, mmGL2C_PERFCOUNTER2_HI},
    {mmGL2C_PERFCOUNTER3_SELECT, 0, mmGL2C_PERFCOUNTER3_LO, mmGL2C_PERFCOUNTER3_HI},
};

/*
 * TA            CORRECT
 */
static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

/*
 * SQG            CORRECT
 * JT: What about mmSQG_PERFCOUNTER_CTRL2 ?
 */
static const CounterRegInfo SqgCounterRegAddr[] = {
    {mmSQG_PERFCOUNTER0_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER0_LO, mmSQG_PERFCOUNTER0_HI},
    {mmSQG_PERFCOUNTER1_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER1_LO, mmSQG_PERFCOUNTER1_HI},
    {mmSQG_PERFCOUNTER2_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER2_LO, mmSQG_PERFCOUNTER2_HI},
    {mmSQG_PERFCOUNTER3_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER3_LO, mmSQG_PERFCOUNTER3_HI},
    {mmSQG_PERFCOUNTER4_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER4_LO, mmSQG_PERFCOUNTER4_HI},
    {mmSQG_PERFCOUNTER5_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER5_LO, mmSQG_PERFCOUNTER5_HI},
    {mmSQG_PERFCOUNTER6_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER6_LO, mmSQG_PERFCOUNTER6_HI},
    {mmSQG_PERFCOUNTER7_SELECT, mmSQG_PERFCOUNTER_CTRL, mmSQG_PERFCOUNTER7_LO, mmSQG_PERFCOUNTER7_HI}};

// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx12_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpcBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPC};
// Counter block CPF
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx12_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpfBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPF};
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx12_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockGRBMAttr};
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx12_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockSPIAttr, NULL /*SpiBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SPI};
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx12_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockSqAttr, NULL, SPM_SE_BLOCK_NAME_SQG};
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx12_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr, NULL /*SxBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SX};
// Counter block TCP
static const GpuBlockInfo TcpCounterBlockInfo = {"TCP", TcpCounterBlockId, 16, TcpCounterBlockMaxEvent, TcpCounterBlockNumCounters, TcpCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSeAttr|CounterBlockSaAttr};
// Counter block GL1A
static const GpuBlockInfo Gl1aCounterBlockInfo = {"GL1A", Gl1aCounterBlockId, 4, Gl1aCounterBlockMaxEvent, Gl1aCounterBlockNumCounters, Gl1aCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockDfltAttr|CounterBlockTcAttr};
// Counter block GL1C
static const GpuBlockInfo Gl1cCounterBlockInfo = {"GL1C", Gl1cCounterBlockId, 4, Gl1cCounterBlockMaxEvent, Gl1cCounterBlockNumCounters, Gl1cCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockSaAttr|CounterBlockDfltAttr|CounterBlockTcAttr};
// Counter block GL2A
static const GpuBlockInfo Gl2aCounterBlockInfo = {"GL2A", Gl2aCounterBlockId, 32, Gl2aCounterBlockMaxEvent, Gl2aCounterBlockNumCounters, Gl2aCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockTcAttr};
// Counter block GL2C
static const GpuBlockInfo Gl2cCounterBlockInfo = {"GL2C", Gl2cCounterBlockId, 32, Gl2cCounterBlockMaxEvent, Gl2cCounterBlockNumCounters, Gl2cCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockTcAttr};
// Counter block GCR
static const GpuBlockInfo GcrCounterBlockInfo = {"GCR", GcrCounterBlockId, 1, GcrCounterBlockMaxEvent, GcrCounterBlockNumCounters, GcrCounterRegAddr, gfx12_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, 235/*TaCounterBlockMaxEvent*/, TaCounterBlockNumCounters, TaCounterRegAddr, gfx12_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, NULL/*TaBlockDelayInfo*/, SPM_SE_BLOCK_NAME_TA};

}  // namespace gfx12
}  // namespace gfxip

#endif  // _GFX12_BLOCKTABLE_H_
