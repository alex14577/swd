#include "direction.hpp"

namespace game::property {


Direction::Direction(double _value) :
    value{ _value }
{ }

double Direction::asDouble() const
{
    return value;
}

void Direction::set(double _value)
{
    value = _value;
}

}