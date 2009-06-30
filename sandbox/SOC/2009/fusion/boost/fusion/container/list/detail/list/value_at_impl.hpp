// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FUSION_CONTAINER_LIST_LIST_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_CONTAINER_LIST_LIST_VALUE_AT_IMPL_HPP

#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion
{
    struct list_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<list_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    detail::result_of_forward_as<
                        Sequence
                      , typename detail::remove_reference<Sequence>::type::storage_type
                   >::type
                storage_type;

                typedef typename
                    result_of::value_at<storage_type,N>::type
                type;
            };
        };
    }
}}

#endif
