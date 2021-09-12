#ifndef FOURIER_EPICYCLES_HPP
#define FOURIER_EPICYCLES_HPP

#include <cstdint>
#include <vector>

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
    static Epicycles fourier_series(std::size_t n, double base_radius = 50.0);

    ~Epicycles();

    math::geom::Vec2 tip(math::geom::Vec2 const& origin) const;
    void draw(canvas::Canvas& canvas, math::geom::Vec2 const& origin) const;
    void rotate(double timestep);

private:
    Epicycles(std::vector<Epicycle> epicycles);
    std::vector<Epicycle> epicycles_;
};

}

#endif
