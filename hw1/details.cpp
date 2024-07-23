#include "details.hpp"

#include <cmath>
#include <limits>


namespace solver::details {

Number::Number(const Value _n) noexcept :
    n{ _n },
    epsilon{ std::numeric_limits<Value>::epsilon() }
{ }

Number::Number(const Value _n, const Value _epsilon) noexcept :
    n{ _n },
    epsilon{ _epsilon }
{ }

bool Number::operator<(const Number& _other) const noexcept
{
    return _other.n - n > epsilon;
}

bool Number::operator>(const Number& _other) const noexcept
{
    return !(*this < _other);
}

bool Number::operator==(const Number& _other) const noexcept
{
    return std::fabs(_other.n - n) < epsilon;
}

auto Number::value() const noexcept -> Value
{
    return n;
}

auto Number::sqrt() const noexcept -> Number
{
    return { std::sqrt(n), epsilon };
}


bool Number::isValid() const noexcept
{
    return !(std::isnan(n) || std::isinf(n)); 
}

} // namespace details.