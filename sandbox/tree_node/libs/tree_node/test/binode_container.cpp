// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <boost/tree_node/balancer/red_black.hpp>
#include <boost/tree_node/balancer/adelson_velskii_landis.hpp>
#include <boost/tree_node/container/binode.hpp>
#include <boost/test/minimal.hpp>
#include "type_definitions.hpp"
#include "container_functions.hpp"

typedef boost::tree_node::binode_container<RedBlackNodeGen,boost::int32_t>
        RedBlackTreeSequence;

void
    test_push_front(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.push_front(t);
    std::cout << std::endl << "After red_black_tree.push_front(" << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.push_front(t);
    test_tree_container(red_black_tree, values);
}

void
    test_push_back(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.push_back(t);
    std::cout << std::endl << "After red_black_tree.push_back(" << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.push_back(t);
    test_tree_container(red_black_tree, values);
}

void
    test_pop_front(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
    )
{
    red_black_tree.pop_front();
    std::cout << std::endl << "After red_black_tree.pop_front():";
    test_red_black_node(*red_black_tree.data());
    values.pop_front();
    test_tree_container(red_black_tree, values);
}

void
    test_pop_back(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
    )
{
    red_black_tree.pop_back();
    std::cout << std::endl << "After red_black_tree.pop_back():";
    test_red_black_node(*red_black_tree.data());
    values.pop_back();
    test_tree_container(red_black_tree, values);
}

void
    test_insert(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::size_type index
      , RedBlackTreeSequence::value_type t
    )
{
    red_black_tree.insert(red_black_tree.begin() + index, t);
    std::cout << std::endl << "After red_black_tree.insert[" << index << "](";
    std::cout << t << "):";
    test_red_black_node(*red_black_tree.data());
    values.insert(values.begin() + index, t);
    test_tree_container(red_black_tree, values);
}

void
    test_erase(
        RedBlackTreeSequence& red_black_tree
      , ValueSequence& values
      , RedBlackTreeSequence::size_type index
    )
{
    RedBlackTreeSequence::iterator tree_itr = red_black_tree.erase(
        red_black_tree.begin() + index
    );

    if (index == red_black_tree.size())
    {
        BOOST_CHECK(tree_itr == red_black_tree.end());
    }
    else
    {
        BOOST_CHECK(test_tree_values(*tree_itr, red_black_tree[index]));
    }

    std::cout << std::endl << "After red_black_tree.erase[" << index << "]:";
    test_red_black_node(*red_black_tree.data());
    values.erase(values.begin() + index);
    test_tree_container(red_black_tree, values);
}

typedef boost::tree_node::binode_container<
            AVLNodeGen
          , boost::int32_t
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeSequence;

void
    test_push_front(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.push_front(t);
    std::cout << std::endl << "After avl_tree.push_front(" << t << "):";
    test_avl_node(*avl_tree.data());
    values.push_front(t);
    test_tree_container(avl_tree, values);
}

void
    test_push_back(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.push_back(t);
    std::cout << std::endl << "After avl_tree.push_back(" << t << "):";
    test_avl_node(*avl_tree.data());
    values.push_back(t);
    test_tree_container(avl_tree, values);
}

void test_pop_front(AVLTreeSequence& avl_tree, ValueSequence& values)
{
    avl_tree.pop_front();
    std::cout << std::endl << "After avl_tree.pop_front():";
    test_avl_node(*avl_tree.data());
    values.pop_front();
    test_tree_container(avl_tree, values);
}

void test_pop_back(AVLTreeSequence& avl_tree, ValueSequence& values)
{
    avl_tree.pop_back();
    std::cout << std::endl << "After avl_tree.pop_back():";
    test_avl_node(*avl_tree.data());
    values.pop_back();
    test_tree_container(avl_tree, values);
}

void
    test_insert(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::size_type index
      , AVLTreeSequence::value_type t
    )
{
    avl_tree.insert(avl_tree.begin() + index, t);
    std::cout << std::endl << "After avl_tree.insert[" << index << "](";
    std::cout << t << "):";
    test_avl_node(*avl_tree.data());
    values.insert(values.begin() + index, t);
    test_tree_container(avl_tree, values);
}

void
    test_erase(
        AVLTreeSequence& avl_tree
      , ValueSequence& values
      , AVLTreeSequence::size_type index
    )
{
    AVLTreeSequence::iterator tree_itr = avl_tree.erase(
        avl_tree.begin() + index
    );

    if (index == avl_tree.size())
    {
        BOOST_CHECK(tree_itr == avl_tree.end());
    }
    else
    {
        BOOST_CHECK(test_tree_values(*tree_itr, avl_tree[index]));
    }

    std::cout << std::endl << "After avl_tree.erase[" << index << "]:";
    test_avl_node(*avl_tree.data());
    values.erase(values.begin() + index);
    test_tree_container(avl_tree, values);
}

#include "sequence.hpp"

void test_red_black_sequence()
{
    RedBlackTreeSequence red_black_tree;
    ValueSequence values;

    test_sequence(red_black_tree, values);

    RedBlackTreeSequence red_black_copy;
    ValueSequence value_copies;

    for (
        RedBlackTreeSequence::size_type index = 0;
        index + 1 < red_black_tree.size();
        ++index
    )
    {
        red_black_copy = red_black_tree;
        value_copies = values;

        if (!index)
        {
            test_tree_container(red_black_copy, value_copies);
        }

        test_erase(red_black_copy, value_copies, index);

        switch (index)
        {
            case 2:
            {
                test_erase(red_black_copy, value_copies, 1);
                break;
            }

            case 4:
            {
                test_erase(red_black_copy, value_copies, 4);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void test_avl_sequence()
{
    AVLTreeSequence avl_tree;
    ValueSequence values;

    test_sequence(avl_tree, values);

    AVLTreeSequence avl_copy;
    ValueSequence value_copies;

    for (
        AVLTreeSequence::size_type index = 0;
        index + 1 < avl_tree.size();
        ++index
    )
    {
        avl_copy = avl_tree;
        value_copies = values;

        if (!index)
        {
            test_tree_container(avl_copy, value_copies);
        }

        test_erase(avl_copy, value_copies, index);

        switch (index)
        {
            case 0:
            {
                test_erase(avl_copy, value_copies, 0);
                break;
            }

            case 1:
            {
                test_erase(avl_copy, value_copies, 1);
                break;
            }

            case 3:
            {
                test_erase(avl_copy, value_copies, 5);
                break;
            }

            case 4:
            {
                test_erase(avl_copy, value_copies, 4);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

int test_main(int argc, char** argv)
{
    test_red_black_sequence();
    test_avl_sequence();
    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

