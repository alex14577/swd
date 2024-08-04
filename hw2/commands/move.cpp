#include "move.hpp"

#include <utils/convert.hpp>

#include <math.h>
#include <numeric>

namespace game::command {

Move::Move(objects::Movable _object) :
    object{ std::move(_object) }
{ }

void Move::execute() 
{
    auto velocity = object.velocity();
    auto direction = object.direction();
    auto ro = object.position();
    auto positionAngle = object.positionAngle();
    auto directionsNumber = object.directionsNumber();

    auto [positionXOld, positionYOld] = utils::convertFromPolar(ro, positionAngle, directionsNumber);
    auto [velocityXOld, velocityYOld] = utils::convertFromPolar(velocity, direction, directionsNumber);

    auto positionXNew = positionXOld + velocityXOld;
    auto positionYNew = positionYOld + velocityYOld;

    auto [roNew, positionAngleNew] = utils::convertToPolar(positionXNew, positionYNew, directionsNumber);

    object.position(roNew);
    object.positionAngle(positionAngleNew);
}


}