#include "position.hpp"


namespace game::property {

Position::Position(const Value &_value) noexcept :
    value{ _value }
{ }

double Position::asDouble() const
{
    return value;
}

void Position::set(double _value) 
{
    value = _value;
}

}