cmake_minimum_required ( VERSION 2.8.12 )

set(EXE_NAME "att_parser_test")

## Test control sources
set(PARSER_SRC ${TEST_DIR}/parser/parser_test.cpp)

## Building test executable
add_executable (${EXE_NAME} ${PARSER_SRC})
install(TARGETS ${EXE_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME} COMPONENT tests)
