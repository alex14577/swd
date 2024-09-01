#include "fuel_consumption.hpp"

namespace game::property {

FuelConsumption::FuelConsumption(Value _value) noexcept :
    value{ _value }
{ }

double FuelConsumption::asDouble() const
{
    return value;
}

void FuelConsumption::set(double _value) 
{
    value = _value;
}

}