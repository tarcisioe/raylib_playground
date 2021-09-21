#include <chrono>
#include <iostream>

#include "canvas/canvas.hpp"
#include "math/geom/bezier.hpp"
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


int main()
try {
    using namespace raylibpp;
    using math::geom::Vec2;

    constexpr auto window_width = 600;
    constexpr auto window_height = 600;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto radius = 100.0;

    while (not raylib.should_close()) {
        auto canvas = canvas::Canvas{raylib.start_drawing()};
        Circle{{300, 300}, radius}.draw(canvas);

        ++radius;
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
