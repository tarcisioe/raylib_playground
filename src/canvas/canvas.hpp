#ifndef CANVAS_CANVAS_HPP
#define CANVAS_CANVAS_HPP

#include <memory>
#include "math/geom/vec2.hpp"

namespace canvas {

class Canvas {
public:
    template <typename D>
    Canvas(D d):
        inner{std::make_unique<Inner<D>>(std::move(d))}
    {}

    void draw_circle(math::geom::Vec2 const& center, double radius)
    {
        inner->draw_circle(center, radius);
    }

private:
    struct InnerBase {
        virtual ~InnerBase() = default;
        virtual void draw_circle(math::geom::Vec2 const& center, double radius) = 0;
    };

    template <typename D>
    struct Inner: public InnerBase {
        Inner(D d):
            d_{std::move(d)}
        {}

        void draw_circle(math::geom::Vec2 const& center, double radius) override
        {
            d_.draw_circle(center, radius);
        }

        D d_;
    };

    std::unique_ptr<InnerBase> inner;
};

}

#endif
