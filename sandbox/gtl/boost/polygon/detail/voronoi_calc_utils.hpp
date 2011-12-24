// Boost.Polygon library detail/voronoi_calc_utils.hpp header file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_VORONOI_CALC_UTILS
#define BOOST_POLYGON_VORONOI_CALC_UTILS

#include "voronoi_robust_fpt.hpp"

namespace boost {
namespace polygon {
namespace detail {

template <typename T>
class voronoi_calc_utils;

// Predicate utilities. Operates with the coordinate types that could
// be converted to the 32-bit signed integer without precision loss.
template <>
class voronoi_calc_utils<int32> {
public:
    typedef fpt64 fpt_type;

    static const uint32 ULPS;
    static const uint32 ULPSx2;
    static const fpt_type fULPS;
    static const fpt_type fULPSx2;

    // Represents the result of the epsilon robust predicate.
    // If the result is undefined some further processing is usually required.
    enum kPredicateResult {
        LESS = -1,
        UNDEFINED = 0,
        MORE = 1
    };

    // Represents orientation test result.
    enum kOrientation {
        RIGHT = -1,
        COLLINEAR = 0,
        LEFT = 1
    };

    // Value is a determinant of two vectors (e.g. x1 * y2 - x2 * y1).
    // Return orientation based on the sign of the determinant.
    template <typename T>
    static kOrientation get_orientation(T value) {
        if (value == static_cast<T>(0.0)) return COLLINEAR;
        return (value < static_cast<T>(0.0)) ? RIGHT : LEFT;
    }

    // Compute robust cross_product: a1 * b2 - b1 * a2.
    // It was mathematically proven that the result is correct
    // with epsilon relative error equal to 1EPS.
    template <typename T>
    static fpt_type robust_cross_product(T a1_, T b1_, T a2_, T b2_) {
        uint64 a1, b1, a2, b2;
        bool a1_plus, a2_plus, b1_plus, b2_plus;
        a1_plus = convert_to_65_bit(a1_, a1);
        b1_plus = convert_to_65_bit(b1_, b1);
        a2_plus = convert_to_65_bit(a2_, a2);
        b2_plus = convert_to_65_bit(b2_, b2);

        uint64 expr_l = a1 * b2;
        bool expr_l_plus = (a1_plus == b2_plus) ? true : false;
        uint64 expr_r = b1 * a2;
        bool expr_r_plus = (a2_plus == b1_plus) ? true : false;

        if (expr_l == 0) expr_l_plus = true;
        if (expr_r == 0) expr_r_plus = true;

        if ((expr_l_plus == expr_r_plus) && (expr_l == expr_r))
            return static_cast<fpt_type>(0.0);

        if (!expr_l_plus) {
            if (expr_r_plus)
                return -static_cast<fpt_type>(expr_l - expr_r);
            else return (expr_l > expr_r) ?
                        -static_cast<fpt_type>(expr_l - expr_r) :
                         static_cast<fpt_type>(expr_r - expr_l);
        } else {
            if (!expr_r_plus)
                return static_cast<fpt_type>(expr_l + expr_r);
            else
                return (expr_l < expr_r) ?
                       -static_cast<fpt_type>(expr_r - expr_l) :
                        static_cast<fpt_type>(expr_l - expr_r);
        }
    }

    template <typename T>
    static kOrientation get_orientation(T dif_x1_, T dif_y1_, T dif_x2_, T dif_y2_) {
        return get_orientation(robust_cross_product(dif_x1_, dif_y1_, dif_x2_, dif_y2_));
    }

    template <typename Point>
    static kOrientation get_orientation(const Point &point1,
                                        const Point &point2,
                                        const Point &point3) {
        fpt_type dx1 = static_cast<fpt_type>(point1.x()) -
                       static_cast<fpt_type>(point2.x());
        fpt_type dx2 = static_cast<fpt_type>(point2.x()) -
                       static_cast<fpt_type>(point3.x());
        fpt_type dy1 = static_cast<fpt_type>(point1.y()) -
                       static_cast<fpt_type>(point2.y());
        fpt_type dy2 = static_cast<fpt_type>(point2.y()) -
                       static_cast<fpt_type>(point3.y());
        return get_orientation(robust_cross_product(dx1, dy1, dx2, dy2));
    }

    template <typename Point>
    static bool is_vertical(const Point &point1, const Point &point2) {
        return point1.x() == point2.x();
    }

    template <typename Site>
    static bool is_vertical(const Site &site) {
        return is_vertical(site.point0(), site.point1());
    }

    template <typename Point>
    class point_comparison_predicate {
    public:
        typedef Point point_type;
        
        bool operator()(const point_type &lhs, const point_type &rhs) const {
            if (lhs.x() == rhs.x()) {
                return lhs.y() < rhs.y();
            }
            return lhs.x() < rhs.x(); 
        }
    };

    template <typename Site, typename Circle>
    class event_comparison_predicate {
    public:
        typedef Site site_type;
        typedef Circle circle_type;

        bool operator()(const site_type &lhs, const site_type &rhs) const {
            if (lhs.x0() != rhs.x0()) {
                return lhs.x0() < rhs.x0();
            }
            if (!lhs.is_segment()) {
                if (!rhs.is_segment()) {
                    return lhs.y0() < rhs.y0();
                }
                if (is_vertical(rhs)) {
                    return lhs.y0() <= rhs.y0();
                }
                return true;
            } else {
                if (is_vertical(rhs)) {
                    if(is_vertical(lhs)) {
                        return lhs.y0() < rhs.y0();
                    }
                    return false;
                }
                if (is_vertical(lhs)) {
                    return true;
                }
                if (lhs.y0() != rhs.y0()) {
                    return lhs.y0() < rhs.y0();
                }
                return get_orientation(lhs.point1(), lhs.point0(), rhs.point1()) == LEFT;
            }
        }

        bool operator()(const site_type &lhs, const circle_type &rhs) const {
            if (almost_equal(static_cast<fpt_type>(lhs.x()),
                             static_cast<fpt_type>(rhs.lower_x()), ULPS)) {
                if (almost_equal(static_cast<fpt_type>(lhs.y()),
                                 static_cast<fpt_type>(rhs.lower_y()), ULPS)) {
                    return false;
                }
                return static_cast<fpt_type>(lhs.y()) <
                       static_cast<fpt_type>(rhs.lower_y());
            }
            return static_cast<fpt_type>(lhs.x()) <
                   static_cast<fpt_type>(rhs.lower_x());
        }

        bool operator()(const circle_type &lhs, const site_type &rhs) const {
            if (almost_equal(static_cast<fpt_type>(lhs.lower_x()),
                             static_cast<fpt_type>(rhs.x()), ULPS)) {
                if (almost_equal(static_cast<fpt_type>(lhs.lower_y()),
                                 static_cast<fpt_type>(rhs.y()), ULPS)) {
                    return false;
                }
                return static_cast<fpt_type>(lhs.lower_y()) <
                       static_cast<fpt_type>(rhs.y());
            }
            return static_cast<fpt_type>(lhs.lower_x()) <
                   static_cast<fpt_type>(rhs.x());
        }

