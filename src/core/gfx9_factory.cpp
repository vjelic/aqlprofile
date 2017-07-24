#include "core/pm4_factory.h"
#include "def/gfx9_def.h"
#include "pm4/gfx9_cmd_builder.h"
#include "pm4/gfx9_pmc_builder.h"
#include "pm4/gfx9_sqtt_builder.h"

namespace aql_profile {

class Gfx9Factory : public Pm4Factory {
 public:
  Gfx9Factory()
      : block_map(block_id_table, Gfx9HwBlocks, Gfx9HwBlockCount), Pm4Factory(block_map) {}
  pm4_builder::CmdBuilder* getCmdBuilder();
  pm4_builder::PmcBuilder* getPmcBuilder();
  pm4_builder::SqttBuilder* getSqttBuilder();

 private:
  static uint32_t block_id_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER];
  const BlockMap block_map;
};

// GFX9 block ID mapping table
uint32_t Gfx9Factory::block_id_table[HSA_VEN_AMD_AQLPROFILE_BLOCKS_NUMBER] = {
    kHsaAiCounterBlockIdCb,    kBadBlockId /*CPF*/,        kHsaAiCounterBlockIdDb,
    kHsaAiCounterBlockIdGrbm,  kHsaAiCounterBlockIdGrbmSe, kHsaAiCounterBlockIdPaSu,
    kHsaAiCounterBlockIdPaSc,  kHsaAiCounterBlockIdSpi,    kHsaAiCounterBlockIdSq,
    kBadBlockId /*GFX8:SQES*/, kHsaAiCounterBlockIdSqGs,   kHsaAiCounterBlockIdSqVs,
    kHsaAiCounterBlockIdSqPs,  kBadBlockId /*GFX8:SQLS*/,  kHsaAiCounterBlockIdSqHs,
    kHsaAiCounterBlockIdSqCs,  kHsaAiCounterBlockIdSx,     kHsaAiCounterBlockIdTa,
    kHsaAiCounterBlockIdTca,   kHsaAiCounterBlockIdTcc,    kHsaAiCounterBlockIdTd,
    kHsaAiCounterBlockIdTcp,   kHsaAiCounterBlockIdGds,    kHsaAiCounterBlockIdVgt,
    kHsaAiCounterBlockIdIa,    kHsaAiCounterBlockIdMc,     kBadBlockId /*SRBM*/,
    kHsaAiCounterBlockIdTcs,   kHsaAiCounterBlockIdWd,     kBadBlockId /*CPG*/,
    kHsaAiCounterBlockIdCpc};

Pm4Factory* Pm4Factory::Gfx9Create() {
  auto p = new Gfx9Factory;
  if (p == NULL) throw aql_profile_exc_msg("Gfx8Factory allocation failed");
  return p;
}

pm4_builder::CmdBuilder* Gfx9Factory::getCmdBuilder() {
  auto p = new pm4_builder::Gfx9CmdBuilder;
  if (p == NULL) throw aql_profile_exc_msg("CmdBuilder allocation failed");
  return p;
}

pm4_builder::PmcBuilder* Gfx9Factory::getPmcBuilder() {
  auto p = new pm4_builder::Gfx9PmcBuilder;
  if (p == NULL) throw aql_profile_exc_msg("PmcBuilder mgr allocation failed");
  return p;
}

pm4_builder::SqttBuilder* Gfx9Factory::getSqttBuilder() {
  auto p = new pm4_builder::Gfx9SqttBuilder;
  if (p == NULL) throw aql_profile_exc_msg("SqttBuilder mgr allocation failed");
  return p;
}

}  // namespace aql_profile
