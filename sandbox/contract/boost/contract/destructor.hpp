
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

/** @file
@brief Macros used to declare destructors with contracts (this header is
automatically included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/function.hpp>
#include <boost/contract/aux_/preprocessor/func_kind.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp>

/**
@brief Macro used to declare destructors with contracts.

This macro is used to declare a destructor.
At least the public destructor of a class with non-empty class invariants should
be declared using this macro in order to check the class invariants (even if
destructors never have preconditions or postconditions).

The semantics of a call to a destructor with contracts are explained in the
@RefSect{contract_programming_overview, Contract Programming Overview} section.
Constructor and member functions are declared using the
@RefMacro{BOOST_CONTRACT_CONSTRUCTOR} and @RefMacro{BOOST_CONTRACT_FUNCTION}
macros respectively.

@Params
@Param{function_declaration,
The destructor declaration syntax is explained in the
@RefSect{grammar\, Grammar} section.
Destructors must always repeat their access level <c>public</c>\,
<c>protected</c>\, or <c>private</c>.
The keyword <c>void</c> must be used to indicate that the destructor has an
empty parameter list.
}
@EndParams

The @RefMacro{BOOST_CONTRACT_CLASS} macro must be used to declare the class
enclosing a destructor declared using this macro.

Within a type-dependent scope (e.g., within templates), the
@RefMacro{BOOST_CONTRACT_DESTRUCTOR_TPL} macro must be used instead of this
macro.

The @RefMacro{BOOST_CONTRACT_DESTRUCTOR_BODY} macro must be used when
separating the destructor body definition from the destruction declaration
programmed using this macro.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_DESTRUCTOR(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_DESTRUCTOR, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

/**
@brief Macro used to declare destructors with contracts within a type-dependent
scope (e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_DESTRUCTOR} but it
must be used when declaring destructors with contracts within a type-dependent
scope.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_DESTRUCTOR_TPL(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_DESTRUCTOR, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

#endif // #include guard

