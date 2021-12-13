#include <iostream>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "math/geom/matrix.hpp"
#include "math/geom/vec3.hpp"
#include "color/color.hpp"


class Image {
public:
    using Pixel = color::ColorRGBDouble;
    using Pixels = math::geom::Matrix<Pixel>;
    using Position = math::geom::MatrixPosition;

    Image(int width, int height):
        pixels{height, width}
    {}

    int height() const {
        return pixels.rows();
    }

    int width() const {
        return pixels.columns();
    }

    Pixel& operator[](Position pos)
    {
        return pixels[pos];
    }

    Pixel const& operator[](Position pos) const
    {
        return pixels[pos];
    }

private:
    Pixels pixels;
};


void print_ppm_color(std::ostream& out, color::ColorRGBDouble const& c)
{
    fmt::print(
        out,
        "{} {} {}\n",
        static_cast<uint8_t>(c.r * 255.999),
        static_cast<uint8_t>(c.g * 255.999),
        static_cast<uint8_t>(c.b * 255.999)
    );
}


void print_ppm(std::ostream& out, Image const& im)
{
    auto const width = im.width();
    auto const height = im.height();

    fmt::print("P3\n{} {}\n255\n", width, height);

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            print_ppm_color(out, im[{{j, i}}]);
        }
    }
}


int main()
{
    Image im{256, 256};

    auto const width = im.width();
    auto const height = im.height();

    for (int j = height - 1; j >= 0; --j) {
        fmt::print(std::cerr, "Scanlines remaining: {}\n", j);
        auto const g = static_cast<double>(j) / (height - 1);

        for (int i = 0; i < width; ++i) {
            im[{{j, i}}] = {
                static_cast<double>(i) / (width - 1),
                g,
                0.25,
            };
        }
    }

    print_ppm(std::cout, im);
}
