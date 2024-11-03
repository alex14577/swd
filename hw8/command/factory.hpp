#pragma once

#include "command/command.hpp"
#include "message.hpp"
#include <memory>
#include <unordered_map>
#include "functional"
#include "object/object.hpp"

namespace game::roting {

class Factory {
    virtual ~Factory() = default;

    void resolve(const Message &_message);

    template<typename Command, typename Creator>
    void add(Creator _creator) {
        fabrics[Command::name] = _creator;
    }

private:
    using CmdPtr = std::shared_ptr<command::Command>;
    std::unordered_map<std::string, std::function<CmdPtr(command::Command::Args)>> fabrics;

    std::unordered_map<uint64_t, std::shared_ptr<object::Object>> objectStorage;
};

}