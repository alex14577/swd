#pragma once

#include <memory>
#include <object/object.hpp>
#include <unordered_map>
#include "variant"

namespace game::command {

class Command {
public:
    using Arg = std::variant<std::string, std::shared_ptr<object::Object>>;
    using Args = std::unordered_map<std::string, Arg>;

    virtual ~Command() = default;

    Command(Args _args) : 
        args{ std::move(_args) }
    { }

    virtual void execute() = 0;

protected:
    Args args;
};


}