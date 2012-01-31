// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMP_3WAY_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMP_3WAY_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/operator/comparison.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/tree_node/traversal_state.hpp>
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
    int
        lexicographical_compare_impl(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
          , IsStrict
        )
    {
        while (itr2)
        {
            if (itr1)
            {
                if (IsStrict::value)
                {
                    if (
                        ::boost::tree_node::traversal_state(itr1)
                      < ::boost::tree_node::traversal_state(itr2)
                    )
                    {
                        return -1;
                    }

                    if (
                        ::boost::tree_node::traversal_state(itr2)
                      < ::boost::tree_node::traversal_state(itr1)
                    )
                    {
                        return 1;
                    }
                }

                if (key_comp(itr1->first, itr2->first))
                {
                    return -1;
                }

                if (key_comp(itr2->first, itr1->first))
                {
                    return 1;
                }

                if (
                    value_comp(
                        itr1->second.get_data()
                      , itr2->second.get_data()
                    )
                )
                {
                    return -1;
                }

                if (
                    value_comp(
                        itr2->second.get_data()
                      , itr1->second.get_data()
                    )
                )
                {
                    return 1;
                }

                ++itr1;
                ++itr2;
            }
            else
            {
                return -1;
            }
        }

        return itr1 ? 1 : 0;
    }

    template <
        typename Iterator1
      , typename Iterator2
      , typename BinaryPredicate
      , typename IsStrict
    >
    int
        lexicographical_compare_impl(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
          , IsStrict
        )
    {
        while (itr2)
        {
            if (itr1)
            {
                if (IsStrict::value)
                {
                    if (
                        ::boost::tree_node::traversal_state(itr1)
                      < ::boost::tree_node::traversal_state(itr2)
                    )
                    {
                        return -1;
                    }

                    if (
                        ::boost::tree_node::traversal_state(itr2)
                      < ::boost::tree_node::traversal_state(itr1)
                    )
                    {
                        return 1;
                    }
                }

                if (comp(itr1->get_data(), itr2->get_data()))
                {
                    return -1;
                }

                if (comp(itr2->get_data(), itr1->get_data()))
                {
                    return 1;
                }

                ++itr1;
                ++itr2;
            }
            else
            {
                return -1;
            }
        }

        return itr1 ? 1 : 0;
    }

    template <typename Iterator1, typename Iterator2, typename IsStrict>
    inline int
        lexicographical_compare_dispatch(
            Iterator1 itr1
          , Iterator2 itr2
          , IsStrict is_strict
          , ::boost::mpl::true_
          , ::boost::mpl::true_
        )
    {
        return lexicographical_compare_impl(
            itr1
          , itr2
          , (
                ::boost::phoenix::arg_names::arg1
              < ::boost::phoenix::arg_names::arg2
            )
          , (
                ::boost::phoenix::arg_names::arg1
              < ::boost::phoenix::arg_names::arg2
            )
          , is_strict
        );
    }

    template <typename Iterator1, typename Iterator2, typename IsStrict>
    inline int
        lexicographical_compare_dispatch(
            Iterator1 itr1
          , Iterator2 itr2
          , IsStrict is_strict
          , ::boost::mpl::false_
          , ::boost::mpl::false_
        )
    {
        return lexicographical_compare_impl(
            itr1
          , itr2
          , (
                ::boost::phoenix::arg_names::arg1
              < ::boost::phoenix::arg_names::arg2
            )
          , is_strict
        );
    }
}}}  // namespace boost::tree_node::_detail

//[reference__lexicographical_compare_3way__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    int
        lexicographical_compare_3way(
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
    inline int
        lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::_detail::lexicographical_compare_impl(
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

//[reference__strict_lexicographical_compare_3way__with_comparators
namespace boost { namespace tree_node {

    template <
        typename Iterator1
      , typename Iterator2
      , typename KeyCompare
      , typename ValueCompare
    >
    int
        strict_lexicographical_compare_3way(
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
    inline int
        strict_lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        return ::boost::tree_node::_detail::lexicographical_compare_impl(
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

//[reference__lexicographical_compare_3way__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    int
        lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        );

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline int
        lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        )
    {
        return ::boost::tree_node::_detail::lexicographical_compare_impl(
            itr1
          , itr2
          , comp
          , ::boost::mpl::false_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__strict_lexicographical_compare_3way__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    int
        strict_lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        );

    //<-
    template <typename Iterator1, typename Iterator2, typename BinaryPredicate>
    inline int
        strict_lexicographical_compare_3way(
            Iterator1 itr1
          , Iterator2 itr2
          , BinaryPredicate comp
        )
    {
        return ::boost::tree_node::_detail::lexicographical_compare_impl(
            itr1
          , itr2
          , comp
          , ::boost::mpl::true_()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__lexicographical_compare_3way
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    int lexicographical_compare_3way(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline int
        lexicographical_compare_3way(Iterator1 itr1, Iterator2 itr2)
    {
        typedef typename ::boost::iterator_value<Iterator1>::type _value_type1;
        typedef typename ::boost::iterator_value<Iterator2>::type _value_type2;

        return ::boost::tree_node::_detail::lexicographical_compare_dispatch(
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

//[reference__strict_lexicographical_compare_3way
namespace boost { namespace tree_node {

    template <typename Iterator1, typename Iterator2>
    int strict_lexicographical_compare_3way(Iterator1 itr1, Iterator2 itr2);

    //<-
    template <typename Iterator1, typename Iterator2>
    inline int
        strict_lexicographical_compare_3way(Iterator1 itr1, Iterator2 itr2)
    {
        typedef typename ::boost::iterator_value<Iterator1>::type _value_type1;
        typedef typename ::boost::iterator_value<Iterator2>::type _value_type2;

        return ::boost::tree_node::_detail::lexicographical_compare_dispatch(
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

#endif  // BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMP_3WAY_HPP_INCLUDED

