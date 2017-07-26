#
# Build is not supported on Windows plaform
#
if ( WIN32 )
  message ( FATAL_ERROR "Windows build is not supported." )
endif ()

#
# Compiler Preprocessor definitions.
#
add_definitions ( -D__linux__ )
add_definitions ( -DUNIX_OS )
add_definitions ( -DLINUX )
add_definitions ( -D__AMD64__ )
add_definitions ( -D__x86_64__ )
add_definitions ( -DAMD_INTERNAL_BUILD )
add_definitions ( -DLITTLEENDIAN_CPU=1 )
add_definitions ( -DHSA_LARGE_MODEL= )
add_definitions ( -DHSA_DEPRECATED= )

#
# Linux Compiler options
#
set ( CMAKE_CXX_FLAGS "-std=c++11")
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=sign-compare" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=enum-compare" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=comment " )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=pointer-arith" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pointer-arith" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-math-errno" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmerge-all-constants" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
# CLANG options
if ( "$ENV{CXX}" STREQUAL "/usr/bin/clang++" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=1000000" )
endif()

#
# Check env vars
#
if ( DEFINED ENV{CMAKE_BUILD_TYPE} )
  set ( CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE} )
endif()
if ( DEFINED ENV{CMAKE_PREFIX_PATH} )
  set ( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )
endif()

#
# Extend Compiler flags based on build type
#
string ( TOLOWER "_${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE )
if ( ${CMAKE_BUILD_TYPE} STREQUAL _debug )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb" )
  set ( CMAKE_BUILD_TYPE "debug" )
else ()
  set ( CMAKE_BUILD_TYPE "release" )
endif ()

#
# Extend Compiler flags based on Processor architecture
#
if ( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64" )
  set ( NBIT 64 )
  set ( NBITSTR "64" )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64  -msse -msse2" )
elseif ( ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86" )
  set ( NBIT 32 )
  set ( NBITSTR "" )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" )
endif ()

#
# Find hsa-runtime headers/lib
#
find_file ( HSA_RUNTIME_INC hsa.h )
find_file ( HSA_RUNTIME_LIB libhsa-runtime64.so )
get_filename_component ( HSA_RUNTIME_INC_PATH ${HSA_RUNTIME_INC} DIRECTORY )
get_filename_component ( HSA_RUNTIME_LIB_PATH ${HSA_RUNTIME_LIB} DIRECTORY )
set ( API_PATH ${HSA_RUNTIME_INC_PATH} )

#
# Basic Tool Chain Information
#
message ( "----------------NBIT: " ${NBIT} )
message ( "-----------BuildType: " ${CMAKE_BUILD_TYPE} )
message ( "------------Compiler: " ${CMAKE_CXX_COMPILER} )
message ( "-------------Version: " ${CMAKE_CXX_COMPILER_VERSION} )
message ( "-----HSA-Runtime-Inc: " ${HSA_RUNTIME_INC_PATH} )
message ( "-----HSA-Runtime-Lib: " ${HSA_RUNTIME_LIB_PATH} )
message ( "------------API-path: " ${API_PATH} )
message ( "-----CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
