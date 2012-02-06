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

#include "polygon.hpp"
#include "voronoi_diagram.hpp"

namespace boost {
namespace polygon {

template <typename fpt_>
struct voronoi_utils_traits;

template<>
struct voronoi_utils_traits<double> {
    typedef double fpt_type;
    typedef point_data<fpt_type> point_type;
    typedef std::vector<point_type> point_set_type;
    typedef directed_line_segment_data<fpt_type> segment_type;
    typedef directed_line_segment_set_data<fpt_type> segment_set_type;
    typedef bounding_rectangle<fpt_type> brect_type;
    typedef struct {
        template <typename CT>
        fpt_type operator()(const CT& value) {
            return static_cast<fpt_type>(value);
        }
    } ctype_converter_type;
};

// Voronoi output postprocessing tools.
template <typename T, typename TRAITS = voronoi_utils_traits<T> >
class voronoi_utils {
public:
    typedef typename TRAITS::fpt_type fpt_type;
    typedef typename TRAITS::point_type point_type;
    typedef typename TRAITS::point_set_type point_set_type;
    typedef typename TRAITS::segment_type segment_type;
    typedef typename TRAITS::segment_set_type segment_set_type;
    typedef typename TRAITS::brect_type brect_type;
    typedef typename TRAITS::ctype_converter_type ctype_converter_type;

    // There are three different types of edges:
    //   1) Segment edge - has both endpoints;
    //   2) Ray edge - has one endpoint, infinite
    //                 in the positive direction;
    //   3) Line edge - is infinite in both directions.
    enum kEdgeType {
        SEGMENT = 0,
        RAY = 1,
        LINE = 2
    };

    // Get a view rectangle based on the voronoi bounding rectangle.
    template <typename CT>
    static brect_type get_view_rectangle(const bounding_rectangle<CT> &brect,
                                         fpt_type scale = 1.0) {
        fpt_type x_len = to_fpt(brect.x_max()) - to_fpt(brect.x_min());
        fpt_type y_len = to_fpt(brect.y_max()) - to_fpt(brect.y_min());
        fpt_type x_mid = to_fpt(brect.x_max()) + to_fpt(brect.x_min());
        fpt_type y_mid = to_fpt(brect.y_max()) + to_fpt(brect.y_min());
        x_mid *= to_fpt(0.5);
        y_mid *= to_fpt(0.5);
        fpt_type offset = (std::max)(x_len, y_len) * scale * to_fpt(0.5);
        brect_type new_brect(x_mid - offset, y_mid - offset,
                             x_mid + offset, y_mid + offset);
        return new_brect;
    }

