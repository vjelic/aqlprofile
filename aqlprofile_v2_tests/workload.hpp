#pragma once

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include "counter.hpp"
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <atomic>
#include <future>
#include "agent.hpp"

class IWorkload
{
public:
    IWorkload() {}
    virtual ~IWorkload() {};
    virtual void run() = 0;
};

class Collection
{
public:
    Collection(AgentInfo& agent, const std::vector<std::string>& counters);
    virtual ~Collection();

    std::map<std::string, int64_t> iterate(Queue& queue, IWorkload& load);

private:
    void start(Queue& queue);
    void stop(Queue& queue);
    std::unique_ptr<AQLPacket> packet{nullptr};
};
