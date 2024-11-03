#include "PluginExecutor.hpp"
#include "command/command.hpp"

namespace cms::command {

PluginExecutor::PluginExecutor(const module::Plugin &_plugin, std::string &_input, const std::vector<QueuePtr> &_queuesOut) :
    plugin{ _plugin },
    input{ std::move(_input) },
    queuesOut{ _queuesOut }
{ }

void PluginExecutor::execute()
{
    auto [routs, res] = plugin->execute(input);

    assert(routs.size() == res.size());

    auto idx = 0;
    for(const auto &rout : routs) {
        Message messageNext{.name = "construct", .data = std::move(res[idx])};

        auto q = std::ranges::find_if(queuesOut, [&rout](const auto &_queue) { return _queue->id() == rout;});
        if (q != queuesOut.end()) {
            (*q)->push(std::move(messageNext));
        }
        idx++;
    }
}

}