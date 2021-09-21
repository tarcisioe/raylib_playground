#ifndef FOURIER_EPICYCLES_HPP
#define FOURIER_EPICYCLES_HPP

#include <cstdint>
#include <vector>

#include "math/geom/vec2.hpp"

namespace math::geom {
    class Vec2;
    struct Polar;
};

namespace canvas {
    class Canvas;
}

namespace fourier {

class Epicycle;

class Epicycles {
public:
    Epicycles(std::vector<Epicycle> epicycles);

    ~Epicycles();

    math::geom::Vec2 tip(math::geom::Vec2 origin) const;
    void draw(canvas::Canvas& canvas, math::geom::Vec2 const& origin) const;
    void rotate(double timestep);

private:
    std::vector<Epicycle> epicycles_;
};

Epicycles square_wave(std::size_t n, double base_radius = 50.0, double base_phase = 0.0);

}

#endif
