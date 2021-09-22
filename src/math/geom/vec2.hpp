#ifndef MATH_GEOM_VEC2D_HPP
#define MATH_GEOM_VEC2D_HPP

namespace math::geom {
    class Vec2 {
    public:
        constexpr Vec2() = default;

        constexpr Vec2(double x, double y):
            x_{x},
            y_{y}
        {}

        constexpr double x() const { return x_; }
        constexpr double y() const { return y_; }

        constexpr Vec2& operator+=(Vec2 const& other)
        {
            x_ += other.x_;
            y_ += other.y_;
            return *this;
        }

        constexpr Vec2& operator*=(double scalar)
        {
            x_ *= scalar;
            y_ *= scalar;
            return *this;
        }

        constexpr Vec2& invert()
        {
            x_ = -x_;
            y_ = -y_;
            return *this;
        }

        constexpr bool operator==(Vec2 const& other) const = default;

    private:
        double x_{}, y_{};
    };

    constexpr Vec2 operator+(Vec2 lhs, Vec2 const& rhs) {
        return lhs += rhs;
    }

    constexpr Vec2 operator-(Vec2 vec) {
        return vec.invert();
    }

    constexpr Vec2 operator-(Vec2 lhs, Vec2 const& rhs) {
        return lhs += -rhs;
    }

    constexpr Vec2 operator*(Vec2 vec, double scalar) {
        return vec *= scalar;
    }

    constexpr Vec2 operator*(double scalar, Vec2 vec) {
        return vec * scalar;
    }

}

#endif
