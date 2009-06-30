/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_TRANSFORM_VIEW_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_TRANSFORM_VIEW_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/mpl/apply.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/view/transform_view/detail/apply_transform_result.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        // Unary Version
        template <>
        struct value_of_impl<transform_view_iterator_tag>
        {
            template <typename ItRef>
            struct apply
            {
                typedef typename detail::remove_reference<ItRef>::type it;

                typedef typename
                    mpl::apply<
                        detail::apply_transform_result<
                            typename it::transform_type
                        >
                      , typename result_of::value_of<
                            typename it::first_type
                        >::type
                    >::type
                type;
            };
        };

        // Binary Version
        template <>
        struct value_of_impl<transform_view_iterator2_tag>
        {
            template <typename ItRef>
            struct apply
            {
                typedef typename detail::remove_reference<ItRef>::type it;

                typedef typename
                    mpl::apply<
                        detail::apply_transform_result<
                            typename it::transform_type
                        >
                      , typename result_of::value_of<
                            typename it::first1_type
                        >::type
                      , typename result_of::value_of<
                            typename it::first2_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif
