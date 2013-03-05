
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_HPP_
#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_HPP_

#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/subboost/contract/class_invariant.hpp>
#include <boost/contract/aux_/subboost/contract/static_class_invariant.hpp>
#include <boost/contract/aux_/macro/code_/assert.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_TYPE_( \
        z, n, id) \
    , BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n)

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_FUNC_( \
        z, n, id) \
    , & BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n) :: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC_FUNC

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_( \
        id, tpl, function_name, is_assertion, dispatch_param) \
    ( /* pp-list */ \
        /* unused tparam to delay assertion-func compilation */ \
        BOOST_PP_EXPR_IIF(is_assertion, \
            template< typename BOOST_CONTRACT_AUX_SYMBOL( (Unused)(id) ) > \
        ) \
        static void function_name( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
        ) \
    , \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_(id, a) \
    BOOST_CONTRACT_AUX_SYMBOL( (static_class_invariant_assertion) \
            (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_DECL_TOKENS_(\
        d, id, tpl, unused, dispatch_param, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_(id, tpl, \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_( \
                    a, id), 1 /* yes for assertion */, dispatch_param)

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_(id, a) \
    <void> /* unused tparam to delay assertion func compilation */ \
    ( \
        BOOST_PP_EXPR_IIF(tpl, typename) \
                /* NOTE: extra param for assertion func dispatch based on */ \
                /* requirements-- mpl::true_ iff assertion requirements */ \
                /* are met at compile-time */ \
                ::boost::mpl::bool_< \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a) \
                >::type() \
    );

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC \
    BOOST_CONTRACT_AUX_SYMBOL( (static_class_invariant) )

#define \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC_FUNC \
    BOOST_CONTRACT_AUX_SYMBOL( (subcontracted_static_class_invariant) )

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC( \
        id, tpl) \
    static void \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC_FUNC ( )\
    { \
        ::contract::aux::subcontract_static_class_invariant< \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_TYPE_, \
                    id) \
        >( \
            & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_COMMA_BASE_FUNC_, \
                    id) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC(id, tpl, v) \
    BOOST_CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, \
            static_class_invariant, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_DECL_TOKENS_,\
            ~, BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC(v)) \
    BOOST_PP_LIST_ENUM( \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_DECL_TOKENS_( \
                    id, tpl, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC, \
                    0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        BOOST_CONTRACT_AUX_CODE_ASSERT(id, tpl, static_class_invariant, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_ASSERTION_FUNC_CALL_, \
                /* POLICY: by default, no static class inv if not specified */ \
                ~, BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_STATIC(v)) \
    }

#endif // #include guard

