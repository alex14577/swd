#include <quadratic.hpp>

#include <gtest/gtest.h>

#include <array>
#include <algorithm>


using namespace solver;
using namespace details;

TEST(Number, Compare)
{
    using namespace details;


    Number a{ 2.11 };
    Number b{ 2.12 };
    Number c{ 2.65 };
    Number d{ 2.65 };
    Number e{ 0.0 };

    EXPECT_TRUE(a.isValid());
    EXPECT_TRUE(b.isValid());
    EXPECT_TRUE(c.isValid());
    EXPECT_TRUE(d.isValid());
    EXPECT_TRUE(e.isValid());

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(c == d);

    EXPECT_FALSE(a > b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a == d);

    Number f{ std::numeric_limits<double>::infinity() };
    EXPECT_FALSE(f.isValid());
}

TEST(Quadratic, NoRoots) {
    Quadratic solver;

    Number a{ 1 };
    Number b{ 0 };
    Number c{ 1 };
    auto roots = solver.process(a, b, c);

    EXPECT_EQ(roots.size(), 0);
}

TEST(Quadratic, TwoRoots) {
    Quadratic solver;

    Number a{ 1 };
    Number b{ 0 };
    Number c{ -1 };
    auto roots = solver.process(a, b, c);

    EXPECT_EQ(roots.size(), 2);
}

TEST(Quadratic, OneRoots) {
    Quadratic solver;

    Number a{ 1 };
    Number b{ 2 };
    Number c{ 1 };
    auto roots = solver.process(a, b, c);

    EXPECT_EQ(roots.size(), 2);
    EXPECT_EQ(roots[0], roots[1]);
}

TEST(Quadratic, NotQuadratic) {
    Quadratic solver;

    Number a{ 0 };
    Number b{ 2 };
    Number c{ 1 };
    EXPECT_ANY_THROW(solver.process(a, b, c));
}

TEST(Quadratic, NonNumbers) {
    Quadratic solver;

    Number inf{ std::numeric_limits<double>::infinity() };
    Number nan{ std::numeric_limits<double>::quiet_NaN() };
    Number num{ 3 };

    std::array<Number, 3> coefs{ inf, nan, num };
    std::ranges::sort(coefs);

    do
    {
        EXPECT_ANY_THROW(solver.process(coefs[0], coefs[1], coefs[2]));
    }
    while (std::ranges::next_permutation(coefs).found);

}

TEST(Quadratic, ANotZero) {
    Quadratic solver;

    Number a{ std::numeric_limits<double>::quiet_NaN() };
    Number b{ 2  };
    Number c{ 3  };
    EXPECT_ANY_THROW(solver.process(a, b, c));
}