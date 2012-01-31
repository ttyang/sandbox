// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_EQUAL_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_EQUAL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/operator/comparison.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/detail/metafunction/has_first_type.hpp>
#include <boost/detail/metafunction/has_second_type.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
      , typename IsStrict
    >
    bool
        equal_impl(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
          , IsStrict
        )
    {
        while (itr1)
        {
            if (
                itr2
             && (!IsStrict::value || (itr1 == itr2))
             && key_comp(itr1->first, itr2->first)
             && value_comp(itr1->second.get_data(), itr2->second.get_data())
            )
            {
                ++itr1;
                ++itr2;
            }
            else
            {
                return false;
            }
        }

        return !itr2;
    }

    template <
        typename Iterator1
      , typename Iterator2
      , typename BinaryPredicate
      , typename IsStrict
    >
    bool
        equal_impl(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
          , IsStrict
        )
    {
        while (itr1)
        {
            if (
                itr2
             && (!IsStrict::value || (itr1 == itr2))
             && comp(itr1->get_data(), itr2->get_data())
            )
            {
                ++itr1;
                ++itr2;
            }
            else
            {
                return false;
            }
        }

        return !itr2;
    }

    template <typename Iterator1, typename Iterator2, typename IsStrict>
    inline bool
        equal_dispatch(
            Iterator1 itr1
          , Iterator2 itr2
          , IsStrict is_strict
          , ::boost::mpl::true_
          , ::boost::mpl::true_
        )
    {
        return equal_impl(
            itr1
          , itr2
          , (
                ::boost::phoenix::arg_names::arg1
             == ::boost::phoenix::arg_names::arg2
            )
          , (
                ::boost::phoenix::arg_names::arg1
             == ::boost::phoenix::arg_names::arg2
            )
          , is_strict
        );
    }

    template <typename Iterator1, typename Iterator2, typename IsStrict>
    inline bool
        equal_dispatch(
            Iterator1 itr1
          , Iterator2 itr2
          , IsStrict is_strict
          , ::boost::mpl::false_
          , ::boost::mpl::false_
        )
    {
        return equal_impl(
            itr1
          , itr2
          , (
                ::boost::phoenix::arg_names::arg1
             == ::boost::phoenix::arg_names::arg2
            )
          , is_strict
        );
    }
}}}  // namespace boost::tree_node::_detail

//[reference__equal__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    bool
        equal(
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
        equal(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::_detail::equal_impl(
            itr1
          , itr2
          , key_comp
          , value_comp
          , ::boost::mpl::false_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strictly_equal__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    bool
        strictly_equal(
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
        strictly_equal(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::_detail::equal_impl(
            itr1
          , itr2
          , key_comp
          , value_comp
          , ::boost::mpl::true_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__equal__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    bool equal(Iterator1 itr1, Iterator2 itr2, BinaryPredicate comp);

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline bool equal(Iterator1 itr1, Iterator2 itr2, BinaryPredicate comp)
    {
        return ::boost::tree_node::_detail::equal_impl(
            itr1
          , itr2
          , comp
          , ::boost::mpl::false_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strictly_equal__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    bool strictly_equal(Iterator1 itr1, Iterator2 itr2, BinaryPredicate comp);

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline bool
        strictly_equal(Iterator1 itr1, Iterator2 itr2, BinaryPredicate comp)
    {
        return ::boost::tree_node::_detail::equal_impl(
            itr1
          , itr2
          , comp
          , ::boost::mpl::true_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__equal
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    bool equal(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline bool equal(Iterator1 itr1, Iterator2 itr2)
    {
        typedef typename ::boost::iterator_value<Iterator1>::type _value_type1;
        typedef typename ::boost::iterator_value<Iterator2>::type _value_type2;

        return ::boost::tree_node::_detail::equal_dispatch(
            itr1
          , itr2
          , ::boost::mpl::false_()
          , typename ::boost::mpl::and_<
                typename ::boost::detail::has_first_type<_value_type1>::type
              , typename ::boost::detail::has_second_type<_value_type1>::type
            >::type()
          , typename ::boost::mpl::and_<
                typename ::boost::detail::has_first_type<_value_type2>::type
              , typename ::boost::detail::has_second_type<_value_type2>::type
            >::type()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strictly_equal
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    bool strictly_equal(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline bool strictly_equal(Iterator1 itr1, Iterator2 itr2)
    {
        typedef typename ::boost::iterator_value<Iterator1>::type _value_type1;
        typedef typename ::boost::iterator_value<Iterator2>::type _value_type2;

        return ::boost::tree_node::_detail::equal_dispatch(
            itr1
          , itr2
          , ::boost::mpl::true_()
          , typename ::boost::mpl::and_<
                typename ::boost::detail::has_first_type<_value_type1>::type
              , typename ::boost::detail::has_second_type<_value_type1>::type
            >::type()
          , typename ::boost::mpl::and_<
                typename ::boost::detail::has_first_type<_value_type2>::type
              , typename ::boost::detail::has_second_type<_value_type2>::type
            >::type()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_EQUAL_HPP_INCLUDED

