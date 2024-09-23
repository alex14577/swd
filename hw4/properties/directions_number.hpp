#pragma once

#include "property.hpp"


namespace game::property {

class DirectionsNumber : public Property
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