        bool operator()(const circle_type &lhs, const circle_type &rhs) const {
            if (almost_equal(static_cast<fpt_type>(lhs.lower_x()),
                             static_cast<fpt_type>(rhs.lower_x()), ULPSx2)) {
                if (almost_equal(static_cast<fpt_type>(lhs.lower_y()),
                                 static_cast<fpt_type>(rhs.lower_y()), ULPSx2)) {
                    return false;
                }
                return lhs.lower_y() < rhs.lower_y();
            }
            return lhs.lower_x() < rhs.lower_x();
        }
    };

    template <typename Site>
    class distance_predicate {
    public:
        typedef Site site_type;

        // Returns true if a horizontal line going through a new site intersects
        // right arc at first, else returns false. If horizontal line goes
        // through intersection point of the given two arcs returns false also.
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

        // Robust predicate, avoids using high-precision libraries.
        // Returns true if a horizontal line going through the new point site
        // intersects right arc at first, else returns false. If horizontal line
        // goes through intersection point of the given two arcs returns false.
        bool pp(const site_type &left_site,
                const site_type &right_site,
                const site_type &new_site) const {
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
                return static_cast<fpt_type>(left_point.y()) +
                       static_cast<fpt_type>(right_point.y()) <
                       2.0 * static_cast<fpt_type>(new_point.y());
            }

            fpt_type dist1 = find_distance_to_point_arc(left_site, new_point);
            fpt_type dist2 = find_distance_to_point_arc(right_site, new_point);

            // The undefined ulp range is equal to 3EPS + 3EPS <= 6ULP.
            return dist1 < dist2;
        }

        bool ps(const site_type &left_site, const site_type &right_site,
                const site_type &new_site, bool reverse_order) const {
            kPredicateResult fast_res = fast_ps(
                left_site, right_site, new_site, reverse_order);
            if (fast_res != UNDEFINED) {
                return (fast_res == LESS);
            }

            fpt_type dist1 = find_distance_to_point_arc(left_site, new_site.point0());
            fpt_type dist2 = find_distance_to_segment_arc(right_site, new_site.point0());

            // The undefined ulp range is equal to 3EPS + 7EPS <= 10ULP.
            return reverse_order ^ (dist1 < dist2);
        }

        bool ss(const site_type &left_site,
                const site_type &right_site,
                const site_type &new_site) const {
            // Handle temporary segment sites.
            if (left_site.point0() == right_site.point0() &&
                left_site.point1() == right_site.point1()) {
                return get_orientation(left_site.point0(),
                                       left_site.point1(),
                                       new_site.point0()) == LEFT;
            }

            fpt_type dist1 = find_distance_to_segment_arc(left_site, new_site.point0());
            fpt_type dist2 = find_distance_to_segment_arc(right_site, new_site.point0());

            // The undefined ulp range is equal to 7EPS + 7EPS <= 14ULP.
            return dist1 < dist2;
        }

        fpt_type find_distance_to_point_arc(const site_type &site,
                                            const point_type &point) const {
            fpt_type dx = site.x() - point.x();
            fpt_type dy = site.y() - point.y();
            // The relative error is atmost 3EPS.
            return (dx * dx + dy * dy) / (static_cast<fpt_type>(2.0) * dx);
        }

        fpt_type find_distance_to_segment_arc(const site_type &site,
                                              const point_type &point) const {
            if (is_vertical(site)) {
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
                if (b1 >= static_cast<fpt_type>(0.0)) {
                    k = static_cast<fpt_type>(1.0) / (b1 + k);
                } else {
                    k = (k - b1) / (a1 * a1);
                }
                // The relative error is atmost 7EPS.
                return robust_cross_product(a1, b1, a3, b3) * k;
            }
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

            if (is_vertical(right_site)) {
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
            fpt_type fast_right_expr = (static_cast<fpt_type>(2) * b) * dif_x * dif_y;
            if (!(almost_equal(fast_left_expr, fast_right_expr, 4))) {
                if ((fast_left_expr > fast_right_expr) ^ reverse_order)
                    return reverse_order ? LESS : MORE;
                return UNDEFINED;
            }
            return UNDEFINED;
        }
    };

    template <typename Node>
    class node_comparison_predicate {
    public:
        typedef Node node_type;
        typedef typename Node::site_type site_type;
        typedef typename site_type::coordinate_type coordinate_type;
        typedef distance_predicate<site_type> distance_predicate_type;

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
        // Get the newer site.
        const site_type &get_comparison_site(const node_type &node) const {
            if (node.left_site().index() > node.right_site().index()) {
                return node.left_site();
            }
            return node.right_site();
        }

        // Get comparison pair: y coordinate and direction of the newer site.
        std::pair<coordinate_type, int> get_comparison_y(
            const node_type &node, bool is_new_node = true) const {
            if (node.left_site().index() == node.right_site().index()) {
                return std::make_pair(node.left_site().y(), 0);
            }
            if (node.left_site().index() > node.right_site().index()) {
                if (!is_new_node &&
                    node.left_site().is_segment() &&
                    is_vertical(node.left_site())) {
                    return std::make_pair(node.left_site().y1(), 1);
                }
                return std::make_pair(node.left_site().y(), 1);
            }
            return std::make_pair(node.right_site().y(), -1);
        }

        distance_predicate_type predicate_;
    };

    template <typename Site>
    class circle_existence_predicate {
    public:
        typedef typename Site::point_type point_type;
        typedef Site site_type;

        bool ppp(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3) const {
            return get_orientation(site1.point0(), site2.point0(), site3.point0()) == RIGHT;
        }

        bool pps(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int segment_index) const {
            if (segment_index != 2) {
                kOrientation orient1 = get_orientation(site1.point0(),
                    site2.point0(), site3.point0(true));
                kOrientation orient2 = get_orientation(site1.point0(),
                    site2.point0(), site3.point1(true));
                if (segment_index == 1 && site1.x0() >= site2.x0()) {
                    if (orient1 != RIGHT)
                        return false;
                } else if (segment_index == 3 && site2.x0() >= site1.x0()) {
                    if (orient2 != RIGHT)
                        return false;
                } else if (orient1 != RIGHT && orient2 != RIGHT) {
                    return false;
                }
            } else {
                if (site3.point0(true) == site1.point0() &&
                    site3.point1(true) == site2.point0())
                    return false;
            }
            return true;
        }

        bool pss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int point_index) const {
            if (site2.point0() == site3.point0() &&
                site2.point1() == site3.point1()) {
                return false;
            }
            if (point_index == 2) {
                if (!site2.is_inverse() && site3.is_inverse())
                    return false;
                if (site2.is_inverse() == site3.is_inverse() &&
                    get_orientation(site2.point0(true), site1.point0(), site3.point1(true)) != RIGHT)
                    return false;
            }
            return true;
        }

