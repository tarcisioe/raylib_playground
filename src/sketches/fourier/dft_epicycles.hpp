#ifndef FOURIER_DFT_EPICYCLES
#define FOURIER_DFT_EPICYCLES

#include <span>
#include <utility>

#include "./epicycles.hpp"

namespace math::geom {
class Vec2;
};

namespace fourier {

std::pair<Epicycles, Epicycles> dft_epicycles(std::span<math::geom::Vec2> points);

};

#endif
