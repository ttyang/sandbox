/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOLD_SEGMENTED_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOLD_SEGMENTED_HPP

#include <boost/fusion/support/internal/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };

    template <typename Sequence, typename State, typename Fun>
    struct result_of_fold<Sequence, State, Fun, true>
    {
        typedef typename
            result_of::segmented_fold_until<
                Sequence,
                State,
                segmented_fold_fun<typename remove_reference<Fun>::type>
            >::type
        type;

        static type
        call(State state, Sequence seq, Fun fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<typename remove_reference<Fun>::type>(fun));
        }
    };
}}}

#endif
