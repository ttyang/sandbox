// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_TYPEOF_COMPLIANT

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <boost/typeof/typeof.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/get_reference.hpp>
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/container_gen.hpp>
#include <boost/container_gen/emplace_function_gen.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/typeof/with_count.hpp>
#include <boost/tree_node/typeof/with_height.hpp>
#include <boost/tree_node/typeof/with_position.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/tree_node/typeof/with_accumulation.hpp>
#endif

#include "../example/type_definitions.hpp"
#include "iterator_functions.hpp"

typedef boost::emplace_function_gen<boost::dequeS>::type
        DFEmplacer;

#include <boost/tree_node/typeof/binary_node.hpp>

#if defined BOOST_NO_SFINAE
typedef boost::tree_node::with_height<
            boost::tree_node::with_position_gen<
                boost::tree_node::with_count_gen<
                    boost::tree_node::binary_node_gen
                >
            >
          , double
        >
        ANode;
#else  // !defined BOOST_NO_SFINAE
typedef boost::tree_node::with_accumulation<
            boost::tree_node::with_height_gen<
                boost::tree_node::with_accumulation_gen<
                    boost::tree_node::with_position_gen<
                        boost::tree_node::with_accumulation_gen<
                            boost::tree_node::with_count_gen<
                                boost::tree_node::with_accumulation_gen<
                                    boost::tree_node::binary_node_gen
                                >
                            >
                          , AccuAccuKey
                        >
                    >
                  , AccuCountKey
                >
            >
          , double
          , void
          , AccuHeightKey
        >
        ANode;
#endif  // BOOST_NO_SFINAE

typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::data_key()
                    )
                )
              , BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::height_key()
                    )
                )
              , BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::count_key()
                    )
                )
#if !defined BOOST_NO_SFINAE
              , BOOST_TYPEOF(
                    boost::tree_node::get<
                        boost::tree_node::accumulation_key<>
                    >(boost::get_reference<ANode const>())
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuHeightKey>(
                        boost::get_reference<ANode const>()
                    )
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuCountKey>(
                        boost::get_reference<ANode const>()
                    )
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuAccuKey>(
                        boost::get_reference<ANode const>()
                    )
                )
#endif  // BOOST_NO_SFINAE
            >
        >::type
        Values;
typedef boost::container_gen<
            boost::dequeS
          , boost::tuples::tuple<
                boost::tree_node::traversal_state
              , BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::data_key()
                    )
                )
              , BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::height_key()
                    )
                )
              , BOOST_TYPEOF(
                    get(
                        boost::get_reference<ANode const>()
                      , boost::tree_node::count_key()
                    )
                )
#if !defined BOOST_NO_SFINAE
              , BOOST_TYPEOF(
                    boost::tree_node::get<
                        boost::tree_node::accumulation_key<>
                    >(boost::get_reference<ANode const>())
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuHeightKey>(
                        boost::get_reference<ANode const>()
                    )
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuCountKey>(
                        boost::get_reference<ANode const>()
                    )
                )
              , BOOST_TYPEOF(
                    boost::tree_node::get<AccuAccuKey>(
                        boost::get_reference<ANode const>()
                    )
                )
#endif  // BOOST_NO_SFINAE
            >
        >::type
        DFValues;

