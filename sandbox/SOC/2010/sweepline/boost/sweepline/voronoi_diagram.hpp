// Boost sweepline/voronoi_diagram.hpp header file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SWEEPLINE_VORONOI_DIAGRAM
#define BOOST_SWEEPLINE_VORONOI_DIAGRAM

#include <algorithm>
#include <cmath>
#include <cstring>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

#pragma warning(disable:4800)
#include <gmpxx.h>

#include "boost/polygon/polygon.hpp"
using namespace boost::polygon;

#include "detail/mpt_wrapper.hpp"
#include "detail/voronoi_fpt_kernel.hpp"
#include "detail/voronoi_formation.hpp"

namespace boost {
namespace sweepline {

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI OUTPUT TYPES ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // Forward declarations.
    template <typename T>
    class voronoi_cell;

    template <typename T>
    class voronoi_edge;

    template <typename T>
    class voronoi_output;

    // Bounding rectangle data structure. Contains coordinates
    // of the bottom left and the upper right points of the rectangle.
    template <typename T>
    class BRect {
    public:
        typedef T coordinate_type;
        typedef point_data<coordinate_type> point_type;

        BRect() {}

        template <typename P>
        BRect(const P &p) {
            x_min_ = x_max_ = static_cast<coordinate_type>(p.x());
            y_min_ = y_max_ = static_cast<coordinate_type>(p.y());
        }

        template <typename P>
        BRect(const P &p1, const P &p2) {
            x_min_ = (std::min)(static_cast<coordinate_type>(p1.x()), static_cast<coordinate_type>(p2.x()));
            y_min_ = (std::min)(static_cast<coordinate_type>(p1.y()), static_cast<coordinate_type>(p2.y()));
            x_max_ = (std::max)(static_cast<coordinate_type>(p1.x()), static_cast<coordinate_type>(p2.x()));
            y_max_ = (std::max)(static_cast<coordinate_type>(p1.y()), static_cast<coordinate_type>(p2.y()));
        }

        BRect(coordinate_type x_mn, coordinate_type y_mn,
              coordinate_type x_mx, coordinate_type y_mx) {
             x_min_ = (std::min)(x_mn, x_mx);
             y_min_ = (std::min)(y_mn, y_mx);
             x_max_ = (std::max)(x_mn, x_mx);
             y_max_ = (std::max)(y_mn, y_mx);
        }

        // Extend the rectangle with a new point.
        template <typename P>
        void update(const P &p) {
            x_min_ = (std::min)(x_min_, static_cast<coordinate_type>(p.x()));
            y_min_ = (std::min)(y_min_, static_cast<coordinate_type>(p.y()));
            x_max_ = (std::max)(x_max_, static_cast<coordinate_type>(p.x()));
            y_max_ = (std::max)(y_max_, static_cast<coordinate_type>(p.y()));
        }

        // Check whether a point is situated inside the bounding rectangle.
        bool contains(const point_type &p) const {
            return p.x() >= x_min_ && p.x() <= x_max_ &&
                   p.y() >= y_min_ && p.y() <= y_max_;
        }

        // Check whether the bounding rectangle has a non-zero area.
        bool verify() const {
            return (x_min_ <= x_max_) && (y_min_ <= y_max_);
        }

        // Return the x-coordinate of the bottom left point of the rectangle.
        coordinate_type x_min() const {
            return x_min_;
        }

        // Return the y-coordinate of the bottom left point of the rectangle.
        coordinate_type y_min() const {
            return y_min_;
        }

        // Return the x-coordinate of the upper right point of the rectangle.
        coordinate_type x_max() const {
            return x_max_;
        }

        // Return the y-coordinate of the upper right point of the rectangle.
        coordinate_type y_max() const {
            return y_max_;
        }

        coordinate_type min_len() const {
            return (std::min)(x_max_ - x_min_, y_max_ - y_min_);
        }

        coordinate_type max_len() const {
            return (std::max)(x_max_ - x_min_, y_max_ - y_min_);
        }

    private:
        coordinate_type x_min_;
        coordinate_type y_min_;
        coordinate_type x_max_;
        coordinate_type y_max_;
    };

    // Voronoi output postprocessing tools.
    template <typename T>
    class voronoi_helper {
    public:
        typedef T coordinate_type;
        typedef point_data<coordinate_type> point_type;
        typedef directed_line_segment_data<coordinate_type> segment_type;
        typedef directed_line_segment_set_data<coordinate_type> segment_set_type;
        typedef BRect<coordinate_type> brect_type;

        // There are three different types of edges:
        //   1) Segment edge - has both endpoints;
        //   2) Ray edge - has one endpoint, infinite
        //                 in the positive direction;
        //   3) Line edge - is infinite in both directions.
        enum kEdgeType {
            SEGMENT = 0,
            RAY = 1,
            LINE = 2,
        };

        // Get a view rectangle based on the voronoi bounding rectangle.
        static BRect<coordinate_type> get_view_rectangle(
                const BRect<coordinate_type> &brect) {
            coordinate_type x_len = (brect.x_max() - brect.x_min());
            coordinate_type y_len = (brect.y_max() - brect.y_min());
            coordinate_type x_mid = (brect.x_max() + brect.x_min()) * 0.5;
            coordinate_type y_mid = (brect.y_max() + brect.y_min()) * 0.5;
            coordinate_type offset = x_len;
            if (offset < y_len)
                offset = y_len;
            if (offset == 0.0)
                offset = 0.5;
            BRect<coordinate_type> new_brect(x_mid - offset, y_mid - offset,
                                             x_mid + offset, y_mid + offset);
            return new_brect;
        }

