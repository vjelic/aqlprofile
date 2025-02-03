#include <assert.h>
#include "counter.hpp"
#include <cstring>

#define CHECK_HSA(x) if ((x) != HSA_STATUS_SUCCESS) { std::cerr << __FILE__ << " error at " << __LINE__ << std::endl; exit(-1); }

hsa_status_t data_callback(
    aqlprofile_pmc_event_t event,
    uint64_t counter_id,
    uint64_t counter_value,
    void* userdata
) {
    auto* packet = static_cast<AQLPacket*>(userdata);
    try {
        packet->results.at(event) += counter_value;
    } catch(...) { abort(); }
    return HSA_STATUS_SUCCESS;
}

hsa_status_t
AQLPacket::Alloc(void** ptr, size_t size, desc_t flags, void* data)
{
    auto* packet = reinterpret_cast<AQLPacket*>(data);
    assert(packet && "Invalid aql packet");
    if (flags.memory_hint != AQLPROFILE_MEMORY_HINT_DEVICE_UNCACHED)
    {
        CHECK_HSA(hsa_amd_memory_pool_allocate(AgentInfo::cpu_pool, size, 
                                               HSA_AMD_MEMORY_POOL_EXECUTABLE_FLAG, ptr));
        CHECK_HSA(hsa_amd_memory_fill(*ptr, 0u, size / sizeof(uint32_t)));
        return hsa_amd_agents_allow_access(1, &packet->hsa_agent, nullptr, *ptr);
    }
    else
    {
        CHECK_HSA(hsa_amd_memory_pool_allocate(AgentInfo::kernarg_pool, size, 
                                               HSA_AMD_MEMORY_POOL_EXECUTABLE_FLAG, ptr));
        CHECK_HSA(hsa_amd_memory_fill(*ptr, 0u, size / sizeof(uint32_t)));
        return hsa_amd_agents_allow_access(1, &packet->hsa_agent, nullptr, *ptr);
    }
}

void AQLPacket::Free(void* ptr, void* data)
{
    if(ptr == nullptr) return;
    hsa_amd_memory_pool_free(ptr);
}

hsa_status_t AQLPacket::Copy(void* dst, const void* src, size_t size, void* data)
{
    if(size == 0) return HSA_STATUS_SUCCESS;
    return hsa_memory_copy(dst, src, size);
}

AQLPacket::AQLPacket(
    AgentInfo& agent,
    const std::vector<std::string>& _counters
): hsa_agent(agent.hsa_agent) {
    constexpr hsa_ext_amd_aql_pm4_packet_t null_amd_aql_pm4_packet =
    {
        .header            = 0,
        .pm4_command       = {0},
        .completion_signal = {.handle = 0}
    };

    packets.start_packet = null_amd_aql_pm4_packet;
    packets.stop_packet  = null_amd_aql_pm4_packet;
    packets.read_packet  = null_amd_aql_pm4_packet;

    aqlprofile_pmc_profile_t profile{};
    std::vector<aqlprofile_pmc_event_t> events;
    for (auto& counter : _counters)
    {
        auto& event = agent.counters.at(counter).at(0);
        results[event] = 0;
        prev_results[event] = 0;
        counter_names[event] = counter;
        for (auto& ev : agent.counters.at(counter))
            events.push_back(ev);
    }

    profile.agent       = agent.handle;
    profile.events      = events.data();
    profile.event_count = static_cast<uint32_t>(events.size());

    CHECK_HSA(aqlprofile_pmc_create_packets(&this->handle,
                                            &this->packets,
                                            profile,
                                            &AQLPacket::Alloc,
                                            &AQLPacket::Free,
                                            &AQLPacket::Copy,
                                            this));

    packets.start_packet.header = HSA_PACKET_TYPE_VENDOR_SPECIFIC << HSA_PACKET_HEADER_TYPE;
    packets.stop_packet.header  = HSA_PACKET_TYPE_VENDOR_SPECIFIC << HSA_PACKET_HEADER_TYPE;
    packets.read_packet.header  = HSA_PACKET_TYPE_VENDOR_SPECIFIC << HSA_PACKET_HEADER_TYPE;
}

void AQLPacket::iterate()
{
    for (auto& [key, value] : results)
    {
        prev_results[key] = value;
        results[key] = 0;
    }
    CHECK_HSA(aqlprofile_pmc_iterate_data(this->handle, data_callback, this));
}
