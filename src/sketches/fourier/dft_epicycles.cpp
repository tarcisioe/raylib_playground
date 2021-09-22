#include <numbers>

#include "./dft_epicycles.hpp"
#include "./dft_impl.hpp"

#include "math/geom/vec2.hpp"

namespace fourier {

std::pair<Epicycles, Epicycles> dft_epicycles(std::span<math::geom::Vec2> points)
{
    using namespace impl;

    constexpr auto half_pi = std::numbers::pi/2;

    return {
        Epicycles{impl::dft_epicycles(points | ranges::views::transform([](auto p){ return p.x(); }))},
        Epicycles{impl::dft_epicycles(points | ranges::views::transform([](auto p){ return p.y(); }), half_pi)},
    };
}

}
