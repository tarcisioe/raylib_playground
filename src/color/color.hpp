#ifndef COLOR_COLOR_HPP
#define COLOR_COLOR_HPP

#include <cstdint>

namespace color {

struct ColorRGBA {
    constexpr ColorRGBA() = default;

    constexpr ColorRGBA(uint8_t red, uint8_t green, uint8_t blue):
        r{red},
        g{green},
        b{blue}
    {}

    constexpr ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha):
        r{red},
        g{green},
        b{blue},
        a{alpha}
    {}

    uint8_t r{0}, g{0}, b{0}, a{255};
};

constinit inline auto WHITE = ColorRGBA{255, 255, 255};
constinit inline auto BLACK = ColorRGBA{0, 0, 0};

}

#endif