        bool sss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3) const {
             if (site1.point0() == site2.point0() &&
                 site1.point1() == site2.point1())
                 return false;
             if (site2.point0() == site3.point0() &&
                 site2.point1() == site3.point1())
                 return false;
             return true;
        }
    };

    template <typename Site, typename Circle>
    class mp_circle_formation_functor {
    public:
        typedef typename Site::point_type point_type;
        typedef Site site_type;
        typedef Circle circle_type;
        typedef robust_sqrt_expr<eint4096, efpt64> robust_sqrt_expr_type;

        void ppp(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &circle,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef eint256 eint;
            eint dif_x[3], dif_y[3], sum_x[2], sum_y[2];
            dif_x[0] = static_cast<int64>(site1.x()) -
                       static_cast<int64>(site2.x());
            dif_x[1] = static_cast<int64>(site2.x()) -
                       static_cast<int64>(site3.x());
            dif_x[2] = static_cast<int64>(site1.x()) -
                       static_cast<int64>(site3.x());
            dif_y[0] = static_cast<int64>(site1.y()) -
                       static_cast<int64>(site2.y());
            dif_y[1] = static_cast<int64>(site2.y()) -
                       static_cast<int64>(site3.y());
            dif_y[2] = static_cast<int64>(site1.y()) -
                       static_cast<int64>(site3.y());
            sum_x[0] = static_cast<int64>(site1.x()) +
                       static_cast<int64>(site2.x());
            sum_x[1] = static_cast<int64>(site2.x()) +
                       static_cast<int64>(site3.x());
            sum_y[0] = static_cast<int64>(site1.y()) +
                       static_cast<int64>(site2.y());
            sum_y[1] = static_cast<int64>(site2.y()) +
                       static_cast<int64>(site3.y());
            fpt_type denom = get_d(dif_x[0] * dif_y[1] - dif_x[1] * dif_y[0]) * 2.0;
            eint numer1 = dif_x[0] * sum_x[0] + dif_y[0] * sum_y[0];
            eint numer2 = dif_x[1] * sum_x[1] + dif_y[1] * sum_y[1];

            if (recompute_c_x || recompute_lower_x) {
                eint c_x = numer1 * dif_y[1] - numer2 * dif_y[0];
                circle.x(get_d(c_x) / denom);

                if (recompute_lower_x) {
                    // Evaluate radius of the circle.
                    eint sqr_r = (dif_x[0] * dif_x[0] + dif_y[0] * dif_y[0]) *
                                 (dif_x[1] * dif_x[1] + dif_y[1] * dif_y[1]) *
                                 (dif_x[2] * dif_x[2] + dif_y[2] * dif_y[2]);
                    fpt_type r = get_sqrt(get_d(sqr_r));

                    // If c_x >= 0 then lower_x = c_x + r,
                    // else lower_x = (c_x * c_x - r * r) / (c_x - r).
                    // To guarantee epsilon relative error.
                    if (circle.x() >= static_cast<fpt_type>(0.0)) {
                        circle.lower_x(circle.x() + r / fabs(denom));
                    } else {
                        eint numer = c_x * c_x - sqr_r;
                        fpt_type lower_x = get_d(numer) /
                                           (denom * (get_d(c_x) + r));
                        circle.lower_x(lower_x);
                    }
                }
            }

            if (recompute_c_y) {
                eint c_y = numer2 * dif_x[0] - numer1 * dif_x[1];
                circle.y(get_d(c_y) / denom);
            }
        }

        // Recompute parameters of the circle event using high-precision library.
        void pps(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int segment_index,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef eint4096 eint;
            eint cA[4], cB[4];
            eint line_a = static_cast<int64>(site3.point1(true).y()) -
                          static_cast<int64>(site3.point0(true).y());
            eint line_b = static_cast<int64>(site3.point0(true).x()) -
                          static_cast<int64>(site3.point1(true).x());
            eint segm_len = line_a * line_a + line_b * line_b;
            eint vec_x = static_cast<int64>(site2.y()) -
                         static_cast<int64>(site1.y());
            eint vec_y = static_cast<int64>(site1.x()) -
                         static_cast<int64>(site2.x());
            eint sum_x = static_cast<int64>(site1.x()) +
                         static_cast<int64>(site2.x());
            eint sum_y = static_cast<int64>(site1.y()) +
                         static_cast<int64>(site2.y());
            eint teta = line_a * vec_x + line_b * vec_y;
            eint denom = vec_x * line_b - vec_y * line_a;

            eint dif0 = static_cast<int64>(site3.point1().y()) -
                        static_cast<int64>(site1.y());
            eint dif1 = static_cast<int64>(site1.x()) -
                        static_cast<int64>(site3.point1().x());
            eint A = line_a * dif1 - line_b * dif0;
            dif0 = static_cast<int64>(site3.point1().y()) -
                   static_cast<int64>(site2.y());
            dif1 = static_cast<int64>(site2.x()) -
                   static_cast<int64>(site3.point1().x());
            eint B = line_a * dif1 - line_b * dif0;
            eint sum_AB = A + B;

            if (is_zero(denom)) {
                eint numer = teta * teta - sum_AB * sum_AB;
                eint denom = teta * sum_AB;
                cA[0] = denom * sum_x * 2 + numer * vec_x;
                cB[0] = segm_len;
                cA[1] = denom * sum_AB * 2 + numer * teta;
                cB[1] = 1;
                cA[2] = denom * sum_y * 2 + numer * vec_y;
                fpt_type inv_denom = 1.0 / get_d(denom);
                if (recompute_c_x) {
                    c_event.x(0.25 * get_d(cA[0]) * inv_denom);
                }
                if (recompute_c_y) {
                    c_event.y(0.25 * get_d(cA[2]) * inv_denom);
                }
                if (recompute_lower_x) {
                    c_event.lower_x(0.25 * get_d(sqrt_expr_.eval2(cA, cB)) * inv_denom /
                                    get_sqrt(get_d(segm_len)));
                }
                return;
            }

            eint det = (teta * teta + denom * denom) * A * B * 4;
            fpt_type inv_denom_sqr = 1.0 / sqr_value(get_d(denom));

            if (recompute_c_x || recompute_lower_x) {
                cA[0] = sum_x * denom * denom + teta * sum_AB * vec_x;
                cB[0] = 1;
                cA[1] = (segment_index == 2) ? -vec_x : vec_x;
                cB[1] = det;
                if (recompute_c_x) {
                    c_event.x(0.5 * get_d(sqrt_expr_.eval2(cA, cB)) * inv_denom_sqr);
                }
            }

            if (recompute_c_y || recompute_lower_x) {
                cA[2] = sum_y * denom * denom + teta * sum_AB * vec_y;
                cB[2] = 1;
                cA[3] = (segment_index == 2) ? -vec_y : vec_y;
                cB[3] = det;
                if (recompute_c_y) {
                    c_event.y(0.5 * get_d(sqrt_expr_.eval2(&cA[2], &cB[2])) *
                              inv_denom_sqr);
                }
            }

            if (recompute_lower_x) {
                cB[0] = cB[0] * segm_len;
                cB[1] = cB[1] * segm_len;
                cA[2] = sum_AB * (denom * denom + teta * teta);
                cB[2] = 1;
                cA[3] = (segment_index == 2) ? -teta : teta;
                cB[3] = det;
                c_event.lower_x(0.5 * get_d(sqrt_expr_.eval4(cA, cB)) * inv_denom_sqr /
                                get_sqrt(get_d(segm_len)));
            }
        }

