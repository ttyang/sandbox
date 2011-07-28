
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_GLOBAL_MATH_HPP_
  #define _E_FLOAT_GLOBAL_MATH_HPP_

  namespace ef
  {
    inline INT64 tol(void) { return static_cast<INT64>(e_float::ef_digits10_tol); }
    inline e_float fabs(const e_float& x) { return (x.isneg() ? e_float(x).negate() : x); }
  }

  // Global operators post-increment and post-decrement
  inline e_float operator++(e_float& u, int) { const e_float v(u); ++u; return v; }
  inline e_float operator--(e_float& u, int) { const e_float v(u); --u; return v; }

  // Global unary operators of e_float reference.
  inline       e_float  operator-(const e_float& u) { return e_float(u).negate(); }
  inline       e_float& operator+(      e_float& u) { return u; }
  inline const e_float& operator+(const e_float& u) { return u; }

  // Global add/sub/mul/div of const e_float reference with const e_float reference
  inline e_float operator+(const e_float& u, const e_float& v) { return e_float(u) += v; }
  inline e_float operator-(const e_float& u, const e_float& v) { return e_float(u) -= v; }
  inline e_float operator*(const e_float& u, const e_float& v) { return e_float(u) *= v; }
  inline e_float operator/(const e_float& u, const e_float& v) { return e_float(u) /= v; }

  // Specialization for global add/sub/mul/div of const e_float reference with INT32
  inline e_float operator+(const e_float& u, const INT32 n) { return (e_float(u) += e_float(n)); }
  inline e_float operator-(const e_float& u, const INT32 n) { return (e_float(u) -= e_float(n)); }
  inline e_float operator*(const e_float& u, const INT32 n) { return  e_float(u).mul_by_int(n); }
  inline e_float operator/(const e_float& u, const INT32 n) { return  e_float(u).div_by_int(n); }

  inline e_float operator+(const INT32 n, const e_float& u) { return (e_float(n) += u); }
  inline e_float operator-(const INT32 n, const e_float& u) { return (e_float(n) -= u); }
  inline e_float operator*(const INT32 n, const e_float& u) { return (e_float(n) *= u); }
  inline e_float operator/(const INT32 n, const e_float& u) { return (e_float(n) /= u); }

  // Specializations of global self-add/sub/mul-div of e_float reference with INT32
  inline e_float& operator+=(e_float& u, const INT32 n) { return (u += e_float(n)); }
  inline e_float& operator-=(e_float& u, const INT32 n) { return (u -= e_float(n)); }
  inline e_float& operator*=(e_float& u, const INT32 n) { return u.mul_by_int(n); }
  inline e_float& operator/=(e_float& u, const INT32 n) { return u.div_by_int(n); }

  // Global comparison operators of const e_float reference with const e_float reference
  inline bool operator< (const e_float& u, const e_float& v) { return (u.cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const e_float& v) { return (u.cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const e_float& v) { return (u.cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const e_float& v) { return (u.cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const e_float& v) { return (u.cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const e_float& v) { return (u.cmp(v) >  static_cast<INT32>(0)); }

#endif // _E_FLOAT_GLOBAL_MATH_HPP_
