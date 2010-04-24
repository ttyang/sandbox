// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ENVELOPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ENVELOPE_HPP

#include <boost/range.hpp>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/combine.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

/*!
\defgroup envelope envelope: calculate envelope (minimum bounding rectangle) of a geometry
\par Source descriptions:
- OGC: Envelope (): Geometry - The minimum bounding rectangle (MBR) for this
    Geometry,
returned as a Geometry. The polygon is defined by the corner points of the
    bounding box
    [(MINX, MINY), (MAXX, MINY), (MAXX, MAXY), (MINX, MAXY), (MINX, MINY)].

\note Implemented in the Generic Geometry Library: The minimum bounding box,
    always as a box, having min <= max

The envelope algorithm calculates the bounding box, or envelope, of a geometry.
There are two versions:
- envelope, taking a reference to a box as second parameter
- make_envelope, returning a newly constructed box (type as a template parameter
    in the function call)

\par Geometries:
- \b point: a box with zero area, the maximum and the minimum point of the box are
set to the point itself.
- \b linestring, \b ring or \b range is the smallest box that contains all points of the
    specified point sequence.
If the linestring is empty, the envelope is the inverse infinite box, that is,
    the minimum point is very large (max infinite) and the maximum point is
    very small (min infinite).
- \b polygon, the envelope of the outer ring
\image html envelope_polygon.png

\par Example:
Example showing envelope calculation
\dontinclude doxygen_1.cpp
\skip example_envelope_linestring
\line {
\until }
*/

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


/// Calculate envelope of an 2D or 3D segment
template<typename Geometry, typename Box>
struct envelope_combine_one
{
    static inline void apply(Geometry const& geometry, Box& mbr)
    {
        assign_inverse(mbr);
        geometry::combine(mbr, geometry);
    }
};


/// Iterate through range (also used in multi*)
template<typename Range, typename Box>
inline void envelope_range_additional(Range const& range, Box& mbr)
{
    typedef typename boost::range_iterator<Range const>::type iterator_type;

    for (iterator_type it = boost::begin(range);
        it != boost::end(range);
        ++it)
    {
        geometry::combine(mbr, *it);
    }
}



/// Generic range dispatching struct
template <typename Range, typename Box>
struct envelope_range
{
    /// Calculate envelope of range using a strategy
    static inline void apply(Range const& range, Box& mbr)
    {
        assign_inverse(mbr);
        envelope_range_additional(range, mbr);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Note, the strategy is for future use (less/greater -> compare spherical
// using other methods), defaults are OK for now.
// However, they are already in the template methods

template
<
    typename Tag1, typename Tag2,
    typename Geometry, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope {};


template
<
    typename Point, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        point_tag, box_tag,
        Point, Box,
        StrategyLess, StrategyGreater
    >
    : detail::envelope::envelope_combine_one<Point, Box>
{};


template
<
    typename BoxIn, typename BoxOut,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        box_tag, box_tag,
        BoxIn, BoxOut,
        StrategyLess, StrategyGreater
    >
    : detail::envelope::envelope_combine_one<BoxIn, BoxOut>
{};


template
<
    typename Segment, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        segment_tag, box_tag,
        Segment, Box,
        StrategyLess, StrategyGreater
    >
    : detail::envelope::envelope_combine_one<Segment, Box>
{};


template
<
    typename Linestring, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        linestring_tag, box_tag,
        Linestring, Box,
        StrategyLess, StrategyGreater
    >
    : detail::envelope::envelope_range<Linestring, Box>
{};


template
<
    typename Ring, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        ring_tag, box_tag,
        Ring, Box,
        StrategyLess, StrategyGreater
    >
    : detail::envelope::envelope_range<Ring, Box>
{};


template
<
    typename Polygon, typename Box,
    typename StrategyLess, typename StrategyGreater
>
struct envelope
    <
        polygon_tag, box_tag,
        Polygon, Box,
        StrategyLess, StrategyGreater
    >
{
    static inline void apply(Polygon const& poly, Box& mbr)
    {
        // For polygon, inspecting outer ring is sufficient

        detail::envelope::envelope_range
            <
                typename ring_type<Polygon>::type,
                Box
            >::apply(exterior_ring(poly), mbr);
    }

};


} // namespace dispatch
#endif


/*!
\brief Calculate envelope of a geometry
\ingroup envelope
\param geometry the geometry
\param mbr the box receiving the envelope
\par Example:
Example showing envelope calculation, using point_ll latlong points
\dontinclude doxygen_1.cpp
\skip example_envelope_polygon
\line {
\until }
*/
template<typename Geometry, typename Box>
inline void envelope(Geometry const& geometry, Box& mbr)
{
    concept::check<const Geometry>();
    concept::check<Box>();

    dispatch::envelope
        <
            typename tag<Geometry>::type, typename tag<Box>::type,
            Geometry, Box,
            void, void
        >::apply(geometry, mbr);
}


/*!
\brief Calculate and return envelope of a geometry
\ingroup envelope
\param geometry the geometry
*/
template<typename Box, typename Geometry>
inline Box make_envelope(Geometry const& geometry)
{
    concept::check<const Geometry>();
    concept::check<Box>();

    Box mbr;
    dispatch::envelope
        <
            typename tag<Geometry>::type, typename tag<Box>::type,
            Geometry, Box,
            void, void
        >::apply(geometry, mbr);
    return mbr;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_ENVELOPE_HPP
