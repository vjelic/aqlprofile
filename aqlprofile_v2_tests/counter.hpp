#pragma once

#include <assert.h>
#include <hsa/hsa.h>
#include <hsa/hsa_ext_amd.h>
#include <hsa/hsa_ven_amd_aqlprofile.h>
#include "/opt/rocm/include/aqlprofile-sdk/aql_profile_v2.h"
#include <stdlib.h>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include "agent.hpp"

class AQLPacket
{
    using desc_t = aqlprofile_buffer_desc_flags_t;
public:
    AQLPacket(AgentInfo& _agent, const std::vector<std::string>& counters);
    ~AQLPacket() { aqlprofile_pmc_delete_packets(this->handle); };

    void iterate();

    static hsa_status_t Alloc(void** ptr, size_t size, desc_t flags, void* data);
    static void         Free(void* ptr, void* data);
    static hsa_status_t Copy(void* dst, const void* src, size_t size, void* data);

    std::map<std::string, int64_t> get()
    {
        std::map<std::string, int64_t> ret;
        for (auto& [event, counter] : counter_names)
            ret.emplace(counter, results.at(event));
        return ret;
    }

    std::map<aqlprofile_pmc_event_t, std::string> counter_names;
    std::map<aqlprofile_pmc_event_t, int64_t> results;
    std::map<aqlprofile_pmc_event_t, int64_t> prev_results;

    aqlprofile_handle_t handle{0};
    hsa_agent_t hsa_agent;
    aqlprofile_pmc_aql_packets_t packets;

    bool delta = false;
};
