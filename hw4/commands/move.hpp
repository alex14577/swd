#pragma once

#include "command.hpp"

#include <objects/movable.hpp>


namespace game::command {

class Move : public Command {
public:
    Move(objects::Movable _object);

    void execute() override;

private:
    objects::Movable object;
};

}