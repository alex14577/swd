#pragma once

#include "property.hpp"


namespace game::property {

class VelocityAngle : public Property {
public:
    VelocityAngle() = delete;
    VelocityAngle(double _value) noexcept;

    void set(double );
    double asDouble() const;

private:
    double value;
};

}