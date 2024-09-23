#include "burn_fuel.hpp"

#include <cmath>
#include <limits>
#include <utility>

namespace game::command {

BurnFuel::BurnFuel(objects::WithFuel _object) :
    object{ _object }
{ }

void BurnFuel::execute() 
{
    auto fuelConsumption = object.fuelConsumption();
    auto fuel = object.fuel();
    auto balance = fuel - fuelConsumption;

    if( balance > 0) {
        object.fuel(balance);
    }
}

}
