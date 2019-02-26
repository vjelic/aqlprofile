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

add_library ( ${TARGET_LIB} SHARED ${LIB_SRC} )
target_include_directories ( ${TARGET_LIB} PRIVATE ${LIB_DIR} ${API_PATH} )
target_link_libraries( ${TARGET_LIB} PRIVATE ${HSA_RUNTIME_LIB} ${HSA_KMT_LIB} c stdc++ )

## Generating definitions
set ( SCRIPT_DIR "${ROOT_DIR}/script" )
set ( GFXIP_DIR "${ROOT_DIR}/gfxip" )
set ( DEF_DIR "${ROOT_DIR}/src/def" )
set ( BINFO_TEMPL "${SCRIPT_DIR}/gpu_block_info.h" )
set ( BINFO_DEF "${GFXIP_DIR}/gpu_block_info.h" )
set ( BINFO_HEADER "${DEF_DIR}/gpu_block_info.h" )
set ( GFX8_TEMPL "${SCRIPT_DIR}/gfx8_def.h" )
set ( GFX8_DEF "${GFXIP_DIR}/gfx8_def.h" )
set ( GFX8_HEADER "${DEF_DIR}/gfx8_def.h" )
set ( GFX9_TEMPL "${SCRIPT_DIR}/gfx9_def.h" )
set ( GFX9_DEF "${GFXIP_DIR}/gfx9_def.h" )
set ( GFX9_HEADER "${DEF_DIR}/gfx9_def.h" )
include_directories ( ${ROOT_DIR} )
add_custom_target( mygen
  COMMAND sh -xc "cp ${BINFO_TEMPL} ${BINFO_HEADER}"
  COMMAND sh -xc "sed '/gfx8_def/ s/.*//' ${GFX8_TEMPL} >${GFX8_HEADER}"
  COMMAND sh -xc "cp ${GFX9_TEMPL} ${GFX9_HEADER}"
  COMMAND sh -xc "${ROOT_DIR}/script/errextr.sh ${GFX8_HEADER} ${GFX8_DEF}"
  COMMAND sh -xc "sed '/gfx9_def/ s/.*//' ${GFX9_TEMPL} >${GFX9_HEADER}"
  COMMAND sh -xc "${ROOT_DIR}/script/errextr.sh ${GFX9_HEADER} ${GFX9_DEF}"
  COMMAND sh -xc "head -n1 ${BINFO_TEMPL} >${BINFO_HEADER}"
  COMMAND sh -xc "sed 's/_GPU_BLOCKINFO_H_/SRC_DEF_GPU_BLOCK_INFO_H_/' ${BINFO_DEF} >>${BINFO_HEADER}"
)
