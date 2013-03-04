
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_AUX_CODE_ASSERT_HPP_
#define BOOST_CONTRACT_AUX_CODE_ASSERT_HPP_

#include <boost/contract/broken.hpp>
#include <boost/contract/detail/preprocessor/traits/assertion.hpp> // a
#include <boost/contract/detail/preprocessor/traits/static_assert.hpp>
#include <boost/contract/detail/preprocessor/traits/const_expr.hpp>
#include <boost/contract/detail/preprocessor/punctuation/curly.hpp>
#include <boost/contract/detail/preprocessor/keyword/const.hpp>
#include <boost/contract/detail/preprocessor/keyword/if.hpp>
#include <boost/contract/detail/preprocessor/keyword/else.hpp>
#include <boost/contract/detail/preprocessor/keyword/static.hpp>
#include <boost/preprocessor/selection/max.hpp>
#include <boost/preprocessor/stringize.hpp>

// PRIVATE //

#define BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, const_tokens, assertion_token) \
    (( \
        /* the pp-list size or 1 (for just assertion_token) is size is 0 */ \
        BOOST_PP_MAX(1, BOOST_PP_LIST_SIZE(const_tokens)) \
    , ( \
        BOOST_PP_LIST_ENUM(const_tokens) \
        assertion_token \
    )))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_STATEMENT_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, \
            BOOST_PP_NIL, /* no const tokens */ \
            /* following trailing `;` ends statement */ \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a) ; )

#define BOOST_CONTRACT_AUX_CODE_ASSERT_IF_CONDITION_FUNC_(id, number) \
    BOOST_CONTRACT_AUX_SYMBOL( (select_assertion_if)(id)(number) )

#define BOOST_CONTRACT_AUX_CODE_ASSERT_IF_CONDITION_(d, id, tpl, a, \
        underscored_name, if_condition) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d \
        /* expand to empty list if condition is not `const ...` */ \
        , BOOST_CONTRACT_AUX_CODE_CONST_EXPR_TOKENS(id, tpl, bool, \
                BOOST_CONTRACT_AUX_CODE_ASSERT_IF_CONDITION_FUNC_(id, \
                        BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)), \
                if_condition) \
        , /* actual code to start if-block */ \
            if( \
                BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT( \
                        if_condition), \
                    /* call local func def by tokens above */ \
                    BOOST_CONTRACT_AUX_CODE_ASSERT_IF_CONDITION_FUNC_(id, \
                            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER( \
                                    a)) \
                            () /* parenthesis call if-condition local func */ \
                , \
                    if_condition /* just the condition (not const) */ \
                ) \
            ) { /* left-curly starts select assertion if block */ \
    )

#define BOOST_CONTRACT_AUX_CODE_ASSERT_IF_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_IF_CONDITION_(d, id, tpl, a, \
            underscored_name, \
            /* extract condition from `if( condition )` */ \
            BOOST_PP_TUPLE_ELEM(1, 0, \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IF_REMOVE_FRONT( \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a))))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_FUNC_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, \
            BOOST_PP_NIL, /* no const tokens */ \
            assertion_func_call_macro(d, id, tpl, data, a))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_STATIC_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, \
            BOOST_PP_NIL, /* no const tokens */ \
            BOOST_CONTRACT_AUX_CODE_ASSERT_STATIC(id, tpl, a, underscored_name))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_LOCAL_FUNC_(id, number) \
    BOOST_CONTRACT_AUX_SYMBOL( (const_assertion)(id)(number) )

#define BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, \
            BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_DEF_TOKENS(id, tpl, a, \
                    underscored_name), \
            BOOST_CONTRACT_AUX_CODE_ASSERT_CONST(id, tpl, a, \
                    underscored_name))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_BOOL_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_DEF_(d, \
            BOOST_PP_NIL, /* no const tokens */ \
            BOOST_CONTRACT_AUX_CODE_ASSERT_BOOL(id, tpl, a, underscored_name))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_(d, id, tpl, a, \
        underscored_name, assertion_func_call_macro, data) \
    /* NOTE: The order of this if conditions matters */ \
    BOOST_PP_IIF(BOOST_PP_EXPAND( /* EXPAND for MSVC */ \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_IS_STATEMENT(a)), \
        BOOST_CONTRACT_AUX_CODE_ASSERT_STATEMENT_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_IF_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
        BOOST_CONTRACT_AUX_CODE_ASSERT_IF_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_ELSE_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
        /* select assertion else block (with its left-curly) */ \
        ((1, ( else { ))) BOOST_PP_TUPLE_EAT(7) \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_IS_RCURLY_MACRO( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
        /* right-curly ends select assertion if and/or else blocks */ \
        ((1, ( } ))) BOOST_PP_TUPLE_EAT(7) \
    , BOOST_PP_IIF(BOOST_PP_COMPL(BOOST_PP_IS_EMPTY( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_REQUIREMENT(a))), \
        BOOST_CONTRACT_AUX_CODE_ASSERT_FUNC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_STATIC_ASSERT_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
        BOOST_CONTRACT_AUX_CODE_ASSERT_STATIC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a)), \
        BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_ \
    , \
        BOOST_CONTRACT_AUX_CODE_ASSERT_BOOL_ \
    )))))))(d, id, tpl, a, underscored_name, assertion_func_call_macro, data)

#define BOOST_CONTRACT_AUX_CODE_ASSERT_TUPLE_( \
        d, id_tpl_name_call_data_code, a) \
    ( \
        BOOST_PP_TUPLE_ELEM(6, 0, id_tpl_name_call_data_code) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 1, id_tpl_name_call_data_code) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 2, id_tpl_name_call_data_code) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 3, id_tpl_name_call_data_code) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 4, id_tpl_name_call_data_code) \
    , \
        BOOST_PP_TUPLE_ELEM(6, 5, id_tpl_name_call_data_code) \
        /* seq append */ \
        BOOST_CONTRACT_AUX_CODE_ASSERT_( \
              d \
            , BOOST_PP_TUPLE_ELEM(6, 0, id_tpl_name_call_data_code) \
            , BOOST_PP_TUPLE_ELEM(6, 1, id_tpl_name_call_data_code) \
            , a \
            , BOOST_PP_TUPLE_ELEM(6, 2, id_tpl_name_call_data_code) \
            , BOOST_PP_TUPLE_ELEM(6, 3, id_tpl_name_call_data_code) \
            , BOOST_PP_TUPLE_ELEM(6, 4, id_tpl_name_call_data_code) \
        ) \
    )

#define BOOST_CONTRACT_AUX_CODE_ASSERT_FROM_ARRAY_(r, unused, code_array) \
    BOOST_PP_LIST_ENUM_R(r, BOOST_PP_TUPLE_TO_LIST( \
            BOOST_PP_ARRAY_SIZE(code_array), BOOST_PP_ARRAY_DATA(code_array)))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_FROM_SEQ_(code_seq) \
    BOOST_PP_SEQ_FOR_EACH(BOOST_CONTRACT_AUX_CODE_ASSERT_FROM_ARRAY_, ~, \
            BOOST_PP_SEQ_TAIL(code_seq))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_GET_(code_seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(code_seq), 1), \
        BOOST_PP_TUPLE_EAT(1) /* no assertion func definition code */ \
    , \
        BOOST_CONTRACT_AUX_CODE_ASSERT_FROM_SEQ_ \
    )(code_seq)

// PUBLIC //

// NOTE: underscored_name is kept for all these macros if it is actually only
// used by static assertion (it can be used with number as unique ID if needed).

#define BOOST_CONTRACT_AUX_CODE_ASSERT_CONDITION( \
        condition, underscored_name, number, print_code) \
    if(!(condition)) { /* no bool conversion, use more general operator! */ \
        throw ::contract::broken(__FILE__, __LINE__, \
                BOOST_PP_STRINGIZE(print_code), /* print assertion code */ \
                number); \
    }

#define BOOST_CONTRACT_AUX_CODE_ASSERT_BOOL(id, tpl, a, underscored_name) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_CONDITION( \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a), \
            underscored_name, \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a), \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_DEF_TOKENS( \
        id, tpl, a, underscored_name) \
    BOOST_CONTRACT_AUX_CODE_CONST_EXPR_TOKENS( \
            /* unique symbol using both id and number to avoid name clashes */ \
            BOOST_PP_SEQ_CAT( (id)(BOOST_CONTRACT_AUX_SYMBOL_INFIX) \
                    (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) ), \
            tpl, bool, \
            BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_LOCAL_FUNC_(id, \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)), \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_CONST(id, tpl, a, underscored_name) \
    BOOST_CONTRACT_AUX_CODE_ASSERT_CONDITION( \
            BOOST_CONTRACT_AUX_CODE_ASSERT_CONST_LOCAL_FUNC_(id, \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) \
                    () /* parenthesis to call local function */, \
            underscored_name, \
            BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a), \
            BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_EXPR( \
                    BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS( \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a))))

#define BOOST_CONTRACT_AUX_CODE_ASSERT_STATIC(id, tpl, a, underscored_name) \
    { \
        /* within a block {} to avoid name clashes when expanding multiple */ \
        /* MPL_ASSERT on same line (i.e., from same contract macro) */ \
        BOOST_CONTRACT_AUX_MPL_ASSERT_MSG( \
              BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS_CONDITION( \
                    BOOST_CONTRACT_DETAIL_PP_STATIC_ASSERT_TRAITS( \
                    BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_INSTRUCTION(a))) \
            , BOOST_PP_SEQ_CAT((ERROR_statically_checked_)\
                    (underscored_name)(_number_) \
                    (BOOST_CONTRACT_DETAIL_PP_ASSERTION_TRAITS_NUMBER(a)) \
                    (_failed_at_line_)(id)) \
            /* ideally, I'd print the static assertion message msg here */ \
            /* but a string cannot be printed as a type in C++03... */ \
            , () \
        ); /* MPL assert requires trailing `;` */ \
    }

// Where `assertion_func_call_macro(d, id, tpl, data, a)` expands to
// assertion function call (single token, func call can be wrapped within ()).
#define BOOST_CONTRACT_AUX_CODE_ASSERT(id, tpl, underscored_name, \
        assertion_func_call_macro, data, assertions) \
    /* can't use LIST_FOR_EACH here instead of FOLD_LEFT because it doesn't */ \
    /* reenter correctly on MSVC (not even if FOR_EACH_R is used) because */ \
    /* many of the alg used to expand the assert func also use LIST_FOR_EACH */\
    BOOST_CONTRACT_AUX_CODE_ASSERT_GET_(BOOST_PP_TUPLE_ELEM(6, 5, \
            BOOST_PP_LIST_FOLD_LEFT(BOOST_CONTRACT_AUX_CODE_ASSERT_TUPLE_, \
                    ( id, tpl, underscored_name, \
                      /* code in seq of array to handle unwrapped commas */ \
                      assertion_func_call_macro, data, ((1, (;))) ), \
                    assertions)))

#endif // #include guard

