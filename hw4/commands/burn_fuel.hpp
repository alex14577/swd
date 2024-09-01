#pragma once

#include "command.hpp"

#include <objects/with_fuel.hpp>


namespace game::command {

class BurnFuel : public Command {
public:
    BurnFuel(objects::WithFuel _object);

    void execute() override;

private:
    objects::WithFuel object;
};

}