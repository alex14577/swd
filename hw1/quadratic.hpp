#pragma once

#include "details.hpp"

#include <vector>

namespace solver {

class Quadratic {
public:
    std::vector<details::Number> process(const details::Number &a, 
                                         const details::Number &b, 
                                         const details::Number &c);
};

} // namespace solver. 