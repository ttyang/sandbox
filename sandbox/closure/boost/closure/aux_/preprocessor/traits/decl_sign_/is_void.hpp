
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_HPP_
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_HPP_

#include <boost/closure/config.hpp>
#include <boost/closure/detail/preprocessor/keyword/void.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/seq/seq.hpp> // For `SEQ_HEAD`.

// PRIVATE //

#if defined(BOOST_CLOSURE_CONFIG_COMPLIANT)
#   define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_ALLOW_EMPTY_ 0
#else
#   define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_ALLOW_EMPTY_ 1
#endif

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_(sign) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(sign), \
        /* handles empty params `()` as no params (C99 only) */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_ALLOW_EMPTY_ \
        BOOST_PP_EMPTY \
    , \
        BOOST_CLOSURE_DETAIL_PP_KEYWORD_IS_VOID_FRONT \
    )(sign)

#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_SEQ_(sign) \
    BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_(BOOST_PP_SEQ_HEAD( \
            sign))

// PUBLIC //

// Check is specified parenthesized sign empty (or void) list.
// Expand to 1 iff sign is empty (C99 only), or `void` (supported also
// for C++ but similar to unparenthesized sign syntax for C99), or `(void)`
// (parenthesized sign syntax for C++).
#define BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID(sign) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(sign), \
        /* it's a pp-seq */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_SEQ_ \
    , /* else, it's a token */ \
        BOOST_CLOSURE_AUX_PP_DECL_TRAITS_SIGN_IS_VOID_TOKEN_ \
    )(sign)

#endif // #include guard

