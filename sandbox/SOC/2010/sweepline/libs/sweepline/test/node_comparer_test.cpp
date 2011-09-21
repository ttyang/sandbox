// Boost sweepline library node_comparer_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#define BOOST_TEST_MODULE node_comparer_test
#include <boost/mpl/list.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/sweepline/voronoi_builder.hpp"
using namespace boost::sweepline;
using namespace boost::sweepline::detail;

typedef boost::mpl::list<double> test_types;

#define DEFINE_BEACH_LINE \
    typedef site_event<T> site_event_type; \
    typedef beach_line_node_key<site_event_type> key_type; \
    typedef beach_line_node_comparer<key_type> node_comparer_type; \
    typedef std::map< key_type, int, node_comparer_type > beach_line_type; \
    typedef typename beach_line_type::iterator beach_line_iterator

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp1, T, test_types) {
    DEFINE_BEACH_LINE;
    beach_line_type test_beach_line;

    site_event_type site1 = site_event<T>(static_cast<T>(0), static_cast<T>(0), 0);
    site_event_type site2 = site_event<T>(static_cast<T>(0), static_cast<T>(2), 1);
    key_type initial_node(site1, site2);
    test_beach_line[initial_node] = 2;

    site_event_type site3 = site_event<T>(static_cast<T>(1), static_cast<T>(0), 2);
    key_type node1(site1, site3);
    key_type node2(site3, site1);
    test_beach_line.insert(std::pair<key_type, int>(node1, 0));
    test_beach_line.insert(std::pair<key_type, int>(node2, 1));

    int cur_value = 0;
    for (beach_line_iterator it = test_beach_line.begin();
         it != test_beach_line.end();
         it++, cur_value++)
        BOOST_CHECK_EQUAL(it->second, cur_value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp2, T, test_types) {
    DEFINE_BEACH_LINE;
    beach_line_type test_beach_line;

    site_event_type site1 = site_event<T>(static_cast<T>(0), static_cast<T>(1), 0);
    site_event_type site2 = site_event<T>(static_cast<T>(2), static_cast<T>(0), 1);
    site_event_type site3 = site_event<T>(static_cast<T>(2), static_cast<T>(4), 2);
    key_type initial_node1(site1, site2);
    key_type initial_node2(site2, site1);
    test_beach_line.insert(std::pair<key_type, int>(initial_node1, 0));
    test_beach_line.insert(std::pair<key_type, int>(initial_node2, 1));

    key_type new_node1(site1, site3);
    key_type new_node2(site3, site1);
    test_beach_line.insert(std::pair<key_type, int>(new_node1, 2));
    test_beach_line.insert(std::pair<key_type, int>(new_node2, 3));

    int cur_value = 0;
    for (beach_line_iterator it = test_beach_line.begin();
         it != test_beach_line.end();
         it++, cur_value++)
        BOOST_CHECK_EQUAL(it->second, cur_value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp3, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(1), static_cast<T>(0), 0),
        site_event<T>(static_cast<T>(0), static_cast<T>(2), 1));

    key_type new_node1(site_event<T>(static_cast<T>(2), static_cast<T>(-10), 2));
    key_type new_node2(site_event<T>(static_cast<T>(2), static_cast<T>(-1), 3));
    key_type new_node3(site_event<T>(static_cast<T>(2), static_cast<T>(0), 4));
    key_type new_node4(site_event<T>(static_cast<T>(2), static_cast<T>(1), 4));
    key_type new_node5(site_event<T>(static_cast<T>(2), static_cast<T>(2), 4));
    key_type new_node6(site_event<T>(static_cast<T>(2), static_cast<T>(3), 4));


    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node4), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node5), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node6), true);


    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node4, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node5, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node6, initial_node), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp4, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(0), static_cast<T>(1), 0),
        site_event<T>(static_cast<T>(1), static_cast<T>(0), 1));

    key_type new_node1(site_event<T>(static_cast<T>(2), static_cast<T>(-3), 2));
    key_type new_node2(site_event<T>(static_cast<T>(2), static_cast<T>(-2), 2));
    key_type new_node3(site_event<T>(static_cast<T>(2), static_cast<T>(-1), 2));
    key_type new_node4(site_event<T>(static_cast<T>(2), static_cast<T>(0), 2));
    key_type new_node5(site_event<T>(static_cast<T>(2), static_cast<T>(1), 2));
    key_type new_node6(site_event<T>(static_cast<T>(2), static_cast<T>(3), 2));

    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node4), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node5), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node6), true);

    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node4, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node5, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node6, initial_node), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp5, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(0), static_cast<T>(0), 0),
        site_event<T>(static_cast<T>(1), static_cast<T>(2), 1));

    key_type new_node1(site_event<T>(static_cast<T>(2), static_cast<T>(-10), 2));
    key_type new_node2(site_event<T>(static_cast<T>(2), static_cast<T>(0), 3));
    key_type new_node3(site_event<T>(static_cast<T>(2), static_cast<T>(1), 4));
    key_type new_node4(site_event<T>(static_cast<T>(2), static_cast<T>(2), 4));
    key_type new_node5(site_event<T>(static_cast<T>(2), static_cast<T>(5), 4));
    key_type new_node6(site_event<T>(static_cast<T>(2), static_cast<T>(20), 4));


    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node4), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node5), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node6), true);


    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node4, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node5, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node6, initial_node), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp6, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(1), static_cast<T>(1), 0),
        site_event<T>(static_cast<T>(0), static_cast<T>(0), 1));

    key_type new_node1(site_event<T>(static_cast<T>(2), static_cast<T>(-3), 2));
    key_type new_node2(site_event<T>(static_cast<T>(2), static_cast<T>(-2), 3));
    key_type new_node3(site_event<T>(static_cast<T>(2), static_cast<T>(0), 4));
    key_type new_node4(site_event<T>(static_cast<T>(2), static_cast<T>(1), 4));
    key_type new_node5(site_event<T>(static_cast<T>(2), static_cast<T>(2), 4));
    key_type new_node6(site_event<T>(static_cast<T>(2), static_cast<T>(3), 4));
    key_type new_node7(site_event<T>(static_cast<T>(2), static_cast<T>(5), 4));

    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node4), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node5), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node6), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node7), true);

    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node4, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node5, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node6, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node7, initial_node), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp7, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(0), static_cast<T>(0), 0),
        site_event<T>(static_cast<T>(0), static_cast<T>(2), 1));

    key_type new_node1(site_event<T>(static_cast<T>(1), static_cast<T>(0), 2));
    key_type new_node2(site_event<T>(static_cast<T>(1), static_cast<T>(1), 3));
    key_type new_node3(site_event<T>(static_cast<T>(1), static_cast<T>(2), 4));

    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), true);

    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(node_comparer_test_pp8, T, test_types) {
    DEFINE_BEACH_LINE;
    node_comparer_type node_comparer_test;

    key_type initial_node(
        site_event<T>(static_cast<T>(0), static_cast<T>(0), 0),
        site_event<T>(static_cast<T>(1), static_cast<T>(1), 1));

    key_type new_node1(site_event<T>(static_cast<T>(1), static_cast<T>(0), 2));
    key_type new_node2(site_event<T>(static_cast<T>(1), static_cast<T>(1), 1));
    key_type new_node3(site_event<T>(static_cast<T>(1), static_cast<T>(2), 3));
    key_type new_node4(
        site_event<T>(static_cast<T>(1), static_cast<T>(1), 1),
        site_event<T>(static_cast<T>(0), static_cast<T>(0), 0));

    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node1), false);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node2), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node3), true);
    BOOST_CHECK_EQUAL(node_comparer_test(initial_node, new_node4), true);

    BOOST_CHECK_EQUAL(node_comparer_test(new_node1, initial_node), true);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node2, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node3, initial_node), false);
    BOOST_CHECK_EQUAL(node_comparer_test(new_node4, initial_node), false);
}
