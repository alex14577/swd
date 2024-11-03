#include "storage.hpp"
#include <mutex>


namespace game::rooms {


void Storage::add(uint64_t _id, std::unique_ptr<command::Command> _command)
{
    std::lock_guard lc(m);

    commands[_id].push_back(std::move(_command));
}

std::vector<std::unique_ptr<command::Command>> Storage::next()
{
    auto [_, res] = std::move(*commands.begin());

    return res;
}

}