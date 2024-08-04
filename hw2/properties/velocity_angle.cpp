#include "velocity_angle.hpp"


namespace game::property {

VelocityAngle::VelocityAngle(const double _value) noexcept :
    value{ _value }
{ }

double VelocityAngle::asDouble() const
{
    return value;
}

void VelocityAngle::set(double _value) 
{
    value = _value;
}

}