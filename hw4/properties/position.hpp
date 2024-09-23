#pragma once

#include "property.hpp"


namespace game::property {

// ro in polar system.
class Position : public Property
{
public:
    using Value = double;

    Position(const Value &_value) noexcept;
    ~Position() = default;

    Value asDouble() const override;

    void set(double _value) override;

protected:
    Value value;
};

}