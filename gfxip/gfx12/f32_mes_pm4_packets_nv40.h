// Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved.

#ifndef F32_MES_PM4_PACKETS_H
#define F32_MES_PM4_PACKETS_H

#ifndef PM4_MES_HEADER_DEFINED
#define PM4_MES_HEADER_DEFINED
typedef union PM4_MES_TYPE_3_HEADER
{
    struct
    {
        uint32_t reserved1 : 8; ///< reserved
        uint32_t opcode    : 8; ///< IT opcode
        uint32_t count     : 14;///< number of DWORDs - 1 in the information body.
        uint32_t type      : 2; ///< packet identifier. It should be 3 for type 3 packets
    };
    uint32_t u32All;
} PM4_MES_TYPE_3_HEADER;
#endif // PM4_MES_HEADER_DEFINED

//--------------------MES_COPY_DATA--------------------

#ifndef PM4_MES_COPY_DATA_DEFINED
#define PM4_MES_COPY_DATA_DEFINED
enum MES_COPY_DATA_src_sel_enum {
     src_sel__mes_copy_data__mem_mapped_register = 0,
     src_sel__mes_copy_data__tc_l2_obsolete = 1,
     src_sel__mes_copy_data__tc_l2 = 2,
     src_sel__mes_copy_data__perfcounters = 4,
     src_sel__mes_copy_data__immediate_data = 5,
     src_sel__mes_copy_data__atomic_return_data = 6,
     src_sel__mes_copy_data__gpu_clock_count = 9,
     src_sel__mes_copy_data__system_clock_count = 10 };

enum MES_COPY_DATA_dst_sel_enum {
     dst_sel__mes_copy_data__mem_mapped_register = 0,
     dst_sel__mes_copy_data__tc_l2 = 2,
     dst_sel__mes_copy_data__perfcounters = 4,
     dst_sel__mes_copy_data__tc_l2_obsolete = 5 };

enum MES_COPY_DATA_src_temporal_enum {
     src_temporal__mes_copy_data__rt = 0,
     src_temporal__mes_copy_data__nt = 1,
     src_temporal__mes_copy_data__ht = 2,
     src_temporal__mes_copy_data__lu = 3 };

enum MES_COPY_DATA_count_sel_enum {
     count_sel__mes_copy_data__32_bits_of_data = 0,
     count_sel__mes_copy_data__64_bits_of_data = 1 };

enum MES_COPY_DATA_wr_confirm_enum {
     wr_confirm__mes_copy_data__do_not_wait_for_confirmation = 0,
     wr_confirm__mes_copy_data__wait_for_confirmation = 1 };

enum MES_COPY_DATA_dst_temporal_enum {
     dst_temporal__mes_copy_data__rt = 0,
     dst_temporal__mes_copy_data__nt = 1,
     dst_temporal__mes_copy_data__ht = 2,
     dst_temporal__mes_copy_data__lu = 3 };


typedef struct PM4_MES_COPY_DATA
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            MES_COPY_DATA_src_sel_enum src_sel:4;
            uint32_t reserved1:4;
            MES_COPY_DATA_dst_sel_enum dst_sel:4;
            uint32_t reserved2:1;
            MES_COPY_DATA_src_temporal_enum src_temporal:2;
            uint32_t reserved3:1;
            MES_COPY_DATA_count_sel_enum count_sel:1;
            uint32_t reserved4:3;
            MES_COPY_DATA_wr_confirm_enum wr_confirm:1;
            uint32_t reserved5:4;
            MES_COPY_DATA_dst_temporal_enum dst_temporal:2;
            uint32_t reserved6:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        uint32_t src_reg_offset_lo;

        struct
        {
            uint32_t reserved7:2;
            uint32_t src_32b_addr_lo:30;
        } bitfields3b;
        struct
        {
            uint32_t reserved8:3;
            uint32_t src_64b_addr_lo:29;
        } bitfields3c;
        uint32_t imm_data;

        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t src_reg_offset_hi:8;
            uint32_t reserved9:24;
        } bitfields4a;
        uint32_t src_memtc_addr_hi;

        uint32_t src_imm_data;

        uint32_t ordinal4;
    };

    union
    {
        uint32_t dst_reg_offset_lo;

        struct
        {
            uint32_t reserved10:2;
            uint32_t dst_32b_addr_lo:30;
        } bitfields5b;
        struct
        {
            uint32_t reserved11:3;
            uint32_t dst_64b_addr_lo:29;
        } bitfields5c;
        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t dst_reg_offset_hi:8;
            uint32_t reserved12:24;
        } bitfields6a;
        uint32_t dst_addr_hi;

        uint32_t ordinal6;
    };

} PM4MES_COPY_DATA, *PPM4MES_COPY_DATA;
#endif

