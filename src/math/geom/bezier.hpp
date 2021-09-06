#ifndef MATH_GEOM_BEZIER_HPP
#define MATH_GEOM_BEZIER_HPP

namespace math::geom {

    class Vec2;

    Vec2 lerp(Vec2 const& v0, Vec2 const& v1, double t);
    Vec2 quadratic(Vec2 const& v0, Vec2 const& v1, Vec2 const& v2, double t);
    Vec2 cubic(Vec2 const& v0, Vec2 const& v1, Vec2 const& v2, Vec2 const& v3, double t);

}

#endif
