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
struct voronoi_calc_kernel_traits;

template <>
struct voronoi_calc_kernel_traits<int> {
    typedef double fpt_type;
    typedef polygon_ulong_long_type ulong_long_type;
};

template <typename T>
class voronoi_calc_kernel;

template <>
class voronoi_calc_kernel<int> {
public:
    typedef voronoi_calc_kernel_traits<int>::fpt_type fpt_type;
    typedef voronoi_calc_kernel_traits<int>::ulong_long_type ulong_long_type;

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

    struct site_comparison_predicate {
        template <typename Site>
        bool operator()(const Site &lhs, const Site &rhs) const {
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

    struct site_equality_predicate {
        template <typename Site>
        bool operator()(const Site &lhs, const Site &rhs) const {
            return lhs.point0() == rhs.point0() &&
                   lhs.point1() == rhs.point1();
        }
    };

    struct circle_comparison_predicate {
        static const unsigned int ULPS = 128;

        template <typename Circle>
        bool operator()(const Circle &lhs, const Circle &rhs) const {
            if (almost_equal(lhs.lower_x(), rhs.lower_x(), ULPS)) {
                if (almost_equal(lhs.lower_y(), rhs.lower_y(), ULPS)) {
                    return false;
                }
                return lhs.lower_y() < rhs.lower_y();
            }
            return lhs.lower_x() < rhs.lower_x();
        }
    };

    struct event_comparison_predicate {
        static const unsigned int ULPS = 64;

        template <typename Site, typename Circle>    
        bool operator()(const Site &lhs, const Circle &rhs) const {
            if (almost_equal(lhs.x(), rhs.lower_x(), ULPS)) {
                if (almost_equal(lhs.y(), rhs.lower_y(), ULPS)) return false;
                return lhs.y() < rhs.lower_y();
            }
            return lhs.x() < rhs.lower_x();
        }
    };

    template <typename Node>
    struct node_comparison_predicate {
        bool operator()(const Node &lhs, const Node &rhs) const {
        }
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