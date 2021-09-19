#include <deque>
#include <iostream>

#include <range/v3/view/iota.hpp>
#include <range/v3/view/sliding.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp/raylibpp.hpp"

#include "./epicycles.hpp"

using namespace math::geom;


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
    using namespace fourier;

    using math::geom::Vec2;

    constexpr auto window_width = 1200;
    constexpr auto window_height = 800;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto origin = Vec2{300, 400};
    auto wave_ys = std::deque<double>{};

    auto epicycles = square_wave(10, 100.0);

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
