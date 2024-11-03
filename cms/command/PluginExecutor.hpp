#pragma once

#include "command.hpp"

#include "modules/module.hpp"

#include <string>

namespace cms::command {

class PluginExecutor final : public Interface {
public:
    PluginExecutor(const module::Plugin &_plugin, std::string &_input, const std::vector<QueuePtr> &_queuesOut);
    ~PluginExecutor() = default;
    void execute() override;

private:
    module::Plugin plugin;
    std::string input;
    const std::vector<QueuePtr> &queuesOut;
};

}