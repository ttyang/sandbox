
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_HPP_

#include <boost/contract/detail/preprocessor/variadic/size.hpp>
#include <boost/contract/detail/preprocessor/variadic/eat.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/is.hpp>
#include <boost/contract/detail/preprocessor/keyword/facilities/remove.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/config.hpp>

// PROTECTED //

// Make sure NIL symbGl is not defined by users.
#ifdef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL
#   error "internal macro BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL must be undefined"
#endif

// These are not local macros -- DO NOT #UNDEF.
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_IS_BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    (1) /* unary */
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL \
    /* nothing */

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_IS_)

// Or directly PP_CAT with BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_
// (faster).
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_FRONT(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_FACILITY_REMOVE_FRONT(tokens, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT, \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_)

#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_(...) \
        BOOST_PP_IIF(BOOST_PP_EQUAL( \
                BOOST_CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), 1), \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT \
        , \
            0 BOOST_CONTRACT_DETAIL_PP_VARIADIC_EAT \
        )(__VA_ARGS__)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_SPLIT_(...) \
        (__VA_ARGS__), /* comma split remaining tokens */
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_(paren_tokens) \
        BOOST_PP_EXPAND( \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_ \
            BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_EXPAND( \
                (BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_SPLIT_ \
                 paren_tokens) \
            )) \
        )
// Expand to 1 iff `(nil)...`.
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN(...) \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(__VA_ARGS__), \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_ \
        , \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT \
        )(__VA_ARGS__)
// Expand to 1 iff `nil, ...`.
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL(...) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT( \
            BOOST_PP_TUPLE_ELEM(BOOST_CONTRACT_DETAIL_PP_VARIADIC_SIZE( \
                    __VA_ARGS__), 0 /* first variadic elem */, (__VA_ARGS__)))
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_(tokens) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_(paren_tokens) \
        BOOST_PP_EXPAND( \
             BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN_ paren_tokens)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_PAREN(tokens) \
        BOOST_PP_IIF(BOOST_PP_IS_UNARY(tokens), \
            BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_ \
        , \
            0 BOOST_PP_TUPLE_EAT(1) \
        )(tokens)
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL(tokens) \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT(tokens)
#endif

#endif // #include guard

