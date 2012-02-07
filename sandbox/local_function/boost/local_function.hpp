
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_HPP_
#define BOOST_LOCAL_FUNCTION_HPP_

#ifndef DOXYGEN

#include <boost/local_function/aux_/macro/decl.hpp>
#include <boost/local_function/aux_/macro/name.hpp>
#include <boost/local_function/aux_/macro/typeof.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl.hpp>
#include <boost/local_function/detail/preprocessor/line_counter.hpp>
#include <boost/local_function/detail/preprocessor/void_list.hpp>
#include <boost/config.hpp>

// PUBLIC //

#ifdef BOOST_NO_VARIADIC_MACROS
#   define BOOST_LOCAL_FUNCTION(declarations) \
        BOOST_LOCAL_FUNCTION_AUX_DECL( \
              BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER \
            , 0 /* not within template */ \
            , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(declarations)) \
        )
#   define BOOST_LOCAL_FUNCTION_TPL(declarations) \
        BOOST_LOCAL_FUNCTION_AUX_DECL( \
              BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER \
            , 1 /* within template */ \
            , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(declarations)) \
        )
#else // VARIADIC
#   define BOOST_LOCAL_FUNCTION(...) \
        BOOST_LOCAL_FUNCTION_AUX_DECL( \
              BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER \
            , 0 /* not within template */ \
            , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(__VA_ARGS__)) \
        )
#   define BOOST_LOCAL_FUNCTION_TPL(...) \
        BOOST_LOCAL_FUNCTION_AUX_DECL( \
              BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER \
            , 1 /* within template */ \
            , BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS( \
                    BOOST_LOCAL_FUNCTION_DETAIL_PP_VOID_LIST(__VA_ARGS__)) \
        )
#endif // VARIADIC

#define BOOST_LOCAL_FUNCTION_NAME(qualified_function_name) \
    BOOST_LOCAL_FUNCTION_AUX_NAME(qualified_function_name)

#define BOOST_LOCAL_FUNCTION_TYPEOF(bound_variable_name) \
    BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE(bound_variable_name)

// DOCUMENTATION //

#else // DOXYGEN

/** @file
@brief Local functions allow to program functions locally, directly within the
scope where they are needed.
*/

