#include "pm4_factory.h"

#include <mutex>
#include <shared_mutex>

namespace aql_profile
{
namespace
{
struct locked_agent_cache
{
    std::shared_mutex                       mutex;
    std::unordered_map<uint64_t, AgentInfo> cache;

    void add(uint64_t& agent_id, const AgentInfo& agent_info)
    {
        auto lock = std::unique_lock{mutex};
        agent_id = cache.size();
        cache[agent_id] = agent_info;
    }

    const AgentInfo* get(uint64_t agent_id)
    {
        auto lock = std::shared_lock{mutex};
        auto it = cache.find(agent_id);
        if(it == cache.end()) return nullptr;
        return &it->second;
    }
};

locked_agent_cache& get_cache() {
    static locked_agent_cache cache;
    return cache;
}
}  // namespace

aqlprofile_agent_handle_t
RegisterAgent(const aqlprofile_agent_info_t* agent_info)
{

    aqlprofile_agent_handle_t agent_id;
    AgentInfo int_agent_info = {
        .cu_num = agent_info->cu_num,
        .se_num = agent_info->se_num,
        .xcc_num = agent_info->xcc_num,
        .shader_arrays_per_se = agent_info->shader_arrays_per_se
    };

    auto len =  strlen(agent_info->agent_gfxip);
    memset(int_agent_info.gfxip, 0, sizeof(int_agent_info.gfxip));
    memcpy(int_agent_info.gfxip, agent_info->agent_gfxip, 
        (len >= sizeof(int_agent_info.gfxip) ? sizeof(int_agent_info.gfxip) - 1 : len));


    get_cache().add(agent_id.handle, int_agent_info);
    return agent_id;
}

const AgentInfo*
GetAgentInfo(aqlprofile_agent_handle_t agent_id) {
    return get_cache().get(agent_id.handle);
}

}  // namespace aql_profile