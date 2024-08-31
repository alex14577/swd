#pragma once

#include "command.hpp"

namespace game::command {

class Retry : public Interface  {
public:
    Retry(const Interface::Ptr &_cmd);

    void execute() override;

private:
    Interface::Ptr cmd;
};

}