
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BOOST_CONTRACT_CLASS_INVARIANT_HPP_
#define BOOST_CONTRACT_CLASS_INVARIANT_HPP_

/** @file
@brief Macros used to specify class invariants (this header is automatically
included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/class_invariant.hpp>
#include <boost/contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/config.hpp>

#ifndef DOXYGEN

#ifndef BOOST_NO_VARIADIC_MACROS

#define BOOST_CONTRACT_CLASS_INVARIANT(...) \
    BOOST_CONTRACT_AUX_CLASS_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0 /* outside template */, \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ((void) /* empty */, \
                    __VA_ARGS__))

#define BOOST_CONTRACT_CLASS_INVARIANT_TPL(...) \
    BOOST_CONTRACT_AUX_CLASS_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1 /* inside template */, \
            BOOST_CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ((void) /* empty */, \
                    __VA_ARGS__))

#else

#define BOOST_CONTRACT_CLASS_INVARIANT(seq) \
    BOOST_CONTRACT_AUX_CLASS_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            seq)

#define BOOST_CONTRACT_CLASS_INVARIANT_TPL(seq) \
    BOOST_CONTRACT_AUX_CLASS_INVARIANT( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            seq)

#endif

#else

/**
@brief Macro used to specify class invariants.

This macro must be used to specify class invariant at the very beginning of the
definition of a class with contracts declared using the
@RefMacro{BOOST_CONTRACT_CLASS} macro (no other statement can appear before this
macro in the class definition, not even a <c>typedef</c> or a <c>friend</c>
declaration).

Constructors, destructors, and member functions with contracts are declared
using the @RefMacro{BOOST_CONTRACT_CONSTRUCTOR},
@RefMacro{BOOST_CONTRACT_DESTRUCTOR}, and @RefMacro{BOOST_CONTRACT_FUNCTION}
macros respectively.
The semantics of calls to constructors, destructors, and member functions of a
class with contracts are explained in the
@RefSect{contract_programming_overview, Contract Programming Overview} section.

@Params
@Param{class_invariants,
The syntax for class invariants is explained in the @RefSect{grammar\, Grammar}
section.
Use <c>void</c> to specify empty class invariant.
}
@EndParams

Within a type-dependent scope (e.g., within templates), the
@RefMacro{BOOST_CONTRACT_CLASS_INVARIANT_TPL} macro must be used instead of
this macro.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CLASS_INVARIANT(class_invariants)

/**
@brief Macro used to specify class invariants within a type-dependent scope
(e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_CLASS_INVARIANT} but
it must be used when specifying class invariants within a type-dependent scope.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CLASS_INVARIANT_TPL(class_invariants)

#endif

#endif // #include guard

