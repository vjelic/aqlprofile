#include "memorymanager.hpp"
#include <algorithm>

std::atomic<size_t> MemoryManager::HANDLE_COUNTER{1};
std::unordered_map<size_t, std::shared_ptr<MemoryManager>> MemoryManager::managers;
std::mutex MemoryManager::managers_map_mutex;

void CounterMemoryManager::CopyEvents(const aqlprofile_pmc_event_t* _events, size_t count)
{
    events.reserve(count+4);
    for (size_t i=0; i<count; i++)
        events.push_back(EventRequest{_events[i], nullptr, false});

    std::sort(events.begin(), events.end());

    std::vector<EventRequest> acc_requests;
    for (auto it = events.begin(); it != events.end(); it++)
    {
        if (!it->flags.raw) continue;

        if (it != events.begin())
        {
            auto prev = std::prev(it);
            if (it->IsSameNoFlags(*prev) && (!prev->flags.raw || prev->bInserted))
                continue;
        }

        EventRequest req = *it;
        req.bInserted = true;
        acc_requests.push_back(req);
    }

    if (!acc_requests.size()) return;

    events.insert(events.end(), acc_requests.begin(), acc_requests.end());
    std::sort(events.begin(), events.end());
}
