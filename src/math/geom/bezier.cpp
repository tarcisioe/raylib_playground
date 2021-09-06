#include "vec2.hpp"

namespace math::geom {

    Vec2 lerp(Vec2 const& v0, Vec2 const& v1, double t) {
        return v0 + (v1 - v0) * t;
    }

    Vec2 quadratic(Vec2 const& v0, Vec2 const& v1, Vec2 const& v2, double t) {
        return lerp(lerp(v0, v1, t), lerp(v1, v2, t), t);
    }

    Vec2 cubic(Vec2 const& v0, Vec2 const& v1, Vec2 const& v2, Vec2 const& v3, double t) {
        return lerp(quadratic(v0, v1, v2, t), quadratic(v1, v2, v3, t), t);
    }

}
