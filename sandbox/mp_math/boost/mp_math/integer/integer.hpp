// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_INTEGER_HPP
#define BOOST_MP_MATH_INTEGER_INTEGER_HPP

#include <boost/config.hpp>

namespace boost {
namespace mp_math {

template<class Type>
struct integer : Type
{
  typedef Type type;
  typedef typename type::traits_type            traits_type;
  typedef typename type::digit_type             digit_type;
  typedef typename type::size_type              size_type;
  typedef typename type::iterator               iterator;
  typedef typename type::const_iterator         const_iterator;
  typedef typename type::reverse_iterator       reverse_iterator;
  typedef typename type::const_reverse_iterator const_reverse_iterator;

  integer(){}

  #if !defined(BOOST_NO_VARIADIC_TEMPLATES) && !defined(BOOST_NO_RVALUE_REFERENCES)
  template<typename... Args>
  integer(Args&&... args)
  :
    type(args...)
  {}

  #else

  template<typename T1>
  integer(const T1& t1)
  : type(t1) {}

  template<typename T1, typename T2>
  integer(const T1& t1, const T2& t2)
  : type(t1, t2) {}

  template<typename T1, typename T2, typename T3>
  integer(const T1& t1, const T2& t2, const T3& t3)
  : type(t1, t2, t3) {}

  template<typename T1, typename T2, typename T3, typename T4>
  integer(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
  : type(t1, t2, t3, t4) {}

  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  integer(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5)
  : type(t1, t2, t3, t4, t5) {}
  #endif

  template<typename T>
  #ifndef BOOST_NO_RVALUE_REFERENCES
  integer& operator = (T&& t)
  #else
  integer& operator = (const T& t)
  #endif
  {
    type::operator=(t);
    return *this;
  }

  operator type&       ()       { return *this; }
  operator const type& () const { return *this; }
};


template<class Type>
struct modpow_ctx<integer<Type> >
:
  modpow_ctx<Type>
{};

// returns base^exp % mod
template<class Type>
inline
integer<Type> modpow(const integer<Type>& base,
                     const integer<Type>& exp,
                     const integer<Type>& mod,
                     modpow_ctx<integer<Type> >* ctx = 0)
{
  return modpow(static_cast<const Type&>(base),
                static_cast<const Type&>(exp),
                static_cast<const Type&>(mod),
                static_cast<modpow_ctx<Type>*>(ctx));
}


} // namespace mp_math
} // namespace boost

#endif
