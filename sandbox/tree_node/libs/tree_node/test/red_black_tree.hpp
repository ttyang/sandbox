// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_RED_BLACK_TREE_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_RED_BLACK_TREE_HPP_INCLUDED

#include "container_functions.hpp"

template <typename Tree, typename Values>
void test_red_black_tree()
{
    Tree red_black_tree;
    Values values;

    BOOST_CHECK(red_black_tree.empty());
    BOOST_CHECK(0 == red_black_tree.size());
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 3);
    test_erase(red_black_tree, values, 1);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, -3);
    test_erase(red_black_tree, values, -1);
    test_clear(red_black_tree, values);

    for (int i = 5; i < 10; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, i);
    }

    test_erase(red_black_tree, values, 5);
    test_clear(red_black_tree, values);

    for (int i = 5; i < 10; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, -i);
    }

    test_erase(red_black_tree, values, -5);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 13);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 11);
    test_insert(red_black_tree, values, 17);
    test_insert(red_black_tree, values, 15);
    test_insert(red_black_tree, values, 22);
    test_insert(red_black_tree, values, 25);
    test_insert(red_black_tree, values, 28);

    Tree red_black_copy(red_black_tree);

    test_tree_container(red_black_copy, values);
    test_insert(red_black_copy, values, 26);
    test_insert(red_black_copy, values, 27);
    test_erase(red_black_copy, values, 15);
    test_value_insert(values, 15);
    values.erase(27);
    values.erase(26);
    test_insert(red_black_tree, values, 20);
    test_insert(red_black_tree, values, 21);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 11);
    red_black_copy = red_black_tree;
    test_value_insert(values, 11);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 15);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -13);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -11);
    test_insert(red_black_tree, values, -17);
    test_insert(red_black_tree, values, -15);
    test_insert(red_black_tree, values, -22);
    test_insert(red_black_tree, values, -25);
    test_insert(red_black_tree, values, -28);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_insert(red_black_copy, values, -26);
    test_insert(red_black_copy, values, -27);
    test_erase(red_black_copy, values, -15);
    test_value_insert(values, -15);
    values.erase(-27);
    values.erase(-26);
    test_insert(red_black_tree, values, -20);
    test_insert(red_black_tree, values, -21);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -11);
    red_black_copy = red_black_tree;
    test_value_insert(values, -11);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -15);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 9);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 3);
    test_insert(red_black_tree, values, 5);
    test_insert(red_black_tree, values, 7);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 9);
    test_erase(red_black_copy, values, 2);
    test_erase(red_black_copy, values, 3);
    test_erase(red_black_copy, values, 1);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, -9);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, -3);
    test_insert(red_black_tree, values, -5);
    test_insert(red_black_tree, values, -7);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -9);
    test_erase(red_black_copy, values, -2);
    test_erase(red_black_copy, values, -3);
    test_erase(red_black_copy, values, -1);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 10; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, i);
    }

    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 1);
    red_black_copy = red_black_tree;
    test_value_insert(values, 1);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 3);
    red_black_copy = red_black_tree;
    test_value_insert(values, 3);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 5);
    red_black_copy = red_black_tree;
    test_value_insert(values, 5);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 7);
    test_erase(red_black_copy, values, 6);
    test_erase(red_black_copy, values, 5);
    test_erase(red_black_copy, values, 8);
    test_erase(red_black_copy, values, 9);
    red_black_copy = red_black_tree;
    test_value_insert(values, 9);
    test_value_insert(values, 8);
    test_value_insert(values, 5);
    test_value_insert(values, 6);
    test_value_insert(values, 7);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 15);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 10; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    for (int i = 15; 9 < i; --i)
    {
        test_insert(red_black_tree, values, -i);
    }

    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -1);
    red_black_copy = red_black_tree;
    test_value_insert(values, -1);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -3);
    red_black_copy = red_black_tree;
    test_value_insert(values, -3);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -5);
    red_black_copy = red_black_tree;
    test_value_insert(values, -5);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -7);
    test_erase(red_black_copy, values, -6);
    test_erase(red_black_copy, values, -5);
    test_erase(red_black_copy, values, -8);
    test_erase(red_black_copy, values, -9);
    red_black_copy = red_black_tree;
    test_value_insert(values, -9);
    test_value_insert(values, -8);
    test_value_insert(values, -5);
    test_value_insert(values, -6);
    test_value_insert(values, -7);
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -15);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 16; ++i)
    {
        test_insert(red_black_tree, values, i);
    }

    test_erase(red_black_tree, values, 5);
    test_clear(red_black_tree, values);

    for (int i = 1; i < 16; ++i)
    {
        test_insert(red_black_tree, values, -i);
    }

    test_erase(red_black_tree, values, -5);
    test_clear(red_black_tree, values);
    test_insert(red_black_tree, values, 0);
    test_insert(red_black_tree, values, -8);
    test_insert(red_black_tree, values, 8);
    test_insert(red_black_tree, values, -16);
    test_insert(red_black_tree, values, -4);
    test_insert(red_black_tree, values, 4);
    test_insert(red_black_tree, values, 16);
    test_insert(red_black_tree, values, -18);
    test_insert(red_black_tree, values, -12);
    test_insert(red_black_tree, values, -6);
    test_insert(red_black_tree, values, -2);
    test_insert(red_black_tree, values, 2);
    test_insert(red_black_tree, values, 6);
    test_insert(red_black_tree, values, 12);
    test_insert(red_black_tree, values, 18);
    test_insert(red_black_tree, values, -19);
    test_insert(red_black_tree, values, -17);
    test_insert(red_black_tree, values, -14);
    test_insert(red_black_tree, values, -10);
    test_insert(red_black_tree, values, -7);
    test_insert(red_black_tree, values, -5);
    test_insert(red_black_tree, values, -3);
    test_insert(red_black_tree, values, -1);
    test_insert(red_black_tree, values, 1);
    test_insert(red_black_tree, values, 3);
    test_insert(red_black_tree, values, 5);
    test_insert(red_black_tree, values, 7);
    test_insert(red_black_tree, values, 10);
    test_insert(red_black_tree, values, 14);
    test_insert(red_black_tree, values, 17);
    test_insert(red_black_tree, values, 19);
    test_insert(red_black_tree, values, -15);
    test_insert(red_black_tree, values, -13);
    test_insert(red_black_tree, values, -11);
    test_insert(red_black_tree, values, -9);
    test_insert(red_black_tree, values, 9);
    test_insert(red_black_tree, values, 11);
    test_insert(red_black_tree, values, 13);
    test_insert(red_black_tree, values, 15);
    test_erase(red_black_tree, values, -19);
    test_erase(red_black_tree, values, -17);
    test_erase(red_black_tree, values, -7);
    test_erase(red_black_tree, values, -5);
    test_erase(red_black_tree, values, -3);
    test_erase(red_black_tree, values, -1);
    test_erase(red_black_tree, values, 1);
    test_erase(red_black_tree, values, 3);
    test_erase(red_black_tree, values, 5);
    test_erase(red_black_tree, values, 7);
    test_erase(red_black_tree, values, 17);
    test_erase(red_black_tree, values, 19);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, 0);
    test_erase(red_black_copy, values, 2);
    test_value_insert(values, 2);
    test_value_insert(values, 0);
    red_black_copy = red_black_tree;
    test_tree_container(red_black_copy, values);
    test_erase(red_black_copy, values, -2);
    test_erase(red_black_copy, values, 0);
}

#endif  // LIBS_TREE_NODE_TEST_RED_BLACK_TREE_HPP_INCLUDED