int test_main(int argc, char** argv)
{
    ANode a_root(5.0);

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
        BOOST_AUTO(data, get(*itr, boost::tree_node::data_key()));

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
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
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
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 4, 15, 26, 3, 51, 4)(3, 2, 5, 7, 1, 11, 2)
            (4, 3, 9, 14, 2, 25, 3)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 4, 15, 26, 3, 51, 4)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 3, 9, 14, 2, 25, 3)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(4, 3, 9, 14, 2, 25, 3)
            (5, 4, 15, 26, 3, 51, 4);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 4, 15, 26, 3, 51, 4)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 4, 15, 26, 3, 51, 4)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::post_order_traversal, 4, 3, 9, 14, 2, 25, 3)
          (boost::tree_node::post_order_traversal, 5, 4, 15, 26, 3, 51, 4);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
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
        ANode::pointer p = a_root.get_left_child_ptr()->get_left_child_ptr();
        ANode::iterator a_child_itr = p->insert_left(a_root);
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 7, 30)(3, 6, 20)(4, 3, 9)(1, 5, 16)(2, 1, 3)(2, 1, 3)(3, 2, 5)
            (5, 4, 15)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 5)(4, 3, 9)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(2, 1, 3)
            (3, 2, 5)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 7, 30)(3, 6, 20)(1, 5, 16)(5, 4, 15)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(4, 3, 9)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (4, 3, 9)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 3, 9)
            (5, 4, 15)(1, 5, 16)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 6, 20)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)
            (4, 3, 9)(5, 7, 30);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 4, 15)(0, 0, 1)
            (2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(1, 5, 16)(3, 6, 20)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 7, 30)
            (0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)
            (2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 7, 30)
                (boost::tree_node::pre_order_traversal, 3, 6, 20)
                    (boost::tree_node::pre_order_traversal, 1, 5, 16)
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
                        (boost::tree_node::post_order_traversal, 5, 4, 15)
                    (boost::tree_node::post_order_traversal, 1, 5, 16)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
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
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 7, 30, 52, 6, 147, 7)(3, 6, 20, 33, 5, 92, 6)
            (4, 3, 9, 14, 2, 25, 3)(1, 5, 16, 27, 4, 67, 5)
            (2, 1, 3, 3, 0, 5, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(5, 4, 15, 26, 3, 51, 4)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(4, 3, 9, 14, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 7, 30, 52, 6, 147, 7)(3, 6, 20, 33, 5, 92, 6)
            (1, 5, 16, 27, 4, 67, 5)(5, 4, 15, 26, 3, 51, 4)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(4, 3, 9, 14, 2, 25, 3)
            (5, 4, 15, 26, 3, 51, 4)(1, 5, 16, 27, 4, 67, 5)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 6, 20, 33, 5, 92, 6)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (4, 3, 9, 14, 2, 25, 3)(5, 7, 30, 52, 6, 147, 7);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 4, 15, 26, 3, 51, 4)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(1, 5, 16, 27, 4, 67, 5)
            (3, 6, 20, 33, 5, 92, 6)(0, 0, 1, 0, 0, 1, 0)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (5, 7, 30, 52, 6, 147, 7)(0, 0, 1, 0, 0, 1, 0)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (4, 3, 9, 14, 2, 25, 3)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 7, 30, 52, 6, 147, 7)
            (boost::tree_node::pre_order_traversal, 3, 6, 20, 33, 5, 92, 6)
              (boost::tree_node::pre_order_traversal, 1, 5, 16, 27, 4, 67, 5)
              (boost::tree_node::pre_order_traversal, 5, 4, 15, 26, 3, 51, 4)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::post_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::post_order_traversal, 5, 4, 15, 26, 3, 51, 4)
              (boost::tree_node::post_order_traversal, 1, 5, 16, 27, 4, 67, 5)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 6, 20, 33, 5, 92, 6)
            (boost::tree_node::pre_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::post_order_traversal, 4, 3, 9, 14, 2, 25, 3)
          (boost::tree_node::post_order_traversal, 5, 7, 30, 52, 6, 147, 7);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);

        a_root = *a_child_itr;
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        in_vals.clear();
        df_vals.clear();

