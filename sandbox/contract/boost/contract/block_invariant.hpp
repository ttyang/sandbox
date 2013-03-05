
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_BLOCK_INVARIANT_HPP_
#define BOOST_CONTRACT_BLOCK_INVARIANT_HPP_

/** @file
@brief Macros used to specify block invariants (this header is automatically
included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/block_invariant.hpp>
#include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/config.hpp>

#ifndef DOXYGEN

#ifndef BOOST_NO_VARIADIC_MACROS

#define BOOST_CONTRACT_BLOCK_INVARIANT(...) \
    BOOST_CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    (ERROR_block_invariants_cannot_be_empty), __VA_ARGS__))

#define BOOST_CONTRACT_BLOCK_INVARIANT_TPL(...) \
    BOOST_CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    (ERROR_block_invariants_cannot_be_empty), __VA_ARGS__))

#else

#define BOOST_CONTRACT_BLOCK_INVARIANT(seq) \
    BOOST_CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            seq)

#define BOOST_CONTRACT_BLOCK_INVARIANT_TPL(seq) \
    BOOST_CONTRACT_AUX_BLOCK_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            seq)

#endif

#else

/**
@brief Macro used to specify block invariants.

This macro can appear at any point in a code block within a function definition
and it is used to assert correctness condition of the implementation (similarly
to C++ <c>assert</c>).

@Params
@Param{assertions,
The syntax for the assertions is explained in the @RefSect{grammar\, Grammar}
section.
Static assertions\, constant assertions\, and select assertions can be used.
}
@EndParams

Within a type-dependent scope (e.g., within templates),
@RefMacro{BOOST_CONTRACT_BLOCK_INVARIANT_TPL} must be used instead of this
macro.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define BOOST_CONTRACT_BLOCK_INVARIANT(assertions)

/**
@brief Macro used to specify block invariants within a type-dependent scope
(e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_BLOCK_INVARIANT} but
it must be used when specifying block invariants within a type-dependent scope.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define BOOST_CONTRACT_BLOCK_INVARIANT_TPL(assertions)

#endif

#endif // #include guard