        // Recompute parameters of the circle event using high-precision library.
        void pss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int point_index,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef eint4096 eint;
            eint a[2], b[2], c[2], cA[4], cB[4];
            const point_type &segm_start1 = site2.point1(true);
            const point_type &segm_end1 = site2.point0(true);
            const point_type &segm_start2 = site3.point0(true);
            const point_type &segm_end2 = site3.point1(true);
            a[0] = static_cast<int64>(segm_end1.x()) -
                   static_cast<int64>(segm_start1.x());
            b[0] = static_cast<int64>(segm_end1.y()) -
                   static_cast<int64>(segm_start1.y());
            a[1] = static_cast<int64>(segm_end2.x()) -
                   static_cast<int64>(segm_start2.x());
            b[1] = static_cast<int64>(segm_end2.y()) -
                   static_cast<int64>(segm_start2.y());
            eint orientation = a[1] * b[0] - a[0] * b[1];
            if (is_zero(orientation)) {
                fpt_type denom = get_d(a[0] * a[0] + b[0] * b[0]) * 2;
                c[0] = b[0] * (static_cast<int64>(segm_start2.x()) -
                               static_cast<int64>(segm_start1.x())) -
                       a[0] * (static_cast<int64>(segm_start2.y()) -
                               static_cast<int64>(segm_start1.y()));
                eint dx = a[0] * (static_cast<int64>(site1.y()) -
                                  static_cast<int64>(segm_start1.y())) -
                          b[0] * (static_cast<int64>(site1.x()) -
                                  static_cast<int64>(segm_start1.x()));
                eint dy = b[0] * (static_cast<int64>(site1.x()) -
                                  static_cast<int64>(segm_start2.x())) -
                          a[0] * (static_cast<int64>(site1.y()) -
                                  static_cast<int64>(segm_start2.y()));
                cB[0] = dx * dy;
                cB[1] = 1;

                if (recompute_c_y) {
                    cA[0] = b[0] * ((point_index == 2) ? 2 : -2);
                    cA[1] = a[0] * a[0] * (static_cast<int64>(segm_start1.y()) +
                                           static_cast<int64>(segm_start2.y())) -
                            a[0] * b[0] * (static_cast<int64>(segm_start1.x()) +
                                           static_cast<int64>(segm_start2.x()) -
                                           static_cast<int64>(site1.x()) * 2) +
                            b[0] * b[0] * (static_cast<int64>(site1.y()) * 2);
                    fpt_type c_y = get_d(sqrt_expr_.eval2(cA, cB));
                    c_event.y(c_y / denom);
                }

                if (recompute_c_x || recompute_lower_x) {
                    cA[0] = a[0] * ((point_index == 2) ? 2 : -2);
                    cA[1] = b[0] * b[0] * (static_cast<int64>(segm_start1.x()) +
                                           static_cast<int64>(segm_start2.x())) -
                            a[0] * b[0] * (static_cast<int64>(segm_start1.y()) +
                                           static_cast<int64>(segm_start2.y()) -
                                           static_cast<int64>(site1.y()) * 2) +
                            a[0] * a[0] * (static_cast<int64>(site1.x()) * 2);

                    if (recompute_c_x) {
                        fpt_type c_x = get_d(sqrt_expr_.eval2(cA, cB));
                        c_event.x(c_x / denom);
                    }

                    if (recompute_lower_x) {
                        cA[2] = is_neg(c[0]) ? -c[0] : c[0];
                        cB[2] = a[0] * a[0] + b[0] * b[0];
                        fpt_type lower_x = get_d(sqrt_expr_.eval3(cA, cB));
                        c_event.lower_x(lower_x / denom);
                    }
                }
                return;
            }
            c[0] = b[0] * static_cast<int32>(segm_end1.x()) -
                   a[0] * static_cast<int32>(segm_end1.y());
            c[1] = a[1] * static_cast<int32>(segm_end2.y()) -
                   b[1] * static_cast<int32>(segm_end2.x());
            eint ix = a[0] * c[1] + a[1] * c[0];
            eint iy = b[0] * c[1] + b[1] * c[0];
            eint dx = ix - orientation * static_cast<int32>(site1.x());
            eint dy = iy - orientation * static_cast<int32>(site1.y());
            if (is_zero(dx) && is_zero(dy)) {
                fpt_type denom = get_d(orientation);
                fpt_type c_x = get_d(ix) / denom;
                fpt_type c_y = get_d(iy) / denom;
                c_event = circle_type(c_x, c_y, c_x);
                return;
            }

            eint sign = ((point_index == 2) ? 1 : -1) * (is_neg(orientation) ? 1 : -1);
            cA[0] = a[1] * -dx + b[1] * -dy;
            cA[1] = a[0] * -dx + b[0] * -dy;
            cA[2] = sign;
            cA[3] = 0;
            cB[0] = a[0] * a[0] + b[0] * b[0];
            cB[1] = a[1] * a[1] + b[1] * b[1];
            cB[2] = a[0] * a[1] + b[0] * b[1];
            cB[3] = (a[0] * dy - b[0] * dx) * (a[1] * dy - b[1] * dx) * -2;
            fpt_type temp = get_d(sqrt_expr_evaluator_pss<eint, efpt64>(cA, cB));
            fpt_type denom = temp * get_d(orientation);

            if (recompute_c_y) {
                cA[0] = b[1] * (dx * dx + dy * dy) - iy * (dx * a[1] + dy * b[1]);
                cA[1] = b[0] * (dx * dx + dy * dy) - iy * (dx * a[0] + dy * b[0]);
                cA[2] = iy * sign;
                fpt_type cy = get_d(sqrt_expr_evaluator_pss<eint, efpt64>(cA, cB));
                c_event.y(cy / denom);
            }

            if (recompute_c_x || recompute_lower_x) {
                cA[0] = a[1] * (dx * dx + dy * dy) - ix * (dx * a[1] + dy * b[1]);
                cA[1] = a[0] * (dx * dx + dy * dy) - ix * (dx * a[0] + dy * b[0]);
                cA[2] = ix * sign;

                if (recompute_c_x) {
                    fpt_type cx = get_d(sqrt_expr_evaluator_pss<eint, efpt64>(cA, cB));
                    c_event.x(cx / denom);
                }

                if (recompute_lower_x) {
                    cA[3] = orientation * (dx * dx + dy * dy) * (temp < 0 ? -1 : 1);
                    fpt_type lower_x = get_d(sqrt_expr_evaluator_pss<eint, efpt64>(cA, cB));
                    c_event.lower_x(lower_x / denom);
                }
            }
        }