        // Compute intermediate points for the voronoi edge within the given
        // bounding rectangle. The assumption is made that voronoi rectangle
        // contains all the finite endpoints of the edge.
        // Max_error is the maximum distance (relative to the minor of two
        // rectangle sides) allowed between the parabola and line segments
        // that interpolate it.
        static std::vector<point_type> get_point_interpolation(
                const voronoi_edge<coordinate_type> *edge,
                const BRect<coordinate_type> &brect,
                double max_error) {
            // Retrieve the cell to the left of the current edge.
            const voronoi_cell<coordinate_type> *cell1 = edge->cell();

            // Retrieve the cell to the right of the current edge.
            const voronoi_cell<coordinate_type> *cell2 = edge->twin()->cell();

            // edge_points - contains intermediate points.
            std::vector<point_type> edge_points;
            if (!(cell1->contains_segment() ^ cell2->contains_segment())) {
                // Edge is a segment, ray, or line.
                if (edge->vertex0() != NULL && edge->vertex1() != NULL) {
                    // Edge is a segment. No further processing is required.
                    edge_points.push_back(edge->vertex0()->vertex());
                    edge_points.push_back(edge->vertex1()->vertex());
                } else {
                    // Edge is a ray or line.
                    // Clip it with the bounding rectangle.
                    const point_type &site1 = cell1->point0();
                    const point_type &site2 = cell2->point0();
                    point_type origin((site1.x() + site2.x()) * 0.5,
                                      (site1.y() + site2.y()) * 0.5);
                    point_type direction(site1.y() - site2.y(),
                                         site2.x() - site1.x());

                    // Find intersection points.
                    find_intersections(origin, direction, LINE,
                                       brect, edge_points);

                    // Update endpoints in case edge is a ray.
                    if (edge->vertex1() != NULL)
                        edge_points[1] = edge->vertex1()->vertex();
                    if (edge->vertex0() != NULL)
                        edge_points[0] = edge->vertex0()->vertex();
                }
            } else {
                // point1 - site point;
                const point_type &point1 = (cell1->contains_segment()) ?
                    cell2->point0() : cell1->point0();

                // point2 - startpoint of the segment site;
                const point_type &point2 = (cell1->contains_segment()) ?
                    cell1->point0() : cell2->point0();

                // point3 - endpoint of the segment site;
                const point_type &point3 = (cell1->contains_segment()) ?
                    cell1->point1() : cell2->point1();

                if (edge->vertex0() != NULL && edge->vertex1() != NULL) {
                    // Edge is a segment or parabolic arc.
                    edge_points.push_back(edge->vertex0()->vertex());
                    edge_points.push_back(edge->vertex1()->vertex());
                    double max_dist = max_error * brect.min_len();
                    fill_intermediate_points(point1, point2, point3,
                                             edge_points, max_dist);
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
                    find_intersections(point1, direction, LINE,
                                       brect, edge_points);

                    // Update endpoints in case edge is a ray.
                    if (edge->vertex1() != NULL)
                        edge_points[1] = edge->vertex1()->vertex();
                    if (edge->vertex0() != NULL)
                        edge_points[0] = edge->vertex0()->vertex();
                }
            }
            return edge_points;
        }

        // Interpolate voronoi edge with a set of segments to satisfy maximal
        // error requirement.
        static segment_set_type get_segment_interpolation(
            const voronoi_edge<coordinate_type> *edge,
            const BRect<coordinate_type> &brect,
            double max_error) {
                std::vector<point_type> point_interpolation = 
                    get_point_interpolcation(edge, brect, max_error);
                segment_set_type ret_val;
                for (size_t i = 1; i < point_interpolation.size(); ++i)
                    ret_val.insert(segment_type(point_interpolation[i-1], point_interpolation[i]));
                return ret_val;
        }

