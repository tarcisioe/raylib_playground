#include <raylib.h>

#include "math/geom/vec2.hpp"
#include "canvas/canvas.hpp"

#include "./raylibpp.hpp"

using namespace math::geom;

namespace {

class MoveMarker {
public:
    MoveMarker() = default;

    MoveMarker(MoveMarker&& other)
    {
        other.moved = true;
    }

    operator bool() const
    {
        return moved;
    }

private:
    bool moved{false};
};

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
    MoveMarker moved;
};


struct RaylibDrawer{
    void draw_circle(Vec2 const& center, double radius)
    {
        DrawCircleLines(
            static_cast<int>(center.x()),
            static_cast<int>(center.y()),
            float(radius),
            WHITE
        );
    }

private:
    DrawingGuard guard;
};


struct RaylibGuard {
};

}

namespace raylibpp {

class Raylib::RaylibImpl {
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

private:
    MoveMarker moved;
};

Raylib::Raylib(int width, int height, std::string_view title):
    impl{std::make_unique<RaylibImpl>(width, height, title)}
{}

Raylib::~Raylib() = default;

canvas::Canvas Raylib::canvas()
{
    return RaylibDrawer{};
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
