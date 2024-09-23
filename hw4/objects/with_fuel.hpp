#pragma once

#include "memory"

namespace game::objects {

class Object;

class WithFuel {
public:
    WithFuel(const std::shared_ptr<Object> &);

    double fuelConsumption() const;

    double fuel() const;
    void fuel(double);

private:
    std::shared_ptr<Object> object;
};

}