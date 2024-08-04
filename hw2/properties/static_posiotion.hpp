#pragma once

#include "position.hpp"


namespace game::property {

// ro in polar system.
class StaticPosition : public Property, public Number<4>
{
public:
    StaticPosition(Property::Pointer _position) noexcept;
    StaticPosition(StaticPosition &&) noexcept;
    ~StaticPosition() = default;

    double asDouble() const override; 

    void set(double _value) override;

private:
    Property::Pointer position;
};

}