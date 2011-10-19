
// Copyright (C) 2009-2011 Lorenzo Caminiti
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0 (see accompanying file LICENSE_1_0.txt or a
// copy at http://www.boost.org/LICENSE_1_0.txt).

/** @file
 * @brief Identity macros are used to pass expressions with commas (not already
 *  wrapped within round parenthesis) as macros parameters.
 *
 * @Note The only way (at least as far as the authors know) to pass an
 *  arbitrary number of commas within macro parameters without explicitly
 *  indicating the number of commas (and without using variadic macros which
 *  are not part of the C++03 standard) is to wrap the expression within round
 *  parenthesis that are not replaced by macro expansion and then to remove the
 *  extra parenthesis at compile-time (for type expressions) or at run-time
 *  (for value expressions).
 *  This is what these macros do.
 */

#ifndef BOOST_IDENTITY_HPP_
#define BOOST_IDENTITY_HPP_

#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/add_reference.hpp>

/** @cond */
namespace boost { namespace aux {

// Identity for values (compilers should be able to optimize call overhead).
template<typename T>
inline typename boost::add_reference<T>::type identity_value(
        typename boost::add_reference<T>::type value) {
    return value;
}

}} // namespace boost::aux
/** @endcond */

/**
 * @brief This macro wraps the specified type expression within extra
 *  parenthesis so the type can be passed as a single macro parameter even if
 *  it contains commas (not already wrapped within round parenthesis).
 *
 * This macro expands to an expression that can be passed as a single macro
 * parameter even if it contains commas and that evaluates to the specified
 * type at compile-time (see the @RefSect2{Advanced_Topics, Advanced Topics}
 * section).
 *
 * For example <c>BOOST_IDENTITY_TYPE((std::map<int, double>))</c> can be
 * passed as a single macro parameter when instead
 * <c>std::map<int, double></c> cannot (because <c>std::map<int, double></c>
 * contains a comma not wrapped by round parenthesis so it will be interpreted
 * as two separate macro parameters by the preprocessor).
 *
 * In many cases it might be possible to use alternatives to this macro that
 * will make the code more readable.
 * For example, it might be possible to use define a new type
 * <c>typedef std::map<int, duble> map_type</c> prior to the macro and then
 * pass the newly defined type <c>map_type</c> which contains no comma as the
 * macro parameter.
 *
 * This macro must be prefixed by <c>typename</c> when used within a
 * type-dependant context (for example, within a template).
 *
 * On some compilers (like GCC), using this macro on abstract types (classes
 * with one or more pure virtual functions) generate a compile-time error.
 * This can be worked around by manipulating the type adding and removing a
 * reference to it:
 * @code
 *  boost::remove_reference< BOOST_IDENTITY_TYPE((boost::add_reference<
 *      my_abstract_type< int, double >
 *  >::type)) >::type
 * @endcode
 *
 * @Params
 * @Param{parenthesized_type,
 *  The type expression to be passed as macro parameter wrapped by a single set
 *  of round parenthesis <c>(...)</c>.
 *  This type expression can contain an arbitrary number of commas.
 * }
 * @EndParams
 *
 * @Note This macro works on C++03 compilers (it does not require variadic
 *  macros). It expands to code equivalent to
 *  <c>boost::function_traits<void parenthesized_type>::arg1_type</c>.
 *
 * @Warning The compiler will not be able to automatically deduce any template
 *  parameter type part of the type expression specified by this macro.
 *  For example, if this macro is used to wrap the type <c>std::map<T, V></c>
 *  where <c>T</c> and <c>V</c> are template parameters, the compiler will not
 *  be able to automatically deduce <c>T</c> and <c>V</c> which will have to be
 *  explicitly specified when invoking the template expression.
 *  (This is never a concern for local functions because they cannot be
 *  templates.)
 *
 * @See @RefSect2{Advanced_Topics, Advanced Topics} section.
 */
#define BOOST_IDENTITY_TYPE(parenthesized_type) \
    /* must NOT prefix this with `::` to work with parenthesized syntax */ \
    boost::function_traits< void parenthesized_type >::arg1_type

/**
 * @brief This macro wraps the specified value expression within extra
 *  parenthesis so the value can be passed as a single macro parameter even if
 *  it contains commas (not already wrapped within round parenthesis).
 *
 * This macro expands to an expression that can be passed as a single macro
 * parameter even if it contains commas and that evaluates to the specified
 * value at run-time (see the @RefSect2{Advanced_Topics, Advanced Topics}
 * section).
 *
 * For example <c>BOOST_IDENTITY_VALUE((key_sizeof<int, double>::value))</c>
 * can be passed as a single macro parameter when instead
 * <c>key_sizeof<int, double>::value</c> cannot (because
 * <c>key_sizeof<int, double>::value</c> contains a comma not wrapped by round
 * parenthesis so it will be interpreted as two separate macro parameters by
 * the preprocessor).
 *
 * In many cases it might be possible to use alternatives to this macro that
 * will make the code more readable.
 * For example, if the expression type is know (and contains no commas) the
 * type constructor can be used to wrap the expression command within
 * parenthesis <c>size_type(key_sizeof<int, double>::value)</c>.
 *
 * @Params
 * @Param{parenthesize_value,
 *  The value expression to be passed as macro parameter wrapped by a single
 *  set of round parenthesis <c>(...)</c>.
 *  This value expression can contain an arbitrary number of commas.
 * }
 * @EndParams
 *
 * @Note This macro works on C++03 compilers (it does not require variadic
 *  macros). This macro expands to code equivalent to
 *  <c>boost::aux::identity_value parenthesized_value</c> where:
 * @code
 *  namespace boost { namespace aux {
 *
 *  template<typename T>
 *  inline typename boost::add_reference<T>::type identity_value(
 *          typename boost::add_reference<T>::type value) {
 *      return value;
 *  }
 *
 *  }} // namespace boost::aux
 * @endcode
 *
 * @See @RefSect2{Advanced_Topics, Advanced Topics} section.
 */
#define BOOST_IDENTITY_VALUE(parenthesized_value) \
    /* must NOT prefix this with `::` to work with parenthesized syntax */ \
    boost::aux::identity_value parenthesized_value

#endif // #include guard

