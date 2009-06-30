/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_EQUAL_TO_HPP
#define BOOST_FUSION_ITERATOR_EQUAL_TO_HPP

#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl
        {
            // default implementation
            template <typename It1Ref, typename It2Ref>
            struct apply
              : is_same<
                    typename detail::identity<It1Ref>::type
                  , typename detail::identity<It2Ref>::type
                >
            {};
        };

        template <>
        struct equal_to_impl<iterator_facade_tag>
        {
            template <typename It1Ref, typename It2Ref>
            struct apply
              : detail::remove_reference<It1Ref>::type::
                    template equal_to<It1Ref, It2Ref>
            {};
        };
    }

    namespace result_of
    {
        template <typename It1, typename It2>
        struct equal_to
          : extension::equal_to_impl<typename traits::tag_of<It1>::type>::
                template apply<
                    typename detail::add_lref<It1>::type
                  , typename detail::add_lref<It2>::type
                >
        {};
    }

    namespace iterator_operators
    {
        template <typename Iter1, typename Iter2>
        inline typename
            enable_if<
                mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
              , bool
                >::type
        operator==(Iter1 const&, Iter2 const&)
        {
            return result_of::equal_to<Iter1 const&, Iter2 const&>::value;
        }

        template <typename Iter1, typename Iter2>
        inline typename
        enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
          , bool
            >::type
        operator!=(Iter1 const&, Iter2 const&)
        {
            return !result_of::equal_to<Iter1 const&, Iter2 const&>::value;
        }
    }

    using iterator_operators::operator==;
    using iterator_operators::operator!=;
}}

#endif
