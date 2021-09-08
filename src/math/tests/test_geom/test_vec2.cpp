#include "catch2/catch.hpp"

#include "math/geom/vec2.hpp"


using namespace math::geom;


TEST_CASE("Vec2 default constructor", "[Vec2]")
{
    auto v = Vec2{};

    REQUIRE(v.x() == 0);
    REQUIRE(v.y() == 0);
}


TEST_CASE("Vec2 constructor", "[Vec2]")
{
    auto v = Vec2{2, 3};

    REQUIRE(v.x() == 2);
    REQUIRE(v.y() == 3);
}


TEST_CASE("Vec2 equality", "[Vec2]")
{
    auto v = Vec2{2, 3};
    auto v2 = Vec2{v};
    auto v3 = Vec2{3, 4};

    REQUIRE(v == v);
    REQUIRE(v == v2);
    REQUIRE(v != v3);
}


TEST_CASE("Vec2 invert", "[Vec2][Vec2invert]")
{
    auto zero = Vec2{0, 0};
    auto v = Vec2{2, 3};

    zero.invert();
    REQUIRE(zero == Vec2{0, 0});

    auto v_orig = v;

    v.invert();
    REQUIRE(v == Vec2{-2, -3});

    v.invert();
    REQUIRE(v == Vec2{2,3});
    REQUIRE(v == v_orig);
}


TEST_CASE("Vec2 unary minus", "[Vec2][Vec2invert]")
{
    auto zero = Vec2{0, 0};
    auto v = Vec2{2, 3};

    REQUIRE(-zero == Vec2{0, 0});
    REQUIRE(-v == Vec2{-2, -3});
    REQUIRE(-(-v) == Vec2{2,3});
    REQUIRE(-(-v) == v);
}


TEST_CASE("Vec2 inline addition", "[Vec2][Vec2add]")
{
    auto v = Vec2{2, 3};
    auto zero = Vec2{0, 0};
    auto v2 = Vec2{3, 4};

    v += zero;
    REQUIRE(v == Vec2{2, 3});

    v += v2;
    REQUIRE(v == Vec2{5, 7});
}


TEST_CASE("Vec2 addition", "[Vec2][Vec2add]")
{
    auto v = Vec2{2, 3};
    auto zero = Vec2{0, 0};
    auto v2 = Vec2{3, 4};

    auto commut_check = [](auto vec1, auto vec2, auto e)
    {
        REQUIRE(vec1 + vec2 == e);
        REQUIRE(vec2 + vec1 == e);
    };

    commut_check(v, zero, v);
    commut_check(v, v, Vec2{4, 6});
    commut_check(v, v2, Vec2{5, 7});
}


TEST_CASE("Vec2 inline scalar multiplication", "[Vec2][Vec2mul]")
{
    auto v = Vec2{2, 3};

    v *= 1;
    REQUIRE(v == Vec2{2, 3});

    v *= 2;
    REQUIRE(v == Vec2{4, 6});

    v *= 0.25;
    REQUIRE(v == Vec2{1, 1.5});
}


TEST_CASE("Vec2 scalar multiplication", "[Vec2][Vec2mul]")
{
    auto v = Vec2{2, 3};

    auto commut_check = [](auto vec, auto s, auto e)
    {
        REQUIRE(vec * s == e);
        REQUIRE(s * vec == e);
    };

    commut_check(v, 1, v);
    commut_check(v, 2, Vec2{4, 6});
    commut_check(v, 2, v + v);
    commut_check(v, 0.5, Vec2{1, 1.5});
}
