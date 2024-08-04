#include "directions_number.hpp"


namespace game::property {

DirectionsNumber::DirectionsNumber(std::size_t _value) noexcept:
    value{ _value }
{ }

std::size_t DirectionsNumber::asNumeric() const
{
    return value;
}

void DirectionsNumber::set(std::size_t _value)
{
    value = _value;
}

}