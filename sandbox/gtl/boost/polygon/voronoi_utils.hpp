// Boost.Polygon library voronoi_utils.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_UTILS
#define BOOST_POLYGON_VORONOI_UTILS

#include <cmath>
#include <stack>
#include <vector>

#include "voronoi_diagram.hpp"

namespace boost {
namespace polygon {

template <typename fpt_>
struct voronoi_utils_traits;

template<>
struct voronoi_utils_traits<double> {
  typedef double coordinate_type;
  typedef detail::point_2d<coordinate_type> point_type;
  typedef std::vector<point_type> point_set_type;
  typedef bounding_rectangle<coordinate_type> brect_type;
  typedef struct {
    template <typename CT>
      coordinate_type operator()(const CT& value) const {
        return static_cast<coordinate_type>(value);
    }
  } ctype_converter_type;
};

// Voronoi output post-processing tools.
template <typename T, typename TRAITS = voronoi_utils_traits<T> >
class voronoi_utils {
public:
  typedef typename TRAITS::coordinate_type coordinate_type;
  typedef typename TRAITS::point_type point_type;
  typedef typename TRAITS::point_set_type point_set_type;
  typedef typename TRAITS::brect_type brect_type;
  typedef typename TRAITS::ctype_converter_type ctype_converter_type;

  // There are three different types of linear primitive:
  //   1) SEGMENT - has two finite endpoints;
  //   2) RAY - has one finite and one infinite endpoint;
  //   3) LINE - has two infinite endpoints.
  enum EdgeType {
    SEGMENT = 0,
    RAY = 1,
    LINE = 2
  };

  // Get scaled by a factor bounding rectangle.
  template <typename CT>
  static brect_type scale(const bounding_rectangle<CT> &brect,
                          coordinate_type factor = 1.0) {
    coordinate_type x_len = to_fpt(brect.x_max()) - to_fpt(brect.x_min());
    coordinate_type y_len = to_fpt(brect.y_max()) - to_fpt(brect.y_min());
    coordinate_type x_mid = to_fpt(brect.x_max()) + to_fpt(brect.x_min());
    coordinate_type y_mid = to_fpt(brect.y_max()) + to_fpt(brect.y_min());
    x_mid *= to_fpt(0.5);
    y_mid *= to_fpt(0.5);
    coordinate_type offset = (std::max)(x_len, y_len) * factor * to_fpt(0.5);
    brect_type new_brect(x_mid - offset, y_mid - offset,
                         x_mid + offset, y_mid + offset);
    return new_brect;
  }

