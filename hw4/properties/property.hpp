#pragma once

#include <memory>
#include <string>

#include <utils/type_index.hpp>


namespace game::property {

class Property {
public:
    using Pointer = std::unique_ptr<Property>;

    virtual ~Property() = default;

    virtual double asDouble() const { throw std::runtime_error("Property does not support 'DOUBLE' values"); };
    virtual void set(double) { throw std::runtime_error("Property does not support 'DOUBLE' values"); };

    virtual std::size_t asNumeric() const { throw std::runtime_error("Property does not support 'UNSIGNED' values"); };
    virtual void set(std::size_t) { throw std::runtime_error("Property does not support 'UNSIGNED' values"); };

    virtual int asInt() const { throw std::runtime_error("Property does not support 'INT' values"); };
    virtual void set(int) { throw std::runtime_error("Property does not support 'INT' values"); };
    
    virtual std::string asString() const { throw std::runtime_error("Property does not support 'STRING' values"); };
    virtual void set(std::string) { throw std::runtime_error("Property does not support 'STRING' values"); };
};

class Direction;
class DirectionsNumber;
class VelocityAngle;
class PositionAngle;
class Position;
class StaticPosition;
class Velocity;
class Fuel;
class FuelConsumption;

template<typename Property>
constexpr int id()
{
    using Storage = 
    type_index::IndexStorage<Direction, DirectionsNumber, VelocityAngle, 
                             DirectionsNumber, PositionAngle, Position, 
                             StaticPosition, Velocity, Fuel,
                             FuelConsumption>;

    constexpr auto result = Storage::get<Property>();

    static_assert(result != 0, "Property not added to storage");

    return result;
}

}