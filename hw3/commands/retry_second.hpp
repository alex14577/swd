#pragma once

#include "command.hpp"

namespace game::command {

class RetrySecond : public Interface  {
public:
    RetrySecond(const Interface::Ptr &_cmd);

    void execute() override;

private:
    Interface::Ptr cmd;
};

}