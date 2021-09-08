#ifndef RAYLIBPP_RAYLIBPP_HPP
#define RAYLIBPP_RAYLIBPP_HPP

#include <memory>

namespace canvas {
class Canvas;
}

namespace raylibpp {

class Raylib {
public:
    Raylib(int width, int height, std::string_view title);

    ~Raylib();

    canvas::Canvas canvas();
    bool should_close();
    void set_target_fps(int fps);

private:
    class RaylibImpl;

    std::unique_ptr<RaylibImpl> impl;
};

}

#endif
