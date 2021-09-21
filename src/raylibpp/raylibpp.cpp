#include <optional>

#include "math/geom/vec2.hpp"
#include "canvas/canvas.hpp"
#include "color/color.hpp"
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

    std::optional<color::ColorRGBA> stroke{color::WHITE};
    std::optional<color::ColorRGBA> fill{};

    ::util::MoveMarker moved;
};

}

class RaylibDrawer{
public:
    RaylibDrawer(impl::RaylibImpl& raylib_impl):
        impl{&raylib_impl}
    {
        BeginDrawing();
    }

    RaylibDrawer(RaylibDrawer&&) = default;
    RaylibDrawer(RaylibDrawer const&) = delete;

    ~RaylibDrawer()
    {
        if (not moved) {
            EndDrawing();
        }
    }

    RaylibDrawer& operator=(RaylibDrawer&&) = default;
    RaylibDrawer& operator=(RaylibDrawer const&) = delete;

    void stroke(color::ColorRGBA const& c)
    {
        impl->stroke = c;
    }

    void fill(color::ColorRGBA const& c)
    {
        impl->fill = c;
    }

    void no_stroke()
    {
        impl->stroke = std::nullopt;
    }

    void no_fill()
    {
        impl->fill = std::nullopt;
    }

    void draw_line(Vec2 const& v1, Vec2 const& v2)
    {
        auto &stroke = impl->stroke;

        if (stroke) {
            DrawLineV(to_raylib(v1), to_raylib(v2), to_raylib(*stroke));
        }
    }

    void draw_circle(Vec2 const& center, double radius)
    {
        auto v = to_raylib(center);
        auto r = static_cast<float>(radius);

        auto &fill = impl->fill;
        auto &stroke = impl->stroke;

        if (fill) {
            DrawCircleSector(v, r, 0, 360, 32, to_raylib(*(fill)));
        }

        if (stroke) {
            DrawCircleSectorLines(v, r, 0, 360, 32, to_raylib(*(stroke)));
        }
    }

    void clear_background(color::ColorRGBA const& c)
    {
        ClearBackground(to_raylib(c));
    }

private:
    impl::RaylibImpl *impl;
    ::util::MoveMarker moved;
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