        // Recompute parameters of the circle event using high-precision library.
        void sss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef eint4096 eint;
            eint a[3], b[3], c[3], cA[4], cB[4];
            // cA - corresponds to the cross product.
            // cB - corresponds to the squared length.
            a[0] = static_cast<int64>(site1.x1(true)) -
                   static_cast<int64>(site1.x0(true));
            a[1] = static_cast<int64>(site2.x1(true)) -
                   static_cast<int64>(site2.x0(true));
            a[2] = static_cast<int64>(site3.x1(true)) -
                   static_cast<int64>(site3.x0(true));

            b[0] = static_cast<int64>(site1.y1(true)) -
                   static_cast<int64>(site1.y0(true));
            b[1] = static_cast<int64>(site2.y1(true)) -
                   static_cast<int64>(site2.y0(true));
            b[2] = static_cast<int64>(site3.y1(true)) -
                   static_cast<int64>(site3.y0(true));

            c[0] = static_cast<int64>(site1.x0(true)) * static_cast<int64>(site1.y1(true)) -
                   static_cast<int64>(site1.y0(true)) * static_cast<int64>(site1.x1(true));
            c[1] = static_cast<int64>(site2.x0(true)) * static_cast<int64>(site2.y1(true)) -
                   static_cast<int64>(site2.y0(true)) * static_cast<int64>(site2.x1(true));
            c[2] = static_cast<int64>(site3.x0(true)) * static_cast<int64>(site3.y1(true)) -
                   static_cast<int64>(site3.y0(true)) * static_cast<int64>(site3.x1(true));

            for (int i = 0; i < 3; ++i) {
                cB[i] = a[i] * a[i] + b[i] * b[i];
            }

            for (int i = 0; i < 3; ++i) {
                int j = (i+1) % 3;
                int k = (i+2) % 3;
                cA[i] = a[j] * b[k] - a[k] * b[j];
            }
            fpt_type denom = get_d(sqrt_expr_.eval3(cA, cB));

            if (recompute_c_y) {
                for (int i = 0; i < 3; ++i) {
                    int j = (i+1) % 3;
                    int k = (i+2) % 3;
                    cA[i] = b[j] * c[k] - b[k] * c[j];
                }
                fpt_type c_y = get_d(sqrt_expr_.eval3(cA, cB));
                c_event.y(c_y / denom);
            }

            if (recompute_c_x || recompute_lower_x) {
                cA[3] = 0;
                for (int i = 0; i < 3; ++i) {
                    int j = (i+1) % 3;
                    int k = (i+2) % 3;
                    cA[i] = a[j] * c[k] - a[k] * c[j];
                    if (recompute_lower_x) {
                        cA[3] = cA[3] + cA[i] * b[i];
                    }
                }

                if (recompute_c_x) {
                    fpt_type c_x = get_d(sqrt_expr_.eval3(cA, cB));
                    c_event.x(c_x / denom);
                }

                if (recompute_lower_x) {
                    cB[3] = 1;
                    fpt_type lower_x = get_d(sqrt_expr_.eval4(cA, cB));
                    c_event.lower_x(lower_x / denom);
                }
            }
        }

