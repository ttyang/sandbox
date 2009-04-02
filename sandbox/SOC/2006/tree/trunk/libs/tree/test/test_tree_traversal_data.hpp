//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP
#define LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP

#include <boost/tree/algorithm.hpp>

#include <boost/mpl/list.hpp>

typedef boost::mpl::list<boost::tree::preorder
                        ,boost::tree::inorder
                        ,boost::tree::postorder> orders;

template <class Cursor>
static void validate_test_dataset1_tree(Cursor cur)
{
    BOOST_CHECK_EQUAL(*cur.begin(), 8);
    BOOST_CHECK_EQUAL(*cur.begin().begin(), 3);
    BOOST_CHECK_EQUAL(*cur.begin().begin().begin(), 1);
    BOOST_CHECK(cur.begin().begin().end().is_leaf());
    BOOST_CHECK(cur.begin().begin().begin().is_leaf()); //Leaf
    
    BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 6);
    BOOST_CHECK_EQUAL(*cur.begin().end().begin().begin(), 4);
    BOOST_CHECK(cur.begin().end().begin().begin().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.begin().end().end().begin(), 7);
    BOOST_CHECK(cur.begin().end().end().begin().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.end().begin(), 10);
    BOOST_CHECK(cur.end().begin().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end().begin(), 14);
    BOOST_CHECK(cur.end().end().end().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 13);
    BOOST_CHECK(cur.end().end().begin().end().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().begin(), 11);
    BOOST_CHECK(cur.end().end().begin().begin().begin().is_leaf()); 
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end().begin(), 12);
    BOOST_CHECK(cur.end().end().begin().begin().end().begin().is_leaf()); //Leaf
}

template <class Cursor>
static void validate_test_dataset1_minus_1_tree(Cursor cur)
{
    BOOST_CHECK_EQUAL(*cur.begin(), 7);
    BOOST_CHECK_EQUAL(*cur.begin().begin(), 2);    
    BOOST_CHECK_EQUAL(*cur.begin().begin().begin(), 0);  //Leaf
    BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 5);        
    BOOST_CHECK_EQUAL(*cur.begin().end().begin().begin(), 3); //Leaf
    BOOST_CHECK_EQUAL(*cur.begin().end().end().begin(), 6); //Leaf

    BOOST_CHECK_EQUAL(*cur.end().begin(), 9);
    BOOST_CHECK_EQUAL(*cur.end().end().begin(), 13);
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 12);
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().begin(), 10); 
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end().begin(), 11); //Leaf
}

template <class Iterator>
void test_traversal_from_leaf4(Iterator a, Iterator b)
{    
    BOOST_CHECK_EQUAL(*a, 4);
    BOOST_CHECK_EQUAL(*++a, 6);
    BOOST_CHECK_EQUAL(*++a, 3);
    BOOST_CHECK_EQUAL(*++a, 8);
    BOOST_CHECK(++a == b);

} // namespace ascending

#endif // LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP
