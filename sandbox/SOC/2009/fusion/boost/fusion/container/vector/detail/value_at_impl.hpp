/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_VECTOR_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_CONTAINER_VECTOR_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/mpl/at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename Tag>
    struct value_at_impl;

    template <>
    struct value_at_impl<vector_tag>
    {
        template <typename SeqRef, typename N>
        struct apply
        {
            typedef typename
                mpl::at<
                    typename detail::remove_reference<SeqRef>::type::types
                  , N
                >::type
            type;
        };
    };
}}}

#endif
