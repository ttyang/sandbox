// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_UNBOUNDED_TRAITS_HPP
#define BOOST_MP_MATH_INTEGER_UNBOUNDED_TRAITS_HPP

#include <cstddef> // size_t
#include <limits>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/lower_bound.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mp_math/integer/detail/base/primitive_ops.hpp>


namespace boost {
namespace mp_math {

namespace detail {

typedef mpl::vector<
  unsigned char,
  unsigned short,
  unsigned int,
  unsigned long int
  #ifdef BOOST_HAS_LONG_LONG
  ,
  unsigned long long int
  #endif
> unsigned_type_vec;

template<typename T1, typename T2>
struct cmp_digits
:
mpl::bool_<
  std::numeric_limits<T1>::digits < std::numeric_limits<T2>::digits/2
>
{
};

// we could also choose unsigned int (since this is propably the
// fastest unsigned integer type) as digit_type then
// try to find a larger type as word_type
// if none exists set unsigned int as word_type and choose next
// smaller type as digit_type
struct choose
{
  typedef mpl::back<unsigned_type_vec>::type word_type;
  typedef mpl::deref<
      mpl::lower_bound<
        unsigned_type_vec, word_type, cmp_digits<mpl::_1,mpl::_2>
        >::type
      >::type digit_type;
};

} // namespace detail


template<
  typename DigitT = detail::choose::digit_type,
  typename WordT = detail::choose::word_type,
  typename SizeT = std::size_t,
  bool debug = false
>
struct unbounded_traits
{
  BOOST_STATIC_ASSERT(
    std::numeric_limits<DigitT>::digits <= std::numeric_limits<WordT>::digits/2
  );

  typedef DigitT digit_type;
  typedef WordT  word_type;
  typedef SizeT  size_type;

#ifdef BOOST_MP_MATH_PRIMITIVE_OPS_OLD
  typedef detail::base::primitive_ops<
    digit_type, word_type, size_type> ops_type;
#else
  typedef detail::base::primitive_ops<digit_type, size_type> ops_type;
#endif

  static const bool enable_debug_mode = debug;

  static const size_type radix_bits = std::numeric_limits<digit_type>::digits;
  static const size_type digit_bits = std::numeric_limits<digit_type>::digits;
  static const digit_type max_digit_value = static_cast<digit_type>(-1);

  static size_type toom_mul_threshold;
  static size_type toom_sqr_threshold;
  static size_type karatsuba_mul_threshold;
  static size_type karatsuba_sqr_threshold;
};


template<typename D, typename W, typename S, bool b>
typename unbounded_traits<D,W,S,b>::size_type
unbounded_traits<D,W,S,b>::toom_mul_threshold = 350;

template<typename D, typename W, typename S, bool b>
typename unbounded_traits<D,W,S,b>::size_type
unbounded_traits<D,W,S,b>::toom_sqr_threshold = 400;

template<typename D, typename W, typename S, bool b>
typename unbounded_traits<D,W,S,b>::size_type
unbounded_traits<D,W,S,b>::karatsuba_mul_threshold = 80;

template<typename D, typename W, typename S, bool b>
typename unbounded_traits<D,W,S,b>::size_type
unbounded_traits<D,W,S,b>::karatsuba_sqr_threshold = 120;



} // namespace mp_math
} // namespace boost

#endif

