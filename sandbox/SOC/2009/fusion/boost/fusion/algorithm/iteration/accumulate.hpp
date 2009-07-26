/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_ACCUMULATE_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_ACCUMULATE_HPP

#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/ref.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Seq, typename State, typename F>
        struct accumulate
          : result_of::fold<Seq, State, F>
        {};
    }

    template <typename Seq, typename State, typename F>
    inline typename result_of::accumulate<
        BOOST_FUSION_R_ELSE_CLREF(Seq)
      , BOOST_FUSION_R_ELSE_CLREF(State)
      , BOOST_FUSION_R_ELSE_CLREF(F)
    >::type
    accumulate(BOOST_FUSION_R_ELSE_CLREF(Seq) seq,
            BOOST_FUSION_R_ELSE_CLREF(State) state,
            BOOST_FUSION_R_ELSE_CLREF(F) f)
    {
        return fusion::fold(
                BOOST_FUSION_FORWARD(Seq,seq),
                BOOST_FUSION_FORWARD(State,state),
                BOOST_FUSION_FORWARD(F,f));
    }

#ifdef BOOST_NO_RVALUE_REFERENCES
    template <typename Seq, typename State, typename F>
    inline typename result_of::accumulate<Seq&, State const&, F const&>::type
    accumulate(Seq& seq,State const& state,F const& f)
    {
        return fusion::fold(seq,state,f);
    }
#endif
}}

#endif
