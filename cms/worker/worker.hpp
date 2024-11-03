#pragma once

#include "command/command.hpp"
#include <command/factory.hpp>
#include "modules/module.hpp"

#include <atomic>
#include <thread>
#include <vector>

namespace cms::worker {

class Worker {
public:
    Worker(Worker &&_other) = delete;
    Worker(const Worker &_other) = delete;
    Worker(const module::Plugin &_plugin, const command::QueuePtr &_queueIn, const std::vector<command::QueuePtr> &_queuesOut) noexcept;

    std::string &name() const noexcept;

    void start();
    
    void stop();

    void wait();

private:
    void runner();

    module::Plugin plugin;

    command::QueuePtr queueIn;

    std::atomic_flag needStop{false};
    std::atomic_flag stopped{false};

    std::thread thread;
    command::Factory cmdFactory;
};

}