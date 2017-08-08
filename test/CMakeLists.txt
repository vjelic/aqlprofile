cmake_minimum_required ( VERSION 3.5.0 )
set ( CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Verbose Output" FORCE )

set ( EXE_NAME "ctrl" )

if ( NOT DEFINED TEST_DIR )
  set ( TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
  project ( ${EXE_NAME} )
  ## Set build environment
  include ( env )
endif ()

## Util sources
file( GLOB UTIL_SRC "${TEST_DIR}/util/*.cpp" )
include_directories ( ${TEST_DIR}/util )

## Test control sources
set ( CTRL_SRC
  ${TEST_DIR}/ctrl/test.cpp
  ${TEST_DIR}/ctrl/test_pmgr.cpp
  ${TEST_DIR}/ctrl/test_hsa.cpp
)
include_directories ( ${TEST_DIR}/ctrl )

## Test kernels sources
set ( TEST_NAME simple_convolution )
include_directories ( ${TEST_DIR}/${TEST_NAME} )
set ( KERN_SRC ${TEST_DIR}/${TEST_NAME}/${TEST_NAME}.cpp )
execute_process ( COMMAND sh -xc "cp ${TEST_DIR}/${TEST_NAME}/*.hsaco ${PROJECT_BINARY_DIR}" )

## Building test executable
include_directories ( ${API_PATH} )
LINK_DIRECTORIES ( ${HSA_RUNTIME_LIB_PATH} )
add_executable ( ${EXE_NAME} ${KERN_SRC} ${CTRL_SRC} ${UTIL_SRC} )
target_link_libraries( ${EXE_NAME} ${HSA_RUNTIME_LIB} c stdc++ dl pthread rt atomic )
execute_process ( COMMAND sh -xc "cp ${TEST_DIR}/run.sh ${PROJECT_BINARY_DIR}" )
