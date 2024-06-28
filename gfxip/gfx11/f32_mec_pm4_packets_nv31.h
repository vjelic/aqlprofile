//
//  (c) 2014-2021 Advanced Micro Devices, Inc.  All rights reserved.
//  THIS SOURCE FILE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
//  OR IMPLIED WARRANTIES . . .
//

#ifndef F32_MEC_PM4_PACKETS_H
#define F32_MEC_PM4_PACKETS_H

#ifndef PM4_MEC_HEADER_DEFINED
#define PM4_MEC_HEADER_DEFINED
typedef union PM4_MEC_TYPE_3_HEADER
{
    struct
    {
        uint32_t reserved1 : 8; ///< reserved
        uint32_t opcode    : 8; ///< IT opcode
        uint32_t count     : 14;///< number of DWORDs - 1 in the information body.
        uint32_t type      : 2; ///< packet identifier. It should be 3 for type 3 packets
    };
    uint32_t u32All;
} PM4_MEC_TYPE_3_HEADER;
#endif // PM4_MEC_HEADER_DEFINED

//--------------------MEC_ACQUIRE_MEM--------------------

#ifndef PM4_MEC_ACQUIRE_MEM_DEFINED
#define PM4_MEC_ACQUIRE_MEM_DEFINED

typedef struct PM4_MEC_ACQUIRE_MEM
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t reserved1;

    uint32_t coher_size;

    union
    {
        struct
        {
            uint32_t coher_size_hi:8;
            uint32_t reserved2:24;
        } bitfields4;
        uint32_t ordinal4;
    };

    uint32_t coher_base_lo;

    union
    {
        struct
        {
            uint32_t coher_base_hi:24;
            uint32_t reserved3:8;
        } bitfields6;
        uint32_t ordinal6;
    };

    union
    {
        struct
        {
            uint32_t poll_interval:16;
            uint32_t reserved4:16;
        } bitfields7;
        uint32_t ordinal7;
    };

    union
    {
        struct
        {
            uint32_t gcr_cntl:19;
            uint32_t reserved5:13;
        } bitfields8;
        uint32_t ordinal8;
    };

} PM4MEC_ACQUIRE_MEM, *PPM4MEC_ACQUIRE_MEM;
#endif

//--------------------MEC_ATOMIC_GDS--------------------

#ifndef PM4_MEC_ATOMIC_GDS_DEFINED
#define PM4_MEC_ATOMIC_GDS_DEFINED
enum MEC_ATOMIC_GDS_atom_cmp_swap_enum {
     atom_cmp_swap__mec_atomic_gds__dont_repeat = 0,
     atom_cmp_swap__mec_atomic_gds__repeat_until_pass = 1 };

enum MEC_ATOMIC_GDS_atom_complete_enum {
     atom_complete__mec_atomic_gds__dont_wait = 0,
     atom_complete__mec_atomic_gds__wait_for_completion = 1 };

enum MEC_ATOMIC_GDS_atom_read_enum {
     atom_read__mec_atomic_gds__dont_read_preop_data = 0,
     atom_read__mec_atomic_gds__read_preop_data = 1 };

enum MEC_ATOMIC_GDS_atom_rd_cntl_enum {
     atom_rd_cntl__mec_atomic_gds__32bits_1returnval = 0,
     atom_rd_cntl__mec_atomic_gds__32bits_2returnval = 1,
     atom_rd_cntl__mec_atomic_gds__64bits_1returnval = 2,
     atom_rd_cntl__mec_atomic_gds__64bits_2returnval = 3 };


typedef struct PM4_MEC_ATOMIC_GDS
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t atom_op:8;
            uint32_t reserved1:8;
            MEC_ATOMIC_GDS_atom_cmp_swap_enum atom_cmp_swap:1;
            MEC_ATOMIC_GDS_atom_complete_enum atom_complete:1;
            MEC_ATOMIC_GDS_atom_read_enum atom_read:1;
            MEC_ATOMIC_GDS_atom_rd_cntl_enum atom_rd_cntl:2;
            uint32_t reserved2:11;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t auto_inc_bytes:6;
            uint32_t reserved3:2;
            uint32_t dmode:1;
            uint32_t reserved4:23;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t atom_base:16;
            uint32_t reserved5:16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t atom_size:16;
            uint32_t reserved6:16;
        } bitfields5;
        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t atom_offset0:8;
            uint32_t reserved7:8;
            uint32_t atom_offset1:8;
            uint32_t reserved8:8;
        } bitfields6;
        uint32_t ordinal6;
    };

    uint32_t atom_dst;

    uint32_t atom_src0;

    uint32_t atom_src0_u;

    uint32_t atom_src1;

    uint32_t atom_src1_u;

} PM4MEC_ATOMIC_GDS, *PPM4MEC_ATOMIC_GDS;
#endif

//--------------------MEC_ATOMIC_MEM--------------------

#ifndef PM4_MEC_ATOMIC_MEM_DEFINED
#define PM4_MEC_ATOMIC_MEM_DEFINED
enum MEC_ATOMIC_MEM_command_enum {
     command__mec_atomic_mem__single_pass_atomic = 0,
     command__mec_atomic_mem__loop_until_compare_satisfied = 1,
     command__mec_atomic_mem__wait_for_write_confirmation = 2,
     command__mec_atomic_mem__send_and_continue = 3 };

enum MEC_ATOMIC_MEM_cache_policy_enum {
     cache_policy__mec_atomic_mem__lru = 0,
     cache_policy__mec_atomic_mem__stream = 1,
     cache_policy__mec_atomic_mem__noa = 2,
     cache_policy__mec_atomic_mem__bypass = 3 };


typedef struct PM4_MEC_ATOMIC_MEM
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t atomic:7;
            uint32_t reserved1:1;
            MEC_ATOMIC_MEM_command_enum command:4;
            uint32_t reserved2:13;
            MEC_ATOMIC_MEM_cache_policy_enum cache_policy:2;
            uint32_t reserved3:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    uint32_t src_data_lo;

    uint32_t src_data_hi;

    uint32_t cmp_data_lo;

    uint32_t cmp_data_hi;

    union
    {
        struct
        {
            uint32_t loop_interval:13;
            uint32_t reserved4:19;
        } bitfields9;
        uint32_t ordinal9;
    };

} PM4MEC_ATOMIC_MEM, *PPM4MEC_ATOMIC_MEM;
#endif

//--------------------MEC_COND_EXEC--------------------

#ifndef PM4_MEC_COND_EXEC_DEFINED
#define PM4_MEC_COND_EXEC_DEFINED
enum MEC_COND_EXEC_cache_policy_enum {
     cache_policy__mec_cond_exec__lru = 0,
     cache_policy__mec_cond_exec__stream = 1,
     cache_policy__mec_cond_exec__noa = 2,
     cache_policy__mec_cond_exec__bypass = 3 };


