//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2009-2011. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/conversion for documentation.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @file
 * @brief Defines the type trait @c is_move_constructible.
 */


#ifndef BOOST_CONVERSION_TT_IS_MOVE_CONSTRUCTIBLE_HPP
#define BOOST_CONVERSION_TT_IS_MOVE_CONSTRUCTIBLE_HPP

#include <boost/conversion/type_traits/is_constructible.hpp>
#include <boost/conversion/type_traits/is_copy_constructible.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost {

  /**
   * States if @c T is move constructible.
   *
   * Condition: <c>is_constructible<T, T&&>::value</c> is @c true.
   *
   * @Requires @c T must be a complete type, (possibly cv-qualified) void, or an array of unknown bound.
   */
  template <class T>
  struct is_move_constructible :
#if ! defined BOOST_NO_RVALUE_REFERENCES
    is_constructible<T, typename add_rvalue_reference<T>::type>
#else
    is_copy_constructible<T>
#endif
    {};

#if !defined(BOOST_CONVERSION_DOXYGEN_INVOKED)
  template <>
  struct is_move_constructible<void> : false_type {};
//  template <typename T>
//  struct is_move_constructible<T&> : true_type {};
//  template <typename T>
//  struct is_move_constructible<T[]> : false_type {};
//  template <typename T, std::size_t N>
//  struct is_move_constructible<T[N]> : false_type {};
#endif

}


#endif

