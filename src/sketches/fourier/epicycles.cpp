#include <numbers>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/polar.hpp"
#include "math/geom/vec2.hpp"

#include "./epicycles.hpp"

using namespace math::geom;

namespace fourier {

Vec2 Epicycle::tip(Vec2 const& origin) const
{
    return origin + Polar{radius_, angle_}.to_cartesian();
}

void Epicycle::draw(canvas::Canvas& canvas, Vec2 const& origin) const
{
    auto tip = this->tip(origin);

    canvas.no_fill();
    canvas.draw_circle(origin, radius_);
    canvas.draw_line(origin, tip);
    canvas.fill(color::WHITE);
    canvas.draw_circle(tip, 1);
}

auto tips(Vec2 const& origin, std::vector<Epicycle> const& epicycles)
{
    auto get_tip = [current=origin](Epicycle const& epicycle) mutable
    {
        current = epicycle.tip(current);
        return current;
    };

    return ranges::views::transform(epicycles, get_tip);
}

Epicycles::Epicycles(std::vector<Epicycle> epicycles):
        epicycles_{std::move(epicycles)}
{}

Epicycles::~Epicycles() = default;

Vec2 Epicycles::tip(Vec2 origin) const
{
    auto current = origin;

    for (auto tip: tips(origin, epicycles_)) {
        current = tip;
    }

    return current;
}

void Epicycles::draw(canvas::Canvas& canvas, Vec2 const& origin) const
{
    auto with_tips = ranges::views::zip(epicycles_, tips(origin, epicycles_));

    auto current_tip = origin;

    for (auto const& [epicycle, tip]: with_tips) {
        epicycle.draw(canvas, current_tip);
        current_tip = tip;
    }
}

void Epicycles::rotate(double timestep)
{
    for (auto& epicycle: epicycles_) {
        epicycle.rotate(timestep);
    }
}

}
