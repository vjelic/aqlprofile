#
# Source files
#
set ( LIB_SRC aql_profile.cpp populate_aql.cpp gfx8_factory.cpp gfx9_factory.cpp legacy_pm4.cpp )

#
# Header files include path(s).
#
include_directories ( $ENV{ROCR_INC_DIR} )
include_directories ( ${PROJ_DIR}/pm4 )
include_directories ( ${API_DIR} )

#
# Build a dynamic Library object
#
add_library ( ${TARGET_LIB} SHARED ${LIB_SRC} )
target_link_libraries( ${TARGET_LIB} ${PM4_LIB} c stdc++)
