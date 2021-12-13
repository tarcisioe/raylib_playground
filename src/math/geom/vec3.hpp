#ifndef MATH_GEOM_VEC3D_HPP
#define MATH_GEOM_VEC3D_HPP

#include <cmath>

namespace math::geom {
    class Vec3 {
    public:
        constexpr Vec3() = default;

        constexpr Vec3(double x, double y, double z):
            x_{x},
            y_{y},
            z_{z}
        {}

        constexpr double x() const { return x_; }
        constexpr double y() const { return y_; }
        constexpr double z() const { return z_; }

        constexpr Vec3& operator+=(Vec3 const& other)
        {
            x_ += other.x_;
            y_ += other.y_;
            z_ += other.z_;
            return *this;
        }

        constexpr Vec3& operator*=(double scalar)
        {
            x_ *= scalar;
            y_ *= scalar;
            z_ *= scalar;
            return *this;
        }

        constexpr Vec3& operator*=(Vec3 const& other)
        {
            x_ *= other.x_;
            y_ *= other.y_;
            z_ *= other.z_;
            return *this;
        }

        constexpr Vec3& invert()
        {
            x_ = -x_;
            y_ = -y_;
            z_ = -z_;
            return *this;
        }

        constexpr double length_squared() const
        {
            return x_*x_ + y_*y_ + z_*z_;
        }

        constexpr double length() const
        {
            return std::sqrt(length_squared());
        }

        constexpr bool operator==(Vec3 const& other) const = default;

    private:
        double x_{}, y_{}, z_{};
    };

    constexpr Vec3 operator+(Vec3 lhs, Vec3 const& rhs)
    {
        return lhs += rhs;
    }

    constexpr Vec3 operator-(Vec3 vec)
    {
        return vec.invert();
    }

    constexpr Vec3 operator-(Vec3 lhs, Vec3 const& rhs)
    {
        return lhs += -rhs;
    }

    constexpr Vec3 operator*(Vec3 lhs, Vec3 const& rhs)
    {
        return lhs *= rhs;
    }

    constexpr Vec3 operator*(Vec3 vec, double scalar)
    {
        return vec *= scalar;
    }

    constexpr Vec3 operator*(double scalar, Vec3 const& vec)
    {
        return vec * scalar;
    }

    constexpr Vec3 operator/(Vec3 vec, double scalar)
    {
        return vec *= 1/scalar;
    }

    constexpr double dot(Vec3 const& lhs, Vec3 const& rhs)
    {
        auto const uv = lhs * rhs;

        return uv.x() + uv.y() + uv.z();
    }

    constexpr Vec3 cross(Vec3 const& lhs, Vec3 const& rhs)
    {
        return {
            lhs.y() * rhs.z() - lhs.z() * rhs.y(),
            lhs.z() * rhs.x() - lhs.x() * rhs.z(),
            lhs.x() * rhs.y() - lhs.y() * rhs.x(),
        };
    }

    constexpr Vec3 unit(Vec3 const& v)
    {
        return v/v.length();
    }
}

#endif
