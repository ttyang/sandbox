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

#include <boost/typeof/boost/tree_node/associative_node.hpp>
#include <boost/container_gen/is_unique_assoc_selector.hpp>

char const* names[] = {"able", "baker", "chuck", "dog", "easy", "fox"};

template <typename Select, typename Node>
void initialize(Node& root)
{
    for (boost::tree_node::breadth_first_iterator<Node> itr(root); itr; ++itr)
    {
        typename Node::traits::data_type const& data = get(
            *itr
          , boost::tree_node::data_key()
        );

        if (1 < data)
        {
            for (std::size_t i = 0; i < data; ++i)
            {
                for (std::size_t j = 0; j + i < data; ++j)
                {
                    typename Node::iterator find_itr(itr->find(names[j]));
                    bool not_found = find_itr == itr->end();
                    typename Node::iterator child_itr(
                        itr->emplace(names[j], i)
                    );
                    Node& child(
                        boost::tree_node::dereference_iterator(child_itr)
                    );
                    Node const& const_child(child);

                    if (not_found)
                    {
                        typename Node::pointer child_ptr(
                            child.get_parent_ptr()
                        );
                        BOOST_CHECK(
                            child_ptr == &*itr
//                          , "Ctor not linking child to parent."
                        );
                        BOOST_CHECK(
                            child_ptr == const_child.get_parent_ptr()
//                          , "Why are these pointers different?"
                        );
                    }
                    else if (
                        boost::is_unique_associative_selector<Select>::value
                    )
                    {
                        BOOST_CHECK(
                            find_itr->first == child_itr->first
//                          , "Keys do not match."
                        );
                        BOOST_CHECK(
                            get(
                                boost::tree_node::dereference_iterator(
                                    find_itr
                                )
                              , boost::tree_node::data_key()
                            ) == get(
                                const_child
                              , boost::tree_node::data_key()
                            )
//                          , "Ctor not linking parent to child."
                        );
                    }
                }
            }
        }
    }
}

