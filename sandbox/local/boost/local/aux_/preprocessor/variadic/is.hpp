
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_LOCAL_AUX_PP_IS_VARIADIC_HPP_
#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_HPP_

#include <boost/config.hpp>

#if !defined(BOOST_NO_VARIADIC_MACROS) // If no variadics then no macros.

#include "size.hpp"
#include "eat.hpp"
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
// `IS_UNARY` not working on Borland and other pp which have no variadic anyway.
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_NOT_UNARY1_(tokens) \
    BOOST_PP_COMPL(BOOST_PP_IS_UNARY(tokens))
    
#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_REMOVE1_(tokens) /* nothing */
        
// Tokens `(t1) t2`.
#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_SKIP1_(tokens) \
    BOOST_LOCAL_AUX_PP_IS_VARIADIC_NOT_UNARY1_( \
        BOOST_LOCAL_AUX_PP_IS_VARIADIC_REMOVE1_ tokens \
        (1) /* trailing unary handles empty */ \
    )

#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_NOT_UNARY2_(tokens) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(tokens), \
        BOOST_LOCAL_AUX_PP_IS_VARIADIC_SKIP1_ \
    , \
        1 /* it is not unary */ \
        BOOST_PP_TUPLE_EAT(1) \
    )(tokens)

#define BOOST_LOCAL_AUX_PP_IS_VARIADIC_(size, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(size, 1), \
        BOOST_LOCAL_AUX_PP_IS_VARIADIC_NOT_UNARY2_ \
    , /* size == 0 or size > 1 (it's variadic) */ \
        1 \
        BOOST_LOCAL_AUX_PP_VARIADIC_EAT \
    )(__VA_ARGS__)

// PUBLIC //

#define BOOST_LOCAL_AUX_PP_IS_VARIADIC(...) \
    BOOST_LOCAL_AUX_PP_IS_VARIADIC_( \
            BOOST_LOCAL_AUX_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

#endif // BOOST_NO_VARIADIC_MACROS

#endif // #include guard


