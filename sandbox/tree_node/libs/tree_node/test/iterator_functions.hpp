// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED
#define LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

#include <iterator>
#include <algorithm>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/tree_node/key/data.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/iterator/breadth_first.hpp>
#include <boost/tree_node/iterator/breadth_first_descendant.hpp>
#include <boost/tree_node/iterator/pre_order.hpp>
#include <boost/tree_node/iterator/pre_order_descendant.hpp>
#include <boost/tree_node/iterator/post_order.hpp>
#include <boost/tree_node/iterator/post_order_descendant.hpp>
#include <boost/tree_node/iterator/depth_first.hpp>
#include <boost/tree_node/iterator/depth_first_descendant.hpp>
#include <boost/tree_node/iterator/in_order.hpp>
#include <boost/tree_node/iterator/dereference.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include "../example/type_definitions.hpp"
#include <boost/test/minimal.hpp>

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
#include <boost/mpl/not.hpp>
#include <boost/fusion/container/map/convert.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/view/filter_view.hpp>
#include <boost/tree_node/intrinsic/get_properties.hpp>

struct test_no_position_predicate
{
    template <typename T>
    struct apply
      : boost::mpl::not_<
            std::tr1::is_same<
                typename boost::fusion::result_of::first<T>::type
              , boost::tree_node::position_key
            >
        >
    {
    };
};
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

//[test__node__children
template <typename Node>
void test_children(Node const& node)
{
    typename Node::const_iterator iend = node.end();

    for (typename Node::const_iterator itr = node.begin(); itr != iend; ++itr)
    {
        // dereference_iterator() calls must be fully qualified here.
        BOOST_CHECK(
            boost::tree_node::dereference_iterator(
                itr
            ).get_parent_ptr() == &node
        );
//<-
#if defined BOOST_TYPEOF_NATIVE
//->
        BOOST_CHECK(
            get(
                boost::tree_node::dereference_iterator(itr)
              , boost::tree_node::position_key()
            ) == itr
        );
//<-
#endif
//->
    }
}
//]

//[test__node__case_and_tag_types
enum test_case
{
    a_node_case
  , f_node_case
  , gui_node_case
};

template <test_case c>
struct test_tag
{
};

template <test_case c>
struct test_df_tag
{
};

template <test_case c>
struct test_associative_tag
{
};

template <test_case c>
struct test_df_associative_tag
{
};
//]

template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_tag<a_node_case>)
{
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::data_key()
        ) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::height_key()
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::count_key()
        ) == boost::get<2>(*itr)
    );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    BOOST_CHECK(
        boost::tree_node::get<boost::tree_node::accumulation_key<> >(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuHeightKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuCountKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuAccuKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<6>(*itr)
    );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    test_children(dereference_iterator(tree_itr));
}

template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_df_tag<a_node_case>)
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::data_key()
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::height_key()
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::count_key()
        ) == boost::get<3>(*itr)
    );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    BOOST_CHECK(
        boost::tree_node::get<boost::tree_node::accumulation_key<> >(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuHeightKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuCountKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<6>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuAccuKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<7>(*itr)
    );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    test_children(dereference_iterator(tree_itr));
}

template <typename TreeItr, typename Itr>
void
    test_contents(TreeItr tree_itr, Itr itr, test_associative_tag<a_node_case>)
{
    BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::data_key()
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::height_key()
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::count_key()
        ) == boost::get<3>(*itr)
    );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    BOOST_CHECK(
        boost::tree_node::get<boost::tree_node::accumulation_key<> >(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuHeightKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuCountKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<6>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuAccuKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<7>(*itr)
    );
#endif  // BOOST_NO_SFINAE
    test_children(dereference_iterator(tree_itr));
}

template <typename TreeItr, typename Itr>
void
    test_contents(
        TreeItr tree_itr
      , Itr itr
      , test_df_associative_tag<a_node_case>
    )
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(tree_itr->first == boost::get<1>(*itr));
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::data_key()
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::height_key()
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        get(
            dereference_iterator(tree_itr)
          , boost::tree_node::count_key()
        ) == boost::get<4>(*itr)
    );
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    BOOST_CHECK(
        boost::tree_node::get<boost::tree_node::accumulation_key<> >(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuHeightKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<6>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuCountKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<7>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuAccuKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<8>(*itr)
    );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
    test_children(dereference_iterator(tree_itr));
}

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_tag<f_node_case>)
{
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_uint>(
            dereference_iterator(tree_itr)
        ) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_char>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuYourUintKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
}

