#ifndef MATH_GEOM_MATRIX_HPP
#define MATH_GEOM_MATRIX_HPP

#include <vector>

namespace math::geom {

enum class Rotation {
    R0,
    R90,
    R180,
    R270,
};

struct Position2D {
    int row;
    int column;

    Position2D& operator+=(Position2D other)
    {
        row += other.row;
        column += other.column;

        return *this;
    }
};

inline Position2D operator+(Position2D lhs, Position2D rhs)
{
    return lhs += rhs;
}

struct MatrixPosition {
    Position2D position;
    Rotation rotation{Rotation::R0};
};

template <typename T>
class Matrix {
public:
    using Contents = std::vector<T>;

    constexpr Matrix(int rows, int columns):
        contents_(static_cast<std::size_t>(rows * columns)),
        rows_{rows},
        columns_{columns}
    {}

    constexpr Matrix(Matrix const&) = default;
    constexpr Matrix(Matrix &&) = default;

    constexpr Matrix& operator=(Matrix const&) = default;
    constexpr Matrix& operator=(Matrix &&) = default;

    constexpr T& operator[](MatrixPosition const& position)
    {
        return contents_[index_of(position)];
    }

    constexpr T const& operator[](MatrixPosition const& position) const
    {
        return contents_[index_of(position)];
    }

    constexpr void fill(T const& element)
    {
        contents_.fill(element);
    }

    constexpr int rows() const
    {
        return rows_;
    }

    constexpr int columns() const
    {
        return columns_;
    }

private:
    struct RotationConstants {
        int base;
        int row_multiplier;
        int column_multiplier;
    };

    constexpr std::size_t index_of(MatrixPosition position) const
    {
        auto const [base, row_multiplier, column_multiplier] =
            rotation_constants(position.rotation);

        return static_cast<std::size_t>(
            base + row_multiplier * position.position.row +
            column_multiplier * position.position.column);
    }

    constexpr RotationConstants rotation_constants(Rotation amount) const
    {
        switch (amount) {
            case Rotation::R0: {
                return {0, columns_, 1};
            }
            case Rotation::R90: {
                return {(rows_ - 1) * columns_, 1, -columns_};
            }
            case Rotation::R180: {
                return {(rows_ * columns_) - 1, -columns_, -1};
            }
            case Rotation::R270: {
                return {columns_ - 1, -1, columns_};
            }
            default:
                return {0, 0, 0};
        }
    }

    Contents contents_;
    int rows_;
    int columns_;
};

}

#endif
