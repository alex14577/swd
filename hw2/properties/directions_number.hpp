#pragma once

#include <memory>

#include "property.hpp"


namespace game::property {

class DirectionsNumber : public Property, public Number<1>
{
public:
    DirectionsNumber(std::size_t _value) noexcept;

    ~DirectionsNumber() = default;

    std::size_t asNumeric() const override;

    void set(std::size_t _value) override;

private:
    std::size_t value;
};

}