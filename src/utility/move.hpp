#ifndef UTILITY_MOVE_HPP
#define UTILITY_MOVE_HPP

namespace util {

class MoveMarker {
public:
    MoveMarker() = default;

    MoveMarker(MoveMarker&& other)
    {
        other.moved = true;
    }

    operator bool() const
    {
        return moved;
    }

private:
    bool moved{false};
};

}

#endif
