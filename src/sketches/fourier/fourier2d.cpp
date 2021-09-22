#include <array>
#include <cmath>
#include <complex>
#include <deque>
#include <iostream>

#include <range/v3/view/sliding.hpp>
#include <range/v3/view/reverse.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp_runner/runner.hpp"

#include "./dft_epicycles.hpp"
#include "./epicycles.hpp"
#include "./train.hpp"

constinit auto two_pi = std::numbers::pi * 2;
constinit auto half_pi = std::numbers::pi / 2;

using namespace math::geom;
using namespace fourier;

void draw_points(canvas::Canvas& canvas, std::span<Vec2> const& points)
{
    using namespace ranges;

    auto point_pairs = points | views::reverse | views::sliding(2);

    for (auto pair: point_pairs) {
        canvas.draw_line(pair[0], pair[1]);
    }
}

class Fourier2DDrawer {
public:
    constexpr static auto width = 1000;
    constexpr static auto height = 1000;

    constexpr static auto name = "2D drawing with fourier transform";

    static auto from_points(std::span<Vec2> points)
    {
        auto [x, y] = dft_epicycles(points);

        return Fourier2DDrawer(std::move(x), std::move(y));
    }

    void draw(canvas::Canvas& canvas)
    {
        using namespace color;

        canvas.clear_background(BLACK);

        auto x_origin = origin - Vec2{-100, 300};
        auto y_origin = origin - Vec2{300, -100};

        auto tip_x = epicycles_x.tip(x_origin, time);
        auto tip_y = epicycles_y.tip(y_origin, time);
        points.push_back({tip_x.x(), tip_y.y()});

        epicycles_x.draw(canvas, x_origin, time);
        epicycles_y.draw(canvas, y_origin, time);

        canvas.draw_line(tip_x, points.back());
        canvas.draw_line(tip_y, points.back());

        draw_points(canvas, points);

        auto dt = two_pi / static_cast<double>(size);
        time += dt;

        if (time > two_pi) {
            points.clear();
            time = 0;
        }
    }

private:
    Fourier2DDrawer(Epicycles x, Epicycles y):
        epicycles_x{std::move(x)},
        epicycles_y{std::move(y)},
        size{x.size()}
    {}

    fourier::Epicycles epicycles_x;
    fourier::Epicycles epicycles_y;
    std::vector<Vec2> points{};
    Vec2 origin{500, 500};
    std::size_t size;
    double time{0.0};
};

int main()
try {
    auto sketch = Fourier2DDrawer::from_points(train);

    raylibpp_runner::run_sketch(sketch);
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
