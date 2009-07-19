/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_MPL_ERASE_HPP
#define BOOST_FUSION_MPL_ERASE_HPP

#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Seq, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Seq, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::traits::tag_of<Seq>::type, result
                >::type
            type;
        };
    };
}}

#endif
