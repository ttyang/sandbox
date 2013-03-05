
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_CLASS_HPP_
#define BOOST_CONTRACT_CLASS_HPP_

/** @file
@brief Macros used to declare classes with contracts (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/class.hpp>
#include <boost/contract/detail/preprocessor/traits/class.hpp>

/**
@brief Macro used to declare classes with contracts.

This macro is used to declare a class with class invariants and member
functions with preconditions and postconditions.
A class declared with this macro must always specify (possibly empty) class
invariants using the @RefMacro{BOOST_CONTRACT_CLASS_INVARIANT} macro.

Constructors, destructors, and member functions with contracts are declared
using the @RefMacro{BOOST_CONTRACT_CONSTRUCTOR},
@RefMacro{BOOST_CONTRACT_DESTRUCTOR}, and @RefMacro{BOOST_CONTRACT_FUNCTION}
macros respectively.
The semantics of calls to constructors, destructors, and member functions with
contracts are explained in the
@RefSect{contract_programming_overview, Contract Programming Overview} section.

@Params
@Param{class_declaration,
The class declaration syntax is explained in the @RefSect{grammar\, Grammar}
section.
If present\, base classes must be specified using <c>extends( ... )</c>.
}
@EndParams

Nested classes with contracts are also declared using this macro but they must
always repeat their access level <c>public</c>, <c>protected</c>, or
<c>private</c>.
Within a type-dependent scope, nested classes with contracts must be declared
using the @RefMacro{BOOST_CONTRACT_CLASS_TPL} macro.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CLASS(class_declaration) \
    BOOST_CONTRACT_AUX_CLASS( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS(class_declaration))

/**
@brief Macro used to declare nested classes with contracts within a
type-dependent scope (e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_CLASS} but it must be
used when declaring nested classes with contracts within a type-dependent scope.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CLASS_TPL(class_declaration) \
    BOOST_CONTRACT_AUX_CLASS( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            BOOST_CONTRACT_DETAIL_PP_CLASS_TRAITS(class_declaration))

#endif // #include guard

