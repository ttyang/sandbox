
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_HPP_
#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_HPP_

#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/subboost/contract/class_invariant.hpp>
#include <boost/contract/aux_/subboost/contract/static_class_invariant.hpp>
#include <boost/contract/aux_/macro/code_/assert.hpp>

// PRIVATE //

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_TYPE_( \
        z, n, id) \
    , BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE(id, n)

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_( \
        z, n, id_tpl) \
    , dynamic_cast< \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(2, 0, id_tpl), n) \
        const volatile* const \
      >(this) \
    , & BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
            BOOST_PP_TUPLE_ELEM(2, 0, id_tpl), n) :: \
      BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 1, id_tpl), \
        template \
      ) \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC\
            <void> /* extra template param to delay compilation */

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_(v) \
    /* POLICY: by default, volatile class inv same as dyn if not specified */ \
    /* (this is likely what the user would want but it could generate */ \
    /* compile-time error because dyn inv use non volatile obj in which */ \
    /* case user will specify volatile inv */ \
    BOOST_PP_IIF( \
            BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_HAS_CONST_VOLATILE(\
                    v), /* has_volatile iff volatile are specified */ \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST_VOLATILE \
    , \
        BOOST_CONTRACT_DETAIL_PP_CLASS_INVARIANT_TRAITS_CONST \
    )(v)

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_(id) \
    BOOST_CONTRACT_AUX_SYMBOL( (check_static_class_invariant)(id) )

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
        id, tpl, function_name, is_assertion, dispatch_param) \
    ( /* pp-list */ \
        /* NOTE: this tparam is also used to disable compilation */ \
        /* of the volatile class invariant lazily until an actual volatile */ \
        /* member function is used (this is because volatile class inv */ \
        /* are defined to match the normal class inv by default and that */ \
        /* errors at compile-time but only when volatile member are used */ \
        template< bool \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_(id) \
        > \
        void function_name( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
        ) const volatile \
    , \
        BOOST_PP_NIL \
    )

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_(id, a) \
    BOOST_CONTRACT_AUX_SYMBOL( (volatile_class_invariant_assertion) \
            (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_DECL_TOKENS_( \
        d, id, tpl, unused, dispatch_param, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
            id, tpl, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_( \
                    id, a), \
            1 /* yes for assertion */, dispatch_param)

#define \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_CALL_( \
        d, id, tpl, unused, a) \
    BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_( \
            id, a) \
    <false> /* unused tparam to delay assertion func compilation */ \
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

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC \
    BOOST_CONTRACT_AUX_SYMBOL( (volatile_class_invariant) )

#define \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC\
    BOOST_CONTRACT_AUX_SYMBOL( (subcontracted_volatile_class_invariant) )

#define \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE( \
        id, tpl) \
    /* NOTE: volatile subcontracted class invariants must be a template so */ \
    /* to not compile unless volatile member actually contracted so to */ \
    /* avoid volatile qualifier errors until because volatile class */ \
    /* invariants defaulted to dynamic ones if not specified (so tpl = 1 */ \
    /* forced here) */ \
    template< typename BOOST_CONTRACT_AUX_SYMBOL( (Unused) ) > /* always tpl */\
    void \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC\
        ( ) \
        const volatile \
    { \
        ::contract::aux::subcontract_class_invariant< \
            BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_TYPE_, \
                    id) \
        >( \
              this \
            , & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
              template /* always a template (tpl = 1 forced) */ \
              BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC< \
                    true /* check static class inv */> \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_COMMA_BASE_, \
                    (id, 1 /* always a template (tpl = 1 forced) */)) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE(id, tpl, v) \
    BOOST_CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, \
            volatile_class_invariant, \
BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_DECL_TOKENS_,\
            ~, BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_( \
                    v)) \
    BOOST_PP_LIST_ENUM( \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_DECL_TOKENS_( \
                    id, tpl, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_FUNC, \
                    0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        /* first always check static class invariants (bool var is used */ \
        /* to not check static inv twice when dyn inv call volatile inv) */ \
        if( \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_CHECK_STATIC_VAR_(id))\
        { \
            BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC(); \
        } \
        /* then check volatile class invariants (in AND with static) */ \
        BOOST_CONTRACT_AUX_CODE_ASSERT(id, tpl, volatile_class_invariant, \
  BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_ASSERTION_FUNC_CALL_, \
                ~, BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_VOLATILE_TRAITS_(v))\
    }

#endif // #include guard