/**
@brief This macro is used to start a local function declaration.

This macro must be used within a declarative context, it must follow the local
function result type, it must be followed by the local function body code, and
then by the @RefMacro{BOOST_LOCAL_FUNCTION_NAME} macro (see the
@RefSect{Tutorial} and @RefSectId{Advanced_Topics, Advanced Topics} sections):
@code
{ // Some declarative context.
    ...
    result_type BOOST_LOCAL_FUNCTION(declarations) {
        ... // Body code.
    } BOOST_LOCAL_FUNCTION_NAME(qualified_function_name)
    ...
}
@endcode

As usual, exceptions specifications can be optionally programmed just after the
macro and before the body code block <c>{ ... }</c> (but the exception
specifications will only apply to the body code and not to the library code
automatically generated by the macro expansion, see the
@RefSectId{Advanced_Topics, Advanced Topics} section).

Within templates, the special macro @RefMacro{BOOST_LOCAL_FUNCTION_TPL} must be
used instead of@RefMacro{BOOST_LOCAL_FUNCTION}.

@Params
@Param{declarations,
On compilers that support variadic macros\, the parameter declarations are
defined by the following grammar:
@code
    declarations:
            void | declaration_tuple | declaration_sequence
    declaration_tuple:
            declaration\, declaration\, ...
    declaration_sequence:
            (declaration) (declaration) ...
    declaration:
            bound_variable | parameter | default_value | result_type
    bound_variable:
            [const] bind [(variable_type)] [&] variable_name
    parameter:
            [auto | register] parameter_type parameter_name
    default_value:
            default parameter_default_value
    result_type:
            return function_result_type
@endcode
On compilers that do not support variadic macros\, <c>declaration_tuple</c>
cannot be used:
@code
    declarations:
            void | declaration_sequence
@endcode

Lexical conventions: <c>token1 | token2</c> means either <c>token1</c> or
<c>token2</c>; <c>[token]</c> means either <c>token</c> or nothing;
<c>{expression}</c> means the token resulting from the expression.
}
@EndParams
 
Note that on compilers that support variadic macros, commas can be used to
separate the declarations resembling more closely the usual C++ function
declaration syntax.
This is the preferred syntax.
However, for portability, on all C++ compilers (with and without variadic
macros) the same library macros also accept parameter declarations specified as
a Boost.Preprocessor sequence separated by round parenthesis <c>()</c>.

When binding the object <c>this</c>, the special symbol <c>this_</c> needs to
be used instead of <c>this</c> as the name of the variable to bind and also
within the local function body to access the object.
(Mistakenly using <c>this</c> instead of <c>this_</c> might not always result in a compiler error and will in general result in undefined behaviour.)

The result type must either be specified just before the macro or within the
macro declarations prefixed by <c>return</c> (but not in both places).

Within the local function body it possible to access the result type using <c>result_type</c>, the type of the first parameter using <c>arg1_type</c>, the type of the second parameter using <c>arg2_type</c>, etc.
The bound variable types can be accessed using @RefMacro{BOOST_LOCAL_FUNCTION_TYPEOF}.

The maximum number of local function parameters (excluding bound variables) is
specified by the configuration macro
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX}.
The maximum number of bound variables is specified by the configuration macro
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}.

@Note Local functions are functors so they can be assigned to other functors
like <c>boost::function</c> (see Boost.Function).

@Note This macro cannot be portably used multiple times on the same line
(because on GCC and other compilers, it internally uses the line number
<c>__LINE__</c> to generate unique identifiers).

@See @RefSect{Tutorial} section,
@RefSectId{Advanced_Topics, Advanced Topics} section,
@RefMacro{BOOST_LOCAL_FUNCTION_TPL},
@RefMacro{BOOST_LOCAL_FUNCTION_NAME},
@RefMacro{BOOST_LOCAL_FUNCTION_TYPEOF},
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX},
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}.
*/
#define BOOST_LOCAL_FUNCTION(declarations)

/**
@brief This macro is used to start a local function declaration within templates.

This macro must be used instead of @RefMacro{BOOST_LOCAL_FUNCTION} when declaring a local function within a template.
A part from that, this macro has the exact same syntax as @RefMacro{BOOST_LOCAL_FUNCTION} (see @RefMacro{BOOST_LOCAL_FUNCTION} for more information):
@code
{ // Some declarative context with a template.
    ...
    result_type BOOST_LOCAL_FUNCTION_TPL(declarations) {
        ... // Body code.
    } BOOST_LOCAL_FUNCTION_NAME(qualified_function_name)
    ...
}
@endcode

@Note C++03 does not allow to use <c>typename</c> outside templates.
This library internally manipulates types, these operations require
<c>typename</c> but only within templates so this macro is used to indicate to
the library when the enclosing scope is a template.

@See @RefSect{Tutorial} section, @RefMacro{BOOST_LOCAL_FUNCTION},
@RefMacro{BOOST_LOCAL_FUNCTION_NAME}.
*/
#define BOOST_LOCAL_FUNCTION_TPL(declarations)

