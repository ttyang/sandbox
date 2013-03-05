
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CODE_FUNC_HPP_
#define BOOST_CONTRACT_AUX_CODE_FUNC_HPP_

#include <boost/contract/aux_/debug.hpp>
#include <boost/contract/aux_/call/nonstatic_member_function.hpp>
#include <boost/contract/aux_/call/static_member_function.hpp>
#include <boost/contract/aux_/call/free_function.hpp>
#include <boost/contract/aux_/call/constructor_exit.hpp>
#include <boost/contract/aux_/call/destructor.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_const.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_const_volatile.hpp>
#include <boost/contract/aux_/macro/code_/class_invariant_static.hpp>
#include <boost/contract/aux_/macro/code_/precondition.hpp>
#include <boost/contract/aux_/macro/code_/constructor_entry.hpp>
#include <boost/contract/aux_/macro/code_/body.hpp>
#include <boost/contract/aux_/macro/code_/override.hpp>
#include <boost/contract/aux_/macro/code_/final.hpp>
#include <boost/contract/aux_/macro/code_/new.hpp>
#include <boost/contract/aux_/macro/code_/result_type.hpp>
#include <boost/contract/aux_/config.hpp>
#include <boost/contract/aux_/concept_assert.hpp>
#include <boost/contract/aux_/preprocessor/func_kind.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp> // f
#include <boost/contract/detail/preprocessor/traits/func_param.hpp> // p
#include <boost/contract/detail/preprocessor/keyword/boost/contract/comma.hpp>
#include <boost/contract/detail/preprocessor/keyword/public.hpp>
#include <boost/preprocessor/list/for_each_i.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/array/enum.hpp>
#include <boost/preprocessor/array/size.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_FUNC_DOUBLE_PAREN_CONCEPT_(r, unused, concept) \
    ((concept))

#define BOOST_CONTRACT_AUX_CODE_FUNC_PARAM_DECL_ENUM_(r, default01, i, p) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_CLASSIFIER(p) \
    BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p)) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p) \
    BOOST_PP_IIF(BOOST_PP_AND(default01, BOOST_PP_ARRAY_SIZE( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p))), \
        = BOOST_PP_ARRAY_ENUM \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_DEFAULT(p))

#define BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_TYPE_(r, unused, p) \
    , \
    BOOST_PP_ARRAY_ENUM(BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_TYPE(p))

#define BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_NAME_(r, unused, p) \
    , \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_CODE_FUNC_PARAM_NAME_ENUM_(r, unused, i, p) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_PARAM_TRAITS_NAME(p)

// Precondition: !EMPTY(ACCESS(f)).
#define BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_( \
        f, class_inv_func_ptr) \
    BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_FRIEND(f))), \
        /* NOTE: friends are contracts as static members however they never */ \
        /* check (static) class invariants (regardless of their declaration */ \
        /* access level) because they are not actually members */ \
        0 /* null ptr to not check class inv */ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS(f)), \
        /* POLICY: only public func check class inv */ \
        class_inv_func_ptr \
    , \
        0 /* null ptr to not check class inv */ \
    ))

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPT_ASSERT_(r, id, i, concept) \
    /* can expand multiple of this macros on same line because of id */ \
    BOOST_CONTRACT_AUX_CONCEPT_ASSERT( (BOOST_PP_ARRAY_ENUM(concept)), \
        /* pp-cat infix because Boost.ConceptCheck will cat it again */ \
        BOOST_CONTRACT_AUX_SYMBOL( (concept_check)(id)(i) ) \
    ); /* `;` ends concept assertion */

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
    /* NOTE: use CONCEPT_ASSERT instead of CONCEPT_REQUIRES because */ \
    /* REQUIRES does not compile and/or gives multiple concept errors when */ \
    /* used with fwd decl (fwd decl are necessary for the contracted func */ \
    /* as impl by this lib) -- the main reason to use REQUIRES is to spec */ \
    /* concepts in func decl instead of def but that is already achieved */ \
    /* by this lib syntax and its `requires` "keyword" */ \
    BOOST_PP_LIST_FOR_EACH_I(BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPT_ASSERT_, id, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONCEPTS(f))

