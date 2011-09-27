// Boost sweepline library event_queue_test.cpp file

//          Copyright Andrii Sydorchuk 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <cmath>

#define BOOST_TEST_MODULE event_queue_test
#include <boost/mpl/list.hpp>
#include <boost/test/test_case_template.hpp>

#include "boost/sweepline/voronoi_builder.hpp"
using namespace boost::sweepline;
using namespace boost::sweepline::detail;

typedef boost::mpl::list<double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(event_queue_test1, T, test_types) {
    ordered_queue<T, std::greater<T> > event_q;
    BOOST_CHECK_EQUAL(event_q.empty(), true);
    for (int i = 0; i <= 10; ++i) {
        event_q.push(static_cast<T>(20 - 2 * i));
        event_q.push(static_cast<T>(2 * i + 1));
    }
    BOOST_CHECK_EQUAL(event_q.empty(), false);
    for (int i = 0; i <= 21; ++i) {
        T top = event_q.top();
        event_q.pop();
        BOOST_CHECK_EQUAL(top, static_cast<T>(i));
    }
    BOOST_CHECK_EQUAL(event_q.empty(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(event_queue_test2, T, test_types) {
    ordered_queue< std::pair<T, T>, std::greater< std::pair<T, T> > > event_q;
    for (int i = 0; i <= 10; i++) {
        event_q.push(std::make_pair(i, i)).second *= 2;
    }
    for (int i = 0; i <= 10; i++) {
        BOOST_CHECK_EQUAL(event_q.top().second, static_cast<T>(2 * i));
        event_q.pop();
    }
    BOOST_CHECK_EQUAL(event_q.empty(), true);
}
