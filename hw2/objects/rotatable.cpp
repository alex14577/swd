#include "rotatable.hpp"

#include "object.hpp"
#include <properties/velocity_angle.hpp>
#include <properties/direction.hpp>

namespace game::objects {

Rotatable::Rotatable(const std::shared_ptr<Object> &_object) :
    object{ _object }
{ }


double Rotatable::velocityAngle() const
{
    return object->get<property::VelocityAngle>().asDouble();
}

void Rotatable::velocityAngle(double _value)
{
    object->get<property::VelocityAngle>().set(_value);
}

double Rotatable::direction() const
{
    return object->get<property::Direction>().asDouble();
}

void Rotatable::direction(double _value)
{
    object->get<property::Direction>().set(_value);
}

}