    // Compute intermediate points for the voronoi edge within the given
    // bounding rectangle. The assumption is made that voronoi rectangle
    // contains all the finite endpoints of the edge.
    // Max_error is the maximum distance (relative to the minor of two
    // rectangle sides) allowed between the parabola and line segments
    // that interpolate it.
    template <typename CT>
    static point_set_type get_point_interpolation(
        const voronoi_edge<CT> *edge,
        const bounding_rectangle<CT> &brect,
        fpt_type max_error) {
        // Retrieve the cell to the left of the current edge.
        const typename voronoi_edge<CT>::voronoi_cell_type *cell1 = edge->cell();

        // Retrieve the cell to the right of the current edge.
        const typename voronoi_edge<CT>::voronoi_cell_type *cell2 = edge->twin()->cell();

        // edge_points - contains intermediate points.
        point_set_type edge_points;
        if (!(cell1->contains_segment() ^ cell2->contains_segment())) {
            // Edge is a segment, ray, or line.
            if (edge->vertex0() != NULL && edge->vertex1() != NULL) {
                // Edge is a segment. No further processing is required.
                edge_points.push_back(
                    get_point(edge->vertex0()->vertex()));
                edge_points.push_back(
                    get_point(edge->vertex1()->vertex()));
            } else {
                // Edge is a ray or line.
                // Clip it with the bounding rectangle.
                const point_type &site1 = get_point(cell1->point0());
                const point_type &site2 = get_point(cell2->point0());
                point_type origin((site1.x() + site2.x()) * to_fpt(0.5),
                                  (site1.y() + site2.y()) * to_fpt(0.5));
                point_type direction(site1.y() - site2.y(),
                                     site2.x() - site1.x());

                // Find intersection points.
                find_intersections(origin, direction, LINE,
                                   brect, edge_points);

                // Update endpoints in case edge is a ray.
                if (edge->vertex1() != NULL)
                    edge_points[1] = get_point(edge->vertex1()->vertex());
                if (edge->vertex0() != NULL)
                    edge_points[0] = get_point(edge->vertex0()->vertex());
            }
        } else {
            // point1 - site point;
            const point_type &point1 = (cell1->contains_segment()) ?
                get_point(cell2->point0()) : get_point(cell1->point0());

            // point2 - startpoint of the segment site;
            const point_type &point2 = (cell1->contains_segment()) ?
                get_point(cell1->point0()) : get_point(cell2->point0());

            // point3 - endpoint of the segment site;
            const point_type &point3 = (cell1->contains_segment()) ?
                get_point(cell1->point1()) : get_point(cell2->point1());

            if (edge->vertex0() != NULL && edge->vertex1() != NULL) {
                // Edge is a segment or parabolic arc.
                edge_points.push_back(
                    get_point(edge->vertex0()->vertex()));
                edge_points.push_back(
                    get_point(edge->vertex1()->vertex()));
                fpt_type max_dist = max_error * brect.min_len();
                fill_intermediate_points(point1, point2, point3,
                                         edge_points, max_dist);
            } else {
                // Edge is a ray or line.
                // Clip it with the bounding rectangle.
                fpt_type dir_x =
                    (cell1->contains_segment() ^ (point1 == point3)) ?
                    point3.y() - point2.y() : point2.y() - point3.y();
                fpt_type dir_y =
                    (cell1->contains_segment() ^ (point1 == point3)) ?
                    point2.x() - point3.x() : point3.x() - point2.x();
                point_type direction(dir_x, dir_y);

                // Find intersection points.
                find_intersections(point1, direction, LINE,
                                   brect, edge_points);

                // Update endpoints in case edge is a ray.
                if (edge->vertex1() != NULL)
                    edge_points[1] = get_point(edge->vertex1()->vertex());
                if (edge->vertex0() != NULL)
                    edge_points[0] = get_point(edge->vertex0()->vertex());
            }
        }
        return edge_points;
    }

    // Interpolate voronoi edge with a set of segments to satisfy maximal
    // error requirement.
    template <typename CT>
    static segment_set_type get_segment_interpolation(
        const voronoi_edge<CT> *edge,
        const bounding_rectangle<CT> &brect,
        fpt_type max_error) {
        point_set_type point_interpolation =
            get_point_interpolcation(edge, brect, max_error);
        segment_set_type ret_val;
        for (size_t i = 1; i < point_interpolation.size(); ++i)
            ret_val.insert(segment_type(point_interpolation[i-1],
                                        point_interpolation[i]));
        return ret_val;
    }