//--------------------MES_INVALIDATE_TLBS--------------------

#ifndef PM4_MES_INVALIDATE_TLBS_DEFINED
#define PM4_MES_INVALIDATE_TLBS_DEFINED
enum MES_INVALIDATE_TLBS_invalidate_sel_enum {
     invalidate_sel__mes_invalidate_tlbs__invalidate = 0,
     invalidate_sel__mes_invalidate_tlbs__use_pasid = 1 };

enum MES_INVALIDATE_TLBS_mmhub_invalidate_sel_enum {
     mmhub_invalidate_sel__mes_invalidate_tlbs__do_not_invalidate_mmhub = 0,
     mmhub_invalidate_sel__mes_invalidate_tlbs__use_mmhub_flush_type = 1,
     mmhub_invalidate_sel__mes_invalidate_tlbs__use_gfx_flush_type = 2 };


typedef struct PM4_MES_INVALIDATE_TLBS
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            MES_INVALIDATE_TLBS_invalidate_sel_enum invalidate_sel:3;
            MES_INVALIDATE_TLBS_mmhub_invalidate_sel_enum mmhub_invalidate_sel:2;
            uint32_t pasid:16;
            uint32_t reserved1:4;
            uint32_t mmhub_flush_type:3;
            uint32_t reserved2:1;
            uint32_t gfx_flush_type:3;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4MES_INVALIDATE_TLBS, *PPM4MES_INVALIDATE_TLBS;
#endif

//--------------------MES_MAP_QUEUES--------------------

#ifndef PM4_MES_MAP_QUEUES_DEFINED
#define PM4_MES_MAP_QUEUES_DEFINED
enum MES_MAP_QUEUES_extended_engine_sel_enum {
     extended_engine_sel__mes_map_queues__legacy_engine_sel = 0,
     extended_engine_sel__mes_map_queues__sdma0_to_7_sel = 1 };

enum MES_MAP_QUEUES_queue_sel_enum {
     queue_sel__mes_map_queues__map_to_specified_queue_slots = 0,
     queue_sel__mes_map_queues__map_to_hws_determined_queue_slots = 1 };

enum MES_MAP_QUEUES_me_id_enum {
     me_id__mes_map_queues__ME1 = 0,
     me_id__mes_map_queues__ME3 = 2 };

enum MES_MAP_QUEUES_queue_type_enum {
     queue_type__mes_map_queues__normal_compute = 0,
     queue_type__mes_map_queues__debug_interface_queue = 1,
     queue_type__mes_map_queues__static_queue = 2 };

enum MES_MAP_QUEUES_static_queue_group_enum {
     static_queue_group__mes_map_queues__no_grouping = 0,
     static_queue_group__mes_map_queues__level_1_static_queue = 1,
     static_queue_group__mes_map_queues__level_2_static_queue = 2,
     static_queue_group__mes_map_queues__level_3_static_queue = 3 };

enum MES_MAP_QUEUES_engine_sel_enum {
     engine_sel__mes_map_queues__compute = 0,
     engine_sel__mes_map_queues__sdma_eng0 = 2,
     engine_sel__mes_map_queues__sdma_eng1 = 3,
     engine_sel__mes_map_queues__gfx = 4,
     engine_sel__mes_map_queues__mes = 5,
     engine_sel__mes_map_queues__sdma0 = 0,
     engine_sel__mes_map_queues__sdma1 = 1 };


