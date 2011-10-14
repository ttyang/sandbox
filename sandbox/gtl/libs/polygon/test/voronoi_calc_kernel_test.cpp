// Boost.Polygon library voronoi_calc_kernel_test.cpp file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE voronoi_calc_kernel_test
#include <boost/test/test_case_template.hpp>

#include "boost/polygon/detail/voronoi_structures.hpp"
#include "boost/polygon/detail/voronoi_calc_kernel.hpp"
using namespace boost::polygon::detail;

typedef voronoi_calc_kernel<int> VCK;
typedef point_2d<int> point_type;
typedef site_event<int> site_type;
typedef circle_event<double> circle_type;
VCK::event_comparison_predicate<site_type, circle_type> event_comparison;
VCK::event_equality_predicate<site_type, circle_type> event_equality;

#define CHECK_EVENT_COMPARISON(A, B, R1, R2) \
    BOOST_CHECK_EQUAL(event_comparison(A, B), R1); \
    BOOST_CHECK_EQUAL(event_comparison(B, A), R2); \
    BOOST_CHECK_EQUAL(event_equality(A, B), !R1 && !R2)

BOOST_AUTO_TEST_CASE(event_comparison_test1) {
    site_type site(1, 2, 0);
    CHECK_EVENT_COMPARISON(site, site_type(0, 2, 1), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(1, 3, 2), true, false);
    CHECK_EVENT_COMPARISON(site, site_type(1, 2, 3), false, false);
}

BOOST_AUTO_TEST_CASE(event_comparison_test2) {
    site_type site(0, 2, 0, 0, 0);
    CHECK_EVENT_COMPARISON(site, site_type(0, 2, 1), true, false);
    CHECK_EVENT_COMPARISON(site, site_type(0, 0, 2), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, -2, 0, -1, 3), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, -2, 1, 1, 4), true, false);
    CHECK_EVENT_COMPARISON(site, site_type(0, 0, 1, 1, 5), true, false);
}

BOOST_AUTO_TEST_CASE(event_comparison_test3) {
    site_type site(10, 10, 0, 0, 0);
    CHECK_EVENT_COMPARISON(site, site_type(0, 0, 1), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, -1, 2), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, 1, 3), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, 1, 0, 10, 4), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, -10, 0, -1, 5), false, true);
    CHECK_EVENT_COMPARISON(site, site_type(0, 0, 10, 9, 6), true, false);
    CHECK_EVENT_COMPARISON(site, site_type(0, 0, 9, 10, 7), false, true);
}

BOOST_AUTO_TEST_CASE(event_comparison_test4) {
    circle_type circle(1, 2, 3);
    CHECK_EVENT_COMPARISON(circle, circle_type(1, 2, 3), false, false);
    CHECK_EVENT_COMPARISON(circle, circle_type(1, 3, 3), true, false);
    CHECK_EVENT_COMPARISON(circle, circle_type(1, 2, 4), true, false);
    CHECK_EVENT_COMPARISON(circle, circle_type(0, 2, 2), false, true);
    CHECK_EVENT_COMPARISON(circle, circle_type(-1, 2, 3), false, false);
}

BOOST_AUTO_TEST_CASE(event_comparison_test5) {
    circle_type circle(1, 2, 3);
    CHECK_EVENT_COMPARISON(circle, site_type(0, 100, 1), false, true);
    CHECK_EVENT_COMPARISON(circle, site_type(3, 0, 2), false, true);
    CHECK_EVENT_COMPARISON(circle, site_type(3, 2, 3), false, false);
    CHECK_EVENT_COMPARISON(circle, site_type(3, 3, 4), true, false);
    CHECK_EVENT_COMPARISON(circle, site_type(4, 2, 5), true, false);
}
