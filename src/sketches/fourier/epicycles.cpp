#include <numbers>
#include <iostream>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/polar.hpp"
#include "math/geom/vec2.hpp"

#include "./epicycles.hpp"

using namespace math::geom;

namespace fourier {

Vec2 Epicycle::tip(Vec2 const& origin, double time) const
{
    return origin + Polar{radius_, phase_ + freq_ * time}.to_cartesian();
}

void Epicycle::draw(canvas::Canvas& canvas, Vec2 const& origin, double time) const
{
    auto tip = this->tip(origin, time);

    canvas.no_fill();
    canvas.draw_circle(origin, radius_);
    canvas.draw_line(origin, tip);
    canvas.fill(color::rgba::WHITE);
    canvas.draw_circle(tip, 1);
}

auto tips(Vec2 const& origin, std::vector<Epicycle> const& epicycles, double time)
{
    auto get_tip = [time, current=origin](Epicycle const& epicycle) mutable
    {
        current = epicycle.tip(current, time);
        return current;
    };

    return ranges::views::transform(epicycles, get_tip);
}

Epicycles::Epicycles(std::vector<Epicycle> epicycles):
        epicycles_{std::move(epicycles)}
{}

Epicycles::~Epicycles() = default;

Vec2 Epicycles::tip(Vec2 origin, double time) const
{
    auto current = origin;

    for (auto tip: tips(origin, epicycles_, time)) {
        current = tip;
    }

    return current;
}

void Epicycles::draw(canvas::Canvas& canvas, Vec2 const& origin, double time) const
{
    auto with_tips = ranges::views::zip(epicycles_, tips(origin, epicycles_, time));

    auto current_tip = origin;

    for (auto const& [epicycle, tip]: with_tips) {
        epicycle.draw(canvas, current_tip, time);
        current_tip = tip;
    }
}

}
