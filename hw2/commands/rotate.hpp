#pragma once

#include "command.hpp"

#include <objects/rotatable.hpp>

namespace game::command {

class Rotate : public Command {
public:
    Rotate(objects::Rotatable _object);

    void execute() override;

private:
    objects::Rotatable object;
};

}