typedef struct PM4_MEC_COND_EXEC
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:2;
            uint32_t addr_lo:30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t addr_hi;

    union
    {
        struct
        {
            uint32_t reserved2:25;
            MEC_COND_EXEC_cache_policy_enum cache_policy:2;
            uint32_t reserved3:5;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t exec_count:14;
            uint32_t reserved4:18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4MEC_COND_EXEC, *PPM4MEC_COND_EXEC;
#endif

//--------------------MEC_COND_INDIRECT_BUFFER--------------------

#ifndef PM4_MEC_COND_INDIRECT_BUFFER_DEFINED
#define PM4_MEC_COND_INDIRECT_BUFFER_DEFINED
enum MEC_COND_INDIRECT_BUFFER_mode_enum {
     mode__mec_cond_indirect_buffer__if_then = 1,
     mode__mec_cond_indirect_buffer__if_then_else = 2 };

enum MEC_COND_INDIRECT_BUFFER_function_enum {
     function__mec_cond_indirect_buffer__always_pass = 0,
     function__mec_cond_indirect_buffer__less_than_ref_value = 1,
     function__mec_cond_indirect_buffer__less_than_equal_to_the_ref_value = 2,
     function__mec_cond_indirect_buffer__equal_to_the_reference_value = 3,
     function__mec_cond_indirect_buffer__not_equal_reference_value = 4,
     function__mec_cond_indirect_buffer__greater_than_or_equal_reference_value = 5,
     function__mec_cond_indirect_buffer__greater_than_reference_value = 6 };

enum MEC_COND_INDIRECT_BUFFER_cache_policy1_enum {
     cache_policy1__mec_cond_indirect_buffer__lru = 0,
     cache_policy1__mec_cond_indirect_buffer__stream = 1,
     cache_policy1__mec_cond_indirect_buffer__noa = 2,
     cache_policy1__mec_cond_indirect_buffer__bypass = 3 };

enum MEC_COND_INDIRECT_BUFFER_cache_policy2_enum {
     cache_policy2__mec_cond_indirect_buffer__lru = 0,
     cache_policy2__mec_cond_indirect_buffer__stream = 1,
     cache_policy2__mec_cond_indirect_buffer__noa = 2,
     cache_policy2__mec_cond_indirect_buffer__bypass = 3 };


typedef struct PM4_MEC_COND_INDIRECT_BUFFER
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_COND_INDIRECT_BUFFER_mode_enum mode:2;
            uint32_t reserved1:6;
            MEC_COND_INDIRECT_BUFFER_function_enum function:3;
            uint32_t reserved2:21;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved3:3;
            uint32_t compare_addr_lo:29;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t compare_addr_hi;

    uint32_t mask_lo;

    uint32_t mask_hi;

    uint32_t reference_lo;

    uint32_t reference_hi;

    union
    {
        struct
        {
            uint32_t reserved4:2;
            uint32_t ib_base1_lo:30;
        } bitfields9;
        uint32_t ordinal9;
    };

    uint32_t ib_base1_hi;

    union
    {
        struct
        {
            uint32_t ib_size1:20;
            uint32_t reserved5:8;
            MEC_COND_INDIRECT_BUFFER_cache_policy1_enum cache_policy1:2;
            uint32_t reserved6:2;
        } bitfields11;
        uint32_t ordinal11;
    };

    union
    {
        struct
        {
            uint32_t reserved7:2;
            uint32_t ib_base2_lo:30;
        } bitfields12;
        uint32_t ordinal12;
    };

    uint32_t ib_base2_hi;

    union
    {
        struct
        {
            uint32_t ib_size2:20;
            uint32_t reserved8:8;
            MEC_COND_INDIRECT_BUFFER_cache_policy2_enum cache_policy2:2;
            uint32_t reserved9:2;
        } bitfields14;
        uint32_t ordinal14;
    };

} PM4MEC_COND_INDIRECT_BUFFER, *PPM4MEC_COND_INDIRECT_BUFFER;
#endif

//--------------------MEC_COND_WRITE--------------------

#ifndef PM4_MEC_COND_WRITE_DEFINED
#define PM4_MEC_COND_WRITE_DEFINED
enum MEC_COND_WRITE_function_enum {
     function__mec_cond_write__always_pass = 0,
     function__mec_cond_write__less_than_ref_value = 1,
     function__mec_cond_write__less_than_equal_to_the_ref_value = 2,
     function__mec_cond_write__equal_to_the_reference_value = 3,
     function__mec_cond_write__not_equal_reference_value = 4,
     function__mec_cond_write__greater_than_or_equal_reference_value = 5,
     function__mec_cond_write__greater_than_reference_value = 6 };

enum MEC_COND_WRITE_poll_space_enum {
     poll_space__mec_cond_write__register = 0,
     poll_space__mec_cond_write__memory = 1 };

enum MEC_COND_WRITE_write_space_enum {
     write_space__mec_cond_write__register = 0,
     write_space__mec_cond_write__memory = 1,
     write_space__mec_cond_write__scratch = 2 };


typedef struct PM4_MEC_COND_WRITE
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_COND_WRITE_function_enum function:3;
            uint32_t reserved1:1;
            MEC_COND_WRITE_poll_space_enum poll_space:1;
            uint32_t reserved2:3;
            MEC_COND_WRITE_write_space_enum write_space:2;
            uint32_t reserved3:22;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t poll_address_lo;

    uint32_t poll_address_hi;

    uint32_t reference;

    uint32_t mask;

    uint32_t write_address_lo;

    uint32_t write_address_hi;

    uint32_t write_data;

} PM4MEC_COND_WRITE, *PPM4MEC_COND_WRITE;
#endif

//--------------------MEC_COPY_DATA--------------------

#ifndef PM4_MEC_COPY_DATA_DEFINED
#define PM4_MEC_COPY_DATA_DEFINED
enum MEC_COPY_DATA_src_sel_enum {
     src_sel__mec_copy_data__mem_mapped_register = 0,
     src_sel__mec_copy_data__tc_l2_obsolete = 1,
     src_sel__mec_copy_data__tc_l2 = 2,
     src_sel__mec_copy_data__gds = 3,
     src_sel__mec_copy_data__perfcounters = 4,
     src_sel__mec_copy_data__immediate_data = 5,
     src_sel__mec_copy_data__atomic_return_data = 6,
     src_sel__mec_copy_data__gds_atomic_return_data0 = 7,
     src_sel__mec_copy_data__gds_atomic_return_data1 = 8,
     src_sel__mec_copy_data__gpu_clock_count = 9,
     src_sel__mec_copy_data__system_clock_count = 10 };

