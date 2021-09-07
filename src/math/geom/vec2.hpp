#ifndef MATH_GEOM_VEC2D_HPP
#define MATH_GEOM_VEC2D_HPP

namespace math::geom {
    class Vec2 {
    public:
        Vec2() = default;

        Vec2(double x, double y):
            x_{x},
            y_{y}
        {}

        double x() const { return x_; }
        double y() const { return y_; }

        Vec2& operator+=(Vec2 const& other)
        {
            x_ += other.x_;
            y_ += other.y_;
            return *this;
        }

        Vec2& operator*=(double scalar)
        {
            x_ *= scalar;
            y_ *= scalar;
            return *this;
        }

        Vec2& invert()
        {
            x_ = -x_;
            y_ = -y_;
            return *this;
        }

        bool operator==(Vec2 const& other) const = default;

    private:
        double x_{}, y_{};
    };

    inline Vec2 operator+(Vec2 lhs, Vec2 const& rhs) {
        return lhs += rhs;
    }

    inline Vec2 operator-(Vec2 vec) {
        return vec.invert();
    }

    inline Vec2 operator-(Vec2 lhs, Vec2 const& rhs) {
        return lhs += -rhs;
    }

    inline Vec2 operator*(Vec2 vec, double scalar) {
        return vec *= scalar;
    }

    inline Vec2 operator*(double lhs, Vec2 rhs) {
        return rhs * lhs;
    }

}

#endif
