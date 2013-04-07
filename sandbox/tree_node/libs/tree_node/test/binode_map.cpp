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

void test_value_insert(ValueMap& values, ValueMap::key_type const& key)
{
    values.insert(ValueMap::value_type(key, key));
}

typedef boost::tree_node::binode_map<
            boost::int32_t
          , boost::int32_t
          , RedBlackNodeGen
          , boost::tree_node::red_black_balancer
        >
        RedBlackTreeMap;

void
    test_insert(
        RedBlackTreeMap& red_black_tree
      , ValueMap& values
      , RedBlackTreeMap::key_type const& key
    )
{
    std::pair<RedBlackTreeMap::iterator,bool> p = red_black_tree.emplace(
        key
      , key
    );

    if (values.insert(ValueMap::value_type(key, key)).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After emplacing " << key << ':';
        test_red_black_node(*red_black_tree.data());
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(p.first->second == key);
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
        RedBlackTreeMap& red_black_tree
      , ValueMap& values
      , RedBlackTreeMap::key_type const& key
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

typedef boost::tree_node::binode_map<
            boost::int32_t
          , boost::int32_t
          , AVLNodeGen
          , boost::tree_node::adelson_velskii_landis_balancer
        >
        AVLTreeMap;

void
    test_insert(
        AVLTreeMap& avl_tree
      , ValueMap& values
      , AVLTreeMap::key_type const& key
    )
{
    std::pair<AVLTreeMap::iterator,bool> p = avl_tree.emplace(key, key);

    if (values.insert(ValueMap::value_type(key, key)).second)
    {
        BOOST_CHECK(p.second);
        std::cout << std::endl << "After emplacing " << key << ':';
        test_avl_node(*avl_tree.data());
        BOOST_CHECK(p.first->first == key);
        BOOST_CHECK(p.first->second == key);
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
        AVLTreeMap& avl_tree
      , ValueMap& values
      , AVLTreeMap::key_type const& key
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
    test_red_black_tree<RedBlackTreeMap,ValueMap>();
    test_avl_tree<AVLTreeMap,ValueMap>();
    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

