// Boost sweepline/voronoi_calc_kernel.hpp header file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SWEEPLINE_VORONOI_CALC_KERNEL
#define BOOST_SWEEPLINE_VORONOI_CALC_KERNEL

#include "voronoi_fpt_kernel.hpp"

namespace boost {
namespace sweepline {
namespace detail {

template <typename T>
class voronoi_calc_kernel;

template <>
class voronoi_calc_kernel<int> {
public:
    typedef double fpt_type;
    typedef polygon_ulong_long_type ulong_long_type;

    enum kOrientation {
        RIGHT = -1,
        COLLINEAR = 0,
        LEFT = 1,
    };

    // Value is a determinant of two vectors.
    // Return orientation based on the sign of the determinant.
    template <typename T>
    static kOrientation get_orientation(T value) {
        if (value == static_cast<T>(0.0)) return COLLINEAR;
        return (value < static_cast<T>(0.0)) ? RIGHT : LEFT;
    }

    // Compute robust cross_product: a1 * b2 - b1 * a2.
    // The result is correct with epsilon relative error equal to 2EPS.
    template <typename T>
    static fpt_type robust_cross_product(T a1_, T b1_, T a2_, T b2_) {
        ulong_long_type a1, b1, a2, b2;
        bool a1_plus, a2_plus, b1_plus, b2_plus;
        a1_plus = convert_to_65_bit(a1_, a1);
        b1_plus = convert_to_65_bit(b1_, b1);
        a2_plus = convert_to_65_bit(a2_, a2);
        b2_plus = convert_to_65_bit(b2_, b2);

        ulong_long_type expr_l = a1 * b2;
        bool expr_l_plus = (a1_plus == b2_plus) ? true : false;
        ulong_long_type expr_r = b1 * a2;
        bool expr_r_plus = (a2_plus == b1_plus) ? true : false;

        if (expr_l == 0) expr_l_plus = true;
        if (expr_r == 0) expr_r_plus = true;

        if ((expr_l_plus == expr_r_plus) && (expr_l == expr_r))
            return static_cast<fpt_type>(0.0);

        // Produce the result with epsilon relative error.
        if (!expr_l_plus) {
            if (expr_r_plus)
                return -static_cast<fpt_type>(expr_l) -
                        static_cast<fpt_type>(expr_r);
            else return (expr_l > expr_r) ?
                        -static_cast<fpt_type>(expr_l - expr_r) :
                         static_cast<fpt_type>(expr_r - expr_l);
        } else {
            if (!expr_r_plus)
                return static_cast<fpt_type>(expr_l) +
                       static_cast<fpt_type>(expr_r);
            else
                return (expr_l < expr_r) ?
                       -static_cast<fpt_type>(expr_r - expr_l) :
                        static_cast<fpt_type>(expr_l - expr_r);
        }
    }

    // Robust orientation test. Works correctly for any input type that
    // can be casted without lose of data to the integer type within a range
    // [-2^32, 2^32-1].
    // Arguments: dif_x1_, dif_y1 - coordinates of the first vector.
    //            dif_x2_, dif_y2 - coordinates of the second vector.
    // Returns orientation test result for input vectors.
    template <typename T>
    static kOrientation get_orientation(T dif_x1_, T dif_y1_, T dif_x2_, T dif_y2_) {
        return get_orientation(robust_cross_product(dif_x1_, dif_y1_, dif_x2_, dif_y2_));
    }

    // Robust orientation test. Works correctly for any input coordinate type
    // that can be casted without lose of data to integer type within a range
    // [-2^31, 2^31 - 1] - signed integer type.
    // Arguments: point1, point2 - represent the first vector;
    //            point2, point3 - represent the second vector;
    // Returns orientation test result for input vectors.
    template <typename Point>
    static kOrientation get_orientation(const Point &point1,
                                        const Point &point2,
                                        const Point &point3) {
        return get_orientation(robust_cross_product(point1.x() - point2.x(),
                                                    point1.y() - point2.y(),
                                                    point2.x() - point3.x(),
                                                    point2.y() - point3.y()));
    }

    template <typename Site>
    struct site_comparison_predicate {
        typedef Site site_type;

        bool operator()(const site_type &lhs, const site_type &rhs) const {
            if (lhs.x0() != rhs.x0()) return lhs.x0() < rhs.x0();
            if (!lhs.is_segment()) {
                if (!rhs.is_segment()) return lhs.y0() < rhs.y0();
                if (rhs.is_vertical()) return lhs.y0() <= rhs.y0();
                return true;
            } else {
                if (rhs.is_vertical()) {
                    if(lhs.is_vertical()) return lhs.y0() < rhs.y0();
                    return false;
                }
                if (lhs.is_vertical()) return true;
                if (lhs.y0() != rhs.y0()) return lhs.y0() < rhs.y0();
                return get_orientation(lhs.point1(), lhs.point0(), rhs.point1()) == LEFT;
            }
        }
    };

