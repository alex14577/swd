#pragma once

#include <compare>


namespace solver::details {

class Number {
public:
    using Value = double;

    Number(Value _n) noexcept;
    Number(Value _n, Value _epsilon) noexcept;

    [[nodiscard]]
    bool operator<(const Number &_other) const noexcept;
    [[nodiscard]]
    bool operator>(const Number &_other) const noexcept;
    [[nodiscard]]
    bool operator==(const Number &_other) const noexcept;
    [[nodiscard]]
    auto operator<=>(const Number&) const = default;

    [[nodiscard]]
    Value value() const noexcept;

    [[nodiscard]]
    Number sqrt() const noexcept;

    [[nodiscard]]
    bool isValid() const noexcept;

private:
    Value n;
    Value epsilon;
};

} // namespace details.