#define BOOST_CONTRACT_AUX_CODE_FUNC_VIRTUAL_SPECIFIERS_CHECK_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_FINAL_CHECK(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_OVERRIDE_CHECK(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NEW_CHECK(id, tpl, k, f)

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_TRY_BLOCK_ENABLE_( \
        id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_BITAND( \
            BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
                    BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01), \
            BOOST_PP_LIST_IS_CONS( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(f))), \
        ( /* a pp-list to be used with constructor member initializers */ \
            /* no typename needed here (inits are always types) */ \
            BOOST_IDENTITY_TYPE((::contract::aux::constructor_inits_eval< \
                  BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
                , ::contract::aux::constructor_inits_eval_try_block_set \
            >))( \
                /* enabled try-block to catch initializers exceptions */ \
                ::contract::aux::constructor_try_block_guard< \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE \
                >::BOOST_CONTRACT_AUX_SYMBOL((enable))() \
            ) \
        , \
            BOOST_PP_NIL \
        ) \
    , \
        BOOST_PP_NIL /* no constructor try-block */ \
    )

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CALL_BOOST_CONTRACT_DEF_( \
        id, tpl, k, f, body_func) \
    { \
        /* POLICY: Only constructor member initializers and body are */ \
        /* within constructor-try-block (but no contract implementation */ \
        /* code and assertions) so disable try-blocks here after */ \
        /* constructor initializers have been executed (contract code will */ \
        /* re-enable try-block while calling the body) */ \
        ::contract::aux::constructor_try_block_guard< \
                BOOST_CONTRACT_AUX_CODE_CLASS_TYPE >:: \
                BOOST_CONTRACT_AUX_SYMBOL((disable))(); \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
        ::contract::aux::call_constructor_exit< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, body_func, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
            , this \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
                BOOST_PP_SEQ_ENUM \
            , \
                BOOST_PP_TUPLE_EAT(1) \
            )( \
                ( BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                        BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC) ) \
                ( BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                        BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_FUNC) ) \
            ) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f),\
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CALL_BODY_DEF_( \
        id, tpl, k, f, body_func) \
    { \
        /* LIMITATION: to handle member initializers (that are defined */ \
        /* within the macros) within the constructor-try-block, the */ \
        /* try-block also needs to be defined within the macros so */ \
        /* constructor macros must expand to an extra function within the */ \
        /* try-block that just calls the body even when contracts are all */ \
        /* turned off (this adds a small run-time overhead for */ \
        /* constructors with member initializers and function-try-blocks */ \
        /* even when contracts are off), also needed for ctor named params */ \
        /* NOTE: no need for try block disable here because no contracts */ \
        (body_func /* outer paren to wrap eventual tparams */ \
            BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE( \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
        ( /* arguments */ \
            BOOST_PP_LIST_FOR_EACH_I( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_PARAM_NAME_ENUM_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
        )); \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CATCH_( \
        r, unused, catch_traits) \
    catch(BOOST_CONTRACT_DETAIL_PP_CATCH_TRAITS_EXCEPTION_DECL(catch_traits)) \
    { \
        BOOST_PP_EXPR_IIF( \
                BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                      ) \
                ), \
            if(!::contract::aux::constructor_try_block_guard< \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE >:: \
                    BOOST_CONTRACT_AUX_SYMBOL((enabled))()) \
                /* POLICY: Contracts exec outside function-try-block */ \
                /* (see N1962) so re-throw and don't allow try-bloc exec */ \
            { throw; } \
        ) \
        BOOST_CONTRACT_DETAIL_PP_CATCH_TRAITS_STATEMENTS(catch_traits) \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_COMMA_INIT_( \
        r, unused, i, init) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_ARRAY_ENUM(init)

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INITS_(inits) \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS(inits), :) \
    BOOST_PP_LIST_FOR_EACH_I( \
            BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_COMMA_INIT_, ~, inits)

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INIT_ARRAY_WRAP_( \
        d, unused, init) \
    /* wrap into 1-size array so can be used with user-specified inits */ \
    /* (which are always wrapped in arrays to handle unwrapped commas) */ \
    (1, (init))

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF_( \
        id, tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF(id, tpl, k, f, body_func, \
            BOOST_PP_NIL) \

#define BOOST_CONTRACT_AUX_CODE_FUNC_DESTRUCTOR_DEF_(id, tpl, k, f, body_func) \
    { \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
        ::contract::aux::call_destructor< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, body_func, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            , this \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
                BOOST_PP_SEQ_ENUM \
            , \
                BOOST_PP_TUPLE_EAT(1) \
            )( \
                ( BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                        BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_STATIC_FUNC) ) \
                ( BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                        BOOST_CONTRACT_AUX_CODE_CLASS_INVARIANT_CONST_FUNC) ) \
                ( BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_FUNC) )\
            ) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_STATIC_MEMBER_DEF_( \
        id, tpl, k, f, body_func) \
    { \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
        return ::contract::aux::call_static_member_function< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, body_func, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_STATIC_FUNC) \
            ) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC( \
                    id, tpl, k, f), BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC(id, tpl, k, f),\
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_FREE_DEF_(id, tpl, k, f, body_func) \
    { \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
        return ::contract::aux::call_free_function< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, body_func, \
                    /* class type not used here */ \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_PRECONDITION_FUNC( \
                    id, tpl, k, f), BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
                    /* class type not used here (because free func */ \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, BOOST_CONTRACT_AUX_CODE_OLDOF_FUNC( \
                    id, tpl, k, f), BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
        ); \
    }