typedef struct PM4_MES_MAP_QUEUES
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1:2;
            MES_MAP_QUEUES_extended_engine_sel_enum extended_engine_sel:2;
            MES_MAP_QUEUES_queue_sel_enum queue_sel:2;
            uint32_t reserved2:2;
            uint32_t vmid:4;
            uint32_t gws_enabled:1;
            uint32_t queue_id:3;
            uint32_t pipe_id:2;
            MES_MAP_QUEUES_me_id_enum me_id:2;
            uint32_t reserved3:1;
            MES_MAP_QUEUES_queue_type_enum queue_type:3;
            MES_MAP_QUEUES_static_queue_group_enum static_queue_group:2;
            MES_MAP_QUEUES_engine_sel_enum engine_sel:3;
            uint32_t num_queues:3;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved4:1;
            uint32_t check_disable:1;
            uint32_t doorbell_offset:26;
            uint32_t reserved5:4;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t mqd_addr_lo;

    uint32_t mqd_addr_hi;

    uint32_t wptr_addr_lo;

    uint32_t wptr_addr_hi;

} PM4MES_MAP_QUEUES, *PPM4MES_MAP_QUEUES;
#endif

//--------------------MES_NOP--------------------

#ifndef PM4_MES_NOP_DEFINED
#define PM4_MES_NOP_DEFINED

typedef struct PM4_MES_NOP
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

//  uint32_t data_block[];  // N-DWords

} PM4MES_NOP, *PPM4MES_NOP;
#endif

//--------------------MES_QUERY_STATUS--------------------

#ifndef PM4_MES_QUERY_STATUS_DEFINED
#define PM4_MES_QUERY_STATUS_DEFINED
enum MES_QUERY_STATUS_interrupt_sel_enum {
     interrupt_sel__mes_query_status__completion_status = 0,
     interrupt_sel__mes_query_status__process_status = 1,
     interrupt_sel__mes_query_status__queue_status = 2 };

enum MES_QUERY_STATUS_command_enum {
     command__mes_query_status__interrupt_only = 0,
     command__mes_query_status__fence_only_immediate = 1,
     command__mes_query_status__fence_only_after_write_ack = 2,
     command__mes_query_status__fence_wait_for_write_ack_send_interrupt = 3 };

enum MES_QUERY_STATUS_engine_sel_enum {
     engine_sel__mes_query_status__compute = 0,
     engine_sel__mes_query_status__gfx = 4 };


typedef struct PM4_MES_QUERY_STATUS
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t context_id:28;
            MES_QUERY_STATUS_interrupt_sel_enum interrupt_sel:2;
            MES_QUERY_STATUS_command_enum command:2;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t pasid:16;
            uint32_t reserved1:16;
        } bitfields3a;
        struct
        {
            uint32_t reserved2:2;
            uint32_t doorbell_offset:26;
            MES_QUERY_STATUS_engine_sel_enum engine_sel:3;
            uint32_t reserved3:1;
        } bitfields3b;
        uint32_t ordinal3;
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    uint32_t data_lo;

    uint32_t data_hi;

} PM4MES_QUERY_STATUS, *PPM4MES_QUERY_STATUS;
#endif

//--------------------MES_SET_RESOURCES--------------------

#ifndef PM4_MES_SET_RESOURCES_DEFINED
#define PM4_MES_SET_RESOURCES_DEFINED
enum MES_SET_RESOURCES_queue_type_enum {
     queue_type__mes_set_resources__kernel_interface_queue_kiq = 0,
     queue_type__mes_set_resources__hsa_interface_queue_hiq = 1,
     queue_type__mes_set_resources__hsa_debug_interface_queue = 4 };