  // Discretize voronoi edge. Infinite edges are clipped by the input
  // rectangle. Finite edges are not clipped at all.
  // Max_error is the maximum distance (relative to the minor of two
  // rectangle sides) allowed between the parabola and line segments
  // that discretize it.
  template <typename CT>
  static void discretize(const voronoi_edge<CT> &edge,
                         const bounding_rectangle<CT> &brect,
                         coordinate_type max_error,
                         point_set_type &discretization) {
    // Retrieve the cell to the left of the current edge.
    const typename voronoi_edge<CT>::voronoi_cell_type *cell1 = edge.cell();

    // Retrieve the cell to the right of the current edge.
    const typename voronoi_edge<CT>::voronoi_cell_type *cell2 =
        edge.twin()->cell();

    if (!(cell1->contains_segment() ^ cell2->contains_segment())) {
      // Edge is a segment, ray, or line.
      if (edge.vertex0() != NULL && edge.vertex1() != NULL) {
        // Edge is a segment. No further processing is required.
        discretization.push_back(get_point(edge.vertex0()->vertex()));
        discretization.push_back(get_point(edge.vertex1()->vertex()));
      } else {
        // Edge is a ray or line.
        // Clip it with the bounding rectangle.
        const point_type &site1 = get_point(cell1->point0());
        const point_type &site2 = get_point(cell2->point0());
        point_type origin((site1.x() + site2.x()) * to_fpt(0.5),
                          (site1.y() + site2.y()) * to_fpt(0.5));
        point_type direction(site1.y() - site2.y(), site2.x() - site1.x());

        // Find intersection points.
        intersect(origin, direction, LINE, get_brect(brect), discretization);

        // Update endpoints in case edge is a ray.
        if (edge.vertex1() != NULL)
          discretization[1] = get_point(edge.vertex1()->vertex());
        if (edge.vertex0() != NULL)
          discretization[0] = get_point(edge.vertex0()->vertex());
      }
    } else {
      // point1 - site point;
      const point_type &point1 = (cell1->contains_segment()) ?
          get_point(cell2->point0()) : get_point(cell1->point0());

      // point2 - start-point of the segment site;
      const point_type &point2 = (cell1->contains_segment()) ?
          get_point(cell1->point0()) : get_point(cell2->point0());

      // point3 - endpoint of the segment site;
      const point_type &point3 = (cell1->contains_segment()) ?
          get_point(cell1->point1()) : get_point(cell2->point1());

      if (edge.vertex0() != NULL && edge.vertex1() != NULL) {
        // Edge is a segment or parabolic arc.
        discretization.push_back(get_point(edge.vertex0()->vertex()));
        discretization.push_back(get_point(edge.vertex1()->vertex()));
        coordinate_type x_len = to_fpt(brect.x_max()) - to_fpt(brect.x_min());
        coordinate_type y_len = to_fpt(brect.y_max()) - to_fpt(brect.y_min());
        coordinate_type max_dist = max_error * (std::min)(x_len, y_len);
        fill_intermediate_points(point1, point2, point3,
                                 discretization, max_dist);
      } else {
        // Edge is a ray or line.
        // Clip it with the bounding rectangle.
        coordinate_type dir_x =
            (cell1->contains_segment() ^ (point1 == point3)) ?
            point3.y() - point2.y() : point2.y() - point3.y();
        coordinate_type dir_y =
            (cell1->contains_segment() ^ (point1 == point3)) ?
            point2.x() - point3.x() : point3.x() - point2.x();
        point_type direction(dir_x, dir_y);

        // Find intersection points.
        intersect(point1, direction, LINE, brect, discretization);

        // Update endpoints in case edge is a ray.
        if (edge.vertex1() != NULL)
          discretization[1] = get_point(edge.vertex1()->vertex());
        if (edge.vertex0() != NULL)
          discretization[0] = get_point(edge.vertex0()->vertex());
      }
    }
  }

  // Find edge-rectangle intersection points.
  // Edge is represented by its origin, direction and type.
  static void intersect(const point_type &origin,
                        const point_type &direction,
                        EdgeType edge_type,
                        const brect_type &brect,
                        point_set_type &intersections) {
    // Find the center of the rectangle.
    coordinate_type center_x = (brect.x_min() + brect.x_max()) * to_fpt(0.5);
    coordinate_type center_y = (brect.y_min() + brect.y_max()) * to_fpt(0.5);

    // Find the half-diagonal vector of the rectangle.
    coordinate_type len_x = brect.x_max() - center_x;
    coordinate_type len_y = brect.y_max() - center_y;

    // Find the vector between the origin and the center of the
    // rectangle.
    coordinate_type diff_x = origin.x() - center_x;
    coordinate_type diff_y = origin.y() - center_y;

    // Find the vector perpendicular to the direction vector.
    coordinate_type perp_x = direction.y();
    coordinate_type perp_y = -direction.x();

    // Projection of the vector between the origin and the center of
    // the rectangle on the line perpendicular to the direction vector.
    coordinate_type lexpr = magnitude(perp_x * diff_x + perp_y * diff_y);

    // Maximum projection among any of the half-diagonals of the
    // rectangle on the line perpendicular to the direction vector.
    coordinate_type rexpr = magnitude(perp_x * len_x) +
                            magnitude(perp_y * len_y);

    // Intersection check. Compare projections.
    if (lexpr > rexpr)
      return;

    // Intersection parameters. If fT[i]_used is true than:
    // origin + fT[i] * direction = intersection point, i = 0 .. 1.
    // For different edge types next fT values are acceptable:
    // Segment: [0; 1];
    // Ray: [0; infinity];
    // Line: [-infinity; infinity].
    bool fT0_used = false;
    bool fT1_used = false;
    coordinate_type fT0 = 0;
    coordinate_type fT1 = 0;

    // Check for the intersections with the lines
    // going through the sides of the bounding rectangle.
    clip_line(+direction.x(), -diff_x - len_x, fT0_used, fT1_used, fT0, fT1);
    clip_line(-direction.x(), +diff_x - len_x, fT0_used, fT1_used, fT0, fT1);
    clip_line(+direction.y(), -diff_y - len_y, fT0_used, fT1_used, fT0, fT1);
    clip_line(-direction.y(), +diff_y - len_y, fT0_used, fT1_used, fT0, fT1);

    // Update intersections vector.
    if (fT0_used && check_extent(fT0, edge_type))
      intersections.push_back(point_type(origin.x() + fT0 * direction.x(),
                                         origin.y() + fT0 * direction.y()));
    if (fT1_used && fT0 != fT1 && check_extent(fT1, edge_type))
      intersections.push_back(point_type(origin.x() + fT1 * direction.x(),
                                         origin.y() + fT1 * direction.y()));
  }

private:
  voronoi_utils();

