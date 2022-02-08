//
//  (c) 2014-2020 Advanced Micro Devices, Inc.  All rights reserved.
//  THIS SOURCE FILE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS
//  OR IMPLIED WARRANTIES . . .
//

#ifndef F32_MEC_AQL_PACKETS_H
#define F32_MEC_AQL_PACKETS_H



//--------------------MEC_INVALID--------------------

#ifndef AQL_MEC_INVALID_DEFINED
#define AQL_MEC_INVALID_DEFINED
enum MEC_INVALID_format_enum {
     format__mec_invalid__invalid = 1 };


typedef struct AQL_MEC_INVALID
{
    union
    {
        struct
        {
            MEC_INVALID_format_enum format:8;
            uint32_t reserved1:24;
        } bitfields1;
        uint32_t ordinal1;
    };

    uint32_t reserved2;

    uint64_t reserved3;

    uint64_t reserved4;

    uint64_t reserved5;

    uint64_t reserved6;

    uint64_t reserved7;

    uint64_t reserved8;

    uint64_t reserved9;

} AQLMEC_INVALID, *PAQLMEC_INVALID;
#endif

//--------------------MEC_KERNEL_DISPATCH--------------------

#ifndef AQL_MEC_KERNEL_DISPATCH_DEFINED
#define AQL_MEC_KERNEL_DISPATCH_DEFINED
enum MEC_KERNEL_DISPATCH_format_enum {
     format__mec_kernel_dispatch__kernel_dispatch = 2 };

enum MEC_KERNEL_DISPATCH_acquire_fence_scope_enum {
     acquire_fence_scope__mec_kernel_dispatch__no_fence = 0,
     acquire_fence_scope__mec_kernel_dispatch__agent_scope = 1,
     acquire_fence_scope__mec_kernel_dispatch__agent_and_system_scope = 2 };

enum MEC_KERNEL_DISPATCH_release_fence_scope_enum {
     release_fence_scope__mec_kernel_dispatch__no_fence = 0,
     release_fence_scope__mec_kernel_dispatch__agent_scope = 1,
     release_fence_scope__mec_kernel_dispatch__agent_and_system_scope = 2 };