#if defined BOOST_NO_SFINAE
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
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 4, 15, 26, 3, 51, 4)(3, 2, 5, 7, 1, 11, 2)
            (4, 3, 9, 14, 2, 25, 3)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 4, 15, 26, 3, 51, 4)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 3, 9, 14, 2, 25, 3)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(4, 3, 9, 14, 2, 25, 3)
            (5, 4, 15, 26, 3, 51, 4);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 4, 15, 26, 3, 51, 4)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 4, 15, 26, 3, 51, 4)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::post_order_traversal, 4, 3, 9, 14, 2, 25, 3)
          (boost::tree_node::post_order_traversal, 5, 4, 15, 26, 3, 51, 4);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);

        *(p = a_root.get_right_child_ptr()) = a_root;
        test_node(*p, bf_vals, pre_vals, post_vals, in_vals, df_vals);

        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        in_vals.clear();
        df_vals.clear();

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21)(3, 2, 5)(5, 4, 15)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 3, 9)
            (0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(2, 1, 3)(3, 2, 5)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 21)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(5, 4, 15)
            (3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 9)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)(2, 1, 3)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 3, 9)(5, 4, 15)(5, 5, 21);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 21)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 4, 15)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(4, 3, 9)(1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 21)
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
                (boost::tree_node::post_order_traversal, 5, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 21);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21, 38, 4, 83, 5)(3, 2, 5, 7, 1, 11, 2)
            (5, 4, 15, 26, 3, 51, 4)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (4, 3, 9, 14, 2, 25, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 21, 38, 4, 83, 5)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (5, 4, 15, 26, 3, 51, 4)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 3, 9, 14, 2, 25, 3)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (4, 3, 9, 14, 2, 25, 3)(5, 4, 15, 26, 3, 51, 4)
            (5, 5, 21, 38, 4, 83, 5);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 5, 21, 38, 4, 83, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 4, 15, 26, 3, 51, 4)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 3, 9, 14, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 21, 38, 4, 83, 5)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 5, 4, 15, 26, 3, 51, 4)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 4, 3, 9, 14, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::post_order_traversal, 4, 3, 9, 14, 2, 25, 3)
            (boost::tree_node::post_order_traversal, 5, 4, 15, 26, 3, 51, 4)
          (boost::tree_node::post_order_traversal, 5, 5, 21, 38, 4, 83, 5);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    a_root.get_right_child_ptr()->rotate_left();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21)(3, 2, 5)(4, 4, 15)(1, 0, 1)(2, 1, 3)(5, 3, 9)(3, 2, 5)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(2, 1, 3)(1, 0, 1)(2, 1, 3)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 21)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 4, 15)
            (5, 3, 9)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 3, 9)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(4, 4, 15)(5, 5, 21);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 21)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 9)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(4, 4, 15)(1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 21)
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
                (boost::tree_node::pre_order_traversal, 4, 4, 15)
                    (boost::tree_node::pre_order_traversal, 5, 3, 9)
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
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 9)
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
                (boost::tree_node::post_order_traversal, 4, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 21);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21, 38, 4, 83, 5)(3, 2, 5, 7, 1, 11, 2)
            (4, 4, 15, 26, 3, 51, 4)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 21, 38, 4, 83, 5)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 4, 15, 26, 3, 51, 4)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(4, 4, 15, 26, 3, 51, 4)
            (5, 5, 21, 38, 4, 83, 5);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 5, 21, 38, 4, 83, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 3, 9, 15, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 4, 15, 26, 3, 51, 4)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 21, 38, 4, 83, 5)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 4, 4, 15, 26, 3, 51, 4)
              (boost::tree_node::pre_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::post_order_traversal, 4, 4, 15, 26, 3, 51, 4)
          (boost::tree_node::post_order_traversal, 5, 5, 21, 38, 4, 83, 5);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    {
        ANode::pointer p(a_root.get_right_child_ptr()->get_right_child_ptr());
        ANode::iterator p_child_itr(p->emplace_right());
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

        put(*p_child_itr, boost::tree_node::data_key(), 7);
#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21)(3, 2, 5)(4, 4, 15)(1, 0, 1)(2, 1, 3)(5, 3, 9)(3, 2, 5)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(2, 1, 3)(1, 0, 1)(7, 1, 3)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 21)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 4, 15)
            (5, 3, 9)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(7, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 3, 9)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(7, 1, 3)(3, 2, 5)(4, 4, 15)(5, 5, 21);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 21)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 9)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(4, 4, 15)(1, 0, 1)(3, 2, 5)(0, 0, 1)(7, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 21)
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
                (boost::tree_node::pre_order_traversal, 4, 4, 15)
                    (boost::tree_node::pre_order_traversal, 5, 3, 9)
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
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 9)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 7, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 21);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21, 43, 4, 83, 6)(3, 2, 5, 7, 1, 11, 2)
            (4, 4, 15, 31, 3, 51, 5)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 12, 1, 11, 4)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 21, 43, 4, 83, 6)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 4, 15, 31, 3, 51, 5)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 12, 1, 11, 4)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(7, 1, 3, 8, 0, 5, 3)
            (3, 2, 5, 12, 1, 11, 4)(4, 4, 15, 31, 3, 51, 5)
            (5, 5, 21, 43, 4, 83, 6);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 5, 21, 43, 4, 83, 6)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 3, 9, 15, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 4, 15, 31, 3, 51, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 12, 1, 11, 4)
            (0, 0, 1, 0, 0, 1, 0)(7, 1, 3, 8, 0, 5, 3)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 21, 43, 4, 83, 6)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 4, 4, 15, 31, 3, 51, 5)
              (boost::tree_node::pre_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 12, 1, 11, 4)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 12, 1, 11, 4)
            (boost::tree_node::post_order_traversal, 4, 4, 15, 31, 3, 51, 5)
          (boost::tree_node::post_order_traversal, 5, 5, 21, 43, 4, 83, 6);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    a_root.get_left_child_ptr()->rotate_right();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21)(1, 0, 5)(4, 4, 15)(3, 2, 4)(5, 3, 9)(3, 2, 5)(2, 1, 3)
            (3, 2, 5)(2, 1, 3)(1, 0, 1)(7, 1, 3)(0, 0, 1)(1, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 21)(1, 0, 5)(3, 2, 4)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 4, 15)
            (5, 3, 9)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(7, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 4)(1, 0, 5)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 3, 9)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(7, 1, 3)(3, 2, 5)(4, 4, 15)(5, 5, 21);
        emplacer[in_vals]
            (1, 0, 5)(3, 2, 4)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 21)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 9)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(4, 4, 15)(1, 0, 1)(3, 2, 5)(0, 0, 1)(7, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 21)
                (boost::tree_node::pre_order_traversal, 1, 0, 5)
                    (boost::tree_node::pre_order_traversal, 3, 2, 4)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 4)
                (boost::tree_node::post_order_traversal, 1, 0, 5)
                (boost::tree_node::pre_order_traversal, 4, 4, 15)
                    (boost::tree_node::pre_order_traversal, 5, 3, 9)
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
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 9)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 7, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 21);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21, 43, 4, 86, 6)(1, 0, 5, 7, 2, 14, 3)
            (4, 4, 15, 31, 3, 51, 5)(3, 2, 4, 6, 1, 9, 2)
            (5, 3, 9, 15, 2, 25, 3)(3, 2, 5, 12, 1, 11, 4)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 21, 43, 4, 86, 6)(1, 0, 5, 7, 2, 14, 3)
            (3, 2, 4, 6, 1, 9, 2)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 4, 15, 31, 3, 51, 5)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 12, 1, 11, 4)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 4, 6, 1, 9, 2)
            (1, 0, 5, 7, 2, 14, 3)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(7, 1, 3, 8, 0, 5, 3)
            (3, 2, 5, 12, 1, 11, 4)(4, 4, 15, 31, 3, 51, 5)
            (5, 5, 21, 43, 4, 86, 6);
        emplacer[in_vals]
            (1, 0, 5, 7, 2, 14, 3)(3, 2, 4, 6, 1, 9, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 5, 21, 43, 4, 86, 6)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 3, 9, 15, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 4, 15, 31, 3, 51, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 12, 1, 11, 4)
            (0, 0, 1, 0, 0, 1, 0)(7, 1, 3, 8, 0, 5, 3)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 21, 43, 4, 86, 6)
            (boost::tree_node::pre_order_traversal, 1, 0, 5, 7, 2, 14, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 4, 6, 1, 9, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 4, 6, 1, 9, 2)
            (boost::tree_node::post_order_traversal, 1, 0, 5, 7, 2, 14, 3)
            (boost::tree_node::pre_order_traversal, 4, 4, 15, 31, 3, 51, 5)
              (boost::tree_node::pre_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 12, 1, 11, 4)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 12, 1, 11, 4)
            (boost::tree_node::post_order_traversal, 4, 4, 15, 31, 3, 51, 5)
          (boost::tree_node::post_order_traversal, 5, 5, 21, 43, 4, 86, 6);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    a_root.get_left_child_ptr()->rotate_left();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21)(3, 2, 5)(4, 4, 15)(1, 0, 1)(2, 1, 3)(5, 3, 9)(3, 2, 5)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(2, 1, 3)(1, 0, 1)(7, 1, 3)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 21)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 4, 15)
            (5, 3, 9)(3, 2, 5)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)(7, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 3, 9)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(7, 1, 3)(3, 2, 5)(4, 4, 15)(5, 5, 21);
        emplacer[in_vals]
            (1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 5, 21)(1, 0, 1)
            (3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)(5, 3, 9)(0, 0, 1)(2, 1, 3)
            (1, 0, 1)(4, 4, 15)(1, 0, 1)(3, 2, 5)(0, 0, 1)(7, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 21)
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
                (boost::tree_node::pre_order_traversal, 4, 4, 15)
                    (boost::tree_node::pre_order_traversal, 5, 3, 9)
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
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 9)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 7, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 21);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 21, 43, 4, 83, 6)(3, 2, 5, 7, 1, 11, 2)
            (4, 4, 15, 31, 3, 51, 5)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 12, 1, 11, 4)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 21, 43, 4, 83, 6)(3, 2, 5, 7, 1, 11, 2)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (4, 4, 15, 31, 3, 51, 5)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 12, 1, 11, 4)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(7, 1, 3, 8, 0, 5, 3)
            (3, 2, 5, 12, 1, 11, 4)(4, 4, 15, 31, 3, 51, 5)
            (5, 5, 21, 43, 4, 83, 6);
        emplacer[in_vals]
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 5, 21, 43, 4, 83, 6)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 3, 9, 15, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 4, 15, 31, 3, 51, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 12, 1, 11, 4)
            (0, 0, 1, 0, 0, 1, 0)(7, 1, 3, 8, 0, 5, 3)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 21, 43, 4, 83, 6)
            (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
            (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
            (boost::tree_node::pre_order_traversal, 4, 4, 15, 31, 3, 51, 5)
              (boost::tree_node::pre_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 12, 1, 11, 4)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 12, 1, 11, 4)
            (boost::tree_node::post_order_traversal, 4, 4, 15, 31, 3, 51, 5)
          (boost::tree_node::post_order_traversal, 5, 5, 21, 43, 4, 83, 6);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    a_root.begin()->clear();

    {
        Values bf_vals, pre_vals, post_vals, in_vals;
        DFValues df_vals;
        DFEmplacer emplacer;

#if defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 17)(3, 0, 1)(4, 4, 15)(5, 3, 9)(3, 2, 5)(3, 2, 5)(2, 1, 3)
            (1, 0, 1)(7, 1, 3)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 5, 17)(3, 0, 1)(4, 4, 15)(5, 3, 9)(3, 2, 5)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 5)(1, 0, 1)
            (7, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (3, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 5)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(5, 3, 9)(1, 0, 1)(0, 0, 1)(1, 0, 1)(7, 1, 3)
            (3, 2, 5)(4, 4, 15)(5, 5, 17);
        emplacer[in_vals]
            (3, 0, 1)(5, 5, 17)(1, 0, 1)(3, 2, 5)(0, 0, 1)(2, 1, 3)(1, 0, 1)
            (5, 3, 9)(0, 0, 1)(2, 1, 3)(1, 0, 1)(4, 4, 15)(1, 0, 1)(3, 2, 5)
            (0, 0, 1)(7, 1, 3)(1, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 5, 17)
                (boost::tree_node::pre_order_traversal, 3, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 0, 1)
                (boost::tree_node::pre_order_traversal, 4, 4, 15)
                    (boost::tree_node::pre_order_traversal, 5, 3, 9)
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
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 5, 3, 9)
                    (boost::tree_node::pre_order_traversal, 3, 2, 5)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 7, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 7, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 5)
                (boost::tree_node::post_order_traversal, 4, 4, 15)
            (boost::tree_node::post_order_traversal, 5, 5, 17);
#else  // !defined BOOST_NO_SFINAE
        emplacer[bf_vals]
            (5, 5, 17, 39, 4, 69, 7)(3, 0, 1, 3, 0, 1, 3)
            (4, 4, 15, 31, 3, 51, 5)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 12, 1, 11, 4)(3, 2, 5, 7, 1, 11, 2)
            (2, 1, 3, 3, 0, 5, 1)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[pre_vals]
            (5, 5, 17, 39, 4, 69, 7)(3, 0, 1, 3, 0, 1, 3)
            (4, 4, 15, 31, 3, 51, 5)(5, 3, 9, 15, 2, 25, 3)
            (3, 2, 5, 7, 1, 11, 2)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(2, 1, 3, 3, 0, 5, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (3, 2, 5, 12, 1, 11, 4)(1, 0, 1, 1, 0, 1, 1)
            (7, 1, 3, 8, 0, 5, 3)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[post_vals]
            (3, 0, 1, 3, 0, 1, 3)(1, 0, 1, 1, 0, 1, 1)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(1, 0, 1, 1, 0, 1, 1)
            (2, 1, 3, 3, 0, 5, 1)(5, 3, 9, 15, 2, 25, 3)
            (1, 0, 1, 1, 0, 1, 1)(0, 0, 1, 0, 0, 1, 0)
            (1, 0, 1, 1, 0, 1, 1)(7, 1, 3, 8, 0, 5, 3)
            (3, 2, 5, 12, 1, 11, 4)(4, 4, 15, 31, 3, 51, 5)
            (5, 5, 17, 39, 4, 69, 7);
        emplacer[in_vals]
            (3, 0, 1, 3, 0, 1, 3)(5, 5, 17, 39, 4, 69, 7)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 7, 1, 11, 2)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(5, 3, 9, 15, 2, 25, 3)
            (0, 0, 1, 0, 0, 1, 0)(2, 1, 3, 3, 0, 5, 1)
            (1, 0, 1, 1, 0, 1, 1)(4, 4, 15, 31, 3, 51, 5)
            (1, 0, 1, 1, 0, 1, 1)(3, 2, 5, 12, 1, 11, 4)
            (0, 0, 1, 0, 0, 1, 0)(7, 1, 3, 8, 0, 5, 3)
            (1, 0, 1, 1, 0, 1, 1);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal, 5, 5, 17, 39, 4, 69, 7)
            (boost::tree_node::pre_order_traversal, 3, 0, 1, 3, 0, 1, 3)
            (boost::tree_node::post_order_traversal, 3, 0, 1, 3, 0, 1, 3)
            (boost::tree_node::pre_order_traversal, 4, 4, 15, 31, 3, 51, 5)
              (boost::tree_node::pre_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 7, 1, 11, 2)
              (boost::tree_node::pre_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 2, 1, 3, 3, 0, 5, 1)
              (boost::tree_node::post_order_traversal, 5, 3, 9, 15, 2, 25, 3)
              (boost::tree_node::pre_order_traversal, 3, 2, 5, 12, 1, 11, 4)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::pre_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::pre_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::post_order_traversal, 0, 0, 1, 0, 0, 1, 0)
              (boost::tree_node::pre_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 1, 0, 1, 1, 0, 1, 1)
              (boost::tree_node::post_order_traversal, 7, 1, 3, 8, 0, 5, 3)
              (boost::tree_node::post_order_traversal, 3, 2, 5, 12, 1, 11, 4)
            (boost::tree_node::post_order_traversal, 4, 4, 15, 31, 3, 51, 5)
          (boost::tree_node::post_order_traversal, 5, 5, 17, 39, 4, 69, 7);
