#include <gtest/gtest.h>

#include <objects/factory.hpp>

#include <commands/move.hpp>
#include <commands/rotate.hpp>
#include <utils/convert.hpp>

#include <math.h>
#include <limits>
#include <numbers>


using namespace game;

constexpr auto error = 0.1;
constexpr auto directionsNumber{ 120U };


void invoker(const std::shared_ptr<Command> &_command)
{
    _command->execute();
}

TEST(Game, MoveObject)
{
    objects::Factory factory{ directionsNumber };
    auto [velocity, direction] = utils::convertToPolar(-7.0, 3.0, directionsNumber);
    auto [ro, positionAngle] = utils::convertToPolar(12.0, 5.0, directionsNumber);
    double velocityAngle = 1.0;
    auto ship = factory.createShip("ship1", ro, 
                                            positionAngle,
                                            velocity,
                                            direction,
                                            velocityAngle);

    objects::Movable movableShip{ ship };
    auto moveCmd{ std::make_shared<command::Move>(movableShip) };

    EXPECT_NO_THROW(invoker(moveCmd));

    auto roNew = ship->get<property::Position>().asDouble();
    auto positionAngleNew = ship->get<property::PositionAngle>().asDouble();
    auto [shipX, shipY] = utils::convertFromPolar(roNew, positionAngleNew, directionsNumber);

    EXPECT_NEAR(shipX, 5.0, error);
    EXPECT_NEAR(shipY, 8.0, error);
}

TEST(Game, TuuretCannotMove)
{
    objects::Factory factory{ directionsNumber };
    auto direction{ property::PositionAngle{ 12.0 } };
    auto [ro, positionAngle] = utils::convertToPolar(12.0, 5.0, directionsNumber);
    auto ship = factory.createTurret("ship1", 
                                     ro,
                                     positionAngle,
                                     60.0 / directionsNumber);

    objects::Movable movableShip{ ship };
    auto moveCmd{ std::make_shared<command::Move>(movableShip) };

    EXPECT_ANY_THROW(invoker(moveCmd));
}

TEST(Game, Rotatable)
{
    objects::Factory factory{ directionsNumber };
    auto [velocity, direction] = utils::convertToPolar(-7.0, 3.0, directionsNumber);
    auto [ro, positionAngle] = utils::convertToPolar(12.0, 5.0, directionsNumber);
    double velocityAngle = 1.0;
    auto ship = factory.createShip("ship1", ro, 
                                            positionAngle,
                                            velocity,
                                            direction,
                                            velocityAngle);

    objects::Rotatable rotatableShip{ ship };
    auto rotateCmd{ std::make_shared<command::Rotate>(rotatableShip) };

    invoker(rotateCmd);

    auto directionNew = ship->get<property::Direction>().asDouble();

    EXPECT_NEAR(directionNew, direction + velocityAngle, error);
}