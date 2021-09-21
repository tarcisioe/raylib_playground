#ifndef RAYLIBPP_RAYLIBPP_HPP
#define RAYLIBPP_RAYLIBPP_HPP

#include <memory>

#include "utility/move.hpp"

namespace math::geom {
class Vec2;
};

namespace color {
struct ColorRGBA;
}

namespace raylibpp {

namespace impl {
class RaylibImpl;
}

class RaylibDrawer{
public:
    RaylibDrawer(impl::RaylibImpl& raylib_impl);
    RaylibDrawer(RaylibDrawer const&) = delete;
    RaylibDrawer(RaylibDrawer&&) = default;

    ~RaylibDrawer();

    RaylibDrawer& operator=(RaylibDrawer const&) = delete;
    RaylibDrawer& operator=(RaylibDrawer&&) = default;

    void stroke(color::ColorRGBA const& c);
    void fill(color::ColorRGBA const& c);
    void no_stroke();
    void no_fill();
    void draw_line(math::geom::Vec2 const& v1, math::geom::Vec2 const& v2);
    void draw_circle(math::geom::Vec2 const& center, double radius);
    void clear_background(color::ColorRGBA const& c);

private:
    impl::RaylibImpl *impl;
    ::util::MoveMarker moved;
};


class Raylib {
public:
    Raylib(int width, int height, std::string_view title);

    ~Raylib();

    RaylibDrawer start_drawing();
    bool should_close();
    void set_target_fps(int fps);

private:
    std::unique_ptr<impl::RaylibImpl> impl;
};

}

#endif
