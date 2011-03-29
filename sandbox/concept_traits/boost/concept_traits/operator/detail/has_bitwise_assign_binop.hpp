///////////////////////////////////////////////////////////////////////////////
// Operator traits
//
// (C) Copyright Terje Sletteb� and Tobias Schwinger 2004.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CT_OPERATOR_DETAIL_HAS_BITWISE_ASSIGN_BINOP_HPP
#define BOOST_CT_OPERATOR_DETAIL_HAS_BITWISE_ASSIGN_BINOP_HPP

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/concept_traits/operator/detail/is_not_const.hpp>
#include <boost/concept_traits/operator/detail/is_integral_or_enum.hpp>
#include <boost/concept_traits/operator/detail/either_is_class_or_union_and_not_void.hpp>

namespace boost {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
// has_bitwise_assign_binop
///////////////////////////////////////////////////////////////////////////////

template<class T,class U>
struct has_bitwise_assign_binop :
  mpl::and_<
    detail::is_not_const<typename remove_reference<T>::type>,
    mpl::or_<
      mpl::and_<
        is_integral<typename remove_reference<T>::type>,
        detail::is_integral_or_enum<typename remove_reference<U>::type>
      >,
      detail::either_is_class_or_union_and_not_void<T,U>
    >
  > {};

} // namespace detail
} // namespace boost

#endif // BOOST_CT_OPERATOR_DETAIL_HAS_BITWISE_ASSIGN_BINOP_HPP