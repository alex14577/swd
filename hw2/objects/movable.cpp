#include "movable.hpp"
#include "object.hpp"

#include <properties/position.hpp>
#include <properties/velocity.hpp>
#include <properties/position_angle.hpp>
#include <properties/directions_number.hpp>
#include <properties/direction.hpp>

namespace game::objects {

Movable::Movable(const std::shared_ptr<objects::Object> &_object) :
    object{ _object }
{ }

double Movable::position() const
{
    auto &position{ object->get<property::Position>() };
    return position.asDouble();
}

void Movable::position(double _ro)
{
    auto &position{ object->get<property::Position>() };
    position.set(_ro);
}

double Movable::velocity() const
{
    auto &velocity{ object->get<property::Velocity>() };
    return velocity.asDouble();
}

double Movable::positionAngle() const
{
    return object->get<property::PositionAngle>().asDouble();
}

void Movable::positionAngle(double _value) 
{
    object->get<property::PositionAngle>().set(_value);
}

double Movable::direction() const
{
    return object->get<property::Direction>().asDouble();
}

std::size_t Movable::directionsNumber() const
{
    return object->get<property::DirectionsNumber>().asNumeric();
}

}