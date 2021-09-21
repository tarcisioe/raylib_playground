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


void draw_points(canvas::Canvas& canvas, std::deque<Vec2> const& points, Vec2)
{
    using namespace ranges;

    auto point_pairs = points | views::sliding(2);

    for (auto pair: point_pairs) {
        canvas.draw_line(pair[0], pair[1]);
    }
}


class SquareWave {
public:
    constexpr static auto width = 1000;
    constexpr static auto height = 1000;

    constexpr static auto name = "Square wave with fourier series";

    void draw(canvas::Canvas& canvas)
    {
        using namespace color;

        canvas.clear_background(BLACK);

        auto x_origin = origin - Vec2{-100, 300};
        auto y_origin = origin - Vec2{300, -100};

        auto tip_x = epicycles_x.tip(x_origin);
        auto tip_y = epicycles_y.tip(y_origin);
        points.push_front({tip_x.x(), tip_y.y()});

        epicycles_x.draw(canvas, x_origin);
        epicycles_y.draw(canvas, y_origin);

        canvas.draw_line(tip_x, points.front());
        canvas.draw_line(tip_y, points.front());

        draw_points(canvas, points, origin);

        if (points.size() > 400) {
            points.pop_back();
        }

        epicycles_x.rotate(0.005);
        epicycles_y.rotate(0.025);
    }

private:
    fourier::Epicycles epicycles_x{fourier::square_wave(1, 80.0, std::numbers::pi/2)};
    fourier::Epicycles epicycles_y{fourier::square_wave(10, 80.0)};
    std::deque<Vec2> points{};
    Vec2 origin{500, 500};
};


int main()
try {
    raylibpp_runner::run_sketch(SquareWave{});
} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
