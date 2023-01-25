# ###############################################################################
# # Copyright (c) 2022 Advanced Micro Devices, Inc.
# #
# # Permission is hereby granted, free of charge, to any person obtaining a copy
# # of this software and associated documentation files (the "Software"), to
# # deal in the Software without restriction, including without limitation the
# # rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# # sell copies of the Software, and to permit persons to whom the Software is
# # furnished to do so, subject to the following conditions:
# #
# # The above copyright notice and this permission notice shall be included in
# # all copies or substantial portions of the Software.
# #
# # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# # FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# # IN THE SOFTWARE.
# ###############################################################################

#
# Build Standaone Library for Advanced Thread Tracer
#

# set default ROCM_PATH
if(NOT DEFINED ROCM_PATH)
  set(ROCM_PATH "/opt/rocm" CACHE STRING "Default ROCM installation directory")
endif()

set ( ROCMTOOLS_SUPPORT_FILES
  ${ROCMTOOLS_DIR}/assembly_parser.cpp
  ${ROCMTOOLS_DIR}/trace_parser.cpp
  ${ROCMTOOLS_DIR}/token.cpp
  ${ROCMTOOLS_DIR}/wave.cpp
  ${ROCMTOOLS_DIR}/trie.cpp
)
add_library(rocmtools_support SHARED ${ROCMTOOLS_SUPPORT_FILES})

target_include_directories(rocmtools_support PUBLIC
 ${ROCM_PATH}/include/rocmtools
 $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
 $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
 PRIVATE
 ${CMAKE_CURRENT_BINARY_DIR}
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${PROJECT_SOURCE_DIR}/inc)

install(TARGETS rocmtools_support LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME})