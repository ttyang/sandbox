
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

/** @file
@brief Macros used to declare constructors with contracts (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/function.hpp>
#include <boost/contract/aux_/preprocessor/func_kind.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp>

/**
@brief Macro used to declare constructors with contracts.

This macro is used to declare a constructor with possible preconditions and
postconditions.
At least all public constructors of a class with non-empty class invariants
should be declared using this macro so to check the class invariants (even if
the constructors have no precondition and no postcondition).

The semantics of a call to a constructor with contracts are explained in the
@RefSect{contract_programming_overview, Contract Programming Overview} section.
Destructors and member functions are declared using the
@RefMacro{BOOST_CONTRACT_DESTRUCTOR} and @RefMacro{BOOST_CONTRACT_FUNCTION}
macros respectively.

@Params
@Param{function_declaration,
The constructor declaration syntax is explained in the
@RefSect{grammar\, Grammar} section.
Constructors must always repeat their access level <c>public</c>\,
<c>protected</c>\, or <c>private</c>.
If present\, member initializers must be specified using
<c>initialize( ... )</c> and within this macro (even if they are technically
part of the constructor definition and not of its declaration).
}
@EndParams

The @RefMacro{BOOST_CONTRACT_CLASS} macro must be used to declare the class
enclosing a constructor declared using this macro.

Within a type-dependent scope (e.g., within templates), the
@RefMacro{BOOST_CONTRACT_CONSTRUCTOR_TPL} macro must be used instead of this
macro.

The @RefMacro{BOOST_CONTRACT_CONSTRUCTOR_BODY} macro must be used when
separating the constructor body definition form the constructor declaration
programmed using this macro.
Unfortunately, it is not possible to use this macro so separate body
definitions for constructors that have member initializers.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CONSTRUCTOR(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_CONSTRUCTOR, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

/**
@brief Macro used to declare constructors with contracts within a
type-dependent scope (e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_CONSTRUCTOR} but it
must be used when declaring constructors with contracts within a type-dependent
scope.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_CONSTRUCTOR_TPL(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_CONSTRUCTOR, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

#endif // #include guard

