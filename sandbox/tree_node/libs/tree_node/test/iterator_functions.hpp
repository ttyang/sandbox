// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
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
#include <boost/test/minimal.hpp>

template <typename Node>
void test_children(Node const& node)
{
    typename Node::const_iterator iend = node.end();

    for (typename Node::const_iterator itr = node.begin(); itr != iend; ++itr)
    {
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr).get_parent_ptr()
         == &node
        );
    }
}

template <typename Node>
void test_children_with_position(Node const& node)
{
    typename Node::const_iterator iend = node.end();

    for (typename Node::const_iterator itr = node.begin(); itr != iend; ++itr)
    {
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr).get_parent_ptr()
         == &node
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr).get_position() == itr
        );
    }
}

template <typename TreeItr, typename Itr>
void test_iterators(TreeItr tree_itr, Itr itr, Itr itr_end, boost::mpl::false_)
{
    while (tree_itr)
    {
        BOOST_CHECK(itr != itr_end);
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_data() == *itr
        );
        test_children(boost::tree_node::dereference_iterator(tree_itr));

        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
}

template <typename TreeItr, typename Itr>
void test_iterators(TreeItr tree_itr, Itr itr, Itr itr_end, boost::mpl::true_)
{
    while (tree_itr)
    {
        BOOST_CHECK(itr != itr_end);
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_data()
         == boost::get<0>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_height()
         == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_count()
         == boost::get<2>(*itr)
        );
        test_children_with_position(
            boost::tree_node::dereference_iterator(tree_itr)
        );

        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
}

template <typename DFItr, typename PairItr>
void
    test_df_iterator(
        DFItr df_itr
      , PairItr p_itr
      , PairItr p_end
      , boost::mpl::false_
    )
{
    while (df_itr)
    {
        BOOST_CHECK(p_itr != p_end);
        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == p_itr->first
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_data()
         == p_itr->second
        );
        test_children(boost::tree_node::dereference_iterator(df_itr));

        ++df_itr;
        ++p_itr;
    }

    BOOST_CHECK(p_itr == p_end);
}

template <typename DFItr, typename TupleItr>
void
    test_df_iterator(
        DFItr df_itr
      , TupleItr t_itr
      , TupleItr t_end
      , boost::mpl::true_
    )
{
    while (df_itr)
    {
        BOOST_CHECK(t_itr != t_end);
        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_data()
         == boost::get<1>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_height()
         == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_count()
         == boost::get<3>(*t_itr)
        );
        test_children_with_position(
            boost::tree_node::dereference_iterator(df_itr)
        );

        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
}

template <
    typename Node
  , typename Values
  , typename DFValues
  , typename BooleanIntegralConstant
>
void
    test_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , DFValues const& df_vals
      , BooleanIntegralConstant has_height
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

    test_iterators(bf_itr, bf_vals.begin(), bf_vals.end(), has_height);
    test_iterators(bf_d_itr, ++bf_vals.begin(), bf_vals.end(), has_height);
    test_iterators(pre_itr, pre_vals.begin(), pre_vals.end(), has_height);
    test_iterators(pre_d_itr, ++pre_vals.begin(), pre_vals.end(), has_height);
    test_iterators(post_itr, post_vals.begin(), post_vals.end(), has_height);
    p_d_vals.pop_back();
    test_iterators(post_d_itr, p_d_vals.begin(), p_d_vals.end(), has_height);
    test_df_iterator(df_itr, df_vals.begin(), df_vals.end(), has_height);
    df_d_vals.pop_front();
    df_d_vals.pop_back();
    test_df_iterator(df_d_itr, df_d_vals.begin(), df_d_vals.end(), has_height);
}

template <
    typename Node
  , typename Values
  , typename DFValues
  , typename BooleanIntegralConstant
>
void
    test_node(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , Values const& in_vals
      , DFValues const& df_vals
      , BooleanIntegralConstant has_height
    )
{
    boost::tree_node::in_order_iterator<Node const> in_itr(node);

    test_node(node, bf_vals, pre_vals, post_vals, df_vals, has_height);
    test_iterators(in_itr, in_vals.begin(), in_vals.end(), has_height);
}

template <typename TreeItr, typename Itr>
void
    test_associative_iterators(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , boost::mpl::false_
    )
{
    while (tree_itr)
    {
        BOOST_CHECK(itr != itr_end);
        BOOST_CHECK(tree_itr->first == itr->first);
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_data()
         == itr->second
        );
        test_children(boost::tree_node::dereference_iterator(tree_itr));

        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
}

