#ifndef RAYLIBPP_RUNNER_RAYLIBPP_RUNNER_HPP
#define RAYLIBPP_RUNNER_RAYLIBPP_RUNNER_HPP

#include "canvas/canvas.hpp"
#include "sketch/sketch.hpp"
#include "raylibpp/raylibpp.hpp"

namespace raylibpp_runner {

template <sketch::Sketch S>
inline void run_sketch(S s)
{
    using namespace raylibpp;

    auto raylib = Raylib{S::width, S::height, S::name};
    raylib.set_target_fps(60);

    while (not raylib.should_close()) {
        auto c = canvas::Canvas{raylib.start_drawing()};

        s.draw(c);
    }
}

}

#endif
