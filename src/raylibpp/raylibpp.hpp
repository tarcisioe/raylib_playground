#ifndef RAYLIBPP_RAYLIBPP_HPP
#define RAYLIBPP_RAYLIBPP_HPP

#include <memory>

namespace canvas {
class Canvas;
}

namespace color {
struct ColorRGBA;
}

namespace raylibpp {

namespace impl {

class RaylibImpl;

}

class Raylib {
public:
    Raylib(int width, int height, std::string_view title);

    ~Raylib();

    canvas::Canvas canvas();
    bool should_close();
    void set_target_fps(int fps);

private:
    std::unique_ptr<impl::RaylibImpl> impl;
};

}

#endif
