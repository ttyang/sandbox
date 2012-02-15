// Boost.Polygon library voronoi.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI
#define BOOST_POLYGON_VORONOI

#include "voronoi_builder.hpp"
#include "voronoi_diagram.hpp"

// Public methods to compute voronoi diagram.
// points - container of input points (supports forward iterator).
// segments - container of input segments (supports forward iterator).
// output - voronoi output data structure to hold voronoi diagram.
// The assumption is made that input doesn't contain segments that intersect
// or points lying on the segments. Also coordinates of the points and of the
// endpoints of the segments should belong to the signed integer range
// [-2^31, 2^31-1]. To use wider input coordinate range use voronoi_builder
// structure with user provided coordinate traits.
// Complexity - O(N*logN), memory usage - O(N),
// where N is the total number of points and segments.
namespace boost {
namespace polygon {

template <typename PC, typename VD>
static inline void construct_voronoi_points(
    const PC &points, VD *output) {
  default_voronoi_builder builder;
  builder.insert_points(points.begin(), points.end());
  builder.construct(output);
  builder.clear();
}

template <typename SC, typename VD>
static inline void construct_voronoi_segments(
    const SC &segments, VD *output) {
  default_voronoi_builder builder;
  builder.insert_segments(segments.begin(), segments.end());
  builder.construct(output);
  builder.clear();
}

template <typename PC, typename SC, typename VD>
static inline void construct_voronoi(
    const PC &points, const SC &segments, VD *output) {
  default_voronoi_builder builder;
  builder.insert_sites(
    points.begin(), points.end(), segments.begin(), segments.end());
  builder.construct(output);
  builder.clear();
}
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI
