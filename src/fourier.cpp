#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>
#include <numbers>
#include <vector>

#include <range/v3/view/iota.hpp>
#include <range/v3/view/sliding.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

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

    void draw(canvas::Canvas& d, Vec2 const& origin) const
    {
        auto tip = this->tip(origin);

        d.no_fill();
        d.draw_circle(origin, radius_);
        d.draw_line(origin, tip);
        d.fill(canvas::colors::WHITE);
        d.draw_circle(tip, 1);
    }

private:
    double radius_;
    double angle_;
    double freq_;
};


class Epicycles {
private:
    auto tips(Vec2 const& origin) const
    {
        auto get_tip = [current=origin](Epicycle const& epicycle) mutable
        {
            current = epicycle.tip(current);
            return current;
        };

        return ranges::views::transform(epicycles_, get_tip);
    }

public:
    static auto fourier_series(std::size_t n, double base_radius = 50.0)
    {
        using namespace std::numbers;

        auto epicycles = std::vector<Epicycle>{};
        epicycles.reserve(n);

        for (auto i = 0; i < 10; ++i) {
            auto n_i = 2.0*i + 1.0;
            auto radius = base_radius * (4.0 / (n_i * pi));
            epicycles.push_back(Epicycle{radius, 0.0, n_i});
        }

        return Epicycles{std::move(epicycles)};
    }

    Vec2 tip(Vec2 const& origin) const
    {
        auto current = Vec2{};

        for (auto tip: tips(origin)) {
            current = tip;
        }

        return current;
    }

    void draw(canvas::Canvas& canvas, Vec2 origin) const
    {
        auto with_tips = ranges::views::zip(epicycles_, tips(origin));

        for (auto const& [epicycle, tip]: with_tips) {
            epicycle.draw(canvas, origin);
            origin = tip;
        }
    }

    void rotate(double timestep)
    {
        for (auto& epicycle: epicycles_) {
            epicycle.rotate(timestep);
        }
    }

private:
    Epicycles(std::vector<Epicycle> epicycles):
        epicycles_{std::move(epicycles)}
    {}

    std::vector<Epicycle> epicycles_;
};


void draw_wave(canvas::Canvas& canvas, std::deque<double> const& wave_ys, double base_x)
{
    using namespace ranges;

    auto calculate_wave_x = [&](auto i)
    {
        return static_cast<double>(i)/2.0 + base_x;
    };

    auto point_from_pair = [](auto pair)
    {
        auto [x, y] = pair;
        return Vec2{x, y};
    };

    auto wave_point_pairs = views::zip(
            views::iota(0) | views::transform(calculate_wave_x),
            wave_ys
        ) | views::transform(point_from_pair) | views::sliding(2);

    for (auto pair: wave_point_pairs) {
        canvas.draw_line(pair[0], pair[1]);
    }
}


int main()
try {
    using namespace raylibpp;
    using namespace canvas;

    using math::geom::Vec2;

        constexpr auto window_width = 1200;
    constexpr auto window_height = 800;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto origin = Vec2{300, 400};
    auto wave_ys = std::deque<double>{};

    auto epicycles = Epicycles::fourier_series(10, 100.0);

    while (not raylib.should_close()) {
        auto canvas = raylib.canvas();

        canvas.clear_background(ColorRGBA{0, 0, 0});

        auto tip = epicycles.tip(origin);
        wave_ys.push_front(tip.y());

        epicycles.draw(canvas, origin);

        auto base_wave_x = origin.x() + 350;
        canvas.draw_line(tip, {base_wave_x, wave_ys.front()});

        draw_wave(canvas, wave_ys, base_wave_x);

        if (wave_ys.size() > 400) {
            wave_ys.pop_back();
        }

        epicycles.rotate(0.025);
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