template <typename Selector>
void test_unique_associative()
{
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
              boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                  boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_accumulation_base_gen<
                      boost::tree_node::with_count_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                          boost::tree_node::associative_node_base_gen<Selector>
                        >
                      >
                    , AccuAccuKey
                    >
                  >
                , AccuCountKey
                >
              >
            , char const*
            , boost::rational<long>
            , AccuHeightKey
            >
            ANode;
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_height<
                boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_count_base_gen<
                        boost::tree_node::associative_node_base_gen<Selector>
                    >
                >
              , char const*
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
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename ANode::traits::key_type
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
            KeyValues;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename ANode::traits::key_type
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
            DFKeyValues;

    ANode a_root(5);

    BOOST_CHECK(
        !a_root.get_parent_ptr()
//      , "Parent member uninitialized."
    );

    initialize<Selector>(a_root);

    {
        Values bf_vals, pre_vals, post_vals;
        KeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFValues df_vals;
        DFKeyValues df_d_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,1,6,
          5,0,11,boost::rational<long>(5,6))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,1,6,
          5,0,11,boost::rational<long>(5,6));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 1, 6)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 1, 6)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(5, 1, 6);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 1, 6)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 1, 6);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
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
        boost::tree_node::depth_first_iterator<ANode const>
            df_root_itr(a_root), df_copy_itr(a_copy);
        boost::tree_node::depth_first_descendant_iterator<ANode const>
            df_d_root_itr(a_root), df_d_copy_itr(a_copy);

        BOOST_CHECK(test_node_copies(bf_root_itr, bf_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(bf_d_root_itr, bf_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(pre_root_itr, pre_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(pre_d_root_itr, pre_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(post_root_itr, post_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(post_d_root_itr, post_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(df_d_root_itr, df_d_copy_itr)
        );
    }

    {
        typename ANode::iterator a_child_itr(
          boost::tree_node::dereference_iterator(
            a_root.find(names[2])
          ).insert(names[5], a_root)
        );
        Values bf_vals, pre_vals, post_vals;
        KeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFValues df_vals;
        DFKeyValues df_d_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 3, 12, 10, 2, 34, boost::rational<long>(5, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 3, 12, 10, 2, 34, boost::rational<long>(5, 3))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 3, 12, 10, 2, 34, boost::rational<long>(5, 3));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("fox", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            ("fox", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("fox", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("chuck", 0, 2, 7, 5, 1, 18, boost::rational<long>(10, 7))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",0,2,7,
          5,1,18,boost::rational<long>(10,7))
            (boost::tree_node::pre_order_traversal,"fox",5,1,6,
            5,0,11,boost::rational<long>(5,6))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"fox",5,1,6,
            5,0,11,boost::rational<long>(5,6))
          (boost::tree_node::post_order_traversal,"chuck",0,2,7,
          5,1,18,boost::rational<long>(10,7))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,3,12,
          10,2,34,boost::rational<long>(5,3))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,2,7,
            5,1,18,boost::rational<long>(10,7))
              (boost::tree_node::pre_order_traversal,5,1,6,
              5,0,11,boost::rational<long>(5,6))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,5,1,6,
              5,0,11,boost::rational<long>(5,6))
            (boost::tree_node::post_order_traversal,0,2,7,
            5,1,18,boost::rational<long>(10,7))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,3,12,
          10,2,34,boost::rational<long>(5,3));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 3, 12)(0, 0, 1)(0, 0, 1)(0, 2, 7)(0, 0, 1)(0, 0, 1)
            (5, 1, 6)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 3, 12)(0, 0, 1)(0, 0, 1)(0, 2, 7)(5, 1, 6)(0, 0, 1)
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(5, 1, 6)(0, 2, 7)(0, 0, 1)(0, 0, 1)(5, 3, 12);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 2, 7)
            ("dog", 0, 0, 1)("easy", 0, 0, 1)("fox", 5, 1, 6)
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 2, 7)
            ("fox", 5, 1, 6)("able", 0, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("dog", 0, 0, 1)("easy", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("baker", 0, 0, 1)("chuck", 0, 0, 1)("dog", 0, 0, 1)
            ("easy", 0, 0, 1)("fox", 5, 1, 6)("chuck", 0, 2, 7)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 2, 7)
                (boost::tree_node::pre_order_traversal, "fox", 5, 1, 6)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "fox", 5, 1, 6)
            (boost::tree_node::post_order_traversal, "chuck", 0, 2, 7)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 3, 12)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 2, 7)
                    (boost::tree_node::pre_order_traversal, 5, 1, 6)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 5, 1, 6)
                (boost::tree_node::post_order_traversal, 0, 2, 7)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 3, 12);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        a_root = boost::tree_node::dereference_iterator(a_child_itr);
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,1,6,
          5,0,11,boost::rational<long>(5,6))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,1,6,
          5,0,11,boost::rational<long>(5,6));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 1, 6)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 1, 6)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(5, 1, 6);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 1, 6)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 1, 6);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        a_child_itr = a_root.find(names[2]);
        boost::tree_node::dereference_iterator(a_child_itr) = a_root;
        test_associative_node<a_node_case>(
            boost::tree_node::dereference_iterator(a_child_itr)
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 2, 11, 10, 1, 26, boost::rational<long>(15, 11))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 2, 11, 10, 1, 26, boost::rational<long>(15, 11))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 2, 11, 10, 1, 26, boost::rational<long>(15, 11));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 6, 5, 0, 11, boost::rational<long>(5, 6))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",5,1,6,
          5,0,11,boost::rational<long>(5,6))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"easy",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"easy",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",5,1,6,
          5,0,11,boost::rational<long>(5,6))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,2,11,
          10,1,26,boost::rational<long>(15,11))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,5,1,6,
            5,0,11,boost::rational<long>(5,6))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,5,1,6,
            5,0,11,boost::rational<long>(5,6))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,2,11,
          10,1,26,boost::rational<long>(15,11));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 2, 11)(0, 0, 1)(0, 0, 1)(5, 1, 6)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 2, 11)(0, 0, 1)(0, 0, 1)(5, 1, 6)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(5, 1, 6)(0, 0, 1)(0, 0, 1)(5, 2, 11);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 5, 1, 6)
            ("dog", 0, 0, 1)("easy", 0, 0, 1)("able", 0, 0, 1)
            ("baker", 0, 0, 1)("chuck", 0, 0, 1)("dog", 0, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 5, 1, 6)
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 0, 0, 1)
            ("dog", 0, 0, 1)("easy", 0, 0, 1)("dog", 0, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("baker", 0, 0, 1)("chuck", 0, 0, 1)("dog", 0, 0, 1)
            ("easy", 0, 0, 1)("chuck", 5, 1, 6)("dog", 0, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 5, 1, 6)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 5, 1, 6)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 2, 11)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 5, 1, 6)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 5, 1, 6)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 2, 11);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(
                a_child_itr
            ).erase(names[1]) == 1
        );
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 2, 10, 10, 1, 23, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 2, 10, 10, 1, 23, boost::rational<long>(3, 2))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 2, 10, 10, 1, 23, boost::rational<long>(3, 2));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 5, 1, 5, 5, 0, 9, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",5,1,5,
          5,0,9,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"easy",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"easy",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",5,1,5,
          5,0,9,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,2,10,
          10,1,23,boost::rational<long>(3,2))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,5,1,5,
            5,0,9,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,5,1,5,
            5,0,9,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,2,10,
          10,1,23,boost::rational<long>(3,2));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 2, 10)(0, 0, 1)(0, 0, 1)(5, 1, 5)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 2, 10)(0, 0, 1)(0, 0, 1)(5, 1, 5)(0, 0, 1)(0, 0, 1)
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)(0, 0, 1)
            (5, 1, 5)(0, 0, 1)(0, 0, 1)(5, 2, 10);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 5, 1, 5)
            ("dog", 0, 0, 1)("easy", 0, 0, 1)("able", 0, 0, 1)
            ("chuck", 0, 0, 1)("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("chuck", 5, 1, 5)
            ("able", 0, 0, 1)("chuck", 0, 0, 1)("dog", 0, 0, 1)
            ("easy", 0, 0, 1)("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("chuck", 0, 0, 1)("dog", 0, 0, 1)("easy", 0, 0, 1)
            ("chuck", 5, 1, 5)("dog", 0, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 5, 1, 5)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 5, 1, 5)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 5, 1, 5)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 5, 1, 5)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 2, 10);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::associative_node_base_gen<Selector>
              , char const*
              , DataMap
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
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename FNode::traits::key_type
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
            MoreKeyValues;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename FNode::traits::key_type
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
            DFMoreKeyValues;

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
        >::type data = boost::tree_node::get<
            example_keys::your_uint
        >(boost::tree_node::dereference_iterator(itr));

        if (1 < data)
        {
            for (unsigned int i = 0; i < data; ++i)
            {
                for (std::size_t j = 0; j + i < data; ++j)
                {
                    itr->emplace(
                        names[j]
                      , boost::fusion::make_pair<example_keys::your_uint>(i)
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
        MoreKeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFMoreKeyValues df_d_vals;
        DFMoreValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (5, '5', 5)(0, '0', 0)(0, '0', 0)(0, '0', 0)(0, '0', 0)
            (0, '0', 0);
        emplacer[pre_vals]
            (5, '5', 5)(0, '0', 0)(0, '0', 0)(0, '0', 0)(0, '0', 0)
            (0, '0', 0);
        emplacer[post_vals]
            (0, '0', 0)(0, '0', 0)(0, '0', 0)(0, '0', 0)(0, '0', 0)
            (5, '5', 5);
        emplacer[bf_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 0, '0', 0)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[pre_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 0, '0', 0)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[post_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 0, '0', 0)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",0,'0',0)
          (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::pre_order_traversal,"easy",0,'0',0)
          (boost::tree_node::post_order_traversal,"easy",0,'0',0);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,'5',5)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
          (boost::tree_node::post_order_traversal,5,'5',5);
        test_associative_node<f_node_case>(
            f_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        put(
            boost::tree_node::dereference_iterator(f_root.find(names[2]))
          , example_keys::your_uint()
          , 7
        );
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

        emplacer[bf_vals]
            (5, '5', 12)(0, '0', 0)(0, '0', 0)(7, '0', 7)(0, '0', 0)
            (0, '0', 0);
        emplacer[pre_vals]
            (5, '5', 12)(0, '0', 0)(0, '0', 0)(7, '0', 7)(0, '0', 0)
            (0, '0', 0);
        emplacer[post_vals]
            (0, '0', 0)(0, '0', 0)(7, '0', 7)(0, '0', 0)(0, '0', 0)
            (5, '5', 12);
        emplacer[bf_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 7, '0', 7)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[pre_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 7, '0', 7)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[post_d_vals]
            ("able", 0, '0', 0)("baker", 0, '0', 0)("chuck", 7, '0', 7)
            ("dog", 0, '0', 0)("easy", 0, '0', 0);
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",0,'0',0)
          (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::pre_order_traversal,"chuck",7,'0',7)
          (boost::tree_node::post_order_traversal,"chuck",7,'0',7)
          (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::pre_order_traversal,"easy",0,'0',0)
          (boost::tree_node::post_order_traversal,"easy",0,'0',0);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,'5',12)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,7,'0',7)
            (boost::tree_node::post_order_traversal,7,'0',7)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
          (boost::tree_node::post_order_traversal,5,'5',12);
        test_associative_node<f_node_case>(
            f_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
}

template <typename Selector>
void test_multiple_associative()
{
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_accumulation<
              boost::tree_node::with_height_base_gen<
                boost::tree_node::with_accumulation_base_gen<
                  boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_accumulation_base_gen<
                      boost::tree_node::with_count_base_gen<
                        boost::tree_node::with_accumulation_base_gen<
                          boost::tree_node::associative_node_base_gen<Selector>
                        >
                      >
                    , AccuAccuKey
                    >
                  >
                , AccuCountKey
                >
              >
            , char const*
            , boost::rational<long>
            , AccuHeightKey
            >
            ANode;
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef boost::tree_node::with_height<
                boost::tree_node::with_position_base_gen<
                    boost::tree_node::with_count_base_gen<
                        boost::tree_node::associative_node_base_gen<Selector>
                    >
                >
              , char const*
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
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename ANode::traits::key_type
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
            KeyValues;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename ANode::traits::key_type
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
            DFKeyValues;

    ANode a_root(5);

    BOOST_CHECK(
        !a_root.get_parent_ptr()
//      , "Parent member uninitialized."
    );

    initialize<Selector>(a_root);

    {
        Values bf_vals, pre_vals, post_vals;
        KeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFValues df_vals;
        DFKeyValues df_d_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,4,68,
          55,3,211,boost::rational<long>(145,68))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,4,68,
          55,3,211,boost::rational<long>(145,68));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 68)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 4, 68)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(5, 4, 68);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("baker", 3, 2, 10)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 3, 2, 10)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 2, 1, 4)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 68)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 4, 3, 26)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 4, 68);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
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
        boost::tree_node::depth_first_iterator<ANode const>
            df_root_itr(a_root), df_copy_itr(a_copy);
        boost::tree_node::depth_first_descendant_iterator<ANode const>
            df_d_root_itr(a_root), df_d_copy_itr(a_copy);

        BOOST_CHECK(test_node_copies(bf_root_itr, bf_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(bf_d_root_itr, bf_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(pre_root_itr, pre_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(pre_d_root_itr, pre_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(post_root_itr, post_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(post_d_root_itr, post_d_copy_itr)
        );
        BOOST_CHECK(test_node_copies(df_root_itr, df_copy_itr));
        BOOST_CHECK(
            test_associative_node_copies(df_d_root_itr, df_d_copy_itr)
        );
    }

    {
        typename ANode::iterator a_child_itr(
          boost::tree_node::dereference_iterator(
            a_root.find(names[2])
          ).insert(names[5], a_root)
        );
        Values bf_vals, pre_vals, post_vals;
        KeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFValues df_vals;
        DFKeyValues df_d_vals;
        Emplacer emplacer;

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 136, 110, 5, 558, boost::rational<long>(50, 17))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 6, 136, 110, 5, 558, boost::rational<long>(50, 17))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 6, 136, 110, 5, 558, boost::rational<long>(50, 17));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("fox", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            ("fox", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("fox", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("chuck", 0, 5, 69, 55, 4, 280, boost::rational<long>(200, 69))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"chuck",0,5,69,
          55,4,280,boost::rational<long>(200,69))
            (boost::tree_node::pre_order_traversal,"fox",5,4,68,
            55,3,211,boost::rational<long>(145,68))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"fox",5,4,68,
            55,3,211,boost::rational<long>(145,68))
          (boost::tree_node::post_order_traversal,"chuck",0,5,69,
          55,4,280,boost::rational<long>(200,69))
          (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,6,136,
          110,5,558,boost::rational<long>(50,17))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,0,5,69,
            55,4,280,boost::rational<long>(200,69))
              (boost::tree_node::pre_order_traversal,5,4,68,
              55,3,211,boost::rational<long>(145,68))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,5,4,68,
              55,3,211,boost::rational<long>(145,68))
            (boost::tree_node::post_order_traversal,0,5,69,
            55,4,280,boost::rational<long>(200,69))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,6,136,
          110,5,558,boost::rational<long>(50,17));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 136)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 5, 69)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(5, 4, 68)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 6, 136)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 5, 69)
            (5, 4, 68)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(5, 4, 68)
            (0, 5, 69)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(5, 6, 136);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("baker", 3, 2, 10)
            ("chuck", 0, 5, 69)("chuck", 1, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("fox", 5, 4, 68)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 3, 2, 10)
            ("able", 4, 3, 26)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("baker", 3, 2, 10)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("chuck", 2, 1, 4)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 3, 2, 10)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 5, 69)("fox", 5, 4, 68)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 3, 2, 10)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("able", 4, 3, 26)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("baker", 3, 2, 10)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("chuck", 2, 1, 4)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1)("fox", 5, 4, 68)
            ("chuck", 0, 5, 69)("chuck", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 5, 69)
                (boost::tree_node::pre_order_traversal, "fox", 5, 4, 68)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "fox", 5, 4, 68)
            (boost::tree_node::post_order_traversal, "chuck", 0, 5, 69)
            (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 136)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 4, 3, 26)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 5, 69)
                    (boost::tree_node::pre_order_traversal, 5, 4, 68)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 4, 3, 26)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 4, 3, 26)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 5, 4, 68)
                (boost::tree_node::post_order_traversal, 0, 5, 69)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 6, 136);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        a_root = boost::tree_node::dereference_iterator(a_child_itr);
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,4,68,
          55,3,211,boost::rational<long>(145,68))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,4,68,
          55,3,211,boost::rational<long>(145,68));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 4, 68)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 4, 68)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(5, 4, 68);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("baker", 3, 2, 10)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 3, 2, 10)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 2, 1, 4)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 4, 68)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 4, 3, 26)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 4, 68);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        a_child_itr = boost::begin(a_root.equal_range(names[2]));

        while (boost::tree_node::dereference_iterator(a_child_itr).empty())
        {
            ++a_child_itr;
        }

        a_child_itr = boost::begin(
            boost::tree_node::dereference_iterator(
                a_child_itr
            ).equal_range(names[1])
        );
        boost::tree_node::dereference_iterator(a_child_itr) = a_root;
        test_associative_node<a_node_case>(
            boost::tree_node::dereference_iterator(a_child_itr)
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 135, 110, 5, 555, boost::rational<long>(80, 27))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 6, 135, 110, 5, 555, boost::rational<long>(80, 27))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            (2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 6, 135, 110, 5, 555, boost::rational<long>(80, 27));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 5, 4, 68, 55, 3, 211, boost::rational<long>(145, 68))
            ("chuck", 2, 5, 71, 58, 4, 284, boost::rational<long>(204, 71))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"chuck",2,5,71,
          58,4,284,boost::rational<long>(204,71))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",5,4,68,
            55,3,211,boost::rational<long>(145,68))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",5,4,68,
            55,3,211,boost::rational<long>(145,68))
          (boost::tree_node::post_order_traversal,"chuck",2,5,71,
          58,4,284,boost::rational<long>(204,71))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,6,135,
          110,5,555,boost::rational<long>(80,27))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,5,71,
            58,4,284,boost::rational<long>(204,71))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,5,4,68,
              55,3,211,boost::rational<long>(145,68))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,5,4,68,
              55,3,211,boost::rational<long>(145,68))
            (boost::tree_node::post_order_traversal,2,5,71,
            58,4,284,boost::rational<long>(204,71))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,6,135,
          110,5,555,boost::rational<long>(80,27));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 135)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (2, 5, 71)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(5, 4, 68)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 6, 135)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 5, 71)(0, 0, 1)(1, 0, 1)(5, 4, 68)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(4, 3, 26)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(5, 4, 68)(2, 5, 71)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(5, 6, 135);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("baker", 3, 2, 10)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 5, 71)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 5, 4, 68)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 3, 2, 10)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("baker", 3, 2, 10)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 1, 4)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 5, 71)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 5, 4, 68)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 3, 2, 10)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 4, 3, 26)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 3, 2, 10)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("chuck", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 3, 2, 10)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("baker", 3, 2, 10)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("baker", 5, 4, 68)("chuck", 2, 5, 71)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 2, 5, 71)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 5, 4, 68)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 5, 4, 68)
            (boost::tree_node::post_order_traversal, "chuck", 2, 5, 71)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 135)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 4, 3, 26)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 5, 71)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 5, 4, 68)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 4, 3, 26)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 4, 3, 26)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 5, 4, 68)
                (boost::tree_node::post_order_traversal, 2, 5, 71)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 6, 135);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(
                a_child_itr
            ).erase(names[1]) == 4
        );
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 119, 98, 5, 476, boost::rational<long>(345, 119))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_vals]
            (5, 6, 119, 98, 5, 476, boost::rational<long>(345, 119))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_vals]
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            (2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            (0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            (5, 6, 119, 98, 5, 476, boost::rational<long>(345, 119));
        emplacer[bf_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[pre_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[post_d_vals]
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 3, 2, 10, 8, 1, 22, boost::rational<long>(7, 5))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 4, 3, 26, 21, 2, 69, boost::rational<long>(23, 13))
            ("chuck", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("able", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("able", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("baker", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("chuck", 2, 1, 4, 3, 0, 7, boost::rational<long>(1, 1))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("baker", 5, 4, 52, 43, 3, 164, boost::rational<long>(57, 26))
            ("chuck", 2, 5, 55, 46, 4, 221, boost::rational<long>(161, 55))
            ("dog", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1))
            ("dog", 1, 0, 1, 1, 0, 1, boost::rational<long>(1, 1))
            ("easy", 0, 0, 1, 0, 0, 1, boost::rational<long>(0, 1));
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"able",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"baker",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"chuck",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"dog",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"able",4,3,26,
          21,2,69,boost::rational<long>(23,13))
          (boost::tree_node::pre_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"baker",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",2,1,4,
          3,0,7,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"baker",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"baker",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"chuck",0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"baker",3,2,10,
          8,1,22,boost::rational<long>(7,5))
          (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"chuck",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"chuck",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"chuck",2,5,55,
          46,4,221,boost::rational<long>(161,55))
            (boost::tree_node::pre_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"able",0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,"able",1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,"baker",5,4,52,
            43,3,164,boost::rational<long>(57,26))
              (boost::tree_node::pre_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"able",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"baker",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"baker",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"able",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,"able",1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,"baker",0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"chuck",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"chuck",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"dog",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"able",4,3,26,
              21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"chuck",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"able",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,"able",1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,"baker",0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"chuck",2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"dog",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,"dog",1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,"easy",0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,"baker",5,4,52,
            43,3,164,boost::rational<long>(57,26))
          (boost::tree_node::post_order_traversal,"chuck",2,5,55,
          46,4,221,boost::rational<long>(161,55))
          (boost::tree_node::pre_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"dog",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::pre_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::post_order_traversal,"dog",1,0,1,
          1,0,1,boost::rational<long>(1,1))
          (boost::tree_node::pre_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,"easy",0,0,1,
          0,0,1,boost::rational<long>(0,1));
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,6,119,
          98,5,476,boost::rational<long>(345,119))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,3,2,10,
              8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,4,3,26,
            21,2,69,boost::rational<long>(23,13))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,2,1,4,
            3,0,7,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,2,1,4,
              3,0,7,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,3,2,10,
            8,1,22,boost::rational<long>(7,5))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,2,5,55,
            46,4,221,boost::rational<long>(161,55))
              (boost::tree_node::pre_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,0,0,1,
              0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::pre_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::post_order_traversal,1,0,1,
              1,0,1,boost::rational<long>(1,1))
              (boost::tree_node::pre_order_traversal,5,4,52,
              43,3,164,boost::rational<long>(57,26))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,3,2,10,
                8,1,22,boost::rational<long>(7,5))
                (boost::tree_node::pre_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,3,2,10,
                  8,1,22,boost::rational<long>(7,5))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,2,1,4,
                  3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,4,3,26,
                21,2,69,boost::rational<long>(23,13))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::pre_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::post_order_traversal,1,0,1,
                  1,0,1,boost::rational<long>(1,1))
                  (boost::tree_node::pre_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                  (boost::tree_node::post_order_traversal,0,0,1,
                  0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,2,1,4,
                3,0,7,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::pre_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::post_order_traversal,1,0,1,
                1,0,1,boost::rational<long>(1,1))
                (boost::tree_node::pre_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
                (boost::tree_node::post_order_traversal,0,0,1,
                0,0,1,boost::rational<long>(0,1))
              (boost::tree_node::post_order_traversal,5,4,52,
              43,3,164,boost::rational<long>(57,26))
            (boost::tree_node::post_order_traversal,2,5,55,
            46,4,221,boost::rational<long>(161,55))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::pre_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::post_order_traversal,1,0,1,
            1,0,1,boost::rational<long>(1,1))
            (boost::tree_node::pre_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
            (boost::tree_node::post_order_traversal,0,0,1,
            0,0,1,boost::rational<long>(0,1))
          (boost::tree_node::post_order_traversal,5,6,119,
          98,5,476,boost::rational<long>(345,119));
#else  // !defined BOOST_TREE_NODE_CAN_USE_FUSION
        emplacer[bf_vals]
            (5, 6, 119)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (2, 5, 55)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(5, 4, 52)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(3, 2, 10)(4, 3, 26)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[pre_vals]
            (5, 6, 119)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 5, 55)(0, 0, 1)(1, 0, 1)(5, 4, 52)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)(0, 0, 1)(1, 0, 1)
            (2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(2, 1, 4)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(0, 0, 1)
            (1, 0, 1)(0, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1);
        emplacer[post_vals]
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(4, 3, 26)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(3, 2, 10)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(1, 0, 1)(0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(4, 3, 26)(0, 0, 1)(1, 0, 1)(0, 0, 1)(1, 0, 1)
            (0, 0, 1)(2, 1, 4)(0, 0, 1)(1, 0, 1)(0, 0, 1)(5, 4, 52)
            (2, 5, 55)(0, 0, 1)(1, 0, 1)(0, 0, 1)(5, 6, 119);
        emplacer[bf_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("able", 4, 3, 26)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("baker", 2, 1, 4)("baker", 3, 2, 10)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 5, 55)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 5, 4, 52)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 3, 2, 10)("able", 4, 3, 26)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("chuck", 2, 1, 4)
            ("dog", 0, 0, 1)("dog", 1, 0, 1)("easy", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1);
        emplacer[pre_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 4, 3, 26)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 1, 0, 1)("dog", 0, 0, 1)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 5, 55)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 5, 4, 52)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 3, 2, 10)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 4, 3, 26)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("baker", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("chuck", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[post_d_vals]
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("able", 0, 0, 1)("able", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("able", 2, 1, 4)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("chuck", 0, 0, 1)("able", 3, 2, 10)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("baker", 2, 1, 4)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("dog", 0, 0, 1)("able", 4, 3, 26)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("baker", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("baker", 3, 2, 10)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("able", 0, 0, 1)
            ("able", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("able", 2, 1, 4)("baker", 0, 0, 1)
            ("baker", 1, 0, 1)("chuck", 0, 0, 1)("able", 3, 2, 10)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("able", 0, 0, 1)("able", 1, 0, 1)("able", 0, 0, 1)
            ("able", 1, 0, 1)("baker", 0, 0, 1)("able", 2, 1, 4)
            ("baker", 0, 0, 1)("baker", 1, 0, 1)("chuck", 0, 0, 1)
            ("able", 3, 2, 10)("baker", 0, 0, 1)("baker", 1, 0, 1)
            ("able", 0, 0, 1)("able", 1, 0, 1)("baker", 0, 0, 1)
            ("baker", 2, 1, 4)("chuck", 0, 0, 1)("chuck", 1, 0, 1)
            ("dog", 0, 0, 1)("able", 4, 3, 26)("chuck", 0, 0, 1)
            ("chuck", 1, 0, 1)("able", 0, 0, 1)("able", 1, 0, 1)
            ("baker", 0, 0, 1)("chuck", 2, 1, 4)("dog", 0, 0, 1)
            ("dog", 1, 0, 1)("easy", 0, 0, 1)("baker", 5, 4, 52)
            ("chuck", 2, 5, 55)("dog", 0, 0, 1)("dog", 1, 0, 1)
            ("easy", 0, 0, 1);
        emplacer[df_d_vals]
            (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
            (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
            (boost::tree_node::pre_order_traversal, "baker", 3, 2, 10)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "baker", 3, 2, 10)
            (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "chuck", 2, 5, 55)
                (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                (boost::tree_node::pre_order_traversal, "baker", 5, 4, 52)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "able", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "baker", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "chuck", 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
                    (boost::tree_node::post_order_traversal, "easy", 0, 0, 1)
                (boost::tree_node::post_order_traversal, "baker", 5, 4, 52)
            (boost::tree_node::post_order_traversal, "chuck", 2, 5, 55)
            (boost::tree_node::pre_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 0, 0, 1)
            (boost::tree_node::pre_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::post_order_traversal, "dog", 1, 0, 1)
            (boost::tree_node::pre_order_traversal, "easy", 0, 0, 1)
            (boost::tree_node::post_order_traversal, "easy", 0, 0, 1);
        emplacer[df_vals]
            (boost::tree_node::pre_order_traversal, 5, 6, 119)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 4, 3, 26)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 4, 3, 26)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 2, 1, 4)
                (boost::tree_node::pre_order_traversal, 3, 2, 10)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 2, 1, 4)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 3, 2, 10)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 2, 5, 55)
                    (boost::tree_node::pre_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::pre_order_traversal, 1, 0, 1)
                    (boost::tree_node::post_order_traversal, 1, 0, 1)
                    (boost::tree_node::pre_order_traversal, 5, 4, 52)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 3, 2, 10)
                        (boost::tree_node::pre_order_traversal, 4, 3, 26)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 3, 2, 10)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 4, 3, 26)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 2, 1, 4)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                            (boost::tree_node::pre_order_traversal, 1, 0, 1)
                            (boost::tree_node::post_order_traversal, 1, 0, 1)
                            (boost::tree_node::pre_order_traversal, 0, 0, 1)
                            (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 2, 1, 4)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                        (boost::tree_node::pre_order_traversal, 1, 0, 1)
                        (boost::tree_node::post_order_traversal, 1, 0, 1)
                        (boost::tree_node::pre_order_traversal, 0, 0, 1)
                        (boost::tree_node::post_order_traversal, 0, 0, 1)
                    (boost::tree_node::post_order_traversal, 5, 4, 52)
                (boost::tree_node::post_order_traversal, 2, 5, 55)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
                (boost::tree_node::pre_order_traversal, 1, 0, 1)
                (boost::tree_node::post_order_traversal, 1, 0, 1)
                (boost::tree_node::pre_order_traversal, 0, 0, 1)
                (boost::tree_node::post_order_traversal, 0, 0, 1)
            (boost::tree_node::post_order_traversal, 5, 6, 119);
