#pragma once

/**
* @file      ttviewer_user_data_format.hpp
* @brief     user data interface between thread trace generators and thread trace viewer
* @copyright 2017 Advanced Micro Devices Inc
* this file defines an interface used to pass UMD and tools user data from a thread trace generator tool to a thread trace viewer
* the register SQ_THREAD_TRACE_USER_DATA_2 is exclusively used to pass the data
* the register SQ_THREAD_TRACE_USER_DATA_2 is exclusively used to pass the data
*/
#define TT_VIEWER_USER_DATA_FORMAT_MAJOR_VERSION 2
#define TT_VIEWER_USER_DATA_FORMAT_MINOR_VERSION 2

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

/**
* @brief version header data
* a version number written after the fourcc
* the version number is expected to change whenever this interface changes
* the minor version should be incremented whenever there is a change that does not alter data used by existing viewers
* the major version must be incremented when the change alters data used by existing viewers
* the minor version should reset to zero when the major version is incremented
* the viewer should check the version to ensure the generator is producing compatible data
* in particular the viewer should not use the data if it does not recognize the major version
*/
union thread_trace_viewer_user_data_header_version
{
  struct
  {
    unsigned int opcode :  8; //!< thread_trace_viewer_user_data_opcode_version
    unsigned int major  : 10; //!< TT_VIEWER_USER_DATA_FORMAT_MAJOR_VERSION
    unsigned int minor  : 14; //!< TT_VIEWER_USER_DATA_FORMAT_MINOR_VERSION
  };
  unsigned int u32All;
};

typedef enum {
  ATT_MARKER_HEADER_CHANNEL = 0,
  ATT_MARKER_SIZE_LO_CHANNEL = 1,
  ATT_MARKER_ADDR_LO_CHANNEL = 2,
  ATT_MARKER_ADDR_HI_CHANNEL = 3,
  ATT_MARKER_SIZE_HI_CHANNEL = 4,
  ATT_MARKER_ID_LO_CHANNEL = 5,
  ATT_MARKER_ID_HI_CHANNEL = 6,
  ATT_MARKER_WAIT_FOR_HEADER = 32
} MarkerState;