        // Find edge-rectangle intersection points.
        // Edge is represented by its origin, direction and type.
        static void find_intersections(
                const point_type &origin, const point_type &direction,
                kEdgeType edge_type, const brect_type &brect,
                std::vector<point_type> &intersections) {
            // Find the center of the rectangle.
            coordinate_type center_x = (brect.x_min() + brect.x_max()) * 0.5;
            coordinate_type center_y = (brect.y_min() + brect.y_max()) * 0.5;

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
            coordinate_type lexpr = magnitude(perp_x * diff_x +
                                              perp_y * diff_y);

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
        voronoi_helper();

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
                std::vector<point_type> &intermediate_points,
                double max_dist) {
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

            // Compute parabola parameterers in the transformed space.
            // Parabola has next representation:
            // f(x) = ((x-rot_x)^2 + rot_y^2) / (2.0*rot_y).
            coordinate_type point_vec_x = point_site.x() -
                                          segment_site_start.x();
            coordinate_type point_vec_y = point_site.y() -
                                          segment_site_start.y();
            coordinate_type rot_x = segm_vec_x * point_vec_x +
                                    segm_vec_y * point_vec_y;
            coordinate_type rot_y = segm_vec_x * point_vec_y -
                                    segm_vec_y * point_vec_x;

            // Save the last point.
            point_type last_point = intermediate_points[1];
            intermediate_points.pop_back();

            // Use stack to avoid recursion.
            std::stack< coordinate_type > point_stack;
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
                coordinate_type mid_x = (new_y - cur_y) / (new_x - cur_x) *
                                        rot_y + rot_x;
                coordinate_type mid_y = parabola_y(mid_x, rot_x, rot_y);

                // Compute maximum distance between the given parabolic arc
                // and line segment that interpolates it.
                double dist = (new_y - cur_y) * (mid_x - cur_x) -
                              (new_x - cur_x) * (mid_y - cur_y);
                dist = dist * dist / ((new_y - cur_y) * (new_y - cur_y) +
                                      (new_x - cur_x) * (new_x - cur_x));
                if (dist <= max_dist) {
                    // Distance between parabola and line segment is
                    // not greater than max_dist.
                    point_stack.pop();
                    coordinate_type inter_x =
                        (segm_vec_x * new_x - segm_vec_y * new_y) /
                        sqr_segment_length + segment_site_start.x();
                    coordinate_type inter_y =
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
        static coordinate_type parabola_y(coordinate_type x,
                                          coordinate_type a,
                                          coordinate_type b) {
            return ((x - a) * (x - a) + b * b) / (2.0 * b);
        }

        // Check whether extent is compatible with the edge type.
        static bool check_extent(coordinate_type extent, kEdgeType etype) {
            switch (etype) {
                case SEGMENT:
                    return extent >= static_cast<coordinate_type>(0.0) &&
                           extent <= static_cast<coordinate_type>(1.0);
                case RAY: return extent >= static_cast<coordinate_type>(0.0);
                case LINE: return true;
            }
            return true;
        }

        // Compute the absolute value.
        static inline coordinate_type magnitude(coordinate_type value) {
            if (value >= static_cast<coordinate_type>(0.0))
                return value;
            return -value;
        }

        // Find fT min and max values: fT = numer / denom.
        static void clip_line(coordinate_type denom, coordinate_type numer,
                              bool &fT0_used, bool &fT1_used,
                              coordinate_type &fT0, coordinate_type &fT1) {
            if (denom > static_cast<coordinate_type>(0.0)) {
                if (fT1_used && numer > denom * fT1)
                    return;
                if (!fT0_used || numer > denom * fT0) {
                    fT0_used = true;
                    fT0 = numer / denom;
                }
            } else if (denom < static_cast<coordinate_type>(0.0)) {
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
        static coordinate_type get_point_projection(
                const point_type &point,
                const point_type &segment_start,
                const point_type &segment_end) {
            coordinate_type segment_vec_x = segment_end.x() -
                                            segment_start.x();
            coordinate_type segment_vec_y = segment_end.y() -
                                            segment_start.y();
            coordinate_type point_vec_x = point.x() - segment_start.x();
            coordinate_type point_vec_y = point.y() - segment_start.y();
            coordinate_type sqr_segment_length =
                segment_vec_x * segment_vec_x + segment_vec_y * segment_vec_y;
            coordinate_type vec_dot = segment_vec_x * point_vec_x +
                                      segment_vec_y * point_vec_y;
            return vec_dot / sqr_segment_length;
        }
    };

    // Represents voronoi cell.
    // Data members: 1) pointer to the incident edge;
    //               2) site inside the cell;
    //               3) number of incident edges.
    // The cell may contain point or segment site.
    template <typename T>
    class voronoi_cell {
    public:
        typedef T coordinate_type;
        typedef point_data<coordinate_type> point_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        template <typename P>
        voronoi_cell(const P &p1, const P &p2,
                     bool contains_segment, voronoi_edge_type *edge) :
            point0_(static_cast<coordinate_type>(p1.x()), static_cast<coordinate_type>(p1.y())),
            point1_(static_cast<coordinate_type>(p2.x()), static_cast<coordinate_type>(p2.y())),
            contains_segment_(contains_segment),
            incident_edge_(edge),
            num_incident_edges_(0) {}

        // Returns true if the cell contains segment site, false else.
        bool contains_segment() const { return contains_segment_; }

        // Returns site point in case cell contains point site,
        // the first point of the segment site else.
        const point_type &point0() const { return point0_; }

        // Returns the second site of the segment site.
        // Don't use with the point sites.
        const point_type &point1() const { return point1_; }

        voronoi_edge_type *incident_edge() { return incident_edge_; }
        const voronoi_edge_type *incident_edge() const {
            return incident_edge_;
        }
        void incident_edge(voronoi_edge_type *e) { incident_edge_ = e; }

        int num_incident_edges() const { return num_incident_edges_; }
        void inc_num_incident_edges() { ++num_incident_edges_; }
        void dec_num_incident_edges() { --num_incident_edges_; }

    private:
        point_type point0_;
        point_type point1_;
        bool contains_segment_;
        voronoi_edge_type *incident_edge_;
        int num_incident_edges_;
    };

    // Represents voronoi vertex.
    // Data members: 1) vertex point itself;
    //               2) pointer to the incident edge;
    //               3) number of incident edges.
    template <typename T>
    class voronoi_vertex {
    public:
        typedef T coordinate_type;
        typedef point_data<T> point_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        template <typename P>
        voronoi_vertex(const P &vertex, voronoi_edge_type *edge) :
            vertex_(static_cast<coordinate_type>(vertex.x()), static_cast<coordinate_type>(vertex.y())),
            incident_edge_(edge),
            num_incident_edges_(3) {}

        const point_type &vertex() const { return vertex_; }

        voronoi_edge_type *incident_edge() { return incident_edge_; }
        const voronoi_edge_type *incident_edge() const { return incident_edge_; }
        void incident_edge(voronoi_edge_type *e) { incident_edge_ = e; }

        int num_incident_edges() const { return num_incident_edges_; }
        void num_incident_edges(int n) { num_incident_edges_ = n; }

    private:
        point_type vertex_;
        voronoi_edge_type *incident_edge_;
        int num_incident_edges_;
    };

    // Half-edge data structure. Represents voronoi edge.
    // Variables: 1) pointer to the corresponding cell;
    //            2) pointer to the vertex that is the starting
    //               point of the half-edge;
    //            3) pointer to the twin edge;
    //            4) pointer to the CCW/CW next edge.
    //            5) pointer to the CCW/CW prev edge.
    template <typename T>
    class voronoi_edge {
    public:
        typedef T coordinate_type;
        typedef voronoi_cell<coordinate_type> voronoi_cell_type;
        typedef voronoi_vertex<coordinate_type> voronoi_vertex_type;
        typedef voronoi_edge<coordinate_type> voronoi_edge_type;

        voronoi_edge() :
            cell_(NULL),
            vertex_(NULL),
            twin_(NULL),
            next_(NULL),
            prev_(NULL) {}

        voronoi_cell_type *cell() { return cell_; }
        const voronoi_cell_type *cell() const { return cell_; }
        void cell(voronoi_cell_type *c) { cell_ = c; }

        voronoi_vertex_type *vertex0() { return vertex_; }
        const voronoi_vertex_type *vertex0() const { return vertex_; }
        void vertex0(voronoi_vertex_type *v) { vertex_ = v; }

        voronoi_vertex_type *vertex1() { return twin_->vertex0(); }
        const voronoi_vertex_type *vertex1() const { return twin_->vertex0(); }
        void vertex1(voronoi_vertex_type *v) { twin_->vertex0(v); }

        voronoi_edge_type *twin() { return twin_; }
        const voronoi_edge_type *twin() const { return twin_; }
        void twin(voronoi_edge_type *e) { twin_ = e; }

        voronoi_edge_type *next() { return next_; }
        const voronoi_edge_type *next() const { return next_; }
        void next(voronoi_edge_type *e) { next_ = e; }

        voronoi_edge_type *prev() { return prev_; }
        const voronoi_edge_type *prev() const { return prev_; }
        void prev(voronoi_edge_type *e) { prev_ = e; }

        // Return a pointer to the rotation next edge
        // over the starting point of the half-edge.
        voronoi_edge_type *rot_next() { return (vertex_) ? prev_->twin() : NULL; }
        const voronoi_edge_type *rot_next() const { return (vertex_) ? prev_->twin() : NULL; }

        // Return a pointer to the rotation prev edge
        // over the starting point of the half-edge.
        voronoi_edge_type *rot_prev() { return (vertex_) ? twin_->next() : NULL; }
        const voronoi_edge_type *rot_prev() const { return (vertex_) ? twin_->next() : NULL; }

        // Return true if the edge is finite (segment, parabolic arc).
        // Return false if the edge is infinite (ray, line).
        bool is_bounded() const { return vertex0() && vertex1(); }

        // Return true if the edge is linear.
        // Return false if the edge is curved (parabolic arc).
        bool is_linear() const {
            return !(cell()->contains_segment() ^ twin()->cell()->contains_segment());
        }

        // Returns true if the edge is curved (parabolic arc).
        // Returns false if the edge is linear.
        bool is_curved() const {
            return (cell()->contains_segment() ^ twin()->cell()->contains_segment());
        }

        // Return false if edge goes through the endpoint of the segment.
        // Return true else.
        bool is_primary() const {
            voronoi_cell_type *cell1 = cell_;
            voronoi_cell_type *cell2 = twin_->cell();
            if (cell1->contains_segment() && !cell2->contains_segment()) {
                if (cell1->point0() == cell2->point0() ||
                    cell1->point1() == cell2->point0())
                    return false;
            }
            if (cell2->contains_segment() && !cell1->contains_segment()) {
                if (cell2->point0() == cell1->point0() ||
                    cell2->point1() == cell1->point0())
                    return false;
            }
            return true;
        }

    private:
        voronoi_cell_type *cell_;
        voronoi_vertex_type *vertex_;
        voronoi_edge_type *twin_;
        voronoi_edge_type *next_;
        voronoi_edge_type *prev_;
    };

    // Voronoi output data structure.
    // Data members:
    //   1) cell_records_ - vector of the voronoi cells;
    //   2) vertex_records_ - list of the voronoi vertices;
    //   3) edge_records_ - list of the voronoi edges;
    //   4) voronoi_rect_ - bounding rectangle;
    //   5) num_cell_records_ - number of the voronoi cells;
    //   6) num_vertex_records_ - number of the voronoi vertices;
    //   7) num_edge_records_ - number of the voronoi edges.
    // CCW ordering is used on the faces perimeter and around the vertices.
    // Robust vertices are used to make the simplification stage epsilon
    // robust. Vector data structure is used to store voronoi cells as the
    // number of the cells may be precomputed at the initialization step.
    // As size() method takes O(n) time on the list data structure three
    // additional counters are used to count the number of the voronoi cells,
    // vertices and edges. As we use list data structure to represent voronoi
    // vertices and edges there is no copy method available, because it will
    // invalidate all the pointers. Another approach could be used to make
    // copying available:
    //     1) use vectors to store voronoi vertices and cells;
    //     2) store vector indices instead of the pointers;
    //     3) store additional pointer to the voronoi output data structure
    //        in the voronoi cell, vertex, edge data structure.
    //     4) implement simplification via copying not degenerate elements
    //        to the new vector as removing elements from a vector takes O(n)
    //        time.
    template <typename T>
    class voronoi_output {
    public:
        typedef T coordinate_type;
        typedef point_data<coordinate_type> point_type;
        typedef detail::site_event<coordinate_type> site_event_type;
        typedef detail::circle_event<coordinate_type> circle_event_type;

        typedef voronoi_cell<coordinate_type> voronoi_cell_type;
        typedef std::vector<voronoi_cell_type> voronoi_cells_type;
        typedef typename voronoi_cells_type::iterator
            voronoi_cell_iterator_type;
        typedef typename voronoi_cells_type::const_iterator
            voronoi_cell_const_iterator_type;

        typedef voronoi_vertex<coordinate_type> voronoi_vertex_type;
        typedef std::list<voronoi_vertex_type> voronoi_vertices_type;
        typedef typename voronoi_vertices_type::iterator
            voronoi_vertex_iterator_type;
        typedef typename voronoi_vertices_type::const_iterator
            voronoi_vertex_const_iterator_type;

        typedef voronoi_edge<coordinate_type> voronoi_edge_type;
        typedef std::list<voronoi_edge_type> voronoi_edges_type;
        typedef typename voronoi_edges_type::iterator
            voronoi_edge_iterator_type;
        typedef typename voronoi_edges_type::const_iterator
            voronoi_edge_const_iterator_type;

        voronoi_output() :
            num_cell_records_(0),
            num_edge_records_(0),
            num_vertex_records_(0) {}

        void clear() {
            voronoi_cells_type().swap(cell_records_);
            vertex_records_.clear();
            edge_records_.clear();

            num_cell_records_ = 0;
            num_edge_records_ = 0;
            num_vertex_records_ = 0;
        }

        const BRect<coordinate_type> &bounding_rectangle() const {
            return voronoi_rect_;
        }

        const voronoi_cells_type &cell_records() const {
            return cell_records_;
        }

        const voronoi_vertices_type &vertex_records() const {
            return vertex_records_;
        }

        const voronoi_edges_type &edge_records() const {
            return edge_records_;
        }

        int num_cell_records() const {
            return num_cell_records_;
        }

        int num_edge_records() const {
            return num_edge_records_;
        }

        int num_vertex_records() const {
            return num_vertex_records_;
        }

        void reserve(int num_sites) {
            // Resize cell vector to avoid reallocations.
            cell_records_.reserve(num_sites);

            // Init counters.
            num_cell_records_ = 0;
            num_edge_records_ = 0;
            num_vertex_records_ = 0;
        }

        // Update the voronoi output in case of a single point input.
        void process_single_site(const site_event_type &site) {
            // Update bounding rectangle.
            voronoi_rect_ = BRect<coordinate_type>(site.point0());

            // Update cell records.
            cell_records_.push_back(voronoi_cell_type(site.point0(),
                                                      site.point1(),
                                                      site.is_segment(),
                                                      NULL));
        }

        // Insert a new half-edge into the output data structure.
        // Takes as input left and right sites that form a new bisector.
        // Returns a pointer to a new half-edge.
        voronoi_edge_type *insert_new_edge(const site_event_type &site1,
                                           const site_event_type &site2) {
            // Get sites' indices.
            int site_index1 = site1.index();
            int site_index2 = site2.index();

            // Create a new half-edge that belongs to the first site.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &edge1 = edge_records_.back();

            // Create a new half-edge that belongs to the second site.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &edge2 = edge_records_.back();

            // Add the initial cell during the first edge insertion.
            if (cell_records_.empty()) {
                cell_records_.push_back(voronoi_cell_type(site1.point0(),
                                                          site1.point1(),
                                                          site1.is_segment(),
                                                          &edge1));
                voronoi_rect_ = BRect<coordinate_type>(site1.point0(),
                                                       site1.point0());
            }
            cell_records_[site_index1].inc_num_incident_edges();

            // Update the bounding rectangle.
            voronoi_rect_.update(site2.point0());
            if (site2.is_segment()) {
                voronoi_rect_.update(site2.point1());	
            }

            // The second site represents a new site during site event
            // processing. Add a new cell to the cell records.
            cell_records_.push_back(voronoi_cell_type(site2.point0(),
                                                      site2.point1(),
                                                      site2.is_segment(),
                                                      &edge2));
            cell_records_.back().inc_num_incident_edges();

            // Set up pointers to cells.
            edge1.cell(&cell_records_[site_index1]);
            edge2.cell(&cell_records_[site_index2]);

            // Set up twin pointers.
            edge1.twin(&edge2);
            edge2.twin(&edge1);

            // Return a pointer to the new half-edge.
            return &edge1;
        }

        // Insert a new half-edge into the output data structure with the
        // start at the point where two previously added half-edges intersect.
        // Takes as input two sites that create a new bisector, circle event
        // that correponds to the intersection point of the two old half-edges,
        // pointers to those half-edges. Half-edges' direction goes out of the
        // new voronoi vertex point. Returns a pointer to the new half-edge.
        voronoi_edge_type *insert_new_edge(const site_event_type &site1,
                                           const site_event_type &site3,
                                           const circle_event_type &circle,
                                           voronoi_edge_type *edge12,
                                           voronoi_edge_type *edge23) {
            // Add a new voronoi vertex.
            vertex_records_.push_back(voronoi_vertex_type(
                point_type(circle.erc_x().dif(), circle.erc_y().dif()), edge12));
            voronoi_vertex_type &new_vertex = vertex_records_.back();

            // Update vertex pointers of the old edges.
            edge12->vertex0(&new_vertex);
            edge23->vertex0(&new_vertex);

            // Add a new half-edge.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &new_edge1 = edge_records_.back();
            new_edge1.cell(&cell_records_[site1.index()]);
            new_edge1.cell()->inc_num_incident_edges();

            // Add a new half-edge.
            edge_records_.push_back(voronoi_edge_type());
            voronoi_edge_type &new_edge2 = edge_records_.back();
            new_edge2.cell(&cell_records_[site3.index()]);
            new_edge2.cell()->inc_num_incident_edges();

            // Update twin pointers.
            new_edge1.twin(&new_edge2);
            new_edge2.twin(&new_edge1);

            // Update vertex pointer.
            new_edge2.vertex0(&new_vertex);

            // Update voronoi prev/next pointers.
            edge12->prev(&new_edge1);
            new_edge1.next(edge12);
            edge12->twin()->next(edge23);
            edge23->prev(edge12->twin());
            edge23->twin()->next(&new_edge2);
            new_edge2.prev(edge23->twin());

            // Return a pointer to the new half-edge.
            return &new_edge1;
        }

        // Remove zero-length edges from the voronoi output.
        void clean() {
            voronoi_edge_iterator_type edge_it1;
            voronoi_edge_iterator_type edge_it = edge_records_.begin();
            num_cell_records_ = cell_records_.size();

            // All the initial sites are colinear.
            if (vertex_records_.empty()) {
                // Update edges counter.
                num_edge_records_ = num_cell_records_ - 1;

                // Return if there are no edges.
                if (edge_it == edge_records_.end())
                    return;

                // Update prev/next pointers of the edges. Those edges won't
                // have any common endpoints, cause they are infinite.
                // But still they follow each other using CCW ordering.
                voronoi_edge_type *edge1 = &(*edge_it);
                edge1->next(edge1);
                edge1->prev(edge1);
                ++edge_it;
                edge1 = &(*edge_it);
                ++edge_it;

                while (edge_it != edge_records_.end()) {
                    voronoi_edge_type *edge2 = &(*edge_it);
                    ++edge_it;

                    edge1->next(edge2);
                    edge1->prev(edge2);
                    edge2->next(edge1);
                    edge2->prev(edge1);

                    edge1 = &(*edge_it);
                    ++edge_it;
                }

                edge1->next(edge1);
                edge1->prev(edge1);
                return;
            }

            // Iterate over all the edges and remove degeneracies
            // (zero-length edges). Edge is considered to be zero-length
            // if both its endpoints lie within some epsilon-rectangle.
            while (edge_it != edge_records_.end()) {
                edge_it1 = edge_it;
                std::advance(edge_it, 2);

                // Degenerate edges exist only among finite edges.
                if (!edge_it1->vertex0() || !edge_it1->vertex1()) {
                    ++num_edge_records_;
                    continue;
                }

                const voronoi_vertex_type *v1 = edge_it1->vertex0();
                const voronoi_vertex_type *v2 = edge_it1->vertex1();

                // Make epsilon robust check.
                if (detail::almost_equal(v1->vertex().x(), v2->vertex().x(), 256) &&
                    detail::almost_equal(v1->vertex().y(), v2->vertex().y(), 256)) {
                    // Decrease number of cell's incident edges.
                    edge_it1->cell()->dec_num_incident_edges();
                    edge_it1->twin()->cell()->dec_num_incident_edges();

                    // Corresponding cell incident edge pointer
                    // points to the degenerate edge.
                    if (edge_it1->cell()->incident_edge() == &(*edge_it1)) {
                        // Update incident edge pointer.
                        if (edge_it1->cell()->incident_edge() ==
                            edge_it1->next()) {
                            edge_it1->cell()->incident_edge(NULL);
                        } else {
                            edge_it1->cell()->incident_edge(edge_it1->next());
                        }
                    }

                    // Cell corresponding to the twin edge
                    // points to the degenerate edge.
                    if (edge_it1->twin()->cell()->incident_edge() ==
                        edge_it1->twin()) {
                        // Update incident edge pointer.
                        if (edge_it1->twin()->cell()->incident_edge() ==
                            edge_it1->twin()->next()) {
                            edge_it1->twin()->cell()->incident_edge(NULL);
                        } else {
                            edge_it1->twin()->cell()->incident_edge(
                                edge_it1->twin()->next());
                        }
                    }

                    // To guarantee N*lon(N) time we merge vertex with
                    // less incident edges to the one with more.
                    if (v1->num_incident_edges() >= v2->num_incident_edges()) {
                            remove_edge(&(*edge_it1));
                    } else {
                        remove_edge(edge_it1->twin());
                    }

                    // Remove zero-length edge.
                    edge_records_.erase(edge_it1, edge_it);
                } else {
                    // Count not degenerate edge.
                    ++num_edge_records_;
                }
            }

            // Remove degenerate voronoi vertices with zero incident edges.
            for (voronoi_vertex_iterator_type vertex_it =
                 vertex_records_.begin();
                 vertex_it != vertex_records_.end();) {
                if (vertex_it->incident_edge() == NULL) {
                    vertex_it = vertex_records_.erase(vertex_it);
                } else {
                    ++vertex_it;
                    ++num_vertex_records_;
                }
            }

            // Update prev/next pointers for the ray-edges.
            for (voronoi_cell_iterator_type cell_it = cell_records_.begin();
                 cell_it != cell_records_.end(); ++cell_it) {
                // Move to the previous edge while
                // it is possible in the CW direction.
                voronoi_edge_type *cur_edge = cell_it->incident_edge();
                if (cur_edge) {
                    while (cur_edge->prev() != NULL) {
                        cur_edge = cur_edge->prev();

                        // Terminate if this is not a boundary cell.
                        if (cur_edge == cell_it->incident_edge())
                            break;
                    }

                    // Rewind incident edge pointer to the
                    // CW leftmost edge for the boundary cells.
                    cell_it->incident_edge(cur_edge);

                    // Set up prev/next half-edge pointers for the ray-edges.
                    if (cur_edge->prev() == NULL) {
                        voronoi_edge_type *last_edge =
                            cell_it->incident_edge();
                        while (last_edge->next() != NULL)
                            last_edge = last_edge->next();
                        last_edge->next(cur_edge);
                        cur_edge->prev(last_edge);
                    }
                }
            }
        }

    private:
        // Remove degenerate edge.
        void remove_edge(voronoi_edge_type *edge) {
            voronoi_vertex_type *vertex1 = edge->vertex0();
            voronoi_vertex_type *vertex2 = edge->vertex1();

            // Update number of incident edges.
            vertex1->num_incident_edges(vertex1->num_incident_edges() +
                                        vertex2->num_incident_edges() - 2);

            // Update the endpoints of the incident edges to the second vertex.
            voronoi_edge_type *updated_edge = edge->twin()->rot_next();
            while (updated_edge != edge->twin()) {
                updated_edge->vertex0(vertex1);
                updated_edge = updated_edge->rot_next();
            }

            voronoi_edge_type *edge1 = edge;
            voronoi_edge_type *edge2 = edge->twin();

            voronoi_edge_type *edge1_rot_prev = edge1->rot_prev();
            voronoi_edge_type *edge1_rot_next = edge1->rot_next();

            voronoi_edge_type *edge2_rot_prev = edge2->rot_prev();
            voronoi_edge_type *edge2_rot_next = edge2->rot_next();

            // Update prev/next pointers for the incident edges.
            edge1_rot_next->twin()->next(edge2_rot_prev);
            edge2_rot_prev->prev(edge1_rot_next->twin());
            edge1_rot_prev->prev(edge2_rot_next->twin());
            edge2_rot_next->twin()->next(edge1_rot_prev);

            // Change the pointer to the incident edge if it points to the
            // degenerate edge.
            if (vertex1->incident_edge() == edge) {
                vertex1->incident_edge(edge->rot_prev());
            }

            // Set the incident edge point of the second vertex to NULL value.
            if (vertex1 != vertex2) {
                vertex2->incident_edge(NULL);
            }
        }

        voronoi_cells_type cell_records_;
        voronoi_vertices_type vertex_records_;
        voronoi_edges_type edge_records_;

        int num_cell_records_;
        int num_edge_records_;
        int num_vertex_records_;

        BRect<coordinate_type> voronoi_rect_;

        // Disallow copy constructor and operator=
        voronoi_output(const voronoi_output&);
        void operator=(const voronoi_output&);
    };

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI TRAITS /////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    struct voronoi_traits;

    template <>
    struct voronoi_traits<int> {
        typedef double coordinate_type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // VORONOI BUILDER ////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

    // The sweepline algorithm implementation to compute voronoi diagram of
    // input data sets of points and segments (Fortune's algorithm).
    // Complexity - O(N*logN), memory usage - O(N), where N is the total
    // number of input objects.
    // Sweepline is a vertical line that sweeps from the left to the right
    // along the x-axis positive direction. Each of the input objects is
    // wrapped into the site event. Each event is characterized by its
    // coordinates: the point site is defined by the point itself,
    // the segment site is defined by its startpoint. At any moment we
    // consider only the sites that lie to the left of the sweepline. Beach
    // line is a curve formed by the parabolic arcs and line segments, that
    // consists of the points equidistant from the sweepline and the nearest
    // site to the left of the sweepline. The part of the generated diagram to
    // the left of the beach line remains unchanged until the end of the
    // algorithm. Each node in the beach line corresponds to some voronoi edge.
    // Each node is represented by two sites. Two neighboring nodes has a
    // common site. Circle event appears at the rightmost point of the circle
    // tangent to the three sites that correspond to the two consecutive
    // bisectors. At each step algorithm goes over the leftmost event
    // and processes it appropriately. This is made until there are no events.
    // At the end output data structure holds the voronoi diagram of the
    // initial set of objects.
    // Each point creates one site event. Each segment creates three site
    // events: two for its endpoints and one for the segment itself (this is
    // made to simplify output construction). All the site events are
    // constructed at the algorithm initialization step. After that they
    // are ordered using quicksort algorithm.
    // Priority queue is used to dynamically hold circle events. At each step
    // of the algorithm the leftmost event is retrieved by comparing the
    // current site event and the topmost element from the circle event queue.
    // Standard map container was chosen to hold state of the beach line. The
    // keys of the map correspond to the bisectors and values to the
    // corresponding edges from the output data structure. Specially defined
    // comparison functor is used to make the beach line correctly ordered.
    // Epsilon-based and high-precision approaches are used to guarantee
    // efficiency and robustness of the algorithm implementation.
    // Member data: 1) site_events_ - vector of the site events;
    //              2) site_event_iterator_ - iterator to the next
    //                 site event;
    //              3) circle_events_ - priority queue of circle events,
    //                 allows to retrieve topmost event in O(logN) time;
    //              4) beach_line_ - contains current state of the beach line;
    //              5) end_points_ - maps endpoints of the segment sites with
    //                 temporary nodes from the beach line. While sweepline
    //                 sweeps over the second endpoint of the segments
    //                 temporary nodes are being removed;
    //              6) output_ - contains voronoi diagram itself.
    template <typename T, typename VD>
    class voronoi_builder {
    public:
        typedef typename voronoi_traits<T>::coordinate_type coordinate_type;
        typedef VD output_type;

        voronoi_builder() {}

        template <typename PointIterator>
        void insert_points(PointIterator first_point, PointIterator last_point) {
            // Create a site event from each input point.
            for (PointIterator it = first_point; it != last_point; ++it) {
                site_events_.push_back(detail::make_site_event(
                    static_cast<coordinate_type>(it->x()),
                    static_cast<coordinate_type>(it->y()), 0));
            }
        }

        template <typename SegmentIterator>
        void insert_segments(SegmentIterator first_segment, SegmentIterator last_segment) {
            // Each segment creates three segment sites:
            //   1) the startpoint of the segment;
            //   2) the endpoint of the segment;
            //   3) the segment itself.
            for (SegmentIterator it = first_segment; it != last_segment; ++it) {
                coordinate_type x1 = static_cast<coordinate_type>(it->low().x());
                coordinate_type y1 = static_cast<coordinate_type>(it->low().y());
                coordinate_type x2 = static_cast<coordinate_type>(it->high().x());
                coordinate_type y2 = static_cast<coordinate_type>(it->high().y());
                site_events_.push_back(detail::make_site_event(x1, y1, 0));
                site_events_.push_back(detail::make_site_event(x2, y2, 0));
                site_events_.push_back(detail::make_site_event(x1, y1, x2, y2, 0));
            }
        }

        template <typename PointIterator, typename SegmentIterator>
        void insert_sites(PointIterator first_point, PointIterator last_point,
                          SegmentIterator first_segment, SegmentIterator last_segment) {
            insert_points(first_point, last_point);
            insert_segments(first_segment, last_segment);
        }

        // Run the sweepline algorithm.
        void construct(output_type &output) {
            // Init structures.
            output_ = &output;
            output_->clear();
            output_->reserve(site_events_.size());
            init_sites_queue();
            init_beach_line();

            // The algorithm stops when there are no events to process.
            // The circle events with the same rightmost point as the next
            // site event go first.
            while (!circle_events_.empty() ||
                   !(site_event_iterator_ == site_events_.end())) {
                if (circle_events_.empty()) {
                    process_site_event();
                } else if (site_event_iterator_ == site_events_.end()) {
                    process_circle_event();
                } else {
                    if (circle_events_.top().compare(*site_event_iterator_) == detail::MORE) {
                        process_site_event();
                    } else {
                        process_circle_event();
                    }
                }
            }

            beach_line_.clear();

            // Clean the output (remove zero-length edges).
            output_->clean();
        }

        void clear() {
            site_events_.clear();
        }

    private:
        typedef detail::point_2d<coordinate_type> point_type;
        typedef detail::site_event<coordinate_type> site_event_type;
        typedef detail::circle_event<coordinate_type> circle_event_type;
        typedef typename std::vector<site_event_type>::const_iterator
            site_event_iterator_type;
        typedef typename output_type::voronoi_edge_type edge_type;
        typedef detail::circle_events_queue<coordinate_type> circle_event_queue_type;
        typedef detail::beach_line_node<coordinate_type> key_type;
        typedef detail::beach_line_node_data<coordinate_type> value_type;
        typedef detail::node_comparer<key_type> node_comparer_type;
        typedef std::map< key_type, value_type, node_comparer_type >
            beach_line_type;
        typedef typename beach_line_type::iterator beach_line_iterator;
        typedef std::pair<point_type, beach_line_iterator> end_point_type;

        // Create site events.
        // There will be one site event for each input point and three site
        // events for each input segment (both endpoints of a segment and the
        // segment itself).
        void init_sites_queue() {
            // Sort the site events.
            sort(site_events_.begin(), site_events_.end());

            // Remove duplicates.
            site_events_.erase(unique(
                site_events_.begin(), site_events_.end()), site_events_.end());

            // Number the sites.
            for (size_t cur = 0; cur < site_events_.size(); ++cur)
                site_events_[cur].index(cur);

            // Init the site's iterator.
            site_event_iterator_ = site_events_.begin();
        }

        void init_beach_line() {
            if (site_events_.empty()) return;
            if (site_events_.size() == 1) {
                // Handle one input site case.
                output_->process_single_site(site_events_[0]);
                ++site_event_iterator_;
            } else {
                int skip = 0;

                // Count the number of the sites to init the beach line.
                while(site_event_iterator_ != site_events_.end() &&
                      site_event_iterator_->x() == site_events_.begin()->x() &&
                      site_event_iterator_->is_vertical()) {
                    ++site_event_iterator_;
                    ++skip;
                }

                if (skip == 1) {
                    // Init the beach line with the two first sites.
                    init_beach_line_default();
                } else {
                    // Init the beach line with the sites situated on the same
                    // vertical line. This could be a set of point and vertical
                    // segment sites.
                    init_beach_line_collinear_sites();
                }
            }
        }

        // Init the beach line with the two first sites.
        // The first site is always a point.
        void init_beach_line_default() {
            // Get the first and the second site events.
            site_event_iterator_type it_first = site_events_.begin();
            site_event_iterator_type it_second = site_events_.begin();
            ++it_second;

            // Update the beach line.
            insert_new_arc(*it_first, *it_first, *it_second, beach_line_.begin());

            // The second site has been already processed.
            // Move the site's iterator.
            ++site_event_iterator_;
        }

        // Insert bisectors for all collinear initial sites.
        void init_beach_line_collinear_sites() {
             site_event_iterator_type it_first = site_events_.begin();
             site_event_iterator_type it_second = site_events_.begin();
             ++it_second;
             while (it_second != site_event_iterator_) {
                 // Create a new beach line node.
                 key_type new_node(*it_first, *it_second);

                 // Update the output.
                 edge_type *edge = output_->insert_new_edge(*it_first, *it_second);

                 // Insert a new bisector into the beach line.
                 beach_line_.insert(
                     std::pair<key_type, value_type>(new_node, value_type(edge)));

                 // Update iterators.
                 ++it_first;
                 ++it_second;
             }
        }

        // Process a single site.
        void process_site_event() {
            // Get the site event to process.
            site_event_type site_event = *site_event_iterator_;

            // Move the site's iterator.
            site_event_iterator_type last = site_event_iterator_ + 1;

            // If a new site is an end point of some segment,
            // remove temporary nodes from the beach line data structure.
            if (!site_event.is_segment()) {
                while (!end_points_.empty() &&
                       end_points_.top().first == site_event.point0()) {
                    beach_line_.erase(end_points_.top().second);
                    end_points_.pop();
                }
            } else {
                while (last != site_events_.end() &&
                       last->is_segment() && last->point0() == site_event.point0())
                    last++;
            }

            for (; site_event_iterator_ != last; ++site_event_iterator_) {
                site_event = *site_event_iterator_;
                // Create degenerate node.
                key_type new_key(site_event);

                // Find the node in the binary search tree with left arc
                // lying above the new site point.
                beach_line_iterator it = beach_line_.lower_bound(new_key);
                int it_dist = site_event.is_segment() ? 2 : 1;

                // Do further processing depending on the above node position.
                // For any two neighbouring nodes the second site of the first node
                // is the same as the first site of the second arc.
                if (it == beach_line_.end()) {
                    // The above arc corresponds to the second arc of the last node.
                    // Move the iterator to the last node.
                    --it;

                    // Get the second site of the last node
                    const site_event_type &site_arc = it->first.right_site();

                    // Insert new nodes into the beach line. Update the output.
                    beach_line_iterator new_node_it =
                        insert_new_arc(site_arc, site_arc, site_event, it);

                    // Add a candidate circle to the circle event queue.
                    // There could be only one new circle event formed by
                    // a new bisector and the one on the left.
                    std::advance(new_node_it, -it_dist);
                    activate_circle_event(it->first.left_site(),
                                          it->first.right_site(),
                                          site_event, new_node_it);
                } else if (it == beach_line_.begin()) {
                    // The above arc corresponds to the first site of the first node.
                    const site_event_type &site_arc = it->first.left_site();

                    // Insert new nodes into the beach line. Update the output.
                    insert_new_arc(site_arc, site_arc, site_event, it);

                    // If the site event is a segment, update its direction.
                    if (site_event.is_segment()) {
                        site_event.inverse();
                    }

                    // Add a candidate circle to the circle event queue.
                    // There could be only one new circle event formed by
                    // a new bisector and the one on the right.
                    activate_circle_event(site_event, it->first.left_site(),
                                          it->first.right_site(), it);
                } else {
                    // The above arc corresponds neither to the first,
                    // nor to the last site in the beach line.
                    const site_event_type &site_arc2 = it->first.left_site();
                    const site_event_type &site3 = it->first.right_site();

                    // Remove the candidate circle from the event queue.
                    it->second.deactivate_circle_event();
                    --it;
                    const site_event_type &site_arc1 = it->first.right_site();
                    const site_event_type &site1 = it->first.left_site();

                    // Insert new nodes into the beach line. Update the output.
                    beach_line_iterator new_node_it =
                        insert_new_arc(site_arc1, site_arc2, site_event, it);

                    // Add candidate circles to the circle event queue.
                    // There could be up to two circle events formed by
                    // a new bisector and the one on the left or right.
                    std::advance(new_node_it, -it_dist);
                    activate_circle_event(site1, site_arc1, site_event,
                                          new_node_it);

                    // If the site event is a segment, update its direction.
                    if (site_event.is_segment()) {
                        site_event.inverse();
                    }
                    std::advance(new_node_it, it_dist + 1);
                    activate_circle_event(site_event, site_arc2, site3,
                                          new_node_it);
                }
            }
        }

        // Process a single circle event.
        // In general case circle event is made of the three consequtive sites
        // that form two bisector nodes in the beach line data structure.
        // Let circle event sites be A, B, C, two bisectors that define
        // circle event be (A, B), (B, C). During circle event processing
        // we remove (A, B), (B, C) and insert (A, C). As beach line comparer
        // works correctly only if one of the nodes is a new one we remove
        // (B, C) bisector and change (A, B) bisector to the (A, C). That's
        // why we use const_cast there and take all the responsibility that
        // map data structure keeps correct ordering.
        void process_circle_event() {
            // Get the topmost circle event.
            const circle_event_type &circle_event = circle_events_.top();
            beach_line_iterator it_first = circle_event.bisector();
            beach_line_iterator it_last = it_first;

            // Get the C site.
            site_event_type site3 = it_first->first.right_site();

            // Get the half-edge corresponding to the second bisector - (B, C).
            edge_type *bisector2 = it_first->second.edge();

            // Get the half-edge corresponding to the first bisector - (A, B).
            --it_first;
            edge_type *bisector1 = it_first->second.edge();

            // Get the A site.
            site_event_type site1 = it_first->first.left_site();

            if (!site1.is_segment() && site3.is_segment() &&
                site3.point1(true) == site1.point0()) {
                site3.inverse();
            }

            // Change the (A, B) bisector node to the (A, C) bisector node.
            const_cast<key_type &>(it_first->first).right_site(site3);

            // Insert the new bisector into the beach line.
            it_first->second.edge(output_->insert_new_edge(site1, site3, circle_event,
                                                           bisector1, bisector2));

            // Remove the (B, C) bisector node from the beach line.
            beach_line_.erase(it_last);
            it_last = it_first;

            // Pop the topmost circle event from the event queue.
            circle_events_.pop();

            // Check new triplets formed by the neighboring arcs
            // to the left for potential circle events.
            if (it_first != beach_line_.begin()) {
                it_first->second.deactivate_circle_event();
                --it_first;
                const site_event_type &site_l1 = it_first->first.left_site();
                activate_circle_event(site_l1, site1, site3, it_last);
            }

            // Check the new triplet formed by the neighboring arcs
            // to the right for potential circle events.
            ++it_last;
            if (it_last != beach_line_.end()) {
                it_last->second.deactivate_circle_event();
                const site_event_type &site_r1 = it_last->first.right_site();
                activate_circle_event(site1, site3, site_r1, it_last);
            }
        }

        // Insert new nodes into the beach line. Update the output.
        beach_line_iterator insert_new_arc(const site_event_type &site_arc1,
                                           const site_event_type &site_arc2,
                                           const site_event_type &site_event,
                                           const beach_line_iterator &position) {
            // Create two new bisectors with opposite directions.
            key_type new_left_node(site_arc1, site_event);
            key_type new_right_node(site_event, site_arc2);

            // Set correct orientation for the first site of the second node.
            if (site_event.is_segment()) {
                new_right_node.inverse_left_site();
            }

            // Update the output.
            edge_type *edge = output_->insert_new_edge(site_arc2, site_event);

            // Update the beach line with the (site_arc1, site_event) bisector.
            beach_line_iterator it = beach_line_.insert(position,
                typename beach_line_type::value_type(new_right_node, value_type(edge->twin())));

            if (site_event.is_segment()) {
                // Update the beach line with temporary bisector, that will
                // disappear after processing site event going through the
                // endpoint of the segment site.
                key_type new_node(site_event, site_event);
                new_node.inverse_right_site();
                beach_line_iterator temp_it = beach_line_.insert(position,
                    typename beach_line_type::value_type(new_node, value_type(NULL)));

                // Update the data structure that holds temporary bisectors.
                end_points_.push(std::make_pair(site_event.point1(), temp_it));
            }

            // Update the beach line with the (site_event, site_arc2) bisector.
            beach_line_.insert(position,
                typename beach_line_type::value_type(new_left_node, value_type(edge)));
            return it;
        }

        // Create a circle event from the given three sites.
        // Returns true if the circle event exists, else false.
        // If exists circle event is saved into the c_event variable.
        bool create_circle_event(const site_event_type &site1,
                                 const site_event_type &site2,
                                 const site_event_type &site3,
                                 circle_event_type &c_event) const {
            if (!site1.is_segment()) {
                if (!site2.is_segment()) {
                    if (!site3.is_segment()) {
                        // (point, point, point) sites.
                        return create_circle_event_ppp(site1, site2, site3, c_event);
                    } else {
                        // (point, point, segment) sites.
                        return create_circle_event_pps(site1, site2, site3, 3, c_event);
                    }
                } else {
                    if (!site3.is_segment()) {
                        // (point, segment, point) sites.
                        return create_circle_event_pps(site1, site3, site2, 2, c_event);
                    } else {
                        // (point, segment, segment) sites.
                        return create_circle_event_pss(site1, site2, site3, 1, c_event);
                    }
                }
            } else {
                if (!site2.is_segment()) {
                    if (!site3.is_segment()) {
                        // (segment, point, point) sites.
                        return create_circle_event_pps(site2, site3, site1, 1, c_event);
                    } else {
                        // (segment, point, segment) sites.
                        return create_circle_event_pss(site2, site1, site3, 2, c_event);
                    }
                } else {
                    if (!site3.is_segment()) {
                        // (segment, segment, point) sites.
                        return create_circle_event_pss(site3, site1, site2, 3, c_event);
                    } else {
                        // (segment, segment, segment) sites.
                        return create_circle_event_sss(site1, site2, site3, c_event);
                    }
                }
            }
        }

        // Add a new circle event to the event queue.
        // bisector_node corresponds to the (site2, site3) bisector.
        void activate_circle_event(const site_event_type &site1,
                                   const site_event_type &site2,
                                   const site_event_type &site3,
                                   beach_line_iterator bisector_node) {
            circle_event_type c_event;
            // Check if the three input sites create a circle event.
            if (create_circle_event(site1, site2, site3, c_event)) {
                // Update circle event's bisector iterator to point to the
                // second bisector that forms it in the beach line.
                c_event.bisector(bisector_node);

                // Add the new circle event to the circle events queue.
                // Update bisector's circle event iterator to point to the
                // new circle event in the circle event queue.
                bisector_node->second.activate_circle_event(
                    circle_events_.push(c_event));
            }
        }

    private:
        struct end_point_comparison {
            bool operator() (const end_point_type &end1, const end_point_type &end2) const {
                return end1.first > end2.first;
            }
        };

        std::vector<site_event_type> site_events_;
        site_event_iterator_type site_event_iterator_;
        std::priority_queue< end_point_type, std::vector<end_point_type>,
                             end_point_comparison > end_points_;
        circle_event_queue_type circle_events_;
        beach_line_type beach_line_;
        output_type *output_;

        //Disallow copy constructor and operator=
        voronoi_builder(const voronoi_builder&);
        void operator=(const voronoi_builder&);
    };

    // Public methods to compute voronoi diagram.
    // points - vector of input points.
    // segments - vector of input segments.
    // output - voronoi output data structure to hold voronoi diagram.
    // The assumption is made that input doesn't contain segments that
    // intersect or points lying on the segments. Also coordinates of
    // the points and of the endpoints of the segments should be within
    // signed integer range [-2^31, 2^31-1].
    // Complexity - O(N*logN), memory usage - O(N), where N is the total
    // number of points and segments.

    template <typename T, typename PC, typename VD>
    static inline void construct_voronoi_points(const PC &points, VD &output) {
        voronoi_builder<T, VD> builder;
        builder.insert_points(points.begin(), points.end());
        builder.construct(output);
        builder.clear();
    }

    template <typename T, typename SC, typename VD>
    static inline void construct_voronoi_segments(const SC &segments, VD &output) {
        voronoi_builder<T, VD> builder;
        builder.insert_segments(segments.begin(), segments.end());
        builder.construct(output);
        builder.clear();
    }

    template <typename T, typename PC, typename SC, typename VD>
    static inline void construct_voronoi(const PC &points, const SC &segments, VD &output) {
        voronoi_builder<T, VD> builder;
        builder.insert_sites(points.begin(), points.end(), segments.begin(), segments.end());
        builder.construct(output);
        builder.clear();
    }

} // sweepline
} // boost

#endif
