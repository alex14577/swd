#include "factory.hpp"
#include "properties/fuel.hpp"
#include "properties/fuel_consumption.hpp"

#include <properties/static_posiotion.hpp>

namespace game::objects {

Factory::Factory(property::DirectionsNumber _directionsNumber) noexcept :
    directionsNumber{ _directionsNumber }
{ }

Object::Pointer Factory::createShip(std::string _name,
                                    property::Position _position,
                                    property::PositionAngle _positionAngle,
                                    property::Velocity _velocity,
                                    property::Direction _direcrion,
                                    property::VelocityAngle _velocityAngle,
                                    property::Fuel _fuel,
                                    property::FuelConsumption _fuelConsumption) const
{
    using namespace property;
    auto result = std::make_shared<Object>(std::move(_name));
    result->add<Position>(std::move(_position));
    result->add<PositionAngle>(std::move(_positionAngle));
    result->add<Velocity>(std::move(_velocity));
    result->add<Direction>(std::move(_direcrion));
    result->add<VelocityAngle>(std::move(_velocityAngle));
    result->add<DirectionsNumber>(std::move(directionsNumber));
    result->add<Fuel>(std::move(_fuel));
    result->add<FuelConsumption>(std::move(_fuelConsumption));
    return result;
}


Object::Pointer Factory::createTurret(std::string _name,
                                      property::Position _position,
                                      property::PositionAngle _positionAngle,
                                      property::Direction _direction) const
{
    using namespace property;

    auto positionPtr = std::make_unique<Position>(std::move(_position));

    auto staticPosition{ StaticPosition{ std::move(positionPtr) } };

    auto result = std::make_shared<Object>(std::move(_name));
    result->add<StaticPosition>(std::move(staticPosition));
    result->add<PositionAngle>(std::move(_positionAngle));
    result->add<Direction>(std::move(_direction));
    result->add<DirectionsNumber>(std::move(directionsNumber));
    return result;
}

}