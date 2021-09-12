#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>
#include <numbers>
#include <vector>

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
    Epicycle(double radius, double phase = 0.0, double freq = 1.0):
        radius_{radius},
        angle_{phase},
        freq_{freq}
    {}

    double radius() const
    {
        return radius_;
    }

    void rotate(double timestep)
    {
        angle_ += timestep * freq_;
    }

    Vec2 tip(Vec2 const& origin) const
    {
        return origin + Polar{radius_, angle_}.to_cartesian();
    }

    void draw(Vec2 const& origin, canvas::Canvas& d) const
    {
        auto tip = this->tip(origin);

        d.no_fill();
        d.draw_circle(origin, radius_);
        d.draw_line(origin, tip);
        d.fill(canvas::colors::WHITE);
        // d.draw_circle(tip, 1);
    }

private:
    double radius_;
    double angle_;
    double freq_;
};


int main()
try {
    using namespace raylibpp;
    using namespace canvas;
    using math::geom::Vec2;
    namespace numbers = std::numbers;

    constexpr auto window_width = 600;
    constexpr auto window_height = 400;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto origin = Vec2{200, 200};
    auto wave_ys = std::deque<double>{};

    auto epicycles = std::vector<Epicycle>{};

    for (auto i = 0; i < 10; ++i) {
        auto n = 2.0*i + 1.0;
        epicycles.push_back(Epicycle{50.0 * (4.0/(n*numbers::pi)), 0.0, n});
    }

    while (not raylib.should_close()) {
        auto canvas = raylib.canvas();

        auto base_wave_x = origin.x() + 75;
        canvas.clear_background(ColorRGBA{0, 0, 0});

        auto current_origin = origin;

        for (auto& epicycle: epicycles) {
            epicycle.draw(current_origin, canvas);
            current_origin = epicycle.tip(current_origin);
        }

        wave_ys.push_front(current_origin.y());
        canvas.draw_line(current_origin, {base_wave_x, wave_ys.front()});

        auto i = 0;
        for (auto y: wave_ys) {
            canvas.draw_circle({base_wave_x + static_cast<double>(i), y}, 1);
            ++i;
        }

        if (wave_ys.size() > 400) {
            wave_ys.pop_back();
        }

        for (auto& epicycle: epicycles) {
            epicycle.rotate(0.05);
        }
    }
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