  template <typename P>
  static point_type get_point(const P &point) {
    coordinate_type x = to_fpt(point.x());
    coordinate_type y = to_fpt(point.y());
    return point_type(x, y);
  }

  template <typename CT>
  static brect_type get_brect(const bounding_rectangle<CT> &rect) {
    coordinate_type x1 = to_fpt(rect.x_min());
    coordinate_type y1 = to_fpt(rect.y_min());
    coordinate_type x2 = to_fpt(rect.x_max());
    coordinate_type y2 = to_fpt(rect.y_max());
    return brect_type(x1, y1, x2, y2);
  }

  // Find intermediate points of the parabola.
  // Parabola is a locus of points equidistant from the point and segment
  // sites. intermediate_points should contain two initial endpoints
  // of the edge (voronoi vertices). Intermediate points are inserted
  // between the given two endpoints.
  // Max_dist is the maximum distance allowed between parabola and line
  // segments that discretize it.
  static void fill_intermediate_points(point_type point_site,
                                       point_type segment_site_start,
                                       point_type segment_site_end,
                                       point_set_type &intermediate_points,
                                       coordinate_type max_dist) {
    // Check if bisector is a segment.
    if (point_site == segment_site_start ||
        point_site == segment_site_end)
      return;

    // Apply the linear transformation to move start point of the
    // segment to the point with coordinates (0, 0) and the direction
    // of the segment to coincide the positive direction of the x-axis.
    coordinate_type segm_vec_x = segment_site_end.x() -
                                 segment_site_start.x();
    coordinate_type segm_vec_y = segment_site_end.y() -
                                 segment_site_start.y();
    coordinate_type sqr_segment_length = segm_vec_x * segm_vec_x +
                                         segm_vec_y * segm_vec_y;

    // Compute x-coordinates of the endpoints of the edge
    // in the transformed space.
    coordinate_type projection_start = sqr_segment_length *
        get_point_projection(intermediate_points[0],
                             segment_site_start,
                             segment_site_end);
    coordinate_type projection_end = sqr_segment_length *
        get_point_projection(intermediate_points[1],
                             segment_site_start,
                             segment_site_end);

    // Compute parabola parameters in the transformed space.
    // Parabola has next representation:
    // f(x) = ((x-rot_x)^2 + rot_y^2) / (2.0*rot_y).
    coordinate_type point_vec_x = point_site.x() - segment_site_start.x();
    coordinate_type point_vec_y = point_site.y() - segment_site_start.y();
    coordinate_type rot_x = segm_vec_x * point_vec_x +
                            segm_vec_y * point_vec_y;
    coordinate_type rot_y = segm_vec_x * point_vec_y -
                            segm_vec_y * point_vec_x;

    // Save the last point.
    point_type last_point = intermediate_points[1];
    intermediate_points.pop_back();

    // Use stack to avoid recursion.
    std::stack<coordinate_type> point_stack;
    point_stack.push(projection_end);
    coordinate_type cur_x = projection_start;
    coordinate_type cur_y = parabola_y(cur_x, rot_x, rot_y);

    // Adjust max_dist parameter in the transformed space.
    max_dist *= max_dist * sqr_segment_length;

    while (!point_stack.empty()) {
      coordinate_type new_x = point_stack.top();
      coordinate_type new_y = parabola_y(new_x, rot_x, rot_y);

      // Compute coordinates of the point of the parabola that is
      // furthest from the current line segment.
      coordinate_type mid_x = (new_y - cur_y) / (new_x - cur_x) * rot_y +
                              rot_x;
      coordinate_type mid_y = parabola_y(mid_x, rot_x, rot_y);

      // Compute maximum distance between the given parabolic arc
      // and line segment that discretize it.
      coordinate_type dist = (new_y - cur_y) * (mid_x - cur_x) -
                             (new_x - cur_x) * (mid_y - cur_y);
      dist = dist * dist / ((new_y - cur_y) * (new_y - cur_y) +
             (new_x - cur_x) * (new_x - cur_x));
      if (dist <= max_dist) {
        // Distance between parabola and line segment is
        // not greater than max_dist.
        point_stack.pop();
        coordinate_type inter_x = (segm_vec_x * new_x - segm_vec_y * new_y) /
                                  sqr_segment_length + segment_site_start.x();
        coordinate_type inter_y = (segm_vec_x * new_y + segm_vec_y * new_x) /
                                  sqr_segment_length + segment_site_start.y();
        intermediate_points.push_back(point_type(inter_x, inter_y));
        cur_x = new_x;
        cur_y = new_y;
      } else {
        point_stack.push(mid_x);
      }
    }

    // Update last point.
    intermediate_points.back() = last_point;
  }

