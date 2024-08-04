#pragma once

#include <memory>

#include "property.hpp"


namespace game::property {

class Direction : public Property, public Number<0> {
public:
    Direction(double _value);

    double asDouble() const override;
    void set(double) override;

private:
    double value;
};

}