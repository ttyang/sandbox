
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

/** @file
 * @brief Configuration macros allow to change the behaviour of this library
 *  at compile-time.
 */

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_HPP_
#define BOOST_LOCAL_FUNCTION_CONFIG_HPP_

// User defined.

/**
 * @brief Maximum number of function parameters supported for the local
 *  functions.
 *
 * If programmers leave this configuration macro undefined, its default
 * value is <c>5</c>.
 * 
 * This only applies to the number of local function parameters and not to the
 * number of bound variables in scope (the limit on the number of bound
 * variables is instead the maximum size allowed for a Boost.Preprocessor
 * sequence).
 *
 * @Warning Increasing this number will increase compilation time.
 *
 * @See @RefSect{Tutorial} section, @RefSect2{Getting_Started, Getting Started}
 *  section.
 */
#ifndef BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX
#   define BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX 5
#endif

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX
#   define BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX 10
#endif

#endif // #include guard

