#
# Build dynamic Library object
#
set ( TARGET_LIB "${TARGET_NAME}" )
set ( LIB_SRC
  ${LIB_DIR}/core/aql_profile.cpp
  ${LIB_DIR}/core/populate_aql.cpp
  ${LIB_DIR}/core/gfx8_factory.cpp
  ${LIB_DIR}/core/gfx9_factory.cpp
  ${LIB_DIR}/core/legacy_pm4.cpp
)
include_directories ( ${LIB_DIR} )
include_directories ( ${API_PATH} )
LINK_DIRECTORIES ( ${HSA_RUNTIME_LIB_PATH}  ${HSA_KMT_LIB_PATH} )
add_library ( ${TARGET_LIB} SHARED ${LIB_SRC} )
target_link_libraries( ${TARGET_LIB} PRIVATE ${HSA_RUNTIME_NAME} PRIVATE ${HSA_KMT_NAME} c stdc++ )
