//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tree/binary_tree.hpp>

#include <boost/tree/iterator.hpp>
#include <boost/tree/algorithm.hpp>

#define BOOST_TEST_MODULE binary_tree test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <list>
#include <algorithm>
#include <iterator>

#include "helpers.hpp"
#include "fake_binary_tree.hpp"
#include "test_tree_traversal_data.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE(binary_tree_search_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE( lower_bound_test )
{   
    fake_binary_tree<int>::cursor c(fbt1, 0), d(fbt1, 0);

    c = lower_bound(fbt1.root(), 4); // (Left) Leaf
    BOOST_CHECK_EQUAL(*c, 4);
    c = lower_bound(fbt1.root(), 7); // (Right) Leaf
    BOOST_CHECK_EQUAL(*c, 7);
    c = lower_bound(fbt1.root(), 6); // Non-Leaf
    BOOST_CHECK_EQUAL(*c, 6);
    c = lower_bound(fbt1.root(), 8); // root().begin()
    BOOST_CHECK_EQUAL(*c, 8);

    c = lower_bound(fbt1.root(), 5); // Not in tree
    BOOST_CHECK_EQUAL(*c, 6);
}

BOOST_AUTO_TEST_SUITE_END()