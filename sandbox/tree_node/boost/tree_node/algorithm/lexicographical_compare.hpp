// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED
#define BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED

#include <functional>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/detail/metafunction/has_first_type.hpp>
#include <boost/detail/metafunction/has_second_type.hpp>

//[reference__lexicographical_compare__with_comparators
namespace boost { namespace tree_node {

    template <typename Iterator, typename KeyCompare, typename ValueCompare>
    bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        );

    //<-
    template <typename Iterator, typename KeyCompare, typename ValueCompare>
    bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , KeyCompare key_comp
          , ValueCompare value_comp
        )
    {
        while (itr2)
        {
            if (itr1)
            {
                if (key_comp(itr1->first, itr2->first))
                {
                    return true;
                }

                if (key_comp(itr2->first, itr1->first))
                {
                    return false;
                }

                if (
                    value_comp(
                        itr1->second.get_data()
                      , itr2->second.get_data()
                    )
                )
                {
                    return true;
                }

                if (
                    value_comp(
                        itr2->second.get_data()
                      , itr1->second.get_data()
                    )
                )
                {
                    return false;
                }

                ++itr1;
                ++itr2;
            }
            else
            {
                return true;
            }
        }

        return false;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__lexicographical_compare__with_comparator
namespace boost { namespace tree_node {

    template <typename Iterator, typename BinaryPredicate>
    bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , BinaryPredicate comp
        );

    //<-
    template <typename Iterator, typename BinaryPredicate>
    bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , BinaryPredicate comp
        )
    {
        while (itr2)
        {
            if (itr1)
            {
                if (comp(itr1->get_data(), itr2->get_data()))
                {
                    return true;
                }
                else if (comp(itr2->get_data(), itr1->get_data()))
                {
                    return false;
                }
                else
                {
                    ++itr1;
                    ++itr2;
                }
            }
            else
            {
                return true;
            }
        }

        return false;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__lexicographical_compare
namespace boost { namespace tree_node {
  //<-
  namespace _detail {

    template <typename Iterator>
    inline bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , ::boost::mpl::true_
        )
    {
        typedef typename ::boost::iterator_value<Iterator>::type _value_type;

        return ::boost::tree_node::lexicographical_compare(
            itr1
          , itr2
          , ::std::less<typename _value_type::first_type>()
          , ::std::less<
                typename _value_type::second_type::traits::data_type
            >()
        );
    }

    template <typename Iterator>
    inline bool
        lexicographical_compare(
            Iterator itr1
          , Iterator itr2
          , ::boost::mpl::false_
        )
    {
        return ::boost::tree_node::lexicographical_compare(
            itr1
          , itr2
          , ::std::less<
                typename ::boost::iterator_value<
                    Iterator
                >::type::traits::data_type
            >()
        );
    }
  }  // namespace _detail
  //->

    template <typename Iterator>
    bool lexicographical_compare(Iterator itr1, Iterator itr2);

    //<-
    template <typename Iterator>
    bool lexicographical_compare(Iterator itr1, Iterator itr2)
    {
        typedef typename ::boost::iterator_value<Iterator>::type _value_type;

        return _detail::lexicographical_compare(
            itr1
          , itr2
          , typename ::boost::mpl::and_<
                typename ::boost::detail::has_first_type<_value_type>::type
              , typename ::boost::detail::has_second_type<_value_type>::type
            >::type()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP_INCLUDED

