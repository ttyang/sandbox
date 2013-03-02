// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <boost/tuple/tuple.hpp>
#include <boost/typeof/boost/rational.hpp>
#include <boost/typeof/boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/intrinsic/value_at_key.hpp>
#include <boost/typeof/boost/tree_node/with_count.hpp>
#include <boost/typeof/boost/tree_node/with_height.hpp>
#include <boost/typeof/boost/tree_node/with_position.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/typeof/boost/tree_node/with_accumulation.hpp>
#endif

#include "../example/type_definitions.hpp"
#include "iterator_functions.hpp"

typedef boost::emplace_function_gen<boost::dequeS>::type
        Emplacer;

#include <boost/typeof/boost/tree_node/binary_node.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
typedef boost::tree_node::with_accumulation<
            boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                    boost::tree_node::with_position_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                            boost::tree_node::with_count_base_gen<
                                boost::tree_node::with_accumulation_base_gen<
                                    boost::tree_node::binary_node_base_gen<>
                                >
                            >
                          , AccuAccuKey
                        >
                    >
                  , AccuCountKey
                >
            >
          , boost::rational<long>
          , void
          , AccuHeightKey
        >
        ANode;
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
typedef boost::tree_node::with_height<
            boost::tree_node::with_position_base_gen<
                boost::tree_node::with_count_base_gen<
                    boost::tree_node::binary_node_base_gen<>
                >
            >
          , boost::rational<long>
        >
        ANode;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::data_key
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::height_key
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::count_key
                >::type
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::accumulation_key<>
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuHeightKey
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuCountKey
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuAccuKey
                >::type
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
            >
        >::type
        Values;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::data_key
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::height_key
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::count_key
                >::type
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , boost::tree_node::accumulation_key<>
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuHeightKey
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuCountKey
                >::type
              , boost::tree_node::result_of::value_at_key<
                    ANode const
                  , AccuAccuKey
                >::type
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
            >
        >::type
        DFValues;

