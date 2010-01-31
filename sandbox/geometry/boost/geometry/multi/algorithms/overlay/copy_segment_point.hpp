// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2010, Geodan, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_MULTI_ALGORITHMS_OVERLAY_COPY_SEGMENT_POINT_HPP
#define BOOST_GEOMETRY_MULTI_ALGORITHMS_OVERLAY_COPY_SEGMENT_POINT_HPP


#include <boost/range/functions.hpp>
#include <boost/range/metafunctions.hpp>

#include <boost/geometry/multi/core/tags.hpp>
#include <boost/geometry/algorithms/overlay/copy_segment_point.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace copy_segments
{


template
<
    typename MultiGeometry,
    typename SegmentIdentifier,
    typename PointOut,
    typename Policy
>
struct copy_segment_point_multi
{
    static inline bool apply(MultiGeometry const& multi,
                SegmentIdentifier const& seg_id, bool second,
                PointOut& point)
    {

        BOOST_ASSERT
            (
                seg_id.multi_index >= 0
                && seg_id.multi_index < boost::size(multi)
            );

        // Call the single-version
        return Policy::apply(multi[seg_id.multi_index], seg_id, second, point);
    }
};


}} // namespace detail::copy_segments
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename MultiGeometry,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
    <
        multi_polygon_tag,
        MultiGeometry,
        SegmentIdentifier,
        PointOut
    >
    : detail::copy_segments::copy_segment_point_multi
        <
            MultiGeometry,
            SegmentIdentifier,
            PointOut,
            detail::copy_segments::copy_segment_point_polygon
                <
                    typename boost::range_value<MultiGeometry>::type,
                    SegmentIdentifier,
                    PointOut
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_MULTI_ALGORITHMS_OVERLAY_COPY_SEGMENT_POINT_HPP