enum MEC_COPY_DATA_dst_sel_enum {
     dst_sel__mec_copy_data__mem_mapped_register = 0,
     dst_sel__mec_copy_data__tc_l2 = 2,
     dst_sel__mec_copy_data__gds = 3,
     dst_sel__mec_copy_data__perfcounters = 4,
     dst_sel__mec_copy_data__tc_l2_obsolete = 5,
     dst_sel__mec_copy_data__mem_mapped_reg_dc = 6 };

enum MEC_COPY_DATA_src_cache_policy_enum {
     src_cache_policy__mec_copy_data__lru = 0,
     src_cache_policy__mec_copy_data__stream = 1,
     src_cache_policy__mec_copy_data__noa = 2,
     src_cache_policy__mec_copy_data__bypass = 3 };

enum MEC_COPY_DATA_count_sel_enum {
     count_sel__mec_copy_data__32_bits_of_data = 0,
     count_sel__mec_copy_data__64_bits_of_data = 1 };

enum MEC_COPY_DATA_wr_confirm_enum {
     wr_confirm__mec_copy_data__do_not_wait_for_confirmation = 0,
     wr_confirm__mec_copy_data__wait_for_confirmation = 1 };

enum MEC_COPY_DATA_dst_cache_policy_enum {
     dst_cache_policy__mec_copy_data__lru = 0,
     dst_cache_policy__mec_copy_data__stream = 1,
     dst_cache_policy__mec_copy_data__noa = 2,
     dst_cache_policy__mec_copy_data__bypass = 3 };

enum MEC_COPY_DATA_pq_exe_status_enum {
     pq_exe_status__mec_copy_data__default = 0,
     pq_exe_status__mec_copy_data__phase_update = 1 };


typedef struct PM4_MEC_COPY_DATA
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_COPY_DATA_src_sel_enum src_sel:4;
            uint32_t reserved1:4;
            MEC_COPY_DATA_dst_sel_enum dst_sel:4;
            uint32_t reserved2:1;
            MEC_COPY_DATA_src_cache_policy_enum src_cache_policy:2;
            uint32_t reserved3:1;
            MEC_COPY_DATA_count_sel_enum count_sel:1;
            uint32_t reserved4:3;
            MEC_COPY_DATA_wr_confirm_enum wr_confirm:1;
            uint32_t reserved5:4;
            MEC_COPY_DATA_dst_cache_policy_enum dst_cache_policy:2;
            uint32_t reserved6:2;
            MEC_COPY_DATA_pq_exe_status_enum pq_exe_status:1;
            uint32_t reserved7:2;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t src_reg_offset:18;
            uint32_t reserved8:14;
        } bitfields3a;
        struct
        {
            uint32_t reserved9:2;
            uint32_t src_32b_addr_lo:30;
        } bitfields3b;
        struct
        {
            uint32_t reserved10:3;
            uint32_t src_64b_addr_lo:29;
        } bitfields3c;
        struct
        {
            uint32_t src_gds_addr_lo:16;
            uint32_t reserved11:16;
        } bitfields3d;
        uint32_t imm_data;

        uint32_t ordinal3;
    };

    union
    {
        uint32_t src_memtc_addr_hi;

        uint32_t src_imm_data;

        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t dst_reg_offset:18;
            uint32_t reserved12:14;
        } bitfields5a;
        struct
        {
            uint32_t reserved13:2;
            uint32_t dst_32b_addr_lo:30;
        } bitfields5b;
        struct
        {
            uint32_t reserved14:3;
            uint32_t dst_64b_addr_lo:29;
        } bitfields5c;
        struct
        {
            uint32_t dst_gds_addr_lo:16;
            uint32_t reserved15:16;
        } bitfields5d;
        uint32_t ordinal5;
    };

    uint32_t dst_addr_hi;

} PM4MEC_COPY_DATA, *PPM4MEC_COPY_DATA;
#endif

//--------------------MEC_COPY_DATA_RB--------------------

#ifndef PM4_MEC_COPY_DATA_RB_DEFINED
#define PM4_MEC_COPY_DATA_RB_DEFINED

typedef struct PM4_MEC_COPY_DATA_RB
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t src_addr_lo;

    uint32_t src_addr_hi;

    uint32_t ptr_addr_lo;

    uint32_t ptr_addr_hi;

    uint32_t data_size;

    uint32_t circular_buffer_size;

    uint32_t circular_buffer_addr_lo;

    uint32_t circular_buffer_addr_hi;

} PM4MEC_COPY_DATA_RB, *PPM4MEC_COPY_DATA_RB;
#endif

//--------------------MEC_DISPATCH_DIRECT--------------------

#ifndef PM4_MEC_DISPATCH_DIRECT_DEFINED
#define PM4_MEC_DISPATCH_DIRECT_DEFINED

typedef struct PM4_MEC_DISPATCH_DIRECT
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t dim_x;

    uint32_t dim_y;

    uint32_t dim_z;

    uint32_t dispatch_initiator;

} PM4MEC_DISPATCH_DIRECT, *PPM4MEC_DISPATCH_DIRECT;
#endif

//--------------------MEC_DISPATCH_INDIRECT--------------------

#ifndef PM4_MEC_DISPATCH_INDIRECT_DEFINED
#define PM4_MEC_DISPATCH_INDIRECT_DEFINED

typedef struct PM4_MEC_DISPATCH_INDIRECT
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    uint32_t dispatch_initiator;

} PM4MEC_DISPATCH_INDIRECT, *PPM4MEC_DISPATCH_INDIRECT;
#endif

//--------------------MEC_DISPATCH_TASK_STATE_INIT--------------------

#ifndef PM4_MEC_DISPATCH_TASK_STATE_INIT_DEFINED
#define PM4_MEC_DISPATCH_TASK_STATE_INIT_DEFINED

typedef struct PM4_MEC_DISPATCH_TASK_STATE_INIT
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:8;
            uint32_t control_buf_addr_lo:24;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t control_buf_addr_hi;

} PM4MEC_DISPATCH_TASK_STATE_INIT, *PPM4MEC_DISPATCH_TASK_STATE_INIT;
#endif

//--------------------MEC_DISPATCH_TASKMESH_DIRECT_ACE--------------------

#ifndef PM4_MEC_DISPATCH_TASKMESH_DIRECT_ACE_DEFINED
#define PM4_MEC_DISPATCH_TASKMESH_DIRECT_ACE_DEFINED

typedef struct PM4_MEC_DISPATCH_TASKMESH_DIRECT_ACE
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t x_dim;

    uint32_t y_dim;

    uint32_t z_dim;

    uint32_t dispatch_initiator;

    union
    {
        struct
        {
            uint32_t ring_entry_loc:16;
            uint32_t reserved1:16;
        } bitfields6;
        uint32_t ordinal6;
    };

} PM4MEC_DISPATCH_TASKMESH_DIRECT_ACE, *PPM4MEC_DISPATCH_TASKMESH_DIRECT_ACE;
#endif

