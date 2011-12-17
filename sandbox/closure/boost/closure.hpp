
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

/** @file
 * @brief Local functions allows to program functions locally within the scope
 *  where they are needed.
 */

#ifndef BOOST_CLOSURE_HPP_
#define BOOST_CLOSURE_HPP_

#include <boost/closure/config.hpp>
#include <boost/closure/aux_/symbol.hpp>
#include <boost/closure/aux_/macro/closure.hpp>
#include <boost/closure/aux_/macro/closure_end.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/config.hpp> // For variadic macros.

// Pass a parenthesized params seq `()()...` on C++. If variadic macros (C99, 
// GCC, MVSC, etc) you can also pass a variable length tuple `..., ...` for
// params and nothing `` for no params.
#if defined(BOOST_NO_VARIADIC_MACROS)

/** @cond */
#define BOOST_CLOSURE_(id, is_template, decl_seq) \
    BOOST_CLOSURE_AUX_CLOSURE(decl_seq, id, is_template)
/** @endcond */

/**
 * @brief This macro is used to declare the local function parameters.
 *
 * This macro must be used within a declarative context, it must follow the
 * local function result type, it must be followed by the local function body
 * code and then by the @RefMacro{BOOST_LOCAL_FUNCTION_NAME} macro (see the
 * @RefSect{Tutorial} and @RefSect2{Advanced_Topics, Advanced Topics}
 * sections):
 * @code
 *  { // Some declarative context.
 *      ...
 *      result_type BOOST_LOCAL_FUNCTION_PARAMS(parameters) {
 *          ... // Body code.
 *      } BOOST_LOCAL_FUNCTION_NAME(name)
 *      ...
 *  }
 * @endcode
 *
 * As usual, exceptions specifications can be optionally programmed before the
 * body code block (but the specifications will only apply the body code and
 * not to the library code automatically generated by the macro expansion,
 * see @RefSect2{Advanced_Topics, Advanced Topics}).
 *
 * Within templates, the special macro
 * @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS_TPL} must be used instead of
 * @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}.
 *
 * @Params
 * @Param{parameters,
 *  On all C++ compilers\, the <em>sequencing macro syntax</em> defined by the
 *  following grammar is used to specify the local function parameters:
 *  @code
 *      parameters:
 *              void_list | parameter_list
 *      void_list:
 *              (void)
 *      parameter_list:
 *              (parameter1) (parameter2) ...
 *      parameter:
 *              normal_parameter | bound_parameter
 *      normal_parameter:
 *              [auto | register] parameter_type parameter_name
 *              [default_parameter_value]
 *      default_parameter_value:
 *              (default_value)
 *      default_value:
 *              default default_vale_expression
 *      bound_parameter:
 *              [const] bind [(variable_type)] [&] variable_name
 *  @endcode
 *  Where the following lexical conventions have been used:
 *  <c>token1 | token2</c> means either <c>token1</c> or <c>token2</c>;
 *  <c>[token]</c> means either <c>token</c> or nothing (i.e.\, <c>token</c> is
 *  optional). 
 *
 *  On C99 and later compilers that support variadic macros\, the above
 *  grammar can be modified as follow to define the <em>variadic macro
 *  syntax</em> that can also be used to specify the local functions
 *  parameters:
 *  @code
 *      void_list:
 *              void
 *      parameter_list:
 *              parameter1\, parameter2\, ...
 *      default_parameter_value:
 *              \, default_value
 *  @endcode
 *  Note that the variadic macro syntax uses commas <c>\,</c> instead of
 *  parenthesis <c>()</c> to separate the parameters and therefore resembles
 *  the usual C++ function parameter declaration syntax more closely than the
 *  sequencing macro syntax. However\, the variadic macro syntax will only work
 *  on C++ compilers that support variadic macros so it should be used with
 *  care in order to avoid portability issues. 
 *
 *  Finally\, on C++ compilers that support empty macro parameters\, the above
 *  grammars can be modified as follow to define the <em>empty macro
 *  syntax</em> that can can also be used to specify an empty parameter list:
 *  @code
 *      void_list:
 *              ()
 *  @endcode
 *  Note that the empty macro parameter syntax uses the usual C++ syntax to
 *  specify empty function parameter list but it will only work on compilers
 *  that support empty macro parameters so it should be used with care in order
 *  to avoid portability issues.
 * }
 * @EndParams
 *
 * When the object <c>this</c> is specified as the name of the variable to
 * bind, the body must use the special name <c>this_</c> to access the bound
 * object.
 * The special name <c>this_</c> is defined by the configuration macro
 * @RefMacro{BOOST_LOCAL_CONFIG_THIS_PARAM_NAME}.
 *
 * The number of local function parameters (excluding bound variables) is
 * specified by the configuration macro
 * @RefMacro{BOOST_LOCAL_CONFIG_FUNCTION_ARITY_MAX}.
 * Both the variadic and empty macro syntaxes are always disabled when the
 * configuration macro @RefMacro{BOOST_LOCAL_CONFIG_COMPLIANT} is defined.
 *
 * @Note Local functions are functors so they can be assigned to other functors
 *  like <c>boost::function</c> (see Boost.Function).
 *
 * @Note This macro cannot be used multiple times on the same line because it
 *  internally uses the line number <c>__LINE__</c> to generate unique
 *  identifiers.
 *
 * @See @RefSect{Tutorial} section, @RefSect2{Advanced_Topics, Advanced Topics}
 *  section, @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS_TPL},
 *  @RefMacro{BOOST_LOCAL_FUNCTION_NAME},
 *  @RefMacro{BOOST_LOCAL_CONFIG_THIS_PARAM_NAME},
 *  @RefMacro{BOOST_LOCAL_CONFIG_FUNCTION_ARITY_MAX},
 *  @RefMacro{BOOST_LOCAL_CONFIG_COMPLIANT}, Boost.Function.
 */