#endif  // BOOST_NO_SFINAE
        test_associative_node<a_node_case>(
            a_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
    }

#if defined BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
    typedef boost::tree_node::with_accumulation<
                boost::tree_node::associative_node_base_gen<Selector>
              , char const*
              , DataMap
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
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    typename FNode::traits::key_type
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
            MoreKeyValues;
    typedef typename boost::container_gen<
                boost::dequeS
              , boost::tuples::tuple<
                    boost::tree_node::traversal_state
                  , typename FNode::traits::key_type
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
            DFMoreKeyValues;

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
        >::type data = boost::tree_node::get<
            example_keys::your_uint
        >(boost::tree_node::dereference_iterator(itr));

        if (1 < data)
        {
            for (unsigned int i = 0; i < data; ++i)
            {
                for (std::size_t j = 0; j + i < data; ++j)
                {
                    itr->emplace(
                        names[j]
                      , boost::fusion::make_pair<example_keys::your_uint>(i)
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
        MoreKeyValues bf_d_vals, pre_d_vals, post_d_vals;
        DFMoreKeyValues df_d_vals;
        DFMoreValues df_vals;
        Emplacer emplacer;

        emplacer[bf_vals]
            (5, '5', 55)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)
            (4, '4', 21)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0);
        emplacer[pre_vals]
            (5, '5', 55)(0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(3, '3', 8)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(4, '4', 21)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(3, '3', 8)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(3, '3', 8)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0);
        emplacer[post_vals]
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (3, '3', 8)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(3, '3', 8)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(4, '4', 21)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(3, '3', 8)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(5, '5', 55);
        emplacer[bf_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 3, '3', 8)("able", 4, '4', 21)("baker", 0, '0', 0)
            ("baker", 1, '1', 1)("baker", 2, '2', 3)("baker", 3, '3', 8)
            ("chuck", 0, '0', 0)("chuck", 1, '1', 1)("chuck", 2, '2', 3)
            ("dog", 0, '0', 0)("dog", 1, '1', 1)("easy", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 3, '3', 8)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("baker", 2, '2', 3)("chuck", 0, '0', 0)("chuck", 1, '1', 1)
            ("dog", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0);
        emplacer[pre_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 4, '4', 21)("able", 0, '0', 0)
            ("able", 1, '1', 1)("able", 2, '2', 3)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 3, '3', 8)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("chuck", 0, '0', 0)("chuck", 1, '1', 1)("dog", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("baker", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("chuck", 0, '0', 0)("chuck", 1, '1', 1)
            ("chuck", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("dog", 0, '0', 0)("dog", 1, '1', 1)
            ("easy", 0, '0', 0);
        emplacer[post_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("able", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 3, '3', 8)("baker", 0, '0', 0)
            ("baker", 1, '1', 1)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 2, '2', 3)("chuck", 0, '0', 0)
            ("chuck", 1, '1', 1)("dog", 0, '0', 0)("able", 4, '4', 21)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("baker", 3, '3', 8)("chuck", 0, '0', 0)("chuck", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("chuck", 2, '2', 3)("dog", 0, '0', 0)("dog", 1, '1', 1)
            ("easy", 0, '0', 0);
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",0,'0',0)
          (boost::tree_node::pre_order_traversal,"able",1,'1',1)
          (boost::tree_node::post_order_traversal,"able",1,'1',1)
          (boost::tree_node::pre_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",2,'2',3)
          (boost::tree_node::pre_order_traversal,"able",3,'3',8)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",3,'3',8)
          (boost::tree_node::pre_order_traversal,"able",4,'4',21)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",3,'3',8)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"able",2,'2',3)
                (boost::tree_node::pre_order_traversal,"able",0,'0',0)
                (boost::tree_node::post_order_traversal,"able",0,'0',0)
                (boost::tree_node::pre_order_traversal,"able",1,'1',1)
                (boost::tree_node::post_order_traversal,"able",1,'1',1)
                (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
                (boost::tree_node::post_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
              (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
              (boost::tree_node::post_order_traversal,"baker",1,'1',1)
              (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
              (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",3,'3',8)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",2,'2',3)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::pre_order_traversal,"chuck",1,'1',1)
            (boost::tree_node::post_order_traversal,"chuck",1,'1',1)
            (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
            (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",4,'4',21)
          (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
          (boost::tree_node::post_order_traversal,"baker",1,'1',1)
          (boost::tree_node::pre_order_traversal,"baker",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",2,'2',3)
          (boost::tree_node::pre_order_traversal,"baker",3,'3',8)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",3,'3',8)
          (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::pre_order_traversal,"chuck",1,'1',1)
          (boost::tree_node::post_order_traversal,"chuck",1,'1',1)
          (boost::tree_node::pre_order_traversal,"chuck",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"chuck",2,'2',3)
          (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::pre_order_traversal,"dog",1,'1',1)
          (boost::tree_node::post_order_traversal,"dog",1,'1',1)
          (boost::tree_node::pre_order_traversal,"easy",0,'0',0)
          (boost::tree_node::post_order_traversal,"easy",0,'0',0);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,'5',55)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,3,'3',8)
            (boost::tree_node::pre_order_traversal,4,'4',21)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,3,'3',8)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,2,'2',3)
                  (boost::tree_node::pre_order_traversal,0,'0',0)
                  (boost::tree_node::post_order_traversal,0,'0',0)
                  (boost::tree_node::pre_order_traversal,1,'1',1)
                  (boost::tree_node::post_order_traversal,1,'1',1)
                  (boost::tree_node::pre_order_traversal,0,'0',0)
                  (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,4,'4',21)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,3,'3',8)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
          (boost::tree_node::post_order_traversal,5,'5',55);
        test_associative_node<f_node_case>(
            f_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );

        put(
            boost::tree_node::dereference_iterator(f_root.find(names[2]))
          , example_keys::your_uint()
          , 7
        );
        bf_vals.clear();
        bf_d_vals.clear();
        pre_vals.clear();
        pre_d_vals.clear();
        post_vals.clear();
        post_d_vals.clear();
        df_vals.clear();
        df_d_vals.clear();

        emplacer[bf_vals]
            (5, '5', 62)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)
            (4, '4', 21)(0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)
            (7, '0', 7)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(3, '3', 8)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0);
        emplacer[pre_vals]
            (5, '5', 62)(0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(3, '3', 8)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(4, '4', 21)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(3, '3', 8)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(0, '0', 0)(1, '1', 1)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(3, '3', 8)
            (0, '0', 0)(1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(0, '0', 0)(1, '1', 1)(0, '0', 0)(7, '0', 7)
            (1, '1', 1)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (0, '0', 0)(1, '1', 1)(0, '0', 0);
        emplacer[post_vals]
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (3, '3', 8)(0, '0', 0)(1, '1', 1)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(3, '3', 8)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(4, '4', 21)(0, '0', 0)(1, '1', 1)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)(1, '1', 1)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(3, '3', 8)(7, '0', 7)(1, '1', 1)
            (0, '0', 0)(1, '1', 1)(0, '0', 0)(2, '2', 3)(0, '0', 0)
            (1, '1', 1)(0, '0', 0)(5, '5', 62);
        emplacer[bf_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 3, '3', 8)("able", 4, '4', 21)("baker", 0, '0', 0)
            ("baker", 1, '1', 1)("baker", 2, '2', 3)("baker", 3, '3', 8)
            ("chuck", 7, '0', 7)("chuck", 1, '1', 1)("chuck", 2, '2', 3)
            ("dog", 0, '0', 0)("dog", 1, '1', 1)("easy", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 3, '3', 8)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("baker", 2, '2', 3)("chuck", 0, '0', 0)("chuck", 1, '1', 1)
            ("dog", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0);
        emplacer[pre_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 4, '4', 21)("able", 0, '0', 0)
            ("able", 1, '1', 1)("able", 2, '2', 3)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 3, '3', 8)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("chuck", 0, '0', 0)("chuck", 1, '1', 1)("dog", 0, '0', 0)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("baker", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("chuck", 7, '0', 7)("chuck", 1, '1', 1)
            ("chuck", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("dog", 0, '0', 0)("dog", 1, '1', 1)
            ("easy", 0, '0', 0);
        emplacer[post_d_vals]
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("able", 3, '3', 8)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 2, '2', 3)("able", 0, '0', 0)("able", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("able", 2, '2', 3)("baker", 0, '0', 0)("baker", 1, '1', 1)
            ("chuck", 0, '0', 0)("able", 3, '3', 8)("baker", 0, '0', 0)
            ("baker", 1, '1', 1)("able", 0, '0', 0)("able", 1, '1', 1)
            ("baker", 0, '0', 0)("baker", 2, '2', 3)("chuck", 0, '0', 0)
            ("chuck", 1, '1', 1)("dog", 0, '0', 0)("able", 4, '4', 21)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("baker", 2, '2', 3)
            ("able", 0, '0', 0)("able", 1, '1', 1)("able", 0, '0', 0)
            ("able", 1, '1', 1)("baker", 0, '0', 0)("able", 2, '2', 3)
            ("baker", 0, '0', 0)("baker", 1, '1', 1)("chuck", 0, '0', 0)
            ("baker", 3, '3', 8)("chuck", 7, '0', 7)("chuck", 1, '1', 1)
            ("able", 0, '0', 0)("able", 1, '1', 1)("baker", 0, '0', 0)
            ("chuck", 2, '2', 3)("dog", 0, '0', 0)("dog", 1, '1', 1)
            ("easy", 0, '0', 0);
        emplacer[df_d_vals]
          (boost::tree_node::pre_order_traversal,"able",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",0,'0',0)
          (boost::tree_node::pre_order_traversal,"able",1,'1',1)
          (boost::tree_node::post_order_traversal,"able",1,'1',1)
          (boost::tree_node::pre_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",2,'2',3)
          (boost::tree_node::pre_order_traversal,"able",3,'3',8)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",3,'3',8)
          (boost::tree_node::pre_order_traversal,"able",4,'4',21)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",3,'3',8)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"able",2,'2',3)
                (boost::tree_node::pre_order_traversal,"able",0,'0',0)
                (boost::tree_node::post_order_traversal,"able",0,'0',0)
                (boost::tree_node::pre_order_traversal,"able",1,'1',1)
                (boost::tree_node::post_order_traversal,"able",1,'1',1)
                (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
                (boost::tree_node::post_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
              (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
              (boost::tree_node::post_order_traversal,"baker",1,'1',1)
              (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
              (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",3,'3',8)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",2,'2',3)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::pre_order_traversal,"chuck",1,'1',1)
            (boost::tree_node::post_order_traversal,"chuck",1,'1',1)
            (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
            (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"able",4,'4',21)
          (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
          (boost::tree_node::post_order_traversal,"baker",1,'1',1)
          (boost::tree_node::pre_order_traversal,"baker",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",2,'2',3)
          (boost::tree_node::pre_order_traversal,"baker",3,'3',8)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"able",2,'2',3)
              (boost::tree_node::pre_order_traversal,"able",0,'0',0)
              (boost::tree_node::post_order_traversal,"able",0,'0',0)
              (boost::tree_node::pre_order_traversal,"able",1,'1',1)
              (boost::tree_node::post_order_traversal,"able",1,'1',1)
              (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
              (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",2,'2',3)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
            (boost::tree_node::pre_order_traversal,"baker",1,'1',1)
            (boost::tree_node::post_order_traversal,"baker",1,'1',1)
            (boost::tree_node::pre_order_traversal,"chuck",0,'0',0)
            (boost::tree_node::post_order_traversal,"chuck",0,'0',0)
          (boost::tree_node::post_order_traversal,"baker",3,'3',8)
          (boost::tree_node::pre_order_traversal,"chuck",7,'0',7)
          (boost::tree_node::post_order_traversal,"chuck",7,'0',7)
          (boost::tree_node::pre_order_traversal,"chuck",1,'1',1)
          (boost::tree_node::post_order_traversal,"chuck",1,'1',1)
          (boost::tree_node::pre_order_traversal,"chuck",2,'2',3)
            (boost::tree_node::pre_order_traversal,"able",0,'0',0)
            (boost::tree_node::post_order_traversal,"able",0,'0',0)
            (boost::tree_node::pre_order_traversal,"able",1,'1',1)
            (boost::tree_node::post_order_traversal,"able",1,'1',1)
            (boost::tree_node::pre_order_traversal,"baker",0,'0',0)
            (boost::tree_node::post_order_traversal,"baker",0,'0',0)
          (boost::tree_node::post_order_traversal,"chuck",2,'2',3)
          (boost::tree_node::pre_order_traversal,"dog",0,'0',0)
          (boost::tree_node::post_order_traversal,"dog",0,'0',0)
          (boost::tree_node::pre_order_traversal,"dog",1,'1',1)
          (boost::tree_node::post_order_traversal,"dog",1,'1',1)
          (boost::tree_node::pre_order_traversal,"easy",0,'0',0)
          (boost::tree_node::post_order_traversal,"easy",0,'0',0);
        emplacer[df_vals]
          (boost::tree_node::pre_order_traversal,5,'5',62)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,3,'3',8)
            (boost::tree_node::pre_order_traversal,4,'4',21)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,3,'3',8)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,2,'2',3)
                  (boost::tree_node::pre_order_traversal,0,'0',0)
                  (boost::tree_node::post_order_traversal,0,'0',0)
                  (boost::tree_node::pre_order_traversal,1,'1',1)
                  (boost::tree_node::post_order_traversal,1,'1',1)
                  (boost::tree_node::pre_order_traversal,0,'0',0)
                  (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,4,'4',21)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,3,'3',8)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,2,'2',3)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
                (boost::tree_node::pre_order_traversal,1,'1',1)
                (boost::tree_node::post_order_traversal,1,'1',1)
                (boost::tree_node::pre_order_traversal,0,'0',0)
                (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,3,'3',8)
            (boost::tree_node::pre_order_traversal,7,'0',7)
            (boost::tree_node::post_order_traversal,7,'0',7)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,2,'2',3)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
              (boost::tree_node::pre_order_traversal,1,'1',1)
              (boost::tree_node::post_order_traversal,1,'1',1)
              (boost::tree_node::pre_order_traversal,0,'0',0)
              (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,2,'2',3)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
            (boost::tree_node::pre_order_traversal,1,'1',1)
            (boost::tree_node::post_order_traversal,1,'1',1)
            (boost::tree_node::pre_order_traversal,0,'0',0)
            (boost::tree_node::post_order_traversal,0,'0',0)
          (boost::tree_node::post_order_traversal,5,'5',62);
        test_associative_node<f_node_case>(
            f_root
          , bf_vals
          , bf_d_vals
          , pre_vals
          , pre_d_vals
          , post_vals
          , post_d_vals
          , df_vals
          , df_d_vals
        );
    }
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION_WITH_TYPEOF
}

#if defined BOOST_MSVC
   #pragma warning (pop)
#endif

#if defined BOOST_TYPEOF_EMULATION
#include <boost/typeof/boost/container_gen/selectors.hpp>
#include <boost/typeof/boost/container_gen/c_str_cmp_selectors.hpp>
#include <boost/typeof/boost/ptr_container/ptr_map.hpp>
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/container/map.hpp>
#include <boost/typeof/boost/container/flat_map.hpp>
#endif
#else  // !defined BOOST_TYPEOF_EMULATION
#include <boost/container_gen/selectors.hpp>
#include <boost/container_gen/c_str_cmp_selectors.hpp>
#endif  // BOOST_TYPEOF_EMULATION

int test_main(int argc, char** argv)
{
    test_unique_associative<
        boost::ptr_map_selector<boost::c_str_ordering_selector>
    >();
    test_multiple_associative<
        boost::ptr_multimap_selector<boost::c_str_ordering_selector>
    >();
#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    test_unique_associative<
        boost::map_selector<boost::mpl::true_,boost::c_str_ordering_selector>
    >();
    test_multiple_associative<
        boost::multimap_selector<
            boost::mpl::true_
          , boost::c_str_ordering_selector
        >
    >();
    test_unique_associative<
        boost::flat_map_selector<boost::c_str_ordering_selector>
    >();
    test_multiple_associative<
        boost::flat_multimap_selector<boost::c_str_ordering_selector>
    >();
#endif

    return 0;
}

