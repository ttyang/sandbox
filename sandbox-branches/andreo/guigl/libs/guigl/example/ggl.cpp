/*=================================---------------------------------------------
Copyright 2009 Andrey Torba

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#include <boost/guigl/application.hpp>
#include <boost/guigl/window.hpp>
#include <boost/guigl/view/positioned.hpp>
#include <boost/guigl/view/impl/positioned.hpp>

#include <boost/guigl/ggl.hpp>
#include <boost/guigl/gl.hpp>

#include <boost/foreach.hpp>

#include <boost/assign/std.hpp>

#include <geometry/geometries/geometries.hpp>
#include <geometry/algorithms/correct.hpp>

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

        // segment
        gl::color(green(0.5f));
        gl::line_width(2);
        ggl::draw(segment<HC>());
        ggl::draw(segment<VC>());

        gl::color(red(0.2f));
        gl::line_width(5);
        ggl::draw(segment<D1>());
        ggl::draw(segment<D2>());

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
        pg.outer() +=
            point<LT>(),
            point<RT>(),
            point<RB>(),
            point<LB>();
        pg.inners().resize(1);
        std::copy(v.begin(), v.end(), std::back_inserter(pg.inners().back()));
        geometry::correct(pg);

        //gl::point_size(10);
        //gl::color(red());
        //glBegin(GL_POINTS);
        //ggl::vertex(pg);
        //glEnd();

        GLuint id = glGenLists(1);  // create a display list
        glNewList(id, GL_COMPILE);
        gl::color(red(0.5));

        {
            gl::tess t;
            gl::tess::polygon p(t);
            {
                gl::tess::polygon::contour c(p);
                BOOST_FOREACH(position_type const& pos, pg.outer())
                    c(pos);
            }
            BOOST_FOREACH(
                geometry::linear_ring<position_type> const& ring,
                pg.inners())
            {
                gl::tess::polygon::contour c(p);
                BOOST_FOREACH(position_type const& pos, ring)
                    c(pos);
            }
        }
        glEndList();

        glCallList(id);
    }

    BOOST_GUIGL_WIDGET_DRAW_IMPL(my_widget);
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
