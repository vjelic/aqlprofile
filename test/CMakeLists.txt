cmake_minimum_required ( VERSION 3.5.0 )
set ( CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Verbose Output" FORCE )

set ( EXE_NAME "ctrl" )

if ( NOT DEFINED TEST_DIR )
  set ( TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
  set ( TEST_BINARY_DIR ${CMAKE_BINARY_DIR} )
  project ( ${EXE_NAME} )
  ## Set build environment
  include ( env )
endif ()


## Util sources
file( GLOB UTIL_SRC "${TEST_DIR}/util/*.cpp" )

## Test control sources
set ( CTRL_SRC
  ${TEST_DIR}/ctrl/test.cpp
  ${TEST_DIR}/ctrl/test_pmgr.cpp
  ${TEST_DIR}/ctrl/test_hsa.cpp
)

## Test kernels sources
set ( TEST_NAME simple_convolution )
set ( KERN_SRC ${TEST_DIR}/${TEST_NAME}/${TEST_NAME}.cpp )

## Building test executable
add_executable ( ${EXE_NAME} ${KERN_SRC} ${CTRL_SRC} ${UTIL_SRC} )
target_include_directories ( ${EXE_NAME} PRIVATE ${TEST_DIR} ${API_PATH} )
target_link_libraries( ${EXE_NAME} PRIVATE ${HSA_RUNTIME_LIB} ${HSA_KMT_LIB} c stdc++ dl pthread rt atomic )

## Deploying test files
execute_process ( COMMAND sh -xc "cp --remove-destination ${TEST_DIR}/${TEST_NAME}/*.hsaco ${TEST_BINARY_DIR}" )
execute_process ( COMMAND sh -xc "cp --remove-destination ${TEST_DIR}/run.sh ${TEST_BINARY_DIR}" )
execute_process ( COMMAND sh -xc "if [ ! -e run.sh ] ; then ln -s ${TEST_BINARY_DIR}/run.sh ; fi" )
