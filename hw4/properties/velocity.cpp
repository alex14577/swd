#include "velocity.hpp"

namespace game::property {

Velocity::Velocity(const double _value) noexcept :
    value{ _value }
{ }

double Velocity::asDouble() const
{
    return value;
}

void Velocity::set(double _value) 
{
    value = _value;
}

}