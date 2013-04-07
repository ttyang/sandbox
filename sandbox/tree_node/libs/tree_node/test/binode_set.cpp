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
#include <boost/tree_node/container/binode_associative.hpp>
#include <boost/test/minimal.hpp>
#include "type_definitions.hpp"
#include "container_functions.hpp"

void test_value_insert(ValueSet& values, ValueSet::key_type const& key)
{
    values.insert(key);
}

typedef boost::tree_node::binode_set<
            boost::int32_t
          , RedBlackNodeGen
          , boost::tree_node::red_black_balancer
        >
        RedBlackTreeSet;

void
    test_insert(
        RedBlackTreeSet& red_black_tree
      , ValueSet& values
      , RedBlackTreeSet::key_type const& key
    )
{
    std::pair<RedBlackTreeSet::iterator,bool> p = red_black_tree.insert(key);

    if (values.insert(key).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After inserting " << key << ':';
        test_red_black_node(*red_black_tree.data());
        BOOST_CHECK(*p.first == key);
        BOOST_CHECK(p.first == red_black_tree.find(key));
        BOOST_CHECK(!red_black_tree.empty());
        test_tree_container(red_black_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        RedBlackTreeSet& red_black_tree
      , ValueSet& values
      , RedBlackTreeSet::key_type const& key
    )
{
    BOOST_CHECK(red_black_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (red_black_tree.empty())
    {
        std::cout << ", red_black_tree is empty." << std::endl;
    }
    {
        std::cout << ':';
        test_red_black_node(*red_black_tree.data());
    }

    test_tree_container(red_black_tree, values);
}

#include "red_black_tree.hpp"

typedef boost::tree_node::binode_set<
            boost::int32_t
          , AVLNodeGen
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeSet;

void
    test_insert(
        AVLTreeSet& avl_tree
      , ValueSet& values
      , AVLTreeSet::key_type const& key
    )
{
    std::pair<AVLTreeSet::iterator,bool> p = avl_tree.insert(key);

    if (values.insert(key).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After inserting " << key << ':';
        test_avl_node(*avl_tree.data());
        BOOST_CHECK(*p.first == key);
        BOOST_CHECK(p.first == avl_tree.find(key));
        BOOST_CHECK(!avl_tree.empty());
        test_tree_container(avl_tree, values);
    }
    else
    {
        BOOST_CHECK(!p.second);
    }
}

void
    test_erase(
        AVLTreeSet& avl_tree
      , ValueSet& values
      , AVLTreeSet::key_type const& key
    )
{
    BOOST_CHECK(avl_tree.erase(key) == values.erase(key));
    std::cout << std::endl << "After erasing " << key;

    if (avl_tree.empty())
    {
        std::cout << ", avl_tree is empty." << std::endl;
    }
    else
    {
        std::cout << ':';
        test_avl_node(*avl_tree.data());
    }

    test_tree_container(avl_tree, values);
}

#include "avl_tree.hpp"

int test_main(int argc, char** argv)
{
    test_red_black_tree<RedBlackTreeSet,ValueSet>();
    test_avl_tree<AVLTreeSet,ValueSet>();
    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

