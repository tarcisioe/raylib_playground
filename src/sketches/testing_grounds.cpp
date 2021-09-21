#include <chrono>
#include <iostream>

#include "canvas/canvas.hpp"
#include "math/geom/bezier.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp_runner/runner.hpp"

using namespace math::geom;

class Circle {
public:
    Circle(Vec2 const& center, double radius):
        center_{center},
        radius_{radius}
    {}

    Vec2 const& center() const
    {
        return center_;
    }

    double radius() const
    {
        return radius_;
    }

    void draw(canvas::Canvas& d) const
    {
        d.draw_circle(center_, radius_);
    }

private:
    Vec2 center_;
    double radius_;
};


class TestingGrounds {
public:
    constexpr auto static width = 600;
    constexpr auto static height = 600;

    constexpr auto static name = "Testing grounds";

    void draw(canvas::Canvas& canvas) {
        canvas.clear_background(color::BLACK);
        Circle{{300, 300}, radius}.draw(canvas);

        ++radius;
    }

private:
    double radius{100.0};
};


int main()
try {
    raylibpp_runner::run_sketch(TestingGrounds{});
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