//--------------------MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE--------------------

#ifndef PM4_MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE_DEFINED
#define PM4_MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE_DEFINED

typedef struct PM4_MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:2;
            uint32_t data_addr_lo:30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t data_addr_hi;

    union
    {
        struct
        {
            uint32_t ring_entry_loc:16;
            uint32_t reserved2:16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t thread_trace_marker_enable:1;
            uint32_t count_indirect_enable:1;
            uint32_t draw_index_enable:1;
            uint32_t compute_xyz_dim_enable:1;
            uint32_t reserved3:12;
            uint32_t dispatch_index_loc:16;
        } bitfields5;
        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t compute_xyz_dim_loc:16;
            uint32_t reserved4:16;
        } bitfields6;
        uint32_t ordinal6;
    };

    uint32_t count;

    union
    {
        struct
        {
            uint32_t reserved5:2;
            uint32_t count_addr_lo:30;
        } bitfields8;
        uint32_t ordinal8;
    };

    uint32_t count_addr_hi;

    uint32_t stride;

    uint32_t dispatch_initiator;

} PM4MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE, *PPM4MEC_DISPATCH_TASKMESH_INDIRECT_MULTI_ACE;
#endif

//--------------------MEC_DMA_DATA--------------------

#ifndef PM4_MEC_DMA_DATA_DEFINED
#define PM4_MEC_DMA_DATA_DEFINED
enum MEC_DMA_DATA_src_cache_policy_enum {
     src_cache_policy__mec_dma_data__lru = 0,
     src_cache_policy__mec_dma_data__stream = 1,
     src_cache_policy__mec_dma_data__noa = 2,
     src_cache_policy__mec_dma_data__bypass = 3 };

enum MEC_DMA_DATA_dst_sel_enum {
     dst_sel__mec_dma_data__dst_addr_using_das = 0,
     dst_sel__mec_dma_data__gds = 1,
     dst_sel__mec_dma_data__dst_nowhere = 2,
     dst_sel__mec_dma_data__dst_addr_using_l2 = 3 };

enum MEC_DMA_DATA_dst_cache_policy_enum {
     dst_cache_policy__mec_dma_data__lru = 0,
     dst_cache_policy__mec_dma_data__stream = 1,
     dst_cache_policy__mec_dma_data__noa = 2,
     dst_cache_policy__mec_dma_data__bypass = 3 };

enum MEC_DMA_DATA_src_sel_enum {
     src_sel__mec_dma_data__src_addr_using_sas = 0,
     src_sel__mec_dma_data__gds = 1,
     src_sel__mec_dma_data__data = 2,
     src_sel__mec_dma_data__src_addr_using_l2 = 3 };

enum MEC_DMA_DATA_sas_enum {
     sas__mec_dma_data__memory = 0 };

enum MEC_DMA_DATA_das_enum {
     das__mec_dma_data__memory = 0 };

enum MEC_DMA_DATA_saic_enum {
     saic__mec_dma_data__increment = 0,
     saic__mec_dma_data__no_increment = 1 };

enum MEC_DMA_DATA_daic_enum {
     daic__mec_dma_data__increment = 0,
     daic__mec_dma_data__no_increment = 1 };


