/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_QUERY_DETAIL_FIND_IF_SEGMENTED_HPP
#define BOOST_FUSION_ALGORITHM_QUERY_DETAIL_FIND_IF_SEGMENTED_HPP

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/internal/segmented_fold_until.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename Pred>
        struct find_if;
    }

    template<typename Pred, typename Seq>
    typename result_of::find_if<BOOST_FUSION_R_ELSE_CLREF(Seq), Pred>::type
    find_if(BOOST_FUSION_R_ELSE_CLREF(Seq) seq);

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename Pred, typename Seq>
    BOOST_FUSION_EXPLICIT_TEMPLATE_NON_CONST_ARG_OVERLOAD(
            result_of::find_if<,Seq,&,Pred>)
    find_if(Seq& seq);
#endif
}}

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename T>
        struct find;
    }

    template<typename T, typename Seq>
    typename result_of::find<BOOST_FUSION_R_ELSE_CLREF(Seq), T>::type
    find(BOOST_FUSION_R_ELSE_CLREF(Seq) seq);

#ifdef BOOST_FUSION_NO_RVALUE_REFERENCES
    template<typename T, typename Seq>
    BOOST_FUSION_EXPLICIT_TEMPLATE_NON_CONST_ARG_OVERLOAD(
        result_of::find<,Seq,&, T>)
    find(Seq& seq);
#endif
}}

namespace boost { namespace fusion { namespace detail
{
    template <typename Pred>
    struct find_if_segmented_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find_if<Sequence, Pred>::type
            iterator_type;

            typedef
                typename result_of::equal_to<
                    iterator_type
                  , typename result_of::end<Sequence>::type
                >::type
            continue_type;

            typedef
                typename mpl::eval_if<
                    continue_type
                  , mpl::identity<State>
                  , result_of::make_segmented_iterator<
                        iterator_type
                      , Context
                    >
                >::type
            type;

            static type call(Sequence& seq, State const&state, Context const& context, find_if_segmented_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }

            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }

            static type call_impl(Sequence& seq, State const&, Context const& context, mpl::false_)
            {
                return fusion::make_segmented_iterator(fusion::find_if<Pred>(seq), context);
            }
        };
    };

    template <typename Sequence, typename Pred>
    struct find_if_segmented
    {
        typedef
             typename result_of::segmented_fold_until<
                 Sequence
               , typename result_of::end<Sequence>::type
               , find_if_segmented_fun<Pred>
            >::type
        type;

        static type
        call(Sequence& seq)
        {
            return fusion::segmented_fold_until(
                seq
              , fusion::end(seq)
              , find_if_segmented_fun<Pred>());
        }
    };
}}}

#endif
