// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/pre_order_iterator.hpp>
#include <boost/tree_node/pre_order_desc_iterator.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/post_order_desc_iterator.hpp>
#include <boost/tree_node/in_order_iterator.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include "../example/type_definitions.hpp"
#include <boost/test/minimal.hpp>

template <typename Node>
void test_children(Node const& node)
{
    typename Node::const_iterator iend = node.end();

    for (typename Node::const_iterator itr = node.begin(); itr != iend; ++itr)
    {
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(
                itr
            ).get_parent_ptr() == &node
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr)
              , boost::tree_node::position_key()
            ) == itr
        );
    }
}

template <typename TreeItr, typename Itr>
bool test_iterators(TreeItr tree_itr, Itr itr, Itr itr_end)
{
    while (tree_itr)
    {
        if (itr == itr_end)
        {
            return false;
        }

        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::data_key()
            ) == boost::get<0>(*itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::height_key()
            ) == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::count_key()
            ) == boost::get<2>(*itr)
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<3>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<4>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<5>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<6>(*itr)
        );
#endif
        test_children(boost::tree_node::dereference_iterator(tree_itr));
        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
    return true;
}

template <typename DFItr, typename TupleItr>
bool test_df_iterator(DFItr df_itr, TupleItr t_itr, TupleItr t_end)
{
    while (df_itr)
    {
        if (t_itr == t_end)
        {
            return false;
        }

        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::data_key()
            ) == boost::get<1>(*t_itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::height_key()
            ) == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::count_key()
            ) == boost::get<3>(*t_itr)
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<4>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<5>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<6>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<7>(*t_itr)
        );
#endif
        test_children(boost::tree_node::dereference_iterator(df_itr));
        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
    return true;
}

template <
    typename Node
  , typename Values
  , typename DFValues