    template <typename Site>
    struct site_equality_predicate {
        typedef Site site_type;

        bool operator()(const site_type &lhs, const site_type &rhs) const {
            return lhs.point0() == rhs.point0() &&
                   lhs.point1() == rhs.point1();
        }
    };

    template <typename Circle>
    struct circle_comparison_predicate {
        typedef Circle circle_type;

        static const unsigned int ULPS = 128;

        bool operator()(const circle_type &lhs, const circle_type &rhs) const {
            if (almost_equal(lhs.lower_x(), rhs.lower_x(), ULPS)) {
                if (almost_equal(lhs.lower_y(), rhs.lower_y(), ULPS)) {
                    return false;
                }
                return lhs.lower_y() < rhs.lower_y();
            }
            return lhs.lower_x() < rhs.lower_x();
        }
    };

    template <typename Site, typename Circle>
    struct event_comparison_predicate {
        typedef Site site_type;
        typedef Circle circle_type;

        static const unsigned int ULPS = 64;

        bool operator()(const site_type &lhs, const circle_type &rhs) const {
            if (almost_equal(lhs.x(), rhs.lower_x(), ULPS)) {
                if (almost_equal(lhs.y(), rhs.lower_y(), ULPS)) return false;
                return lhs.y() < rhs.lower_y();
            }
            return lhs.x() < rhs.lower_x();
        }
    };

    template <typename Site>
    class distance_predicate {
    public:
        typedef Site site_type;
        
        bool operator()(const site_type& left_site,
                        const site_type& right_site,
                        const site_type& new_site) const {
            if (!left_site.is_segment()) {
                if (!right_site.is_segment()) {
                    return pp(left_site, right_site, new_site);
                } else {
                    return ps(left_site, right_site, new_site, false);
                }
            } else {
                if (!right_site.is_segment()) {
                    return ps(right_site, left_site, new_site, true);
                } else {
                    return ss(left_site, right_site, new_site);
                }
            }
        }

    private:
        typedef typename Site::point_type point_type;

        // Find the x-coordinate (relative to the sweepline position) of the point
        // of the intersection of the horizontal line going through the new site
        // with the arc corresponding to the point site.
        // The relative error is atmost 3EPS.
        fpt_type find_distance_to_point_arc(const site_type &site,
                                            const point_type &point) const {
            fpt_type dx = static_cast<fpt_type>(site.x()) -
                          static_cast<fpt_type>(point.x());
            fpt_type dy = static_cast<fpt_type>(site.y()) -
                          static_cast<fpt_type>(point.y());
            return (dx * dx + dy * dy) / (static_cast<fpt_type>(2.0) * dx);
        }

        // Find the x-coordinate (relative to the sweepline position) of the point
        // of the intersection of the horizontal line going through the new site
        // with the arc corresponding to the segment site.
        // The relative error is atmost 8EPS.
        fpt_type find_distance_to_segment_arc(const site_type &site,
                                              const point_type &point) const {
            if (site.is_vertical()) {
                return (static_cast<fpt_type>(site.x()) - static_cast<fpt_type>(point.x())) *
                       static_cast<fpt_type>(0.5);
            } else {
                const point_type &segment0 = site.point0(true);
                const point_type &segment1 = site.point1(true);
                fpt_type a1 = static_cast<fpt_type>(segment1.x()) -
                              static_cast<fpt_type>(segment0.x());
                fpt_type b1 = static_cast<fpt_type>(segment1.y()) -
                              static_cast<fpt_type>(segment0.y());
                fpt_type a3 = static_cast<fpt_type>(point.x()) -
                              static_cast<fpt_type>(segment0.x());
                fpt_type b3 = static_cast<fpt_type>(point.y()) -
                              static_cast<fpt_type>(segment0.y());
                fpt_type k = std::sqrt(a1 * a1 + b1 * b1);
                // Avoid substraction while computing k.
                if (b1 >= static_cast<fpt_type>(0.0)) k = static_cast<fpt_type>(1.0) / (b1 + k);
                else k = (k - b1) / (a1 * a1);
                // Relative error of the robust cross product is 2EPS.
                // Relative error of the k is atmost 5EPS.
                // The resulting relative error is atmost 8EPS.
                return robust_cross_product(a1, b1, a3, b3) * k;
            }
        }

