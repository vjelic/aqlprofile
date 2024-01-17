#pragma once

union ttv_user_data_header_codeobj
{
  struct
  {
    unsigned int opcode   :  8;  //!< One of the opcode values in thread_trace_viewer_user_data_opcode
    unsigned int type     :  4;  //!< One of att_userdata_channels
    unsigned int reserved : 20;  //!< Reserved. Must be zero.
  };
  unsigned int u32All;
};

/**
* @brief user data opcode as defined by the thread trace viewer. Imported for compatibility.
* each data passed through SQ_THREAD_TRACE_USER_DATA_2 is preceded by a header
* the header first 8 bits represent an opcode identifying the data (or operation)
*/
enum thread_trace_viewer_user_data_opcode
{
    thread_trace_viewer_user_data_opcode_fourcc = 0,    //!< The first written user data register is the fourcc \0TTV
    thread_trace_viewer_user_data_opcode_version,       //!< The second written user data register is a version number
    thread_trace_viewer_user_data_opcode_shader_crc,    //!< Shader CRCs
    thread_trace_viewer_user_data_opcode_api_function,  //!< API functions
    thread_trace_viewer_user_data_opcode_codeobj,       //!< Rocprofv2/v3 Codeobj Load/Unload Data Marker
};

/**
* @brief fourcc header data as defined by the thread trace viewer. Imported for compatibility.
* .out files only contain thread trace data
* the fourcc should be used to identify the type of data available in SQ_THREAD_TRACE_USER_DATA_2
* fourcc should be the first SQ_THREAD_TRACE_USER_DATA_2 in each command buffer
*/
union thread_trace_viewer_user_data_header_fourcc
{
  struct
  {
    unsigned int opcode : 8; //!< FourCC 1st char: '\0' thread_trace_viewer_user_data_opcode_fourcc
    unsigned int char2  : 8; //!< FourCC 2nd char: 'R'
    unsigned int char3  : 8; //!< FourCC 3nd char: 'O'
    unsigned int char4  : 8; //!< FourCC 4th char: 'C'
  };
  unsigned int u32All;
};
