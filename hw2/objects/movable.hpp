#pragma once

#include <memory>


namespace game::objects {

class Object;

class Movable {
public:
    Movable(const std::shared_ptr<Object> &_object);

    double position() const;
    void position(double _ro);
    
    double velocity() const;
    double direction() const;

    double positionAngle() const;
    void positionAngle(double);

    std::size_t directionsNumber() const;

private:
    std::shared_ptr<Object> object;
};

}