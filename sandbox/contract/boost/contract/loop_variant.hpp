
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_LOOP_VARIANT_HPP_
#define BOOST_CONTRACT_LOOP_VARIANT_HPP_

/** @file
@brief Macros used to specify loop variants (this header is automatically
included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/loop_variant.hpp>
#include <boost/contract/aux_/macro/loop_variant.hpp>
#include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/config.hpp>

// PUBLIC //

/**
@brief Macro used to declare a loop that will specify a loop variant.

This macro must be used to declare a loop that will later specify a loop
variant using the @RefMacro{BOOST_CONTRACT_LOOP_VARIANT} macro.

@Params
@Param{loop_declaration,
This is a loop declaration (<c>for</c>\, <c>while</c>\, etc) that follows the
usual C++ syntax (see also the @RefSect{grammar\, Grammar} section).
}
@EndParams

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
// No need for LOOP_TPL because variant decl always int and never type-depend.
#define BOOST_CONTRACT_LOOP(loop_declaration) \
    /* NOTE: this declared trick (originally from Boost.ScopeExit) allows */ \
    /* redefine the old variant with the same name in the same scope */ \
    /* without the "duplicate definition" compiler-error (this avoids the */ \
    /* need to wrap the code into a local scope {...} and therefore */ \
    /* avoiding an additional LOOP_END macro) plus it prevents the compiler */ \
    /* warning "unused variable" in case the loop variant expression is */ \
    /* disabled by importance ordering */ \
    BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CONFIG_LOOP_VARIANTS_01, \
        ::contract::aux::loop_variant::declared< \
            ::contract::aux::loop_variant::resolve< \
                sizeof(BOOST_CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR) \
            >::cmp1<0>::cmp2 \
        > BOOST_CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR; \
        BOOST_CONTRACT_AUX_CODE_LOOP_VARIANT_OLD_VAR.value = \
                ::contract::aux::loop_variant::uninitialized; \
    ) \
    loop_declaration

#ifndef DOXYGEN

#ifndef BOOST_NO_VARIADIC_MACROS

#define BOOST_CONTRACT_LOOP_VARIANT(...) \
    BOOST_CONTRACT_AUX_LOOP_VARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0 /* outside template */, \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    ERROR_loop_variant_cannot_be_empty, __VA_ARGS__))

#define BOOST_CONTRACT_LOOP_VARIANT_TPL(...) \
    BOOST_CONTRACT_AUX_LOOP_VARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1 /* inside template */, \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ( \
                    ERROR_loop_variant_cannot_be_empty, __VA_ARGS__))

#else

#define BOOST_CONTRACT_LOOP_VARIANT(seq) \
    BOOST_CONTRACT_AUX_LOOP_VARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            seq)

#define BOOST_CONTRACT_LOOP_VARIANT_TPL(seq) \
    BOOST_CONTRACT_AUX_LOOP_VARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            seq)

#endif

#else

/**
@brief Macro used to specify a loop variant.

This macro is used to specify loop variants which ensure that loops terminate.
This macro must be used within the body <c>{ ... }</c> of a loop declared using
the @RefMacro{BOOST_CONTRACT_LOOP} macro.
Each loop can have at most one loop variant.

@Params
@Param{loop_variant,
The loop variant must be a non-negative integral expression that monotonically
decreases when calculated at each subsequent loop iteration
(constant-expressions can also be used\, see the @RefSect{grammar\, Grammar}
section).
}
@EndParams

Within type-dependent scope (e.g., within templates), the
@RefMacro{BOOST_CONTRACT_LOOP_VARIANT_TPL} macro must be used instead of this
macro.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define BOOST_CONTRACT_LOOP_VARIANT(loop_variant)

/**
@brief Macro used to specify a loop variant within a type-dependent scope
(e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_LOOP_VARIANT} but it
must be used when specifying loop variants within a type-dependent scope.

@SeeAlso @RefSect{advanced_topics, Advanced Topics} section.
*/
#define BOOST_CONTRACT_LOOP_VARIANT_TPL(loop_variant)

#endif

#endif // #include guard

