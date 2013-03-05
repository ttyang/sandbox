
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_HPP_
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_HPP_

#include <boost/contract/detail/preprocessor/tuple/split.hpp>

// PRIVATE //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_(size_tuple_rest) \
    (BOOST_PP_TUPLE_ELEM(3, 0, size_tuple_rest), \
            BOOST_PP_TUPLE_ELEM(3, 1, size_tuple_rest))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_(size_tuple_rest) \
    BOOST_PP_TUPLE_ELEM(3, 2, size_tuple_rest)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_SPLIT_(size) \
    size, BOOST_CONTRACT_DETAIL_PP_TUPLE_SPLIT(size) /* split */

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_comma(comma_count) \
    /* tuple size is number of commas + 1 */ \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_SPLIT_(BOOST_PP_INC(comma_count))
    
// tokens: `comma(n) (token0, ..., token_n) ...`
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_ \
    )((BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_, tokens)))
    
#ifndef BOOST_NO_VARIADIC_MACROS
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_(...) \
        BOOST_CONTRACT_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), (__VA_ARGS__) \
        , /* comma splits */
#else
#   define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_(token) \
        1, (token), /* comma splits */
#endif

// tokens: `(token0, ...) ...`
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_AFTER_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ARRAY_ \
    )((BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_SPLIT_ tokens))
        
#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_AFTER_(rest) \
    rest

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ARRAY_(token) \
    /* training EMPTY() so MSVC properly handle when token is empty */ \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(token BOOST_PP_EMPTY()), \
        (0, ()) /* 0-size array for empty */ \
    , \
        (1, (token)) \
    )

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(after01, \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_AFTER_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ARRAY_ \
    )(no_comma_macro(tokens))

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
        after01, no_comma_macro, tokens) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_COMMA_FRONT(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_PAREN_ \
    , \
        BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_NOT_ \
    ))(after01, no_comma_macro, tokens)

// PROTECTED //

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA(no_comma_macro, tokens) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
            0 /* array, not after */, no_comma_macro, tokens)

#define BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_COMMA( \
        no_comma_macro, tokens) \
    BOOST_CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA_DISPATCH_( \
            1 /* after */, no_comma_macro, tokens)

#endif // #include guard