    private:
        // Evaluates A[3] + A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
        //           A[2] * sqrt(B[3] * (sqrt(B[0] * B[1]) + B[2]));
        template <typename _int, typename _fpt>
        _fpt sqrt_expr_evaluator_pss(_int *A, _int *B) {
            _int cA[4], cB[4];
            if (is_zero(A[3])) {
                _fpt lh = sqrt_expr_.eval2(A, B);
                cA[0] = 1;
                cB[0] = B[0] * B[1];
                cA[1] = B[2];
                cB[1] = 1;
                _fpt rh = sqrt_expr_.eval1(A+2, B+3) * get_sqrt(sqrt_expr_.eval2(cA, cB));
                if ((!is_neg(lh) && !is_neg(rh)) || (!is_pos(lh) && !is_pos(rh))) {
                    return lh + rh;
                }
                cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
                        A[2] * A[2] * B[3] * B[2];
                cB[0] = 1;
                cA[1] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
                cB[1] = B[0] * B[1];
                _fpt numer = sqrt_expr_.eval2(cA, cB);
                return numer / (lh - rh);
            }
            cA[0] = A[3];
            cB[0] = 1;
            cA[1] = A[0];
            cB[1] = B[0];
            cA[2] = A[1];
            cB[2] = B[1];
            _fpt lh = sqrt_expr_.eval3(cA, cB);
            cA[0] = 1;
            cB[0] = B[0] * B[1];
            cA[1] = B[2];
            cB[1] = 1;
            _fpt rh = sqrt_expr_.eval1(A+2, B+3) * get_sqrt(sqrt_expr_.eval2(cA, cB));
            if ((!is_neg(lh) && !is_neg(rh)) || (!is_pos(lh) && !is_pos(rh))) {
                return lh + rh;
            }
            cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] +
                    A[3] * A[3] - A[2] * A[2] * B[2] * B[3];
            cB[0] = 1;
            cA[1] = A[3] * A[0] * 2;
            cB[1] = B[0];
            cA[2] = A[3] * A[1] * 2;
            cB[2] = B[1];
            cA[3] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
            cB[3] = B[0] * B[1];
            _fpt numer = sqrt_expr_.eval4(cA, cB);
            return numer / (lh - rh);
        }

        robust_sqrt_expr_type sqrt_expr_;
    };

    template <typename Site, typename Circle>
    class lazy_circle_formation_functor {
    public:
        typedef robust_fpt<fpt_type> robust_fpt_type;
        typedef robust_dif<robust_fpt_type> robust_dif_type;
        typedef typename Site::point_type point_type;
        typedef Site site_type;
        typedef Circle circle_type;
        typedef mp_circle_formation_functor<site_type, circle_type>
            exact_circle_formation_functor_type;

        void ppp(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event) {
            fpt_type dif_x1 = static_cast<fpt_type>(site1.x()) -
                              static_cast<fpt_type>(site2.x());
            fpt_type dif_x2 = static_cast<fpt_type>(site2.x()) -
                              static_cast<fpt_type>(site3.x());
            fpt_type dif_y1 = static_cast<fpt_type>(site1.y()) -
                              static_cast<fpt_type>(site2.y());
            fpt_type dif_y2 = static_cast<fpt_type>(site2.y()) -
                              static_cast<fpt_type>(site3.y());
            fpt_type orientation = robust_cross_product(dif_x1, dif_y1, dif_x2, dif_y2);
            robust_fpt_type inv_orientation(0.5 / orientation, 2.0);
            fpt_type sum_x1 = static_cast<fpt_type>(site1.x()) +
                              static_cast<fpt_type>(site2.x());
            fpt_type sum_x2 = static_cast<fpt_type>(site2.x()) +
                              static_cast<fpt_type>(site3.x());
            fpt_type sum_y1 = static_cast<fpt_type>(site1.y()) +
                              static_cast<fpt_type>(site2.y());
            fpt_type sum_y2 = static_cast<fpt_type>(site2.y()) +
                              static_cast<fpt_type>(site3.y());
            fpt_type dif_x3 = static_cast<fpt_type>(site1.x()) -
                              static_cast<fpt_type>(site3.x());
            fpt_type dif_y3 = static_cast<fpt_type>(site1.y()) -
                              static_cast<fpt_type>(site3.y());
            robust_dif_type c_x, c_y;
            c_x += robust_fpt_type(dif_x1 * sum_x1 * dif_y2, 2.0);
            c_x += robust_fpt_type(dif_y1 * sum_y1 * dif_y2, 2.0);
            c_x -= robust_fpt_type(dif_x2 * sum_x2 * dif_y1, 2.0);
            c_x -= robust_fpt_type(dif_y2 * sum_y2 * dif_y1, 2.0);
            c_y += robust_fpt_type(dif_x2 * sum_x2 * dif_x1, 2.0);
            c_y += robust_fpt_type(dif_y2 * sum_y2 * dif_x1, 2.0);
            c_y -= robust_fpt_type(dif_x1 * sum_x1 * dif_x2, 2.0);
            c_y -= robust_fpt_type(dif_y1 * sum_y1 * dif_x2, 2.0);
            robust_dif_type lower_x(c_x);
            lower_x -= robust_fpt_type(std::sqrt(sqr_distance(dif_x1, dif_y1) *
                                                 sqr_distance(dif_x2, dif_y2) *
                                                 sqr_distance(dif_x3, dif_y3)), 5.0);
            c_event = circle_type(c_x.dif().fpv() * inv_orientation.fpv(),
                                  c_y.dif().fpv() * inv_orientation.fpv(),
                                  lower_x.dif().fpv() * inv_orientation.fpv());
            bool recompute_c_x = c_x.dif().ulp() > fULPS;
            bool recompute_c_y = c_y.dif().ulp() > fULPS;
            bool recompute_lower_x = lower_x.dif().ulp() > fULPS;
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                exact_circle_formation_functor_.ppp(
                    site1, site2, site3, c_event, recompute_c_x, recompute_c_y, recompute_lower_x);
            }
        }

        void pps(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int segment_index,
                 circle_type &c_event) {
            fpt_type line_a = static_cast<fpt_type>(site3.point1(true).y()) -
                              static_cast<fpt_type>(site3.point0(true).y());
            fpt_type line_b = static_cast<fpt_type>(site3.point0(true).x()) -
                              static_cast<fpt_type>(site3.point1(true).x());
            fpt_type vec_x = static_cast<fpt_type>(site2.y()) -
                             static_cast<fpt_type>(site1.y());
            fpt_type vec_y = static_cast<fpt_type>(site1.x()) -
                             static_cast<fpt_type>(site2.x());
            robust_fpt_type teta(robust_cross_product(line_a, line_b, -vec_y, vec_x), 1.0);
            robust_fpt_type A(robust_cross_product(line_a, line_b,
                                                   static_cast<fpt_type>(site3.point1().y()) -
                                                   static_cast<fpt_type>(site1.y()),
                                                   static_cast<fpt_type>(site1.x()) -
                                                   static_cast<fpt_type>(site3.point1().x())), 1.0);
            robust_fpt_type B(robust_cross_product(line_a, line_b,
                                                   static_cast<fpt_type>(site3.point1().y()) -
                                                   static_cast<fpt_type>(site2.y()),
                                                   static_cast<fpt_type>(site2.x()) -
                                                   static_cast<fpt_type>(site3.point1().x())), 1.0);
            robust_fpt_type denom(robust_cross_product(vec_x, vec_y, line_a, line_b), 1.0);
            robust_fpt_type inv_segm_len(1.0 / std::sqrt(sqr_distance(line_a, line_b)), 3.0);
            robust_dif_type t;
            if (get_orientation(denom) == COLLINEAR) {
                t += teta / (robust_fpt_type(8.0, false) * A);
                t -= A / (robust_fpt_type(2.0, false) * teta);
            } else {
                robust_fpt_type det = ((teta * teta + denom * denom) * A * B).sqrt();
                if (segment_index == 2) {
                    t -= det / (denom * denom);
                } else {
                    t += det / (denom * denom);
                }
                t += teta * (A + B) / (robust_fpt_type(2.0, false) * denom * denom);
            }
            robust_dif_type c_x, c_y;
            c_x += robust_fpt_type(0.5 * (
                static_cast<fpt_type>(site1.x()) +
                static_cast<fpt_type>(site2.x())), false);
            c_x += robust_fpt_type(vec_x, false) * t;
            c_y += robust_fpt_type(0.5 * (
                static_cast<fpt_type>(site1.y()) +
                static_cast<fpt_type>(site2.y())), false);
            c_y += robust_fpt_type(vec_y, false) * t;
            robust_dif_type r, lower_x(c_x);
            r -= robust_fpt_type(line_a, false) * robust_fpt_type(site3.x0(), false);
            r -= robust_fpt_type(line_b, false) * robust_fpt_type(site3.y0(), false);
            r += robust_fpt_type(line_a, false) * c_x;
            r += robust_fpt_type(line_b, false) * c_y;
            r.abs();
            lower_x += r * inv_segm_len;
            c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            bool recompute_c_x = c_x.dif().ulp() > fULPS;
            bool recompute_c_y = c_y.dif().ulp() > fULPS;
            bool recompute_lower_x = lower_x.dif().ulp() > fULPS;
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                exact_circle_formation_functor_.pps(
                    site1, site2, site3, segment_index, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
        }

        void pss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int point_index,
                 circle_type &c_event) {
            const point_type &segm_start1 = site2.point1(true);
            const point_type &segm_end1 = site2.point0(true);
            const point_type &segm_start2 = site3.point0(true);
            const point_type &segm_end2 = site3.point1(true);
            fpt_type a1 = static_cast<fpt_type>(segm_end1.x()) -
                          static_cast<fpt_type>(segm_start1.x());
            fpt_type b1 = static_cast<fpt_type>(segm_end1.y()) -
                          static_cast<fpt_type>(segm_start1.y());
            fpt_type a2 = static_cast<fpt_type>(segm_end2.x()) -
                          static_cast<fpt_type>(segm_start2.x());
            fpt_type b2 = static_cast<fpt_type>(segm_end2.y()) -
                          static_cast<fpt_type>(segm_start2.y());
            bool recompute_c_x, recompute_c_y, recompute_lower_x;
            robust_fpt_type orientation(robust_cross_product(b1, a1, b2, a2), 1.0);
            if (get_orientation(orientation) == COLLINEAR) {
                robust_fpt_type a(a1 * a1 + b1 * b1, 2.0);
                robust_fpt_type c(robust_cross_product(b1, a1,
                                                       static_cast<fpt_type>(segm_start2.y()) -
                                                       static_cast<fpt_type>(segm_start1.y()),
                                                       static_cast<fpt_type>(segm_start2.x()) -
                                                       static_cast<fpt_type>(segm_start1.x())), 1.0);
                robust_fpt_type det(robust_cross_product(a1, b1,
                                                         static_cast<fpt_type>(site1.x()) -
                                                         static_cast<fpt_type>(segm_start1.x()),
                                                         static_cast<fpt_type>(site1.y()) -
                                                         static_cast<fpt_type>(segm_start1.y())) *
                                    robust_cross_product(b1, a1,
                                                         static_cast<fpt_type>(site1.y()) -
                                                         static_cast<fpt_type>(segm_start2.y()),
                                                         static_cast<fpt_type>(site1.x()) -
                                                         static_cast<fpt_type>(segm_start2.x())), 3.0);
                robust_dif_type t;
                t -= robust_fpt_type(a1, false) * robust_fpt_type(
                    (static_cast<fpt_type>(segm_start1.x()) +
                     static_cast<fpt_type>(segm_start2.x())) * 0.5 -
                     static_cast<fpt_type>(site1.x()), false);
                t -= robust_fpt_type(b1, false) * robust_fpt_type((
                     static_cast<fpt_type>(segm_start1.y()) +
                     static_cast<fpt_type>(segm_start2.y())) * 0.5 -
                     static_cast<fpt_type>(site1.y()), false);
                if (point_index == 2) {
                    t += det.sqrt();
                } else {
                    t -= det.sqrt();
                }
                t /= a;
                robust_dif_type c_x, c_y;
                c_x += robust_fpt_type(0.5 * (
                    static_cast<fpt_type>(segm_start1.x()) +
                    static_cast<fpt_type>(segm_start2.x())), false);
                c_x += robust_fpt_type(a1, false) * t;
                c_y += robust_fpt_type(0.5 * (
                    static_cast<fpt_type>(segm_start1.y()) +
                    static_cast<fpt_type>(segm_start2.y())), false);
                c_y += robust_fpt_type(b1, false) * t;
                robust_dif_type lower_x(c_x);
                lower_x += robust_fpt_type(0.5, false) * c.fabs() / a.sqrt();
                recompute_c_x = c_x.dif().ulp() > fULPS;
                recompute_c_y = c_y.dif().ulp() > fULPS;
                recompute_lower_x = lower_x.dif().ulp() > fULPS;
                c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            } else {
                robust_fpt_type sqr_sum1(std::sqrt(a1 * a1 + b1 * b1), 2.0);
                robust_fpt_type sqr_sum2(std::sqrt(a2 * a2 + b2 * b2), 2.0);
                robust_fpt_type a(robust_cross_product(a1, b1, -b2, a2), 1.0);
                if (a >= 0) {
                    a += sqr_sum1 * sqr_sum2;
                } else {
                    a = (orientation * orientation) / (sqr_sum1 * sqr_sum2 - a);
                }
                robust_fpt_type or1(robust_cross_product(b1, a1,
                                                         static_cast<fpt_type>(segm_end1.y()) -
                                                         static_cast<fpt_type>(site1.y()),
                                                         static_cast<fpt_type>(segm_end1.x()) -
                                                         static_cast<fpt_type>(site1.x())), 1.0);
                robust_fpt_type or2(robust_cross_product(a2, b2,
                                                         static_cast<fpt_type>(segm_end2.x()) -
                                                         static_cast<fpt_type>(site1.x()),
                                                         static_cast<fpt_type>(segm_end2.y()) -
                                                         static_cast<fpt_type>(site1.y())), 1.0);
                robust_fpt_type det = robust_fpt_type(2.0, false) * a * or1 * or2;
                robust_fpt_type c1(robust_cross_product(b1, a1,
                                                        static_cast<fpt_type>(segm_end1.y()),
                                                        static_cast<fpt_type>(segm_end1.x())), 1.0);
                robust_fpt_type c2(robust_cross_product(a2, b2,
                                                        static_cast<fpt_type>(segm_end2.x()),
                                                        static_cast<fpt_type>(segm_end2.y())), 1.0);
                robust_fpt_type inv_orientation = robust_fpt_type(1.0, false) / orientation;
                robust_dif_type t, b, ix, iy;
                ix += robust_fpt_type(a2, false) * c1 * inv_orientation;
                ix += robust_fpt_type(a1, false) * c2 * inv_orientation;
                iy += robust_fpt_type(b1, false) * c2 * inv_orientation;
                iy += robust_fpt_type(b2, false) * c1 * inv_orientation;

                b += ix * (robust_fpt_type(a1, false) * sqr_sum2);
                b += ix * (robust_fpt_type(a2, false) * sqr_sum1);
                b += iy * (robust_fpt_type(b1, false) * sqr_sum2);
                b += iy * (robust_fpt_type(b2, false) * sqr_sum1);
                b -= sqr_sum1 * robust_fpt_type(robust_cross_product(a2, b2,
                                                                     static_cast<fpt_type>(-site1.y()),
                                                                     static_cast<fpt_type>(site1.x())), 1.0);
                b -= sqr_sum2 * robust_fpt_type(robust_cross_product(a1, b1,
                                                                     static_cast<fpt_type>(-site1.y()),
                                                                     static_cast<fpt_type>(site1.x())), 1.0);
                t -= b;
                if (point_index == 2) {
                    t += det.sqrt();
                } else {
                    t -= det.sqrt();
                }
                t /= (a * a);
                robust_dif_type c_x(ix), c_y(iy);
                c_x += t * (robust_fpt_type(a1, false) * sqr_sum2);
                c_x += t * (robust_fpt_type(a2, false) * sqr_sum1);
                c_y += t * (robust_fpt_type(b1, false) * sqr_sum2);
                c_y += t * (robust_fpt_type(b2, false) * sqr_sum1);
                t.abs();
                robust_dif_type lower_x(c_x);
                lower_x += t * orientation.fabs();
                recompute_c_x = c_x.dif().ulp() > fULPS;
                recompute_c_y = c_y.dif().ulp() > fULPS;
                recompute_lower_x = lower_x.dif().ulp() > fULPS;
                c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            }
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                exact_circle_formation_functor_.pss(
                    site1, site2, site3, point_index, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
        }

        void sss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event) {
            robust_fpt_type a1(static_cast<fpt_type>(site1.x1(true)) -
                               static_cast<fpt_type>(site1.x0(true)), 0.0);
            robust_fpt_type b1(static_cast<fpt_type>(site1.y1(true)) -
                               static_cast<fpt_type>(site1.y0(true)), 0.0);
            robust_fpt_type c1(robust_cross_product(site1.x0(true), site1.y0(true), site1.x1(true), site1.y1(true)), 1.0);

            robust_fpt_type a2(static_cast<fpt_type>(site2.x1(true)) -
                               static_cast<fpt_type>(site2.x0(true)), 0.0);
            robust_fpt_type b2(static_cast<fpt_type>(site2.y1(true)) -
                               static_cast<fpt_type>(site2.y0(true)), 0.0);
            robust_fpt_type c2(robust_cross_product(site2.x0(true), site2.y0(true), site2.x1(true), site2.y1(true)), 1.0);

            robust_fpt_type a3(static_cast<fpt_type>(site3.x1(true)) -
                               static_cast<fpt_type>(site3.x0(true)), 0.0);
            robust_fpt_type b3(static_cast<fpt_type>(site3.y1(true)) -
                               static_cast<fpt_type>(site3.y0(true)), 0.0);
            robust_fpt_type c3(robust_cross_product(site3.x0(true), site3.y0(true), site3.x1(true), site3.y1(true)), 1.0);

            robust_fpt_type len1 = (a1 * a1 + b1 * b1).sqrt();
            robust_fpt_type len2 = (a2 * a2 + b2 * b2).sqrt();
            robust_fpt_type len3 = (a3 * a3 + b3 * b3).sqrt();
            robust_fpt_type cross_12(robust_cross_product(a1.fpv(), b1.fpv(), a2.fpv(), b2.fpv()), 1.0);
            robust_fpt_type cross_23(robust_cross_product(a2.fpv(), b2.fpv(), a3.fpv(), b3.fpv()), 1.0);
            robust_fpt_type cross_31(robust_cross_product(a3.fpv(), b3.fpv(), a1.fpv(), b1.fpv()), 1.0);
            robust_dif_type denom, c_x, c_y, r;

            // denom = cross_12 * len3 + cross_23 * len1 + cross_31 * len2.
            denom += cross_12 * len3;
            denom += cross_23 * len1;
            denom += cross_31 * len2;

            // denom * r = (b2 * c_x - a2 * c_y - c2 * denom) / len2.
            r -= cross_12 * c3;
            r -= cross_23 * c1;
            r -= cross_31 * c2;

            c_x += a1 * c2 * len3;
            c_x -= a2 * c1 * len3;
            c_x += a2 * c3 * len1;
            c_x -= a3 * c2 * len1;
            c_x += a3 * c1 * len2;
            c_x -= a1 * c3 * len2;
            c_y += b1 * c2 * len3;
            c_y -= b2 * c1 * len3;
            c_y += b2 * c3 * len1;
            c_y -= b3 * c2 * len1;
            c_y += b3 * c1 * len2;
            c_y -= b1 * c3 * len2;
            robust_dif_type lower_x(c_x + r);
            bool recompute_c_x = c_x.dif().ulp() > fULPS;
            bool recompute_c_y = c_y.dif().ulp() > fULPS;
            bool recompute_lower_x = lower_x.dif().ulp() > fULPS;
            bool recompute_denom = denom.dif().ulp() > fULPS;
            c_event = circle_type(c_x.dif().fpv() / denom.dif().fpv(),
                                  c_y.dif().fpv() / denom.dif().fpv(),
                                  lower_x.dif().fpv() / denom.dif().fpv());
            if (recompute_c_x || recompute_c_y || recompute_lower_x || recompute_denom) {
                exact_circle_formation_functor_.sss(
                    site1, site2, site3, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
        }

    private:
        exact_circle_formation_functor_type exact_circle_formation_functor_;
    };

    template <typename Site,
              typename Circle,
              typename CEP = circle_existence_predicate<Site>,
              typename CFF = lazy_circle_formation_functor<Site, Circle> >
    class circle_formation_predicate {
    public:
        typedef Site site_type;
        typedef Circle circle_type;
        typedef CEP circle_existence_predicate_type;
        typedef CFF circle_formation_functor_type;

        // Create a circle event from the given three sites.
        // Returns true if the circle event exists, else false.
        // If exists circle event is saved into the c_event variable.
        bool operator()(const site_type &site1, const site_type &site2,
                        const site_type &site3, circle_type &circle) {
            if (!site1.is_segment()) {
                if (!site2.is_segment()) {
                    if (!site3.is_segment()) {
                        // (point, point, point) sites.
                        if (!circle_existence_predicate_.ppp(site1, site2, site3))
                            return false;
                        circle_formation_functor_.ppp(site1, site2, site3, circle);
                    } else {
                        // (point, point, segment) sites.
                        if (!circle_existence_predicate_.pps(site1, site2, site3, 3))
                            return false;
                        circle_formation_functor_.pps(site1, site2, site3, 3, circle);
                    }
                } else {
                    if (!site3.is_segment()) {
                        // (point, segment, point) sites.
                        if (!circle_existence_predicate_.pps(site1, site3, site2, 2))
                            return false;
                        circle_formation_functor_.pps(site1, site3, site2, 2, circle);
                    } else {
                        // (point, segment, segment) sites.
                        if (!circle_existence_predicate_.pss(site1, site2, site3, 1))
                            return false;
                        circle_formation_functor_.pss(site1, site2, site3, 1, circle);
                    }
                }
            } else {
                if (!site2.is_segment()) {
                    if (!site3.is_segment()) {
                        // (segment, point, point) sites.
                        if (!circle_existence_predicate_.pps(site2, site3, site1, 1))
                            return false;
                        circle_formation_functor_.pps(site2, site3, site1, 1, circle);
                    } else {
                        // (segment, point, segment) sites.
                        if (!circle_existence_predicate_.pss(site2, site1, site3, 2))
                            return false;
                        circle_formation_functor_.pss(site2, site1, site3, 2, circle);
                    }
                } else {
                    if (!site3.is_segment()) {
                        // (segment, segment, point) sites.
                        if (!circle_existence_predicate_.pss(site3, site1, site2, 3))
                            return false;
                        circle_formation_functor_.pss(site3, site1, site2, 3, circle);
                    } else {
                        // (segment, segment, segment) sites.
                        if (!circle_existence_predicate_.sss(site1, site2, site3))
                            return false;
                        circle_formation_functor_.sss(site1, site2, site3, circle);
                    }
                }
            }
            return true;
        }
    private:
        circle_existence_predicate_type circle_existence_predicate_;
        circle_formation_functor_type circle_formation_functor_;
    };

private:
    // Convert value to 64-bit unsigned integer.
    // Return true if the value is positive, else false.
    template <typename T>
    static bool convert_to_65_bit(T value, uint64 &res) {
        if (value >= static_cast<T>(0)) {
            res = static_cast<uint64>(value);
            return true;
        } else {
            res = static_cast<uint64>(-value);
            return false;
        }
    }

    template <typename T>
    static T sqr_value(T value) {
        return value * value;
    }

    template <typename T>
    static T sqr_distance(T dif_x, T dif_y) {
        return dif_x * dif_x + dif_y * dif_y;
    }
};

const uint32 voronoi_calc_utils<int>::ULPS = 64;
const uint32 voronoi_calc_utils<int>::ULPSx2 = 128;
const voronoi_calc_utils<int>::fpt_type voronoi_calc_utils<int>::fULPS =
    voronoi_calc_utils<int>::ULPS;
const voronoi_calc_utils<int>::fpt_type voronoi_calc_utils<int>::fULPSx2 =
    voronoi_calc_utils<int>::ULPSx2;

} // detail
} // polygon
} // boost

#endif
