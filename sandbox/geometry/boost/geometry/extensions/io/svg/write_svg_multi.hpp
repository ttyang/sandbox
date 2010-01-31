// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_SVG_WRITE_SVG_MULTI_HPP
#define BOOST_GEOMETRY_IO_SVG_WRITE_SVG_MULTI_HPP


#include <boost/geometry/extensions/io/svg/write_svg.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace svg {


template <typename MultiGeometry, typename Policy>
struct svg_multi
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        MultiGeometry const& multi, std::string const& style, int size)
    {
        for (typename boost::range_const_iterator<MultiGeometry>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(os, *it, style, size);
        }

    }

};



}} // namespace detail::svg
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {


template <typename MultiPolygon>
struct svg<multi_polygon_tag, MultiPolygon>
    : detail::svg::svg_multi
        <
            MultiPolygon,
            detail::svg::svg_poly
                <
                    typename boost::range_value<MultiPolygon>::type
                >

        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_SVG_WRITE_SVG_MULTI_HPP
