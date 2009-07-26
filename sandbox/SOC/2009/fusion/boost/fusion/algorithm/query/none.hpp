/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_QUERY_NONE_HPP
#define BOOST_FUSION_ALGORITHM_QUERY_NONE_HPP

#include <boost/fusion/algorithm/query/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Seq, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Seq, typename F>
    inline bool
    none(BOOST_FUSION_R_ELSE_CLREF(Seq) seq, BOOST_FUSION_R_ELSE_CLREF(F) f)
    {
        return !fusion::any(
                BOOST_FUSION_FORWARD(Seq,seq),
                BOOST_FUSION_FORWARD(F,f));
    }

#ifdef BOOST_NO_RVALUE_REFERENCES
    template <typename Seq, typename F>
    inline bool
    none(Seq& seq, F const& f)
    {
        return !fusion::any(seq,f);
    }
#endif
}}

#endif
