#include "static_posiotion.hpp"

#include <exception>

namespace game::property {

StaticPosition::StaticPosition(Property::Pointer _position) noexcept :
    position{ std::move(_position) }
{ }

StaticPosition::StaticPosition(StaticPosition &&_other) noexcept :
    position{ std::move(_other.position) }
{ }


double StaticPosition::asDouble() const
{
    return position->asDouble();
}

void StaticPosition::set(double _value) 
{
    throw std::runtime_error("Can not change static poosition");
}

}