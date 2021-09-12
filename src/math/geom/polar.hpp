#ifndef MATH_GEOM_POLAR_HPP
#define MATH_GEOM_POLAR_HPP

#include <cmath>

#include "./vec2.hpp"

namespace math::geom {

struct Polar {
    double radius, angle;

    Vec2 to_cartesian() {
        return {radius * std::cos(angle), radius * std::sin(angle)};
    }
};

}

#endif