  // Compute y(x) = ((x - a) * (x - a) + b * b) / (2 * b).
  static coordinate_type parabola_y(coordinate_type x,
                                    coordinate_type a,
                                    coordinate_type b) {
    return ((x - a) * (x - a) + b * b) / (to_fpt(2.0) * b);
  }

  // Check whether extent is compatible with the edge type.
  static bool check_extent(coordinate_type extent, EdgeType etype) {
    switch (etype) {
      case SEGMENT: return extent >= to_fpt(0.0) && extent <= to_fpt(1.0);
      case RAY: return extent >= to_fpt(0.0);
      case LINE: return true;
    }
    return true;
  }

  // Compute the absolute value.
  static inline coordinate_type magnitude(coordinate_type value) {
    return (value >= to_fpt(0.0)) ? value : -value;
  }

  // Find fT min and max values: fT = numer / denom.
  static void clip_line(coordinate_type denom,
                        coordinate_type numer,
                        bool &fT0_used,
                        bool &fT1_used,
                        coordinate_type &fT0,
                        coordinate_type &fT1) {
    if (denom > to_fpt(0.0)) {
      if (fT1_used && numer > denom * fT1)
        return;
      if (!fT0_used || numer > denom * fT0) {
        fT0_used = true;
        fT0 = numer / denom;
      }
    } else if (denom < to_fpt(0.0)) {
      if (fT0_used && numer > denom * fT0)
        return;
      if (!fT1_used || numer > denom * fT1) {
        fT1_used = true;
        fT1 = numer / denom;
      }
    }
  }

  // Get normalized length of the distance between:
  //   1) point projection onto the segment;
  //   2) start point of the segment.
  // Return this length divided by the segment length.
  // This is made to avoid sqrt computation during transformation from
  // the initial space to the transformed one and vice versa.
  // Assumption is made that projection of the point lies
  // between the start-point and endpoint of the segment.
  static coordinate_type get_point_projection(
      const point_type &point,
      const point_type &segment_start,
      const point_type &segment_end) {
    coordinate_type segment_vec_x = segment_end.x() - segment_start.x();
    coordinate_type segment_vec_y = segment_end.y() - segment_start.y();
    coordinate_type point_vec_x = point.x() - segment_start.x();
    coordinate_type point_vec_y = point.y() - segment_start.y();
    coordinate_type sqr_segment_length = segment_vec_x * segment_vec_x +
                                         segment_vec_y * segment_vec_y;
    coordinate_type vec_dot = segment_vec_x * point_vec_x +
                              segment_vec_y * point_vec_y;
    return vec_dot / sqr_segment_length;
  }

  template <typename CT>
  static coordinate_type to_fpt(const CT& value) {
    static ctype_converter_type converter;
    return converter(value);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI_UTILS
