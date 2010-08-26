/*==============================================================================
    Copyright (c) 2001-2006 Joel de Guzman
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOR_EACH_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_DETAIL_FOR_EACH_HPP

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace fusion { namespace detail
{
    template<int N>
    struct for_each_unrolled;

#define BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_N(Z,N,_)                            \
    f(fusion::deref(BOOST_PP_CAT(it,N)));                                       \
                                                                                \
    typedef typename                                                            \
        result_of::next<BOOST_PP_CAT(It,N) const&>::type                        \
    BOOST_PP_CAT(It,BOOST_PP_INC(N));                                           \
    BOOST_PP_CAT(It,BOOST_PP_INC(N)) const BOOST_PP_CAT(it,BOOST_PP_INC(N))(    \
        fusion::next(BOOST_PP_CAT(it,N)));

#define BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_NEXT(N_)                            \
    for_each_unrolled<N-BOOST_FUSION_UNROLLED_DEPTH>::call(                     \
        fusion::next(BOOST_PP_CAT(it,BOOST_PP_DEC(N_))),                        \
        BOOST_FUSION_FORWARD(F,f));

#define BOOST_FUSION_UNROLLED_FOR_EACH_IMPL(Z,N_,_)                             \
    template<BOOST_PP_EXPR_IIF(                                                 \
        BOOST_PP_EQUAL(BOOST_PP_INC(N_),BOOST_FUSION_UNROLLED_DEPTH), int N)    \
    >                                                                           \
    struct for_each_unrolled                                                    \
    BOOST_PP_EXPR_IIF(                                                          \
        BOOST_PP_NOT_EQUAL(BOOST_PP_INC(N_),BOOST_FUSION_UNROLLED_DEPTH), <N_>) \
    {                                                                           \
        template<typename It0, typename F>                                      \
        static void                                                             \
        call(                                                                   \
            It0 const& BOOST_PP_EXPR_IF(N_,it0),                                \
            BOOST_FUSION_RREF_ELSE_OBJ(F) BOOST_PP_EXPR_IF(N_,f))               \
        {                                                                       \
            BOOST_PP_REPEAT(N_,BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_N,_)         \
                                                                                \
            BOOST_PP_IIF(                                                       \
                BOOST_PP_EQUAL(N_,BOOST_FUSION_UNROLLED_DEPTH),                 \
                BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_NEXT,                       \
                BOOST_PP_TUPLE_EAT(1))(N);                                      \
        }                                                                       \
    };

    BOOST_PP_REPEAT(
        BOOST_FUSION_UNROLLED_DEPTH,
        BOOST_FUSION_UNROLLED_FOR_EACH_IMPL,
        _)

#undef BOOST_FUSION_UNROLLED_FOR_EACH_IMPL
#undef BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_NEXT
#undef BOOST_FUSION_UNROLLED_FOR_EACH_IMPL_N
}}}


#endif
