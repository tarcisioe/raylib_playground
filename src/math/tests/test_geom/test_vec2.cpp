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
