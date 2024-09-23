#pragma once

#include "properties/property.hpp"


namespace game::property {

class FuelConsumption : public Property
{
public:
    using Value = double;

    FuelConsumption(Value _value) noexcept;
    ~FuelConsumption() = default;

    double asDouble() const override;

    void set(double) override;

private:
    Value value;
};

}