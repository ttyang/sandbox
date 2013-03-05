
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_HPP_
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_HPP_

#include <boost/contract/detail/preprocessor/keyword/boost/contract/out.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/in.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/deduce.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/requires.hpp>
#include <boost/contract/detail/preprocessor/keyword/auto.hpp>

// Utilities that only transform parameter traits into Boost.Parameter formats.

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQ_( \
        d, p, required_params, optional_params) \
    ( \
        BOOST_PP_LIST_APPEND(required_params, ( \
            ( /* Boost.Parameter required param is 2-tuple */ \
                BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
            , \
                BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
            ) \
        , BOOST_PP_NIL)) \
    , \
        optional_params \
    )

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_OPT_( \
        d, p, required_params, optional_params) \
    ( \
        required_params \
    , \
        BOOST_PP_LIST_APPEND(optional_params, ( \
            ( /* Boost.Parameter optional param is 3-tuple */ \
                BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
            , \
                BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
            , \
                BOOST_PP_ARRAY_ENUM( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)) \
            ) \
        , BOOST_PP_NIL)) \
    )

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT_TUPLE_( \
        d, required_optional, p) \
    BOOST_PP_IF(BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p)), \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_OPT_ \
    , \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQ_ \
    )(d, p \
        , BOOST_PP_TUPLE_ELEM(2, 0, required_optional) \
        , BOOST_PP_TUPLE_ELEM(2, 1, required_optional) \
    )

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT(params) \
    BOOST_PP_LIST_FOLD_LEFT( \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_REQOPT_TUPLE_, \
            (BOOST_PP_NIL, BOOST_PP_NIL), params)

// Expand to 1 iff `out` (not if `in out`).
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_ONLY(p) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            ))

// Expand to 1 iff `out` or `in out`.
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OUT_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))

// Precondition: classifier is `[deduce] out | in | in out` (i.e., named param).
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_CLASSIFIED_NAME(p) \
    /* order of following checking is important */ \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_ONLY(p), \
        out \
    , BOOST_PP_IIF( /* already checked not out-only, so in-out */ \
            BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_IS_OUT_OR_INOUT(p), \
        in_out \
    , /* else, in-only */ \
        BOOST_PP_TUPLE_REM(1) \
    ))(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p))
                
#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TYPE_REQUIREMENT(p) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT( \
            /* the following removal order is important */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))), \
        * BOOST_PP_TUPLE_EAT(1) /* any type */ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT( \
            /* the following removal order is important */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_OUT_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
                BOOST_PP_NIL /* handle possible EMPTY after removals */ \
            )))), \
        * BOOST_PP_ARRAY_DATA /* matching type requirement */ \
    , \
        BOOST_PP_ARRAY_DATA /* exact type specified */ \
    ))(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

// Tag.

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TAG(params, p) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE(params)), \
        BOOST_CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE \
    )(params) \
    :: \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_BOOST_TEMPLATE_TAG(tparams, t) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE(tparams)), \
        BOOST_CONTRACT_AUX_CONFIG_NAMED_PARAMETER_TAG_NAMESPACE_DEFAULT \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMESPACE \
    )(tparams) \
    :: \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_NAME(t)

#endif // #include guard

