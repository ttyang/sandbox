///////////////////////////////////////////////////////////////////////////////
// Operator traits
//
// (C) Copyright Terje Sletteb� and Tobias Schwinger 2004.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CT_OPERATOR_HAS_BITWISE_XOR_OP_HPP
#define BOOST_CT_OPERATOR_HAS_BITWISE_XOR_OP_HPP

#include <boost/mpl/and.hpp>
#include <boost/concept_traits/operator/detail/has_bitwise_binop.hpp>
#include <boost/concept_traits/operator/detail/unop.hpp>

namespace boost {

///////////////////////////////////////////////////////////////////////////////
// has_bitwise_xor_op
///////////////////////////////////////////////////////////////////////////////

BOOST_CT_OPERATOR_DETAIL_DEFINE_BINOP_TRAIT(has_bitwise_xor_op_impl, ^)

template<class T,class U = T>
struct has_bitwise_xor_op :
  mpl::and_<
    detail::has_bitwise_binop<T,U>,
    detail::has_bitwise_xor_op_impl<T,U>
  > {};

} // namespace boost

#endif // BOOST_CT_OPERATOR_HAS_BITWISE_XOR_OP_HPP
