#ifndef SKETCH_SKETCH_HPP
#define SKETCH_SKETCH_HPP

#include <concepts>
#include <string_view>

namespace canvas {
class Canvas;
}

namespace sketch {

template <typename T>
concept HasHeightAndWidth = requires () {
    { T::height } -> std::convertible_to<int>;
    { T::width } -> std::convertible_to<int>;
};

template <typename T>
concept HasName = requires () {
    { T::name } -> std::convertible_to<std::string_view>;
};

template <typename T>
concept HasDrawOnCanvas = requires (T& a, canvas::Canvas& c) {
    { a.draw(c) } -> std::convertible_to<void>;
};

template <typename T>
concept Sketch = HasHeightAndWidth<T> && HasName<T> && HasDrawOnCanvas<T>;

}

#endif
