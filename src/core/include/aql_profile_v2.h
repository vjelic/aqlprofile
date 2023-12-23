#pragma once

#include <hsa/hsa.h>
#include <hsa/hsa_ven_amd_aqlprofile.h>

#define PUBLIC_API __attribute__((visibility("default")))

extern "C" {

typedef union {
    uint32_t raw;
    struct {
        uint32_t accum_lo_res : 1;
        uint32_t accum_hi_res : 1;
        uint32_t _reserved : 30;
    } sq_flags;
} aqlprofile_pmc_event_flags_t;

typedef union {
    uint32_t raw;
    struct {
        uint32_t agent_access : 1;
        uint32_t host_access  : 1;
        uint32_t _reserved    : 30;
    };
} aqlprofile_buffer_desc_flags_t;

typedef struct
{
    aqlprofile_pmc_event_flags_t flags;
    uint32_t block_index;
    uint32_t event_id;
    hsa_ven_amd_aqlprofile_block_name_t block_name;
} aqlprofile_pmc_event_t;

typedef struct
{
    void* ptr;
    uint64_t size;
    aqlprofile_buffer_desc_flags_t flags;
} aqlprofile_buffer_descriptor_t;

typedef struct
{
  hsa_agent_t agent;                             // GFXIP handle
  aqlprofile_buffer_descriptor_t output_buffer;  // Output buffer
  aqlprofile_buffer_descriptor_t command_buffer; // PM4 commands
  const aqlprofile_pmc_event_t* events;          // Events array
  uint32_t event_count;                          // Events count
} aqlprofile_pmc_profile_t;

typedef struct
{
  hsa_agent_t agent;                                     // GFXIP handle
  aqlprofile_buffer_descriptor_t output_buffer;          // Output buffer
  aqlprofile_buffer_descriptor_t command_buffer;         // PM4 commands
  const hsa_ven_amd_aqlprofile_parameter_t* parameters;  // Parameters array
  uint32_t parameter_count;                              // Parameters count
} aqlprofile_att_profile_t;

// Definition of output data iterator callback
typedef hsa_status_t (*aqlprofile_pmc_data_callback_t)(
    aqlprofile_pmc_event_t event,
    uint64_t counter_id,
    uint64_t counter_value,
    void* userdata
);

// Definition of output data iterator callback
typedef hsa_status_t (*aqlprofile_att_data_callback_t)(
    uint32_t shader,
    void* buffer,
    uint64_t size,
    void* callback_data
);

PUBLIC_API hsa_status_t aqlprofile_pmc_iterate_data(
    aqlprofile_pmc_profile_t profile,
    aqlprofile_pmc_data_callback_t callback,
    void* userdata
);

PUBLIC_API hsa_status_t aqlprofile_pmc_start(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_start_packet
);

PUBLIC_API hsa_status_t aqlprofile_pmc_stop(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_stop_packet
);

PUBLIC_API hsa_status_t aqlprofile_pmc_read(
    aqlprofile_pmc_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_read_packet
);

PUBLIC_API hsa_status_t aqlprofile_att_iterate_data(
    aqlprofile_att_profile_t profile,
    aqlprofile_att_data_callback_t callback,
    void* userdata
);

PUBLIC_API hsa_status_t aqlprofile_att_start(
    aqlprofile_att_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_start_packet
);

PUBLIC_API hsa_status_t aqlprofile_att_stop(
    aqlprofile_att_profile_t profile,
    hsa_ext_amd_aql_pm4_packet_t* aql_stop_packet
);

/**
 * @brief Callback for iteration of all possible event coordinate IDs and coordinate names.
 * @param [in] id Integer identifying the dimension.
 * @param [in] name Name of the dimension
 * @param [in] data User data supplied to @ref aqlprofile_iterate_event_ids
 * @return hsa_status_t
 * @retval HSA_STATUS_SUCCESS Continues iteration
 * @retval OTHERS Any other HSA return values stops iteration, passing back this value through
 *         @ref aqlprofile_iterate_event_ids
 */
typedef hsa_status_t (*aqlprofile_eventname_callback_t)(int id, const char* name, void* data);

/**
 * @brief Iterate over all possible event coordinate IDs and their names.
 * @param [in] callback Callback to use for iteration of dimensions
 * @param [in] user_data Data to supply to callback @ref aqlprofile_eventname_callback_t
 * @return hsa_status_t
 * @retval HSA_STATUS_SUCCESS if successful
 * @retval HSA_STATUS_ERROR if error on interation
 * @retval OTHERS If @ref aqlprofile_eventname_callback_t returns non-HSA_STATUS_SUCCESS, 
 *         that value is returned. 
 */
PUBLIC_API hsa_status_t aqlprofile_iterate_event_ids(
    aqlprofile_eventname_callback_t callback,
    void* user_data
);

/**
 * @brief Iterate over all event coordinates for a given agent_t and event_t.
 * @param position A counting sequence indicating callback number.
 * @param id Coordinate ID as in _iterate_event_ids.
 * @param extent Coordinate extent indicating maximum allowed instances.
 * @param coordinate The coordinate, in the range [0,extent-1].
 * @param name Coordinate name as in _iterate_event_ids.
 * @param userdata Userdata returned from _iterate_event_coord function.
*/
typedef hsa_status_t(*aqlprofile_coordinate_callback_t)(
  int position,
  int id,
  int extent,
  int coordinate,
  const char* name,
  void* userdata
);

/**
 * @brief Iterate over all event coordinates for a given agent_t and event_t.
 * @param[in] agent HSA agent.
 * @param[in] event The event ID and block ID to iterate for.
 * @param[in] sample_id aqlprofile_info_data_t.sample_id returned from _aqlprofile_iterate_data.
 * @param[in] callback Callback function to return the coordinates.
 * @param[in] userdata Arbitrary data pointer to be sent back to the user via callback.
*/
hsa_status_t aqlprofile_iterate_event_coord(
  hsa_agent_t agent,
  aqlprofile_pmc_event_t event,
  uint64_t sample_id,
  aqlprofile_coordinate_callback_t callback,
  void* userdata
);

typedef union
{
    uint64_t raw;
    struct {
        uint64_t isValid : 1;
        uint64_t isNavi : 1;
        uint64_t npiWaveData : 1;
        uint64_t version : 13;
    };
} att_output_flags_t;

typedef struct
{
    int64_t time;
    uint16_t events0;
    uint16_t events1;
    uint16_t events2;
    uint16_t events3;
    uint8_t CU;
    uint8_t bank;
} att_perfevent_t;

typedef struct
{
    uint64_t kernel_id : 12;
    uint64_t simd : 2;
    uint64_t slot : 4;
    uint64_t enable : 1;
    uint64_t cu : 4;
    uint64_t time : 41; // Time_value/8
} att_occupancy_info_t;

typedef struct
{
    int32_t type;
    int32_t duration;
} wave_state_t;

typedef struct
{
    int64_t time;
    int64_t duration;
} wave_instruction_t;

enum WAVESLOT_STATE
{
    WS_EMPTY = 0,
    WS_IDLE = 1,
    WS_EXEC = 2,
    WS_WAIT = 3,
    WS_STALL = 4,
    WS_UNKNOWN = 5,
};

enum WaveInstCategory
{
    NONE = 0,
    SMEM = 1,
    SALU = 2,
    VMEM = 3,
    FLAT = 4,
    LDS = 5,
    VALU = 6,
    JUMP = 7,
    NEXT = 8,
    IMMED = 9,
    TRAP = 10,
    PCINFO = 15,
    WAVE_NOT_FINISHED,
};

enum WaveTrapStatus
{
    TRAP_RESTORED = 0,
    TRAP_REQUEST = 1,
    TRAP_SAVED = 1,
    TRAP_STANDBY = 2
};

typedef struct {
    WaveInstCategory inst;
    uint32_t hitcount;
    uint64_t latency;
    uint64_t pc;
} att_trace_event_t;

struct wave_data_t
{
    uint8_t simd;
    uint8_t wave_id;
    uint8_t trap_status;
    uint8_t reserved;

    // VMEM Pipeline: instrs and stalls
    uint32_t num_vmem_instrs = 0;
    uint32_t num_vmem_stalls = 0;
    // FLAT instrs and stalls
    uint32_t num_flat_instrs = 0;
    uint32_t num_flat_stalls = 0;

    // LDS instr and stalls
    uint32_t num_lds_instrs = 0;
    uint32_t num_lds_stalls = 0;

    // SCA instrs stalls
    uint32_t num_salu_instrs = 0;
    uint32_t num_smem_instrs = 0;
    uint32_t num_salu_stalls = 0;
    uint32_t num_smem_stalls = 0;

    // Branch
    uint32_t num_branch_instrs = 0;
    uint32_t num_branch_taken_instrs = 0;
    uint32_t num_branch_stalls = 0;

    // total VMEM/FLAT/LDS/SMEM instructions issued
    uint32_t num_mem_instrs = 0;     // total issued memory instructions
    uint32_t num_valu_stalls = 0;
    uint64_t num_valu_instrs = 0;
    uint64_t num_issued_instrs = 0;  // total issued instructions (compute + memory)

    int64_t begin_time = 0;  // Begin and end cycle
    int64_t end_time = 0;
    int64_t traceID = -1;

    uint64_t timeline_size = 0;
    uint64_t instructions_size = 0;
    wave_state_t* timeline_array;
    wave_instruction_t* instructions_array;
};

/**
 * @brief Callback for iteration of all possible event coordinate IDs and coordinate names.
 * @param [in] id Integer identifying type ID.
 * @param [in] name Name of the trace type.
 * @param [in] userdata User data supplied to back caller
 * @return hsa_status_t
 * @retval HSA_STATUS_SUCCESS Continues iteration
 * @retval OTHERS Any other HSA return values stops iteration, passing back this value through
 *         @ref aqlprofile_iterate_trace_type_ids
 */
typedef hsa_status_t (*aqlprofile_att_tracename_callback_t)(int id, const char* name, void* data);

/**
 * @brief Iterate over all possible event coordinate IDs and their names.
 * @param [in] callback Callback to use for iteration of trace types
 * @param [in] userdata Data to supply to callback @ref aqlprofile_tracename_callback_t
 * @return hsa_status_t
 * @retval HSA_STATUS_SUCCESS if successful
 * @retval HSA_STATUS_ERROR if error on interation
 * @retval OTHERS If @ref aqlprofile_eventname_callback_t returns non-HSA_STATUS_SUCCESS, 
 *         that value is returned. 
 */
PUBLIC_API hsa_status_t aqlprofile_att_iterate_trace_type_ids(
    aqlprofile_att_tracename_callback_t callback,
    void* userdata
);

/**
 * @brief Callback for rocprofiler to return the largest instruction length and source reference.
 * These values will be used as preallocation for aqlprofile_att_isa_string_callback_t.
 * @param[in] marker_id The ID of generated ATT marker for given symbol.
 * @param[in] userdata Arbitrary data pointer to be sent back to the user via callback.
 * @param[out] isa_length Minimum necessary space to copy the ISA to.
 * @param[out] source_length Minimum necessary space to copy the source reference to.
*/
typedef hsa_status_t(*aqlprofile_att_isa_length_callback_t)(
    uint64_t marker_id,
    void* userdata,
    uint64_t* isa_length,
    uint64_t* source_length
);

/**
 * @brief Callback for rocprofiler to return ISA to aqlprofile ATT parser.
 * The caller must copy a desired instruction on symbol_name and source_reference,
 * while obeying the max length returned by aqlprofile_att_isa_length_callback_t
 * @param[in] marker_id The ID of generated ATT marker for given codeobject ID.
 * @param[in] offset  The offset from base virtual address for given marker_id.
 *                    If marker_id == 0, this parameter is raw virtual address.
 * @param[in] userdata Arbitrary data pointer to be sent back to the user via callback.
 * @param[out] isa_memory_size (Auto) The number of bytes to next instruction. 0 for custom ISA.
 * @param[out] isa_instruction The char* name where to copy the ISA line to.
 * @param[out] isa_size Size of returned ISA string.
 * @param[out] source_reference Reference to source line and/or additional comments in the binary.
 * @param[out] source_size Size of returned reference string.
*/
typedef hsa_status_t(*aqlprofile_att_isa_string_callback_t)(
    uint32_t marker_id,
    uint64_t offset,
    void* userdata,
    uint64_t* isa_memory_size,
    char* isa_instruction,
    uint64_t* isa_size,
    char* source_reference,
    uint64_t* source_size
);

/**
 * @brief Callback for rocprofiler to return ISA to aqlprofile ATT parser.
 * The caller must copy a desired instruction on symbol_name and source_reference,
 * while obeying the max length returned by aqlprofile_att_isa_length_callback_t
 * @param[in] trace_type_id The type of this trace as in _iterate_event_ids().
 * @param[in] correlation_id The ID of shader engine or trace callback number.
 * @param[in] trace_events A pointer to sequence of events, of size trace_size.
 * @param[in] trace_size The number of events in the trace.
 * @param[in] userdata Arbitrary data pointer to be sent back to the user via callback.
*/
typedef hsa_status_t(*aqlprofile_att_trace_callback_t)(
    int trace_type_id,
    int correlation_id,
    void* trace_events,
    uint64_t trace_size,
    void* userdata
);

/**
 * @brief Callback for the ATT parser to retrieve Shader Engine data.
 * Returns the amount of data filled. If no more data is available, then callback return 0
 * If the space available in the buffer is less than required for parsing the full data,
 * the full data is transfered over multiple calls.
 * When all data has been transfered from current shader_engine_id, the caller has the option to
 *  1) Return -1 on shader_engine ID and parsing terminates
 *  2) Move to the next shader engine.
 * @param[out] shader_engine_id The ID of given shader engine.
 * @param[out] buffer The buffer to fill up with SE data.
 * @param[in] buffer_size The space available in the buffer.
 * @param[in] userdata Arbitrary data pointer to be sent back to the user via callback.
 * @returns Number of bytes filled.
 * @retval 0 if no more SE data is available. Parsing will stop.
 * @retval buffer_size if the buffer does not hold enough data for the current shader engine.
 * @retval 0 > ret > buffer_size for partially filled buffer, and caller moves over to next SE.
*/
typedef uint64_t(*aqlprofile_att_se_data_callback_t)(
    int* shader_engine_id,
    uint8_t* buffer,
    uint64_t buffer_size,
    void* userdata
);

/**
 * @brief Iterate over all available event types.
 * @param[in] trace_event_id ID of the event.
 * @param[in] trace_event_name Event name.
*/
hsa_status_t aqlprofile_att_parser_iterate_event_list(
    int trace_event_id,
    const char* trace_event_name,
    void* userdata
);

/**
 * @brief Iterate over all event coordinates for a given agent_t and event_t.
 * @param[in] se_data_callback Callback to return shader engine data from.
 * @param[in] trace_callback Callback where the trace data is returned to.
 * Each trace will be marked by the ID returned on aqlprofile_att_parser_iterate_event_list
 * @param[in] symbol_length_callback Callback to return ISA lengths.
 * @param[in] symbol_name_callback Callback to return ISA lines.
 * @param[in] userdata Userdata passed back to caller via callback.
*/
hsa_status_t aqlprofile_att_parse_data(
    aqlprofile_att_se_data_callback_t se_data_callback,
    aqlprofile_att_trace_callback_t trace_callback,
    aqlprofile_att_isa_length_callback_t isa_length_callback,
    aqlprofile_att_isa_string_callback_t isa_string_callback,
    void* userdata
);

}
