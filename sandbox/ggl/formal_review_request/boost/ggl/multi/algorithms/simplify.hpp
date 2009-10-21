// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_MULTI_ALGORITHMS_SIMPLIFY_HPP
#define GGL_MULTI_ALGORITHMS_SIMPLIFY_HPP

#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>

#include <ggl/multi/core/tags.hpp>
#include <ggl/multi/core/is_multi.hpp>

#include <ggl/multi/util/as_range.hpp>

#include <ggl/algorithms/simplify.hpp>


namespace ggl
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace simplify {

template<typename MultiGeometry, typename Strategy, typename Policy>
struct simplify_multi
{
    static inline void apply(MultiGeometry const& multi, MultiGeometry& out,
                    double max_distance, Strategy const& strategy)
    {
        out.resize(boost::size(multi));

        typename boost::range_iterator<MultiGeometry>::type it_out 
                = boost::begin(out);
        for (typename boost::range_const_iterator<MultiGeometry>::type it_in 
                    = boost::begin(multi); 
            it_in != boost::end(multi); 
            ++it_in, ++it_out)
        {
            Policy::apply(*it_in, *it_out, max_distance, strategy);
        }
    }
};



}} // namespace detail::simplify
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename MultiPoint, typename Strategy>
struct simplify<multi_point_tag, MultiPoint, Strategy>
    : detail::simplify::simplify_copy
        <
            MultiPoint,
            Strategy
        >

{};


template <typename MultiLinestring, typename Strategy>
struct simplify<multi_linestring_tag, MultiLinestring, Strategy>
    : detail::simplify::simplify_multi
        <
            MultiLinestring,
            Strategy,
            detail::simplify::simplify_range
                <
                    typename boost::range_value<MultiLinestring>::type,
                    Strategy,
                    2
                >
        >

{};


template <typename MultiPolygon, typename Strategy>
struct simplify<multi_polygon_tag, MultiPolygon, Strategy>
    : detail::simplify::simplify_multi
        <
            MultiPolygon,
            Strategy,
            detail::simplify::simplify_polygon
                <
                    typename boost::range_value<MultiPolygon>::type,
                    Strategy
                >
        >

{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


} // namespace ggl


#endif // GGL_MULTI_ALGORITHMS_SIMPLIFY_HPP
