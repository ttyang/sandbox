// Boost sweepline library predicates_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE predicates_test
#include <boost/mpl/list.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/sweepline/voronoi_builder.hpp"
using namespace boost::sweepline;
using namespace boost::sweepline::detail;

typedef boost::mpl::list<double> test_types;

#define CHECK_ORIENTATION_EQUAL(p1, p2, p3, exp) \
        BOOST_CHECK_EQUAL(orientation_test(p1, p2, p3) == exp, true)

#define CHECK_LESS_PREDICATE_PP(ls, rs, ns, exp) \
        BOOST_CHECK_EQUAL(less_predicate_pp(ls, rs, ns) == exp, true)

#define CHECK_FAST_LESS_PREDICATE_PS(ls, rs, ns, reverse, exp) \
        BOOST_CHECK_EQUAL(fast_less_predicate_ps(ls, rs, ns, reverse) == exp, true); \
        if (exp != UNDEFINED) { \
            bool exp_res = (exp == LESS) ? true : false; \
            BOOST_CHECK_EQUAL(less_predicate_ps(ls, rs, ns, reverse), exp_res); \
        }

#define CHECK_LESS_PREDICATE_PS(ls, rs, ns, reverse, exp) \
        BOOST_CHECK_EQUAL(less_predicate_ps(ls, rs, ns, reverse) == exp, true)

#define CHECK_LESS_PREDICATE_SS(ls, rs, ns, exp) \
        BOOST_CHECK_EQUAL(less_predicate_ss(ls, rs, ns) == exp, true)

// This test uses integer values in the range [-2^31, 2^31), to validate
// orientation predicate for the hole integer range input coordinates.
BOOST_AUTO_TEST_CASE_TEMPLATE(orientation_test1, T, test_types) {
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    point_2d<T> point1 = point_2d<T>(min_int, min_int);
    point_2d<T> point2 = point_2d<T>(0, 0);
    point_2d<T> point3 = point_2d<T>(max_int, max_int);
    point_2d<T> point4 = point_2d<T>(min_int, max_int);
    point_2d<T> point5 = point_2d<T>(max_int - 1, max_int);

    CHECK_ORIENTATION_EQUAL(point1, point2, point3, COLLINEAR);
    CHECK_ORIENTATION_EQUAL(point1, point3, point2, COLLINEAR);
    CHECK_ORIENTATION_EQUAL(point2, point3, point1, COLLINEAR);
    CHECK_ORIENTATION_EQUAL(point2, point1, point3, COLLINEAR);
    CHECK_ORIENTATION_EQUAL(point3, point1, point2, COLLINEAR);
    CHECK_ORIENTATION_EQUAL(point3, point2, point1, COLLINEAR);

    CHECK_ORIENTATION_EQUAL(point1, point4, point3, RIGHT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point1, point3, point4, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point4, point1, point3, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point4, point3, point1, RIGHT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point3, point4, point1, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point3, point1, point4, RIGHT_ORIENTATION);

    CHECK_ORIENTATION_EQUAL(point1, point5, point3, RIGHT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point1, point3, point5, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point5, point1, point3, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point5, point3, point1, RIGHT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point3, point5, point1, LEFT_ORIENTATION);
    CHECK_ORIENTATION_EQUAL(point3, point1, point5, RIGHT_ORIENTATION);
}

// Test main point-point predicate.
BOOST_AUTO_TEST_CASE_TEMPLATE(less_predicates_point_point_test1, T, test_types) {
    site_event<T> point1(static_cast<T>(-5), static_cast<T>(0), 0);
    site_event<T> point2(static_cast<T>(-8), static_cast<T>(9), 0);
    site_event<T> point3(static_cast<T>(-2), static_cast<T>(1), 0);

    site_event<T> site1(static_cast<T>(0), static_cast<T>(5), 0);
    CHECK_LESS_PREDICATE_PP(point1, point2, site1, false);
    CHECK_LESS_PREDICATE_PP(point3, point1, site1, false);

    site_event<T> site2(static_cast<T>(0), static_cast<T>(4), 0);
    CHECK_LESS_PREDICATE_PP(point1, point2, site2, false);
    CHECK_LESS_PREDICATE_PP(point3, point1, site2, false);

    site_event<T> site3(static_cast<T>(0), static_cast<T>(6), 0);
    CHECK_LESS_PREDICATE_PP(point1, point2, site3, true);
    CHECK_LESS_PREDICATE_PP(point3, point1, site3, true);
}

