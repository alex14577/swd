#include "fuel.hpp"

namespace game::property {

Fuel::Fuel(Value _value) noexcept :
    value{ _value }
{ }


double Fuel::asDouble() const
{
    return value;
}

void Fuel::set(double _value) 
{
    value = _value;
}

}