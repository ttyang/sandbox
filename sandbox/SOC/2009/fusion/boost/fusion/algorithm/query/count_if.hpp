/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_QUERY_COUNT_IF_HPP
#define BOOST_FUSION_ALGORITHM_QUERY_COUNT_IF_HPP

#include <boost/fusion/support/ref.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/fusion/algorithm/query/detail/count_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct count_if
        {
            typedef int type;
        };
    }

    template <typename Seq, typename F>
    inline int
    count_if(BOOST_FUSION_R_ELSE_LREF(Seq) seq, BOOST_FUSION_R_ELSE_LREF(F) f)
    {
        return detail::count_if(
            BOOST_FUSION_FORWARD(Seq,seq),
            BOOST_FUSION_FORWARD(F,f),
            typename traits::category_of<BOOST_FUSION_R_ELSE_LREF(Seq)>::type()
            );
    }
}}

#endif
