#include <array>
#include <complex>
#include <deque>
#include <iostream>

#include <range/v3/action/sort.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/sliding.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/vec2.hpp"
#include "raylibpp_runner/runner.hpp"

#include <cmath>

#include "./epicycles.hpp"
#include "./train.hpp"

constinit auto two_pi = std::numbers::pi * 2;
constinit auto half_pi = std::numbers::pi / 2;

using namespace math::geom;
using namespace fourier;

auto dft(ranges::forward_range auto const& signal)
{
    using namespace ranges;

    auto const N = ranges::distance(signal);

    auto calculate_Xk = [&signal, N](auto k)
    {
        auto calculate_term = [k, N](auto n_xn)
        {
            auto [n, xn] = n_xn;
            auto phi = (two_pi * static_cast<double>(k) * static_cast<double>(n))/static_cast<double>(N);
            return std::complex<double>{xn * cos(phi), -(xn * sin(phi))};
        };

        auto Xk = accumulate(signal | views::enumerate | views::transform(calculate_term), std::complex<double>{0.0, 0.0});

        auto result = Xk/static_cast<double>(N);
        return result;
    };

    return views::indices(N) | views::transform(calculate_Xk);
}

auto dft_epicycles(ranges::forward_range auto const& signal, double phase = 0.0)
{
    using namespace ranges;

    auto make_epicycle = [&](auto k_c)
    {
        auto [k, c] = k_c;
        return Epicycle{abs(c), std::arg(c) + phase, static_cast<double>(static_cast<long>(k))};
    };

    auto epicycles =
        dft(signal)
        | views::enumerate
        | views::transform(make_epicycle)
        | ranges::to<std::vector>()
        | actions::sort([](auto a, auto b){ return a.radius() > b.radius(); })
    ;

    return Epicycles{epicycles};
}

void draw_points(canvas::Canvas& canvas, std::deque<Vec2> const& points)
{
    using namespace ranges;

    auto point_pairs = points | views::sliding(2);

    for (auto pair: point_pairs) {
        canvas.draw_line(pair[0], pair[1]);
    }
}

auto circle(int points, double radius)
{
    using namespace ranges;

    auto calculate_circle_point = [&](auto point)
    {
        auto angle = static_cast<double>(point)/points * two_pi;

        return Vec2{
            radius * cos(angle),
            radius * sin(angle),
        };
    };

    return views::indices(points) | views::transform(calculate_circle_point) | to<std::vector>();
}

class Fourier2DDrawer {
public:
    constexpr static auto width = 1000;
    constexpr static auto height = 1000;

    constexpr static auto name = "2D drawing with fourier transform";

    Fourier2DDrawer(ranges::forward_range auto const& drawing):
        epicycles_x{dft_epicycles(drawing | ranges::views::transform([](auto p){ return p.x(); }))},
        epicycles_y{dft_epicycles(drawing | ranges::views::transform([](auto p){ return p.y(); }), -half_pi)},
        size{ranges::size(drawing)}
    {}

    void draw(canvas::Canvas& canvas)
    {
        using namespace color;

        canvas.clear_background(BLACK);

        auto x_origin = origin - Vec2{-100, 300};
        auto y_origin = origin - Vec2{300, -100};

        auto tip_x = epicycles_x.tip(x_origin, time);
        auto tip_y = epicycles_y.tip(y_origin, time);
        points.push_front({tip_x.x(), tip_y.y()});

        epicycles_x.draw(canvas, x_origin, time);
        epicycles_y.draw(canvas, y_origin, time);

        canvas.draw_line(tip_x, points.front());
        canvas.draw_line(tip_y, points.front());

        draw_points(canvas, points);

        if (points.size() > 5000) {
            points.pop_back();
        }

        auto dt = two_pi / static_cast<double>(size);
        time += dt;

        if (time > two_pi) {
            points.clear();
            time = 0;
        }
    }

private:
    fourier::Epicycles epicycles_x;
    fourier::Epicycles epicycles_y;
    std::deque<Vec2> points{};
    Vec2 origin{500, 500};
    std::size_t size;
    double time{0.0};
};

int main()
try {
    auto sketch = Fourier2DDrawer{train};

    raylibpp_runner::run_sketch(sketch);
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