typedef struct PM4_MEC_DMA_DATA
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:13;
            MEC_DMA_DATA_src_cache_policy_enum src_cache_policy:2;
            uint32_t reserved2:5;
            MEC_DMA_DATA_dst_sel_enum dst_sel:2;
            uint32_t reserved3:3;
            MEC_DMA_DATA_dst_cache_policy_enum dst_cache_policy:2;
            uint32_t reserved4:2;
            MEC_DMA_DATA_src_sel_enum src_sel:2;
            uint32_t reserved5:1;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t src_addr_lo_or_data;

    uint32_t src_addr_hi;

    uint32_t dst_addr_lo;

    uint32_t dst_addr_hi;

    union
    {
        struct
        {
            uint32_t byte_count:26;
            MEC_DMA_DATA_sas_enum sas:1;
            MEC_DMA_DATA_das_enum das:1;
            MEC_DMA_DATA_saic_enum saic:1;
            MEC_DMA_DATA_daic_enum daic:1;
            uint32_t raw_wait:1;
            uint32_t dis_wc:1;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4MEC_DMA_DATA, *PPM4MEC_DMA_DATA;
#endif

//--------------------MEC_DMA_DATA_FILL_MULTI--------------------

#ifndef PM4_MEC_DMA_DATA_FILL_MULTI_DEFINED
#define PM4_MEC_DMA_DATA_FILL_MULTI_DEFINED
enum MEC_DMA_DATA_FILL_MULTI_dst_sel_enum {
     dst_sel__mec_dma_data_fill_multi__dst_addr_using_l2 = 3 };

enum MEC_DMA_DATA_FILL_MULTI_dst_cache_policy_enum {
     dst_cache_policy__mec_dma_data_fill_multi__lru = 0,
     dst_cache_policy__mec_dma_data_fill_multi__stream = 1,
     dst_cache_policy__mec_dma_data_fill_multi__noa = 2,
     dst_cache_policy__mec_dma_data_fill_multi__bypass = 3 };

enum MEC_DMA_DATA_FILL_MULTI_src_sel_enum {
     src_sel__mec_dma_data_fill_multi__data = 2 };


typedef struct PM4_MEC_DMA_DATA_FILL_MULTI
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:10;
            uint32_t memlog_clear:1;
            uint32_t reserved2:9;
            MEC_DMA_DATA_FILL_MULTI_dst_sel_enum dst_sel:2;
            uint32_t reserved3:3;
            MEC_DMA_DATA_FILL_MULTI_dst_cache_policy_enum dst_cache_policy:2;
            uint32_t reserved4:2;
            MEC_DMA_DATA_FILL_MULTI_src_sel_enum src_sel:2;
            uint32_t reserved5:1;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t byte_stride;

    uint32_t dma_count;

    uint32_t dst_addr_lo;

    uint32_t dst_addr_hi;

    union
    {
        struct
        {
            uint32_t byte_count:26;
            uint32_t reserved6:6;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4MEC_DMA_DATA_FILL_MULTI, *PPM4MEC_DMA_DATA_FILL_MULTI;
#endif

//--------------------MEC_EVENT_WRITE--------------------

#ifndef PM4_MEC_EVENT_WRITE_DEFINED
#define PM4_MEC_EVENT_WRITE_DEFINED
enum MEC_EVENT_WRITE_event_index_enum {
     event_index__mec_event_write__other = 0,
     event_index__mec_event_write__sample_pipelinestat = 2,
     event_index__mec_event_write__cs_partial_flush = 4,
     event_index__mec_event_write__sample_streamoutstats = 8,
     event_index__mec_event_write__sample_streamoutstats1 = 9,
     event_index__mec_event_write__sample_streamoutstats2 = 10,
     event_index__mec_event_write__sample_streamoutstats3 = 11 };

enum MEC_EVENT_WRITE_samp_plst_cntr_mode_enum {
     samp_plst_cntr_mode__mec_event_write__legacy_mode = 0,
     samp_plst_cntr_mode__mec_event_write__mixed_mode1 = 1,
     samp_plst_cntr_mode__mec_event_write__new_mode = 2,
     samp_plst_cntr_mode__mec_event_write__mixed_mode3 = 3 };


typedef struct PM4_MEC_EVENT_WRITE
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t event_type:6;
            uint32_t reserved1:2;
            MEC_EVENT_WRITE_event_index_enum event_index:4;
            uint32_t reserved2:17;
            MEC_EVENT_WRITE_samp_plst_cntr_mode_enum samp_plst_cntr_mode:2;
            uint32_t offload_enable:1;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MEC_EVENT_WRITE, *PPM4MEC_EVENT_WRITE;
#endif

//--------------------MEC_HDP_FLUSH--------------------

#ifndef PM4_MEC_HDP_FLUSH_DEFINED
#define PM4_MEC_HDP_FLUSH_DEFINED

typedef struct PM4_MEC_HDP_FLUSH
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t dummy;

} PM4MEC_HDP_FLUSH, *PPM4MEC_HDP_FLUSH;
#endif

//--------------------MEC_INDIRECT_BUFFER--------------------

#ifndef PM4_MEC_INDIRECT_BUFFER_DEFINED
#define PM4_MEC_INDIRECT_BUFFER_DEFINED
enum MEC_INDIRECT_BUFFER_cache_policy_enum {
     cache_policy__mec_indirect_buffer__lru = 0,
     cache_policy__mec_indirect_buffer__stream = 1,
     cache_policy__mec_indirect_buffer__noa = 2,
     cache_policy__mec_indirect_buffer__bypass = 3 };


typedef struct PM4_MEC_INDIRECT_BUFFER
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:2;
            uint32_t ib_base_lo:30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t ib_base_hi;

    union
    {
        struct
        {
            uint32_t ib_size:20;
            uint32_t chain:1;
            uint32_t offload_polling:1;
            uint32_t reserved2:1;
            uint32_t valid:1;
            uint32_t vmid:4;
            MEC_INDIRECT_BUFFER_cache_policy_enum cache_policy:2;
            uint32_t reserved3:1;
            uint32_t priv:1;
        } bitfields4;
        uint32_t ordinal4;
    };

} PM4MEC_INDIRECT_BUFFER, *PPM4MEC_INDIRECT_BUFFER;
#endif

//--------------------MEC_INDIRECT_BUFFER_PASID--------------------

#ifndef PM4_MEC_INDIRECT_BUFFER_PASID_DEFINED
#define PM4_MEC_INDIRECT_BUFFER_PASID_DEFINED
enum MEC_INDIRECT_BUFFER_PASID_cache_policy_enum {
     cache_policy__mec_indirect_buffer_pasid__lru = 0,
     cache_policy__mec_indirect_buffer_pasid__stream = 1,
     cache_policy__mec_indirect_buffer_pasid__noa = 2,
     cache_policy__mec_indirect_buffer_pasid__bypass = 3 };


typedef struct PM4_MEC_INDIRECT_BUFFER_PASID
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:2;
            uint32_t ib_base_lo:30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t ib_base_hi;

    union
    {
        struct
        {
            uint32_t ib_size:20;
            uint32_t chain:1;
            uint32_t offload_polling:1;
            uint32_t reserved2:1;
            uint32_t valid:1;
            uint32_t reserved3:4;
            MEC_INDIRECT_BUFFER_PASID_cache_policy_enum cache_policy:2;
            uint32_t reserved4:1;
            uint32_t priv:1;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t pasid:16;
            uint32_t reserved5:16;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4MEC_INDIRECT_BUFFER_PASID, *PPM4MEC_INDIRECT_BUFFER_PASID;
#endif

//--------------------MEC_INVALIDATE_TLBS--------------------

#ifndef PM4_MEC_INVALIDATE_TLBS_DEFINED
#define PM4_MEC_INVALIDATE_TLBS_DEFINED
enum MEC_INVALIDATE_TLBS_invalidate_sel_enum {
     invalidate_sel__mec_invalidate_tlbs__invalidate = 0,
     invalidate_sel__mec_invalidate_tlbs__use_pasid = 1 };

enum MEC_INVALIDATE_TLBS_mmhub_invalidate_sel_enum {
     mmhub_invalidate_sel__mec_invalidate_tlbs__do_not_invalidate_mmhub = 0,
     mmhub_invalidate_sel__mec_invalidate_tlbs__use_mmhub_flush_type = 1,
     mmhub_invalidate_sel__mec_invalidate_tlbs__use_gfx_flush_type = 2 };


typedef struct PM4_MEC_INVALIDATE_TLBS
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_INVALIDATE_TLBS_invalidate_sel_enum invalidate_sel:3;
            MEC_INVALIDATE_TLBS_mmhub_invalidate_sel_enum mmhub_invalidate_sel:2;
            uint32_t pasid:16;
            uint32_t reserved1:4;
            uint32_t mmhub_flush_type:3;
            uint32_t reserved2:1;
            uint32_t gfx_flush_type:3;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MEC_INVALIDATE_TLBS, *PPM4MEC_INVALIDATE_TLBS;
#endif

//--------------------MEC_LOAD_SH_REG_INDEX--------------------

#ifndef PM4_MEC_LOAD_SH_REG_INDEX_DEFINED
#define PM4_MEC_LOAD_SH_REG_INDEX_DEFINED
enum MEC_LOAD_SH_REG_INDEX_index_enum {
     index__mec_load_sh_reg_index__direct_addr = 0,
     index__mec_load_sh_reg_index__indirect_addr = 2 };

enum MEC_LOAD_SH_REG_INDEX_data_format_enum {
     data_format__mec_load_sh_reg_index__offset_and_size = 0,
     data_format__mec_load_sh_reg_index__offset_and_data = 1 };


typedef struct PM4_MEC_LOAD_SH_REG_INDEX
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_LOAD_SH_REG_INDEX_index_enum index:2;
            uint32_t mem_addr_lo:30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t mem_addr_hi;

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:15;
            MEC_LOAD_SH_REG_INDEX_data_format_enum data_format:1;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords:14;
            uint32_t reserved2:18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4MEC_LOAD_SH_REG_INDEX, *PPM4MEC_LOAD_SH_REG_INDEX;
#endif

//--------------------MEC_NOP--------------------

#ifndef PM4_MEC_NOP_DEFINED
#define PM4_MEC_NOP_DEFINED

typedef struct PM4_MEC_NOP
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

//  uint32_t data_block[];  // N-DWords

} PM4MEC_NOP, *PPM4MEC_NOP;
#endif

//--------------------MEC_PERFMON_CONTROL--------------------

#ifndef PM4_MEC_PERFMON_CONTROL_DEFINED
#define PM4_MEC_PERFMON_CONTROL_DEFINED
enum MEC_PERFMON_CONTROL_pmc_en_enum {
     pmc_en__mec_perfmon_control__perfmon_disable = 0,
     pmc_en__mec_perfmon_control__perfmon_enable = 1 };


typedef struct PM4_MEC_PERFMON_CONTROL
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t pmc_id:3;
            uint32_t reserved1:12;
            MEC_PERFMON_CONTROL_pmc_en_enum pmc_en:1;
            uint32_t pmc_unit_mask:8;
            uint32_t reserved2:8;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t pmc_event:14;
            uint32_t reserved3:18;
        } bitfields3;
        uint32_t ordinal3;
    };

} PM4MEC_PERFMON_CONTROL, *PPM4MEC_PERFMON_CONTROL;
#endif

//--------------------MEC_PRIME_UTCL2--------------------

#ifndef PM4_MEC_PRIME_UTCL2_DEFINED
#define PM4_MEC_PRIME_UTCL2_DEFINED
enum MEC_PRIME_UTCL2_cache_perm_enum {
     cache_perm__mec_prime_utcl2__read = 0,
     cache_perm__mec_prime_utcl2__write = 1,
     cache_perm__mec_prime_utcl2__execute = 2 };

enum MEC_PRIME_UTCL2_prime_mode_enum {
     prime_mode__mec_prime_utcl2__dont_wait_for_xack = 0,
     prime_mode__mec_prime_utcl2__wait_for_xack = 1 };


typedef struct PM4_MEC_PRIME_UTCL2
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_PRIME_UTCL2_cache_perm_enum cache_perm:3;
            MEC_PRIME_UTCL2_prime_mode_enum prime_mode:1;
            uint32_t reserved1:28;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    union
    {
        struct
        {
            uint32_t requested_pages:14;
            uint32_t reserved2:18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4MEC_PRIME_UTCL2, *PPM4MEC_PRIME_UTCL2;
#endif

//--------------------MEC_RELEASE_MEM--------------------

#ifndef PM4_MEC_RELEASE_MEM_DEFINED
#define PM4_MEC_RELEASE_MEM_DEFINED
enum MEC_RELEASE_MEM_event_index_enum {
     event_index__mec_release_mem__end_of_pipe = 5,
     event_index__mec_release_mem__shader_done = 6 };

enum MEC_RELEASE_MEM_cache_policy_enum {
     cache_policy__mec_release_mem__lru = 0,
     cache_policy__mec_release_mem__stream = 1,
     cache_policy__mec_release_mem__noa = 2,
     cache_policy__mec_release_mem__bypass = 3 };

enum MEC_RELEASE_MEM_dst_sel_enum {
     dst_sel__mec_release_mem__memory_controller = 0,
     dst_sel__mec_release_mem__tc_l2 = 1,
     dst_sel__mec_release_mem__queue_write_pointer_register = 2,
     dst_sel__mec_release_mem__queue_write_pointer_poll_mask_bit = 3 };

enum MEC_RELEASE_MEM_mes_action_id_enum {
     mes_action_id__mec_release_mem__no_mes_notification = 0,
     mes_action_id__mec_release_mem__interrupt_and_fence = 1,
     mes_action_id__mec_release_mem__interrupt_no_fence_then_address_payload = 2,
     mes_action_id__mec_release_mem__interrupt_and_address_payload = 3 };

enum MEC_RELEASE_MEM_int_sel_enum {
     int_sel__mec_release_mem__none = 0,
     int_sel__mec_release_mem__send_interrupt_only = 1,
     int_sel__mec_release_mem__send_interrupt_after_write_confirm = 2,
     int_sel__mec_release_mem__send_data_and_write_confirm = 3,
     int_sel__mec_release_mem__unconditionally_send_int_ctxid = 4,
     int_sel__mec_release_mem__conditionally_send_int_ctxid_based_on_32_bit_compare = 5,
     int_sel__mec_release_mem__conditionally_send_int_ctxid_based_on_64_bit_compare = 6 };

enum MEC_RELEASE_MEM_data_sel_enum {
     data_sel__mec_release_mem__none = 0,
     data_sel__mec_release_mem__send_32_bit_low = 1,
     data_sel__mec_release_mem__send_64_bit_data = 2,
     data_sel__mec_release_mem__send_gpu_clock_counter = 3,
     data_sel__mec_release_mem__send_system_clock_counter = 4,
     data_sel__mec_release_mem__store_gds_data_to_memory = 5 };


typedef struct PM4_MEC_RELEASE_MEM
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t event_type:6;
            uint32_t reserved1:2;
            MEC_RELEASE_MEM_event_index_enum event_index:4;
            uint32_t gcr_cntl:13;
            MEC_RELEASE_MEM_cache_policy_enum cache_policy:2;
            uint32_t reserved2:1;
            uint32_t pq_exe_status:1;
            uint32_t reserved3:1;
            uint32_t glk_inv:1;
            uint32_t pws_enable:1;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved4:16;
            MEC_RELEASE_MEM_dst_sel_enum dst_sel:2;
            uint32_t reserved5:2;
            uint32_t mes_intr_pipe:2;
            MEC_RELEASE_MEM_mes_action_id_enum mes_action_id:2;
            MEC_RELEASE_MEM_int_sel_enum int_sel:3;
            uint32_t reserved6:2;
            MEC_RELEASE_MEM_data_sel_enum data_sel:3;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reserved7:2;
            uint32_t address_lo_32b:30;
        } bitfields4a;
        struct
        {
            uint32_t reserved8:3;
            uint32_t address_lo_64b:29;
        } bitfields4b;
        uint32_t reserved9;

        uint32_t ordinal4;
    };

    union
    {
        uint32_t address_hi;

        uint32_t reserved10;

        uint32_t ordinal5;
    };

    union
    {
        uint32_t data_lo;

        uint32_t cmp_data_lo;

        struct
        {
            uint32_t dw_offset:16;
            uint32_t num_dwords:16;
        } bitfields6c;
        uint32_t reserved11;

        uint32_t ordinal6;
    };

    union
    {
        uint32_t data_hi;

        uint32_t cmp_data_hi;

        uint32_t reserved12;

        uint32_t reserved13;

        uint32_t ordinal7;
    };

    uint32_t int_ctxid;

} PM4MEC_RELEASE_MEM, *PPM4MEC_RELEASE_MEM;
#endif