>
void
    test_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , DFValues const& df_vals
    )
{
    boost::tree_node::breadth_first_iterator<Node const> bf_itr(node);
    boost::tree_node::breadth_first_descendant_iterator<Node const> bf_d_itr(
        node
    );
    boost::tree_node::pre_order_iterator<Node const> pre_itr(node);
    boost::tree_node::pre_order_descendant_iterator<Node const> pre_d_itr(
        node
    );
    boost::tree_node::post_order_iterator<Node const> post_itr(node);
    boost::tree_node::post_order_descendant_iterator<Node const> post_d_itr(
        node
    );
    boost::tree_node::depth_first_iterator<Node const> df_itr(node);
    boost::tree_node::depth_first_descendant_iterator<Node const> df_d_itr(
        node
    );
    Values p_d_vals(post_vals);
    DFValues df_d_vals(df_vals);

    BOOST_CHECK(test_iterators(bf_itr, bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(test_iterators(bf_d_itr, ++bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(test_iterators(pre_itr, pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(test_iterators(pre_d_itr, ++pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(test_iterators(post_itr, post_vals.begin(), post_vals.end()));
    p_d_vals.pop_back();
    BOOST_CHECK(test_iterators(post_d_itr, p_d_vals.begin(), p_d_vals.end()));
    BOOST_CHECK(test_df_iterator(df_itr, df_vals.begin(), df_vals.end()));
    df_d_vals.pop_front();
    df_d_vals.pop_back();
    BOOST_CHECK(
        test_df_iterator(df_d_itr, df_d_vals.begin(), df_d_vals.end())
    );
}

template <
    typename Node
  , typename Values
  , typename DFValues
>
void
    test_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , Values const& in_vals
      , DFValues const& df_vals
    )
{
    boost::tree_node::in_order_iterator<Node const> in_itr(node);

    test_node(node, bf_vals, pre_vals, post_vals, df_vals);
    BOOST_CHECK(test_iterators(in_itr, in_vals.begin(), in_vals.end()));
}

template <typename TreeItr, typename Itr>
bool test_associative_iterators(TreeItr tree_itr, Itr itr, Itr itr_end)
{
    while (tree_itr)
    {
        if (itr == itr_end)
        {
            return false;
        }

        BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::data_key()
            ) == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::height_key()
            ) == boost::get<2>(*itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(tree_itr)
              , boost::tree_node::count_key()
            ) == boost::get<3>(*itr)
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<4>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<5>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<6>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<7>(*itr)
        );
#endif
        test_children(boost::tree_node::dereference_iterator(tree_itr));
        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
    return true;
}

template <typename DFItr, typename TupleItr>
bool test_df_assoc_iterator(DFItr df_itr, TupleItr t_itr, TupleItr t_end)
{
    while (df_itr)
    {
        if (t_itr == t_end)
        {
            return false;
        }

        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(df_itr->first == boost::get<1>(*t_itr));
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::data_key()
            ) == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::height_key()
            ) == boost::get<3>(*t_itr)
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(df_itr)
              , boost::tree_node::count_key()
            ) == boost::get<4>(*t_itr)
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<5>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<6>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<7>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<8>(*t_itr)
        );
#endif
        test_children(boost::tree_node::dereference_iterator(df_itr));
        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
    return true;
}

template <
    typename Node
  , typename Values
  , typename KeyValues
  , typename DFValues
  , typename DFKeyValues
>
void
    test_associative_node(
        Node const& node
      , Values const& bf_vals
      , KeyValues const& bf_kvs
      , Values const& pre_vals
      , KeyValues const& pre_kvs
      , Values const& post_vals
      , KeyValues const& post_kvs
      , DFValues const& df_vals
      , DFKeyValues const& df_kvs
    )
{
    boost::tree_node::breadth_first_iterator<Node const> bf_itr(node);
    boost::tree_node::breadth_first_descendant_iterator<Node const> bf_d_itr(
        node
    );
    boost::tree_node::pre_order_iterator<Node const> pre_itr(node);
    boost::tree_node::pre_order_descendant_iterator<Node const> pre_d_itr(
        node
    );
    boost::tree_node::post_order_iterator<Node const> post_itr(node);
    boost::tree_node::post_order_descendant_iterator<Node const> post_d_itr(
        node
    );
    boost::tree_node::depth_first_iterator<Node const> df_itr(node);
    boost::tree_node::depth_first_descendant_iterator<Node const> df_d_itr(
        node
    );

    BOOST_CHECK(test_iterators(bf_itr, bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(
        test_associative_iterators(bf_d_itr, bf_kvs.begin(), bf_kvs.end())
    );
    BOOST_CHECK(test_iterators(pre_itr, pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(
        test_associative_iterators(pre_d_itr, pre_kvs.begin(), pre_kvs.end())
    );
    BOOST_CHECK(test_iterators(post_itr, post_vals.begin(), post_vals.end()));
    BOOST_CHECK(
        test_associative_iterators(
            post_d_itr
          , post_kvs.begin()
          , post_kvs.end()
        )
    );
    BOOST_CHECK(test_df_iterator(df_itr, df_vals.begin(), df_vals.end()));
    BOOST_CHECK(
        test_df_assoc_iterator(df_d_itr, df_kvs.begin(), df_kvs.end())
    );
}

template <typename Itr1, typename Itr2>
bool test_node_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        if (
            boost::tree_node::traversal_state(
                itr2
            ) == boost::tree_node::no_traversal
        )
        {
            return false;
        }

        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::data_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::data_key()
            )
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::height_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::height_key()
            )
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::count_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::count_key()
            )
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
#endif
        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(
            itr2
        ) == boost::tree_node::no_traversal
    );
    return true;
}

template <typename Itr1, typename Itr2>
bool test_associative_node_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        if (
            boost::tree_node::traversal_state(
                itr2
            ) == boost::tree_node::no_traversal
        )
        {
            return false;
        }

        BOOST_CHECK(itr1->first == itr2->first);
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::data_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::data_key()
            )
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::height_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::height_key()
            )
        );
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr1)
              , boost::tree_node::count_key()
            ) == get(
                boost::tree_node::dereference_iterator(itr2)
              , boost::tree_node::count_key()
            )
        );
#if !defined BOOST_NO_SFINAE
        BOOST_CHECK(
            boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<boost::tree_node::accumulation_key<> >(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuHeightKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuCountKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(itr1)
            ) == boost::tree_node::get<AccuAccuKey>(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
#endif
        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(
            itr2
        ) == boost::tree_node::no_traversal
    );
    return true;
}

template <typename TreeItr, typename Itr>
bool test_f_iters(TreeItr tree_itr, Itr itr, Itr itr_end)
{
    while (tree_itr)
    {
        if (itr == itr_end)
        {
            return false;
        }

        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_uint>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<0>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_char>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuYourUintKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<2>(*itr)
        );
        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
    return true;
}

template <typename DFItr, typename TupleItr>
bool test_f_df_iter(DFItr df_itr, TupleItr t_itr, TupleItr t_end)
{
    while (df_itr)
    {
        if (t_itr == t_end)
        {
            return false;
        }

        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_uint>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<1>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_char>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuYourUintKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<3>(*t_itr)
        );
        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
    return true;
}

template <
    typename Node
  , typename Values
  , typename DFValues
