#pragma once

#include <commands/command.hpp>
#include <initializer_list>
#include <memory>
#include <vector>

namespace game {

class MacroCommand : public Command {
public:
    MacroCommand(std::vector<std::shared_ptr<Command>> _commands);

    void execute();

private:
    std::vector<std::shared_ptr<Command>> commands;

};

}