#include "pm4_factory.h"
// CmdBuilder includes
#include "gfx8_cmd_builder.h"
// PMC includes
#include "gfx8_pmc_builder.h"
// SQTT includes
#include "gfx8_sqtt_builder.h"
// Block info
#include "gfxip/gfx8/gfx8_block_info.h"

namespace aql_profile {
using namespace gfxip::gfx8;

class Gfx8Factory : public Pm4Factory {
 public:
  Gfx8Factory() : Pm4Factory(block_map) {
    block_map.init(block_id_table, Gfx8HwBlocks, Gfx8HwBlockCount);
  }
  pm4_builder::CmdBuilder* getCmdBuilder();
  pm4_builder::PmcBuilder* getPmcBuilder();
  pm4_builder::SqttBuilder* getSqttBuilder();

 private:
  static uint32_t block_id_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
  BlockMap block_map;
};

// GFX8 block ID mapping table
uint32_t Gfx8Factory::block_id_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    kHsaViCounterBlockIdCb0,  kHsaViCounterBlockIdCpf,    kHsaViCounterBlockIdDb0,
    kHsaViCounterBlockIdGrbm, kHsaViCounterBlockIdGrbmSe, kHsaViCounterBlockIdPaSu,
    kHsaViCounterBlockIdPaSc, kHsaViCounterBlockIdSpi,    kHsaViCounterBlockIdSq,
    kHsaViCounterBlockIdSqEs, kHsaViCounterBlockIdSqGs,   kHsaViCounterBlockIdSqVs,
    kHsaViCounterBlockIdSqPs, kHsaViCounterBlockIdSqLs,   kHsaViCounterBlockIdSqHs,
    kHsaViCounterBlockIdSqCs, kHsaViCounterBlockIdSx,     kHsaViCounterBlockIdTa0,
    kHsaViCounterBlockIdTca0, kHsaViCounterBlockIdTcc0,   kHsaViCounterBlockIdTd0,
    kHsaViCounterBlockIdTcp0, kHsaViCounterBlockIdGds,    kHsaViCounterBlockIdVgt,
    kHsaViCounterBlockIdIa,   kHsaViCounterBlockIdMc,     kHsaViCounterBlockIdSrbm,
    kHsaViCounterBlockIdTcs,  kHsaViCounterBlockIdWd,     kHsaViCounterBlockIdCpg,
    kHsaViCounterBlockIdCpc};

Pm4Factory* Pm4Factory::Gfx8Create() {
  auto p = new Gfx8Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

pm4_builder::CmdBuilder* Gfx8Factory::getCmdBuilder() {
  auto p = new pm4_builder::Gfx8CmdBuilder;
  if (p == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");
  return p;
}

pm4_builder::PmcBuilder* Gfx8Factory::getPmcBuilder() {
  auto p = new pm4_builder::Gfx8PmcBuilder;
  if (p == NULL) throw aql_profile_exc_msg("PmcBuilder mgr allocation failed");
  return p;
}

pm4_builder::SqttBuilder* Gfx8Factory::getSqttBuilder() {
  auto p = new pm4_builder::Gfx8SqttBuilder;
  if (p == NULL) throw aql_profile_exc_msg("SqttBuilder mgr allocation failed");
  return p;
}

}  // aql_profile
