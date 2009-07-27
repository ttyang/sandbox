// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/template.hpp>

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        VARIADIC_TEMPLATE_WITH_DEFAULT(BOOST_FUSION_MAX_SEQ_SIZE)
        struct BOOST_PP_CAT(make_,BOOST_FUSION_SEQ_NAME);
    }

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp/make_seq.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_FUSION_MAX_SEQ_SIZE)
#include BOOST_PP_ITERATE()

}}

#else

#define N BOOST_PP_ITERATION()

    namespace result_of
    {
        VARIADIC_TEMPLATE(N)
        struct BOOST_PP_CAT(make_,BOOST_FUSION_SEQ_NAME)
            EXPAND_TEMPLATE_ARGUMENTS_SPECIALIZATION(
                BOOST_FUSION_MAX_SEQ_SIZE,N)
        {
            typedef
                BOOST_FUSION_SEQ_NAME<
                    EXPAND_TEMPLATE_ARGUMENTS_BINARY(
                            N,
                            typename detail::as_fusion_element<,
                            >::type
                    )
                >
            type;
        };
    }

    VARIADIC_TEMPLATE_A(N)
    inline
#if N
        typename
#endif
        result_of::BOOST_PP_CAT(make_,BOOST_FUSION_SEQ_NAME)<
            EXPAND_TEMPLATE_ARGUMENTS_A_R_ELSE_CLREF(N)
        >::type
    BOOST_PP_CAT(make_,BOOST_FUSION_SEQ_NAME)(
        EXPAND_TEMPLATE_ARGUMENTS_PARAMETERS_A_R_ELSE_CLREF(N))
    {
        return
#if N
            typename
#endif
            result_of::BOOST_PP_CAT(make_,BOOST_FUSION_SEQ_NAME)<
                EXPAND_TEMPLATE_ARGUMENTS_A_R_ELSE_CLREF(N)
            >::type(EXPAND_PARAMETERS_A(N));
    }

#undef N
#endif
