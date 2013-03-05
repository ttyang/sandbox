
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_HPP_

#include <boost/contract/aux_/macro/code_/named_params_func.hpp>
#include <boost/contract/aux_/macro/code_/signature.hpp>
#include <boost/contract/aux_/macro/code_/precondition.hpp>
#include <boost/contract/aux_/macro/code_/postcondition.hpp>
#include <boost/contract/aux_/macro/code_/oldof.hpp>
#include <boost/contract/aux_/macro/code_/func.hpp>
#include <boost/contract/aux_/macro/code_/body.hpp>
#include <boost/contract/aux_/macro/code_/final.hpp>
#include <boost/contract/aux_/macro/code_/virtual.hpp>
#include <boost/contract/aux_/macro/code_/subcontract.hpp>
#include <boost/contract/aux_/macro/code_/exception_spec.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_FUNCTION_POSTCONDITION_AND_OLDOF_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_POSTCONDITION(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_OLDOF(id, tpl, k, f)

#define BOOST_CONTRACT_AUX_FUNCTION_BODY_FORWARD_DECL_( \
        id, tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_CODE_BODY_DECL(id, tpl, k, f, body_func) \
    ; /* forward declaration (no definition here, will be def by user later) */

#define BOOST_CONTRACT_AUX_FUNCTION_OVERRIDE_AND_NEW_AND_FINAL_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_FINAL(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_OVERRIDE(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_NEW(id, tpl, k, f)

#define BOOST_CONTRACT_AUX_FUNCTION_VIRTUAL_SPECIFIERS_(id, tpl, k, f) \
    BOOST_PP_IIF( \
            BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_VIRTUAL_SPECIFIERS_01 \
                , BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                      ) \
                  ) \
            ), \
        BOOST_CONTRACT_AUX_CODE_VIRTUAL \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_VIRTUAL_SPECIFIERS_01, \
        BOOST_CONTRACT_AUX_FUNCTION_OVERRIDE_AND_NEW_AND_FINAL_ \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f)

#define BOOST_CONTRACT_AUX_CODE_FUNCTION_VIRTUAL_FINAL_AND_SUBBOOST_CONTRACT_( \
        id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_VIRTUAL_TAG(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_FINAL_TAG(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_SUBBOOST_CONTRACT_PREPOSTCONDITION_FROM_BASES( \
            id, tpl, k, f)

#define BOOST_CONTRACT_AUX_FUNCTION_FORWARD_DECL_(id, tpl, k, f) \
    BOOST_CONTRACT_AUX_CODE_FUNC_DECL(id, tpl, k, f \
        , 0 /* fwd decl never friend (only contracted func def) */ \
        , 1 /* with defaults */ \
    ) ; /* fwd decl `;` */

// Expand to 1 if the specific function kind has contracts enabled, 0 otherwise.
#define BOOST_CONTRACT_AUX_FUNCTION_HAS_BOOST_CONTRACT_(k, f) \
    /* order of this matters, start with free func */ \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FREE_FUNCTION(k, f), \
        BOOST_PP_BITOR( \
              BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
        ) \
    /* not free func then dtor, ctor, or (static or not) member func */ \
    , BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
        BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
    /* not free func or dtor then ctor or (static or not) member func */ \
    , \
        BOOST_PP_BITOR( \
              BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
            , BOOST_PP_BITOR( \
                  BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
            ) \
        ) \
    ))

#define BOOST_CONTRACT_AUX_FUNCTION_NEEDS_BODY_(k, f) \
    BOOST_PP_BITOR( \
        /* contracts are enabled for this function */ \
          BOOST_CONTRACT_AUX_FUNCTION_HAS_BOOST_CONTRACT_(k, f) \
        /* or, contracts off but (constructor) member initializers have */ \
        /* constructor-try blocks for its inits */ \
        /* POLICY: Function-try block only apply to exception */ \
        /* thrown by the body (see N1962) so they are */ \
        /* programmed outside the macros for functions and */ \
        /* destructor (so to have no extra body call overhead */ \
        /* when contracts are off); they need to be */ \
        /* programmed within the macros for constructor */ \
        /* because member initializers are programmed within */ \
        /* the macros constructor try blocks need to apply */ \
        /* to exception thrown by both the constructor body */ \
        /* and its initializers (so this library internally */ \
        /* disables constructor-try-block handlers when not */ \
        /* executing constructor initializers or body) */ \
        , BOOST_PP_LIST_IS_CONS( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(f)) \
    )
            
// PUBLIC //

