#ifndef FOURIER_DFT_IMPL_HPP
#define FOURIER_DFT_IMPL_HPP

#include <complex>
#include <numbers>

#include <range/v3/action/sort.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/range/concepts.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/transform.hpp>

#include "./epicycles.hpp"

namespace fourier::impl {

auto dft(auto const& signal)
{
    using namespace ranges;

    constexpr auto two_pi = std::numbers::pi * 2;

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

auto dft_epicycles(auto const& signal, double phase = 0.0)
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

}

#endif