#endif  // BOOST_NO_SFINAE
        test_node(a_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::binary_node_gen
              , DataMap
              , void
              , AccuYourUintKey
            >
            FNode;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    BOOST_TYPEOF(
                        boost::tree_node::get<
                            example_keys::your_uint
                        >(boost::get_reference<FNode const>())
                    )
                  , BOOST_TYPEOF(
                        boost::tree_node::get<
                            example_keys::your_char
                        >(boost::get_reference<FNode const>())
                    )
                  , BOOST_TYPEOF(
                        boost::tree_node::get<AccuYourUintKey>(
                            boost::get_reference<FNode const>()
                        )
                    )
                >
            >::type
            MoreValues;
    typedef boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , BOOST_TYPEOF(
                        boost::tree_node::get<
                            example_keys::your_uint
                        >(boost::get_reference<FNode const>())
                    )
                  , BOOST_TYPEOF(
                        boost::tree_node::get<
                            example_keys::your_char
                        >(boost::get_reference<FNode const>())
                    )
                  , BOOST_TYPEOF(
                        boost::tree_node::get<AccuYourUintKey>(
                            boost::get_reference<FNode const>()
                        )
                    )
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
        BOOST_AUTO(data, boost::tree_node::get<example_keys::your_uint>(*itr));

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
        DFEmplacer emplacer;

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
        test_f_node(f_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }

    put(
        *f_root.get_right_child_ptr()->get_left_child_ptr()
      , example_keys::your_uint()
      , 7
    );

    {
        MoreValues bf_vals, pre_vals, post_vals, in_vals;
        DFMoreValues df_vals;
        DFEmplacer emplacer;

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
        test_f_node(f_root, bf_vals, pre_vals, post_vals, in_vals, df_vals);
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    return 0;
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

