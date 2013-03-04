
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_PRECONDITION_HPP_
#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_HPP_

#include <boost/contract/aux_/symbol.hpp>
#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/subboost/contract/precondition.hpp>
#include <boost/contract/aux_/macro/code_/name.hpp>
#include <boost/contract/aux_/macro/code_/assert.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_COMMA_PARAM_DECL_(r, tpl_f, p) \
    , \
    BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(BOOST_PP_TUPLE_ELEM(2, 0, tpl_f), \
            BOOST_PP_TUPLE_ELEM(2, 1, tpl_f)) \
    ::contract::aux::arg_const< \
        BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))\
    >::type \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_COMMA_PARAM_NAME_(r, unused, p) \
    , \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

// Precondition: !CONFIG_PRECONDITION_OVERRIDE_01 && member(f)
#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_NO_OVERRIDE_(id, tpl, k, f) \
    /* if not ( !has_virtual(B::f) || pre(f) == NIL ) then error */\
    BOOST_CONTRACT_AUX_MPL_ASSERT_MSG( \
          (!BOOST_CONTRACT_AUX_CODE_OVERRIDE_CONDITION(id, tpl, k, f)) || \
          (BOOST_PP_LIST_IS_NIL( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS(f))) \
        , BOOST_PP_SEQ_CAT( \
  (ERROR_library_configuration_forbids_precondition_override_at_line_) \
                (id) ) \
        , ( /* can't print any type here because all bases checked */ ) \
    ); /* MPL assert requires trailing `;` */ \
    /* if has_virtual(B::f) then assert false (so overridden pre must hold) */ \
    BOOST_CONTRACT_AUX_CODE_ASSERT_CONDITION( \
            (!(BOOST_CONTRACT_AUX_CODE_OVERRIDE_CONDITION(id, tpl, k, f)) || \
                    false), \
            precondition, 0 /* no number (it will not be printed) */, \
            /* print same asserted condition */ \
            (!(BOOST_CONTRACT_AUX_CODE_OVERRIDE_CONDITION(id, tpl, k, f)) || \
                    false))

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC_DECL_TOKENS_(id, tpl, k, f, \
        function_name, is_assertion, dispatch_param) \
    BOOST_PP_TUPLE_TO_LIST( /* pp-list for tparams unwrapped commas */ \
        BOOST_PP_MAX(1, BOOST_PP_ADD( /* always at least 1 elem in tuple */ \
              BOOST_CONTRACT_AUX_CODE_TEMPLATE_COUNT( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
            , is_assertion /* add 1 if true, 0 otherwise */ \
        )) \
    , ( \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(is_assertion, \
                BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f)), \
            /* if not assertion, can't decl private here for subcontracting */ \
            private: \
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(is_assertion, \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f)), \
            template< \
        ) \
            /* actual tparams last because of trailing default params */ \
            BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
                    0, /* no `template<` and `>` */ \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
            /* unused tparam to delay assertion-func compilation */ \
            BOOST_PP_COMMA_IF(BOOST_PP_BITAND(is_assertion, \
                    BOOST_PP_LIST_IS_CONS( \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                                    f))))) \
            BOOST_PP_EXPR_IIF(is_assertion, \
                typename BOOST_CONTRACT_AUX_SYMBOL( (Unused)(id) ) \
            ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(is_assertion, \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f)), \
            > \
        ) \
        BOOST_PP_EXPR_IIF(BOOST_PP_COMPL( \
                BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                        k, f)), \
            /* POLICY: also cons pre are static so they cannot access obj */ \
            /* because there is no obj before successful const body exec */ \
            static \
        ) \
        void function_name \
        ( \
            /* extra param for type-dispatching based on ass. requirements */ \
            /* (can't go at the end because of default parameters) */\
            BOOST_PP_EXPR_IIF(is_assertion, dispatch_param) \
            BOOST_PP_COMMA_IF(is_assertion) /* next param always there */ \
            /* function_type for a dummy param used to resolve overloading */ \
            /* (because pre add const to args and obj so it might have same */ \
            /* signature as of overloaded func with const arg and obj) */ \
            /* not named so it cannot be used by mistake */ \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f)::body_type \
            /* all params are const (and ref) for const-correctness */ \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_PRECONDITION_COMMA_PARAM_DECL_, \
                    (tpl, f), \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        ) \
        BOOST_PP_EXPR_IIF( \
                BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                        k, f), \
            const /* const obj for const-correctness (unless static) */ \
        ) \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f) \
    ) )

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_(id, a) \
    BOOST_CONTRACT_AUX_SYMBOL( (precondition_assertion) \
            (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) (id) )

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_DECL_TOKENS_( \
        d, id, tpl, k_f, dispatch_param, a) \
    BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC_DECL_TOKENS_(id, tpl, \
            BOOST_PP_TUPLE_ELEM(2, 0, k_f), BOOST_PP_TUPLE_ELEM(2, 1, k_f), \
            BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_(id, a), \
            1 /* yes for assertion */, dispatch_param)

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_CALL_DATA_( \
        k, f, id, tpl, a) \
    /* NOTE: Extra parens (assertion_func<...>(...)); wrap tparam commas */ \
    (BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_(id, a) \
    < /* always a tpl because of extra Unused tparam */ \
        BOOST_CONTRACT_AUX_CODE_TEMPLATE_PARAM_NAME_ENUM( \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
        BOOST_PP_COMMA_IF(BOOST_PP_LIST_IS_CONS( \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f)))) \
        void /* unused tparam to disable assertion func compilation */ \
    > \
    ( \
        BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                /* NOTE: extra param for assertion func dispatch based on */ \
                /* requirements-- mpl::true_ iff assertion requirements */ \
                /* are met at compile-time */ \
                ::boost::mpl::bool_< \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a) \
                >::type() \
        , BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
                BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f):: \
                body_type() \
        BOOST_PP_LIST_FOR_EACH( \
                BOOST_CONTRACT_AUX_CODE_PRECONDITION_COMMA_PARAM_NAME_, tpl, \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ));

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_CALL_( \
        d, id, tpl, k_f, a) \
    BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_CALL_DATA_(id, tpl, \
            BOOST_PP_TUPLE_ELEM(2, 0, k_f), BOOST_PP_TUPLE_ELEM(2, 1, k_f), a)

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_ASSERTION_FUNC_DEF(id, tpl, precondition, \
            BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_DECL_TOKENS_, \
            (k, f), BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS(f)) \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        private: \
    ) \
    BOOST_PP_LIST_ENUM(BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC_DECL_TOKENS_( \
            id, tpl, k, f, \
            BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC(id, tpl, k, f), \
            0 /* not for assertion */, ~ /* no dispatch param */)) \
    { \
        /* POLICY: N1962 requires that preconditions cannot be overridden */ \
        BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL( \
                BOOST_CONTRACT_AUX_CONFIG_PRECONDITION_OVERRIDE_01), \
                BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
                        k, f)), \
            BOOST_CONTRACT_AUX_CODE_PRECONDITION_NO_OVERRIDE_ \
        , \
            BOOST_PP_TUPLE_EAT(4) \
        )(id, tpl, k, f) \
        BOOST_CONTRACT_AUX_CODE_ASSERT(id, tpl, precondition, \
                BOOST_CONTRACT_AUX_CODE_PRECONDITION_ASSERTION_FUNC_CALL_, \
                (k, f), BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PRECONDITIONS(f)) \
    }

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_COMMA_BASE_( \
        z, n, id_tpl_k_f) \
    , dynamic_cast< \
        BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n) \
        const \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE( \
                BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f)) \
        * const \
      >(this) \
    /* call function to check all (base, base's base, etc) preconditions */ \
    , BOOST_CONTRACT_AUX_CODE_FUNC_PTR( \
            BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), \
            BOOST_PP_TUPLE_ELEM(4, 1, id_tpl_k_f), \
            BOOST_PP_TUPLE_ELEM(4, 2, id_tpl_k_f), \
            BOOST_PP_TUPLE_ELEM(4, 3, id_tpl_k_f), \
            BOOST_PP_EXPAND( \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_FUNC \
                    id_tpl_k_f), \
            BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_BASE_TYPE( \
                    BOOST_PP_TUPLE_ELEM(4, 0, id_tpl_k_f), n))

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_( \
        id, tpl, k, f) \
    /* this cannot be private */ \
    BOOST_PP_LIST_ENUM(BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC_DECL_TOKENS_( \
            id, tpl, k, f, \
            BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_FUNC( \
                    id, tpl, k, f), \
            0 /* not for assertion */, void /* no ass. req. dispatch type */)) \
    { \
        ::contract::aux::subcontract_precondition< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
              this \
            /* call func to check this object (not all) precondition */ \
            , BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, \
                    BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC(id, tpl, k, f), \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_REPEAT(BOOST_CONTRACT_CONFIG_INHERITANCE_MAX, \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_COMMA_BASE_, \
                    (id, tpl, k, f)) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_PRECONDITION_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        ); \
    }

// PUBLIC //

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (precondition))

#define BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_FUNC( \
        id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (subcontracted_precondition))

#define BOOST_CONTRACT_AUX_CODE_PRECONDITION(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        BOOST_CONTRACT_AUX_CODE_PRECONDITION_ \
    )(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION( \
            k, f), \
        /* must be public for subcontracting */ \
        public: BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_ \
    , \
        /* ctor and dtor subcontract via base-class creation rules */ \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f)

#endif // #include guard