template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_df_tag<f_node_case>)
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_uint>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_char>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuYourUintKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
}

template <typename TreeItr, typename Itr>
void
    test_contents(TreeItr tree_itr, Itr itr, test_associative_tag<f_node_case>)
{
    BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_uint>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_char>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuYourUintKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
}

template <typename TreeItr, typename Itr>
void
    test_contents(
        TreeItr tree_itr
      , Itr itr
      , test_df_associative_tag<f_node_case>
    )
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(tree_itr->first == boost::get<1>(*itr));
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_uint>(
            boost::tree_node::dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::your_char>(
            boost::tree_node::dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<AccuYourUintKey>(
            boost::tree_node::dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
}

//[test__node__iterator_contents__gui_case
template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_tag<gui_node_case>)
{
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_location>(
            dereference_iterator(tree_itr)
        ) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_height>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_priority>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<HeightSumKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<MinPriorityKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
}
//]

template <typename TreeItr, typename Itr>
void test_contents(TreeItr tree_itr, Itr itr, test_df_tag<gui_node_case>)
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_location>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_height>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_priority>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<HeightSumKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<MinPriorityKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
}

template <typename TreeItr, typename Itr>
void
    test_contents(
        TreeItr tree_itr
      , Itr itr
      , test_associative_tag<gui_node_case>
    )
{
    BOOST_CHECK(tree_itr->first == boost::get<0>(*itr));
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_location>(
            dereference_iterator(tree_itr)
        ) == boost::get<1>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_height>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_priority>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<HeightSumKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<MinPriorityKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
}

template <typename TreeItr, typename Itr>
void
    test_contents(
        TreeItr tree_itr
      , Itr itr
      , test_df_associative_tag<gui_node_case>
    )
{
    BOOST_CHECK(
        boost::tree_node::traversal_state(tree_itr) == boost::get<0>(*itr)
    );
    BOOST_CHECK(tree_itr->first == boost::get<1>(*itr));
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_location>(
            dereference_iterator(tree_itr)
        ) == boost::get<2>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_height>(
            dereference_iterator(tree_itr)
        ) == boost::get<3>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<example_keys::row_priority>(
            dereference_iterator(tree_itr)
        ) == boost::get<4>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<HeightSumKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<5>(*itr)
    );
    BOOST_CHECK(
        boost::tree_node::get<MinPriorityKey>(
            dereference_iterator(tree_itr)
        ) == boost::get<6>(*itr)
    );
}
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

//[test__node__iterator__is_forward
template <typename TreeItr, typename Itr, typename Tag>
bool
    test_iterator_more(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , Tag tag
      , std::tr1::false_type
    )
{
    while (tree_itr)
    {
        if (itr == itr_end)
        {
            return false;
        }

        test_contents(tree_itr, itr, tag);
        ++tree_itr;
        ++itr;
    }

    BOOST_CHECK(itr == itr_end);
    return true;
}
//]

//[test__node__iterator__is_also_reversible
template <typename TreeItr, typename Itr, typename Tag>
bool
    test_iterator_more(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , Tag tag
      , std::tr1::true_type
    )
{
    Itr copy_itr(itr);

    while (copy_itr != itr_end)
    {
        if (!tree_itr)
        {
            return false;
        }

        test_contents(tree_itr, copy_itr, tag);
        ++tree_itr;
        ++copy_itr;
    }

    while (itr != copy_itr)
    {
        test_contents(--tree_itr, --copy_itr, tag);
    }

    return test_iterator_more(
        tree_itr
      , itr
      , itr_end
      , tag
      , std::tr1::false_type()
    );
}
//]

//[test__node__iterator__is_bidirectional
template <typename TreeItr, typename Itr, typename Tag>
bool
    test_iterator(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , Tag tag
      , std::tr1::false_type
    )
{
    return test_iterator_more(
        tree_itr
      , itr
      , itr_end
      , tag
      , std::tr1::is_base_of<
            std::bidirectional_iterator_tag
          , typename boost::BOOST_ITERATOR_CATEGORY<TreeItr>::type
        >()
    );
}
//]

