################################################################################
##
## Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
##
## MIT LICENSE:
## Permission is hereby granted, free of charge, to any person obtaining a copy of
## this software and associated documentation files (the "Software"), to deal in
## the Software without restriction, including without limitation the rights to
## use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
## of the Software, and to permit persons to whom the Software is furnished to do
## so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all
## copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.
##
################################################################################

cmake_minimum_required ( VERSION 2.8.12 )

## Verbose output.
set ( CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Verbose Output" FORCE )

## Set module name and project name.
set ( AQLPROFILE_NAME "hsa-amd-aqlprofile" )
set ( AQLPROFILE_TARGET "${AQLPROFILE_NAME}64" )
set ( AQLPROFILE_LIBRARY "lib${AQLPROFILE_TARGET}" )
project ( ${AQLPROFILE_TARGET} )

## Adding default path cmake modules
list ( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" )
## Include common cmake modules
include ( utils )
## Set build environment
include ( env )

## Setup the package version.
get_version ( "1.0.0" )
message ( "-- BUILD-VERSION: ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )

set ( BUILD_VERSION_MAJOR ${VERSION_MAJOR} )
set ( BUILD_VERSION_MINOR ${VERSION_MINOR} )
set ( BUILD_VERSION_PATCH ${VERSION_PATCH} )
if ( DEFINED VERSION_BUILD AND NOT ${VERSION_BUILD} STREQUAL "" )
  message ( "VERSION BUILD DEFINED ${VERSION_BUILD}" )
  set ( BUILD_VERSION_PATCH "${BUILD_VERSION_PATCH}-${VERSION_BUILD}" )
endif ()
set ( BUILD_VERSION_STRING "${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}.${BUILD_VERSION_PATCH}" )

set ( LIB_VERSION_MAJOR ${VERSION_MAJOR} )
set ( LIB_VERSION_MINOR ${VERSION_MINOR} )
if ( ${ROCM_PATCH_VERSION} )
   set ( LIB_VERSION_PATCH ${ROCM_PATCH_VERSION} )
else()
   set ( LIB_VERSION_PATCH ${VERSION_PATCH} )
endif()
set ( LIB_VERSION_STRING "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}" )

## Set target and root/lib/test directory
set ( TARGET_NAME "${AQLPROFILE_TARGET}" )
set ( ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
set ( LIB_DIR "${ROOT_DIR}/src" )
set ( TEST_DIR "${ROOT_DIR}/test" )

## Build library
include ( ${LIB_DIR}/CMakeLists.txt )

## Set the VERSION and SOVERSION values
set_property ( TARGET ${TARGET_NAME} PROPERTY VERSION "${LIB_VERSION_STRING}" )
set_property ( TARGET ${TARGET_NAME} PROPERTY SOVERSION "${LIB_VERSION_MAJOR}" )

## If the library is a release, strip the target library
if ( "${CMAKE_BUILD_TYPE}" STREQUAL release )
  add_custom_command ( TARGET ${AQLPROFILE_TARGET} POST_BUILD COMMAND ${CMAKE_STRIP} *.so )
endif ()

## Build tests
set ( TEST_BINARY_DIR ${PROJECT_BINARY_DIR}/test )
add_subdirectory ( ${TEST_DIR} ${TEST_BINARY_DIR} )

## Add the install directives for the runtime library.
set ( DEST_NAME ${AQLPROFILE_NAME} )
add_custom_target ( so-link ALL WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ../${DEST_NAME}/lib/${AQLPROFILE_LIBRARY}.so so-link )
install ( TARGETS ${AQLPROFILE_TARGET} LIBRARY DESTINATION ${AQLPROFILE_NAME}/lib COMPONENT ${AQLPROFILE_LIBRARY} )
install ( FILES ${PROJECT_BINARY_DIR}/so-link DESTINATION lib RENAME ${AQLPROFILE_LIBRARY}.so )

## Add the packaging directives for the runtime library.
set ( CPACK_PACKAGE_NAME ${AQLPROFILE_NAME} )
set ( CPACK_PACKAGE_VENDOR "Advanced Micro Devices, Inc." )
set ( CPACK_PACKAGE_VERSION_MAJOR ${BUILD_VERSION_MAJOR} )
set ( CPACK_PACKAGE_VERSION_MINOR ${BUILD_VERSION_MINOR} )
set ( CPACK_PACKAGE_VERSION_PATCH ${BUILD_VERSION_PATCH} )
set ( CPACK_PACKAGE_CONTACT "ROCm Profiler Support <dl.rocm-profiler.support@amd.com>" )
set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "AQLPROFILE library for AMD HSA runtime API extension support" )
set ( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md" )
set ( ENABLE_LDCONFIG ON CACHE BOOL "Set library links and caches using ldconfig.")

## Debian package specific variables
set ( CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/RadeonOpenCompute/HSA-AqlProfile-AMD-extension" )
## Process the Debian install/remove scripts to update the CPACK variables
configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/DEBIAN/postinst.in DEBIAN/postinst @ONLY )
configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/DEBIAN/prerm.in DEBIAN/prerm @ONLY )
set ( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "DEBIAN/postinst;DEBIAN/prerm" )

## Process the Rpm install/remove scripts to update the CPACK variables
configure_file ( "${CMAKE_CURRENT_SOURCE_DIR}/RPM/post.in" RPM/post @ONLY )
configure_file ( "${CMAKE_CURRENT_SOURCE_DIR}/RPM/postun.in" RPM/postun @ONLY )
## RPM package specific variables
set ( CPACK_RPM_PRE_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_BINARY_DIR}/RPM/post" )
set ( CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${CMAKE_CURRENT_BINARY_DIR}/RPM/postun" )

if ( DEFINED CPACK_PACKAGING_INSTALL_PREFIX )
    set ( CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "${CPACK_PACKAGING_INSTALL_PREFIX}" )
endif ( )

include ( CPack )
