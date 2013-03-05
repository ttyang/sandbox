
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/apply_1.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/list_1.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/deduce.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/in.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/out.hpp>
#include <boost/contract/detail/preprocessor/keyword/typename.hpp>
#include <boost/contract/detail/preprocessor/keyword/class.hpp>
#include <boost/contract/detail/preprocessor/keyword/template.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/array/elem.hpp>

// PRIVATE //

// Cannot use PP_TUPLE_REM for reentrancy on GCC with C++0x.
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_REM_(tokens) tokens

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_REQUIRES_AUTO_(sign) \
    BOOST_PP_EXPR_IF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_REQUIRES_FRONT(sign), \
        requires \
    ) \
    BOOST_PP_EXPR_IF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(sign), \
        auto /* named value template parameter any type */ \
    )

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_template\
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_YES_( \
        sign) \
    template( \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_1(sign, \
                1, /* might be empty */ \
                0, /* no defaults (use usual `=` instead) */ \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_TEMPLATE_REMOVE_FRONT, \
                BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_REM_) \
    ) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST(sign, \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
  BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_)), \
        class \
    )

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_(sign) \
    /* template tparam `template(tparam_list) class` */ \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT(sign), \
        BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_YES_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(sign)
    
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REQUIRES_AUTO_(\
        sign) \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_(sign) \
    /* requires and auto (named params only ) */ \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_REQUIRES_AUTO_( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST( \
                  sign \
                , BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT \
  , BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_ \
            )))

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TRAIT_(sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEDUCE_FRONT(sign), \
        deduce \
    ) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IN_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign)), \
        in \
    ) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TYPENAME_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign))), \
        BOOST_PP_IDENTITY(typename) \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CLASS_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT(sign))), \
        BOOST_PP_IDENTITY(class) \
    , BOOST_PP_EMPTY \
    ))() \
    /* template tparam `template(tparam_list) class` */ \
    BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REQUIRES_AUTO_( \
            /* the following removal order matters */ \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPENAME_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
                sign \
            )))))

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_SIGN_(sign) \
    /* the following removal order matters */ \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_REQUIRES_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_TYPENAME_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_CLASS_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_IN_REMOVE_FRONT( \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEDUCE_REMOVE_FRONT( \
            sign \
        )))), \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TPL_REMOVE_ \
    ))))

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_AUX_KIND(traits_sign) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY_INIT_1(traits_sign, \
            BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_TRAIT_, \
            BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND_SIGN_)

// PUBLIC //

// Expand to `[deduce] [in] [typename | class | template(tparam_list) class]
// [auto | requires]` (empty for positional value tparam).
#define BOOST_CONTRACT_DETAIL_PP_TEMPLATE_PARAM_TRAITS_KIND(tparam_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_ARRAY_ELEM(0, BOOST_PP_TUPLE_ELEM(2, 0, tparam_traits)))

#endif // #include guard