#define BOOST_CLOSURE(declarations) \
    BOOST_CLOSURE_(__LINE__, 0 /* no template */, declarations)

/**
 * @brief This macro is the same as @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS} but
 *  it must be used when declaring local functions within templates.
 *
 * @See @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}, @RefSect{Tutorial} section.
 */
#define BOOST_CLOSURE_TPL(declarations) \
    BOOST_CLOSURE_(__LINE__, 1 /* template */, declarations)

#else // BOOST_NO_VARIADIC_MACROS

#include <boost/closure/aux_/preprocessor/variadic/to_seq.hpp>

#define BOOST_CLOSURE_(id, is_template, ...) \
    BOOST_CLOSURES_AUX_CLOSURE(BOOST_CLOSURE_AUX_PP_VARIADIC_TO_SEQ( \
            (void) /* for empty seq */, __VA_ARGS__), \
            id, is_template)

#define BOOST_CLOSURE(...) \
    BOOST_CLOSURE_(__LINE__, 0 /* no template */, __VA_ARGS__)

#define BOOST_CLOSURE_TPL(...) \
    BOOST_CLOSURE_(__LINE__, 1 /* template */, __VA_ARGS__)

#endif // BOOST_NO_VARIADIC_MACROS

/**
 * @brief This macro is used to specify the local function name.
 *
 * This macro must follow the local function body code block <c>{ ... }</c> as
 * shown in the @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS} documentation.
 *
 * The local function name can be prefixed by the "keyword" <c>inline</c>
 * (see the @RefSect2{Advanced_Topics, Advanced Topics} section):
 * @code
 *  ... BOOST_LOCAL_FUNCTION_NAME(inline name)
 * @endcode
 * This increases the chances that the compiler will be able to inline the
 * local function calls (thus reducing their run-time).
 * However, inlined local functions cannot be passed as template parameters or
 * assigned to other functors like <c>boost::function</c> (that is true on
 * C++03 compilers, see @RefMacro{BOOST_LOCAL_CONFIG_COMPLIANT}, but inlined
 * local functions can instead be passed as template parameters on C++11
 * compilers).
 * On C++11 compilers, there is no need to declare a local function lined
 * because this library will automatically use C++11 specific features to
 * inline the local function while always allowing to pass it as a template
 * parameter.
 *
 * The local function name can also be prefixed by the "keyword"
 * <c>recursive</c> (see the @RefSect2{Advanced_Topics, Advanced Topics}
 * section):
 * @code
 *  ... BOOST_LOCAL_FUNCTION_NAME(recursive name)
 * @endcode
 * This allows the local function to recursively call itself from its body (as
 * usual in C++).
 * However, compilers have not been observed to be able to inline recursive
 * local function calls (not even when the recursive local function is also
 * declared inlined).
 *
 * @Params
 * @Param{name,
 *  The name of the local function. 
 *  The local function name can be prefixed by the "keyword" <c>inline</c> to
 *  declare the local function inlined or by the "keyword" <c>recursive</c> to
 *  declare the local function recursive (see the @RefSect2{Advanced_Topics\,
 *  Advanced Topics} section).
 *  The local function name cannot be the name of an operator
 *  <c>operator...</c> and it cannot be the same name of another local function
 *  declared within the same enclosing scope (use the
 *  @RefClass{boost::local::function::overload} functor to overload local
 *  functions\, see the @RefSect2{Advanced_Topics\, Advanced Topics} section).
 * }
 * @EndParams
 *
 * @See @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}, @RefSect{Tutorial} section,
 *  @RefSect2{Advanced_Topics, Advanced Topics} section,
 *  @RefMacro{BOOST_LOCAL_CONFIG_COMPLIANT}.
 */