#define BOOST_CONTRACT_AUX_CODE_FUNC_NONSTATIC_MEMBER_DEF_( \
        id, tpl, k, f, body_func) \
    { \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONCEPTS_(id, tpl, k, f) \
        return ::contract::aux::call_nonstatic_member_function< \
            BOOST_CONTRACT_AUX_CODE_FUNC_TYPENAME(tpl, f) \
            BOOST_CONTRACT_AUX_CODE_SIGNATURE_TYPE(id, tpl, k, f) \
        >( \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __FILE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01, __LINE__) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_DEBUG_01) \
            BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, body_func, \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_LIST_FOR_EACH( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_COMMA_PARAM_NAME_, ~, \
                    BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
            , this \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01) \
            BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_CLASS_INVARIANT_PTR_(f, \
                        & BOOST_CONTRACT_AUX_CODE_CLASS_TYPE :: \
                    BOOST_PP_IIF(BOOST_PP_IS_EMPTY( \
                            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)), \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_FUNC \
                    , \
                        BOOST_PP_EXPR_IIF(tpl, template) \
BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_CLASS_INVARIANT_CONST_VOLATILE_FUNC\
                                <void> /* unused tparam to delay compilation */\
                    ) \
                ) \
            ) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, \
  BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_PRECONDITION_FUNC( \
                            id, tpl, k, f), \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
            BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01) \
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
                BOOST_CONTRACT_AUX_CODE_FUNC_PTR \
            , \
                BOOST_PP_TUPLE_EAT(6) \
            )(id, tpl, k, f, \
                    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACTED_OLDOF_FUNC( \
                            id, tpl, k, f), \
                    BOOST_CONTRACT_AUX_CODE_CLASS_TYPE) \
        ); \
        /* for tpl func virtual spec checks must be within this func def */ \
        /* so they can access actual tparam instantiated types, however */ \
        /* for non-tpl func this causes MSVC duplicate definition linker */ \
        /* errors so... (continues below) */ \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_AUX_CODE_FUNC_VIRTUAL_SPECIFIERS_CHECK_ \
        , \
            BOOST_PP_TUPLE_EAT(4) \
        )(id, tpl, k, f) \
    } \
    /* (continued from above) ... for non-tpl func these virtual spec */ \
    /* checks must appear outside the func def to avoid MSVC liker errors */ \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        BOOST_CONTRACT_AUX_CODE_FUNC_VIRTUAL_SPECIFIERS_CHECK_ \
    )(id, tpl, k, f)

// PUBLIC //

// Used to access a function pointer eventually member and template (class_type
// ignored if not a member function).
// Expand to: `& [class_type::[template]] func_name [<tparam_name, ...>]`
#define BOOST_CONTRACT_AUX_CODE_FUNC_PTR(id, tpl, k, f, func_name, class_type) \
    & /* get pointer to function */ \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        class_type :: \
    ) \
    BOOST_PP_EXPR_IIF( \
            BOOST_PP_BITAND( \
                  tpl \
                , BOOST_PP_BITAND( \
                      BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
                    , BOOST_PP_LIST_IS_CONS( \
                            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
  BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS( \
                                    f)))\
                ) \
            ), \
        template \
    ) \
    func_name \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_INSTANCE( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f)))