int test_main(int argc, char** argv)
{
    ANode a_root(5);

    BOOST_CHECK(
        !a_root.get_parent_ptr()
//      , "Parent member uninitialized."
    );

    for (
        boost::tree_node::breadth_first_iterator<ANode> itr(a_root);
        itr;
        ++itr
    )
    {
        ANode::traits::data_type const& data = get(
            *itr
          , boost::tree_node::data_key()
        );

        if (1 < data)
        {
            ANode::iterator child_itr(itr->emplace_left(data - 2));
            ANode::const_pointer const_child(&*child_itr);

            BOOST_CHECK(
                child_itr->get_parent_ptr() == &*itr
//              , "Ctor not linking child to parent."
            );
            BOOST_CHECK(
                itr->get_left_child_ptr() == &*child_itr
//              , "Ctor not linking parent to child."
            );
            BOOST_CHECK(
                child_itr->get_parent_ptr() == const_child->get_parent_ptr()
//              , "Why are these pointers different?"
            );
            BOOST_CHECK(
                get(
                    *child_itr
                  , boost::tree_node::position_key()
                ) == child_itr
//              , "Position iterator incorrect."
            );

            child_itr = itr->emplace_right(data - 1);
            const_child = &*child_itr;

            BOOST_CHECK(
                child_itr->get_parent_ptr() == &*itr
//              , "Ctor not linking child to parent."
            );
            BOOST_CHECK(
                itr->get_right_child_ptr() == &*child_itr
//              , "Ctor not linking parent to child."
            );
            BOOST_CHECK(
                child_itr->get_parent_ptr() == const_child->get_parent_ptr()
//              , "Why are these pointers different?"
            );
            BOOST_CHECK(
                get(
                    *child_itr
                  , boost::tree_node::position_key()
                ) == child_itr
//              , "Position iterator incorrect."
            );
        }
    }

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 15, 26, 3, 51, boost::rational<long>(68, 15))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 4, 15, 26, 3, 51, boost::rational<long>(68, 15))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (5, 4, 15, 26, 3, 51, boost::rational<long>(68, 15));
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 15, 26, 3, 51, boost::rational<long>(68, 15))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 15,
            26, 3, 51, boost::rational<long>(68, 15))
                (boost::tree_node::pre_order_traversal, 3, 2, 5,
                7, 1, 11, boost::rational<long>(12, 5))
                    (boost::tree_node::pre_order_traversal, 1, 0, 1,
                    1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 1, 0, 1,
                    1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 5,
                7, 1, 11, boost::rational<long>(12, 5))
                (boost::tree_node::pre_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::pre_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                (boost::tree_node::post_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
            (boost::tree_node::post_order_traversal, 5, 4, 15,
            26, 3, 51, boost::rational<long>(68, 15));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 15)(3, 2, 5)(4, 3, 9)(1, 0, 1)(2, 1, 3)(2, 1, 3)(3, 2, 5)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1);
        emplacer[pre_vals]
            (5, 4, 15)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 9)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 3, 9)
            (5, 4, 15);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 4, 15)(0, 0, 1)
            (2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)
            (1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 15)
                (boost::tree_node::pre_order_traversal, 3, 2, 5)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::pre_order_traversal, 4, 3, 9)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 3, 9)
            (boost::tree_node::post_order_traversal, 5, 4, 15);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    {
        ANode a_copy(a_root);
        boost::tree_node::breadth_first_iterator<ANode const>
            bf_root_itr(a_root), bf_copy_itr(a_copy);
        boost::tree_node::breadth_first_descendant_iterator<ANode const>
            bf_d_root_itr(a_root), bf_d_copy_itr(a_copy);
        boost::tree_node::pre_order_iterator<ANode const>
            pre_root_itr(a_root), pre_copy_itr(a_copy);
        boost::tree_node::pre_order_descendant_iterator<ANode const>
            pre_d_root_itr(a_root), pre_d_copy_itr(a_copy);
        boost::tree_node::post_order_iterator<ANode const>
            post_root_itr(a_root), post_copy_itr(a_copy);
        boost::tree_node::post_order_descendant_iterator<ANode const>
            post_d_root_itr(a_root), post_d_copy_itr(a_copy);
        boost::tree_node::in_order_iterator<ANode const>
            in_root_itr(a_root), in_copy_itr(a_copy);
        boost::tree_node::depth_first_iterator<ANode const>
            df_root_itr(a_root), df_copy_itr(a_copy);
        boost::tree_node::depth_first_descendant_iterator<ANode const>
            df_d_root_itr(a_root), df_d_copy_itr(a_copy);

        BOOST_CHECK(test_node_copies(bf_root_itr, bf_copy_itr));
        BOOST_CHECK(test_node_copies(bf_d_root_itr, bf_d_copy_itr));
        BOOST_CHECK(test_node_copies(pre_root_itr, pre_copy_itr));
        BOOST_CHECK(test_node_copies(pre_d_root_itr, pre_d_copy_itr));
        BOOST_CHECK(test_node_copies(post_root_itr, post_copy_itr));
        BOOST_CHECK(test_node_copies(post_d_root_itr, post_d_copy_itr));
        BOOST_CHECK(test_node_copies(in_root_itr, in_copy_itr));
        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));
        BOOST_CHECK(test_node_copies(df_d_root_itr, df_d_copy_itr));
    }

    {
        ANode::pointer p(
            a_root.get_left_child_ptr()->get_right_child_ptr()
        );
        ANode::iterator a_child_itr = p->insert_left(a_root);
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 7, 30, 52, 6, 150, boost::rational<long>(107, 15))
            (3, 6, 20, 33, 5, 95, boost::rational<long>(33, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 18, 29, 4, 74, boost::rational<long>(49, 9))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 7, 30, 52, 6, 150, boost::rational<long>(107, 15))
            (3, 6, 20, 33, 5, 95, boost::rational<long>(33, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 18, 29, 4, 74, boost::rational<long>(49, 9))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 18, 29, 4, 74, boost::rational<long>(49, 9))
            (3, 6, 20, 33, 5, 95, boost::rational<long>(33, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (5, 7, 30, 52, 6, 150, boost::rational<long>(107, 15));
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 6, 20, 33, 5, 95, boost::rational<long>(33, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 18, 29, 4, 74, boost::rational<long>(49, 9))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 7, 30, 52, 6, 150, boost::rational<long>(107, 15))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 7, 30,
            52, 6, 150, boost::rational<long>(107, 15))
                (boost::tree_node::pre_order_traversal, 3, 6, 20,
                33, 5, 95, boost::rational<long>(33, 5))
                    (boost::tree_node::pre_order_traversal, 1, 0, 1,
                    1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 1, 0, 1,
                    1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::pre_order_traversal, 2, 5, 18,
                    29, 4, 74, boost::rational<long>(49, 9))
                        (boost::tree_node::pre_order_traversal, 5, 4, 16,
                        26, 3, 55, boost::rational<long>(17, 4))
                            (boost::tree_node::pre_order_traversal, 3, 2, 6,
                            7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::post_order_traversal, 3, 2, 6,
                            7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 4, 3, 9,
                            14, 2, 25, boost::rational<long>(10, 3))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 3, 2, 5,
                            7, 1, 11, boost::rational<long>(12, 5))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::post_order_traversal, 3, 2, 5,
                            7, 1, 11, boost::rational<long>(12, 5))
                            (boost::tree_node::post_order_traversal, 4, 3, 9,
                            14, 2, 25, boost::rational<long>(10, 3))
                        (boost::tree_node::post_order_traversal, 5, 4, 16,
                        26, 3, 55, boost::rational<long>(17, 4))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 5, 18,
                    29, 4, 74, boost::rational<long>(49, 9))
                (boost::tree_node::post_order_traversal, 3, 6, 20,
                33, 5, 95, boost::rational<long>(33, 5))
                (boost::tree_node::pre_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::pre_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                (boost::tree_node::post_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
            (boost::tree_node::post_order_traversal, 5, 7, 30,
            52, 6, 150, boost::rational<long>(107, 15));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 7, 30)(3, 6, 20)(4, 3, 9)(1, 0, 1)(2, 5, 18)(2, 1, 3)(3, 2, 5)
            (5, 4, 16)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (4, 3, 9)(0, 0, 1)(1, 0, 1)(1, 1, 2)(2, 1, 3)(2, 1, 3)(3, 2, 5)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 7, 30)(3, 6, 20)(1, 0, 1)(2, 5, 18)(5, 4, 16)(3, 2, 6)(1, 1, 2)
            (0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 9)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(1, 0, 1)
            (4, 3, 9)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 5)(4, 3, 9)(5, 4, 16)(1, 0, 1)(2, 5, 18)(3, 6, 20)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)
            (4, 3, 9)(5, 7, 30);
        emplacer[in_vals]
            (1, 0, 1)(3, 6, 20)(0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(5, 4, 16)(0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(2, 5, 18)(1, 0, 1)(5, 7, 30)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)
            (2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 7, 30)
                (boost::tree_node::pre_order_traversal, 3, 6, 20)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 5, 18)
                        (boost::tree_node::pre_order_traversal, 5, 4, 16)
                            (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 4, 3, 9)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 3, 2, 5)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 5)
                            (boost::tree_node::post_order_traversal, 4, 3, 9)
                        (boost::tree_node::post_order_traversal, 5, 4, 16)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 5, 18)
                (boost::tree_node::post_order_traversal, 3, 6, 20)
                (boost::tree_node::pre_order_traversal, 4, 3, 9)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 3, 9)
            (boost::tree_node::post_order_traversal, 5, 7, 30);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );

        a_root = *a_child_itr;
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        in_vals.clear();
        df_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 16,
            26, 3, 55, boost::rational<long>(17, 4))
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::pre_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                (boost::tree_node::post_order_traversal, 4, 3, 9,
                14, 2, 25, boost::rational<long>(10, 3))
            (boost::tree_node::post_order_traversal, 5, 4, 16,
            26, 3, 55, boost::rational<long>(17, 4));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 16)(3, 2, 6)(4, 3, 9)(1, 1, 2)(2, 1, 3)(2, 1, 3)(3, 2, 5)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 4, 16)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 3, 9)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)
            (4, 3, 9)(5, 4, 16);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 4, 16)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)
            (2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 16)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 1, 2)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 3, 9)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 3, 9)
            (boost::tree_node::post_order_traversal, 5, 4, 16);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );

        *(p = a_root.get_right_child_ptr()) = a_root;
        test_node<a_node_case>(
            *p
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );

        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        in_vals.clear();
        df_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 23, 38, 4, 92, boost::rational<long>(118, 23))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 23, 38, 4, 92, boost::rational<long>(118, 23))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (5, 5, 23, 38, 4, 92, boost::rational<long>(118, 23));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 5, 23, 38, 4, 92, boost::rational<long>(118, 23))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 16, 26, 3, 55, boost::rational<long>(17, 4))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 9, 14, 2, 25, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 23,
            38, 4, 92, boost::rational<long>(118, 23))
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 5, 4, 16,
                26, 3, 55, boost::rational<long>(17, 4))
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 1, 1, 2,
                        1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 1, 1, 2,
                        1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 4, 3, 9,
                    14, 2, 25, boost::rational<long>(10, 3))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 3, 2, 5,
                        7, 1, 11, boost::rational<long>(12, 5))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 5,
                        7, 1, 11, boost::rational<long>(12, 5))
                    (boost::tree_node::post_order_traversal, 4, 3, 9,
                    14, 2, 25, boost::rational<long>(10, 3))
                (boost::tree_node::post_order_traversal, 5, 4, 16,
                26, 3, 55, boost::rational<long>(17, 4))
            (boost::tree_node::post_order_traversal, 5, 5, 23,
            38, 4, 92, boost::rational<long>(118, 23));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 23)(3, 2, 6)(5, 4, 16)(1, 1, 2)(2, 1, 3)(3, 2, 6)(4, 3, 9)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(1, 1, 2)(2, 1, 3)(2, 1, 3)(3, 2, 5)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 23)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (5, 4, 16)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 3, 9)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)
            (1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 3, 9)
            (5, 4, 16)(5, 5, 23);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 23)
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 4, 16)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)
            (2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 23)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 1, 2)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 5, 4, 16)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 4, 3, 9)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 3, 2, 5)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 5)
                    (boost::tree_node::post_order_traversal, 4, 3, 9)
                (boost::tree_node::post_order_traversal, 5, 4, 16)
            (boost::tree_node::post_order_traversal, 5, 5, 23);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    a_root.get_right_child_ptr()->rotate_left();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 23, 38, 4, 93, boost::rational<long>(119, 23))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 4, 16, 26, 3, 56, boost::rational<long>(69, 16))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 23, 38, 4, 93, boost::rational<long>(119, 23))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 16, 26, 3, 56, boost::rational<long>(69, 16))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (4, 4, 16, 26, 3, 56, boost::rational<long>(69, 16))
            (5, 5, 23, 38, 4, 93, boost::rational<long>(119, 23));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 5, 23, 38, 4, 93, boost::rational<long>(119, 23))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 16, 26, 3, 56, boost::rational<long>(69, 16))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 5, 7, 1, 11, boost::rational<long>(12, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 23,
            38, 4, 93, boost::rational<long>(119, 23))
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 4, 16,
                26, 3, 56, boost::rational<long>(69, 16))
                    (boost::tree_node::pre_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                    (boost::tree_node::pre_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 5,
                    7, 1, 11, boost::rational<long>(12, 5))
                (boost::tree_node::post_order_traversal, 4, 4, 16,
                26, 3, 56, boost::rational<long>(69, 16))
            (boost::tree_node::post_order_traversal, 5, 5, 23,
            38, 4, 93, boost::rational<long>(119, 23));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 23)(3, 2, 6)(4, 4, 16)(1, 1, 2)(2, 1, 3)(5, 3, 10)(3, 2, 5)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(3, 2, 6)(2, 1, 3)(1, 0, 1)(2, 1, 3)
            (1, 1, 2)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 23)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 4, 16)(5, 3, 10)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)
            (1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(5, 3, 10)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)
            (4, 4, 16)(5, 5, 23);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 23)
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 10)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 16)(1, 0, 1)(3, 2, 5)(0, 0, 1)
            (2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 23)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 1, 2)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 4, 16)
                    (boost::tree_node::pre_order_traversal, 5, 3, 10)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 10)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 4, 16)
            (boost::tree_node::post_order_traversal, 5, 5, 23);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    {
        ANode::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator p_child_itr(p->emplace_right());
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

        put(*p_child_itr, boost::tree_node::data_key(), 7);
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24,
            45, 4, 100, boost::rational<long>(25, 4))
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
                    (boost::tree_node::pre_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                    (boost::tree_node::pre_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                    (boost::tree_node::post_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                (boost::tree_node::post_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
            (boost::tree_node::post_order_traversal, 5, 5, 24,
            45, 4, 100, boost::rational<long>(25, 4));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24)(3, 2, 6)(4, 4, 17)(1, 1, 2)(2, 1, 3)(5, 3, 10)(3, 3, 6)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(3, 2, 6)(2, 1, 3)(1, 0, 1)(7, 2, 4)
            (1, 1, 2)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 24)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 4, 17)(5, 3, 10)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 3, 6)(1, 0, 1)(7, 2, 4)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)
            (1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(5, 3, 10)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(7, 2, 4)
            (3, 3, 6)(4, 4, 17)(5, 5, 24);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 24)
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 10)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 17)(1, 0, 1)(3, 3, 6)(7, 2, 4)
            (0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 1, 2)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 4, 17)
                    (boost::tree_node::pre_order_traversal, 5, 3, 10)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 10)
                    (boost::tree_node::pre_order_traversal, 3, 3, 6)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 2, 4)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 7, 2, 4)
                    (boost::tree_node::post_order_traversal, 3, 3, 6)
                (boost::tree_node::post_order_traversal, 4, 4, 17)
            (boost::tree_node::post_order_traversal, 5, 5, 24);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    a_root.get_left_child_ptr()->rotate_right();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24, 45, 4, 102, boost::rational<long>(155, 24))
            (1, 1, 6, 7, 2, 16, boost::rational<long>(17, 6))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 4, 6, 1, 9, boost::rational<long>(5, 2))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 24, 45, 4, 102, boost::rational<long>(155, 24))
            (1, 1, 6, 7, 2, 16, boost::rational<long>(17, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 4, 6, 1, 9, boost::rational<long>(5, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 4, 6, 1, 9, boost::rational<long>(5, 2))
            (1, 1, 6, 7, 2, 16, boost::rational<long>(17, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 5, 24, 45, 4, 102, boost::rational<long>(155, 24));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 6, 7, 2, 16, boost::rational<long>(17, 6))
            (3, 2, 4, 6, 1, 9, boost::rational<long>(5, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 5, 24, 45, 4, 102, boost::rational<long>(155, 24))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24,
            45, 4, 102, boost::rational<long>(155, 24))
                (boost::tree_node::pre_order_traversal, 1, 1, 6,
                7, 2, 16, boost::rational<long>(17, 6))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::pre_order_traversal, 3, 2, 4,
                    6, 1, 9, boost::rational<long>(5, 2))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 3, 2, 4,
                    6, 1, 9, boost::rational<long>(5, 2))
                (boost::tree_node::post_order_traversal, 1, 1, 6,
                7, 2, 16, boost::rational<long>(17, 6))
                (boost::tree_node::pre_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
                    (boost::tree_node::pre_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                    (boost::tree_node::pre_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                    (boost::tree_node::post_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                (boost::tree_node::post_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
            (boost::tree_node::post_order_traversal, 5, 5, 24,
            45, 4, 102, boost::rational<long>(155, 24));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24)(1, 1, 6)(4, 4, 17)(0, 0, 1)(3, 2, 4)(5, 3, 10)(3, 3, 6)
            (2, 1, 3)(3, 2, 6)(2, 1, 3)(1, 0, 1)(7, 2, 4)(0, 0, 1)(1, 0, 1)
            (1, 1, 2)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 24)(1, 1, 6)(0, 0, 1)(3, 2, 4)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 4, 17)(5, 3, 10)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 3, 6)(1, 0, 1)(7, 2, 4)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 4)(1, 1, 6)(0, 0, 1)
            (1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(5, 3, 10)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(7, 2, 4)
            (3, 3, 6)(4, 4, 17)(5, 5, 24);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 6)(3, 2, 4)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 24)
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 10)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 17)(1, 0, 1)(3, 3, 6)(7, 2, 4)
            (0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24)
                (boost::tree_node::pre_order_traversal, 1, 1, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 3, 2, 4)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 4)
                (boost::tree_node::post_order_traversal, 1, 1, 6)
                (boost::tree_node::pre_order_traversal, 4, 4, 17)
                    (boost::tree_node::pre_order_traversal, 5, 3, 10)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 10)
                    (boost::tree_node::pre_order_traversal, 3, 3, 6)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 2, 4)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 7, 2, 4)
                    (boost::tree_node::post_order_traversal, 3, 3, 6)
                (boost::tree_node::post_order_traversal, 4, 4, 17)
            (boost::tree_node::post_order_traversal, 5, 5, 24);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    a_root.get_left_child_ptr()->rotate_left();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4));
        emplacer[in_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 5, 24, 45, 4, 100, boost::rational<long>(25, 4))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24,
            45, 4, 100, boost::rational<long>(25, 4))
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 1, 1, 2,
                    1, 0, 3, boost::rational<long>(1, 2))
                    (boost::tree_node::pre_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                    (boost::tree_node::post_order_traversal, 2, 1, 3,
                    3, 0, 5, boost::rational<long>(4, 3))
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 14, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
                    (boost::tree_node::pre_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                    (boost::tree_node::pre_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                    (boost::tree_node::post_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                (boost::tree_node::post_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
            (boost::tree_node::post_order_traversal, 5, 5, 24,
            45, 4, 100, boost::rational<long>(25, 4));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 24)(3, 2, 6)(4, 4, 17)(1, 1, 2)(2, 1, 3)(5, 3, 10)(3, 3, 6)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(3, 2, 6)(2, 1, 3)(1, 0, 1)(7, 2, 4)
            (1, 1, 2)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 24)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 4, 17)(5, 3, 10)(3, 2, 6)(1, 1, 2)(0, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 3, 6)(1, 0, 1)(7, 2, 4)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)
            (1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(5, 3, 10)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(7, 2, 4)
            (3, 3, 6)(4, 4, 17)(5, 5, 24);
        emplacer[in_vals]
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 24)
            (0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 10)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 17)(1, 0, 1)(3, 3, 6)(7, 2, 4)
            (0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 24)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 1, 1, 2)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 1, 2)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 4, 17)
                    (boost::tree_node::pre_order_traversal, 5, 3, 10)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 10)
                    (boost::tree_node::pre_order_traversal, 3, 3, 6)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 2, 4)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 7, 2, 4)
                    (boost::tree_node::post_order_traversal, 3, 3, 6)
                (boost::tree_node::post_order_traversal, 4, 4, 17)
            (boost::tree_node::post_order_traversal, 5, 5, 24);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    a_root.begin()->clear();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 19, 41, 4, 82, boost::rational<long>(137, 19))
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 5, 19, 41, 4, 82, boost::rational<long>(137, 19))
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (5, 5, 19, 41, 4, 82, boost::rational<long>(137, 19));
        emplacer[in_vals]
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (5, 5, 19, 41, 4, 82, boost::rational<long>(137, 19))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 1, 2, 1, 0, 3, boost::rational<long>(1, 2))
            (3, 2, 6, 7, 1, 14, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 3, 10, 15, 2, 29, boost::rational<long>(31, 10))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 4, 17, 33, 3, 62, boost::rational<long>(93, 17))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 3, 6, 14, 2, 16, boost::rational<long>(29, 6))
            (7, 2, 4, 10, 1, 9, boost::rational<long>(7, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 19,
            41, 4, 82, boost::rational<long>(137, 19))
                (boost::tree_node::pre_order_traversal, 3, 0, 1,
                3, 0, 1, boost::rational<long>(3, 1))
                (boost::tree_node::post_order_traversal, 3, 0, 1,
                3, 0, 1, boost::rational<long>(3, 1))
                (boost::tree_node::pre_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
                    (boost::tree_node::pre_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 1, 1, 2,
                            1, 0, 3, boost::rational<long>(1, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 14, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 1, 3,
                        3, 0, 5, boost::rational<long>(4, 3))
                    (boost::tree_node::post_order_traversal, 5, 3, 10,
                    15, 2, 29, boost::rational<long>(31, 10))
                    (boost::tree_node::pre_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                            (boost::tree_node::pre_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 2, 1, 3,
                            3, 0, 5, boost::rational<long>(4, 3))
                        (boost::tree_node::post_order_traversal, 7, 2, 4,
                        10, 1, 9, boost::rational<long>(7, 2))
                    (boost::tree_node::post_order_traversal, 3, 3, 6,
                    14, 2, 16, boost::rational<long>(29, 6))
                (boost::tree_node::post_order_traversal, 4, 4, 17,
                33, 3, 62, boost::rational<long>(93, 17))
            (boost::tree_node::post_order_traversal, 5, 5, 19,
            41, 4, 82, boost::rational<long>(137, 19));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 5, 19)(3, 0, 1)(4, 4, 17)(5, 3, 10)(3, 3, 6)(3, 2, 6)(2, 1, 3)
            (1, 0, 1)(7, 2, 4)(1, 1, 2)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 19)(3, 0, 1)(4, 4, 17)(5, 3, 10)(3, 2, 6)(1, 1, 2)(0, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 3, 6)
            (1, 0, 1)(7, 2, 4)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (3, 0, 1)(0, 0, 1)(1, 1, 2)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 3, 10)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(7, 2, 4)(3, 3, 6)(4, 4, 17)(5, 5, 19);
        emplacer[in_vals]
            (3, 0, 1)(5, 5, 19)(0, 0, 1)(1, 1, 2)(3, 2, 6)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(5, 3, 10)(0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 17)(1, 0, 1)
            (3, 3, 6)(7, 2, 4)(0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 19)
                (boost::tree_node::pre_order_traversal, 3, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 0, 1)
                (boost::tree_node::pre_order_traversal, 4, 4, 17)
                    (boost::tree_node::pre_order_traversal, 5, 3, 10)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 1, 2)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 10)
                    (boost::tree_node::pre_order_traversal, 3, 3, 6)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 2, 4)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 7, 2, 4)
                    (boost::tree_node::post_order_traversal, 3, 3, 6)
                (boost::tree_node::post_order_traversal, 4, 4, 17)
            (boost::tree_node::post_order_traversal, 5, 5, 19);
