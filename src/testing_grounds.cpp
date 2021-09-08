#include <iostream>
#include <string_view>
#include <vector>
#include <memory>

#include <raylib.h>

#include "math/geom/bezier.hpp"
#include "math/geom/vec2.hpp"

math::geom::Vec2 from_raylib(Vector2 const& vec) {
    return {static_cast<double>(vec.x), static_cast<double>(vec.y)};
}

Vector2 to_raylib(math::geom::Vec2 const& vec) {
    return {static_cast<float>(vec.x()), static_cast<float>(vec.y())};
}

namespace {
    using math::geom::Vec2;
}

class Canvas {
public:
    template <typename D>
    Canvas(D d):
        inner{std::make_unique<Inner<D>>(std::move(d))}
    {}

    void draw_circle(Vec2 const& center, double radius)
    {
        inner->draw_circle(center, radius);
    }

private:
    struct InnerBase {
        virtual ~InnerBase() = default;
        virtual void draw_circle(Vec2 const& center, double radius) = 0;
    };

    template <typename D>
    struct Inner: public InnerBase {
        Inner(D d):
            d_{std::move(d)}
        {}

        void draw_circle(Vec2 const& center, double radius) override
        {
            d_.draw_circle(center, radius);
        }

        D d_;
    };

    std::unique_ptr<InnerBase> inner;
};


namespace raylibpp {

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
    RaylibGuard(int width, int height, std::string_view title)
    {
        InitWindow(width, height, title.data());
    }

    RaylibGuard(RaylibGuard const&) = delete;
    RaylibGuard(RaylibGuard&& other) = default;

    ~RaylibGuard()
    {
        if (not moved) {
            CloseWindow();
        }
    }

private:
    MoveMarker moved;
};


class Raylib {
public:
    Raylib(int width, int height, std::string_view title):
        guard{width, height, title}
    {}

    Canvas canvas()
    {
        return Canvas{RaylibDrawer{}};
    }

    bool should_close()
    {
        return WindowShouldClose();
    }

    void set_target_fps(int fps)
    {
        SetTargetFPS(fps);
    }

private:
    RaylibGuard guard;
};

}


class Circle {
public:
    Circle(Vec2 const& center, double radius):
        center_{center},
        radius_{radius}
    {}

    Vec2 const& center() const
    {
        return center_;
    }

    double radius() const
    {
        return radius_;
    }

    void draw(Canvas& d) const
    {
        d.draw_circle(center_, radius_);
    }

private:
    Vec2 center_;
    double radius_;
};


int main()
try {
    using namespace raylibpp;
    using math::geom::Vec2;

    constexpr auto window_width = 600;
    constexpr auto window_height = 600;

    auto raylib = Raylib{window_width, window_height, "My Raylib Window."};
    raylib.set_target_fps(60);

    auto radius = 100.0;

    while (not raylib.should_close()) {
        auto canvas = raylib.canvas();

        ClearBackground(BLACK);
        Circle{{300, 300}, radius}.draw(canvas);

        ++radius;
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