//[test__node__iterator__is_indexable
template <typename TreeItr, typename Itr, typename Tag>
bool
    test_iterator(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , Tag tag
      , std::tr1::true_type
    )
{
    typename boost::iterator_difference<
        Itr
    >::type n = std::distance(itr, itr_end), d;
    TreeItr tree_end(tree_itr), tree_itr1, tree_itr2;

    tree_end += n;

    for (
        typename boost::iterator_difference<
            Itr
        >::type i = boost::initialized_value;
        i < n;
        ++i
    )
    {
        tree_itr1 = tree_itr;
        tree_itr1 += i;
        tree_itr2 = tree_itr;

        for (d = boost::initialized_value; d < i; ++d)
        {
            ++tree_itr2;
        }

        BOOST_CHECK(tree_itr1 == tree_itr2);
        BOOST_CHECK(tree_itr == tree_itr1 - i);
        BOOST_CHECK(i == tree_itr1 - tree_itr);
        BOOST_CHECK(-i == tree_itr - tree_itr1);
        test_contents(tree_itr1, itr + i, tag);

        for (d = boost::initialized_value; d < n; ++d)
        {
            tree_itr2 = tree_itr;
            tree_itr2 += d;
            BOOST_CHECK(i - d == tree_itr1 - tree_itr2);
            BOOST_CHECK(d - i == tree_itr2 - tree_itr1);
            BOOST_CHECK((i < d) == (tree_itr1 < tree_itr2));
            BOOST_CHECK((d < i) == (tree_itr2 < tree_itr1));

            if (d + i < n)
            {
                BOOST_CHECK(tree_itr1 + d == tree_itr2 + i);
                BOOST_CHECK(tree_itr1 == tree_itr2 + i - d);
                BOOST_CHECK(tree_itr2 == tree_itr1 + d - i);
            }
        }

        if (i)
        {
            tree_itr1 = tree_end;
            tree_itr1 -= i;
            tree_itr2 = tree_end;

            for (d = boost::initialized_value; d < i; ++d)
            {
                --tree_itr2;
            }

            BOOST_CHECK(tree_itr1 == tree_itr2);
            BOOST_CHECK(tree_end == tree_itr1 + i);
            BOOST_CHECK(i == tree_end - tree_itr1);
            BOOST_CHECK(-i == tree_itr1 - tree_end);
            test_contents(tree_itr1, itr_end - i, tag);
        }
    }

    return test_iterator(
        tree_itr
      , itr
      , itr_end
      , tag
      , std::tr1::false_type()
    );
}
//]

//[test__node__iterator__driver
template <typename TreeItr, typename Itr, typename Tag>
bool
    test_iterator(
        TreeItr tree_itr
      , Itr itr
      , Itr itr_end
      , Tag tag
    )
{
    return test_iterator(
        tree_itr
      , itr
      , itr_end
      , tag
        // TODO: Replace with check for indexable iterator type.
      , std::tr1::is_base_of<
            std::random_access_iterator_tag
          , typename boost::BOOST_ITERATOR_CATEGORY<TreeItr>::type
        >()
    );
}
//]

//[test__node__iterators__are_forward
template <
    test_case c
  , typename Node
  , typename Values
  , typename DFValues
>
void
    test_iterators(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , DFValues const& df_vals
      , std::tr1::true_type
    )
{
    BOOST_CHECK(
        test_iterator(
            make_breadth_first_iterator(node)
          , bf_vals.begin()
          , bf_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_breadth_first_descendant_iterator(node)
          , ++bf_vals.begin()
          , bf_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_iterator(node)
          , pre_vals.begin()
          , pre_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_descendant_iterator(node)
          , ++pre_vals.begin()
          , pre_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_iterator(node)
          , post_vals.begin()
          , post_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_descendant_iterator(node)
          , post_vals.begin()
          , post_vals.begin() + post_vals.size() - 1
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_iterator(node)
          , df_vals.begin()
          , df_vals.end()
          , test_df_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_descendant_iterator(node)
          , ++df_vals.begin()
          , df_vals.begin() + df_vals.size() - 1
          , test_df_tag<c>()
        )
    );
}
//]

//[test__node__iterators__are_also_reversible
template <
    test_case c
  , typename Node
  , typename Values
  , typename DFValues
