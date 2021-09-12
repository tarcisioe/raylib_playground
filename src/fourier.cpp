#include <cmath>
#include <chrono>
#include <iostream>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp/raylibpp.hpp"

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


struct Polar {
    double radius, angle;

    Vec2 to_cartesian() {
        return {radius * std::cos(angle), radius * std::sin(angle)};
    }
};


int main()
try {
    using namespace raylibpp;
    using namespace canvas;
    using math::geom::Vec2;

    constexpr auto window_width = 600;
    constexpr auto window_height = 400;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto time = 0.0;
    auto radius = 50.0;

    auto circle_pos = Vec2{200, 200};

    while (not raylib.should_close()) {
        auto canvas = raylib.canvas();
        canvas.clear_background(ColorRGBA{0, 0, 0});
        canvas.no_fill();
        Circle{circle_pos, radius}.draw(canvas);
        canvas.fill(colors::WHITE);
        Circle{circle_pos + Polar{radius, time}.to_cartesian(), 4}.draw(canvas);

        time += 0.01;
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
