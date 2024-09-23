#include "macro_command.hpp"
#include "commands/command.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace game {

MacroCommand::MacroCommand(std::vector<std::shared_ptr<Command>> _commands) :
    commands{ _commands }
{ }

void MacroCommand::execute()
{
    std::ranges::for_each(commands, [](auto &command) {
                                              command->execute();
                                          });
}
}