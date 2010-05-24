// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2010, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CLOSURE_HPP
#define BOOST_GEOMETRY_CORE_CLOSURE_HPP


#include <boost/range.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{


enum closure_selector { open = 0, closed = 1, closure_undertermined = -1 };

namespace traits
{

/*!
    \brief Traits class indicating if points within a
        ring or (multi)polygon are closed (last point == first point),
        open or not known.
    \ingroup traits
    \par Geometries:
        - ring
    \tparam G geometry
*/
template <typename G>
struct closure
{
    static const closure_selector value = closed;
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct closure
{
    static const closure_selector value = closed;
};


template <typename Ring>
struct closure<ring_tag, Ring>
{
    static const closure_selector value = geometry::traits::closure<Ring>::value;
};

// Specialization for polygon: the closure is the closure of its rings
template <typename Polygon>
struct closure<polygon_tag, Polygon>
{
    static const closure_selector value = core_dispatch::closure
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Meta-function which defines closure of any geometry
    \ingroup core
*/
template <typename Geometry>
struct closure
{
    static const closure_selector value = core_dispatch::closure
        <
            typename tag<Geometry>::type,
            typename boost::remove_const<Geometry>::type
        >::value;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_CLOSURE_HPP
