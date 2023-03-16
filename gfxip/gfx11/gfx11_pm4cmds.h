/*
***************************************************************************************************
*
*  Trade secret of Advanced Micro Devices, Inc.
*  Copyright (c) 2021 Advanced Micro Devices, Inc. (unpublished)
*
*  All rights reserved.  This notice is intended as a precaution against inadvertent publication and
*  does not imply publication or any waiver of confidentiality.  The year included in the foregoing
*  notice is the year of creation of the work.
*
***************************************************************************************************
*/

#ifndef _GFX11_PM4CMDS_H_
#define _GFX11_PM4CMDS_H_

/******************************************************************************
*
*  gfx11_pm4cmds.h
*
*  GFX11 PM4 definitions, typedefs, and enumerations.
*
******************************************************************************/

#include "gfx11_pm4defs.h"
#include "gfx11_pm4_it_opcodes.h"

// Wrapper on the new header-generation macro
#define PM4_CMD(op, count)                          PM4_TYPE_3_HDR(op, count, ShaderGraphics, PredDisable)

//IT_DRAW_INDEX is replaced by IT_DRAW_INDEX_2
#define PM4_CMD_DRAW_INDEX_2(count)                 PM4_CMD(IT_DRAW_INDEX_2, count)
#define PM4_CMD_DRAW_INDEX_OFFSET_2(count)          PM4_CMD(IT_DRAW_INDEX_OFFSET_2, count)
#define PM4_CMD_DRAW_INDEX_AUTO(count)              PM4_CMD(IT_DRAW_INDEX_AUTO, count)
#define PM4_CMD_DRAW_INDEX_TYPE(count)              PM4_CMD(IT_INDEX_TYPE, count)
#define PM4_CMD_DRAW_INDEX_BASE(count)              PM4_CMD(IT_INDEX_BASE, count)
#define PM4_CMD_DRAW_INDEX_BUFFER_SIZE(count)       PM4_CMD(IT_INDEX_BUFFER_SIZE, count)
#define PM4_CMD_DRAW_NUM_INSTANCES(count)           PM4_CMD(IT_NUM_INSTANCES, count)
#define PM4_CMD_DRAW_PREAMBLE(count)                PM4_CMD(IT_DRAW_PREAMBLE, count)

#define PM4_CMD_WAIT_REG_MEM(count)                 PM4_CMD(IT_WAIT_REG_MEM, count)
#define PM4_CMD_MEM_WRITE(count)                    PM4_CMD(IT_MEM_WRITE, count)
#define PM4_CMD_EVENT_WRITE(count)                  PM4_CMD(IT_EVENT_WRITE, count)
#define PM4_CMD_EVENT_WRITE_EOP(count)              PM4_CMD(IT_EVENT_WRITE_EOP, count)
#define PM4_CMD_STRMOUT_BUFFER_UPDATE(count)        PM4_CMD(IT_STRMOUT_BUFFER_UPDATE,count)
#define PM4_CMD_COPY_DATA(count)                    PM4_CMD(IT_COPY_DATA,count)
#define PM4_CMD_CP_DMA(count)                       PM4_CMD(IT_CP_DMA, count)
#define PM4_CMD_SET_PREDICATION(count)              PM4_CMD(IT_SET_PREDICATION,count)
#define PM4_CMD_SURFACE_BASE_UPDATE(count)          PM4_CMD(IT_SURFACE_BASE_UPDATE,count)
#define PM4_CMD_STRMOUT_BASE_UPDATE(count)          PM4_CMD(IT_STRMOUT_BASE_UPDATE,count)
#define PM4_CMD_START_3D_CMDBUF(count)              PM4_CMD(IT_START_3D_CMDBUF, count)
#define PM4_CMD_ROLL_CONTEXT(count)                 PM4_CMD(IT_ROLL_CONTEXT, count)
#define PM4_CMD_CONTEXT_CTL(count)                  PM4_CMD(IT_CONTEXT_CONTROL, count)
#define PM4_CMD_PRED_EXEC                           PM4_CMD(IT_PRED_EXEC, 2)
#define PM4_CMD_SURFACE_SYNC(count)                 PM4_CMD(IT_SURFACE_SYNC, count)
#define PM4_CMD_ACQUIRE_MEM(count)                  PM4_CMD(IT_ACQUIRE_MEM, count)
#define PM4_CMD_RELEASE_MEM(count)                  PM4_CMD(IT_RELEASE_MEM, count)

#define PM4_CMD_LOAD_CONFIG_REG(count)              PM4_CMD(IT_LOAD_CONFIG_REG, count)
#define PM4_CMD_LOAD_CONTEXT_REG(count)             PM4_CMD(IT_LOAD_CONTEXT_REG, count)
#define PM4_CMD_LOAD_SH_REG(count)                  PM4_CMD(IT_LOAD_SH_REG, count)
#define PM4_CMD_LOAD_UCONFIG_REG(count)             PM4_CMD(IT_LOAD_UCONFIG_REG, count)

#define PM4_CMD_SET_CONFIG_REG(count)               PM4_CMD(IT_SET_CONFIG_REG, count)
#define PM4_CMD_SET_CONTEXT_REG(count)              PM4_CMD(IT_SET_CONTEXT_REG, count)
#define PM4_CMD_SET_SH_REG(count)                   PM4_CMD(IT_SET_SH_REG, count)
#define PM4_CMD_SET_UCONFIG_REG(count)              PM4_CMD(IT_SET_UCONFIG_REG, count)

#define PM4_CMD_INDIRECT_BUFFER_CNST_END(count)     PM4_CMD(IT_INDIRECT_BUFFER_CNST_END, count)
#define PM4_CMD_INDIRECT_BUFFER_CNST_PRIV(count)    PM4_CMD(IT_INDIRECT_BUFFER_CNST_PRIV, count)
#define PM4_CMD_INDIRECT_BUFFER_CNST(count)         PM4_CMD(IT_INDIRECT_BUFFER_CNST, count)

#define PM4_CMD_LOAD_CONST_RAM(count)               PM4_CMD(IT_LOAD_CONST_RAM, count)
#define PM4_CMD_WRITE_CONST_RAM(count)              PM4_CMD(IT_WRITE_CONST_RAM, count)
#define PM4_CMD_DUMP_CONST_RAM(count)               PM4_CMD(IT_DUMP_CONST_RAM, count)

#define PM4_CMD_INC_CE_COUNTER(count)               PM4_CMD(IT_INCREMENT_CE_COUNTER, count)
#define PM4_CMD_INC_DE_COUNTER(count)               PM4_CMD(IT_INCREMENT_DE_COUNTER, count)

#define PM4_CMD_WAIT_ON_CE_COUNTER(count)           PM4_CMD(IT_WAIT_ON_CE_COUNTER, count)
#define PM4_CMD_WAIT_ON_DE_COUNTER_DIFF(count)      PM4_CMD(IT_WAIT_ON_DE_COUNTER_DIFF, count)

#define PM4_CMD_WRITE_DATA(count)                   PM4_CMD(IT_WRITE_DATA, count)

#define PM4_CMD_PREAMBLE_CNTL(count)                PM4_CMD(IT_PREAMBLE_CNTL, count)

#define PM4_CMD_EVENT_WRITE_EOS(count)              PM4_CMD(IT_EVENT_WRITE_EOS, count)

#endif // _GFX11_PM4CMDS_H_
