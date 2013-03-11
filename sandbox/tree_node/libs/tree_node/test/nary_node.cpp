// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined BOOST_MSVC
    #pragma warning (push)
    #pragma warning (disable : 4996)  // fn called w/params that may be unsafe
#endif

#include <iterator>
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

#include <boost/typeof/boost/tree_node/nary_node.hpp>

template <typename Selector>
void test()
{
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
              boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                  boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_accumulation_base_gen<
                      boost::tree_node::with_count_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                          boost::tree_node::nary_node_base_gen<Selector>
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
                        boost::tree_node::nary_node_base_gen<Selector>
                    >
                >
              , boost::rational<long>
            >
            ANode;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::data_key
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::height_key
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::count_key
                    >::type
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::accumulation_key<>
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuHeightKey
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuCountKey
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuAccuKey
                    >::type
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
                >
            >::type
            Values;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::data_key
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::height_key
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::count_key
                    >::type
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , boost::tree_node::accumulation_key<>
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuHeightKey
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuCountKey
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        ANode const
                      , AccuAccuKey
                    >::type
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
                >
            >::type
            DFValues;

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
        typename ANode::traits::data_type const& data = get(
            *itr
          , boost::tree_node::data_key()
        );

        if (1 < data)
        {
            for (std::size_t i = 0; i < data; ++i)
            {
                typename ANode::iterator child_itr(
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    (std::tr1::is_same<Selector,boost::slistS>::value) ? (
                        (*itr).emplace(data - 1 - i)
                    ) :
#endif
                    (*itr).emplace(i)
                );
                typename ANode::const_pointer const_child(&*child_itr);
                BOOST_CHECK(
                    (*child_itr).get_parent_ptr() == &*itr
//                  , "Ctor not linking child to parent."
                );
                BOOST_CHECK(
                    (
                        (*child_itr).get_parent_ptr()
                    ) == (*const_child).get_parent_ptr()
//                  , "Why are these pointers different?"
                );

                {
                    typename ANode::iterator c_itr = (*itr).begin();

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
                    if (!std::tr1::is_same<Selector,boost::slistS>::value)
#endif
                    std::advance(c_itr, i);
                    BOOST_CHECK(
                        &*child_itr == &*c_itr
//                      , "Ctor not linking parent to child."
                    );
                }
            }
        }
    }

    {
        Values bf_vals, pre_vals, post_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 24,
            31, 3, 76, boost::rational<long>(10, 3))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
            (boost::tree_node::post_order_traversal, 5, 4, 24,
            31, 3, 76, boost::rational<long>(10, 3));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 12)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(4, 3, 12)(5, 4, 24);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 24)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 3, 12)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 3, 12)
            (boost::tree_node::post_order_traversal, 5, 4, 24);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);
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
        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));
        BOOST_CHECK(test_node_copies(df_d_root_itr, df_d_copy_itr));
    }

    {
        typename ANode::iterator a_child_itr(
            (*(++a_root.begin())).insert(a_root)
        );
        Values bf_vals, pre_vals, post_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 48, 62, 5, 200, boost::rational<long>(37, 8))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 5, 25, 32, 4, 101, boost::rational<long>(112, 25))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 6, 48, 62, 5, 200, boost::rational<long>(37, 8))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 5, 25, 32, 4, 101, boost::rational<long>(112, 25))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 5, 25, 32, 4, 101, boost::rational<long>(112, 25))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 6, 48, 62, 5, 200, boost::rational<long>(37, 8));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 48,
            62, 5, 200, boost::rational<long>(37, 8))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::pre_order_traversal, 1, 5, 25,
                32, 4, 101, boost::rational<long>(112, 25))
                    (boost::tree_node::pre_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::post_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::post_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::post_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
                (boost::tree_node::post_order_traversal, 1, 5, 25,
                32, 4, 101, boost::rational<long>(112, 25))
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
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
            (boost::tree_node::post_order_traversal, 5, 6, 48,
            62, 5, 200, boost::rational<long>(37, 8));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 48)(0, 0, 1)(1, 5, 25)(2, 1, 3)(3, 2, 6)(4, 3, 12)(5, 4, 24)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 6, 48)(0, 0, 1)(1, 5, 25)(5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(4, 3, 12)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(4, 3, 12)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(3, 2, 6)(4, 3, 12)(5, 4, 24)(1, 5, 25)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)(5, 6, 48);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 48)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 5, 25)
                    (boost::tree_node::pre_order_traversal, 5, 4, 24)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 4, 3, 12)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::post_order_traversal, 4, 3, 12)
                    (boost::tree_node::post_order_traversal, 5, 4, 24)
                (boost::tree_node::post_order_traversal, 1, 5, 25)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 3, 12)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 3, 12)
            (boost::tree_node::post_order_traversal, 5, 6, 48);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);

        a_root = *a_child_itr;
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        df_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 24,
            31, 3, 76, boost::rational<long>(10, 3))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 3, 12,
                15, 2, 32, boost::rational<long>(8, 3))
            (boost::tree_node::post_order_traversal, 5, 4, 24,
            31, 3, 76, boost::rational<long>(10, 3));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 12)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(4, 3, 12)(5, 4, 24);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 24)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 3, 12)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 3, 12)
            (boost::tree_node::post_order_traversal, 5, 4, 24);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);

        a_child_itr = a_root.begin();
        std::advance(a_child_itr, 4);
        a_child_itr = (*a_child_itr).begin();
        *a_child_itr = a_root;
        test_node<a_node_case>(*a_child_itr, bf_vals, pre_vals, post_vals, df_vals);

        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        df_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 47,
            62, 5, 197, boost::rational<long>(222, 47))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
                    (boost::tree_node::pre_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                        (boost::tree_node::pre_order_traversal, 3, 2, 6,
                        7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                        (boost::tree_node::post_order_traversal, 3, 2, 6,
                        7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::post_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::post_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::post_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
            (boost::tree_node::post_order_traversal, 5, 6, 47,
            62, 5, 197, boost::rational<long>(222, 47));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 47)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 5, 35)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 4, 24)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (4, 3, 12)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 6, 47)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 5, 35)(5, 4, 24)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 3, 12)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)(5, 4, 24)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 5, 35)(5, 6, 47);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 47)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 5, 35)
                    (boost::tree_node::pre_order_traversal, 5, 4, 24)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                        (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 4, 3, 12)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::post_order_traversal, 4, 3, 12)
                    (boost::tree_node::post_order_traversal, 5, 4, 24)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 5, 35)
            (boost::tree_node::post_order_traversal, 5, 6, 47);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);

        a_child_itr = (*a_child_itr).begin();
        std::advance(a_child_itr, 2);

        typename ANode::iterator a_desc_itr = a_child_itr;
        typename ANode::iterator a_src_itr = (*(++a_desc_itr)).begin();
        typename ANode::iterator a_end_itr = (*a_desc_itr).end();

        (*a_child_itr).splice(
            ++(*a_child_itr).begin()
          , *a_desc_itr
          , ++a_src_itr
          , a_end_itr
        );
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        df_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 6, 47, 62, 5, 197, boost::rational<long>(222, 47));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 47,
            62, 5, 197, boost::rational<long>(222, 47))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::pre_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                    (boost::tree_node::pre_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
                    (boost::tree_node::post_order_traversal, 0, 0, 1,
                    0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::post_order_traversal, 3, 2, 6,
                7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::pre_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
                    (boost::tree_node::pre_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 2, 7,
                        7, 1, 15, boost::rational<long>(13, 7))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 2, 7,
                        7, 1, 15, boost::rational<long>(13, 7))
                        (boost::tree_node::pre_order_traversal, 3, 1, 2,
                        3, 0, 3, boost::rational<long>(3, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 3, 1, 2,
                        3, 0, 3, boost::rational<long>(3, 2))
                        (boost::tree_node::pre_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::post_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::post_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::post_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
            (boost::tree_node::post_order_traversal, 5, 6, 47,
            62, 5, 197, boost::rational<long>(222, 47));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 47)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 5, 35)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(5, 4, 24)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 2, 7)(3, 1, 2)
            (4, 3, 12)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 6, 47)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(4, 5, 35)(5, 4, 24)
            (0, 0, 1)(1, 0, 1)(2, 2, 7)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(1, 0, 1)(3, 1, 2)(0, 0, 1)(4, 3, 12)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)
            (0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(1, 0, 1)(2, 2, 7)(0, 0, 1)
            (3, 1, 2)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 3, 12)(5, 4, 24)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 5, 35)(5, 6, 47);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 47)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 2, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::pre_order_traversal, 4, 5, 35)
                    (boost::tree_node::pre_order_traversal, 5, 4, 24)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 2, 7)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 2, 7)
                        (boost::tree_node::pre_order_traversal, 3, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 1, 2)
                        (boost::tree_node::pre_order_traversal, 4, 3, 12)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::post_order_traversal, 4, 3, 12)
                    (boost::tree_node::post_order_traversal, 5, 4, 24)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 5, 35)
            (boost::tree_node::post_order_traversal, 5, 6, 47);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);
    }

    {
        typename ANode::iterator a_child_itr(a_root.begin());

        std::advance(a_child_itr, 3);
        (*a_child_itr).clear();

        Values bf_vals, pre_vals, post_vals;
        DFValues df_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 42, 58, 5, 180, boost::rational<long>(209, 42))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[pre_vals]
            (5, 6, 42, 58, 5, 180, boost::rational<long>(209, 42))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 0, 1, 3, 0, 1, boost::rational<long>(3, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 2, 7, 7, 1, 15, boost::rational<long>(13, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 1, 2, 3, 0, 3, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 3, 12, 15, 2, 32, boost::rational<long>(8, 3))
            (5, 4, 24, 31, 3, 76, boost::rational<long>(10, 3))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 3, 3, 0, 5, boost::rational<long>(4, 3))
            (3, 2, 6, 7, 1, 13, boost::rational<long>(2, 1))
            (4, 5, 35, 46, 4, 130, boost::rational<long>(143, 35))
            (5, 6, 42, 58, 5, 180, boost::rational<long>(209, 42));
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 42,
            58, 5, 180, boost::rational<long>(209, 42))
                (boost::tree_node::pre_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
                (boost::tree_node::post_order_traversal, 0, 0, 1,
                0, 0, 1, boost::rational<long>(0, 1))
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
                (boost::tree_node::pre_order_traversal, 3, 0, 1,
                3, 0, 1, boost::rational<long>(3, 1))
                (boost::tree_node::post_order_traversal, 3, 0, 1,
                3, 0, 1, boost::rational<long>(3, 1))
                (boost::tree_node::pre_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
                    (boost::tree_node::pre_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::pre_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 1, 0, 1,
                        1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::pre_order_traversal, 2, 2, 7,
                        7, 1, 15, boost::rational<long>(13, 7))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                            (boost::tree_node::post_order_traversal, 1, 0, 1,
                            1, 0, 1, boost::rational<long>(1, 1))
                        (boost::tree_node::post_order_traversal, 2, 2, 7,
                        7, 1, 15, boost::rational<long>(13, 7))
                        (boost::tree_node::pre_order_traversal, 3, 1, 2,
                        3, 0, 3, boost::rational<long>(3, 2))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 3, 1, 2,
                        3, 0, 3, boost::rational<long>(3, 2))
                        (boost::tree_node::pre_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::pre_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                            (boost::tree_node::pre_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
                            (boost::tree_node::post_order_traversal, 0, 0, 1,
                            0, 0, 1, boost::rational<long>(0, 1))
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
                            (boost::tree_node::post_order_traversal, 3, 2, 6,
                            7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::post_order_traversal, 4, 3, 12,
                        15, 2, 32, boost::rational<long>(8, 3))
                    (boost::tree_node::post_order_traversal, 5, 4, 24,
                    31, 3, 76, boost::rational<long>(10, 3))
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
                    (boost::tree_node::pre_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                        (boost::tree_node::pre_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
                        (boost::tree_node::post_order_traversal, 0, 0, 1,
                        0, 0, 1, boost::rational<long>(0, 1))
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
                    (boost::tree_node::post_order_traversal, 3, 2, 6,
                    7, 1, 13, boost::rational<long>(2, 1))
                (boost::tree_node::post_order_traversal, 4, 5, 35,
                46, 4, 130, boost::rational<long>(143, 35))
            (boost::tree_node::post_order_traversal, 5, 6, 42,
            58, 5, 180, boost::rational<long>(209, 42));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 42)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 0, 1)(4, 5, 35)(0, 0, 1)
            (1, 0, 1)(5, 4, 24)(1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)
            (2, 2, 7)(3, 1, 2)(4, 3, 12)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(2, 1, 3)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(3, 2, 6)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[pre_vals]
            (5, 6, 42)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 0, 1)
            (4, 5, 35)(5, 4, 24)(0, 0, 1)(1, 0, 1)(2, 2, 7)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(1, 0, 1)(3, 1, 2)(0, 0, 1)(4, 3, 12)
            (0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(3, 2, 6)(0, 0, 1)
            (1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(3, 2, 6)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)(1, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(1, 0, 1)
            (2, 2, 7)(0, 0, 1)(3, 1, 2)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 3)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)
            (4, 3, 12)(5, 4, 24)(1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 3)(3, 2, 6)(4, 5, 35)(5, 6, 42);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 42)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 3)
                (boost::tree_node::pre_order_traversal, 3, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 0, 1)
                (boost::tree_node::pre_order_traversal, 4, 5, 35)
                    (boost::tree_node::pre_order_traversal, 5, 4, 24)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 2, 7)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 2, 7)
                        (boost::tree_node::pre_order_traversal, 3, 1, 2)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 1, 2)
                        (boost::tree_node::pre_order_traversal, 4, 3, 12)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 3, 2, 6)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 3)
                            (boost::tree_node::post_order_traversal, 3, 2, 6)
                        (boost::tree_node::post_order_traversal, 4, 3, 12)
                    (boost::tree_node::post_order_traversal, 5, 4, 24)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 3)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::pre_order_traversal, 3, 2, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 3)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 3)
                    (boost::tree_node::post_order_traversal, 3, 2, 6)
                (boost::tree_node::post_order_traversal, 4, 5, 35)
            (boost::tree_node::post_order_traversal, 5, 6, 42);
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
        test_node<a_node_case>(a_root, bf_vals, pre_vals, post_vals, df_vals);
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::nary_node_base_gen<Selector>
              , DataMap
              , void
              , AccuYourUintKey
            >
            FNode;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_uint
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_char
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        FNode const
                      , AccuYourUintKey
                    >::type
                >
            >::type
            MoreValues;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_uint
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
                        FNode const
                      , example_keys::your_char
                    >::type
                  , typename boost::tree_node::result_of::value_at_key<
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
        typename boost::tree_node::result_of::value_at_key<
            FNode const
          , example_keys::your_uint
        >::type data = boost::tree_node::get<example_keys::your_uint>(*itr);

        if (1 < data)
        {
            for (unsigned int i = 0; i < data; ++i)
            {
                if (std::tr1::is_same<Selector,boost::slistS>::value)
                {
                    (*itr).emplace(
                        boost::fusion::make_pair<example_keys::your_uint>(
                            data - 1 - i
                        )
                      , boost::fusion::make_pair<example_keys::your_char>(
                            '0' + data - 1 - i
                        )
                    );
                }
                else
                {
                    (*itr).emplace(
                        boost::fusion::make_pair<example_keys::your_uint>(i)
                      , boost::fusion::make_pair<example_keys::your_char>(
                            '0' + i
                        )
                    );
                }
            }

        }
    }

    {
        MoreValues bf_vals, pre_vals, post_vals;
        DFMoreValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (5, '5', 31)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 7)
            (4, '4', 15)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 7)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[pre_vals]
            (5, '5', 31)(0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(3, '3', 7)(0, '0', 0)(1, '1', 1)(2, '2', 3)
            (0, '0', 0)(1, '1', 1)(4, '4', 15)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(3, '3', 7)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[post_vals]
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(2, '2', 3)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(2, '2', 3)
            (3, '3', 7)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(3, '3', 7)(4, '4', 15)(5, '5', 31);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, '5', 31)
                (boost::tree_node::pre_order_traversal, 0, '0', 0)
                (boost::tree_node::post_order_traversal, 0, '0', 0)
                (boost::tree_node::pre_order_traversal, 1, '1', 1)
                (boost::tree_node::post_order_traversal, 1, '1', 1)
                (boost::tree_node::pre_order_traversal, 2, '2', 3)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                (boost::tree_node::post_order_traversal, 2, '2', 3)
                (boost::tree_node::pre_order_traversal, 3, '3', 7)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::pre_order_traversal, 4, '4', 15)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::pre_order_traversal, 3, '3', 7)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::pre_order_traversal, 2, '2', 3)
                            (boost::tree_node::pre_order_traversal, 0, '0', 0)
                            (boost::tree_node::post_order_traversal, 0, '0', 0)
                            (boost::tree_node::pre_order_traversal, 1, '1', 1)
                            (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::post_order_traversal, 4, '4', 15)
            (boost::tree_node::post_order_traversal, 5, '5', 31);
        test_node<f_node_case>(f_root, bf_vals, pre_vals, post_vals, df_vals);

        typename FNode::iterator f_child_itr(f_root.begin());

        std::advance(f_child_itr, 3);
        f_child_itr = (*f_child_itr).begin();
        std::advance(f_child_itr, 2);
        boost::tree_node::put(*f_child_itr, example_keys::your_uint(), 7);
        bf_vals.clear();
        pre_vals.clear();
        post_vals.clear();
        df_vals.clear();

        emplacer[bf_vals]
            (5, '5', 36)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 12)
            (4, '4', 15)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (7, '2', 8)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 7)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[pre_vals]
            (5, '5', 36)(0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(3, '3', 12)(0, '0', 0)(1, '1', 1)(7, '2', 8)
            (0, '0', 0)(1, '1', 1)(4, '4', 15)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(3, '3', 7)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1);
        emplacer[post_vals]
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(2, '2', 3)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(7, '2', 8)
            (3, '3', 12)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(3, '3', 7)(4, '4', 15)(5, '5', 36);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, '5', 36)
                (boost::tree_node::pre_order_traversal, 0, '0', 0)
                (boost::tree_node::post_order_traversal, 0, '0', 0)
                (boost::tree_node::pre_order_traversal, 1, '1', 1)
                (boost::tree_node::post_order_traversal, 1, '1', 1)
                (boost::tree_node::pre_order_traversal, 2, '2', 3)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                (boost::tree_node::post_order_traversal, 2, '2', 3)
                (boost::tree_node::pre_order_traversal, 3, '3', 12)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 7, '2', 8)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 7, '2', 8)
                (boost::tree_node::post_order_traversal, 3, '3', 12)
                (boost::tree_node::pre_order_traversal, 4, '4', 15)
                    (boost::tree_node::pre_order_traversal, 0, '0', 0)
                    (boost::tree_node::post_order_traversal, 0, '0', 0)
                    (boost::tree_node::pre_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::pre_order_traversal, 2, '2', 3)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                    (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::pre_order_traversal, 3, '3', 7)
                        (boost::tree_node::pre_order_traversal, 0, '0', 0)
                        (boost::tree_node::post_order_traversal, 0, '0', 0)
                        (boost::tree_node::pre_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::pre_order_traversal, 2, '2', 3)
                            (boost::tree_node::pre_order_traversal, 0, '0', 0)
                            (boost::tree_node::post_order_traversal, 0, '0', 0)
                            (boost::tree_node::pre_order_traversal, 1, '1', 1)
                            (boost::tree_node::post_order_traversal, 1, '1', 1)
                        (boost::tree_node::post_order_traversal, 2, '2', 3)
                    (boost::tree_node::post_order_traversal, 3, '3', 7)
                (boost::tree_node::post_order_traversal, 4, '4', 15)
            (boost::tree_node::post_order_traversal, 5, '5', 36);
        test_node<f_node_case>(f_root, bf_vals, pre_vals, post_vals, df_vals);
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/boost/ptr_container/ptr_vector.hpp>
#include <boost/typeof/boost/ptr_container/ptr_deque.hpp>
#include <boost/typeof/boost/ptr_container/ptr_list.hpp>
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/container/vector.hpp>
#include <boost/typeof/boost/container/stable_vector.hpp>
#include <boost/typeof/boost/container/deque.hpp>
#include <boost/typeof/boost/container/list.hpp>
#include <boost/typeof/boost/container/slist.hpp>
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#endif  // BOOST_TYPEOF_EMULATION

int test_main(int argc, char** argv)
{
    test<boost::ptr_vecS>();
    test<boost::ptr_dequeS>();
    test<boost::ptr_listS>();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test<boost::vector_selector<boost::mpl::true_> >();
//    test<boost::stable_vecS>();
//    test<boost::deque_selector<boost::mpl::true_> >();
    test<boost::list_selector<boost::mpl::true_> >();
    test<boost::slistS>();
#endif

    return 0;
}