    // Find edge-rectangle intersection points.
    // Edge is represented by its origin, direction and type.
    static void find_intersections(
            const point_type &origin, const point_type &direction,
            kEdgeType edge_type, const brect_type &brect,
            point_set_type &intersections) {
        // Find the center of the rectangle.
        fpt_type center_x = (brect.x_min() + brect.x_max()) * to_fpt(0.5);
        fpt_type center_y = (brect.y_min() + brect.y_max()) * to_fpt(0.5);

        // Find the half-diagonal vector of the rectangle.
        fpt_type len_x = brect.x_max() - center_x;
        fpt_type len_y = brect.y_max() - center_y;

        // Find the vector between the origin and the center of the
        // rectangle.
        fpt_type diff_x = origin.x() - center_x;
        fpt_type diff_y = origin.y() - center_y;

        // Find the vector perpendicular to the direction vector.
        fpt_type perp_x = direction.y();
        fpt_type perp_y = -direction.x();

        // Projection of the vector between the origin and the center of
        // the rectangle on the line perpendicular to the direction vector.
        fpt_type lexpr = magnitude(perp_x * diff_x + perp_y * diff_y);

        // Maximum projection among any of the half-diagonals of the
        // rectangle on the line perpendicular to the direction vector.
        fpt_type rexpr = magnitude(perp_x * len_x) + magnitude(perp_y * len_y);

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
        fpt_type fT0 = 0;
        fpt_type fT1 = 0;

        // Check for the intersections with the lines
        // going through the sides of the bounding rectangle.
        clip_line(+direction.x(), -diff_x - len_x,
                  fT0_used, fT1_used, fT0, fT1);
        clip_line(-direction.x(), +diff_x - len_x,
                  fT0_used, fT1_used, fT0, fT1);
        clip_line(+direction.y(), -diff_y - len_y,
                  fT0_used, fT1_used, fT0, fT1);
        clip_line(-direction.y(), +diff_y - len_y,
                  fT0_used, fT1_used, fT0, fT1);

        // Update intersections vector.
        if (fT0_used && check_extent(fT0, edge_type))
            intersections.push_back(point_type(
                origin.x() + fT0 * direction.x(),
                origin.y() + fT0 * direction.y()));
        if (fT1_used && fT0 != fT1 && check_extent(fT1, edge_type))
            intersections.push_back(point_type(
                origin.x() + fT1 * direction.x(),
                origin.y() + fT1 * direction.y()));
    }

private:
    voronoi_utils();

    template <typename P>
    static point_type get_point(const P &point) {
        fpt_type x = to_fpt(point.x());
        fpt_type y = to_fpt(point.y());
        return point_type(x, y);
    }

