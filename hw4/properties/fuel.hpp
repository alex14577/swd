#pragma once

#include "properties/property.hpp"


namespace game::property {

class Fuel : public Property
{
public:
    using Value = double;

    Fuel(Value _value) noexcept;
    ~Fuel() = default;

    double asDouble() const override;

    void set(double) override;

private:
    Value value;
};

}