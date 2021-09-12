#include <optional>

#include "math/geom/vec2.hpp"
#include "canvas/canvas.hpp"
#include "canvas/color.hpp"
#include "utility/move.hpp"

#include "./raylibpp.hpp"
#include "./raylib_utils.hpp"


using namespace math::geom;
using namespace raylibpp::util;

namespace raylibpp {

namespace impl {

class RaylibImpl {
public:
    RaylibImpl(int width, int height, std::string_view title)
    {
        InitWindow(width, height, title.data());
    }

    RaylibImpl(RaylibImpl const&) = delete;
    RaylibImpl(RaylibImpl&& other) = default;

    ~RaylibImpl()
    {
        if (not moved) {
            CloseWindow();
        }
    }

    std::optional<canvas::ColorRGBA> stroke_{canvas::colors::WHITE};
    std::optional<canvas::ColorRGBA> fill_{};

    ::util::MoveMarker moved;
};

}

class RaylibDrawer{
public:
    RaylibDrawer(impl::RaylibImpl& raylib_impl):
        impl{raylib_impl}
    {}

    void draw_circle(math::geom::Vec2 const& center, double radius)
    {
        auto x = static_cast<int>(center.x());
        auto y = static_cast<int>(center.y());
        auto r = float(radius);

        if (impl.fill_) {
            DrawCircle(x, y, r, to_raylib(*impl.fill_));
        }

        if (impl.stroke_) {
            DrawCircleLines(x, y, r, to_raylib(*impl.stroke_));
        }
    }

    void stroke(canvas::ColorRGBA const& c)
    {
        impl.stroke_ = c;
    }

    void fill(canvas::ColorRGBA const& c)
    {
        impl.fill_ = c;
    }

    void no_stroke()
    {
        impl.stroke_ = std::nullopt;
    }

    void no_fill()
    {
        impl.fill_ = std::nullopt;
    }

    void clear_background(canvas::ColorRGBA const& c)
    {
        ClearBackground(to_raylib(c));
    }

private:
    impl::RaylibImpl& impl;
    DrawingGuard guard;
};

Raylib::Raylib(int width, int height, std::string_view title):
    impl{std::make_unique<impl::RaylibImpl>(width, height, title)}
{}

Raylib::~Raylib() = default;

canvas::Canvas Raylib::canvas()
{
    return RaylibDrawer{*impl};
}

bool Raylib::should_close()
{
    return WindowShouldClose();
}

void Raylib::set_target_fps(int fps)
{
    SetTargetFPS(fps);
}

}