// Vertical segment case.
BOOST_AUTO_TEST_CASE_TEMPLATE(fast_less_predicate_point_segment_test1, T, test_types) {
    point_2d<T> segm_start = point_2d<T>(static_cast<T>(-4), static_cast<T>(0));
    point_2d<T> segm_end = point_2d<T>(static_cast<T>(-4), static_cast<T>(20));
    site_event<T> segm_site(segm_start, segm_end, 0);

    site_event<T> site_p(static_cast<T>(-2), static_cast<T>(10), 0);
    site_event<T> new_p1(static_cast<T>(0), static_cast<T>(11), 1);
    site_event<T> new_p2(static_cast<T>(0), static_cast<T>(9), 2);

    CHECK_FAST_LESS_PREDICATE_PS(site_p, segm_site, new_p1, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p, segm_site, new_p2, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p, segm_site, new_p1, true, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p, segm_site, new_p2, true, UNDEFINED);
}

// Not vertical segment case. Site is to the left of the segment vector.
BOOST_AUTO_TEST_CASE_TEMPLATE(fast_less_predicate_point_segment_test2, T, test_types) {
    point_2d<T> segm_start = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end = point_2d<T>(static_cast<T>(2), static_cast<T>(-2));
    site_event<T> segm_site(segm_start, segm_end, 0);

    site_event<T> site_p1(static_cast<T>(-2), static_cast<T>(4), 0);
    site_event<T> new_p1(static_cast<T>(0), static_cast<T>(-1), 0);
    segm_site.inverse();
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p1, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p1, true, MORE);

    site_event<T> new_p2(static_cast<T>(0), static_cast<T>(1), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p2, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p2, true, UNDEFINED);

    site_event<T> new_p3(static_cast<T>(0), static_cast<T>(4), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p3, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p3, true, UNDEFINED);

    site_event<T> new_p4(static_cast<T>(0), static_cast<T>(5), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p4, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p4, true, LESS);
}

// Not vertical segment case. Site is to the right of the segment vector.
BOOST_AUTO_TEST_CASE_TEMPLATE(fast_less_predicate_point_segment_test3, T, test_types) {
    point_2d<T> segm_start = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end = point_2d<T>(static_cast<T>(2), static_cast<T>(-2));
    site_event<T> segm_site(segm_start, segm_end, 0);

    site_event<T> site_p1(static_cast<T>(-2), static_cast<T>(-4), 0);
    site_event<T> site_p2(static_cast<int>(-4), static_cast<int>(1), 0);

    site_event<T> new_p1(static_cast<T>(0), static_cast<T>(1), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p1, false, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p1, true, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p1, false, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p1, true, LESS);

    site_event<T> new_p2(static_cast<T>(0), static_cast<T>(-2), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p2, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p2, true, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p2, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p2, true, LESS);

    site_event<T> new_p3(static_cast<T>(0), static_cast<T>(-8), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p3, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p3, true, LESS);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p3, false, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p3, true, LESS);

    site_event<T> new_p4(static_cast<T>(0), static_cast<T>(-9), 0);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p4, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p1, segm_site, new_p4, true, UNDEFINED);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p4, false, MORE);
    CHECK_FAST_LESS_PREDICATE_PS(site_p2, segm_site, new_p4, true, UNDEFINED);
}

// Test main point-segment predicate.
BOOST_AUTO_TEST_CASE_TEMPLATE(less_predicate_point_segment_test1, T, test_types) {
    point_2d<T> segm_start = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end = point_2d<T>(static_cast<T>(2), static_cast<T>(-2));
    site_event<T> segm_site1(segm_start, segm_end, 0);
    site_event<T> segm_site2(segm_start, segm_end, 0);
    segm_site2.inverse();

    site_event<T> site_p1(static_cast<T>(-2), static_cast<T>(4), 0);
    site_event<T> site_p2(static_cast<T>(-2), static_cast<T>(-4), 0);
    site_event<T> site_p3(static_cast<int>(-4), static_cast<int>(1), 0);

    site_event<T> new_p1(static_cast<T>(0), static_cast<T>(1), 0);
    CHECK_LESS_PREDICATE_PS(site_p1, segm_site2, new_p1, true, false);

    site_event<T> new_p2(static_cast<T>(0), static_cast<T>(4), 0);
    CHECK_LESS_PREDICATE_PS(site_p1, segm_site2, new_p2, true, true);

    site_event<T> new_p3(static_cast<T>(0), static_cast<T>(5), 0);
    CHECK_LESS_PREDICATE_PS(site_p1, segm_site2, new_p3, false, false);

    site_event<T> new_p4(static_cast<T>(0), static_cast<T>(7), 0);
    CHECK_LESS_PREDICATE_PS(site_p1, segm_site2, new_p4, false, true);

    site_event<T> new_p5(static_cast<T>(0), static_cast<T>(-2), 0);
    CHECK_LESS_PREDICATE_PS(site_p2, segm_site1, new_p5, false, false);
    CHECK_LESS_PREDICATE_PS(site_p3, segm_site1, new_p5, false, false);

    site_event<T> new_p6(static_cast<T>(0), static_cast<T>(-8), 0);
    CHECK_LESS_PREDICATE_PS(site_p2, segm_site1, new_p6, false, false);
    CHECK_LESS_PREDICATE_PS(site_p3, segm_site1, new_p6, false, false);

    site_event<T> new_p7(static_cast<T>(0), static_cast<T>(-9), 0);
    CHECK_LESS_PREDICATE_PS(site_p2, segm_site1, new_p7, true, true);
    CHECK_LESS_PREDICATE_PS(site_p3, segm_site1, new_p7, true, true);

    site_event<T> new_p8(static_cast<T>(0), static_cast<T>(-18), 0);
    CHECK_LESS_PREDICATE_PS(site_p2, segm_site1, new_p8, true, false);
    CHECK_LESS_PREDICATE_PS(site_p3, segm_site1, new_p8, true, false);

    site_event<T> new_p9(static_cast<T>(0), static_cast<T>(-1), 0);
    CHECK_LESS_PREDICATE_PS(site_p2, segm_site1, new_p9, false, true);
    CHECK_LESS_PREDICATE_PS(site_p3, segm_site1, new_p9, false, true);
}

