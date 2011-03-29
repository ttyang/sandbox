/*=================================---------------------------------------------
Copyright 2009 Andrey Torba

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#include "pch.hpp"

#include <boost/guigl/application.hpp>
#include <boost/guigl/window.hpp>
#include <boost/guigl/view/positioned.hpp>
#include <boost/guigl/view/impl/positioned.hpp>

#include <boost/guigl/ggl.hpp>
#include <boost/guigl/gl.hpp>

#include <boost/foreach.hpp>

#include <boost/assign/std.hpp>

#include <geometry/geometry.hpp>

namespace geometry { namespace traits{
    template<class T>
    struct point_type<std::vector<T> >
    {
        typedef T type;
    };
}}

using namespace boost::guigl;

typedef view::positioned<> my_widget_base_type;
class my_widget : public my_widget_base_type
{
public:
    typedef my_widget_base_type base_type;

    template<typename ArgumentPack>
    my_widget(const ArgumentPack &args)
        : base_type(args)
    {}

    void draw_prologue()
    {
        base_type::draw_prologue();
        using namespace boost::assign;

        geometry::linear_ring<position_type> r;
        r.push_back(point<LT>());
        r.push_back(point<RB>());
        r.push_back(point<RT>());
        r.push_back(point<LB>());

        // linear_ring
        gl::color(yellow());
        gl::line_width(7);
        ggl::draw(r);

        // box
        gl::color(blue());
        gl::line_width(1);
        geometry::box<position_type> b(
            point<LT>(),
            point<RB>());
        ggl::draw(b);

        //// segment
        //gl::color(green(0.5f));
        //gl::line_width(2);
        //ggl::draw(segment<HC>());
        //ggl::draw(segment<VC>());

        //gl::color(red(0.2f));
        //gl::line_width(5);
        //ggl::draw(segment<D1>());
        //ggl::draw(segment<D2>());

        // std::vector as a ring
        gl::color(black());
        std::vector<position_type> v;
        v +=
            point<LC>(),
            point<CT>(),
            point<RC>(),
            point<CB>();
        ggl::draw<geometry::ring_tag>(v);

        // std::vector as a linestring
        gl::line_width(0.5);
        gl::color(white());
        ggl::draw<geometry::linestring_tag>(v);

        // polygon
        geometry::polygon<position_type> pg;

        // making outer contour
        pg.outer() +=
            point<LT>(),
            point<RT>(),
            point<RB>(),
            point<LB>();

        // making inner contour
        pg.inners().resize(1);
        std::copy(v.begin(), v.end(), std::back_inserter(pg.inners().back()));

        // correct polygon
        geometry::correct(pg);

        // drawing polygon
        gl::color(red(0.5));
        ggl::draw(pg);

        // drawing all points of polygon
        gl::color(blue(0.5));
        gl::point_size(10);
        glBegin(GL_POINTS);
        ggl::vertex(pg);
        glEnd();
    }

    void draw()
    {
        draw_prologue();
        draw_epilogue();
    }
};

int main()
{
    window wnd((
        _label = "GGL example",
        _size = size_type(500, 500),
        _background = white()
        ));

    wnd << new my_widget((
        _size = size_type(300, 300),
        _position = position_type(100, 100)
        ));

    application::run();
    return 0;
}