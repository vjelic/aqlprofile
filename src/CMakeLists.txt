#
# Build dynamic Library object
#
set ( TARGET_LIB "${TARGET_NAME}${NBITSTR}" )
set ( LIB_SRC
  ${LIB_DIR}/core/aql_profile.cpp
  ${LIB_DIR}/core/populate_aql.cpp
  ${LIB_DIR}/core/gfx8_factory.cpp
  ${LIB_DIR}/core/gfx9_factory.cpp
  ${LIB_DIR}/core/legacy_pm4.cpp
)
include_directories ( ${LIB_DIR} )
include_directories ( ${ROOT_DIR} )
include_directories ( ${API_PATH} )
add_library ( ${TARGET_LIB} SHARED ${LIB_SRC} )
target_link_libraries( ${TARGET_LIB} c stdc++)

#
# Creating the library link
#
execute_process ( COMMAND sh -xc "/bin/ln -s lib${TARGET_LIB}.so libhsa-amd-${TARGET_LIB}.so.1" )
