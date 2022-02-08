/*
 ***********************************************************************************************************************
 *
 *  Trade secret of Advanced Micro Devices, Inc.
 *  Copyright (c) 2016, Advanced Micro Devices, Inc., (unpublished)
 *
 *  All rights reserved. This notice is intended as a precaution against inadvertent publication and
 *does not imply
 *  publication or any waiver of confidentiality. The year included in the foregoing notice is the
 *year of creation of
 *  the work.
 *
 **********************************************************************************************************************/
/******************************************************************************
*
*  gfx9_pm4defs.h
*
*  GFX9 PM4 definitions, typedefs, and enumerations.
*
******************************************************************************/

#ifndef _GFX10_PM4DEFS_H_
#define _GFX10_PM4DEFS_H_

#define COPY_DATA_SEL_REG 0                   ///< Mem-mapped register
#define COPY_DATA_SEL_SRC_SYS_PERF_COUNTER 4  ///< Privileged memory performance counter
#define COPY_DATA_SEL_COUNT_1DW 0             ///< Copy 1 word (32 bits)
#define COPY_DATA_SEL_COUNT_2DW 1             ///< Copy 2 words (64 bits)

/*
 * PM4 packet helper constants and macros.
 * Constructed from header file:
 *    core/hw/gfxip/gfx9/chip/gfx9_f32_pfp_pm4_packets_gr.h
 */

// Shift amounts for each field of a type-3 PM4 header:
#define PM4_PREDICATE_SHIFT 0
#define PM4_SHADERTYPE_SHIFT 1
#define PM4_TYPE_SHIFT 30
#define PM4_COUNT_SHIFT 16
#define PM4_OPCODE_SHIFT 8

/*
 * Constructs a PM4 type-3 header and packs it into a uint.
 */
#define PM4_TYPE3_HDR(_opc_, _count_)                                                              \
  (uint32_t)((3) << PM4_TYPE_SHIFT | ((_count_)-2) << PM4_COUNT_SHIFT | (_opc_) << PM4_OPCODE_SHIFT)

#endif  // _GFX10_PM4DEFS_H_
