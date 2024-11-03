#include "factory.hpp"
#include "command/command.hpp"
#include "command/PluginExecutor.hpp"
#include "command/workerStop.hpp"
#include <memory>


namespace cms::command {

Factory::Factory(const module::Plugin &_plugin, worker::Worker *_worker, const std::vector<QueuePtr> &_queuesOut) :
    plugin{ _plugin },
    worker{ _worker },
    queues{ _queuesOut }
{
    fabrics["construct"] = [this](Message &_message) {
        assert(_message.data);
        return std::make_shared<PluginExecutor>(plugin, _message.data.value(), queues);
    };
    fabrics["stop"] = [this](const Message &) {
        return std::make_shared<WorkerStop>(worker);
    };
}


std::shared_ptr<Interface> Factory::create(Message &_command)
{
    auto it = fabrics.find(_command.name);
    if(it != fabrics.end()){    
        return it->second(_command);
    }

    return  nullptr;
}

}