>
void
    test_iterators(
        Node const& node
      , Values const& bf_vals
      , Values const& pre_vals
      , Values const& post_vals
      , DFValues const& df_vals
      , std::tr1::false_type
    )
{
    test_iterators<c>(
        node
      , bf_vals
      , pre_vals
      , post_vals
      , df_vals
      , std::tr1::true_type()
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_reverse_iterator(node)
          , pre_vals.rbegin()
          , pre_vals.rend()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_descendant_reverse_iterator(node)
          , pre_vals.rbegin()
          , pre_vals.rbegin() + pre_vals.size() - 1
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_reverse_iterator(node)
          , post_vals.rbegin()
          , post_vals.rend()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_descendant_reverse_iterator(node)
          , ++post_vals.rbegin()
          , post_vals.rend()
          , test_tag<c>()
        )
    );

    DFValues df_d_v(df_vals);

    for (typename DFValues::size_type i = 0; i < df_d_v.size(); ++i)
    {
        boost::get<0>(df_d_v[i]) = (
            (boost::tree_node::pre_order_traversal == boost::get<0>(df_d_v[i]))
          ? boost::tree_node::post_order_traversal
          : boost::tree_node::pre_order_traversal
        );
    }

    BOOST_CHECK(
        test_iterator(
            make_depth_first_reverse_iterator(node)
          , df_d_v.rbegin()
          , df_d_v.rend()
          , test_df_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_descendant_reverse_iterator(node)
          , ++df_d_v.rbegin()
          , df_d_v.rbegin() + df_d_v.size() - 1
          , test_df_tag<c>()
        )
    );
}
//]

//[test__node__iterators
template <
    test_case c
  , typename Node
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
    test_iterators<c>(
        node
      , bf_vals
      , pre_vals
      , post_vals
      , df_vals
      , std::tr1::is_void<typename Node::reverse_iterator>()
    );
}

template <
    test_case c
  , typename Node
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
    test_node<c>(node, bf_vals, pre_vals, post_vals, df_vals);
    BOOST_CHECK(
        test_iterator(
            make_in_order_iterator(node)
          , in_vals.begin()
          , in_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_in_order_reverse_iterator(node)
          , in_vals.rbegin()
          , in_vals.rend()
          , test_tag<c>()
        )
    );
}
//]

template <
    test_case c
  , typename Node
  , typename Values
  , typename KeyValues
  , typename DFValues
  , typename DFKeyValues
>
void
    test_associative_iterators(
        Node const& node
      , Values const& bf_vals
      , KeyValues const& bf_kvs
      , Values const& pre_vals
      , KeyValues const& pre_kvs
      , Values const& post_vals
      , KeyValues const& post_kvs
      , DFValues const& df_vals
      , DFKeyValues const& df_kvs
      , std::tr1::true_type
    )
{
    BOOST_CHECK(
        test_iterator(
            make_breadth_first_iterator(node)
          , bf_vals.begin()
          , bf_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_breadth_first_descendant_iterator(node)
          , bf_kvs.begin()
          , bf_kvs.end()
          , test_associative_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_iterator(node)
          , pre_vals.begin()
          , pre_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_descendant_iterator(node)
          , pre_kvs.begin()
          , pre_kvs.end()
          , test_associative_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_iterator(node)
          , post_vals.begin()
          , post_vals.end()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_descendant_iterator(node)
          , post_kvs.begin()
          , post_kvs.end()
          , test_associative_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_iterator(node)
          , df_vals.begin()
          , df_vals.end()
          , test_df_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_descendant_iterator(node)
          , df_kvs.begin()
          , df_kvs.end()
          , test_df_associative_tag<c>()
        )
    );
}

template <
    test_case c
  , typename Node
  , typename Values
  , typename KeyValues
  , typename DFValues
  , typename DFKeyValues