typedef struct PM4_MES_SET_RESOURCES
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t vmid_mask:16;
            uint32_t unmap_latency:8;
            uint32_t reserved1:5;
            MES_SET_RESOURCES_queue_type_enum queue_type:3;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t queue_mask_lo;

    uint32_t queue_mask_hi;

    uint32_t gws_mask_lo;

    uint32_t gws_mask_hi;

    union
    {
        struct
        {
            uint32_t oac_mask:16;
            uint32_t reserved2:16;
        } bitfields7;
        uint32_t ordinal7;
    };

    uint32_t reserved3;

} PM4MES_SET_RESOURCES, *PPM4MES_SET_RESOURCES;
#endif

//--------------------MES_UNMAP_QUEUES--------------------

#ifndef PM4_MES_UNMAP_QUEUES_DEFINED
#define PM4_MES_UNMAP_QUEUES_DEFINED
enum MES_UNMAP_QUEUES_action_enum {
     action__mes_unmap_queues__preempt_queues = 0,
     action__mes_unmap_queues__reset_queues = 1,
     action__mes_unmap_queues__disable_process_queues = 2,
     action__mes_unmap_queues__preempt_queues_no_unmap = 3 };

enum MES_UNMAP_QUEUES_extended_engine_sel_enum {
     extended_engine_sel__mes_unmap_queues__legacy_engine_sel = 0,
     extended_engine_sel__mes_unmap_queues__sdma0_to_7_sel = 1 };

enum MES_UNMAP_QUEUES_queue_sel_enum {
     queue_sel__mes_unmap_queues__perform_request_on_specified_queues = 0,
     queue_sel__mes_unmap_queues__perform_request_on_pasid_queues = 1,
     queue_sel__mes_unmap_queues__unmap_all_queues = 2,
     queue_sel__mes_unmap_queues__unmap_all_non_static_queues = 3 };

enum MES_UNMAP_QUEUES_engine_sel_enum {
     engine_sel__mes_unmap_queues__compute = 0,
     engine_sel__mes_unmap_queues__sdma_eng0 = 2,
     engine_sel__mes_unmap_queues__sdma_eng1 = 3,
     engine_sel__mes_unmap_queues__gfx = 4,
     engine_sel__mes_unmap_queues__mes = 5,
     engine_sel__mes_unmap_queues__sdma0 = 0,
     engine_sel__mes_unmap_queues__sdma1 = 1,
     engine_sel__mes_unmap_queues__sdma2 = 2,
     engine_sel__mes_unmap_queues__sdma3 = 3,
     engine_sel__mes_unmap_queues__sdma4 = 4,
     engine_sel__mes_unmap_queues__sdma5 = 5,
     engine_sel__mes_unmap_queues__sdma6 = 6,
     engine_sel__mes_unmap_queues__sdma7 = 7 };


typedef struct PM4_MES_UNMAP_QUEUES
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            MES_UNMAP_QUEUES_action_enum action:2;
            MES_UNMAP_QUEUES_extended_engine_sel_enum extended_engine_sel:2;
            MES_UNMAP_QUEUES_queue_sel_enum queue_sel:2;
            uint32_t reserved1:20;
            MES_UNMAP_QUEUES_engine_sel_enum engine_sel:3;
            uint32_t num_queues:3;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t pasid:16;
            uint32_t reserved2:16;
        } bitfields3a;
        struct
        {
            uint32_t reserved3:2;
            uint32_t doorbell_offset0:26;
            uint32_t reserved4:4;
        } bitfields3b;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reserved5:2;
            uint32_t doorbell_offset1:26;
            uint32_t reserved6:4;
        } bitfields4a;
        struct
        {
            uint32_t reserved7:2;
            uint32_t tf_addr_lo32:30;
        } bitfields4b;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t reserved8:2;
            uint32_t doorbell_offset2:26;
            uint32_t reserved9:4;
        } bitfields5a;
        uint32_t tf_addr_hi32;

        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t reserved10:2;
            uint32_t doorbell_offset3:26;
            uint32_t reserved11:4;
        } bitfields6a;
        uint32_t tf_data;

        uint32_t ordinal6;
    };

} PM4MES_UNMAP_QUEUES, *PPM4MES_UNMAP_QUEUES;
#endif

