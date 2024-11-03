#pragma once

#include "command/command.hpp"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>


namespace game::rooms {

class Storage {
    void add(uint64_t _id, std::unique_ptr<command::Command> _command);

    std::vector<std::unique_ptr<command::Command>> next();

private:
    std::mutex m;
    std::unordered_map<uint64_t, std::vector<std::unique_ptr<command::Command>>> commands;
};

}