template <typename TreeItr, typename Itr>
void
    test_associative_iterators(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , boost::mpl::true_
    )
{
    while (tree_itr)
    {
        BOOST_CHECK(itr != itr_end);
        BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_data()
         == boost::get<1>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_height()
         == boost::get<2>(*itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(tree_itr).get_count()
         == boost::get<3>(*itr)
        );
        test_children_with_position(
            boost::tree_node::dereference_iterator(tree_itr)
        );

        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
}

template <typename DFItr, typename TupleItr>
void
    test_df_assoc_iterator(
        DFItr df_itr
      , TupleItr t_itr
      , TupleItr t_end
      , boost::mpl::false_
    )
{
    while (df_itr)
    {
        BOOST_CHECK(t_itr != t_end);
        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(df_itr->first == boost::get<1>(*t_itr));
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_data()
         == boost::get<2>(*t_itr)
        );
        test_children(boost::tree_node::dereference_iterator(df_itr));

        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
}

template <typename DFItr, typename TupleItr>
void
    test_df_assoc_iterator(
        DFItr df_itr
      , TupleItr t_itr
      , TupleItr t_end
      , boost::mpl::true_
    )
{
    while (df_itr)
    {
        BOOST_CHECK(t_itr != t_end);
        BOOST_CHECK(
            boost::tree_node::traversal_state(df_itr) == boost::get<0>(*t_itr)
        );
        BOOST_CHECK(df_itr->first == boost::get<1>(*t_itr));
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_data()
         == boost::get<2>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_height()
         == boost::get<3>(*t_itr)
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(df_itr).get_count()
         == boost::get<4>(*t_itr)
        );
        test_children_with_position(
            boost::tree_node::dereference_iterator(df_itr)
        );

        ++df_itr;
        ++t_itr;
    }

    BOOST_CHECK(t_itr == t_end);
}

template <
    typename Node
  , typename Values
  , typename KeyValues
  , typename DFValues
  , typename DFKeyValues
  , typename BooleanIntegralConstant
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
      , BooleanIntegralConstant has_height
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

    test_iterators(bf_itr, bf_vals.begin(), bf_vals.end(), has_height);
    test_associative_iterators(
        bf_d_itr
      , bf_kvs.begin()
      , bf_kvs.end()
      , has_height
    );
    test_iterators(pre_itr, pre_vals.begin(), pre_vals.end(), has_height);
    test_associative_iterators(
        pre_d_itr
      , pre_kvs.begin()
      , pre_kvs.end()
      , has_height
    );
    test_iterators(post_itr, post_vals.begin(), post_vals.end(), has_height);
    test_associative_iterators(
        post_d_itr
      , post_kvs.begin()
      , post_kvs.end()
      , has_height
    );
//  test_df_iterator(df_itr, df_vals.begin(), df_vals.end(), has_height);
//  test_df_assoc_iterator(df_d_itr, df_kvs.begin(), df_kvs.end(), has_height);
}

template <typename Itr1, typename Itr2>
void test_node_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        BOOST_CHECK(
            boost::tree_node::traversal_state(itr2)
         != boost::tree_node::no_traversal
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_data()
         == boost::tree_node::dereference_iterator(itr2).get_data()
        );

        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(itr2)
     == boost::tree_node::no_traversal
    );
}

template <typename Itr1, typename Itr2>
void test_node_with_depth_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        BOOST_CHECK(
            boost::tree_node::traversal_state(itr2)
         != boost::tree_node::no_traversal
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_data()
         == boost::tree_node::dereference_iterator(itr2).get_data()
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_height()
         == boost::tree_node::dereference_iterator(itr2).get_height()
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_count()
         == boost::tree_node::dereference_iterator(itr2).get_count()
        );

        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(itr2)
     == boost::tree_node::no_traversal
    );
}

template <typename Itr1, typename Itr2>
void test_associative_node_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        BOOST_CHECK(
            boost::tree_node::traversal_state(itr2)
         != boost::tree_node::no_traversal
        );
        BOOST_CHECK(itr1->first == itr2->first);
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_data()
         == boost::tree_node::dereference_iterator(itr2).get_data()
        );

        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(itr2)
     == boost::tree_node::no_traversal
    );
}

template <typename Itr1, typename Itr2>
void test_assoc_node_with_depth_copies(Itr1 itr1, Itr2 itr2)
{
    while (itr1)
    {
        BOOST_CHECK(
            boost::tree_node::traversal_state(itr2)
         != boost::tree_node::no_traversal
        );
        BOOST_CHECK(itr1->first == itr2->first);
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_data()
         == boost::tree_node::dereference_iterator(itr2).get_data()
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_height()
         == boost::tree_node::dereference_iterator(itr2).get_height()
        );
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(itr1).get_count()
         == boost::tree_node::dereference_iterator(itr2).get_count()
        );

        ++itr1;
        ++itr2;
    }

    BOOST_CHECK(
        boost::tree_node::traversal_state(itr2)
     == boost::tree_node::no_traversal
    );
}

#endif  // LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

