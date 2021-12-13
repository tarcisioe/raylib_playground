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

namespace rgba {
    constexpr auto WHITE = ColorRGBA{255, 255, 255};
    constexpr auto BLACK = ColorRGBA{0, 0, 0};
}


struct ColorRGBDouble {
    constexpr ColorRGBDouble() = default;

    constexpr ColorRGBDouble(double red, double green, double blue):
        r{red},
        g{green},
        b{blue}
    {}

    double r{0.}, g{0.}, b{0.};
};

namespace rgb_double {
    constexpr auto WHITE = ColorRGBDouble{1.0, 1.0, 1.0};
    constexpr auto BLACK = ColorRGBDouble{0.0, 0.0, 0.0};
}

}

#endif
