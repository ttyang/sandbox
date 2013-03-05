
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_HPP_
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/deduce.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/in.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/out.hpp>
#include <boost/contract/detail/preprocessor/keyword/register.hpp>
#include <boost/contract/detail/preprocessor/keyword/auto.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// Second `auto` is for named parameter any type.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_AUTO_2ND_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(sign), \
        auto \
    )

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_REQUIRES_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(sign),\
        requires \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_AUTO_2ND_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT(sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_OUT_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT(sign), \
        out \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_REQUIRES_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT(sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_IN_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT(sign), \
        in \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_OUT_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT(sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_DEDUCE_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(sign), \
        deduce \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_IN_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_REGISTER_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_FRONT(sign),\
        register \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_DEDUCE_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_FRONT(sign))

// First `auto` is for storage classifiers.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_AUTO_1ST_(sign) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(sign), \
        auto \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_REGISTER_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT(sign))

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_AUTO_1ST_(sign)

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_TRAIT_xx(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(sign), \
        auto BOOST_PP_TUPLE_EAT(1) /* auto for storage classifier */ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REGISTER_FRONT(sign), \
        register BOOST_PP_TUPLE_EAT(1) \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(sign), \
        deduce BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_IN_xx \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT(sign), \
        in BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_OUT_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT(sign), \
        out BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_REQUIRES_ \
    , \
        BOOST_PP_TUPLE_EAT(1) /* empty (for not classified pos param) */ \
    )))))( /* the following removal order is important */ \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \
            sign \
        ))))) \
    )

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_SIGN_(sign) \
    /* the following removal order is important */ \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT( \
    /* auto for named param of any type */ \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_REGISTER_REMOVE_FRONT( \
    /* auto as storage classifier */ \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \
        sign \
    )))))))

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_AUX_CLASSIFIER(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT_1(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER_SIGN_)

// PUBLIC //

// Expand to `[deduce] in | out | in out [auto | requires]` for named params,
// or `[auto | register]` for positional param.
#define BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(fparam_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(0, BOOST_PP_TUPLE_ELEM(2, 0, fparam_traits)))

#endif // #include guard

