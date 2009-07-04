/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_TRANSFORM_VIEW_TRANSFORM_VIEW_ITERATOR_HPP
#define BOOST_FUSION_VIEW_TRANSFORM_VIEW_TRANSFORM_VIEW_ITERATOR_HPP

#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/fusion/view/transform_view/detail/deref_impl.hpp>
#include <boost/fusion/view/transform_view/detail/next_impl.hpp>
#include <boost/fusion/view/transform_view/detail/prior_impl.hpp>
#include <boost/fusion/view/transform_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/transform_view/detail/advance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/distance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    // Unary Version
    struct transform_view_iterator_tag;

    template <typename First, typename FRef>
    struct transform_view_iterator
        : iterator_base<transform_view_iterator<First, FRef> >
    {
        //TODO !!!
        typedef FRef transform_type;
        typedef First first_type;

        typedef transform_view_iterator_tag fusion_tag;
        typedef typename traits::category_of<first_type>::type category;

        template<typename OtherTransformViewIt>
        transform_view_iterator(
                BOOST_FUSION_R_ELSE_CLREF(OtherTransformViewIt) it)
          : first(it.first)
          , f(it.f)
        {}

        transform_view_iterator(First const& first, transform_type f)
          : first(first)
          , f(&f)
        {}

        template<typename OtherTransformViewIt>
        transform_view_iterator&
        operator=(BOOST_FUSION_R_ELSE_CLREF(OtherTransformViewIt) it)
        {
            first=it.first;
            f=it.f;
            return *this;
        }

        first_type first;
        typename detail::remove_reference<transform_type>::type* f;
    };

    // Binary Version
    struct transform_view_iterator2_tag;

    template <typename First1, typename First2, typename FRef>
    struct transform_view_iterator2
        : iterator_base<transform_view_iterator2<First1, First2, FRef> >
    {
        typedef First1 first1_type;
        typedef First2 first2_type;
        typedef FRef transform_type;

        typedef transform_view_iterator2_tag fusion_tag;
        typedef typename traits::category_of<first1_type>::type category;

        template<typename OtherTransformViewIt>
        transform_view_iterator2(
                BOOST_FUSION_R_ELSE_CLREF(OtherTransformViewIt) it)
          : first1(it.first1)
          , first2(it.first2)
          , f(it.f)
        {}

        transform_view_iterator2(First1 const& first1,
                First2 const& first2,
                FRef f)
          : first1(first1)
          , first2(first2)
          , f(&f)
        {}

        template<typename OtherTransformViewIt>
        transform_view_iterator2&
        operator=(BOOST_FUSION_R_ELSE_CLREF(OtherTransformViewIt) it)
        {
            first1=it.first1;
            first2=it.first2;
            f=it.f;
            return *this;
        }

        first1_type first1;
        first2_type first2;
        typename detail::remove_reference<transform_type>::type* f;
    };
}}

#endif
