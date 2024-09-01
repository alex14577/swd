#include "check_fuel.hpp"


namespace game::command {

CheckFuel::CheckFuel(objects::WithFuel _object) :
    object{ _object }
{ }

void CheckFuel::execute()
{
    auto fuelConsumption = object.fuelConsumption();
    auto fuel = object.fuel();

    if( fuel - fuelConsumption < 0.0 ){
        throw std::runtime_error("No fuel");
    }
}

}