>
void
    test_associative_iterators(
        Node const& node
      , Values const& bf_vals
      , KeyValues const& bf_kvs
      , Values const& pre_vals
      , KeyValues const& pre_kvs
      , Values const& post_vals
      , KeyValues const& post_kvs
      , DFValues const& df_vals
      , DFKeyValues const& df_kvs
      , std::tr1::false_type
    )
{
    test_associative_iterators<c>(
        node
      , bf_vals
      , bf_kvs
      , pre_vals
      , pre_kvs
      , post_vals
      , post_kvs
      , df_vals
      , df_kvs
      , std::tr1::true_type()
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_reverse_iterator(node)
          , pre_vals.rbegin()
          , pre_vals.rend()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_pre_order_descendant_reverse_iterator(node)
          , pre_kvs.rbegin()
          , pre_kvs.rend()
          , test_associative_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_reverse_iterator(node)
          , post_vals.rbegin()
          , post_vals.rend()
          , test_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_post_order_descendant_reverse_iterator(node)
          , post_kvs.rbegin()
          , post_kvs.rend()
          , test_associative_tag<c>()
        )
    );

    DFValues df_d_v(df_vals);
    DFKeyValues df_d_kvs(df_kvs);

    for (typename DFValues::size_type i = 0; i < df_d_v.size(); ++i)
    {
        boost::get<0>(df_d_v[i]) = (
            (boost::tree_node::pre_order_traversal == boost::get<0>(df_d_v[i]))
          ? boost::tree_node::post_order_traversal
          : boost::tree_node::pre_order_traversal
        );
    }

    for (typename DFKeyValues::size_type i = 0; i < df_d_kvs.size(); ++i)
    {
        boost::get<0>(df_d_kvs[i]) = (
            (
                boost::tree_node::pre_order_traversal == boost::get<0>(
                    df_d_kvs[i]
                )
            )
          ? boost::tree_node::post_order_traversal
          : boost::tree_node::pre_order_traversal
        );
    }

    BOOST_CHECK(
        test_iterator(
            make_depth_first_reverse_iterator(node)
          , df_d_v.rbegin()
          , df_d_v.rend()
          , test_df_tag<c>()
        )
    );
    BOOST_CHECK(
        test_iterator(
            make_depth_first_descendant_reverse_iterator(node)
          , df_d_kvs.rbegin()
          , df_d_kvs.rend()
          , test_df_associative_tag<c>()
        )
    );
}

template <
    test_case c
  , typename Node
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
    test_associative_iterators<c>(
        node
      , bf_vals
      , bf_kvs
      , pre_vals
      , pre_kvs
      , post_vals
      , post_kvs
      , df_vals
      , df_kvs
      , std::tr1::is_void<typename Node::reverse_iterator>()
    );
}

template <typename Itr1, typename Itr2>
bool test_node_copies(Itr1 itr1, Itr2 itr2)
{
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef typename boost::tree_node::result_of::get_properties<
                typename ::std::tr1::remove_reference<
                    typename boost::tree_node::result_of::dereference_iterator<
                        Itr1
                    >::type
                >::type
            >::type
            KVPairs1;
    typedef typename boost::tree_node::result_of::get_properties<
                typename ::std::tr1::remove_reference<
                    typename boost::tree_node::result_of::dereference_iterator<
                        Itr2
                    >::type
                >::type
            >::type
            KVPairs2;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

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

#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        KVPairs1 p1(
            boost::tree_node::get_properties(
                boost::tree_node::dereference_iterator(itr1)
            )
        );
        boost::fusion::filter_view<KVPairs1,test_no_position_predicate> view1(
            p1
        );
        KVPairs2 p2(
            boost::tree_node::get_properties(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        boost::fusion::filter_view<KVPairs2,test_no_position_predicate> view2(
            p2
        );

        BOOST_CHECK(
            boost::fusion::equal_to(
                boost::fusion::as_map(view1)
              , boost::fusion::as_map(view2)
            )
        );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
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
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
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
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
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
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
    typedef typename boost::tree_node::result_of::get_properties<
                typename ::std::tr1::remove_reference<
                    typename boost::tree_node::result_of::dereference_iterator<
                        Itr1
                    >::type
                >::type
            >::type
            KVPairs1;
    typedef typename boost::tree_node::result_of::get_properties<
                typename ::std::tr1::remove_reference<
                    typename boost::tree_node::result_of::dereference_iterator<
                        Itr2
                    >::type
                >::type
            >::type
            KVPairs2;
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION

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
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
        KVPairs1 p1(
            boost::tree_node::get_properties(
                boost::tree_node::dereference_iterator(itr1)
            )
        );
        boost::fusion::filter_view<KVPairs1,test_no_position_predicate> view1(
            p1
        );
        KVPairs2 p2(
            boost::tree_node::get_properties(
                boost::tree_node::dereference_iterator(itr2)
            )
        );
        boost::fusion::filter_view<KVPairs2,test_no_position_predicate> view2(
            p2
        );

        BOOST_CHECK(
            boost::fusion::equal_to(
                boost::fusion::as_map(view1)
              , boost::fusion::as_map(view2)
            )
        );
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
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
#if defined BOOST_TREE_NODE_CAN_USE_FUSION
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
#endif  // BOOST_TREE_NODE_CAN_USE_FUSION
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

#endif  // LIBS_TREE_NODE_TEST_ITERATOR_FUNCTIONS_HPP_INCLUDED

