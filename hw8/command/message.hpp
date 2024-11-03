#pragma once

#include <cstdint>
#include <string>


namespace game {

struct Message {
    uint64_t gameId;
    uint64_t objectId;
    std::string command;
    std::string args;
};

}