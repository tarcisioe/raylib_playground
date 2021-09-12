#ifndef RAYLIBPP_RAYLIB_UTILS_HPP
#define RAYLIBPP_RAYLIB_UTILS_HPP

#include <raylib.h>
#undef WHITE
#undef BLACK

#include "math/geom/vec2.hpp"
#include "canvas/color.hpp"
#include "utility/move.hpp"


namespace raylibpp::util {

struct DrawingGuard {
    DrawingGuard()
    {
        BeginDrawing();
    }

    DrawingGuard(DrawingGuard const&) = delete;
    DrawingGuard(DrawingGuard&& other) = default;

    ~DrawingGuard() {
        if (not moved) {
            EndDrawing();
        }
    }

private:
    ::util::MoveMarker moved;
};

Color to_raylib(canvas::ColorRGBA const& c) {
    return Color{c.r, c.g, c.b, c.a};
}

}

#endif
