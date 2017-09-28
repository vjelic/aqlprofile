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

#include_directories ( ${ROOT_DIR} )

add_library ( ${TARGET_LIB} SHARED ${LIB_SRC} )
target_include_directories ( ${TARGET_LIB} PRIVATE ${LIB_DIR} ${API_PATH} )
target_link_libraries( ${TARGET_LIB} PRIVATE ${HSA_RUNTIME_LIB} ${HSA_KMT_LIB} c stdc++ )
