
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

/** @file
@brief Macros used to declare free functions, member functions, and operators
with contracts (this header is automatically included by <c>contract.hpp</c>).
*/

#include <boost/contract/aux_/macro/function.hpp>
#include <boost/contract/aux_/preprocessor/func_kind.hpp>
#include <boost/contract/detail/preprocessor/traits/func.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>

/**
@brief Macro used to declare free functions, free function operators, member
functions, and member function operators with contracts.

This macro is used to declare a function with possible preconditions and
postconditions.
At least all public member functions and public member function operators of a
class with non-empty class invariants should be declared using this macro in
order to check the class invariants (even if the functions and operators have
no precondition and no postcondition).

The semantics of a call to a function with contracts are explained in the
@RefSect{contract_programming_overview, Contract Programming Overview} section.
Constructors and destructors are declared using the
@RefMacro{BOOST_CONTRACT_CONSTRUCTOR} and @RefMacro{BOOST_CONTRACT_DESTRUCTOR}
macros respectively.

@Params
@Param{function_declaration,
The function declaration syntax is explained in the @RefSect{grammar\, Grammar}
section.
Member functions must always repeat their access level <c>public</c>\,
<c>protected</c>\, or <c>private</c>.
Operators use a special syntax to specify their symbols and names.
}
@EndParams

The @RefMacro{BOOST_CONTRACT_CLASS} macro must be used to declare classes
enclosing member functions and member function operators declared using this
macro.

Within a type-dependent scope (e.g., within templates), the
@RefMacro{BOOST_CONTRACT_FUNCTION_TPL} macro must be used instead of this macro.

The @RefMacro{BOOST_CONTRACT_FREE_BODY} and
@RefMacro{BOOST_CONTRACT_MEMBER_BODY} macros must be used when separating free
and member function body definitions from the function declarations programmed
using this macro.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_FUNCTION(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            0, /* outside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_FUNCTION, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

/**
@brief Macro used to declared free functions, free function operators, member
functions, and member function operators with contracts within a type-dependent
scope (e.g., within templates).

This macro is the exact same as @RefMacro{BOOST_CONTRACT_FUNCTION} but it must
be used when declaring functions with contracts within a type-dependent scope.

@SeeAlso @RefSect{tutorial, Tutorial} section.
*/
#define BOOST_CONTRACT_FUNCTION_TPL(function_declaration) \
    BOOST_CONTRACT_AUX_FUNCTION( \
            BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER, \
            1, /* inside template */ \
            BOOST_CONTRACT_AUX_PP_FUNC_KIND_FUNCTION, \
            BOOST_CONTRACT_DETAIL_PP_FUNC_TRAITS(function_declaration))

#endif // #include guard

