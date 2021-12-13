#include <deque>
#include <iostream>

#include <range/v3/view/iota.hpp>
#include <range/v3/view/sliding.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp_runner/runner.hpp"

#include "./epicycles.hpp"

using namespace math::geom;
using namespace fourier;

Epicycles square_wave(std::size_t n, double base_radius, double base_phase = 0.00)
{
    using namespace std::numbers;

    auto epicycles = std::vector<Epicycle>{};
    epicycles.reserve(n);

    for (auto i = 0u; i < n; ++i) {
        auto n_i = 2.0*i + 1.0;
        auto radius = base_radius * (4.0 / (n_i * pi));
        epicycles.push_back(Epicycle{radius, base_phase, n_i});
    }

    return Epicycles{std::move(epicycles)};
}

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


class SquareWave {
public:
    constexpr static auto width = 1200;
    constexpr static auto height = 800;

    constexpr static auto name = "Square wave with fourier series";

    void draw(canvas::Canvas& canvas)
    {
        using namespace color;

        canvas.clear_background(rgba::BLACK);

        auto tip = epicycles.tip(origin, time);
        wave_ys.push_front(tip.y());

        epicycles.draw(canvas, origin, time);

        auto base_wave_x = origin.x() + 350;
        canvas.draw_line(tip, {base_wave_x, wave_ys.front()});

        draw_wave(canvas, wave_ys, base_wave_x);

        if (wave_ys.size() > 400) {
            wave_ys.pop_back();
        }

        time += 0.025;
    }

private:
    Epicycles epicycles{square_wave(10, 100.0)};
    std::deque<double> wave_ys{};
    Vec2 origin{300, 400};
    double time{0.0};
};


int main()
try {
    raylibpp_runner::run_sketch(SquareWave{});
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
