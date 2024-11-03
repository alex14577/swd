#pragma once

#include "factory.hpp"
#include "command/command.hpp"

namespace game::roting {

void Factory::resolve(const Message &_message)
{
    command::Command::Args args;

    args["object"] = objectStorage[_message.objectId];
    args["args"] = _message.args;
}

}