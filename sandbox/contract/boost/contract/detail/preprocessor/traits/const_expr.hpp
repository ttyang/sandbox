
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/detail/preprocessor/keyword/void.hpp>
#include <boost/contract/detail/preprocessor/keyword/const.hpp>
#include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/config.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VAR_(d, vars, var) \
    BOOST_PP_LIST_APPEND(vars, \
        ( \
            ( \
                BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* could be empty */ \
                BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE(var) \
            , \
                BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE(var) \
            ) \
        , \
            BOOST_PP_NIL \
        ) \
    )

// Precondition: size(seq) == 1
#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_SEQ_IS_EMPTY_HEAD_( \
        vars_seq) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT(BOOST_PP_BOOST_PP_SEQ_HEAD( \
            seq))

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_SEQ_IS_EMPTY_( \
        vars_seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(1, BOOST_PP_SEQ_SIZE(vars_seq)), \
        BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_SEQ_IS_EMPTY_HEAD_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(vars_seq)

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_FROM_SEQ_(vars_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_SEQ_IS_EMPTY_(\
            vars_seq), \
        BOOST_PP_NIL /* empty list */ BOOST_PP_TUPLE_EAT(3) \
    , \
        BOOST_PP_SEQ_FOLD_LEFT \
    )(BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VAR_, BOOST_PP_NIL, vars_seq)

#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_SPLIT_(...) \
        BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ(void, __VA_ARGS__) \
        , /* comma to split */
#else
#   define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_SPLIT_(seq) \
        seq, /* comma to split */
#endif

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_(varseq_instruction) \
    ( /* const expr traits is 2-tuple `(vars, instruction)` */ \
        BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS_FROM_SEQ_( \
                BOOST_PP_TUPLE_ELEM(2, 0, varseq_instruction)) \
    , \
        BOOST_PP_TUPLE_ELEM(2, 1, varseq_instruction) \
    )

// PUBLIC //

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS(const_expr) \
    BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_(BOOST_PP_EXPAND( ( \
        BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_SPLIT_ \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT(const_expr) \
    ) ))

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_EXPR(traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, traits)

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_TRAITS_VARS(traits) \
    BOOST_PP_TUPLE_ELEM(2, 0, traits)

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_TYPE(var_traits) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \
            BOOST_PP_TUPLE_ELEM(2, 0, var_traits))

#define BOOST_CONTRACT_DETAIL_PP_CONST_EXPR_VAR_TRAITS_NAME(var_traits) \
    BOOST_PP_TUPLE_ELEM(2, 1, var_traits)

#endif // #include guard