#define BOOST_CLOSURE_END(name) \
    BOOST_CLOSURE_AUX_CLOSURE_END(name)

/** @todo make this accept this_ and error on this */
// Bound variable name. Expand to qualified bound type (i.e., bound variable
// type with extra const and/or & for const and/or reference binds).
// Can be used with local functions, blocks, and exits. It accepts `this`.
/**
 * @brief This macro expands to the fully qualified type of a variable bound
 *  to to local functions, local blocks, and local exits.
 *
 * The type is fully qualified in that it contains the extra constant and
 * reference qualifiers when they are specified for binding by constant and by
 * reference.
 * For example, if a variable named <c>t</c> of type <c>T</c> is:
 * @li Bound by value using <c>bind t</c> then
 *  <c>BOOST_LOCAL_TYPEOF(t)</c> is <c>T</c>.
 * @li Bound by constant value using <c>const bind t</c>
 *  then <c>BOOST_LOCAL_TYPEOF(t)</c> is <c>const T</c>.
 * @li Bound by reference using <c>bind& t</c>
 *  then <c>BOOST_LOCAL_TYPEOF(t)</c> is <c>T&</c>.
 * @li Bound by constant reference using <c>const bind& t</c>
 *  then <c>BOOST_LOCAL_TYPEOF(t)</c> is <c>const T&</c>.
 *
 * Within local functions, local blocks, and local exits, this macro can be
 * used to deduce the bound variable types to declare local variables, check
 * concepts (using Boost.ConceptCheck), etc (see @RefSect2{Advanced_Topics,
 * Advanced Topics} section).
 *
 * @Params
 * @Param{bound_variable_name,
 *  The name of the bound variable for which the type is being deduced.
 * }
 * @EndParams
 *
 * @See @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}, @RefMacro{BOOST_LOCAL_BLOCK},
 *  @RefMacro{BOOST_LOCAL_EXIT}, @RefSect2{Advanced_Topics, Advanced Topics}
 *  section.
 */
#define BOOST_CLOSURE_TYPEOF(bound_variable_name) \
    BOOST_CLOSURE_AUX_SYMBOL_TYPEOF_TYPE(bound_variable_name)

#endif // #include guard