>
void
    test_f_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , DFValues const& df_vals
    )
{
    boost::tree_node::breadth_first_iterator<Node const> bf_itr(node);
    boost::tree_node::breadth_first_descendant_iterator<Node const> bf_d_itr(
        node
    );
    boost::tree_node::pre_order_iterator<Node const> pre_itr(node);
    boost::tree_node::pre_order_descendant_iterator<Node const> pre_d_itr(
        node
    );
    boost::tree_node::post_order_iterator<Node const> post_itr(node);
    boost::tree_node::post_order_descendant_iterator<Node const> post_d_itr(
        node
    );
    boost::tree_node::depth_first_iterator<Node const> df_itr(node);
    boost::tree_node::depth_first_descendant_iterator<Node const> df_d_itr(
        node
    );
    Values p_d_vals(post_vals);
    DFValues df_d_vals(df_vals);

    BOOST_CHECK(test_f_iters(bf_itr, bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(test_f_iters(bf_d_itr, ++bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(test_f_iters(pre_itr, pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(test_f_iters(pre_d_itr, ++pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(test_f_iters(post_itr, post_vals.begin(), post_vals.end()));
    p_d_vals.pop_back();
    BOOST_CHECK(test_f_iters(post_d_itr, p_d_vals.begin(), p_d_vals.end()));
    BOOST_CHECK(test_f_df_iter(df_itr, df_vals.begin(), df_vals.end()));
    df_d_vals.pop_front();
    df_d_vals.pop_back();
    BOOST_CHECK(test_f_df_iter(df_d_itr, df_d_vals.begin(), df_d_vals.end()));
}

template <
    typename Node
  , typename Values
  , typename DFValues
>
void
    test_f_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , Values const& in_vals
      , DFValues const& df_vals
    )
{
    boost::tree_node::in_order_iterator<Node const> in_itr(node);

    test_f_node(node, bf_vals, pre_vals, post_vals, df_vals);
    BOOST_CHECK(test_f_iters(in_itr, in_vals.begin(), in_vals.end()));
}

template <typename TreeItr, typename Itr>
bool test_f_associative_iters(TreeItr tree_itr, Itr itr, Itr itr_end)
{
    while (tree_itr)
    {
        if (itr == itr_end)
        {
            return false;
        }

        BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_uint>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_char>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<2>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuYourUintKey>(
                boost::tree_node::dereference_iterator(tree_itr)
            ) == boost::get<3>(*itr)
        );
        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
    return true;
}

template <typename DFItr, typename TupleItr>
bool test_f_df_assoc_iter(DFItr df_itr, TupleItr t_itr, TupleItr t_end)
{
    while (df_itr)
    {
        if (t_itr == t_end)
        {
            return false;
        }

        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(df_itr->first == boost::get<1>(*t_itr));
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_uint>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<example_keys::your_char>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<3>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::get<AccuYourUintKey>(
                boost::tree_node::dereference_iterator(df_itr)
            ) == boost::get<4>(*t_itr)
        );
        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
    return true;
}

template <
    typename Node
  , typename Values
  , typename KeyValues
  , typename DFValues
  , typename DFKeyValues
>
void
    test_f_associative_node(
        Node const& node
      , Values const& bf_vals
      , KeyValues const& bf_kvs
      , Values const& pre_vals
      , KeyValues const& pre_kvs
      , Values const& post_vals
      , KeyValues const& post_kvs
      , DFValues const& df_vals
      , DFKeyValues const& df_kvs
    )
{
    boost::tree_node::breadth_first_iterator<Node const> bf_itr(node);
    boost::tree_node::breadth_first_descendant_iterator<Node const> bf_d_itr(
        node
    );
    boost::tree_node::pre_order_iterator<Node const> pre_itr(node);
    boost::tree_node::pre_order_descendant_iterator<Node const> pre_d_itr(
        node
    );
    boost::tree_node::post_order_iterator<Node const> post_itr(node);
    boost::tree_node::post_order_descendant_iterator<Node const> post_d_itr(
        node
    );
    boost::tree_node::depth_first_iterator<Node const> df_itr(node);
    boost::tree_node::depth_first_descendant_iterator<Node const> df_d_itr(
        node
    );

    BOOST_CHECK(test_f_iters(bf_itr, bf_vals.begin(), bf_vals.end()));
    BOOST_CHECK(
        test_f_associative_iters(bf_d_itr, bf_kvs.begin(), bf_kvs.end())
    );
    BOOST_CHECK(test_f_iters(pre_itr, pre_vals.begin(), pre_vals.end()));
    BOOST_CHECK(
        test_f_associative_iters(pre_d_itr, pre_kvs.begin(), pre_kvs.end())
    );
    BOOST_CHECK(test_f_iters(post_itr, post_vals.begin(), post_vals.end()));
    BOOST_CHECK(
        test_f_associative_iters(post_d_itr, post_kvs.begin(), post_kvs.end())
    );
    BOOST_CHECK(test_f_df_iter(df_itr, df_vals.begin(), df_vals.end()));
    BOOST_CHECK(test_f_df_assoc_iter(df_d_itr, df_kvs.begin(), df_kvs.end()));
}

#endif  // LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

