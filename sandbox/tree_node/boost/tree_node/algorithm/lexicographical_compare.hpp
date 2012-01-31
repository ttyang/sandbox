// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED

#include <boost/tree_node/algorithm/lexicographical_comp_3way.hpp>

//[reference__lexicographical_compare__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    bool
        lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        );

    //<-
    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    inline bool
        lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::lexicographical_compare_3way(
            itr1
          , itr2
          , key_comp
          , value_comp
        ) < 0;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strict_lexicographical_compare__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    bool
        strict_lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        );

    //<-
    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    inline bool
        strict_lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::strict_lexicographical_compare_3way(
            itr1
          , itr2
          , key_comp
          , value_comp
        ) < 0;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__lexicographical_compare__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    bool
        lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        );

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline bool
        lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        )
    {
        return ::boost::tree_node::lexicographical_compare_3way(
            itr1
          , itr2
          , comp
        ) < 0;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strict_lexicographical_compare__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    bool
        strict_lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        );

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline bool
        strict_lexicographical_compare(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        )
    {
        return ::boost::tree_node::strict_lexicographical_compare_3way(
            itr1
          , itr2
          , comp
        ) < 0;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__lexicographical_compare
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    bool lexicographical_compare(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline bool lexicographical_compare(Iterator1 itr1, Iterator2 itr2)
    {
        return (
            ::boost::tree_node::lexicographical_compare_3way(itr1, itr2) < 0
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strict_lexicographical_compare
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    bool strict_lexicographical_compare(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline bool strict_lexicographical_compare(Iterator1 itr1, Iterator2 itr2)
    {
        return (
            ::boost::tree_node::strict_lexicographical_compare_3way(itr1, itr2)
          < 0
        );
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED

