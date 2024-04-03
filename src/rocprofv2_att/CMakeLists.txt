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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB ROCMTOOLS_SUPPORT_FILES
  ${ROCMTOOLS_DIR}/assembly_parser.cpp
  ${ROCMTOOLS_DIR}/trace_parser.cpp
  ${ROCMTOOLS_DIR}/tracebranch.cpp
  ${ROCMTOOLS_DIR}/trie.cpp
  ${ROCMTOOLS_DIR}/gfx9/*.cpp
  ${ROCMTOOLS_DIR}/gfx10/*.cpp
  ${ROCMTOOLS_DIR}/gfx11/*.cpp
  ${ROCMTOOLS_DIR}/stitch/pctranslator.cpp
  ${ROCMTOOLS_DIR}/stitch/stitch.cpp
  ${ROCMTOOLS_DIR}/stitch/codeservice.cpp
)

add_library(rocprofv2_att SHARED ${ROCMTOOLS_SUPPORT_FILES})

target_include_directories(rocprofv2_att PUBLIC
   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   PRIVATE
   ${CMAKE_CURRENT_BINARY_DIR}
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${PROJECT_SOURCE_DIR}/inc)
  target_link_libraries(rocprofv2_att PRIVATE pthread hsa-runtime64::hsa-runtime64)

install(
   TARGETS rocprofv2_att LIBRARY
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}
   COMPONENT asan)
install(
   TARGETS rocprofv2_att LIBRARY
   DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}
   COMPONENT runtime)
