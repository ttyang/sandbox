
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

/** @file
 * @brief Local functions allows to program functions locally within the scope
 *  where they are needed (within enclosing functions, etc).
 */

#ifndef BOOST_LOCAL_FUNCTION_HPP_
#define BOOST_LOCAL_FUNCTION_HPP_

#include "config.hpp"
#include "aux_/function_macros/params.hpp"
#include "aux_/function_macros/name.hpp"
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/config.hpp> // For variadic macros.

// Params.

// Pass a parenthesized params seq `()()...` on C++. If variadic macros (C99, 
// GCC, MVSC, etc) you can also pass a variable length tuple `..., ...` for
// params and nothing `` for no params.
#if defined(BOOST_NO_VARIADIC_MACROS) || defined(BOOST_LOCAL_CONFIG_COMPLIANT)

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
 *              [const] bind[&] variable_name
 *  @endcode
 *  Where the following lexical conventions have been used:
 *  <c>token1 | token2</c> means either <c>token1</c> or <c>token2</c>;
 *  <c>[token]</c> means either <c>token</c> or nothing (i.e.\, <c>token</c> is
 *  optional). 
 *
 *  On C99 and later compilers which support variadic macros\, the above
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
 *  Finally\, on C++ compilers which support empty macro parameters\, the above
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
 * @Note Local functions are functors. They cannot be copied but they can be
 *  assigned to other functor objects like @RefClass{boost::local::function}.
 *
 * @See @RefSect{Tutorial} section, @RefSect2{Advanced_Topics, Advanced Topics}
 *  section, @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS_TPL},
 *  @RefMacro{BOOST_LOCAL_FUNCTION_NAME}, @RefClass{boost::local::function}.
 */
#define BOOST_LOCAL_FUNCTION_PARAMS(parameters) \
    BOOST_LOCAL_AUX_FUNCTION_PARAMS(parameters, \
            __LINE__, 0 /* no template */)

/**
 * @brief This macro is the same as @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS} but
 *  it must be used when declaring local functions within templates.
 *
 * @See @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}, @RefSect{Tutorial} section.
 */
#define BOOST_LOCAL_FUNCTION_PARAMS_TPL(parameters) \
    BOOST_LOCAL_AUX_FUNCTION_PARAMS(parameters, \
            __LINE__, 1 /* template */)

#else // BOOST_NO_VARIADIC_MACROS

#include "aux_/preprocessor/variadic/to_seq.hpp"

#define BOOST_LOCAL_FUNCTION_PARAMS(...) \
    BOOST_LOCAL_AUX_FUNCTION_PARAMS(BOOST_LOCAL_AUX_PP_VARIADIC_TO_SEQ( \
            (void) /* for empty seq */, __VA_ARGS__), \
            __LINE__, 0 /* no template */)

#define BOOST_LOCAL_FUNCTION_PARAMS_TPL(...) \
    BOOST_LOCAL_AUX_FUNCTION_PARAMS(BOOST_LOCAL_AUX_PP_VARIADIC_TO_SEQ( \
            (void) /* for empty seq */, __VA_ARGS__), \
            __LINE__, 1 /* template */)

#endif // BOOST_NO_VARIADIC_MACROS

/**
 * @brief This macro is used to specify the local function name.
 *
 * This macro must follow the local function body code block <c>{ ... }</c> as
 * shown in the @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS} documentation.
 *
 * @Params
 * @Param{name,
 *  The name of the local function. This name cannot be the name of an operator
 *  <c>operator...</c> and it cannot be the same name of another local function
 *  declared within the same enclosing scope (i.e.\, it is not possible to
 *  overload local function declarations) -- see the
 *  @RefSect2{Advanced_Topics\, Advanced Topics} section.
 * }
 * @EndParams
 *
 * @See @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS}, @RefSect{Tutorial} section,
 *  @RefSect2{Advanced_Topics, Advanced Topics} section.
 */
#define BOOST_LOCAL_FUNCTION_NAME(name) \
    BOOST_LOCAL_AUX_FUNCTION_NAME(name)

namespace boost { namespace local {

/**
 * @brief Functor with support for default function parameters.
 *
 * This template defines several specializations to handle a generic number
 * of function parameters some of which can have default values.
 * The number of supported function parameters <c>N</c> goes from <c>0</c> (for
 * a function with no parameter) to a maximum of
 * @RefMacro{BOOST_LOCAL_CONFIG_FUNCTION_ARITY_MAX}.
 *
 * Each template specialization defines call operators <c>operator()(...)</c>
 * with a different set of parameters to handle the number of default
 * parameters specified by <c>defaults</c> (see @RefSect2{Advanced_Topics,
 * Advanced Topics} section):
 * @code
 *  template<typename Result, typename Arg1, ..., typename ArgN, size_t defaults = 0>
 *  class function<Result (Arg1, ..., ArgN), defaults> {
 *  public:
 *      Result operator()(Arg1, ..., ArgN-2, ArgN-1, ArgN);
 *      // Call operators to handle default parameters:
 *      Result operator()(Arg1, ..., ArgN-2, ArgN-1); // iff defaults >= 1
 *      Result operator()(Arg1, ..., ArgN-2);         // iff defaults >= 2
 *      ...                                           // etc
 *
 *      // Default and copy constructors, and assignment operator.
 *      function();
 *      function(local_function_type<F, defaults> local_function);
 *      function& operator=(local_function_type<F, defaults> local_function);
 *  };
 * @endcode
 * Where:
 * - <c>Result</c> is the function result type.
 *   It can be <c>void</c>.
 * - <c>ArgN</c> is the last function parameter type, <c>ArgN-1</c> is the
 *   second last function parameter type, etc.
 *   These are all optional: None is specified for a function with no
 *   parameter; Only <c>Arg1</c> is specified for a function with only one
 *   parameter; Etc.
 * - The operator <c>Result operator()(Arg1, ..., ArgN-2, ArgN-1)</c> is
 *   declared if and only if there are one or more default parameters
 *   (<c>defaults >= 1</c>), the operator
 *   <c>Result operator()(Arg1, ..., ArgN-2)</c> is defined if and only if
 *   there are two or more default parameters (<c>defaults >= 2</c>), etc.
 * - <c>local_function_type<F, defaults></c> is an internal (i.e.,
 *   implementation specific) type for a local function with a signature
 *   matching <c>F</c> and with a number of default parameters equal to
 *   <c>defaults</c>.
 * - The default constructor allows to constructor this functor without
 *   assigning it to any function. A run-time error is generated if the call
 *   operator <c>operator()</c> is invoked for a functor not assigned to any
 *   function.
 * - The copy constructor and assignment operator <c>operator=</c> allow to
 *   assign this functor to a local function with a signature matching <c>F</c>
 *   and with a number of default parameters equal to <c>defaults</c>.
 * 
 * @Warning Programmers must make sure that the local function assigned to this
 *  functor survives the scope of the functor (otherwise the functor will be
 *  invalid and its use will generate a run-time error as usual with C++
 *  functors).
 *
 * @Params
 * @Param{F,
 *  The function type specifying function signature expressed using the same
 *  syntax as Boost.Function's preferred syntax:
 *  <c>F = Result (Arg1\, ...\, ArgN)</c>.
 * }
 * @Param{defaults,
 *  The number of the function default parameters in
 *  <c>[0\,</c>
 *  @RefMacro{BOOST_LOCAL_CONFIG_FUNCTION_ARITY_MAX}<c>]</c>.
 *  As usual in C++\, default parameters are counted starting from the last
 *  parameter:
 *  <c>defaults = 0</c> means that no parameter is optional\,
 *  <c>defaults = 1</c> means that the last parameter is optional\,
 *  <c>defaults = 2</c> means that the last two parameters are optional\, etc.
 * }
 * @EndParams
 *
 * @Note This functor is similar to Boost.Funciton's <c>boost::function<></c>
 *  but it also supports eventual default parameters.
 *
 * @See @RefSect2{Advanced_Topics, Advanced Topics} section,
 *  @RefMacro{BOOST_LOCAL_CONFIG_FUNCTION_ARITY_MAX},
 *  @RefMacro{BOOST_LOCAL_FUNCTION_PARAMS},
 *  @RefMacro{BOOST_LOCAL_FUNCTION_NAME},
 *  <a href='http://www.boost.org/doc/libs/release/doc/html/function.html'>Boost.Function</a>.
 */ 
template<typename F, size_t defaults = 0> // Defaults count is opt.
struct function {}; // Empty so never used directly.

}} // namespace boost::local

// Template specializations (must be #included here after the above template).
#include "aux_/function.hpp"

#endif // #include guard

