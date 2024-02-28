#include "memorymanager.hpp"

std::atomic<size_t> MemoryManager::HANDLE_COUNTER{1};
std::unordered_map<size_t, std::shared_ptr<MemoryManager>> MemoryManager::managers;
std::mutex MemoryManager::managers_map_mutex;