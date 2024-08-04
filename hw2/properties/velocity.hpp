#pragma once

#include "property.hpp"


namespace game::property {

class Velocity : public Property, public Number<6> {
public:
    Velocity() = delete;
    Velocity(double _value) noexcept;

    void set(double );
    double asDouble() const;

private:
    double value;
};

}