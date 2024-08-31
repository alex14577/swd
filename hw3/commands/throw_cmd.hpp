#pragma once

#include "command.hpp"

namespace game::command {

class Throwing : public Interface  {
public:
    Throwing();

    void execute() override;

};

}