//--------------------MES_WAIT_REG_MEM--------------------

#ifndef PM4_MES_WAIT_REG_MEM_DEFINED
#define PM4_MES_WAIT_REG_MEM_DEFINED
enum MES_WAIT_REG_MEM_function_enum {
     function__mes_wait_reg_mem__always_pass = 0,
     function__mes_wait_reg_mem__less_than_ref_value = 1,
     function__mes_wait_reg_mem__less_than_equal_to_the_ref_value = 2,
     function__mes_wait_reg_mem__equal_to_the_reference_value = 3,
     function__mes_wait_reg_mem__not_equal_reference_value = 4,
     function__mes_wait_reg_mem__greater_than_or_equal_reference_value = 5,
     function__mes_wait_reg_mem__greater_than_reference_value = 6 };

enum MES_WAIT_REG_MEM_mem_space_enum {
     mem_space__mes_wait_reg_mem__register_space = 0,
     mem_space__mes_wait_reg_mem__memory_space = 1 };

enum MES_WAIT_REG_MEM_operation_enum {
     operation__mes_wait_reg_mem__wait_reg_mem = 0,
     operation__mes_wait_reg_mem__wr_wait_wr_reg = 1 };


typedef struct PM4_MES_WAIT_REG_MEM
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            MES_WAIT_REG_MEM_function_enum function:3;
            uint32_t reserved1:1;
            MES_WAIT_REG_MEM_mem_space_enum mem_space:2;
            MES_WAIT_REG_MEM_operation_enum operation:2;
            uint32_t reserved2:14;
            uint32_t mes_intr_pipe:2;
            uint32_t mes_action:1;
            uint32_t reserved3:7;
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
            uint32_t reserved8:16;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4MES_WAIT_REG_MEM, *PPM4MES_WAIT_REG_MEM;
#endif

//--------------------MES_WRITE_DATA--------------------

#ifndef PM4_MES_WRITE_DATA_DEFINED
#define PM4_MES_WRITE_DATA_DEFINED
enum MES_WRITE_DATA_dst_sel_enum {
     dst_sel__mes_write_data__mem_mapped_register = 0,
     dst_sel__mes_write_data__tc_l2 = 2,
     dst_sel__mes_write_data__memory = 5 };

enum MES_WRITE_DATA_addr_incr_enum {
     addr_incr__mes_write_data__increment_address = 0,
     addr_incr__mes_write_data__do_not_increment_address = 1 };

enum MES_WRITE_DATA_wr_confirm_enum {
     wr_confirm__mes_write_data__do_not_wait_for_write_confirmation = 0,
     wr_confirm__mes_write_data__wait_for_write_confirmation = 1 };

enum MES_WRITE_DATA_temporal_enum {
     temporal__mes_write_data__rt = 0,
     temporal__mes_write_data__nt = 1,
     temporal__mes_write_data__ht = 2,
     temporal__mes_write_data__lu = 3 };


typedef struct PM4_MES_WRITE_DATA
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1:8;
            MES_WRITE_DATA_dst_sel_enum dst_sel:4;
            uint32_t reserved2:4;
            MES_WRITE_DATA_addr_incr_enum addr_incr:1;
            uint32_t reserved3:3;
            MES_WRITE_DATA_wr_confirm_enum wr_confirm:1;
            uint32_t reserved4:4;
            MES_WRITE_DATA_temporal_enum temporal:2;
            uint32_t reserved5:5;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        uint32_t dst_mmreg_addr_lo;

        struct
        {
            uint32_t reserved6:2;
            uint32_t dst_mem_addr_lo:30;
        } bitfields3b;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t dst_mmreg_addr_hi:8;
            uint32_t reserved7:24;
        } bitfields4a;
        uint32_t dst_mem_addr_hi;

        uint32_t ordinal4;
    };

//  uint32_t data[];  // N-DWords

} PM4MES_WRITE_DATA, *PPM4MES_WRITE_DATA;
#endif

#endif
