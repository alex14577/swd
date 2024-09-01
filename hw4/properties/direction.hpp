#pragma once

#include "property.hpp"


namespace game::property {

class Direction : public Property {
public:
    Direction(double _value);

    double asDouble() const override;
    void set(double) override;

private:
    double value;
};

}