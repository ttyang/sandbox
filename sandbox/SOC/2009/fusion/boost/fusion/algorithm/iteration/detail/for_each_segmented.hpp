/*==============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOR_EACH_SEGMENTED_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOR_EACH_SEGMENTED_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/void.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/internal/segmented_fold_until.hpp>

namespace boost { namespace fusion
{
    template<typename Seq, typename F>
    void
    for_each(BOOST_FUSION_R_ELSE_CLREF(Seq) seq,
        BOOST_FUSION_RREF_ELSE_OBJ(F) f);

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename Seq, typename F>
    void
    for_each(Seq& seq,F f);
#endif
}}

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_for_each_fun
    {
        explicit segmented_for_each_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef mpl::void_ type;
            typedef mpl::true_ continue_type;

            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return type();
            }
        };
    };

    template<typename SeqRef, typename F>
    void
    for_each(SeqRef seq, F const& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, mpl::void_(), segmented_for_each_fun<F>(f));
    }
}}}


#endif
