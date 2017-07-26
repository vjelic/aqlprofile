#
# Minimum version of cmake required
#
cmake_minimum_required ( VERSION 3.5.0 )

#
# Set verbose flag
#
set ( CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Verbose Output" FORCE )

#
# Set project name
# @note: Must come before adding any sub-directories
#
set ( TARGET_NAME "aqlprofile" )
project ( ${TARGET_NAME} )

#
# Set root/lib/test directory
#
set ( ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set ( LIB_DIR ${ROOT_DIR}/src )
set ( TEST_DIR ${ROOT_DIR}/test )

#
# Set build environment
#
include ( cmake_modules/env.cmake )

#
# Build library
#
include ( ${LIB_DIR}/CMakeLists.txt )

#
# Build tests
#
add_subdirectory ( ${TEST_DIR} ${PROJECT_BINARY_DIR}/test )

#
# Style format
#
execute_process ( COMMAND sh -xc "/usr/bin/find ${LIB_DIR} ${TEST_DIR} -name '*.cpp' -exec /usr/bin/clang-format -i -style=file \{\} \;" )
execute_process ( COMMAND sh -xc "/usr/bin/find ${LIB_DIR} ${TEST_DIR} -name '*.hpp' -exec /usr/bin/clang-format -i -style=file \{\} \;" )
execute_process ( COMMAND sh -xc "/usr/bin/find ${LIB_DIR} ${TEST_DIR} -name '*.h' -exec /usr/bin/clang-format -i -style=file \{\} \;" )
