#pragma once

#include "object.hpp"

#include <properties/position_angle.hpp>
#include <properties/directions_number.hpp>
#include <properties/position.hpp>
#include <properties/velocity.hpp>
#include <properties/direction.hpp>
#include <properties/velocity_angle.hpp>

namespace game::objects {

class Factory {
public:
    Factory(property::DirectionsNumber) noexcept;

    Object::Pointer createShip(std::string _name,
                               property::Position,
                               property::PositionAngle, 
                               property::Velocity,
                               property::Direction,
                               property::VelocityAngle) const;

    Object::Pointer createTurret(std::string _name,
                                 property::Position,
                                 property::PositionAngle,
                                 property::Direction) const;

private:
    property::DirectionsNumber directionsNumber;


};

}