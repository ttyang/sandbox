
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/*************************************************************/
/* WARNING:  FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT! */
/* Instead modify the generation script "<FILE>-generate.py" */
/*************************************************************/
// Used maximum number of iterations: 1

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_1_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_1_HPP_

#include <boost/contract/aux_/config.hpp>
#include <boost/contract/detail/preprocessor/punctuation/has_paren.hpp>
#include <boost/contract/detail/preprocessor/keyword/default.hpp>
#include <boost/contract/detail/preprocessor/keyword/void.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/seq/fold_right.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/config.hpp>

// PRIVATE //

#define CHECK_BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_1 (1)
#define ERASE_BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_1 \
    /* nothing */

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_CHECK_1_( \
        tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT \
    )(tokens, CHECK_)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_ERASE_1_( \
        tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_CHECK_1_, \
            ERASE_)

// From PP_EXPAND (my own reentrant version).
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && \
        ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_1_(x) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_I_1_(x)
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_1_(x) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_OO_1_((x))
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_OO_1_(par) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_I_1_ ## par
#endif
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_I_1_(x) x

#define \
BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_LASTDFLT_1_( \
        s, elem, list, last_default, elem_macro) \
    ( \
        list /* unchanged list */ \
    , \
        /* set last-default */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_DEFAULT_REMOVE_FRONT(elem)) \
    , \
        elem_macro /* unchanged op-macro */ \
    ) \

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_ELEM_1_( \
        s, elem, list, last_default, elem_macro) \
    ( \
        /* append elem_macro(elem) (in front because FOLD_RIGHT) */ \
        BOOST_PP_LIST_APPEND( \
            ( /* list of... */ \
                ( /* .. 2-tuple `(elem_macro(elem), default)` */ \
                    elem_macro(elem) \
                , \
                    last_default \
                ) \
            , BOOST_PP_NIL ), list) \
    , \
        (0, ()) /* no last-default */ \
    , \
        elem_macro /* unchanged op-macro */ \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_1_( \
        s, list_lastdefault_macro, elem) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(elem), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_LASTDFLT_1_\
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_ELEM_1_ \
    )(s, elem, \
            BOOST_PP_TUPLE_ELEM(3, 0, list_lastdefault_macro), \
            BOOST_PP_TUPLE_ELEM(3, 1, list_lastdefault_macro), \
            BOOST_PP_TUPLE_ELEM(3, 2, list_lastdefault_macro))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_1_( \
        seq, elem_macro) \
    BOOST_PP_TUPLE_ELEM( \
          3 \
        , 0 \
        , BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_1_( \
            BOOST_PP_SEQ_FOLD_RIGHT( \
  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_OP_1_ \
                , ( \
                      BOOST_PP_NIL
                    , (0, ()) /* no last-default to start */ \
                    , elem_macro \
                  ) \
                  , seq \
            ) \
         ) \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_OP_ELEM_1_( \
        s, elem, list, elem_macro) \
    ( \
        BOOST_PP_LIST_APPEND( \
            ( /* list of 1-tuple `elem_macro(elem)` */ \
                elem_macro(elem) \
            , BOOST_PP_NIL ), list) \
    , \
        elem_macro /* unchanged op-macro */ \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_OP_1_( \
        s, list_macro, elem) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_OP_ELEM_1_( \
            s, elem, \
            BOOST_PP_TUPLE_ELEM(2, 0, list_macro), \
            BOOST_PP_TUPLE_ELEM(2, 1, list_macro))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_1_( \
        seq, elem_macro) \
    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_SEQ_FOLD_RIGHT( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_OP_1_, \
            ( BOOST_PP_NIL, elem_macro ), seq))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NOTEMPTY_1_( \
        seq, allow_empty, with_defaults, elem_macro) \
    BOOST_PP_IIF(with_defaults, \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_DFLT_1_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NODFLT_1_ \
    )(seq, elem_macro)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_EMPTY_1_( \
        seq, allow_empty, with_defaults, elem_macro) \
    BOOST_PP_IIF(allow_empty, \
        BOOST_PP_NIL /* nil list */ \
        BOOST_PP_TUPLE_EAT(2) /* no error */ \
    , \
        BOOST_PP_ASSERT_MSG /* error */ \
    )(0, ERROR_unexpected_empty_token_list)

#define \
BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_CHECK_HEAD_1_( \
        seq) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT(BOOST_PP_SEQ_HEAD(seq))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_CHECK_1_( \
        seq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(seq), 1), \
  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_CHECK_HEAD_1_ \
    , \
        0 BOOST_PP_TUPLE_EAT(1) \
    )(seq)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_1_( \
        void_or_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT(void_or_seq), \
        1 BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_CHECK_1_ \
    )(void_or_seq)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_1_( \
        void_or_seq, allow_empty, with_defaults, elem_macro) \
    BOOST_PP_IIF(BOOST_PP_EXPAND( /* expand for MSVC */ \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_IS_EMPTY_1_( \
                    void_or_seq)), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_EMPTY_1_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_NOTEMPTY_1_ \
    )(void_or_seq, allow_empty, with_defaults, elem_macro)

#ifndef BOOST_NO_VARIADIC_MACROS
#   include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_SPLIT_SEQ_1_(...) \
        BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ(void, __VA_ARGS__) \
        , /* split into 2-tuple `(seq_from(__VA_ARGS__), following_tokens)` */
#else // variadics
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_SPLIT_SEQ_1_(seq) \
        seq \
        , /* split into 2-tuple `(seq_from(__VA_ARGS__), following_tokens)` */
#endif // variadics

// Expand from paren_tokens `(a, b, ...) tokens...` (variadics) or
// `( (a) (b) ... ) tokens...` to `(a) (b) ...`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_GET_SEQ_1_(paren_tokens) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
        ( /* split expand to 2-tuple `(seq, ignore_tokens)` */ \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_SPLIT_SEQ_1_ \
            paren_tokens \
        ) \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_1_( \
        tokens, allow_empty, with_defaults, remove_tag_macro, elem_macro) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_1_( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_GET_SEQ_1_( \
            remove_tag_macro(tokens)), \
            allow_empty, with_defaults, elem_macro)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_1(tokens, \
        allow_empty, with_defaults, \
        is_tagged_macro, remove_tag_macro, elem_macro) \
    BOOST_PP_IIF(is_tagged_macro(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_1_ \
    , \
        BOOST_PP_NIL /* nil list */ \
        BOOST_PP_TUPLE_EAT(5) \
    )(tokens, allow_empty, with_defaults, remove_tag_macro, elem_macro)

#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_1(...) \
        /* nothing */
#else // variadics
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_1(seq) \
        /* nothing */
#endif // variadics

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TAGGED_LIST_1( \
        tokens, is_tagged_macro, removing_prefix) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            is_tagged_macro, removing_prefix)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_1(tokens, \
        allow_empty, with_defaults, elem_macro) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_FROM_SEQ_1_( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_GET_SEQ_1_(tokens), \
            allow_empty, with_defaults, elem_macro)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_LIST_1(tokens) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_ERASE_1_( \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_EXPAND_1_( \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TAGGED_LIST_REMOVE_1 tokens \
    ))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_OPTIONAL_LIST_1( \
        tokens, allow_empty, with_defaults, elem_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_LIST_1 /* list present */ \
    , \
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(4) /* expand to nil pp-list */ \
    )(tokens, allow_empty, with_defaults, elem_macro)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_OPTIONAL_LIST_1(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_LIST_1 /* list present */ \
    , \
        tokens BOOST_PP_TUPLE_EAT(1) /* expand to tokens */ \
    )(tokens)

#endif // #include guard

