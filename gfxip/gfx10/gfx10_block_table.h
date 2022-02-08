#ifndef _GFX10_BLOCKTABLE_H_
#define _GFX10_BLOCKTABLE_H_

namespace gfxip {
namespace gfx10 {

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
 * GDS
 */
static const CounterRegInfo GdsCounterRegAddr[] = {
    {mmGDS_PERFCOUNTER0_SELECT, 0, mmGDS_PERFCOUNTER0_LO, mmGDS_PERFCOUNTER0_HI},
    {mmGDS_PERFCOUNTER1_SELECT, 0, mmGDS_PERFCOUNTER1_LO, mmGDS_PERFCOUNTER1_HI},
    {mmGDS_PERFCOUNTER2_SELECT, 0, mmGDS_PERFCOUNTER2_LO, mmGDS_PERFCOUNTER2_HI},
    {mmGDS_PERFCOUNTER3_SELECT, 0, mmGDS_PERFCOUNTER3_LO, mmGDS_PERFCOUNTER3_HI}};

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
 * SX
 */
static const CounterRegInfo SxCounterRegAddr[] = {
    {mmSX_PERFCOUNTER0_SELECT, 0, mmSX_PERFCOUNTER0_LO, mmSX_PERFCOUNTER0_HI},
    {mmSX_PERFCOUNTER1_SELECT, 0, mmSX_PERFCOUNTER1_LO, mmSX_PERFCOUNTER1_HI},
    {mmSX_PERFCOUNTER2_SELECT, 0, mmSX_PERFCOUNTER2_LO, mmSX_PERFCOUNTER2_HI},
    {mmSX_PERFCOUNTER3_SELECT, 0, mmSX_PERFCOUNTER3_LO, mmSX_PERFCOUNTER3_HI}};

// Define GFX10 specific blocks table entries like GC caches blocks
/*
 * GCR
 */
static const CounterRegInfo GcrCounterRegAddr[] = {
    {mmGCR_PERFCOUNTER0_SELECT, mmGCR_GENERAL_CNTL, mmGCR_PERFCOUNTER0_LO, mmGCR_PERFCOUNTER0_HI},
    {mmGCR_PERFCOUNTER1_SELECT, mmGCR_GENERAL_CNTL, mmGCR_PERFCOUNTER1_LO, mmGCR_PERFCOUNTER1_HI},
};

/*
 * GL1A
 */
static const CounterRegInfo Gl1aCounterRegAddr[] = {
    {mmGL1A_PERFCOUNTER0_SELECT, 0, mmGL1A_PERFCOUNTER0_LO, mmGL1A_PERFCOUNTER0_HI},
    {mmGL1A_PERFCOUNTER1_SELECT, 0, mmGL1A_PERFCOUNTER1_LO, mmGL1A_PERFCOUNTER1_HI},
    {mmGL1A_PERFCOUNTER2_SELECT, 0, mmGL1A_PERFCOUNTER2_LO, mmGL1A_PERFCOUNTER2_HI},
    {mmGL1A_PERFCOUNTER3_SELECT, 0, mmGL1A_PERFCOUNTER3_LO, mmGL1A_PERFCOUNTER3_HI},
};

/*
 * GL1C
 */
static const CounterRegInfo Gl1cCounterRegAddr[] = {
    {mmGL1C_PERFCOUNTER0_SELECT, 0, mmGL1C_PERFCOUNTER0_LO, mmGL1C_PERFCOUNTER0_HI},
    {mmGL1C_PERFCOUNTER1_SELECT, 0, mmGL1C_PERFCOUNTER1_LO, mmGL1C_PERFCOUNTER1_HI},
    {mmGL1C_PERFCOUNTER2_SELECT, 0, mmGL1C_PERFCOUNTER2_LO, mmGL1C_PERFCOUNTER2_HI},
    {mmGL1C_PERFCOUNTER3_SELECT, 0, mmGL1C_PERFCOUNTER3_LO, mmGL1C_PERFCOUNTER3_HI},
};

/*
 * GL2A
 */
static const CounterRegInfo Gl2aCounterRegAddr[] = {
    {mmGL2A_PERFCOUNTER0_SELECT, 0, mmGL2A_PERFCOUNTER0_LO, mmGL2A_PERFCOUNTER0_HI},
    {mmGL2A_PERFCOUNTER1_SELECT, 0, mmGL2A_PERFCOUNTER1_LO, mmGL2A_PERFCOUNTER1_HI},
    {mmGL2A_PERFCOUNTER2_SELECT, 0, mmGL2A_PERFCOUNTER2_LO, mmGL2A_PERFCOUNTER2_HI},
    {mmGL2A_PERFCOUNTER3_SELECT, 0, mmGL2A_PERFCOUNTER3_LO, mmGL2A_PERFCOUNTER3_HI},
};

/*
 * GL2C
 */
static const CounterRegInfo Gl2cCounterRegAddr[] = {
    {mmGL2C_PERFCOUNTER0_SELECT, 0, mmGL2C_PERFCOUNTER0_LO, mmGL2C_PERFCOUNTER0_HI},
    {mmGL2C_PERFCOUNTER1_SELECT, 0, mmGL2C_PERFCOUNTER1_LO, mmGL2C_PERFCOUNTER1_HI},
    {mmGL2C_PERFCOUNTER2_SELECT, 0, mmGL2C_PERFCOUNTER2_LO, mmGL2C_PERFCOUNTER2_HI},
    {mmGL2C_PERFCOUNTER3_SELECT, 0, mmGL2C_PERFCOUNTER3_LO, mmGL2C_PERFCOUNTER3_HI},
};

/*
 * GUS
 */
static const CounterRegInfo GusCounterRegAddr[] = {
  {mmGUS_PERFCOUNTER0_CFG, mmGUS_PERFCOUNTER_RSLT_CNTL, mmGUS_PERFCOUNTER_LO , mmGUS_PERFCOUNTER_HI},
  {mmGUS_PERFCOUNTER1_CFG, mmGUS_PERFCOUNTER_RSLT_CNTL, mmGUS_PERFCOUNTER2_LO , mmGUS_PERFCOUNTER2_HI},
};

/*
 * TA
 */
static const CounterRegInfo TaCounterRegAddr[] = {
    {mmTA_PERFCOUNTER0_SELECT, 0, mmTA_PERFCOUNTER0_LO, mmTA_PERFCOUNTER0_HI},
    {mmTA_PERFCOUNTER1_SELECT, 0, mmTA_PERFCOUNTER1_LO, mmTA_PERFCOUNTER1_HI}};

// Counter block CPC
static const GpuBlockInfo CpcCounterBlockInfo = {"CPC", CpcCounterBlockId, 1, CpcCounterBlockMaxEvent, CpcCounterBlockNumCounters, CpcCounterRegAddr, gfx10_cntx_prim::select_value<regCPC_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpcBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPC};
// Counter block CPF
static const GpuBlockInfo CpfCounterBlockInfo = {"CPF", CpfCounterBlockId, 1, CpfCounterBlockMaxEvent, CpfCounterBlockNumCounters, CpfCounterRegAddr, gfx10_cntx_prim::select_value<regCPF_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*CpfBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_CPF};
// Counter block GDS
static const GpuBlockInfo GdsCounterBlockInfo = {"GDS", GdsCounterBlockId, 1, GdsCounterBlockMaxEvent, GdsCounterBlockNumCounters, GdsCounterRegAddr, gfx10_cntx_prim::select_value<regGDS_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr|CounterBlockSpmGlobalAttr, NULL/*GdsBlockDelayInfo*/, SPM_GLOBAL_BLOCK_NAME_GDS};
// Counter block GRBM
static const GpuBlockInfo GrbmCounterBlockInfo = {"GRBM", GrbmCounterBlockId, 1, GrbmCounterBlockMaxEvent, GrbmCounterBlockNumCounters, GrbmCounterRegAddr, gfx10_cntx_prim::select_value<regGRBM_PERFCOUNTER0_SELECT>, CounterBlockDfltAttr};
// Counter block GRBMSE
static const GpuBlockInfo GrbmSeCounterBlockInfo = {"GRBM_SE", GrbmSeCounterBlockId, 1, GrbmSeCounterBlockMaxEvent, GrbmSeCounterBlockNumCounters, GrbmSeCounterRegAddr, gfx10_cntx_prim::select_value<regGRBM_SE0_PERFCOUNTER_SELECT>, CounterBlockDfltAttr};
// Counter block SPI
static const GpuBlockInfo SpiCounterBlockInfo = {"SPI", SpiCounterBlockId, 1, SpiCounterBlockMaxEvent, SpiCounterBlockNumCounters, SpiCounterRegAddr, gfx10_cntx_prim::select_value<regSPI_PERFCOUNTER0_SELECT>, CounterBlockSeAttr, NULL /*SpiBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SPI};
// Counter block SQ
static const GpuBlockInfo SqCounterBlockInfo = {"SQ", SqCounterBlockId, 1, SqCounterBlockMaxEvent, SqCounterBlockNumCounters, SqCounterRegAddr, gfx10_cntx_prim::sq_select_value, CounterBlockSeAttr|CounterBlockSqAttr, NULL, SPM_SE_BLOCK_NAME_SQG};
// Counter block SX
static const GpuBlockInfo SxCounterBlockInfo = {"SX", SxCounterBlockId, 1, SxCounterBlockMaxEvent, SxCounterBlockNumCounters, SxCounterRegAddr, gfx10_cntx_prim::select_value<regSX_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockCleanAttr, NULL /*SxBlockDelayInfo*/, SPM_SE_BLOCK_NAME_SX};
// Counter block GL1A
static const GpuBlockInfo Gl1aCounterBlockInfo = {"GL1A", Gl1aCounterBlockId, 16, Gl1aCounterBlockMaxEvent, Gl1aCounterBlockNumCounters, Gl1aCounterRegAddr, gfx10_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block GL1C
static const GpuBlockInfo Gl1cCounterBlockInfo = {"GL1C", Gl1cCounterBlockId, 16, Gl1cCounterBlockMaxEvent, Gl1cCounterBlockNumCounters, Gl1cCounterRegAddr, gfx10_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block GL2A
static const GpuBlockInfo Gl2aCounterBlockInfo = {"GL2A", Gl2aCounterBlockId, 16, Gl2aCounterBlockMaxEvent, Gl2aCounterBlockNumCounters, Gl2aCounterRegAddr, gfx10_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block GL2C
static const GpuBlockInfo Gl2cCounterBlockInfo = {"GL2C", Gl2cCounterBlockId, 16, Gl2cCounterBlockMaxEvent, Gl2cCounterBlockNumCounters, Gl2cCounterRegAddr, gfx10_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block GCR
static const GpuBlockInfo GcrCounterBlockInfo = {"GCR", GcrCounterBlockId, 1, GcrCounterBlockMaxEvent, GcrCounterBlockNumCounters, GcrCounterRegAddr, gfx10_cntx_prim::select_value<regTCP_PERFCOUNTER0_SELECT>, CounterBlockTcAttr};
// Counter block GUS
static const GpuBlockInfo GusCounterBlockInfo = {"GUS", GusCounterBlockId, 1, GusCounterBlockMaxEvent, GusCounterBlockNumCounters, GusCounterRegAddr, gfx10_cntx_prim::mc_select_value<regRPB_PERFCOUNTER0_CFG>, CounterBlockGusAttr};
// Counter block TA
static const GpuBlockInfo TaCounterBlockInfo = {"TA", TaCounterBlockId, TaCounterBlockNumInstances, 235/*TaCounterBlockMaxEvent*/, TaCounterBlockNumCounters, TaCounterRegAddr, gfx10_cntx_prim::select_value<regTA_PERFCOUNTER0_SELECT>, CounterBlockSeAttr|CounterBlockTcAttr, NULL/*TaBlockDelayInfo*/, SPM_SE_BLOCK_NAME_TA};

}  // namespace gfx10
}  // namespace gfxip

#endif  //  _GFX10_BLOCKTABLE_H_