        // Robust predicate, avoids using high-precision libraries.
        // Returns true if a horizontal line going through the new point site
        // intersects right arc at first, else returns false. If horizontal line
        // goes through intersection point of the given two arcs returns false.
        // Works correctly for any input coordinate type that can be casted without
        // lose of data to the integer type within a range [-2^31, 2^31-1].
        bool pp(const site_type &left_site,
                const site_type &right_site,
                const site_type &new_site) const {
            // Any two point sites with different x-coordinates create two
            // bisectors. Each bisector is defined by the order the sites
            // appear in its representation. Predicates used in this function
            // won't produce the correct result for the any arrangment of the
            // input sites. That's why some preprocessing is required to handle
            // such cases.
            const point_type &left_point = left_site.point0();
            const point_type &right_point = right_site.point0();
            const point_type &new_point = new_site.point0();
            if (left_point.x() > right_point.x()) {
                if (new_point.y() <= left_point.y())
                    return false;
            } else if (left_point.x() < right_point.x()) {
                if (new_point.y() >= right_point.y())
                    return true;
            } else {
                // If x-coordinates of the sites are equal, we may produce the
                // result without any further computations.
                return static_cast<fpt_type>(left_point.y()) +
                       static_cast<fpt_type>(right_point.y()) <
                       static_cast<fpt_type>(2.0) *
                       static_cast<fpt_type>(new_point.y());
            }

            fpt_type dist1 = find_distance_to_point_arc(left_site, new_point);
            fpt_type dist2 = find_distance_to_point_arc(right_site, new_point);

            // The undefined ulp range is equal to 3EPS + 3EPS <= 6ULP.
            return dist1 < dist2;
        }

        kPredicateResult fast_ps(const site_type &left_site, const site_type &right_site,
                                 const site_type &new_site, bool reverse_order) const {
            const point_type &site_point = left_site.point0();
            const point_type &segment_start = right_site.point0(true);
            const point_type &segment_end = right_site.point1(true);
            const point_type &new_point = new_site.point0();
            if (get_orientation(segment_start, segment_end, new_point) != RIGHT) {
                return (!right_site.is_inverse()) ? LESS : MORE;
            }

            fpt_type dif_x = static_cast<fpt_type>(new_point.x()) -
                             static_cast<fpt_type>(site_point.x());
            fpt_type dif_y = static_cast<fpt_type>(new_point.y()) -
                             static_cast<fpt_type>(site_point.y());
            fpt_type a = static_cast<fpt_type>(segment_end.x()) -
                         static_cast<fpt_type>(segment_start.x());
            fpt_type b = static_cast<fpt_type>(segment_end.y()) -
                         static_cast<fpt_type>(segment_start.y());

            if (right_site.is_vertical()) {
                if (new_point.y() < site_point.y() && !reverse_order)
                    return MORE;
                else if (new_point.y() > site_point.y() && reverse_order)
                    return LESS;
                return UNDEFINED;
            } else {
                kOrientation orientation = get_orientation(a, b, dif_x, dif_y);
                if (orientation == LEFT) {
                    if (!right_site.is_inverse())
                        return reverse_order ? LESS : UNDEFINED;
                    return reverse_order ? UNDEFINED : MORE;
                }
            }

            fpt_type fast_left_expr = a * (dif_y + dif_x) * (dif_y - dif_x);
            fpt_type fast_right_expr = (2.0 * b) * dif_x * dif_y;
            if (!(almost_equal(fast_left_expr, fast_right_expr, 4))) {
                if ((fast_left_expr > fast_right_expr) ^ reverse_order)
                    return reverse_order ? LESS : MORE;
                return UNDEFINED;
            }
            return UNDEFINED;
        }

        // Returns true if a horizontal line going through a new site intersects
        // right arc at first, else returns false. If horizontal line goes
        // through intersection point of the given two arcs returns false also.
        // reverse_order flag defines arrangement of the sites. If it's false
        // the order is (point, segment), else - (segment, point).
        bool ps(const site_type &left_site, const site_type &right_site,
                const site_type &new_site, bool reverse_order) const {
            kPredicateResult fast_res = fast_ps(
                left_site, right_site, new_site, reverse_order);
            if (fast_res != UNDEFINED) {
                return (fast_res == LESS);
            }

            fpt_type dist1 = find_distance_to_point_arc(left_site, new_site.point0());
            fpt_type dist2 = find_distance_to_segment_arc(right_site, new_site.point0());

            // The undefined ulp range is equal to 3EPS + 8EPS <= 11ULP.
            return reverse_order ^ (dist1 < dist2);
        }

