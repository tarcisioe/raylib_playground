#include <numbers>

#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>

#include "canvas/canvas.hpp"
#include "math/geom/polar.hpp"
#include "math/geom/vec2.hpp"

#include "./epicycles.hpp"

using namespace math::geom;

namespace fourier {

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

Epicycles Epicycles::fourier_series(std::size_t n, double base_radius)
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

Vec2 Epicycles::tip(Vec2 const& origin) const
{
    auto current = Vec2{};

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