#endif  // BOOST_NO_SFINAE
        test_node<a_node_case>(
            a_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::binary_node_base_gen<>
              , DataMap
              , void
              , AccuYourUintKey
            >
            FNode;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_uint
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_char
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        FNode const
                      , AccuYourUintKey
                    >::type
                >
            >::type
            MoreValues;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_uint
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_char
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        FNode const
                      , AccuYourUintKey
                    >::type
                >
            >::type
            DFMoreValues;

    FNode f_root(
        boost::fusion::make_pair<example_keys::your_uint>(5)
      , boost::fusion::make_pair<example_keys::your_char>('5')
    );

    for (
        boost::tree_node::breadth_first_iterator<FNode> itr(f_root);
        itr;
        ++itr
    )
    {
        boost::tree_node::result_of::value_at_key<
            FNode const
          , example_keys::your_uint
        >::type data = boost::tree_node::get<example_keys::your_uint>(*itr);

        if (1 < data)
        {
            --data;
            itr->emplace_right(
                boost::fusion::make_pair<example_keys::your_uint>(data)
              , boost::fusion::make_pair<example_keys::your_char>('0' + data)
            );
            --data;
            itr->emplace_left(
                boost::fusion::make_pair<example_keys::your_uint>(data)
              , boost::fusion::make_pair<example_keys::your_char>('0' + data)
            );
        }
    }

    {
        MoreValues bf_vals, pre_vals, post_vals, in_vals;
        DFMoreValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (5, '5', 26)(3, '3', 7)(4, '4', 14)(1, '1', 1)(2, '2', 3)
            (2, '2', 3)(3, '3', 7)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[pre_vals]
            (5, '5', 26)(3, '3', 7)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(4, '4', 14)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (3, '3', 7)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[post_vals]
            (1, '1', 1)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 7)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(3, '3', 7)(4, '4', 14)(5, '5', 26);
        emplacer[in_vals]
            (1, '1', 1)(3, '3', 7)(0, '0', 0)(2, '2', 3)(1, '1', 1)
            (5, '5', 26)(0, '0', 0)(2, '2', 3)(1, '1', 1)(4, '4', 14)
            (1, '1', 1)(3, '3', 7)(0, '0', 0)(2, '2', 3)(1, '1', 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, '5', 26)
                (boost::tree_node::pre_order_traversal, 3, '3', 7)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::pre_order_traversal, 4, '4', 14)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::pre_order_traversal, 3, '3', 7)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::pre_order_traversal, 2, '2', 3)
                            (boost::tree_node::pre_order_traversal, 0, '0', 0)
                            (boost::tree_node::post_order_traversal, 0, '0', 0)
                            (boost::tree_node::pre_order_traversal, 1, '1', 1)
                            (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::post_order_traversal, 4, '4', 14)
            (boost::tree_node::post_order_traversal, 5, '5', 26);
        test_node<f_node_case>(
            f_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    put(
        *f_root.get_right_child_ptr()->get_left_child_ptr()
      , example_keys::your_uint()
      , 7
    );

    {
        MoreValues bf_vals, pre_vals, post_vals, in_vals;
        DFMoreValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (5, '5', 31)(3, '3', 7)(4, '4', 19)(1, '1', 1)(2, '2', 3)
            (7, '2', 8)(3, '3', 7)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[pre_vals]
            (5, '5', 31)(3, '3', 7)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(4, '4', 19)(7, '2', 8)(0, '0', 0)(1, '1', 1)
            (3, '3', 7)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[post_vals]
            (1, '1', 1)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 7)
            (0, '0', 0)(1, '1', 1)(7, '2', 8)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(3, '3', 7)(4, '4', 19)(5, '5', 31);
        emplacer[in_vals]
            (1, '1', 1)(3, '3', 7)(0, '0', 0)(2, '2', 3)(1, '1', 1)
            (5, '5', 31)(0, '0', 0)(7, '2', 8)(1, '1', 1)(4, '4', 19)
            (1, '1', 1)(3, '3', 7)(0, '0', 0)(2, '2', 3)(1, '1', 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, '5', 31)
                (boost::tree_node::pre_order_traversal, 3, '3', 7)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::pre_order_traversal, 4, '4', 19)
                    (boost::tree_node::pre_order_traversal, 7, '2', 8)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 7, '2', 8)
                    (boost::tree_node::pre_order_traversal, 3, '3', 7)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::pre_order_traversal, 2, '2', 3)
                            (boost::tree_node::pre_order_traversal, 0, '0', 0)
                            (boost::tree_node::post_order_traversal, 0, '0', 0)
                            (boost::tree_node::pre_order_traversal, 1, '1', 1)
                            (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::post_order_traversal, 4, '4', 19)
            (boost::tree_node::post_order_traversal, 5, '5', 31);
        test_node<f_node_case>(
            f_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }

    //[example__gui__binary_node__types
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::with_accumulation_base_gen<
                    boost::tree_node::binary_node_base_gen<>
                  , HeightSumKey
                >
              , GUITable
              , void
              , MinPriorityKey
            >
            GUINode;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_location
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_height
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_priority
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , HeightSumKey
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , MinPriorityKey
                    >::type
                >
            >::type
            GUIValues;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_location
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_height
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , example_keys::row_priority
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , HeightSumKey
                    >::type
                  , boost::tree_node::result_of::value_at_key<
                        GUINode const
                      , MinPriorityKey
                    >::type
                >
            >::type
            DFGUIValues;
    //]

    //[example__gui__binary_node__build
    GUINode gui_root(
        boost::fusion::make_pair<example_keys::row_location>(20)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(64)
    );
    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(0)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(20)
    );
    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(3)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(88)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(4)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(79)
    );
    gui_root.emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(5)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(36)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(10)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(5)
    )->emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(12)
      , boost::fusion::make_pair<example_keys::row_height>(4)
      , boost::fusion::make_pair<example_keys::row_priority>(19)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(59)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(25)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(55)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(91)
    )->emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(51)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(7)
    );
    gui_root.emplace_right(
        boost::fusion::make_pair<example_keys::row_location>(42)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(19)
    )->emplace_left(
        boost::fusion::make_pair<example_keys::row_location>(22)
      , boost::fusion::make_pair<example_keys::row_height>(12)
      , boost::fusion::make_pair<example_keys::row_priority>(54)
    );
    //]

    //[example__gui__binary_node__test
    {
        GUIValues bf_vals, pre_vals, post_vals, in_vals;
        DFGUIValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (20, 12, 64, 112, 5)(5, 4, 36, 40, 5)(42, 12, 19, 60, 7)
            (3, 4, 88, 28, 20)(10, 4, 5, 8, 5)(22, 12, 54, 12, 54)
            (55, 12, 91, 36, 7)(0, 12, 20, 12, 20)(4, 12, 79, 12, 79)
            (12, 4, 19, 4, 19)(51, 12, 7, 12, 7)(59, 12, 25, 12, 25);
        emplacer[pre_vals]
            (20, 12, 64, 112, 5)(5, 4, 36, 40, 5)(3, 4, 88, 28, 20)
            (0, 12, 20, 12, 20)(4, 12, 79, 12, 79)(10, 4, 5, 8, 5)
            (12, 4, 19, 4, 19)(42, 12, 19, 60, 7)(22, 12, 54, 12, 54)
            (55, 12, 91, 36, 7)(51, 12, 7, 12, 7)(59, 12, 25, 12, 25);
        emplacer[post_vals]
            (0, 12, 20, 12, 20)(4, 12, 79, 12, 79)(3, 4, 88, 28, 20)
            (12, 4, 19, 4, 19)(10, 4, 5, 8, 5)(5, 4, 36, 40, 5)
            (22, 12, 54, 12, 54)(51, 12, 7, 12, 7)(59, 12, 25, 12, 25)
            (55, 12, 91, 36, 7)(42, 12, 19, 60, 7)(20, 12, 64, 112, 5);
        emplacer[in_vals]
            (0, 12, 20, 12, 20)(3, 4, 88, 28, 20)(4, 12, 79, 12, 79)
            (5, 4, 36, 40, 5)(10, 4, 5, 8, 5)(12, 4, 19, 4, 19)
            (20, 12, 64, 112, 5)(22, 12, 54, 12, 54)(42, 12, 19, 60, 7)
            (51, 12, 7, 12, 7)(55, 12, 91, 36, 7)(59, 12, 25, 12, 25);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 20, 12, 64, 112, 5)
                (boost::tree_node::pre_order_traversal, 5, 4, 36, 40, 5)
                    (boost::tree_node::pre_order_traversal, 3, 4, 88, 28, 20)
                        (boost::tree_node::pre_order_traversal, 0, 12, 20, 12, 20)
                        (boost::tree_node::post_order_traversal, 0, 12, 20, 12, 20)
                        (boost::tree_node::pre_order_traversal, 4, 12, 79, 12, 79)
                        (boost::tree_node::post_order_traversal, 4, 12, 79, 12, 79)
                    (boost::tree_node::post_order_traversal, 3, 4, 88, 28, 20)
                    (boost::tree_node::pre_order_traversal, 10, 4, 5, 8, 5)
                        (boost::tree_node::pre_order_traversal, 12, 4, 19, 4, 19)
                        (boost::tree_node::post_order_traversal, 12, 4, 19, 4, 19)
                    (boost::tree_node::post_order_traversal, 10, 4, 5, 8, 5)
                (boost::tree_node::post_order_traversal, 5, 4, 36, 40, 5)
                (boost::tree_node::pre_order_traversal, 42, 12, 19, 60, 7)
                    (boost::tree_node::pre_order_traversal, 22, 12, 54, 12, 54)
                    (boost::tree_node::post_order_traversal, 22, 12, 54, 12, 54)
                    (boost::tree_node::pre_order_traversal, 55, 12, 91, 36, 7)
                        (boost::tree_node::pre_order_traversal, 51, 12, 7, 12, 7)
                        (boost::tree_node::post_order_traversal, 51, 12, 7, 12, 7)
                        (boost::tree_node::pre_order_traversal, 59, 12, 25, 12, 25)
                        (boost::tree_node::post_order_traversal, 59, 12, 25, 12, 25)
                    (boost::tree_node::post_order_traversal, 55, 12, 91, 36, 7)
                (boost::tree_node::post_order_traversal, 42, 12, 19, 60, 7)
            (boost::tree_node::post_order_traversal, 20, 12, 64, 112, 5);
        test_node<gui_node_case>(
            gui_root
          , bf_vals
          , pre_vals
          , post_vals
          , in_vals
          , df_vals
        );
    }
    //]
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

