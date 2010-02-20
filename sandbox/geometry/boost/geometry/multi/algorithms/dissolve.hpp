// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2010, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_MULTI_ALGORITHMS_DISSOLVE_HPP
#define BOOST_GEOMETRY_MULTI_ALGORITHMS_DISSOLVE_HPP


#include <boost/geometry/multi/core/tags.hpp>
#include <boost/geometry/algorithms/dissolve.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Multi,
    typename OutputIterator
>
struct dissolve
    <
        multi_polygon_tag,
        Multi,
        OutputIterator
    >
    : detail::dissolve::dissolve_region<Multi, OutputIterator>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_MULTI_ALGORITHMS_DISSOLVE_HPP
