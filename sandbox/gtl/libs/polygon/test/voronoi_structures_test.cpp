// Boost.Polygon library voronoi_structures_test.cpp file

//          Copyright Andrii Sydorchuk 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE voronoi_structures_test

#include <boost/test/test_case_template.hpp>
#include "boost/polygon/detail/voronoi_structures.hpp"
using namespace boost::polygon::detail;

typedef point_2d<int> point_type;
typedef site_event<int> site_type;
typedef circle_event<int> circle_type;
typedef ordered_queue<int, std::greater<int> > ordered_queue_type;
typedef beach_line_node_key<int> node_key_type;
typedef beach_line_node_data<int, int> node_data_type;

BOOST_AUTO_TEST_CASE(point_2d_test) {
    point_type p(1, 2);
    BOOST_CHECK_EQUAL(p.x(), 1);
    BOOST_CHECK_EQUAL(p.y(), 2);
    p.x(3);
    BOOST_CHECK_EQUAL(p.x(), 3);
    p.y(4);
    BOOST_CHECK_EQUAL(p.y(), 4);
}

BOOST_AUTO_TEST_CASE(site_event_test1) {
    site_type s(1, 2, 0);
    BOOST_CHECK_EQUAL(s.x0() == s.x1() && s.x1() == 1, true);
    BOOST_CHECK_EQUAL(s.y0() == s.y1() && s.y1() == 2, true);
    BOOST_CHECK_EQUAL(s.index() == 0, true);
    BOOST_CHECK_EQUAL(s.is_segment(), false);
    BOOST_CHECK_EQUAL(s.is_vertical(), true);
    BOOST_CHECK_EQUAL(s.is_inverse(), false);
}

BOOST_AUTO_TEST_CASE(site_event_test2) {
    site_type s(1, 2, 3, 4, 0);
    BOOST_CHECK_EQUAL(s.x0(true) == 1 && s.x0() == 1, true);
    BOOST_CHECK_EQUAL(s.y0(true) == 2 && s.y0() == 2, true);
    BOOST_CHECK_EQUAL(s.x1(true) == 3 && s.x1() == 3, true);
    BOOST_CHECK_EQUAL(s.y1(true) == 4 && s.y1() == 4, true);
    BOOST_CHECK_EQUAL(s.index() == 0, true);
    BOOST_CHECK_EQUAL(s.is_segment(), true);
    BOOST_CHECK_EQUAL(s.is_vertical(), false);
    BOOST_CHECK_EQUAL(s.is_inverse(), false);
    s.inverse();
    BOOST_CHECK_EQUAL(s.x1(true) == 1 && s.x0() == 1, true);
    BOOST_CHECK_EQUAL(s.y1(true) == 2 && s.y0() == 2, true);
    BOOST_CHECK_EQUAL(s.x0(true) == 3 && s.x1() == 3, true);
    BOOST_CHECK_EQUAL(s.y0(true) == 4 && s.y1() == 4, true);
    BOOST_CHECK_EQUAL(s.is_inverse(), true);   
}

BOOST_AUTO_TEST_CASE(circle_event_test) {
    circle_type c(0, 1, 2);
    BOOST_CHECK_EQUAL(c.x(), 0);
    BOOST_CHECK_EQUAL(c.y(), 1);
    BOOST_CHECK_EQUAL(c.lower_x(), 2);
    BOOST_CHECK_EQUAL(c.lower_y(), 1);
    BOOST_CHECK_EQUAL(c.is_active(), true);
    c.x(3);
    BOOST_CHECK_EQUAL(c.x(), 3);
    c.y(4);
    BOOST_CHECK_EQUAL(c.y(), 4);
    c.lower_x(5);
    BOOST_CHECK_EQUAL(c.lower_x(), 5);
    c.deactivate();
    BOOST_CHECK_EQUAL(c.is_active(), false);
}

BOOST_AUTO_TEST_CASE(ordered_queue_test) {
    ordered_queue_type q;
    BOOST_CHECK_EQUAL(q.empty(), true);
    std::vector<int*> vi;
    for (int i = 0; i < 20; ++i)
        vi.push_back(&q.push(i));
    for (int i = 0; i < 20; ++i)
        *vi[i] <<= 1;
    BOOST_CHECK_EQUAL(q.empty(), false);
    for (int i = 0; i < 20; ++i, q.pop())
        BOOST_CHECK_EQUAL(q.top(), i << 1);
    BOOST_CHECK_EQUAL(q.empty(), true);
}

BOOST_AUTO_TEST_CASE(beach_line_node_key_test) {
    node_key_type key(1);
    BOOST_CHECK_EQUAL(key.left_site(), 1);
    BOOST_CHECK_EQUAL(key.right_site(), 1);
    key.left_site(2);
    BOOST_CHECK_EQUAL(key.left_site() == 2, true);
    BOOST_CHECK_EQUAL(key.right_site() == 1, true);
    key.right_site(3);
    BOOST_CHECK_EQUAL(key.left_site() == 2, true);
    BOOST_CHECK_EQUAL(key.right_site() == 3, true);
}

BOOST_AUTO_TEST_CASE(beach_line_node_data_test) {
    node_data_type node_data(NULL);
    BOOST_CHECK_EQUAL(node_data.edge() == NULL, true);
    BOOST_CHECK_EQUAL(node_data.circle_event() == NULL, true);
    int data = 4;
    node_data.circle_event(&data);
    BOOST_CHECK_EQUAL(node_data.edge() == NULL, true);
    BOOST_CHECK_EQUAL(node_data.circle_event() == &data, true);
    node_data.edge(&data);
    BOOST_CHECK_EQUAL(node_data.edge() == &data, true);
    BOOST_CHECK_EQUAL(node_data.circle_event() == &data, true);
}
