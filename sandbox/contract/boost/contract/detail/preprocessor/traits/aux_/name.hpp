
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_HPP_

#include <boost/contract/detail/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <boost/contract/detail/preprocessor/facilities/is_digit.hpp>
#include <boost/contract/detail/preprocessor/keyword/boost/contract/comma.hpp>
#include <boost/contract/detail/preprocessor/keyword/new.hpp>
#include <boost/contract/detail/preprocessor/keyword/delete.hpp>
#include <boost/contract/detail/preprocessor/keyword/operator.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

// PRIVATE //

#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_SPLIT_( \
            ...) \
        BOOST_PP_TUPLE_ELEM( \
                BOOST_CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), 0, \
                (__VA_ARGS__)) , /* split */
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_SPLIT_( \
            seq) \
        seq , /* split */
#endif

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_2ND_(tokens)\
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_IS_DIGIT(BOOST_PP_TUPLE_ELEM(2, 0, \
            BOOST_PP_EXPAND(( \
  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_SPLIT_ \
                BOOST_CONTRACT_DETAIL_PP_KEYWORD_COMMA_REMOVE_FRONT(tokens) \
            )))), \
        0 /* e.g., `operator comam(1)(std::map<int, char>)` */ \
    , \
        1 /* e.g., `operator comma ( ((int&) i) (int const j) )` */ \
    )

// Is comma operator `operator comma ( int i, int j )` (and not comma in macro
// `operator comma(1)(std::map<int, char>) ( void )`).
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_(tokens) \
    BOOST_PP_EXPAND( /* EXPAND for MSVC */ \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_2ND_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) /* not `operator comma ...` */ \
        )(tokens) \
    )

// Function name (not an operator): `(f) ( int i, int j)`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_(tokens) \
    ( /* operator tokens (0-size array if not an operator) */ \
        (0, ()) \
    , /* alphanumeric name */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME(tokens) \
    )

// Symbolic operator: `operator(==)(equal)` and also commas in macros
// `operator comma(1)(std::map<int, char>)(std_map)`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_SYMBOL_(tokens) \
    ( /* operator tokens (0-size array if not an operator) */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(BOOST_PP_TUPLE_REM(1), \
                tokens) \
    , /* alphanumeric name */ \
        BOOST_PP_SEQ_HEAD(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_COMMA( \
                BOOST_PP_TUPLE_REM(1), tokens)) \
    )
        
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_SYMBOL_OP_( \
        tokens) \
    /* skips after symbol and eats name `(symbol)(name)` */\
    BOOST_PP_TUPLE_EAT(1) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_COMMA(BOOST_PP_TUPLE_REM(1), \
            tokens)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_SYMBOL_(tokens)\
    BOOST_PP_EXPAND( /* extra OP and EXPAND macros needed for MSVC */ \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_SYMBOL_OP_(\
                    tokens))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_SEQ_UNWRAP_( \
        r, unused, type_bit) \
    type_bit /* remove seq paren */

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_SEQ_(seq) \
    ( /* operator tokens (0-size array if not an operator) */ \
        (1, (BOOST_PP_SEQ_FOR_EACH( \
  BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_SEQ_UNWRAP_, \
                ~, seq))) \
    , /* alphanumeric name */ \
        BOOST_PP_SEQ_CAT(seq) \
    )

// Keyword operator: `operator int const ( vooid )`, `operator new`.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_(tokens) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_SEQ_( \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NEW_FRONT(tokens), \
            (new) BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DELETE_FRONT( \
                tokens), \
            (delete) BOOST_PP_TUPLE_EAT(1) \
        , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens),\
            (comma) BOOST_PP_TUPLE_EAT(1) \
        , \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_SEQ \
        )))(tokens) \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_KEYWORD_( \
        tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_NEW_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_NEW_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_DELETE_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_DELETE_REMOVE_FRONT \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_KEYWORD_COMMA_REMOVE_FRONT \
    , /* operator type */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE \
    )))(tokens)

// Dispatch operator parsing.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_(tokens) \
    /* the order of these if-statements matter */ \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_( \
            tokens), \
        /* comma operator `operator comma ( int i, int j )` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
        /* comma in macors `operator comma(1)(map<int, char)(map) ( void )` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_SYMBOL_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        /* symbolic operator `operator(==)(equal)` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_SYMBOL_ \
    , \
        /* keyword operator `operator new`, `operator int const` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_KEYWORD_ \
    )))(tokens)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_(tokens) \
    /* the order of these if-statements matter */ \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_IS_COMMA_OPERATOR_( \
            tokens), \
        /* comma operator `operator comma ( int i, int j )` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_KEYWORD_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
        /* comma in macors `operator comma(1)(map<int, char)(map) ( void )` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_SYMBOL_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        /* symbolic operator `operator(==)(equal)` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_SYMBOL_ \
    , \
        /* keyword operator `operator new`, `operator int const` */ \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_KEYWORD_ \
    )))(tokens)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_SPLIT_(tokens) \
    tokens , /* slits into 2-tuple `(tokens, following_tokens)` */

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME(tokens) \
    BOOST_PP_TUPLE_ELEM(2, 0, \
            (BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_SPLIT_ tokens) )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME(tokens) \
    BOOST_PP_TUPLE_ELEM(2, 1, \
            (BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_SPLIT_ tokens) )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_WITH_OPERATOR(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_OPERATOR_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NAME_ \
    )(BOOST_CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_WITH_OPERATOR(tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_OPERATOR_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME_OPERATOR_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_NAME \
    )(BOOST_CONTRACT_DETAIL_PP_KEYWORD_OPERATOR_REMOVE_FRONT(tokens))

#endif // #include guard

