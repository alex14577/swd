#include "position_angle.hpp"


namespace game::property {

PositionAngle::PositionAngle(Value _value) noexcept :
    value{ _value }
{ }

double PositionAngle::asDouble() const
{
    return value;
}

void PositionAngle::set(double _value)
{
    value = _value;
}

}