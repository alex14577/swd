#pragma once

#include "command.hpp"

namespace game::command {

class SetSpeed : public Command {
public:
    ~SetSpeed() = default;

    static constexpr std::string_view name = "SetSpeed";

    void execute();

};

}