    // Find intermediate points of the parabola. Number of points
    // is defined by the value of max_dist parameter - maximum distance
    // between parabola and line segments that interpolate it.
    // Parabola is a locus of points equidistant from the point and segment
    // sites. intermediate_points should contain two initial endpoints
    // of the edge (voronoi vertices). Intermediate points are inserted
    // between the given two endpoints.
    // Max_dist is the maximum distance allowed between parabola and line
    // segments that interpolate it.
    static void fill_intermediate_points(
            point_type point_site,
            point_type segment_site_start,
            point_type segment_site_end,
            point_set_type &intermediate_points,
            fpt_type max_dist) {
        // Check if bisector is a segment.
        if (point_site == segment_site_start ||
            point_site == segment_site_end)
            return;

        // Apply the linear transformation to move start point of the
        // segment to the point with coordinates (0, 0) and the direction
        // of the segment to coincide the positive direction of the x-axis.
        fpt_type segm_vec_x = segment_site_end.x() -
                              segment_site_start.x();
        fpt_type segm_vec_y = segment_site_end.y() -
                              segment_site_start.y();
        fpt_type sqr_segment_length = segm_vec_x * segm_vec_x +
                                      segm_vec_y * segm_vec_y;

        // Compute x-coordinates of the endpoints of the edge
        // in the transformed space.
        fpt_type projection_start = sqr_segment_length *
            get_point_projection(intermediate_points[0],
                                 segment_site_start,
                                 segment_site_end);
        fpt_type projection_end = sqr_segment_length *
            get_point_projection(intermediate_points[1],
                                 segment_site_start,
                                 segment_site_end);

        // Compute parabola parameterers in the transformed space.
        // Parabola has next representation:
        // f(x) = ((x-rot_x)^2 + rot_y^2) / (2.0*rot_y).
        fpt_type point_vec_x = point_site.x() - segment_site_start.x();
        fpt_type point_vec_y = point_site.y() - segment_site_start.y();
        fpt_type rot_x = segm_vec_x * point_vec_x +
                         segm_vec_y * point_vec_y;
        fpt_type rot_y = segm_vec_x * point_vec_y -
                         segm_vec_y * point_vec_x;

        // Save the last point.
        point_type last_point = intermediate_points[1];
        intermediate_points.pop_back();

        // Use stack to avoid recursion.
        std::stack<fpt_type> point_stack;
        point_stack.push(projection_end);
        fpt_type cur_x = projection_start;
        fpt_type cur_y = parabola_y(cur_x, rot_x, rot_y);

        // Adjust max_dist parameter in the transformed space.
        max_dist *= max_dist * sqr_segment_length;

        while (!point_stack.empty()) {
            fpt_type new_x = point_stack.top();
            fpt_type new_y = parabola_y(new_x, rot_x, rot_y);

            // Compute coordinates of the point of the parabola that is
            // furthest from the current line segment.
            fpt_type mid_x = (new_y - cur_y) / (new_x - cur_x) * rot_y +
                             rot_x;
            fpt_type mid_y = parabola_y(mid_x, rot_x, rot_y);

            // Compute maximum distance between the given parabolic arc
            // and line segment that interpolates it.
            fpt_type dist = (new_y - cur_y) * (mid_x - cur_x) -
                            (new_x - cur_x) * (mid_y - cur_y);
            dist = dist * dist / ((new_y - cur_y) * (new_y - cur_y) +
                                  (new_x - cur_x) * (new_x - cur_x));
            if (dist <= max_dist) {
                // Distance between parabola and line segment is
                // not greater than max_dist.
                point_stack.pop();
                fpt_type inter_x =
                    (segm_vec_x * new_x - segm_vec_y * new_y) /
                    sqr_segment_length + segment_site_start.x();
                fpt_type inter_y =
                    (segm_vec_x * new_y + segm_vec_y * new_x) /
                    sqr_segment_length + segment_site_start.y();
                intermediate_points.push_back(
                    point_type(inter_x, inter_y));
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
    static fpt_type parabola_y(fpt_type x, fpt_type a, fpt_type b) {
        return ((x - a) * (x - a) + b * b) / (to_fpt(2.0) * b);
    }

    // Check whether extent is compatible with the edge type.
    static bool check_extent(fpt_type extent, kEdgeType etype) {
        switch (etype) {
            case SEGMENT:
                return extent >= to_fpt(0.0) &&
                       extent <= to_fpt(1.0);
            case RAY: return extent >= to_fpt(0.0);
            case LINE: return true;
        }
        return true;
    }

    // Compute the absolute value.
    static inline fpt_type magnitude(fpt_type value) {
        if (value >= to_fpt(0.0))
            return value;
        return -value;
    }

    // Find fT min and max values: fT = numer / denom.
    static void clip_line(fpt_type denom, fpt_type numer,
                          bool &fT0_used, bool &fT1_used,
                          fpt_type &fT0, fpt_type &fT1) {
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
    //     1) point projection onto the segment;
    //     2) start point of the segment.
    // Return this length divided by the segment length.
    // This is made to avoid sqrt computation during transformation from
    // the initial space to the transformed one and vice versa.
    // Assumption is made that projection of the point lies
    // between the startpoint and endpoint of the segment.
    static fpt_type get_point_projection(
            const point_type &point,
            const point_type &segment_start,
            const point_type &segment_end) {
        fpt_type segment_vec_x = segment_end.x() - segment_start.x();
        fpt_type segment_vec_y = segment_end.y() - segment_start.y();
        fpt_type point_vec_x = point.x() - segment_start.x();
        fpt_type point_vec_y = point.y() - segment_start.y();
        fpt_type sqr_segment_length = segment_vec_x * segment_vec_x +
                                      segment_vec_y * segment_vec_y;
        fpt_type vec_dot = segment_vec_x * point_vec_x +
                           segment_vec_y * point_vec_y;
        return vec_dot / sqr_segment_length;
    }

    template <typename CT>
    static fpt_type to_fpt(const CT& value) {
        static ctype_converter_type converter;
        return converter(value);
    }

};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_VORONOI_UTILS