// Test main segment-segment predicate.
BOOST_AUTO_TEST_CASE_TEMPLATE(less_predicate_segment_segment_test1, T, test_types) {
    point_2d<T> segm_start1 = point_2d<T>(static_cast<T>(-5), static_cast<T>(0));
    point_2d<T> segm_end1 = point_2d<T>(static_cast<T>(2), static_cast<T>(7));
    site_event<T> segm_site1_1(segm_start1, segm_end1, 0);
    site_event<T> segm_site1_2(segm_start1, segm_end1, 0);
    segm_site1_2.inverse();

    // New sites.
    site_event<T> new_site1(static_cast<T>(2), static_cast<T>(7), 0);
    site_event<T> new_site2(static_cast<T>(1), static_cast<T>(5), 0);
    site_event<T> new_site3(static_cast<T>(-1), static_cast<T>(5), 0);

    CHECK_LESS_PREDICATE_SS(segm_site1_1, segm_site1_2, new_site1, false);
    CHECK_LESS_PREDICATE_SS(segm_site1_1, segm_site1_2, new_site2, false);
    CHECK_LESS_PREDICATE_SS(segm_site1_1, segm_site1_2, new_site3, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(less_predicate_segment_segment_test2, T, test_types) {
    typedef site_event<T> site_event_type;

    point_2d<T> segm_start1 = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end1 = point_2d<T>(static_cast<T>(2), static_cast<T>(-2));
    site_event_type segm_site1_1(segm_start1, segm_end1, 0);
    site_event_type segm_site1_2(segm_start1, segm_end1, 0);
    segm_site1_2.inverse();

    // New sites.
    site_event<T> new_site1(static_cast<T>(0), static_cast<T>(2), 0);
    site_event<T> new_site2(static_cast<T>(0), static_cast<T>(5), 0);
    site_event<T> new_site3(static_cast<T>(0), static_cast<T>(6), 0);
    site_event<T> new_site4(static_cast<T>(0), static_cast<T>(8), 0);

    // Common end points.
    point_2d<T> segm_start2 = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end2 = point_2d<T>(static_cast<T>(0), static_cast<T>(6));
    site_event_type segm_site2(segm_start2, segm_end2, 1);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site2, new_site1, false);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site2, new_site2, true);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site2, new_site3, true);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site2, new_site4, true);

    // No common end points.
    point_2d<T> segm_start3 = point_2d<T>(static_cast<T>(-2), static_cast<T>(4));
    point_2d<T> segm_end3 = point_2d<T>(static_cast<T>(0), static_cast<T>(4));
    site_event_type segm_site3(segm_start3, segm_end3, 2);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site3, new_site1, false);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site3, new_site2, true);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site3, new_site3, true);
    CHECK_LESS_PREDICATE_SS(segm_site1_2, segm_site3, new_site4, true);
    segm_site3.inverse();
    CHECK_LESS_PREDICATE_SS(segm_site3, segm_site1_2, new_site1, false);
    CHECK_LESS_PREDICATE_SS(segm_site3, segm_site1_2, new_site2, false);
    CHECK_LESS_PREDICATE_SS(segm_site3, segm_site1_2, new_site3, false);
    CHECK_LESS_PREDICATE_SS(segm_site3, segm_site1_2, new_site4, true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(less_predicate_segment_segment_test3, T, test_types) {
    typedef site_event<T> site_event_type;
    point_2d<T> segm_start1 = point_2d<T>(static_cast<T>(-5), static_cast<T>(3));
    point_2d<T> segm_start2 = point_2d<T>(static_cast<T>(-5), static_cast<T>(5));
    point_2d<T> segm_end = point_2d<T>(static_cast<T>(-2), static_cast<T>(2));
    site_event_type segm_site1(segm_start1, segm_end, 0);
    segm_site1.inverse();
    site_event_type segm_site2(segm_start2, segm_end, 1);
    site_event<T> point(-4, 2, 0);
    CHECK_LESS_PREDICATE_SS(segm_site1, segm_site2, point, false);
}
