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

    fmt::print(out, "P3\n{} {}\n255\n", width, height);

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            print_ppm_color(out, im[{{j, i}}]);
        }
    }
}


class Ray {
public:
    Ray() = default;
    Ray(math::geom::Vec3 const& origin, math::geom::Vec3 const& direction):
        origin_{origin},
        direction_{direction}
    {}

    math::geom::Vec3 origin() const
    {
        return origin_;
    }

    math::geom::Vec3 direction() const
    {
        return direction_;
    }

    math::geom::Vec3 at(double t) const
    {
        return origin_ + t * direction_;
    }

private:
    math::geom::Vec3 origin_;
    math::geom::Vec3 direction_;
};


bool hit_sphere(math::geom::Vec3 const& center, double radius, Ray const& ray)
{
    auto const oc = ray.origin() - center;
    auto const a = dot(ray.direction(), ray.direction());
    auto const b = 2.0 * dot(oc, ray.direction());
    auto const c = dot(oc, oc) - radius * radius;
    auto const discriminant = b*b - 4*a*c;
    return discriminant > 0;
}


color::ColorRGBDouble ray_color(Ray const& ray)
{
    using math::geom::Vec3;

    if (hit_sphere(Vec3{0, 0, -1}, 0.5, ray)) {
        return {1, 0, 0};
    }

    auto const unit_direction = unit(ray.direction());
    auto const t = 0.5 * (unit_direction.y() + 1.0);
    auto const vec_color = (1.0 - t) * Vec3{1.0, 1.0, 1.0} + t * Vec3{0.5, 0.7, 1.0};

    return {vec_color.x(), vec_color.y(), vec_color.z()};
}


int main()
{
    auto constexpr aspect_ratio = 16.0 / 9.0;
    auto constexpr image_width = 400;
    auto constexpr image_height = static_cast<int>(image_width / aspect_ratio);

    Image im{image_width, image_height};

    auto constexpr viewport_height = 2.0;
    auto constexpr viewport_width = aspect_ratio * viewport_height;
    auto constexpr focal_length = 1.0;

    using math::geom::Vec3;

    auto constexpr origin = Vec3{0, 0, 0};
    auto constexpr horizontal = Vec3{viewport_width, 0, 0};
    auto constexpr vertical = Vec3{0, viewport_height, 0};
    auto constexpr lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3{0, 0, focal_length};

    for (int j = image_height - 1; j >= 0; --j) {
        // fmt::print(std::cerr, "Scanlines remaining: {}\n", j);
        auto const v = static_cast<double>(j) / (image_height - 1);

        for (int i = 0; i < image_width; ++i) {
            auto const u = static_cast<double>(i) / (image_width - 1) ;
            auto const ray = Ray{origin, lower_left_corner + u * horizontal + v * vertical + origin};

            im[{{j, i}}] = ray_color(ray);
        }
    }

    print_ppm(std::cout, im);
}