typedef struct AQL_MEC_KERNEL_DISPATCH
{
    union
    {
        struct
        {
            MEC_KERNEL_DISPATCH_format_enum format:8;
            uint32_t barrier:1;
            MEC_KERNEL_DISPATCH_acquire_fence_scope_enum acquire_fence_scope:2;
            MEC_KERNEL_DISPATCH_release_fence_scope_enum release_fence_scope:2;
            uint32_t reserved1:3;
            uint32_t dimensions:2;
            uint32_t reserved2:14;
        } bitfields1;
        uint32_t ordinal1;
    };

    union
    {
        struct
        {
            uint32_t workgroup_size_x:16;
            uint32_t workgroup_size_y:16;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t workgroup_size_z:16;
            uint32_t reserved3:16;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t grid_size_x;

    uint32_t grid_size_y;

    uint32_t grid_size_z;

    uint32_t private_segment_size_bytes;

    uint32_t group_segment_size_bytes;

    uint64_t kernel_object_address;

    uint64_t kernarg_address;

    uint64_t reserved4;

    uint64_t completion_signal;

} AQLMEC_KERNEL_DISPATCH, *PAQLMEC_KERNEL_DISPATCH;
#endif

//--------------------MEC_BARRIER_AND--------------------

#ifndef AQL_MEC_BARRIER_AND_DEFINED
#define AQL_MEC_BARRIER_AND_DEFINED
enum MEC_BARRIER_AND_format_enum {
     format__mec_barrier_and__barrier_and = 3 };

enum MEC_BARRIER_AND_acquire_fence_scope_enum {
     acquire_fence_scope__mec_barrier_and__no_fence = 0 };

enum MEC_BARRIER_AND_release_fence_scope_enum {
     release_fence_scope__mec_barrier_and__no_fence = 0 };


typedef struct AQL_MEC_BARRIER_AND
{
    union
    {
        struct
        {
            MEC_BARRIER_AND_format_enum format:8;
            uint32_t barrier:1;
            MEC_BARRIER_AND_acquire_fence_scope_enum acquire_fence_scope:2;
            MEC_BARRIER_AND_release_fence_scope_enum release_fence_scope:2;
            uint32_t reserved1:19;
        } bitfields1;
        uint32_t ordinal1;
    };

    uint32_t reserved2;

    uint64_t barrier_field0;

    uint64_t barrier_field1;

    uint64_t barrier_field2;

    uint64_t barrier_field3;

    uint64_t barrier_field4;

    uint64_t reserved3;

    uint64_t completion_signal;

} AQLMEC_BARRIER_AND, *PAQLMEC_BARRIER_AND;
#endif

//--------------------MEC_BARRIER_OR--------------------

#ifndef AQL_MEC_BARRIER_OR_DEFINED
#define AQL_MEC_BARRIER_OR_DEFINED
enum MEC_BARRIER_OR_format_enum {
     format__mec_barrier_or__barrier_or = 5 };

enum MEC_BARRIER_OR_acquire_fence_scope_enum {
     acquire_fence_scope__mec_barrier_or__no_fence = 0 };

enum MEC_BARRIER_OR_release_fence_scope_enum {
     release_fence_scope__mec_barrier_or__no_fence = 0 };


typedef struct AQL_MEC_BARRIER_OR
{
    union
    {
        struct
        {
            MEC_BARRIER_OR_format_enum format:8;
            uint32_t barrier:1;
            MEC_BARRIER_OR_acquire_fence_scope_enum acquire_fence_scope:2;
            MEC_BARRIER_OR_release_fence_scope_enum release_fence_scope:2;
            uint32_t reserved1:19;
        } bitfields1;
        uint32_t ordinal1;
    };

    uint32_t reserved2;

    uint64_t barrier_field0;

    uint64_t barrier_field1;

    uint64_t barrier_field2;

    uint64_t barrier_field3;

    uint64_t barrier_field4;

    uint64_t reserved3;

    uint64_t completion_signal;

} AQLMEC_BARRIER_OR, *PAQLMEC_BARRIER_OR;
#endif

//--------------------MEC_BARRIER_VALUE--------------------

#ifndef AQL_MEC_BARRIER_VALUE_DEFINED
#define AQL_MEC_BARRIER_VALUE_DEFINED
enum MEC_BARRIER_VALUE_format_enum {
     format__mec_barrier_value__vendor_specific = 0 };

enum MEC_BARRIER_VALUE_acquire_fence_scope_enum {
     acquire_fence_scope__mec_barrier_value__no_fence = 0,
     acquire_fence_scope__mec_barrier_value__agent_scope = 1,
     acquire_fence_scope__mec_barrier_value__agent_and_system_scope = 2 };

enum MEC_BARRIER_VALUE_release_fence_scope_enum {
     release_fence_scope__mec_barrier_value__no_fence = 0,
     release_fence_scope__mec_barrier_value__agent_scope = 1,
     release_fence_scope__mec_barrier_value__agent_and_system_scope = 2 };

enum MEC_BARRIER_VALUE_amd_format_enum {
     amd_format__mec_barrier_value__barrier_value = 2 };

enum MEC_BARRIER_VALUE_cond_enum {
     cond__mec_barrier_value__equal = 0,
     cond__mec_barrier_value__not_equal = 1,
     cond__mec_barrier_value__less_than = 2,
     cond__mec_barrier_value__greater_than_or_equal = 3 };


typedef struct AQL_MEC_BARRIER_VALUE
{
    union
    {
        struct
        {
            MEC_BARRIER_VALUE_format_enum format:8;
            uint32_t barrier:1;
            MEC_BARRIER_VALUE_acquire_fence_scope_enum acquire_fence_scope:2;
            MEC_BARRIER_VALUE_release_fence_scope_enum release_fence_scope:2;
            uint32_t reserved1:3;
            MEC_BARRIER_VALUE_amd_format_enum amd_format:8;
            uint32_t reserved2:8;
        } bitfields1;
        uint32_t ordinal1;
    };

    uint32_t reserved3;

    uint64_t dep_signal;

    uint64_t wait_value;

    uint64_t mask;

    union
    {
        struct
        {
            MEC_BARRIER_VALUE_cond_enum cond:3;
            uint32_t reserved4:29;
        } bitfields9;
        uint32_t ordinal9;
    };

    uint32_t reserved5;

    uint64_t reserved6;

    uint64_t reserved7;

    uint64_t completion_signal;

} AQLMEC_BARRIER_VALUE, *PAQLMEC_BARRIER_VALUE;
#endif

//--------------------MEC_ESACAPE_TO_IB--------------------

#ifndef AQL_MEC_ESACAPE_TO_IB_DEFINED
#define AQL_MEC_ESACAPE_TO_IB_DEFINED
enum MEC_ESACAPE_TO_IB_format_enum {
     format__mec_esacape_to_ib__vendor_specific = 0 };

enum MEC_ESACAPE_TO_IB_acquire_fence_scope_enum {
     acquire_fence_scope__mec_esacape_to_ib__no_fence = 0,
     acquire_fence_scope__mec_esacape_to_ib__agent_scope = 1,
     acquire_fence_scope__mec_esacape_to_ib__agent_and_system_scope = 2 };

enum MEC_ESACAPE_TO_IB_release_fence_scope_enum {
     release_fence_scope__mec_esacape_to_ib__no_fence = 0,
     release_fence_scope__mec_esacape_to_ib__agent_scope = 1,
     release_fence_scope__mec_esacape_to_ib__agent_and_system_scope = 2 };

enum MEC_ESACAPE_TO_IB_amd_format_enum {
     amd_format__mec_esacape_to_ib__escape_to_ib = 1 };

enum MEC_ESACAPE_TO_IB_remaining_dws_enum {
     remaining_dws__mec_esacape_to_ib__0xa = 10 };


typedef struct AQL_MEC_ESACAPE_TO_IB
{
    union
    {
        struct
        {
            MEC_ESACAPE_TO_IB_format_enum format:8;
            uint32_t barrier:1;
            MEC_ESACAPE_TO_IB_acquire_fence_scope_enum acquire_fence_scope:2;
            MEC_ESACAPE_TO_IB_release_fence_scope_enum release_fence_scope:2;
            uint32_t reserved1:3;
            MEC_ESACAPE_TO_IB_amd_format_enum amd_format:8;
            uint32_t reserved2:8;
        } bitfields1;
        uint32_t ordinal1;
    };

    uint32_t ib_packet_hdr;

    uint32_t ib_packet_dw2;

    uint32_t ib_packet_dw3;

    uint32_t ib_packet_dw4;

    union
    {
        struct
        {
            MEC_ESACAPE_TO_IB_remaining_dws_enum remaining_dws:4;
            uint32_t reserved3:28;
        } bitfields6;
        uint32_t ordinal6;
    };

    uint64_t reserved4;

    uint64_t reserved5;

    uint64_t reserved6;

    uint64_t reserved7;

    uint64_t completion_signal;

} AQLMEC_ESACAPE_TO_IB, *PAQLMEC_ESACAPE_TO_IB;
#endif

#endif
