#pragma once

#include <hsa/hsa_ven_amd_aqlprofile.h>
#include "def/gpu_block_info.h"
#include "core/aql_profile.hpp"
#include "core/pm4_factory.h"

#include <cstdint>
#include <string>
#include <vector>

struct EventDimension
{
    EventDimension(const EventDimension& other) = default;
    EventDimension(std::string_view _name, size_t _extent):
        id(dimension_table.at(std::string(_name))), name(_name), extent(_extent) {}

    uint64_t id;
    uint64_t extent;
    std::string_view name;

    static std::vector<std::string> dimension_list;
    static std::unordered_map<std::string, size_t> dimension_table;
    static void init()
    {
        if (dimension_list.size()) return;

        dimension_list.push_back("XCD");
        dimension_list.push_back("AID");
        dimension_list.push_back("SE");
        dimension_list.push_back("SA");
        dimension_list.push_back("WGP");
        dimension_list.push_back("INSTANCE");

        for (size_t i=0; i<dimension_list.size(); i++)
            dimension_table[dimension_list[i]] = i;
    }
};


class EventKey
{
public:
    uint64_t agent;
    hsa_ven_amd_aqlprofile_block_name_t block;

    bool operator==(const EventKey& other) const {
        return  agent == other.agent && block == other.block;
    }
    bool operator!=(const EventKey& other) const {
        return !(*this == other);
    }
};

class EventAttribDimension
{
public:
    template<typename AgentType>
    EventAttribDimension(AgentType agent, hsa_ven_amd_aqlprofile_block_name_t block_name):
        key({agent.handle, block_name})
    {
        EventDimension::init();

        aql_profile::Pm4Factory* pm4_factory = aql_profile::Pm4Factory::Create(agent);
        this->block_info = pm4_factory->GetBlockInfo(block_name);

        bIsGFX11 = pm4_factory->IsGFX11();
        bIsGFX9 = pm4_factory->IsGFX9();

        num_xccs = pm4_factory->GetXccNumber();
        if (num_xccs > 1 && HasAttr(CounterBlockUmcAttr)) { // For MI300 AID only
            num_xccs = 1;
            num_aid = 4;
        }
        shader_engine = HasAttr(CounterBlockSeAttr);
        shader_array = HasAttr(CounterBlockSaAttr);

        if (bIsGFX9)
            compute_unit = HasAttr(CounterBlockTcAttr) && shader_engine;
        else if (bIsGFX11)
            workgroup_processor = HasAttr(CounterBlockSqAttr);

        se_num = pm4_factory->GetShaderEnginesNumber();
        sarrays = pm4_factory->GetShaderArraysNumber() * se_num;

        cu_num = (pm4_factory->GetComputeUnitNumber() + sarrays - 1) / sarrays;
        wgp_num = (pm4_factory->GetComputeUnitNumber()/2 + sarrays - 1) / sarrays;

        if (HasAttr(CounterBlockUmcAttr))
            block_instance_count = block_info->instance_count / num_aid;
        else if (compute_unit)
            block_instance_count = std::min<size_t>(block_info->instance_count, cu_num+1);
        else
            block_instance_count = block_info->instance_count;

        if (num_xccs > 1)
            dimensions.push_back({"XCD", num_xccs});
        if (num_aid > 1)
            dimensions.push_back({"AID", num_aid});
        if (shader_engine)
            dimensions.push_back({"SE", pm4_factory->GetShaderEnginesNumber()});
        if (shader_array)
            dimensions.push_back({"SA", pm4_factory->GetShaderArraysNumber()});

        if (workgroup_processor)
            dimensions.push_back({"WGP", wgp_num});
        else
            dimensions.push_back({"INSTANCE", block_instance_count});
    }

    size_t get_num_xccs() const { return num_xccs; };
    size_t get_total_elements() const {
        size_t acc = 1;
        for (auto& d : dimensions) acc *= d.extent;
        return acc;
    }
    uint64_t get_num() const { return dimensions.size(); };
    EventDimension get_dim(uint64_t index) const { return dimensions.at(index); };

    hsa_status_t get_coordinates(uint8_t* coordinates, int64_t cumulative_id) const
    {
        const int end = static_cast<int>(get_num())-1;
        for (int i=end; i>=0; i--)
        {
            coordinates[end-i] = static_cast<uint8_t>(cumulative_id % dimensions.at(end-i).extent);
            cumulative_id /= dimensions.at(end-i).extent;
        }
        if (cumulative_id != 0)
            return HSA_STATUS_ERROR_INVALID_INDEX;
        return HSA_STATUS_SUCCESS;
    }

    size_t get_num_instances() const { return block_instance_count; }

private:
    bool HasAttr(CounterBlockAttr attr) const { return (block_info->attr & attr) != 0; }

    EventKey key;
    const GpuBlockInfo* block_info = nullptr;
    hsa_ven_amd_aqlprofile_event_t event{};

    bool bIsGFX11;
    bool bIsGFX9;

    bool shader_engine = false;
    bool shader_array = false;
    bool compute_unit = false;
    bool workgroup_processor = false;

    size_t num_xccs = 1;
    size_t num_aid = 1;
    size_t se_num = 1;
    size_t sarrays = 1;
    size_t cu_num = 1;
    size_t wgp_num = 1;
    size_t block_instance_count = 1;

    std::vector<EventDimension> dimensions;

public:
    template<typename AgentType>
    static const EventAttribDimension& get(AgentType agent, hsa_ven_amd_aqlprofile_block_name_t block_name)
    {
        thread_local std::unique_ptr<EventAttribDimension> event_cache{nullptr};
        EventKey key{agent.handle, block_name};

        if (!event_cache || event_cache->key != key)
            event_cache = std::make_unique<EventAttribDimension>(agent, block_name);

        return *event_cache;
    }
};

