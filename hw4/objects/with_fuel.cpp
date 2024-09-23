#include "with_fuel.hpp"

#include "object.hpp"
#include "properties/fuel_consumption.hpp"
#include <properties/fuel.hpp>

namespace game::objects {


WithFuel::WithFuel(const std::shared_ptr<Object> &_object) :
    object{ _object }
{ }

double WithFuel::fuel() const
{
    return object->get<property::Fuel>().asDouble();
}

void WithFuel::fuel(double _value) 
{
    return object->get<property::Fuel>().set(_value);
}

double WithFuel::fuelConsumption() const
{
    return object->get<property::FuelConsumption>().asDouble();
}

}