/**
@brief This macro is used to end a local function declaration specifying its
name.

This macro must follow the local function body code block <c>{ ... }</c>:
@code
{ // Some declarative context.
    ...
    result_type BOOST_LOCAL_FUNCTION(declarations) {
        ... // Body code.
    } BOOST_LOCAL_FUNCTION_NAME(qualified_function_name)
    ...
}
@endcode

@Params
@Param{qualified_function_name,
The name of the local function optionally qualified as follow:
@code
qualified_function_name:
        [inline] [recursive] name
@endcode
Lexical conventions: <c>token1 | token2</c> means either <c>token1</c> or
<c>token2</c>; <c>[token]</c> means either <c>token</c> or nothing;
<c>{expression}</c> means the token resulting from the expression.
}
@EndParams

The local function name can be qualified by prefixing it with the keyword
<c>inline</c> (see the @RefSectId{Advanced_Topics, Advanced Topics} section):
<c>BOOST_LOCAL_FUNCTION_NAME(inline name)</c>.
This increases the chances that the compiler will be able to inline the local
function calls (thus reducing run-time).
However, inlined local functions cannot be passed as template parameters (e.g., to <c>std::for_each</c>) or assigned to other functors (e.g., to
<c>boost::function</c>).
That is true on C++03 compilers but inlined local functions can instead be
passed as template parameters on C++11 compilers.
On C++11 compilers, there is no need to declare a local function lined because
this library will automatically use C++11 specific features to inline the local
function while always allowing to pass it as a template parameter.

The local function name can also be qualified by prefixing it with the
"keyword" <c>recursive</c> (see the
@RefSectId{Advanced_Topics, Advanced Topics} section):
<c>BOOST_LOCAL_FUNCTION_NAME(recursive name)</c>.
This allows the local function to recursively call itself from its body (as
usual in C++).
However, compilers have not been observed to be able to inline recursive
local function calls (not even when the recursive local function is also
declared inline: <c>BOOST_LOCAL_FUNCTION(inline recursive name)</c>).
Furthermore, recursive local functions should only be called within their
declaration scope (otherwise the result is undefined behaviour).

@Note The local function name cannot be the name of an operator
<c>operator...</c> and it cannot be the same name of another local function
declared within the same enclosing scope (but <c>boost::overloaded_function</c>
can be used to overload local functions, see
Boost.Functional/OverloadedFunction and the
@RefSectId{Advanced_Topics, Advanced Topics} section).

@See @RefSect{Tutorial} section,
@RefSectId{Advanced_Topics, Advanced Topics} section,
@RefMacro{BOOST_LOCAL_FUNCTION}.
*/
#define BOOST_LOCAL_FUNCTION_NAME(qualified_function_name)

/**
@brief This macro expands to the type of the specified bound variable.

This macro can be used within the local functions body to refer to the bound
variable types so to declare local variables, check concepts (using
Boost.ConceptCheck), etc (see the @RefSectId{Advanced_Topics, Advanced Topics}
section).
This way the local function can be programmed entirely without explicitly
specifying the bound variable types thus facilitating maintenance (e.g., if
the type of a bound variable changes in the enclosing scope, the local function
code does not have to change).

@Params
@Param{bound_variable_name,
The name of one of the local function's bound variables.
}
@EndParams

The type returned by the macro is fully qualified in that it contains the extra
constant and reference qualifiers when the specified variable is bound by
constant and by reference.
For example, if a variable named <c>t</c> of type <c>T</c> is:
@li Bound by value using <c>bind t</c> then
<c>BOOST_LOCAL_FUNCTION_TYPEOF(t)</c> is <c>T</c>.
@li Bound by constant value using <c>const bind t</c> then
<c>BOOST_LOCAL_FUNCTION_TYPEOF(t)</c> is <c>const T</c>.
@li Bound by reference using <c>bind& t</c> then
<c>BOOST_LOCAL_FUNCTION_TYPEOF(t)</c> is <c>T&</c>.
@li Bound by constant reference using <c>const bind& t</c> then
<c>BOOST_LOCAL_FUNCTION_TYPEOF(t)</c> is <c>const T&</c>.

This macro must be prefixed by <c>typename</c> when used in a type dependant context.

It is best to use this macro instead of Boost.Typeof so to reduce the number of times Boost.Typeof is used to deduce types (see the @RefSectId{Advanced_Topics, Advanced Topics} section).

@See @RefSectId{Advanced_Topics, Advanced Topics} section,
@RefMacro{BOOST_LOCAL_FUNCTION}.
*/
#define BOOST_LOCAL_FUNCTION_TYPEOF(bound_variable_name)

#endif // DOXYGEN

#endif // #include guard

