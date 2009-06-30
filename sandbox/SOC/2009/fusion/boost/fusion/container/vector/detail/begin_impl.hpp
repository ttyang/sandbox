/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_VECTOR_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_VECTOR_DETAIL_BEGIN_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef vector_iterator<Sequence, 0> type;

                static type
                call(Sequence v)
                {
                    return type(BOOST_FUSION_FORWARD(Sequence,v));
                }
            };
        };
    }
}}

#endif
