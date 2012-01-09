
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_HPP_
#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_HPP_

#include <boost/config.hpp>

#if !defined(BOOST_NO_VARIADIC_MACROS) // If no variadics then no macros.

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/tuple/eat.hpp> // For PP_EAT.
// `IS_UNARY` not working on Borland and other pp which have no variadic anyway.
#include <boost/preprocessor/detail/is_unary.hpp>

// PRIVATE //

#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_1OR0_TOKEN_(maybe_empty) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(maybe_empty (/*exapnd empty */) ), 0, 1)

#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_1OR0_(maybe_empty) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(maybe_empty (/*exapnd empty */) ), \
        1 BOOST_PP_EAT \
    , \
        BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_1OR0_TOKEN_ \
    )(maybe_empty)

#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_(size, ...) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(size, 1), \
        BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_1OR0_ \
    , \
        size BOOST_PP_EAT \
    )(__VA_ARGS__ BOOST_PP_EMPTY)

// PUBLIC //

// Expand () to 0 (differently from BOOST_PP_VARIADIC_SIZE() that expand to 1).
#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE(...) \
    BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE_(BOOST_PP_VARIADIC_SIZE( \
            __VA_ARGS__), __VA_ARGS__)

#endif // BOOST_NO_VARIADIC_MACROS

#endif // #include guard

