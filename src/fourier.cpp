#include <cmath>
#include <chrono>
#include <iostream>
#include <deque>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp/raylibpp.hpp"

using namespace math::geom;

struct Polar {
    double radius, angle;

    Vec2 to_cartesian() {
        return {radius * std::cos(angle), radius * std::sin(angle)};
    }
};


class Epicycle {
public:
    Epicycle(Vec2 const& center, double radius, double phase = 0.0):
        center_{center},
        radius_{radius},
        angle_{phase}
    {}

    Vec2 const& center() const
    {
        return center_;
    }

    double radius() const
    {
        return radius_;
    }

    void rotate(double amount)
    {
        angle_ += amount;
    }

    Vec2 tip() const
    {
        return center_ + Polar{radius_, angle_}.to_cartesian();
    }

    void draw(canvas::Canvas& d) const
    {
        auto tip = this->tip();

        d.no_fill();
        d.draw_circle(center_, radius_);
        d.draw_line(center_, tip);
        d.fill(canvas::colors::WHITE);
        d.draw_circle(tip, 4);
    }

private:
    Vec2 center_;
    double radius_;
    double angle_;
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

    auto origin = Vec2{200, 200};
    auto epicycle = Epicycle{origin, 50.0};

    auto wave_ys = std::deque<double>{};

    while (not raylib.should_close()) {
        auto canvas = raylib.canvas();

        canvas.clear_background(ColorRGBA{0, 0, 0});

        epicycle.draw(canvas);

        auto tip = epicycle.tip();
        auto base_wave_x = origin.x() + 75;
        wave_ys.push_front(tip.y());

        canvas.draw_line(tip, {base_wave_x, wave_ys.front()});

        auto i = 0;
        for (auto y: wave_ys) {
            canvas.draw_circle({base_wave_x + static_cast<double>(i), y}, 1);
            ++i;
        }

        if (wave_ys.size() > 400) {
            wave_ys.pop_back();
        }

        epicycle.rotate(0.05);
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
