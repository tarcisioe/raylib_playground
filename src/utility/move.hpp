#ifndef UTILITY_MOVE_HPP
#define UTILITY_MOVE_HPP

namespace util {

class MoveMarker {
public:
    MoveMarker() = default;

    MoveMarker(MoveMarker const&) = default;
    MoveMarker(MoveMarker&& other)
    {
        other.moved = true;
    }

    MoveMarker& operator=(MoveMarker const&) = default;
    MoveMarker& operator=(MoveMarker&&) = default;

    operator bool() const
    {
        return moved;
    }

private:
    bool moved{false};
};

}

#endif
