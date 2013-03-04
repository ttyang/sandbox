
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_HPP_
#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_HPP_

#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/subboost/contract/has_class_invariant.hpp>
#include <boost/contract/aux_/subboost/contract/class_invariant.hpp>
#include <boost/contract/aux_/subboost/contract/static_class_invariant.hpp>
#include <boost/contract/aux_/macro/code_/assert.hpp>
#include <boost/contract/detail/preprocessor/traits/class_invariant.hpp> // v

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_COMMA_BASE_TYPE_( \
        z, n, id) \
    , BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n)

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_COMMA_BASE_(z, n, id) \
    , dynamic_cast< \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n) \
        const* const \
      >(this) \
    , & BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n) :: \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_FUNC

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_DECL_TOKENS_(id, tpl, \
        function_name, is_assertion, dispatch_param) \
    ( /* pp-list */ \
        /* unused tparam to delay assertion-func compilation */ \
        BOOST_PP_EXPR_IIF(is_assertion, \
            template< typename BOOST_CONTRACT_AUX_SYMBOL( (Unused)(id) ) > \
        ) \
        void function_name( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
        ) const \
    , \
        BOOST_PP_NIL \
    )

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_(id, a) \
    BOOST_CONTRACT_AUX_SYMBOL( (class_invariant_assertion) \
            (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_DECL_TOKENS_( \
        d, id, tpl, unused, dispatch_param, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_DECL_TOKENS_(id, tpl, \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_( \
                    id, a), 1 /* yes for assertion */, dispatch_param)

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_(id, a) \
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

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_FUNC \
    /* func name also used to report error when INVARIANT macro is missing */ \
    ERROR_missing_class_invariant

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_FUNC \
    /* NOTE: must use this exact func name for introspection check to work */ \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_HAS_CLASS_INVARIANT_FUNC

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST( \
        id, tpl) \
    void \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_FUNC ( ) \
        const \
    { \
        ::contract::aux::subcontract_class_invariant< \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_COMMA_BASE_TYPE_, \
                    id) \
        >( \
              this \
            , & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_FUNC \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_COMMA_BASE_, \
                            id) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST(id, tpl, v) \
    BOOST_CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, class_invariant, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_DECL_TOKENS_, \
            ~, BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST(v)) \
    BOOST_PP_LIST_ENUM( \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_DECL_TOKENS_( \
                    id, tpl, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_FUNC, \
                    0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        /* first always check static class invariants */ \
        BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC(); \
        /* then check dynamic class invariants (in AND) */ \
        BOOST_CONTRACT_AUX_CODE_ASSERT(id, tpl, class_invariant, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_ASSERTION_FUNC_CALL_, \
                ~, BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST(v)) \
        /* then check volatile class inv but only if diff from dyn (in AND) */ \
        BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
                BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_VOLATILE(v)), \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC< \
                    false /* don't check static class inv (again) */>(); \
        ) \
    }

#endif // #include guard

