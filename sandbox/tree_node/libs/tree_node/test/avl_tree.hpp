// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_AVL_TREE_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_AVL_TREE_HPP_INCLUDED

template <typename Tree, typename Values>
void test_avl_tree()
{
    Tree avl_tree;
    Values values;

    BOOST_CHECK(avl_tree.empty());
    BOOST_CHECK(0 == avl_tree.size());

    test_insert(avl_tree, values, 13);
    test_insert(avl_tree, values, 8);
    test_insert(avl_tree, values, 1);
    test_insert(avl_tree, values, 6);
    test_insert(avl_tree, values, 11);
    test_insert(avl_tree, values, 17);
    test_insert(avl_tree, values, 15);
    test_insert(avl_tree, values, 22);
    test_insert(avl_tree, values, 25);
    test_insert(avl_tree, values, 27);
    test_insert(avl_tree, values, 20);
    test_insert(avl_tree, values, 21);
    test_erase(avl_tree, values, 1);
    test_erase(avl_tree, values, 11);
    test_erase(avl_tree, values, 15);
}

#endif  // LIBS_TREE_NODE_TEST_AVL_TREE_HPP_INCLUDED

