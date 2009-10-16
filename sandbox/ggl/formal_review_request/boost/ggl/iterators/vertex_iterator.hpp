// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef GGL_ITERATORS_VERTEX_ITERATOR_HPP
#define GGL_ITERATORS_VERTEX_ITERATOR_HPP


#include <boost/type_traits/remove_const.hpp>
#include <boost/range/metafunctions.hpp>


#include <ggl/core/tag.hpp>
#include <ggl/core/tags.hpp>
#include <ggl/core/ring_type.hpp>


namespace ggl
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Tag, typename Geometry, bool IsConst>
struct vertex_iterator
{};


template <typename Tag, typename Geometry>
struct vertex_iterator<Tag, Geometry, true>
{
    // For most geometries: meta-forward this to boost
    // This enables calling this function using std::vector as well, even if they
    // are not registered.
    // It also requires less specializations
    typedef typename boost::range_const_iterator<Geometry>::type type;
};

template <typename Tag, typename Geometry>
struct vertex_iterator<Tag, Geometry, false>
{
    typedef typename boost::range_iterator<Geometry>::type type;
};




template <typename Polygon>
struct vertex_iterator<polygon_tag, Polygon, false>
{
    typedef typename boost::range_iterator
        <
            typename ggl::ring_type<Polygon>::type
        >::type type;
};



template <typename Polygon>
struct vertex_iterator<polygon_tag, Polygon, true>
{
    typedef typename boost::range_const_iterator
        <
            typename ggl::ring_type<Polygon>::type
        >::type type;
};





} // namespace dispatch
#endif


/*!
    \brief Meta-function which defines vertex_iterator type
    \details The vertex_iterator meta-function enables approaching
        any geometry with the same type of iterator. It is used within
        the library in conjuction with sections.
        A section defines a part of a geometry (linestring, polygon:
        outer ring or inner ring). The library, at that point, does not
        need to know if it is a polygon, multi-polygon or ring. Using
        this meta-function it still does not need to know that.
    \tparam Geometry the geometry type
    \tparam is_const: true if const iterator is defined, else false
    \ingroup iterators
*/
template <typename Geometry, bool IsConst>
struct vertex_iterator
{
    typedef typename dispatch::vertex_iterator
        <
            typename tag<Geometry>::type,
            typename boost::remove_const<Geometry>::type,
            IsConst
        >::type type;
};



}


#endif // GGL_ITERATORS_VERTEX_ITERATOR_HPP
