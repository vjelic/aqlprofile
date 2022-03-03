# Copyright (c) 2022 Advanced Micro Devices, Inc. All Rights Reserved.
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.16.8)

set(AQLPROF_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(AQLPROF_WRAPPER_DIR ${AQLPROF_BUILD_DIR}/wrapper_dir)
set(AQLPROF_WRAPPER_LIB_DIR ${AQLPROF_WRAPPER_DIR}/lib)

#function to create symlink to libraries
function(create_library_symlink)
  file(MAKE_DIRECTORY ${AQLPROF_WRAPPER_LIB_DIR})
  set(LIB_AQLPROF "${AQLPROFILE_LIBRARY}.so")
  set(MAJ_VERSION "${LIB_VERSION_MAJOR}")
  set(SO_VERSION "${LIB_VERSION_STRING}")
  set(library_files "${LIB_AQLPROF}"  "${LIB_AQLPROF}.${MAJ_VERSION}" "${LIB_AQLPROF}.${SO_VERSION}")

  foreach(file_name ${library_files})
     add_custom_target(link_${file_name} ALL
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                  COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ../../lib/${file_name} ${AQLPROF_WRAPPER_LIB_DIR}/${file_name})
  endforeach()
endfunction()

# Create symlink to library files
create_library_symlink()
install(DIRECTORY ${AQLPROF_WRAPPER_LIB_DIR} DESTINATION ${AQLPROFILE_NAME} COMPONENT ${AQLPROFILE_LIBRARY})