#define BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BOOST_CONTRACT( \
        id, tpl, k, f, body_func) \
    /* NOTE: Some of these tpl is OR with IS_TEMPLATE so _TPL does */ \
    /* not have to (but it still can) be used with function templates */ \
    BOOST_PP_IIF( \
            BOOST_PP_BITAND( \
                  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_NONSTATIC_MEMBER_FUNCTION(\
                        k, f) \
                , BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_PP_BITOR( \
                          BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                        , BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
                    ) \
                ) \
            ), \
        /* NOTE: virtual specifiers (override, new, and final) are enabled */ \
        /* if and only if contract compilation is enabled because they */ \
        /* need to use the separation between body and contracted function */ \
        /* in order to program their static assertion check (necessary to */ \
        /* access actual template param type for function templates) */ \
        BOOST_CONTRACT_AUX_CODE_FUNCTION_VIRTUAL_FINAL_AND_SUBBOOST_CONTRACT_ \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        /* NOTE: non-members are fwd decl up here so pre and post can call */ \
        /* func itself (e.g., to recursively check factorial result) */ \
        BOOST_CONTRACT_AUX_FUNCTION_FORWARD_DECL_ \
    )(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_FUNCTION_HAS_BOOST_CONTRACT_(k, f), \
        BOOST_CONTRACT_AUX_CODE_SIGNATURE \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01, \
        BOOST_CONTRACT_AUX_CODE_PRECONDITION \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl /* don't force tpl for templates */, k, f) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01, \
        BOOST_CONTRACT_AUX_FUNCTION_POSTCONDITION_AND_OLDOF_ \
    , \
        BOOST_PP_TUPLE_EAT(4) \
    )(id, tpl /* don't force tpl for templates */, k, f)

#define BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BOOST_CONTRACTED_FUNC( \
        id, tpl, k, f, body_func) \
    BOOST_PP_IIF( \
            BOOST_PP_BITAND( \
                  BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_FREE_FUNCTION(k, f) \
                , BOOST_PP_BITOR( \
                      BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
                    , BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
                ) \
            ), \
        /* NOTE: Free func body needs to be forward declared so body func */ \
        /* ptr can be passed to the contract caller even if the actual */ \
        /* body func will be defined later by the user (this is not the */ \
        /* case for member func because within a class symbols are visible */ \
        /* regardless of their declaration order) */ \
        BOOST_CONTRACT_AUX_FUNCTION_BODY_FORWARD_DECL_ \
    , \
        BOOST_PP_TUPLE_EAT(5) \
    )(id, tpl, k, f, body_func) \
    /* actual func always decl (not matter if contracts or not) */ \
    BOOST_CONTRACT_AUX_CODE_FUNC_DECL(id, tpl, k, f \
        /* contracted function of a friend decl is the only part that */ \
        /* retains friendship (rest of contract is as for static member) */ \
        , BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
                BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_FRIEND(f))) \
        /* default params for members while for non-members defaults */ \
        /* already specified by fwd decl above */ \
        , BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_MEMBER(k, f) \
    ) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_FUNCTION_NEEDS_BODY_(k, f), \
        /* def calls body */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_DEF \
    , BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS( \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_INITIALIZERS(f)), \
        /* def init members (ctor only) and possibly calls body */ \
        BOOST_CONTRACT_AUX_CODE_FUNC_DEF \
    , \
        BOOST_PP_TUPLE_EAT(5) \
    ))(id, tpl /* don't force tpl for template */, k, f, body_func)

#define BOOST_CONTRACT_AUX_FUNCTION_BODY_FUNC(k, f) \
    BOOST_CONTRACT_AUX_CODE_NAME_POSTFIXED( \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_CONSTRUCTOR(k), \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_IS_DESTRUCTOR(k), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_OPERATOR(f), \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_NAME(f), \
            (body))

// Named parameters need to force body even if all contracts off.
#define BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BODY_DECL_FORCE( \
        id, tpl, k, f, body_func, force_body) \
    BOOST_PP_IIF(force_body, \
        BOOST_CONTRACT_AUX_CODE_BODY_DECL \
    , \
        BOOST_PP_TUPLE_EAT(5) \
    )(id, tpl, k, f, body_func) \
    /* POLICY: Exception spec only apply to exceptions thrown by the body */ \
    /* and not to exceptions thrown by contract handlers (if they are */ \
    /* redefined to throw) or by this library implementation code */ \
    BOOST_CONTRACT_AUX_CODE_EXCEPTION_SPEC(id, tpl, k, f) \
    /* user's function definition { ... } (and try-blocks) follows here */

#define BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BODY_DECL( \
        id, tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BODY_DECL_FORCE(id, tpl, k, \
            f, body_func, BOOST_CONTRACT_AUX_FUNCTION_NEEDS_BODY_(k, f))

#define BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS( \
        id, tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BOOST_CONTRACT(id, tpl, k, \
            f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BOOST_CONTRACTED_FUNC(id, \
            tpl, k, f, body_func) \
    BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS_BODY_DECL(id, tpl, k, f, \
            body_func)

#define BOOST_CONTRACT_AUX_FUNCTION(id, tpl, k, f) \
    BOOST_PP_IIF(BOOST_PP_LIST_IS_CONS(BOOST_PP_LIST_APPEND( \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_NAMED( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)), \
            BOOST_CONTRACT_DETAIL_PP_PARAMS_TRAITS_DEDUCED( \
                    BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS_PARAMS(f)))), \
        BOOST_CONTRACT_AUX_CODE_NAMED_PARAMS_FUNC \
    , \
        BOOST_CONTRACT_AUX_FUNCTION_POSITIONAL_PARAMS \
    )(id, tpl, k, f, BOOST_CONTRACT_AUX_FUNCTION_BODY_FUNC(k, f))

#endif // #include guard

