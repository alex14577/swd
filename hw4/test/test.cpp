
#include "commands/burn_fuel.hpp"
#include "commands/check_fuel.hpp"
#include "objects/with_fuel.hpp"
#include "properties/fuel.hpp"
#include "gtest/gtest.h"

#include <macro_commands/factory.hpp>
#include <memory>
#include <utils/convert.hpp>
#include <objects/factory.hpp>
#include <commands/command.hpp>


using namespace game;

constexpr auto directionsNumber{ 120U };

void invoker(const std::shared_ptr<Command> &_command)
{
    _command->execute();
}

auto createShip(double _fuel, double _fuelConsumption) 
{
    objects::Factory factory{ directionsNumber };
    auto [velocity, direction] = utils::convertToPolar(-7.0, 3.0, directionsNumber);
    auto [ro, positionAngle] = utils::convertToPolar(12.0, 5.0, directionsNumber);
    double velocityAngle = 1.0;

    auto ship = factory.createShip("ship1", ro, 
                                            positionAngle,
                                            velocity,
                                            direction,
                                            velocityAngle,
                                            _fuel,
                                            _fuelConsumption);
    return  ship;
}

TEST(Command, CheckFuelSuccess)
{
    auto ship = createShip(100, 5);

    objects::WithFuel withFuel(ship);

    auto checkFuel = std::make_shared<command::CheckFuel>(withFuel);

    EXPECT_NO_THROW(invoker(checkFuel));
}

TEST(Command, CheckFuelFail)
{
    auto ship = createShip(4, 5);

    objects::WithFuel withFuel(ship);

    auto checkFuel = std::make_shared<command::CheckFuel>(withFuel);

    EXPECT_ANY_THROW(invoker(checkFuel));
}

TEST(Command, BurnFuel)
{
    auto ship = createShip(100, 5);

    objects::WithFuel withFuel(ship);

    auto burnFuel = std::make_shared<command::BurnFuel>(withFuel);

    EXPECT_NO_THROW(invoker(burnFuel));

    EXPECT_EQ(ship->get<property::Fuel>().asDouble(), 100 - 5);
}

TEST(Command, BurnFuelFail)
{
    auto ship = createShip(4, 5);

    objects::WithFuel withFuel(ship);

    auto burnFuel = std::make_shared<command::BurnFuel>(withFuel);

    EXPECT_NO_THROW(invoker(burnFuel));

    EXPECT_EQ(ship->get<property::Fuel>().asDouble(), 4);
}

TEST(MacroCommand, MoveSuccess)
{
    auto ship = createShip(100, 5);

    macro_command::Factory macroCommands(ship);

    auto move = macroCommands.createMove();

    auto fuelBalance = ship->get<property::Fuel>().asDouble();
    EXPECT_EQ(fuelBalance, 100.0);

    EXPECT_NO_THROW(invoker(move));

    fuelBalance = ship->get<property::Fuel>().asDouble();

    EXPECT_EQ(fuelBalance, 100.0 - 5.0);
}

TEST(MacroCommand, MoveFail)
{
    auto ship = createShip(4, 5);

    macro_command::Factory macroCommands(ship);

    auto move = macroCommands.createMove();

    auto fuelBalance = ship->get<property::Fuel>().asDouble();
    EXPECT_EQ(fuelBalance, 4.0);

    EXPECT_ANY_THROW(invoker(move));
}