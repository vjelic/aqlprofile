#pragma once
#include <vector>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <memory>
#include "include/aql_profile_v2.h"

class MemoryManager
{
public:
    MemoryManager(
        hsa_agent_t agent,
        aqlprofile_memory_alloc_callback_t alloc,
        aqlprofile_memory_dealloc_callback_t dealloc,
        void* data
    ) : agent(agent), alloc_cb(alloc), dealloc_cb(dealloc),
        userdata(data), handle(HANDLE_COUNTER.fetch_add(1)) {}

    ~MemoryManager()
    {
        if (cmdbuf) dealloc_cb(cmdbuf, userdata);
        if (outputbuf) dealloc_cb(outputbuf, userdata);
        cmdbuf = nullptr;
        outputbuf = nullptr;
    }

    void* GetCmdBuf() const { return cmdbuf; }
    void* GetOutputBuf() const { return outputbuf; }
    void* GetTraceControlBuf() const { return trace_control_buf; }

    size_t GetCmdBufSize() const { return cmdbuf_size; }
    size_t GetOutputBufSize() const { return outputbuf_size; }
    size_t GetTraceControlBufSize() const { return trace_control_buf_size; }

    size_t GetHandler() const { return handle; }
    hsa_agent_t GetAgent() const { return agent; }
    const std::vector<aqlprofile_pmc_event_t>& GetEvents() const { return events; }
    const std::vector<hsa_ven_amd_aqlprofile_parameter_t>& GetATTParams() const { return att_params; }

    void CopyEvents(const aqlprofile_pmc_event_t* events, size_t count) {
        for (size_t i=0; i<count; i++)
            this->events.push_back(events[i]);
    }
    void CopyATTParams(hsa_ven_amd_aqlprofile_parameter_t* params, size_t count) {
        for (size_t i=0; i<count; i++)
            this->att_params.push_back(params[i]);
    }

    void CreateCmdBuf(size_t size)
    {
        if (cmdbuf) throw "Cmdbuf already allocated";

        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = true;
        flags.device_access = true;
        alloc_cb(&cmdbuf, size, flags, userdata);
        cmdbuf_size = size;
    }

    void CreateOutputBuf(size_t size)
    {
        if (outputbuf) throw "outputbuf already allocated";

        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        hsa_status_t status = alloc_cb(&outputbuf, size, flags, userdata);
        if (status != HSA_STATUS_SUCCESS)
            throw std::string("Memory callback returned error");
        outputbuf_size = size;
    }

    void CreateTraceControlBuf(size_t size)
    {
        if (trace_control_buf) throw "trace_control_buf already allocated";

        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        hsa_status_t status = alloc_cb(&trace_control_buf, size, flags, userdata);
        if (status != HSA_STATUS_SUCCESS)
            throw std::string("Memory callback returned error");
        trace_control_buf_size = size;
    }

    static std::shared_ptr<MemoryManager> CreateManager(
        hsa_agent_t agent,
        aqlprofile_memory_alloc_callback_t alloc,
        aqlprofile_memory_dealloc_callback_t dealloc,
        void* data
    ) {
        auto shared = std::make_shared<MemoryManager>(agent, alloc, dealloc, data);
        {
            std::lock_guard<std::mutex> lk(managers_map_mutex);
            managers[shared->handle] = shared;
        }
        return shared;
    }

    static void DeleteManager(size_t handle)
    {
        std::lock_guard<std::mutex> lk(managers_map_mutex);
        managers.erase(handle);
    }

    static std::shared_ptr<MemoryManager> GetManager(size_t handle)
    {
        std::lock_guard<std::mutex> lk(managers_map_mutex);
        return managers.at(handle);
    }

protected:
    hsa_agent_t agent;
    std::vector<aqlprofile_pmc_event_t> events;
    std::vector<hsa_ven_amd_aqlprofile_parameter_t> att_params;

    void* cmdbuf = nullptr;
    size_t cmdbuf_size = 0;
    void* outputbuf = nullptr;
    size_t outputbuf_size = 0;
    void* trace_control_buf = nullptr;
    size_t trace_control_buf_size = 0;

    void* const userdata;
    aqlprofile_memory_alloc_callback_t const alloc_cb;
    aqlprofile_memory_dealloc_callback_t const dealloc_cb;
    size_t handle;

    static std::atomic<size_t> HANDLE_COUNTER;
    static std::unordered_map<size_t, std::shared_ptr<MemoryManager>> managers;
    static std::mutex managers_map_mutex;
};