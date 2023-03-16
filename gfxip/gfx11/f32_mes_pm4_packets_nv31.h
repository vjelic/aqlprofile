//
//  (c) 2014-2021 Advanced Micro Devices, Inc.  All rights reserved.
//  THIS SOURCE FILE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
//  OR IMPLIED WARRANTIES . . .
//

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

//--------------------MES_MAP_PROCESS--------------------

#ifndef PM4_MES_MAP_PROCESS_DEFINED
#define PM4_MES_MAP_PROCESS_DEFINED

typedef struct PM4_MES_MAP_PROCESS
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
            uint32_t pasid:16;
            uint32_t reserved1:2;
            uint32_t debug_vmid:4;
            uint32_t debug_flag:1;
            uint32_t tmz:1;
            uint32_t diq_enable:1;
            uint32_t process_quantum:7;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t vm_context_page_table_base_addr_lo32;

    uint32_t vm_context_page_table_base_addr_hi32;

    uint32_t sh_mem_bases;

    uint32_t sh_mem_config;

    uint32_t sq_shader_tba_lo;

    uint32_t sq_shader_tba_hi;

    uint32_t sq_shader_tma_lo;

    uint32_t sq_shader_tma_hi;

    uint32_t reserved2;

    uint32_t gds_addr_lo;

    uint32_t gds_addr_hi;

    union
    {
        struct
        {
            uint32_t num_gws:6;
            uint32_t reserved3:1;
            uint32_t sdma_enable:1;
            uint32_t num_oac:4;
            uint32_t reserved4:4;
            uint32_t gds_size:6;
            uint32_t num_queues:10;
        } bitfields14;
        uint32_t ordinal14;
    };

    uint32_t completion_signal_lo32;

    uint32_t completion_signal_hi32;

} PM4MES_MAP_PROCESS, *PPM4MES_MAP_PROCESS;
#endif

//--------------------MES_MAP_PROCESS_VM--------------------

#ifndef PM4_MES_MAP_PROCESS_VM_DEFINED
#define PM4_MES_MAP_PROCESS_VM_DEFINED

typedef struct PM4_MES_MAP_PROCESS_VM
{
    union
    {
        PM4_MES_TYPE_3_HEADER   header;            ///header
        uint32_t            ordinal1; 
    };

    uint32_t reserved1;

    uint32_t vm_context_cntl;

    uint32_t reserved2;

    uint32_t vm_context_page_table_end_addr_lo32;

    uint32_t vm_context_page_table_end_addr_hi32;

    uint32_t vm_context_page_table_start_addr_lo32;

    uint32_t vm_context_page_table_start_addr_hi32;

    uint32_t reserved3;

    uint32_t reserved4;

    uint32_t reserved5;

    uint32_t reserved6;

    uint32_t reserved7;

    uint32_t reserved8;

    uint32_t completion_signal_lo32;

    uint32_t completion_signal_hi32;

} PM4MES_MAP_PROCESS_VM, *PPM4MES_MAP_PROCESS_VM;
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
     me_id__mes_map_queues__ME2 = 1,
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
     engine_sel__mes_map_queues__sdma1 = 1,
     engine_sel__mes_map_queues__sdma2 = 2,
     engine_sel__mes_map_queues__sdma3 = 3,
     engine_sel__mes_map_queues__sdma4 = 4,
     engine_sel__mes_map_queues__sdma5 = 5,
     engine_sel__mes_map_queues__sdma6 = 6,
     engine_sel__mes_map_queues__sdma7 = 7 };


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

//--------------------MES_RUN_LIST--------------------

#ifndef PM4_MES_RUN_LIST_DEFINED
#define PM4_MES_RUN_LIST_DEFINED

typedef struct PM4_MES_RUN_LIST
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
            uint32_t process_cnt:4;
            uint32_t reserved3:4;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t level_1_static_queue_cnt:4;
            uint32_t level_2_static_queue_cnt:4;
            uint32_t level_3_static_queue_cnt:4;
            uint32_t reserved4:20;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4MES_RUN_LIST, *PPM4MES_RUN_LIST;
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

    union
    {
        struct
        {
            uint32_t gds_heap_base:6;
            uint32_t reserved3:5;
            uint32_t gds_heap_size:6;
            uint32_t reserved4:15;
        } bitfields8;
        uint32_t ordinal8;
    };

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

#endif
