#include <stdexcept>

#include "quadratic.hpp"


namespace solver {


auto Quadratic::process(const details::Number &_a,
                        const details::Number &_b, 
                        const details::Number &_c) -> std::vector<details::Number>
{
    if (!_a.isValid()) {
        throw std::runtime_error("Coefficient 'a' is not valid"); 
    } 
    if (!_b.isValid()) {
        throw std::runtime_error("Coefficient 'b' is not valid"); 
    } 
    if (!_c.isValid()) {
        throw std::runtime_error("Coefficient 'c' is not valid"); 
    }
    if (_a == 0) {
        throw std::runtime_error("Coefficient 'a' can not be a zero"); 
    }

    auto a = _a.value();
    auto b = _b.value();
    auto c = _c.value();

    details::Number discriminant { b * b - 4 *a * c };

    if(discriminant < 0) {
        return {};
    } else if (discriminant == 0) {
        auto root = -b / 2 * a * c;
        return {root, root};
    } else {
        auto discriminantSqrt = discriminant.sqrt().value();
        auto root1 = (-b + discriminantSqrt) / 2 * a * c;
        auto root2 =  (-b - discriminantSqrt) / 2 * a * c;
        return { root1, root2 };
    }
}

} // namespace solver.