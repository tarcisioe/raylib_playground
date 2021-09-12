#include <iostream>
#include <string_view>
#include <vector>

#include <raylib.h>

#include "math/geom/bezier.hpp"
#include "math/geom/vec2.hpp"

math::geom::Vec2 from_raylib(Vector2 const& vec) {
    return {static_cast<double>(vec.x), static_cast<double>(vec.y)};
}

Vector2 to_raylib(math::geom::Vec2 const& vec) {
    return {static_cast<float>(vec.x()), static_cast<float>(vec.y())};
}

auto begin_drawing()
{
    struct DrawingGuard {
        ~DrawingGuard() {
            EndDrawing();
        }
    };

    BeginDrawing();
    return DrawingGuard();
}

auto init_raylib(int width, int height, std::string_view const name)
{
    struct RaylibGuard {
        ~RaylibGuard() {
            CloseWindow();
        }
    };

    InitWindow(width, height, name.data());
    return RaylibGuard{};
}


int main()
try {
    using math::geom::Vec2;

    const auto window_width = 600;
    const auto window_height = 600;

    [[maybe_unused]] auto raylib = init_raylib(window_width, window_height, "My Raylib Window.");

    SetTargetFPS(60);

    auto p0 = Vec2(0, 300);
    auto p1 = Vec2(300, 400);
    auto p2 = Vec2(300, 400);
    auto p3 = Vec2(600, 300);

    auto poly = std::vector<Vector2>{};
    poly.reserve(100);

    while (not WindowShouldClose()) {
        [[maybe_unused]] auto guard = begin_drawing();

        if (IsKeyDown(KEY_A)) {
            p0 = from_raylib(GetMousePosition());
        }
        if (IsKeyDown(KEY_S)) {
            p1 = from_raylib(GetMousePosition());
        }
        if (IsKeyDown(KEY_D)) {
            p2 = from_raylib(GetMousePosition());
        }
        if (IsKeyDown(KEY_F)) {
            p3 = from_raylib(GetMousePosition());
        }

        ClearBackground(BLACK);

        for (auto t = 0.0; t <= 1.0; t += 0.05) {
            auto point = cubic(p0, p1, p2, p3, t);
            poly.push_back(to_raylib(point));
        }
        poly.push_back(to_raylib(p3));

        DrawCircleV(poly.front(), 3, WHITE);
        for (auto i = 1u; i < poly.size(); ++i) {
            DrawLineV(poly[i-1], poly[i], WHITE);
            DrawCircleV(poly[i], 3, WHITE);
        }

        auto rp0 = to_raylib(p0);
        auto rp1 = to_raylib(p1);
        auto rp2 = to_raylib(p2);
        auto rp3 = to_raylib(p3);

        DrawLineV(rp0, rp1, BLUE);
        DrawLineV(rp2, rp3, BLUE);
        DrawCircleV(rp0, 5, RED);
        DrawCircleV(rp1, 5, RED);
        DrawCircleV(rp2, 5, RED);
        DrawCircleV(rp3, 5, RED);

        poly.clear();
    }

} catch (...) {
    std::clog << "Unknown error. Aborting.";
    return 1;
}
