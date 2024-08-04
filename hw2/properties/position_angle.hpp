#pragma once

#include <memory>

#include "property.hpp"


namespace game::property {

// alfa in polar system.
class PositionAngle : public Property, public Number<2>
{
public:
    using Value = double;

    PositionAngle(Value _value) noexcept;
    ~PositionAngle() = default;

    double asDouble() const override;

    void set(double) override;

private:
    Value value;
};

}