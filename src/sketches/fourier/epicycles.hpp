#ifndef FOURIER_EPICYCLES_HPP
#define FOURIER_EPICYCLES_HPP

#include <cstdint>
#include <vector>

namespace math::geom {
    class Vec2;
};

namespace canvas {
    class Canvas;
}

namespace fourier {

class Epicycle {
public:
    Epicycle(double radius, double phase = 0.0, double freq = 1.0):
        radius_{radius},
        phase_{phase},
        freq_{freq}
    {}

    double radius() const
    {
        return radius_;
    }

    math::geom::Vec2 tip(math::geom::Vec2 const& origin, double time) const;

    void draw(canvas::Canvas& d, math::geom::Vec2 const& origin, double time) const;

private:
    double radius_;
    double phase_;
    double freq_;
};


class Epicycles {
public:
    Epicycles(std::vector<Epicycle> epicycles);

    ~Epicycles();

    math::geom::Vec2 tip(math::geom::Vec2 origin, double time) const;
    void draw(canvas::Canvas& canvas, math::geom::Vec2 const& origin, double time) const;

    auto size()
    {
        return epicycles_.size();
    }

private:
    std::vector<Epicycle> epicycles_;
};

}

#endif
