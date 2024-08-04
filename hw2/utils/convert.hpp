#pragma once

#include <utility>
#include <math.h>
#include <numbers>

namespace game::utils {

constexpr
std::pair<double, double> convertToPolar(double _x, double _y, std::size_t directionsNumber)
{
    constexpr auto pi = std::numbers::pi;
    auto angle = std::atan2(_y, _x) / (2.0 * pi) * static_cast<double>(directionsNumber);
    auto ro = std::sqrt(_x*_x + _y*_y);

    return std::make_pair(ro, angle);
}

constexpr
std::pair<double, double> convertFromPolar(double _ro, double _positionAngle, std::size_t directionsNumber)
{
    constexpr auto pi = std::numbers::pi;
    auto x{ _ro * std::cos(_positionAngle * (2.0 * pi ) / directionsNumber) };
    auto y{ _ro * std::sin(_positionAngle * (2.0 * pi ) / directionsNumber) };

    return std::make_pair(x, y);
}

}