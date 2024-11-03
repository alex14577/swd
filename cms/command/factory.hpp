#pragma once


#include "command/command.hpp"
#include "modules/module.hpp"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace cms::worker {
class Worker;
}

namespace cms::command {

class Factory {
public:
    Factory(const module::Plugin &_plugin, worker::Worker *_worker, const std::vector<QueuePtr> &_queuesOut);

    std::shared_ptr<Interface> create(Message &_command);

private:
    module::Plugin plugin;
    worker::Worker *worker;
    const std::vector<QueuePtr> &queues;
    
    using Creator = std::function<std::shared_ptr<Interface>(Message &_command)>;
    std::unordered_map<std::string, Creator> fabrics;
};

}