//--------------------MEC_REWIND--------------------

#ifndef PM4_MEC_REWIND_DEFINED
#define PM4_MEC_REWIND_DEFINED

typedef struct PM4_MEC_REWIND
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:24;
            uint32_t offload_enable:1;
            uint32_t reserved2:6;
            uint32_t valid:1;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MEC_REWIND, *PPM4MEC_REWIND;
#endif

//--------------------MEC_SECURE_CONTROL--------------------

#ifndef PM4_MEC_SECURE_CONTROL_DEFINED
#define PM4_MEC_SECURE_CONTROL_DEFINED
enum MEC_SECURE_CONTROL_command_enum {
     command__mec_secure_control__clear_tmz_memory = 0 };


typedef struct PM4_MEC_SECURE_CONTROL
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_SECURE_CONTROL_command_enum command:8;
            uint32_t reserved1:24;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MEC_SECURE_CONTROL, *PPM4MEC_SECURE_CONTROL;
#endif

//--------------------MEC_SET_CONFIG_REG--------------------

#ifndef PM4_MEC_SET_CONFIG_REG_DEFINED
#define PM4_MEC_SET_CONFIG_REG_DEFINED
enum MEC_SET_CONFIG_REG_index_enum {
     index__mec_set_config_reg__default = 0,
     index__mec_set_config_reg__insert_vmid = 1 };


typedef struct PM4_MEC_SET_CONFIG_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:7;
            uint32_t vmid_shift:5;
            MEC_SET_CONFIG_REG_index_enum index:4;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_CONFIG_REG, *PPM4MEC_SET_CONFIG_REG;
#endif

//--------------------MEC_SET_QUEUE_REG--------------------

#ifndef PM4_MEC_SET_QUEUE_REG_DEFINED
#define PM4_MEC_SET_QUEUE_REG_DEFINED

typedef struct PM4_MEC_SET_QUEUE_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reg_offset:8;
            uint32_t reserved1:7;
            uint32_t defer_exec:1;
            uint32_t vqid:10;
            uint32_t reserved2:6;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_QUEUE_REG, *PPM4MEC_SET_QUEUE_REG;
#endif

//--------------------MEC_SET_SH_REG--------------------

#ifndef PM4_MEC_SET_SH_REG_DEFINED
#define PM4_MEC_SET_SH_REG_DEFINED
enum MEC_SET_SH_REG_index_enum {
     index__mec_set_sh_reg__default = 0,
     index__mec_set_sh_reg__insert_vmid = 1 };


typedef struct PM4_MEC_SET_SH_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:7;
            uint32_t vmid_shift:5;
            MEC_SET_SH_REG_index_enum index:4;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_SH_REG, *PPM4MEC_SET_SH_REG;
#endif

//--------------------MEC_SET_SH_REG_INDEX--------------------

#ifndef PM4_MEC_SET_SH_REG_INDEX_DEFINED
#define PM4_MEC_SET_SH_REG_INDEX_DEFINED
enum MEC_SET_SH_REG_INDEX_index_enum {
     index__mec_set_sh_reg_index__default = 0,
     index__mec_set_sh_reg_index__insert_vmid = 1,
     index__mec_set_sh_reg_index__apply_kmd_cu_and_mask = 3 };


typedef struct PM4_MEC_SET_SH_REG_INDEX
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:7;
            uint32_t vmid_shift:5;
            MEC_SET_SH_REG_INDEX_index_enum index:4;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_SH_REG_INDEX, *PPM4MEC_SET_SH_REG_INDEX;
#endif

//--------------------MEC_SET_UCONFIG_REG--------------------

#ifndef PM4_MEC_SET_UCONFIG_REG_DEFINED
#define PM4_MEC_SET_UCONFIG_REG_DEFINED

typedef struct PM4_MEC_SET_UCONFIG_REG
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reg_offset:16;
            uint32_t reserved1:16;
        } bitfields2;
        uint32_t ordinal2;
    };

//  uint32_t reg_data[];  // N-DWords

} PM4MEC_SET_UCONFIG_REG, *PPM4MEC_SET_UCONFIG_REG;
#endif

//--------------------MEC_WAIT_ON_CE_COUNTER--------------------

#ifndef PM4_MEC_WAIT_ON_CE_COUNTER_DEFINED
#define PM4_MEC_WAIT_ON_CE_COUNTER_DEFINED

typedef struct PM4_MEC_WAIT_ON_CE_COUNTER
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t cond_acquire_mem:1;
            uint32_t force_sync:1;
            uint32_t reserved1:30;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MEC_WAIT_ON_CE_COUNTER, *PPM4MEC_WAIT_ON_CE_COUNTER;
#endif

//--------------------MEC_WAIT_REG_MEM--------------------

#ifndef PM4_MEC_WAIT_REG_MEM_DEFINED
#define PM4_MEC_WAIT_REG_MEM_DEFINED
enum MEC_WAIT_REG_MEM_function_enum {
     function__mec_wait_reg_mem__always_pass = 0,
     function__mec_wait_reg_mem__less_than_ref_value = 1,
     function__mec_wait_reg_mem__less_than_equal_to_the_ref_value = 2,
     function__mec_wait_reg_mem__equal_to_the_reference_value = 3,
     function__mec_wait_reg_mem__not_equal_reference_value = 4,
     function__mec_wait_reg_mem__greater_than_or_equal_reference_value = 5,
     function__mec_wait_reg_mem__greater_than_reference_value = 6 };

enum MEC_WAIT_REG_MEM_mem_space_enum {
     mem_space__mec_wait_reg_mem__register_space = 0,
     mem_space__mec_wait_reg_mem__memory_space = 1 };

enum MEC_WAIT_REG_MEM_operation_enum {
     operation__mec_wait_reg_mem__wait_reg_mem = 0,
     operation__mec_wait_reg_mem__wr_wait_wr_reg = 1,
     operation__mec_wait_reg_mem__wait_mem_preemptable = 3 };

enum MEC_WAIT_REG_MEM_cache_policy_enum {
     cache_policy__mec_wait_reg_mem__lru = 0,
     cache_policy__mec_wait_reg_mem__stream = 1,
     cache_policy__mec_wait_reg_mem__noa = 2,
     cache_policy__mec_wait_reg_mem__bypass = 3 };