// Named params need to force body even if all contracts off.
#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF_FORCE( \
        id, tpl, k, f, body_func, first_inits, force_body) \
    BOOST_PP_EXPR_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(f)), \
        try /* constructor-try-block within macros to handle initializers */ \
    ) \
    BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INITS_( \
        BOOST_PP_LIST_APPEND( \
              BOOST_PP_LIST_TRANSFORM( \
                    BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INIT_ARRAY_WRAP_, \
                            ~, first_inits) \
            , BOOST_PP_LIST_APPEND( \
            /* NOTE: order of this pp-list append follows inheritance order */ \
            /* (and try-block must be enabled after constructor-entry) */ \
                  BOOST_PP_LIST_TRANSFORM( \
  BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INIT_ARRAY_WRAP_, \
                        ~, BOOST_CONTRACT_AUX_CODE_CONSTRUCTOR_ENTRY( \
                                id, tpl, k, f)) \
                , BOOST_PP_LIST_APPEND( \
                      BOOST_PP_LIST_TRANSFORM( \
  BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_INIT_ARRAY_WRAP_, \
                            ~, \
  BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_TRY_BLOCK_ENABLE_( \
                                    id, tpl, k, f)) \
                    , BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS(f) \
                ) \
            ) \
        ) \
    ) \
    BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
            BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
                    BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01)), \
        /* constructor contracts */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CALL_BOOST_CONTRACT_DEF_ \
    , BOOST_PP_IIF(force_body, \
        /* no contracts but constructor try-blocks */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CALL_BODY_DEF_ \
    , \
        /* no contract and no try-blocks (eventually just constructor inits */ \
        BOOST_PP_TUPLE_EAT(5) \
    ))(id, tpl, k, f, body_func) \
    BOOST_PP_LIST_FOR_EACH(BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_CATCH_, ~, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(f))

#define BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF( \
        id, tpl, k, f, body_func, first_inits) \
    BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF_FORCE(id, tpl, k, f, \
            body_func, first_inits, BOOST_PP_LIST_IS_CONS( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(f)))

#define BOOST_CONTRACT_AUX_CODE_FUNC_NAMED_DECL(id, tpl, k, f, name, \
        access_level01, force_friend01, explicit01, force_inline01, \
        force_result_type01, param_defaults01) \
    BOOST_PP_IIF(access_level01, \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(f) \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(access_level01, BOOST_PP_COMPL( \
            BOOST_PP_IS_EMPTY(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_ACCESS( \
                    f)))), \
        : \
    ) \
    BOOST_PP_EXPR_IIF(force_friend01, friend) /* see also static below */ \
    BOOST_CONTRACT_AUX_CODE_TEMPLATE_DECL( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_IS_TEMPLATE(f), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f))) \
    BOOST_PP_IIF(explicit01, \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXPLICIT \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(f) \
    BOOST_PP_IIF(force_inline01, \
        inline \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_INLINE \
    )(f) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_EXTERN(f) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_STATIC(f) \
    /* friends contracted as static members (unless forcing friendship) */ \
    BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(force_friend01), \
            BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_FRIEND(f)))), \
        static \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VIRTUAL(f) \
    BOOST_CONTRACT_AUX_CODE_RESULT_TYPE(f, \
            BOOST_PP_COMPL(force_result_type01)) \
    name \
    ( \
        BOOST_PP_LIST_FOR_EACH_I( \
                BOOST_CONTRACT_AUX_CODE_FUNC_PARAM_DECL_ENUM_, \
                param_defaults01, \
                BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_POSITIONAL( \
                        BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f))) \
    ) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CONST(f) \
    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_VOLATILE(f)

#define BOOST_CONTRACT_AUX_CODE_FUNC_DECL(id, tpl, k, f, friend01, defaults01) \
    BOOST_CONTRACT_AUX_CODE_FUNC_NAMED_DECL( \
          id, tpl, k, f, \
  BOOST_CONTRACT_AUX_CODE_NAME(BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR( \
                f) \
        , BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f)) \
        , 1 /* with access level */ \
        , friend01 \
        , 1 /* with explicit */ \
          /* NOTE: force inline for free contracted func to avoid */ \
          /* duplicate def compiler error (this is same behaviour as for */ \
          /* member func automatically inlined when def in class decl, */ \
          /* which is always the case for contracted func) */ \
        , BOOST_PP_BITAND( \
              BOOST_PP_COMPL(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f)) \
            , BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                , BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
            ) \
          ) \
        , 0 /* no forced result type */ \
        , defaults01 /* with param defaults */ \
    )

#define BOOST_CONTRACT_AUX_CODE_FUNC_DEF(id, tpl, k, f, body_func) \
    /* the order of the following if-statement matter */ \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
        BOOST_CONTRACT_AUX_CODE_FUNC_CONSTRUCTOR_DEF_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_CONTRACT_AUX_CODE_FUNC_DESTRUCTOR_DEF_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_STATIC_MEMBER_FUNCTION( \
            k, f), \
        /* friend members are also contracted as static members */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_STATIC_MEMBER_DEF_ \
    , BOOST_PP_IIF( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(k, f),\
        BOOST_CONTRACT_AUX_CODE_FUNC_NONSTATIC_MEMBER_DEF_ \
    , \
        BOOST_CONTRACT_AUX_CODE_FUNC_FREE_DEF_ \
    ))))(id, tpl, k, f, body_func)

#endif // #include guard

