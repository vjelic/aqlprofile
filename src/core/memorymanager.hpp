#pragma once
#include <vector>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <memory>
#include "include/aql_profile_v2.h"

struct EventRequest: public aqlprofile_pmc_event_t
{
    void* loc;
    bool bInserted;

    auto GetOrder() const -> auto {
        uint64_t idx{0}, blk{0};
        idx |= bInserted ? 0 : 1;
        idx |= uint64_t(flags.raw)<<1;
        idx |= uint64_t(event_id) << 33;
        blk |= uint64_t(block_index);
        blk |= uint64_t(block_name) << 32;

        return std::pair<uint64_t, uint64_t>{blk, idx};
    }

    bool operator<(const EventRequest& other) const {
        auto idx1 = this->GetOrder();
        auto idx2 = other.GetOrder();
        if (idx1.first == idx2.first) return idx1.second < idx2.second;
        else return idx1.first < idx2.first;
    }

    bool operator==(const EventRequest& other) const {
        auto idx1 = this->GetOrder();
        auto idx2 = other.GetOrder();
        return idx1.second == idx2.second && idx1.first == idx2.first;
    }

    bool IsSameNoFlags(const EventRequest& other) const {
        auto idx1 = this->GetOrder();
        auto idx2 = other.GetOrder();
        return idx1.first == idx2.first && event_id == other.event_id;
    }
};

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

    virtual ~MemoryManager() {}

    void CheckStatus(hsa_status_t status) const { if (status != HSA_STATUS_SUCCESS) throw status; }

    void* GetCmdBuf() const { return cmdbuf.get(); }
    void* GetOutputBuf() const { return outputbuf.get(); }

    size_t GetOutputBufSize() const { return outputbuf_size; }

    size_t GetHandler() const { return handle; }
    hsa_agent_t GetAgent() const { return agent; }

    void CreateCmdBuf(size_t size)
    {
        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        cmdbuf = AllocMemory(size, flags);
    }

    virtual void CreateOutputBuf(size_t size) = 0;

    static void RegisterManager(const std::shared_ptr<MemoryManager>& shared)
    {
        std::lock_guard<std::mutex> lk(managers_map_mutex);
        managers[shared->handle] = shared;
    }

    static void DeleteManager(size_t handle)
    {
        std::lock_guard<std::mutex> lk(managers_map_mutex);
        managers.erase(handle);
    }

    static std::shared_ptr<MemoryManager> GetManager(size_t handle)
    {
        std::lock_guard<std::mutex> lk(managers_map_mutex);
        try {
            return managers.at(handle);
        } catch(std::out_of_range& e) {
            return nullptr;
        }
    }

protected:
    struct MemoryDeleter
    {
        aqlprofile_memory_dealloc_callback_t free_fn;
        void* userdata;
        void operator()(void* ptr) const { if (ptr && free_fn) free_fn(ptr, userdata); };
    };

    std::unique_ptr<void, MemoryDeleter>
    AllocMemory(size_t size, aqlprofile_buffer_desc_flags_t flags) const
    {
        void* ptr;
        CheckStatus(alloc_cb(&ptr, size, flags, userdata));
        return std::unique_ptr<void, MemoryDeleter>{ptr, MemoryDeleter{dealloc_cb, userdata}};
    }

    hsa_agent_t agent;
    std::unique_ptr<void, MemoryDeleter> cmdbuf = nullptr;
    std::unique_ptr<void, MemoryDeleter> outputbuf = nullptr;
    size_t outputbuf_size = 0;

    void* const userdata;
    aqlprofile_memory_alloc_callback_t const alloc_cb;
    aqlprofile_memory_dealloc_callback_t const dealloc_cb;
    size_t handle;

    static std::atomic<size_t> HANDLE_COUNTER;
    static std::unordered_map<size_t, std::shared_ptr<MemoryManager>> managers;
    static std::mutex managers_map_mutex;
};

class CounterMemoryManager: public MemoryManager
{
public:
    CounterMemoryManager(
        hsa_agent_t agent,
        aqlprofile_memory_alloc_callback_t alloc,
        aqlprofile_memory_dealloc_callback_t dealloc,
        void* data
    ): MemoryManager(agent, alloc, dealloc, data) {}

    void CreateOutputBuf(size_t size) override
    {
        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        outputbuf = AllocMemory(size, flags);
        outputbuf_size = size;
    }

    const std::vector<EventRequest>& GetEvents() const { return events; }
    void CopyEvents(const aqlprofile_pmc_event_t* events, size_t count);

protected:
    std::vector<EventRequest> events;
};

class TraceMemoryManager: public MemoryManager
{
public:
    TraceMemoryManager(
        hsa_agent_t agent,
        aqlprofile_memory_alloc_callback_t alloc,
        aqlprofile_memory_dealloc_callback_t dealloc,
        void* data
    ): MemoryManager(agent, alloc, dealloc, data) {}

    void CreateOutputBuf(size_t size) override
    {
        aqlprofile_buffer_desc_flags_t flags{};
        flags.device_access = true;
        outputbuf = AllocMemory(size, flags);
        outputbuf_size = size;
    }

    void CreateTraceControlBuf(size_t size)
    {
        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        trace_control_buf = AllocMemory(size, flags);
    }

    [[nodiscard]] void* AddMarkerCmdBuffer(size_t size)
    {
        aqlprofile_buffer_desc_flags_t flags{};
        flags.host_access = flags.device_access = true;
        this->marker_cmd_buffer.emplace_back(AllocMemory(size, flags));
        return this->marker_cmd_buffer.back().get();
    }

    const std::vector<hsa_ven_amd_aqlprofile_parameter_t>& GetATTParams() const { return att_params; }
    void CopyATTParams(hsa_ven_amd_aqlprofile_parameter_t* params, size_t count) {
        for (size_t i=0; i<count; i++)
            this->att_params.push_back(params[i]);
    }

    template<typename Type> Type*
    GetTraceControlBuf() const { return reinterpret_cast<Type*>(trace_control_buf.get()); }

protected:
    std::vector<hsa_ven_amd_aqlprofile_parameter_t> att_params;

    std::unique_ptr<void, MemoryDeleter> trace_control_buf = nullptr;
    std::vector<std::unique_ptr<void, MemoryDeleter>> marker_cmd_buffer;
};