        // Returns true if a horizontal line going through a new site intersects
        // right arc at first, else returns false. If horizontal line goes
        // through intersection point of the given two arcs returns false also.
        bool ss(const site_type &left_site,
                const site_type &right_site,
                const site_type &new_site) const {
            // Handle temporary segment sites.
            if (left_site.index() == right_site.index()) {
                return get_orientation(left_site.point0(),
                                       left_site.point1(),
                                       new_site.point0()) == LEFT;
            }

            // Distances between the x-coordinate of the sweepline and
            // the x-coordinates of the points of the intersections of the
            // horizontal line going through the new site with arcs corresponding
            // to the first and to the second segment sites respectively.
            fpt_type dist1 = find_distance_to_segment_arc(left_site, new_site.point0());
            fpt_type dist2 = find_distance_to_segment_arc(right_site, new_site.point0());

            // The undefined ulp range is equal to 8EPS + 8EPS <= 16ULP.
            return dist1 < dist2;
        }
    };

    template <typename Node>
    class node_comparison_predicate {
    public:
        typedef Node node_type;
        typedef typename Node::coordinate_type coordinate_type;
        typedef typename Node::site_event_type site_type;

        // Compares nodes in the balanced binary search tree. Nodes are
        // compared based on the y coordinates of the arcs intersection points.
        // Nodes with less y coordinate of the intersection point go first.
        // Comparison is only called during the new site events processing.
        // That's why one of the nodes will always lie on the sweepline and may
        // be represented as a straight horizontal line.
        bool operator() (const node_type &node1,
                         const node_type &node2) const {
            // Get x coordinate of the righmost site from both nodes.
            const site_type &site1 = get_comparison_site(node1);
            const site_type &site2 = get_comparison_site(node2);

            if (site1.x() < site2.x()) {
                // The second node contains a new site.
                return predicate_(node1.left_site(), node1.right_site(), site2);
            } else if (site1.x() > site2.x()) {
                // The first node contains a new site.
                return !predicate_(node2.left_site(), node2.right_site(), site1);
            } else {
                // This checks were evaluated experimentally.
                if (site1.index() == site2.index()) {
                    // Both nodes are new (inserted during the same site event processing).
                    return get_comparison_y(node1) < get_comparison_y(node2);
                } else if (site1.index() < site2.index()) {
                    std::pair<coordinate_type, int> y1 = get_comparison_y(node1, false);
                    std::pair<coordinate_type, int> y2 = get_comparison_y(node2, true);
                    if (y1.first != y2.first) return y1.first < y2.first;
                    return (!site1.is_segment()) ? (y1.second < 0) : false;
                } else {
                    std::pair<coordinate_type, int> y1 = get_comparison_y(node1, true);
                    std::pair<coordinate_type, int> y2 = get_comparison_y(node2, false);
                    if (y1.first != y2.first) return y1.first < y2.first;
                    return (!site2.is_segment()) ? (y2.second > 0) : true;
                }
            }
        }

    private:
        typedef distance_predicate<site_type> distance_predicate_type;

        // Get the newer site.
        const site_type &get_comparison_site(const node_type &node) const {
            if (node.left_site().index() > node.right_site().index()) {
                return node.left_site();
            }
            return node.right_site();
        }
        
        // Get comparison pair: y coordinate and direction of the newer site.
        std::pair<coordinate_type, int> get_comparison_y(const node_type &node,
                                                         bool is_new_node = true) const {
            if (node.left_site().index() == node.right_site().index()) {
                return std::make_pair(node.left_site().y(), 0);
            }
            if (node.left_site().index() > node.right_site().index()) {
                if (!is_new_node &&
                    node.left_site().is_segment() &&
                    node.left_site().is_vertical()) {
                    return std::make_pair(node.left_site().y1(), 1);
                }
                return std::make_pair(node.left_site().y(), 1);
            }
            return std::make_pair(node.right_site().y(), -1);
        }

        distance_predicate_type predicate_;
    };

private:
    // Convert value to 64-bit unsigned integer.
    // Return true if the value is positive, else false.
    template <typename T>
    static inline bool convert_to_65_bit(T value, ulong_long_type &res) {
        if (value >= static_cast<T>(0.0)) {
            res = static_cast<ulong_long_type>(value);
            return true;
        } else {
            res = static_cast<ulong_long_type>(-value);
            return false;
        }
    }
};

} // detail
} // sweepline
} // boost

#endif