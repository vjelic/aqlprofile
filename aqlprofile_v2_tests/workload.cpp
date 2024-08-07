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
#include "workload.hpp"
#include "counter.hpp"

Collection::Collection(AgentInfo& agent, const std::vector<std::string>& counters)
    : packet(std::make_unique<AQLPacket>(agent, counters)) {}

Collection::~Collection() {}

std::map<std::string, int64_t> Collection::iterate(Queue& queue, IWorkload& load)
{
    start(queue);
    load.run();
    stop(queue);
    return packet->get();
}

void Collection::start(Queue& queue)
{
    assert(packet);
    queue.flush();
    queue.Submit(&packet->packets.start_packet);
}

void Collection::stop(Queue& queue)
{
    assert(packet);
    queue.flush();

    queue.Submit(&packet->packets.read_packet);
    queue.Submit(&packet->packets.stop_packet);
    packet->iterate();
}
