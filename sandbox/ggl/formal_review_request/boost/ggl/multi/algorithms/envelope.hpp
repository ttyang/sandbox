// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_MULTI_ALGORITHMS_ENVELOPE_HPP
#define GGL_MULTI_ALGORITHMS_ENVELOPE_HPP

#include <vector>

#include <ggl/core/exterior_ring.hpp>
#include <ggl/algorithms/envelope.hpp>

#include <ggl/multi/core/point_type.hpp>


namespace ggl
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail { namespace envelope {


template<typename MultiLinestring, typename Box>
struct envelope_multi_linestring
{
    static inline void apply(MultiLinestring const& mp, Box& mbr)
    {
        assign_inverse(mbr);
        for (typename boost::range_const_iterator<MultiLinestring>::type
                    it = mp.begin();
            it != mp.end();
            ++it)
        {
            envelope_range_additional(*it, mbr);
        }
    }
};


// version for multi_polygon: outer linear_ring's of all polygons
template<typename MultiPolygon, typename Box>
struct envelope_multi_polygon
{
    static inline void apply(MultiPolygon const& mp, Box& mbr)
    {
        assign_inverse(mbr);
        for (typename boost::range_const_iterator<MultiPolygon>::type
                    it = mp.begin();
            it != mp.end();
            ++it)
        {
            envelope_range_additional(exterior_ring(*it), mbr);
        }
    }
};


}} // namespace detail::envelope

#endif


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template 
<
    typename Multi, typename Box, 
    typename StrategyLess, typename StrategyGreater
>
struct envelope<multi_point_tag, box_tag, Multi, Box, StrategyLess, StrategyGreater>
    : detail::envelope::envelope_range<Multi, Box>
{};

template 
<
    typename Multi, typename Box, 
    typename StrategyLess, typename StrategyGreater
>
struct envelope<multi_linestring_tag, box_tag, Multi, Box, StrategyLess, StrategyGreater>
    : detail::envelope::envelope_multi_linestring<Multi, Box>
{};


template 
<
    typename Multi, typename Box, 
    typename StrategyLess, typename StrategyGreater
>
struct envelope<multi_polygon_tag, box_tag, Multi, Box, StrategyLess, StrategyGreater>
    : detail::envelope::envelope_multi_polygon<Multi, Box>
{};


} // namespace dispatch
#endif




} // namespace ggl


#endif // GGL_MULTI_ALGORITHMS_ENVELOPE_HPP
