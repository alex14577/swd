#include "rotate.hpp"

#include <utils/convert.hpp>

#include <math.h>
#include <numeric>

namespace game::command {

Rotate::Rotate(objects::Rotatable _object) :
    object{ std::move(_object) }
{ }

void Rotate::execute() 
{
    auto direction = object.direction();
    auto velocityAngle = object.velocityAngle();

    auto directionNew = direction + velocityAngle;

    object.direction(directionNew);
}


}