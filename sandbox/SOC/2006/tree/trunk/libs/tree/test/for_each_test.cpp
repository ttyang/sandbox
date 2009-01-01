//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#include <boost/lambda/bind.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include "helpers.hpp"
#include "test_tree_traversal_data.hpp"

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE(cursor_algorithms_test, fake_binary_tree_with_list_fixture<int>)

BOOST_AUTO_TEST_CASE_TEMPLATE( test_for_each_descending, Order, orders)
{
    boost::tree::for_each(
        Order(),
        fbt1.descending_root(), 
        boost::lambda::bind(&std::list<int>::push_back, &l, boost::lambda::_1)
    );
    test_traversal(Order(), l.begin(), l.end());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( test_for_each_ascending, Order, orders)
{
    boost::tree::for_each(
        Order(),
        fbt1.ascending_root(), 
        boost::lambda::bind(&std::list<int>::push_back, &l, boost::lambda::_1)
    );
    test_traversal(Order(), l.begin(), l.end());
}

BOOST_AUTO_TEST_CASE( test_for_each_subtree3_descending )
{
    boost::tree::for_each(
        preorder(),
        fbt1.descending_root().begin(), 
        boost::lambda::bind(&std::list<int>::push_back, &l, boost::lambda::_1)
    );
    test_subtree_traversal(preorder(), l.begin(), l.end(), 1);
    BOOST_CHECK_EQUAL(l.size(), 5);
}

BOOST_AUTO_TEST_CASE( test_for_each_subtree3_ascending )
{
    boost::tree::for_each(
        preorder(),
        fbt1.ascending_root().begin(), 
        boost::lambda::bind(&std::list<int>::push_back, &l, boost::lambda::_1)
    );
    test_subtree_traversal(preorder(), l.begin(), l.end(), 1);
    BOOST_CHECK_EQUAL(l.size(), 5);
}

BOOST_AUTO_TEST_SUITE_END()