typedef struct PM4_MEC_WAIT_REG_MEM
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_WAIT_REG_MEM_function_enum function:3;
            uint32_t reserved1:1;
            MEC_WAIT_REG_MEM_mem_space_enum mem_space:2;
            MEC_WAIT_REG_MEM_operation_enum operation:2;
            uint32_t reserved2:14;
            uint32_t mes_intr_pipe:2;
            uint32_t mes_action:1;
            MEC_WAIT_REG_MEM_cache_policy_enum cache_policy:2;
            uint32_t reserved3:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved4:2;
            uint32_t mem_poll_addr_lo:30;
        } bitfields3a;
        struct
        {
            uint32_t reg_poll_addr:18;
            uint32_t reserved5:14;
        } bitfields3b;
        struct
        {
            uint32_t reg_write_addr1:18;
            uint32_t reserved6:14;
        } bitfields3c;
        uint32_t ordinal3;
    };

    union
    {
        uint32_t mem_poll_addr_hi;

        struct
        {
            uint32_t reg_write_addr2:18;
            uint32_t reserved7:14;
        } bitfields4b;
        uint32_t ordinal4;
    };

    uint32_t reference;

    uint32_t mask;

    union
    {
        struct
        {
            uint32_t poll_interval:16;
            uint32_t reserved8:15;
            uint32_t optimize_ace_offload_mode:1;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4MEC_WAIT_REG_MEM, *PPM4MEC_WAIT_REG_MEM;
#endif

//--------------------MEC_WAIT_REG_MEM64--------------------

#ifndef PM4_MEC_WAIT_REG_MEM64_DEFINED
#define PM4_MEC_WAIT_REG_MEM64_DEFINED
enum MEC_WAIT_REG_MEM64_function_enum {
     function__mec_wait_reg_mem64__always_pass = 0,
     function__mec_wait_reg_mem64__less_than_ref_value = 1,
     function__mec_wait_reg_mem64__less_than_equal_to_the_ref_value = 2,
     function__mec_wait_reg_mem64__equal_to_the_reference_value = 3,
     function__mec_wait_reg_mem64__not_equal_reference_value = 4,
     function__mec_wait_reg_mem64__greater_than_or_equal_reference_value = 5,
     function__mec_wait_reg_mem64__greater_than_reference_value = 6 };

enum MEC_WAIT_REG_MEM64_mem_space_enum {
     mem_space__mec_wait_reg_mem64__register_space = 0,
     mem_space__mec_wait_reg_mem64__memory_space = 1 };

enum MEC_WAIT_REG_MEM64_operation_enum {
     operation__mec_wait_reg_mem64__wait_reg_mem = 0,
     operation__mec_wait_reg_mem64__wr_wait_wr_reg = 1,
     operation__mec_wait_reg_mem64__wait_mem_preemptable = 3 };

enum MEC_WAIT_REG_MEM64_cache_policy_enum {
     cache_policy__mec_wait_reg_mem64__lru = 0,
     cache_policy__mec_wait_reg_mem64__stream = 1,
     cache_policy__mec_wait_reg_mem64__noa = 2,
     cache_policy__mec_wait_reg_mem64__bypass = 3 };


typedef struct PM4_MEC_WAIT_REG_MEM64
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            MEC_WAIT_REG_MEM64_function_enum function:3;
            uint32_t reserved1:1;
            MEC_WAIT_REG_MEM64_mem_space_enum mem_space:2;
            MEC_WAIT_REG_MEM64_operation_enum operation:2;
            uint32_t reserved2:14;
            uint32_t mes_intr_pipe:2;
            uint32_t mes_action:1;
            MEC_WAIT_REG_MEM64_cache_policy_enum cache_policy:2;
            uint32_t reserved3:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved4:3;
            uint32_t mem_poll_addr_lo:29;
        } bitfields3a;
        struct
        {
            uint32_t reg_poll_addr:18;
            uint32_t reserved5:14;
        } bitfields3b;
        struct
        {
            uint32_t reg_write_addr1:18;
            uint32_t reserved6:14;
        } bitfields3c;
        uint32_t ordinal3;
    };

    union
    {
        uint32_t mem_poll_addr_hi;

        struct
        {
            uint32_t reg_write_addr2:18;
            uint32_t reserved7:14;
        } bitfields4b;
        uint32_t ordinal4;
    };

    uint32_t reference;

    uint32_t reference_hi;

    uint32_t mask;

    uint32_t mask_hi;

    union
    {
        struct
        {
            uint32_t poll_interval:16;
            uint32_t reserved8:15;
            uint32_t optimize_ace_offload_mode:1;
        } bitfields9;
        uint32_t ordinal9;
    };

} PM4MEC_WAIT_REG_MEM64, *PPM4MEC_WAIT_REG_MEM64;
#endif

//--------------------MEC_WRITE_DATA--------------------

#ifndef PM4_MEC_WRITE_DATA_DEFINED
#define PM4_MEC_WRITE_DATA_DEFINED
enum MEC_WRITE_DATA_dst_sel_enum {
     dst_sel__mec_write_data__mem_mapped_register = 0,
     dst_sel__mec_write_data__tc_l2 = 2,
     dst_sel__mec_write_data__gds = 3,
     dst_sel__mec_write_data__memory = 5,
     dst_sel__mec_write_data__memory_mapped_adc_persistent_state = 6 };

enum MEC_WRITE_DATA_addr_incr_enum {
     addr_incr__mec_write_data__increment_address = 0,
     addr_incr__mec_write_data__do_not_increment_address = 1 };

enum MEC_WRITE_DATA_wr_confirm_enum {
     wr_confirm__mec_write_data__do_not_wait_for_write_confirmation = 0,
     wr_confirm__mec_write_data__wait_for_write_confirmation = 1 };

enum MEC_WRITE_DATA_cache_policy_enum {
     cache_policy__mec_write_data__lru = 0,
     cache_policy__mec_write_data__stream = 1,
     cache_policy__mec_write_data__noa = 2,
     cache_policy__mec_write_data__bypass = 3 };


typedef struct PM4_MEC_WRITE_DATA
{
    union
    {
        PM4_MEC_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    union
    {
        struct
        {
            uint32_t reserved1:8;
            MEC_WRITE_DATA_dst_sel_enum dst_sel:4;
            uint32_t reserved2:4;
            MEC_WRITE_DATA_addr_incr_enum addr_incr:1;
            uint32_t reserved3:3;
            MEC_WRITE_DATA_wr_confirm_enum wr_confirm:1;
            uint32_t reserved4:4;
            MEC_WRITE_DATA_cache_policy_enum cache_policy:2;
            uint32_t reserved5:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t dst_mmreg_addr:18;
            uint32_t reserved6:14;
        } bitfields3a;
        struct
        {
            uint32_t dst_gds_addr:16;
            uint32_t reserved7:16;
        } bitfields3b;
        struct
        {
            uint32_t reserved8:2;
            uint32_t dst_mem_addr_lo:30;
        } bitfields3c;
        uint32_t ordinal3;
    };

    uint32_t dst_mem_addr_hi;

//  uint32_t data[];  // N-DWords

} PM4MEC_WRITE_DATA, *PPM4MEC_WRITE_DATA;
#endif

#endif
