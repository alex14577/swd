#include "factory.hpp"
#include "macro_command.hpp"

#include <commands/command.hpp>
#include <commands/move.hpp>
#include <commands/rotate.hpp>
#include <commands/check_fuel.hpp>
#include <commands/burn_fuel.hpp>

#include <objects/movable.hpp>
#include <objects/rotatable.hpp>
#include <objects/with_fuel.hpp>

#include <memory>

namespace game::macro_command {

Factory::Factory(const std::shared_ptr<objects::Object> &_object) :
    object{ _object }
{ }

std::shared_ptr<Command> Factory::createMove() {
    objects::Movable movable(object);
    objects::WithFuel fueable(object);
    
    return std::make_shared<MacroCommand>(
        std::vector<std::shared_ptr<Command>>{std::make_shared<command::CheckFuel>(fueable),
                                              std::make_shared<command::Move>(object),
                                              std::make_shared<command::BurnFuel>(fueable)}
    );
}

}