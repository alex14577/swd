#pragma once

#include "command.hpp"

#include <objects/with_fuel.hpp>


namespace game::command {

class CheckFuel : public Command {
public:
    CheckFuel(objects::WithFuel _object);

    void execute() override;

private:
    objects::WithFuel object;
};

}