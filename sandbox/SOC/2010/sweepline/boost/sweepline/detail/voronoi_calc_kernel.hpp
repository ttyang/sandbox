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

// Geometry predicates with floating-point variables usually require
// high-precision predicates to retrieve the correct result.
// Epsilon robust predicates give the result within some epsilon relative
// error, but are a lot faster than high-precision predicates.
// To make algorithm robust and efficient epsilon robust predicates are
// used at the first step. In case of the undefined result high-precision
// arithmetic is used to produce required robustness. This approach
// requires exact computation of epsilon intervals within which epsilon
// robust predicates have undefined value.
// There are two ways to measure an error of floating-point calculations:
// relative error and ULPs(units in the last place).
// Let EPS be machine epsilon, then next inequalities have place:
// 1 EPS <= 1 ULP <= 2 EPS (1), 0.5 ULP <= 1 EPS <= 1 ULP (2).
// ULPs are good for measuring rounding errors and comparing values.
// Relative erros are good for computation of general relative
// errors of formulas or expressions. So to calculate epsilon
// intervals within which epsilon robust predicates have undefined result
// next schema is used:
//     1) Compute rounding errors of initial variables using ULPs;
//     2) Transform ULPs to epsilons using upper bound of the (1);
//     3) Compute relative error of the formula using epsilon arithmetic;
//     4) Transform epsilon to ULPs using upper bound of the (2);
// In case two values are inside undefined ULP range use high-precision
// arithmetic to produce the correct result, else output the result.
// Look at almost_equal function to see how two floating-point variables
// are checked to fit in the ULP range.
// If A has relative error of r(A) and B has relative error of r(B) then:
//     1) r(A + B) <= max(r(A), r(B)), for A * B >= 0;
//     2) r(A - B) <= B*r(A)+A*r(B)/(A-B), for A * B >= 0;
//     2) r(A * B) <= r(A) + r(B);
//     3) r(A / B) <= r(A) + r(B);
// In addition rounding error should be added, that is always equal to
// 0.5 ULP or atmost 1 epsilon. As you might see from the above formulas
// substraction relative error may be extremely large, that's why
// epsilon robust comparator class is used to store floating point values
// and avoid substraction.
// For further information about relative errors and ULPs try this link:
// http://docs.sun.com/source/806-3568/ncg_goldberg.html
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
        typedef typename Site::point_type point_type;
        typedef Site site_type;
        
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
                return left_point.y() + right_point.y() < 2.0 * new_point.y();
            }

            fpt_type dist1 = find_distance_to_point_arc(left_site, new_point);
            fpt_type dist2 = find_distance_to_point_arc(right_site, new_point);

            // The undefined ulp range is equal to 3EPS + 3EPS <= 6ULP.
            return dist1 < dist2;
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

    private:
        // Find the x-coordinate (relative to the sweepline position) of the point
        // of the intersection of the horizontal line going through the new site
        // with the arc corresponding to the point site.
        // The relative error is atmost 3EPS.
        fpt_type find_distance_to_point_arc(const site_type &site,
                                            const point_type &point) const {
            fpt_type dx = site.x() - point.x();
            fpt_type dy = site.y() - point.y();
            return (dx * dx + dy * dy) / (2.0 * dx);
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
                fpt_type a1 = segment1.x() - segment0.x();
                fpt_type b1 = segment1.y() - segment0.y();
                fpt_type a3 = point.x() - segment0.x();
                fpt_type b3 = point.y() - segment0.y();
                fpt_type k = std::sqrt(a1 * a1 + b1 * b1);
                // Avoid substraction while computing k.
                if (b1 >= 0.0) k = 1.0 / (b1 + k);
                else k = (k - b1) / (a1 * a1);
                // Relative error of the robust cross product is 2EPS.
                // Relative error of the k is atmost 5EPS.
                // The resulting relative error is atmost 8EPS.
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

            fpt_type dif_x = new_point.x() - site_point.x();
            fpt_type dif_y = new_point.y() - site_point.y();
            fpt_type a = segment_end.x() - segment_start.x();
            fpt_type b = segment_end.y() - segment_start.y();

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
    };

    template <typename Node>
    class node_comparison_predicate {
    public:
        typedef Node node_type;
        typedef typename Node::coordinate_type coordinate_type;
        typedef typename Node::site_event_type site_type;
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
                return less(node1.left_site(), node1.right_site(), site2);
            } else if (site1.x() > site2.x()) {
                // The first node contains a new site.
                return !less(node2.left_site(), node2.right_site(), site1);
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

        bool less(const site_type& left_site,
                  const site_type& right_site,
                  const site_type& new_site) const {
            if (!left_site.is_segment()) {
                if (!right_site.is_segment()) {
                    return predicate_.pp(left_site, right_site, new_site);
                } else {
                    return predicate_.ps(left_site, right_site, new_site, false);
                }
            } else {
                if (!right_site.is_segment()) {
                    return predicate_.ps(right_site, left_site, new_site, true);
                } else {
                    return predicate_.ss(left_site, right_site, new_site);
                }
            }
        }

    private:
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
            if (site2.index() == site3.index()) {
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
             if (site1.index() == site2.index())
                 return false;
             if (site2.index() == site3.index())
                 return false;
             return true;
        }
    };

    template <typename Site, typename Circle>
    class gmp_circle_formation_functor {
    public:
        typedef typename Site::point_type point_type;
        typedef Site site_type;
        typedef Circle circle_type;

        bool ppp(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &circle,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef mpt_wrapper<mpz_class, 8> mpt_type;
            static mpt_type mpz_dif_x[3], mpz_dif_y[3], mpz_sum_x[2], mpz_sum_y[2],
                            mpz_numerator[3], mpz_c_x, mpz_c_y, mpz_sqr_r, denom,
                            cA[2], cB[2];
            mpz_dif_x[0] = static_cast<double>(site1.x()) - static_cast<double>(site2.x());
            mpz_dif_x[1] = static_cast<double>(site2.x()) - static_cast<double>(site3.x());
            mpz_dif_x[2] = static_cast<double>(site1.x()) - static_cast<double>(site3.x());
            mpz_dif_y[0] = static_cast<double>(site1.y()) - static_cast<double>(site2.y());
            mpz_dif_y[1] = static_cast<double>(site2.y()) - static_cast<double>(site3.y());
            mpz_dif_y[2] = static_cast<double>(site1.y()) - static_cast<double>(site3.y());
            denom = (mpz_dif_x[0] * mpz_dif_y[1] - mpz_dif_x[1] * mpz_dif_y[0]) * 2.0;
            mpz_sum_x[0] = static_cast<double>(site1.x()) + static_cast<double>(site2.x());
            mpz_sum_x[1] = static_cast<double>(site2.x()) + static_cast<double>(site3.x());
            mpz_sum_y[0] = static_cast<double>(site1.y()) + static_cast<double>(site2.y());
            mpz_sum_y[1] = static_cast<double>(site2.y()) + static_cast<double>(site3.y());
        
            mpz_numerator[1] = mpz_dif_x[0] * mpz_sum_x[0] + mpz_dif_y[0] * mpz_sum_y[0];
            mpz_numerator[2] = mpz_dif_x[1] * mpz_sum_x[1] + mpz_dif_y[1] * mpz_sum_y[1];

            if (recompute_c_x || recompute_lower_x) {
                mpz_c_x = mpz_numerator[1] * mpz_dif_y[1] - mpz_numerator[2] * mpz_dif_y[0];
                circle.x(mpz_c_x.get_d() / denom.get_d());

                if (recompute_lower_x) {
                    // Evaluate radius of the circle.
                    mpz_sqr_r = 1.0;
                    for (int i = 0; i < 3; ++i)
                        mpz_sqr_r *= mpz_dif_x[i] * mpz_dif_x[i] + mpz_dif_y[i] * mpz_dif_y[i];
                    double r = std::sqrt(mpz_sqr_r.get_d());

                    // If c_x >= 0 then lower_x = c_x + r,
                    // else lower_x = (c_x * c_x - r * r) / (c_x - r).
                    // To guarantee epsilon relative error.
                    if (circle.x() >= 0) {
                        circle.lower_x(circle.x() + r / fabs(denom.get_d()));
                    } else {
                        mpz_numerator[0] = mpz_c_x * mpz_c_x - mpz_sqr_r;
                        double lower_x = mpz_numerator[0].get_d() /
                                         (denom.get_d() * (mpz_c_x.get_d() + r));
                        circle.lower_x(lower_x);
                    }
                }
            }

            if (recompute_c_y) {
                mpz_c_y = mpz_numerator[2] * mpz_dif_x[0] - mpz_numerator[1] * mpz_dif_x[1];
                circle.y(mpz_c_y.get_d() / denom.get_d());
            }

            return true;
        }

        // Recompute parameters of the circle event using high-precision library.
        bool pps(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int segment_index,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef mpt_wrapper<mpz_class, 8> mpt_type;
            typedef mpt_wrapper<mpf_class, 2> mpf_type;
            static mpt_type line_a, line_b, segm_len, vec_x, vec_y, sum_x, sum_y, teta,
                            denom, A, B, sum_AB, dif[2], numer, cA[4], cB[4], det;

            line_a = site3.point1(true).y() - site3.point0(true).y();
            line_b = site3.point0(true).x() - site3.point1(true).x();
            segm_len = line_a * line_a + line_b * line_b;
            vec_x = site2.y() - site1.y();
            vec_y = site1.x() - site2.x();
            sum_x = site1.x() + site2.x();
            sum_y = site1.y() + site2.y();
            teta = line_a * vec_x + line_b * vec_y;
            denom = vec_x * line_b - vec_y * line_a;
            
            dif[0] = site3.point1().y() - site1.y();
            dif[1] = site1.x() - site3.point1().x();
            A = line_a * dif[1] - line_b * dif[0];
            dif[0] = site3.point1().y() - site2.y();
            dif[1] = site2.x() - site3.point1().x();
            B = line_a * dif[1] - line_b * dif[0];
            sum_AB = A + B;

            if (denom == 0) {
                numer = teta * teta - sum_AB * sum_AB;
                denom = teta * sum_AB;
                cA[0] = denom * sum_x * 2 + numer * vec_x;
                cB[0] = segm_len;
                cA[1] = denom * sum_AB * 2 + numer * teta;
                cB[1] = 1;
                cA[2] = denom * sum_y * 2 + numer * vec_y;
                if (recompute_c_x) {
                    c_event.x(0.25 * cA[0].get_d() / denom.get_d());
                }
                if (recompute_c_y) {
                    c_event.y(0.25 * cA[2].get_d() / denom.get_d());
                }
                if (recompute_lower_x) {
                    c_event.lower_x(0.25 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                                    (denom.get_d() * std::sqrt(segm_len.get_d())));
                }
                return true;
            }

            det = (teta * teta + denom * denom) * A * B * 4;
            double denom_sqr = denom.get_d() * denom.get_d();

            if (recompute_c_x || recompute_lower_x) {
                cA[0] = sum_x * denom * denom + teta * sum_AB * vec_x;
                cB[0] = 1;
                cA[1] = (segment_index == 2) ? -vec_x : vec_x;
                cB[1] = det;
                if (recompute_c_x) {
                    c_event.x(0.5 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                              denom_sqr);
                }
            }
            
            if (recompute_c_y || recompute_lower_x) {
                cA[2] = sum_y * denom * denom + teta * sum_AB * vec_y;
                cB[2] = 1;
                cA[3] = (segment_index == 2) ? -vec_y : vec_y;
                cB[3] = det;
                if (recompute_c_y) {
                    c_event.y(0.5 * sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(&cA[2], &cB[2]).get_d() /
                              denom_sqr);
                }
            }
            
            if (recompute_lower_x) {
                cB[0] *= segm_len;
                cB[1] *= segm_len;
                cA[2] = sum_AB * (denom * denom + teta * teta);
                cB[2] = 1;
                cA[3] = (segment_index == 2) ? -teta : teta;
                cB[3] = det;
                c_event.lower_x(0.5 * sqrt_expr_evaluator<4>::eval<mpt_type, mpf_type>(cA, cB).get_d() /
                                (denom_sqr * std::sqrt(segm_len.get_d())));
            }
            
            return true;
        }
        
        // Recompute parameters of the circle event using high-precision library.
        bool pss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int point_index,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef mpt_wrapper<mpz_class, 8> mpt_type;
            typedef mpt_wrapper<mpf_class, 2> mpf_type;
            static mpt_type a[2], b[2], c[2], cA[4], cB[4], orientation, dx, dy, ix, iy;

            const point_type &segm_start1 = site2.point1(true);
            const point_type &segm_end1 = site2.point0(true);
            const point_type &segm_start2 = site3.point0(true);
            const point_type &segm_end2 = site3.point1(true);

            a[0] = segm_end1.x() - segm_start1.x();
            b[0] = segm_end1.y() - segm_start1.y();
            a[1] = segm_end2.x() - segm_start2.x();
            b[1] = segm_end2.y() - segm_start2.y();
            orientation = a[1] * b[0] - a[0] * b[1];
            if (orientation == 0) {
                double denom = (a[0] * a[0] + b[0] * b[0]).get_d() * 2.0;
                c[0] = b[0] * (segm_start2.x() - segm_start1.x()) -
                       a[0] * (segm_start2.y() - segm_start1.y());
                dx = a[0] * (site1.y() - segm_start1.y()) -
                     b[0] * (site1.x() - segm_start1.x());
                dy = b[0] * (site1.x() - segm_start2.x()) -
                     a[0] * (site1.y() - segm_start2.y());
                cB[0] = dx * dy;
                cB[1] = 1;

                if (recompute_c_y) {
                    cA[0] = b[0] * ((point_index == 2) ? 2 : -2);
                    cA[1] = a[0] * a[0] * (segm_start1.y() + segm_start2.y()) -
                            a[0] * b[0] * (segm_start1.x() + segm_start2.x() - 2.0 * site1.x()) +
                            b[0] * b[0] * (2.0 * site1.y());
                    double c_y = sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                    c_event.y(c_y / denom);
                }

                if (recompute_c_x || recompute_lower_x) {
                    cA[0] = a[0] * ((point_index == 2) ? 2 : -2);
                    cA[1] = b[0] * b[0] * (segm_start1.x() + segm_start2.x()) -
                            a[0] * b[0] * (segm_start1.y() + segm_start2.y() - 2.0 * site1.y()) +
                            a[0] * a[0] * (2.0 * site1.x());

                    if (recompute_c_x) {
                        double c_x = sqrt_expr_evaluator<2>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                        c_event.x(c_x / denom);
                    }

                    if (recompute_lower_x) {
                        cA[2] = (c[0] < 0) ? -c[0] : c[0];
                        cB[2] = a[0] * a[0] + b[0] * b[0];
                        double lower_x = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cA, cB).get_d();
                        c_event.lower_x(lower_x / denom);
                    }
                }
                return true;
            }
            c[0] = b[0] * segm_end1.x() - a[0] * segm_end1.y();
            c[1] = a[1] * segm_end2.y() - b[1] * segm_end2.x();
            ix = a[0] * c[1] + a[1] * c[0];
            iy = b[0] * c[1] + b[1] * c[0];
            dx = ix - orientation * site1.x();
            dy = iy - orientation * site1.y();
            if ((dx == 0) && (dy == 0)) {
                double denom = orientation.get_d();
                double c_x = ix.get_d() / denom;
                double c_y = iy.get_d() / denom;
                c_event = circle_type(c_x, c_y, c_x);
                return true;
            }

            double sign = ((point_index == 2) ? 1 : -1) * ((orientation < 0) ? 1 : -1);
            cA[0] = a[1] * -dx + b[1] * -dy;
            cA[1] = a[0] * -dx + b[0] * -dy;
            cA[2] = sign;
            cA[3] = 0;
            cB[0] = a[0] * a[0] + b[0] * b[0];
            cB[1] = a[1] * a[1] + b[1] * b[1];
            cB[2] = a[0] * a[1] + b[0] * b[1];
            cB[3] = (a[0] * dy - b[0] * dx) * (a[1] * dy - b[1] * dx) * -2;
            double temp = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
            double denom = temp * orientation.get_d();

            if (recompute_c_y) {
                cA[0] = b[1] * (dx * dx + dy * dy) - iy * (dx * a[1] + dy * b[1]);
                cA[1] = b[0] * (dx * dx + dy * dy) - iy * (dx * a[0] + dy * b[0]);
                cA[2] = iy * sign;
                double cy = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
                c_event.y(cy / denom);
            }

            if (recompute_c_x || recompute_lower_x) {
                cA[0] = a[1] * (dx * dx + dy * dy) - ix * (dx * a[1] + dy * b[1]);
                cA[1] = a[0] * (dx * dx + dy * dy) - ix * (dx * a[0] + dy * b[0]);
                cA[2] = ix * sign;

                if (recompute_c_x) {
                    double cx = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
                    c_event.x(cx / denom);
                }

                if (recompute_lower_x) {
                    cA[3] = orientation * (dx * dx + dy * dy) * (temp < 0 ? -1 : 1);
                    double lower_x = sqrt_expr_evaluator_pss<mpt_type, mpf_type>(cA, cB).get_d();
                    c_event.lower_x(lower_x / denom);
                }
            }

            return true;
        }

        // Recompute parameters of the circle event using high-precision library.
        bool sss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event,
                 bool recompute_c_x = true,
                 bool recompute_c_y = true,
                 bool recompute_lower_x = true) {
            typedef mpt_wrapper<mpz_class, 8> mpt_type;
            typedef mpt_wrapper<mpf_class, 2> mpf_type;
            static mpt_type a[3], b[3], c[3], sqr_len[4], cross[4];

            a[0] = site1.x1(true) - site1.x0(true);
            a[1] = site2.x1(true) - site2.x0(true);
            a[2] = site3.x1(true) - site3.x0(true);
        
            b[0] = site1.y1(true) - site1.y0(true);
            b[1] = site2.y1(true) - site2.y0(true);
            b[2] = site3.y1(true) - site3.y0(true);

            c[0] = mpt_cross(site1.x0(true), site1.y0(true), site1.x1(true), site1.y1(true));										
            c[1] = mpt_cross(site2.x0(true), site2.y0(true), site2.x1(true), site2.y1(true));
            c[2] = mpt_cross(site3.x0(true), site3.y0(true), site3.x1(true), site3.y1(true));

            for (int i = 0; i < 3; ++i) {
                sqr_len[i] = a[i] * a[i] + b[i] * b[i];
            }

            for (int i = 0; i < 3; ++i) {
                int j = (i+1) % 3;
                int k = (i+2) % 3;
                cross[i] = a[j] * b[k] - a[k] * b[j];
            }
            double denom = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();

            if (recompute_c_y) {
                for (int i = 0; i < 3; ++i) {
                    int j = (i+1) % 3;
                    int k = (i+2) % 3;
                    cross[i] = b[j] * c[k] - b[k] * c[j];
                }
                double c_y = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
                c_event.y(c_y / denom);
            }

            if (recompute_c_x || recompute_lower_x) {
                cross[3] = 0;
                for (int i = 0; i < 3; ++i) {
                    int j = (i+1) % 3;
                    int k = (i+2) % 3;
                    cross[i] = a[j] * c[k] - a[k] * c[j];
                    if (recompute_lower_x) {
                        cross[3] += cross[i] * b[i];
                    }
                }

                if (recompute_c_x) {
                    double c_x = sqrt_expr_evaluator<3>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
                    c_event.x(c_x / denom);
                }
                
                if (recompute_lower_x) {
                    sqr_len[3] = 1;
                    double lower_x = sqrt_expr_evaluator<4>::eval<mpt_type, mpf_type>(cross, sqr_len).get_d();
                    c_event.lower_x(lower_x / denom);
                }
            }
            
            return true;
        }

    private:
        template <typename T>
        mpt_wrapper<mpz_class, 8> &mpt_cross(T a0, T b0, T a1, T b1) {
            static mpt_wrapper<mpz_class, 8> temp[2];
            temp[0] = a0;
            temp[1] = b0;
            temp[0] = temp[0] * b1;
            temp[1] = temp[1] * a1;
            temp[0] -= temp[1];
            return temp[0];
        }

        // Evaluates A[3] + A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
        //           A[2] * sqrt(B[3] * (sqrt(B[0] * B[1]) + B[2]));
        template <typename mpt, typename mpf>
        mpf sqrt_expr_evaluator_pss(mpt *A, mpt *B) {
            static mpt cA[4], cB[4];
            static mpf lh, rh, numer;
            if (A[3] == 0) {
                lh = sqrt_expr_evaluator<2>::eval<mpt, mpf>(A, B);
                cA[0] = 1;
                cB[0] = B[0] * B[1];
                cA[1] = B[2];
                cB[1] = 1;
                rh = A[2].get_d() * std::sqrt(B[3].get_d() *
                    sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB).get_d());
                if (((lh >= 0) && (rh >= 0)) || ((lh <= 0) && (rh <= 0))) {
                    return lh + rh;
                }
                cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
                cA[0] -= A[2] * A[2] * B[3] * B[2];
                cB[0] = 1;
                cA[1] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
                cB[1] = B[0] * B[1];
                numer = sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB);
                return numer / (lh - rh);
            }
            cA[0] = A[3];
            cB[0] = 1;
            cA[1] = A[0];
            cB[1] = B[0];
            cA[2] = A[1];
            cB[2] = B[1];
            lh = sqrt_expr_evaluator<3>::eval<mpt, mpf>(cA, cB);
            cA[0] = 1;
            cB[0] = B[0] * B[1];
            cA[1] = B[2];
            cB[1] = 1;
            rh = A[2].get_d() * std::sqrt(B[3].get_d() *
                sqrt_expr_evaluator<2>::eval<mpt, mpf>(cA, cB).get_d());
            if (((lh >= 0) && (rh >= 0)) || ((lh <= 0) && (rh <= 0))) {
                return lh + rh;
            }
            cA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1];
            cA[0] += A[3] * A[3] - A[2] * A[2] * B[2] * B[3];
            cB[0] = 1;
            cA[1] = A[3] * A[0] * 2;
            cB[1] = B[0];
            cA[2] = A[3] * A[1] * 2;
            cB[2] = B[1];
            cA[3] = A[0] * A[1] * 2 - A[2] * A[2] * B[3];
            cB[3] = B[0] * B[1];
            numer = sqrt_expr_evaluator<4>::eval<mpt, mpf>(cA, cB);
            return numer / (lh - rh);
        }
    };

    template <typename Site, typename Circle>
    class lazy_circle_formation_functor {
    public:
        typedef typename Site::point_type point_type;
        typedef Site site_type;
        typedef Circle circle_type;
        typedef gmp_circle_formation_functor<site_type, circle_type>
            exact_circle_formation_functor_type;

        // Find parameters of the inscribed circle that is tangent to three
        // point sites.
        bool ppp(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event) {
            double dif_x1 = site1.x() - site2.x();
            double dif_x2 = site2.x() - site3.x();
            double dif_y1 = site1.y() - site2.y();
            double dif_y2 = site2.y() - site3.y();
            double orientation = robust_cross_product(dif_x1, dif_y1, dif_x2, dif_y2);
            robust_fpt<double> inv_orientation(0.5 / orientation, 3.0);
            double sum_x1 = site1.x() + site2.x();
            double sum_x2 = site2.x() + site3.x();
            double sum_y1 = site1.y() + site2.y();
            double sum_y2 = site2.y() + site3.y();
            double dif_x3 = site1.x() - site3.x();
            double dif_y3 = site1.y() - site3.y();
            epsilon_robust_comparator< robust_fpt<double> > c_x, c_y;
            c_x += robust_fpt<double>(dif_x1 * sum_x1 * dif_y2, 2.0);
            c_x += robust_fpt<double>(dif_y1 * sum_y1 * dif_y2, 2.0);
            c_x -= robust_fpt<double>(dif_x2 * sum_x2 * dif_y1, 2.0);
            c_x -= robust_fpt<double>(dif_y2 * sum_y2 * dif_y1, 2.0);
            c_y += robust_fpt<double>(dif_x2 * sum_x2 * dif_x1, 2.0);
            c_y += robust_fpt<double>(dif_y2 * sum_y2 * dif_x1, 2.0);
            c_y -= robust_fpt<double>(dif_x1 * sum_x1 * dif_x2, 2.0);
            c_y -= robust_fpt<double>(dif_y1 * sum_y1 * dif_x2, 2.0);
            epsilon_robust_comparator< robust_fpt<double> > lower_x(c_x);
            lower_x -= robust_fpt<double>(std::sqrt(sqr_distance(dif_x1, dif_y1) *
                                                    sqr_distance(dif_x2, dif_y2) *
                                                    sqr_distance(dif_x3, dif_y3)), 5.0);
            c_event = circle_type(c_x.dif().fpv() * inv_orientation.fpv(),
                                           c_y.dif().fpv() * inv_orientation.fpv(),
                                           lower_x.dif().fpv() * inv_orientation.fpv());
            bool recompute_c_x = c_x.dif().ulp() >= 128;
            bool recompute_c_y = c_y.dif().ulp() >= 128;
            bool recompute_lower_x = lower_x.dif().ulp() >= 128;
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                return exact_circle_formation_functor_.ppp(
                    site1, site2, site3, c_event, recompute_c_x, recompute_c_y, recompute_lower_x);
            }
            return true;
        }

        // Find parameters of the inscribed circle that is tangent to two
        // point sites and on segment site.
        bool pps(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int segment_index,
                 circle_type &c_event) {
            double line_a = site3.point1(true).y() - site3.point0(true).y();
            double line_b = site3.point0(true).x() - site3.point1(true).x();
            double vec_x = site2.y() - site1.y();
            double vec_y = site1.x() - site2.x();
            robust_fpt<double> teta(robust_cross_product(line_a, line_b, -vec_y, vec_x), 2.0);
            robust_fpt<double> A(robust_cross_product(line_a, line_b,
                                                 site3.point1().y() - site1.y(),
                                                 site1.x() - site3.point1().x()), 2.0);
            robust_fpt<double> B(robust_cross_product(line_a, line_b,
                                                 site3.point1().y() - site2.y(),
                                                 site2.x() - site3.point1().x()), 2.0);
            robust_fpt<double> denom(robust_cross_product(vec_x, vec_y, line_a, line_b), 2.0);
            robust_fpt<double> inv_segm_len(1.0 / std::sqrt(sqr_distance(line_a, line_b)), 3.0);
            epsilon_robust_comparator< robust_fpt<double> > t;
            if (get_orientation(denom) == COLLINEAR) {
                t += teta / (robust_fpt<double>(8.0) * A);
                t -= A / (robust_fpt<double>(2.0) * teta);
            } else {
                robust_fpt<double> det = ((teta * teta + denom * denom) * A * B).sqrt();
                if (segment_index == 2) {
                    t -= det / (denom * denom);
                } else {
                    t += det / (denom * denom);
                }
                t += teta * (A + B) / (robust_fpt<double>(2.0) * denom * denom);
            }
            epsilon_robust_comparator< robust_fpt<double> > c_x, c_y;
            c_x += robust_fpt<double>(0.5 * (site1.x() + site2.x()));
            c_x += robust_fpt<double>(vec_x) * t;
            c_y += robust_fpt<double>(0.5 * (site1.y() + site2.y()));
            c_y += robust_fpt<double>(vec_y) * t;
            epsilon_robust_comparator< robust_fpt<double> > r, lower_x(c_x);
            r -= robust_fpt<double>(line_a) * robust_fpt<double>(site3.x0());
            r -= robust_fpt<double>(line_b) * robust_fpt<double>(site3.y0());
            r += robust_fpt<double>(line_a) * c_x;
            r += robust_fpt<double>(line_b) * c_y;
            r.abs();
            lower_x += r * inv_segm_len;
            c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            bool recompute_c_x = c_x.dif().ulp() >= 128;
            bool recompute_c_y = c_y.dif().ulp() >= 128;
            bool recompute_lower_x = lower_x.dif().ulp() >= 128;
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                return exact_circle_formation_functor_.pps(
                    site1, site2, site3, segment_index, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
            return true;
        }

        // Find parameters of the inscribed circle that is tangent to one
        // point site and two segment sites.
        bool pss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 int point_index,
                 circle_type &c_event) {
            const point_type &segm_start1 = site2.point1(true);
            const point_type &segm_end1 = site2.point0(true);
            const point_type &segm_start2 = site3.point0(true);
            const point_type &segm_end2 = site3.point1(true);
            double a1 = segm_end1.x() - segm_start1.x();
            double b1 = segm_end1.y() - segm_start1.y();
            double a2 = segm_end2.x() - segm_start2.x();
            double b2 = segm_end2.y() - segm_start2.y();
            bool recompute_c_x, recompute_c_y, recompute_lower_x;
            robust_fpt<double> orientation(robust_cross_product(b1, a1, b2, a2), 2.0);
            if (get_orientation(orientation) == COLLINEAR) {
                robust_fpt<double> a(a1 * a1 + b1 * b1, 2.0);
                robust_fpt<double> c(robust_cross_product(b1, a1, segm_start2.y() - segm_start1.y(),
                                                     segm_start2.x() - segm_start1.x()), 2.0);
                robust_fpt<double> det(robust_cross_product(a1, b1, site1.x() - segm_start1.x(),
                                                       site1.y() - segm_start1.y()) *
                                  robust_cross_product(b1, a1, site1.y() - segm_start2.y(),
                                                       site1.x() - segm_start2.x()), 5.0);
                epsilon_robust_comparator< robust_fpt<double> > t;
                t -= robust_fpt<double>(a1) * robust_fpt<double>((segm_start1.x() + segm_start2.x()) * 0.5 - site1.x());
                t -= robust_fpt<double>(b1) * robust_fpt<double>((segm_start1.y() + segm_start2.y()) * 0.5 - site1.y());
                if (point_index == 2) {
                    t += det.sqrt();
                } else {
                    t -= det.sqrt();
                }
                t /= a;
                epsilon_robust_comparator< robust_fpt<double> > c_x, c_y;
                c_x += robust_fpt<double>(0.5 * (segm_start1.x() + segm_start2.x()));
                c_x += robust_fpt<double>(a1) * t;
                c_y += robust_fpt<double>(0.5 * (segm_start1.y() + segm_start2.y()));
                c_y += robust_fpt<double>(b1) * t;
                epsilon_robust_comparator< robust_fpt<double> > lower_x(c_x);
                lower_x += robust_fpt<double>(0.5) * c.fabs() / a.sqrt();
                recompute_c_x = c_x.dif().ulp() > 128;
                recompute_c_y = c_y.dif().ulp() > 128;
                recompute_lower_x = lower_x.dif().ulp() > 128;
                c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            } else {
                robust_fpt<double> sqr_sum1(std::sqrt(a1 * a1 + b1 * b1), 2.0);
                robust_fpt<double> sqr_sum2(std::sqrt(a2 * a2 + b2 * b2), 2.0);
                robust_fpt<double> a(robust_cross_product(a1, b1, -b2, a2), 2.0);
                if (a >= 0) {
                    a += sqr_sum1 * sqr_sum2;
                } else {
                    a = (orientation * orientation) / (sqr_sum1 * sqr_sum2 - a);
                }
                robust_fpt<double> or1(robust_cross_product(b1, a1, segm_end1.y() - site1.y(),
                                                       segm_end1.x() - site1.x()), 2.0);
                robust_fpt<double> or2(robust_cross_product(a2, b2, segm_end2.x() - site1.x(),
                                                       segm_end2.y() - site1.y()), 2.0);
                robust_fpt<double> det = robust_fpt<double>(2.0) * a * or1 * or2;
                robust_fpt<double> c1(robust_cross_product(b1, a1, segm_end1.y(), segm_end1.x()), 2.0);
                robust_fpt<double> c2(robust_cross_product(a2, b2, segm_end2.x(), segm_end2.y()), 2.0);
                robust_fpt<double> inv_orientation = robust_fpt<double>(1.0) / orientation;
                epsilon_robust_comparator< robust_fpt<double> > t, b, ix, iy;
                ix += robust_fpt<double>(a2) * c1 * inv_orientation;
                ix += robust_fpt<double>(a1) * c2 * inv_orientation;
                iy += robust_fpt<double>(b1) * c2 * inv_orientation;
                iy += robust_fpt<double>(b2) * c1 * inv_orientation;

                b += ix * (robust_fpt<double>(a1) * sqr_sum2);
                b += ix * (robust_fpt<double>(a2) * sqr_sum1);
                b += iy * (robust_fpt<double>(b1) * sqr_sum2);
                b += iy * (robust_fpt<double>(b2) * sqr_sum1);
                b -= sqr_sum1 * robust_fpt<double>(robust_cross_product(a2, b2, -site1.y(), site1.x()), 2.0);
                b -= sqr_sum2 * robust_fpt<double>(robust_cross_product(a1, b1, -site1.y(), site1.x()), 2.0);
                t -= b;
                if (point_index == 2) {
                    t += det.sqrt();
                } else {
                    t -= det.sqrt();
                }
                t /= (a * a);
                epsilon_robust_comparator< robust_fpt<double> > c_x(ix), c_y(iy);
                c_x += t * (robust_fpt<double>(a1) * sqr_sum2);
                c_x += t * (robust_fpt<double>(a2) * sqr_sum1);
                c_y += t * (robust_fpt<double>(b1) * sqr_sum2);
                c_y += t * (robust_fpt<double>(b2) * sqr_sum1);
                t.abs();
                epsilon_robust_comparator< robust_fpt<double> > lower_x(c_x);
                lower_x += t * orientation.fabs();
                recompute_c_x = c_x.dif().ulp() > 128;
                recompute_c_y = c_y.dif().ulp() > 128;
                recompute_lower_x = lower_x.dif().ulp() > 128;
                c_event = circle_type(c_x.dif().fpv(), c_y.dif().fpv(), lower_x.dif().fpv());
            }
            if (recompute_c_x || recompute_c_y || recompute_lower_x) {
                return exact_circle_formation_functor_.pss(
                    site1, site2, site3, point_index, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
            return true;
        }

        // Find parameters of the inscribed circle that is tangent to three
        // segment sites.
        bool sss(const site_type &site1,
                 const site_type &site2,
                 const site_type &site3,
                 circle_type &c_event) {
            robust_fpt<double> a1(site1.x1(true) - site1.x0(true), 0.0);
            robust_fpt<double> b1(site1.y1(true) - site1.y0(true), 0.0);
            robust_fpt<double> c1(robust_cross_product(site1.x0(true), site1.y0(true), site1.x1(true), site1.y1(true)), 2.0);
            
            robust_fpt<double> a2(site2.x1(true) - site2.x0(true), 0.0);
            robust_fpt<double> b2(site2.y1(true) - site2.y0(true), 0.0);
            robust_fpt<double> c2(robust_cross_product(site2.x0(true), site2.y0(true), site2.x1(true), site2.y1(true)), 2.0);
            
            robust_fpt<double> a3(site3.x1(true) - site3.x0(true), 0.0);
            robust_fpt<double> b3(site3.y1(true) - site3.y0(true), 0.0);
            robust_fpt<double> c3(robust_cross_product(site3.x0(true), site3.y0(true), site3.x1(true), site3.y1(true)), 2.0);
            
            robust_fpt<double> len1 = (a1 * a1 + b1 * b1).sqrt();
            robust_fpt<double> len2 = (a2 * a2 + b2 * b2).sqrt();
            robust_fpt<double> len3 = (a3 * a3 + b3 * b3).sqrt();
            robust_fpt<double> cross_12(robust_cross_product(a1.fpv(), b1.fpv(), a2.fpv(), b2.fpv()), 2.0);
            robust_fpt<double> cross_23(robust_cross_product(a2.fpv(), b2.fpv(), a3.fpv(), b3.fpv()), 2.0);
            robust_fpt<double> cross_31(robust_cross_product(a3.fpv(), b3.fpv(), a1.fpv(), b1.fpv()), 2.0);
            epsilon_robust_comparator< robust_fpt<double> > denom, c_x, c_y, r;

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
            epsilon_robust_comparator< robust_fpt<double> > lower_x(c_x + r);
            bool recompute_c_x = c_x.dif().ulp() > 128;
            bool recompute_c_y = c_y.dif().ulp() > 128;
            bool recompute_lower_x = lower_x.dif().ulp() > 128;
            bool recompute_denom = denom.dif().ulp() > 128;
            c_event = circle_type(c_x.dif().fpv() / denom.dif().fpv(),
                                           c_y.dif().fpv() / denom.dif().fpv(),
                                           lower_x.dif().fpv() / denom.dif().fpv());
            if (recompute_c_x || recompute_c_y || recompute_lower_x || recompute_denom) {
                return exact_circle_formation_functor_.sss(
                    site1, site2, site3, c_event,
                    recompute_c_x, recompute_c_y, recompute_lower_x);
            }
            return true;
        }

    private:
        template <typename T>
        T sqr_distance(T dif_x, T dif_y) {
            return dif_x * dif_x + dif_y * dif_y;
        }

    private:
        exact_circle_formation_functor_type exact_circle_formation_functor_; 
    };

    template <typename Site, typename Circle>
    class circle_formation_predicate {
    public:
        typedef Site site_type;
        typedef Circle circle_type;
        typedef circle_existence_predicate<site_type> circle_existence_predicate_type;
        typedef lazy_circle_formation_functor<site_type, circle_type>
            circle_formation_functor_type;

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
    static bool convert_to_65_bit(T value, ulong_long_type &res) {
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
