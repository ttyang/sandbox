/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_MPL_INSERT_RANGE_HPP
#define BOOST_FUSION_MPL_INSERT_RANGE_HPP

#include <boost/mpl/insert_range.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_range_impl;

    template <>
    struct insert_range_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename Range>
        struct apply
        {
            typedef typename
                fusion::result_of::insert_range<Sequence, Pos, Range>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::traits::tag_of<Sequence>::type, result
                >::type
            type;
        };
    };
}}

#endif
