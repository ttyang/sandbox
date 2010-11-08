// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_MULTI_ALGORITHMS_DETAIL_SECTIONS_GET_SECTION_HPP
#define BOOST_GEOMETRY_MULTI_ALGORITHMS_DETAIL_SECTIONS_GET_SECTION_HPP


// OBSOLETE
/*
#include <boost/assert.hpp>
#include <boost/concept/requires.hpp>
#include <boost/range.hpp>

#include <boost/geometry/multi/core/tags.hpp>

#include <boost/geometry/algorithms/detail/sections/get_section.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPolygon, typename Section, bool IsConst>
struct get_section<multi_polygon_tag, MultiPolygon, Section, IsConst>
{
    typedef typename boost::range_iterator
        <
            typename add_const_if_c
            <
                IsConst,
                typename geometry::range_type<MultiPolygon>::type
            >::type
        >::type iterator_type;

    static inline void apply(
                typename add_const_if_c
                    <
                        IsConst,
                        MultiPolygon
                    >::type const& multi_polygon,
                Section const& section,
                iterator_type& begin, iterator_type& end)
    {
        BOOST_ASSERT(
                section.multi_index >= 0
                && section.multi_index < boost::size(multi_polygon)
                );

        get_section
            <
                polygon_tag,
                typename boost::range_value<MultiPolygon>::type,
                Section,
                IsConst
            >::apply(multi_polygon[section.multi_index], section, begin, end);
    }
};


} // namespace dispatch
#endif


}} // namespace boost::geometry

*/

#endif // BOOST_GEOMETRY_MULTI_ALGORITHMS_DETAIL_SECTIONS_GET_SECTION_HPP
