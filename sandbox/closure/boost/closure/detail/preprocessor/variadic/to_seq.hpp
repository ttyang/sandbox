
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ_HPP_
#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ_HPP_

#include <boost/config.hpp>

#if !defined(BOOST_NO_VARIADIC_MACROS) // If no variadics then no macros.

#include <boost/closure/detail/preprocessor/variadic/is.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/tuple/rem.hpp> // For PP_REM.
#include <boost/preprocessor/tuple/eat.hpp> // For PP_EAT.

// PRIVATE //

#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ_NOT_EMPTY_(...) \
    BOOST_PP_IIF(BOOST_CLOSURE_DETAIL_PP_IS_VARIADIC(__VA_ARGS__), \
        BOOST_PP_VARIADIC_TO_SEQ \
    , \
        BOOST_PP_REM \
    )(__VA_ARGS__)

// PUBLIC //

// Expand to `(arg0)(arg1)...` is __VA_ARGS__ is `arg0, arg1, ...` or already
// `(arg0)(arg1)...`, if __VA_ARGS__ is empty `` expand to `empty_seq`.
#define BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ(empty_seq, ...) \
    BOOST_PP_IF(BOOST_CLOSURE_DETAIL_PP_VARIADIC_SIZE(__VA_ARGS__), \
        BOOST_CLOSURE_DETAIL_PP_VARIADIC_TO_SEQ_NOT_EMPTY_ \
    , \
        empty_seq BOOST_PP_EAT \
    )(__VA_ARGS__)

#endif // BOOST_NO_VARIADIC_MACROS

#endif // #include guard


