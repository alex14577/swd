#pragma once

#include <memory>


namespace game::objects {

class Object;

class Rotatable {
public:
    Rotatable(const std::shared_ptr<Object> &);

    double velocityAngle() const;
    void velocityAngle(double);
    
    double direction() const;
    void direction(double);

private:
    std::shared_ptr<Object> object;
};

}