#ifndef CANVAS_CANVAS_HPP
#define CANVAS_CANVAS_HPP

#include <memory>
#include "math/geom/vec2.hpp"

#include "color/color.hpp"

namespace canvas {

class Canvas {
public:
    template <typename D>
    Canvas(D d):
        inner{std::make_unique<Inner<D>>(std::move(d))}
    {}

    void fill(color::ColorRGBA const& c)
    {
        inner->fill(c);
    }

    void stroke(color::ColorRGBA const& c)
    {
        inner->stroke(c);
    }

    void no_fill()
    {
        inner->no_fill();
    }

    void no_stroke()
    {
        inner->no_stroke();
    }

    void draw_line(math::geom::Vec2 const& v1, math::geom::Vec2 const& v2)
    {
        inner->draw_line(v1, v2);
    }

    void draw_circle(math::geom::Vec2 const& center, double radius)
    {
        inner->draw_circle(center, radius);
    }

    void clear_background(color::ColorRGBA const& c)
    {
        inner->clear_background(c);
    }

private:
    struct InnerBase {
        virtual ~InnerBase() = default;
        virtual void fill(color::ColorRGBA const& c) = 0;
        virtual void stroke(color::ColorRGBA const& c) = 0;
        virtual void no_fill() = 0;
        virtual void no_stroke() = 0;
        virtual void draw_line(math::geom::Vec2 const& v1, math::geom::Vec2 const& v2) = 0;
        virtual void draw_circle(math::geom::Vec2 const& center, double radius) = 0;
        virtual void clear_background(color::ColorRGBA const& c) = 0;
    };

    template <typename D>
    struct Inner: public InnerBase {
        Inner(D d):
            d_{std::move(d)}
        {}

        void fill(color::ColorRGBA const& c) override
        {
            d_.fill(c);
        }

        void stroke(color::ColorRGBA const& c) override
        {
            d_.stroke(c);
        }

        void no_fill() override
        {
            d_.no_fill();
        }

        void no_stroke() override
        {
            d_.no_stroke();
        }

        void draw_line(math::geom::Vec2 const& v1, math::geom::Vec2 const& v2) override
        {
            d_.draw_line(v1, v2);
        }

        void draw_circle(math::geom::Vec2 const& center, double radius) override
        {
            d_.draw_circle(center, radius);
        }

        void clear_background(color::ColorRGBA const& c) override
        {
            d_.clear_background(c);
        }

        D d_;
    };

    std::unique_ptr<InnerBase> inner;
};

}

#endif
