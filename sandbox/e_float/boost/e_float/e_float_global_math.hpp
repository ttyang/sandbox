
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
    inline INT64 tol(void) { return static_cast<INT64>(e_float::ef_max_digits10); }
    inline e_float fabs(const e_float& x) { return (x.isneg() ? e_float(x).negate() : x); }
  }

  // Global operators post-increment and post-decrement.
  inline e_float operator++(e_float& u, int) { const e_float v(u); ++u; return v; }
  inline e_float operator--(e_float& u, int) { const e_float v(u); --u; return v; }

  // Global unary operators of e_float reference.
  inline       e_float  operator-(const e_float& u) { return e_float(u).negate(); }
  inline       e_float& operator+(      e_float& u) { return u; }
  inline const e_float& operator+(const e_float& u) { return u; }

  // Global add/sub/mul/div of const e_float& with const e_float&.
  inline e_float operator+(const e_float& u, const e_float& v) { return e_float(u) += v; }
  inline e_float operator-(const e_float& u, const e_float& v) { return e_float(u) -= v; }
  inline e_float operator*(const e_float& u, const e_float& v) { return e_float(u) *= v; }
  inline e_float operator/(const e_float& u, const e_float& v) { return e_float(u) /= v; }

  // Global add/sub/mul/div of const e_float& with all built-in types.
  inline e_float operator+(const e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).add_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator+(const e_float& u, const signed char n)        { return e_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator+(const e_float& u, const signed short n)       { return e_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator+(const e_float& u, const signed int n)         { return e_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator+(const e_float& u, const signed long n)        { return e_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator+(const e_float& u, const signed long long n)   { return e_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator+(const e_float& u, const unsigned char n)      { return e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator+(const e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).add_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator+(const e_float& u, const unsigned short n)     { return e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator+(const e_float& u, const unsigned int n)       { return e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator+(const e_float& u, const unsigned long n)      { return e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator+(const e_float& u, const unsigned long long n) { return e_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator+(const e_float& u, const float f)              { return e_float(u) += e_float(f); }
  inline e_float operator+(const e_float& u, const double d)             { return e_float(u) += e_float(d); }
  inline e_float operator+(const e_float& u, const long double ld)       { return e_float(u) += e_float(ld); }

  inline e_float operator-(const e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).sub_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator-(const e_float& u, const signed char n)        { return e_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator-(const e_float& u, const signed short n)       { return e_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator-(const e_float& u, const signed int n)         { return e_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator-(const e_float& u, const signed long n)        { return e_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator-(const e_float& u, const signed long long n)   { return e_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator-(const e_float& u, const unsigned char n)      { return e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator-(const e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).sub_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator-(const e_float& u, const unsigned short n)     { return e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator-(const e_float& u, const unsigned int n)       { return e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator-(const e_float& u, const unsigned long n)      { return e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator-(const e_float& u, const unsigned long long n) { return e_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator-(const e_float& u, const float f)              { return e_float(u) -= e_float(f); }
  inline e_float operator-(const e_float& u, const double d)             { return e_float(u) -= e_float(d); }
  inline e_float operator-(const e_float& u, const long double ld)       { return e_float(u) -= e_float(ld); }

  inline e_float operator*(const e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).mul_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator*(const e_float& u, const signed char n)        { return e_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator*(const e_float& u, const signed short n)       { return e_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator*(const e_float& u, const signed int n)         { return e_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator*(const e_float& u, const signed long n)        { return e_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator*(const e_float& u, const signed long long n)   { return e_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator*(const e_float& u, const unsigned char n)      { return e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator*(const e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).mul_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator*(const e_float& u, const unsigned short n)     { return e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator*(const e_float& u, const unsigned int n)       { return e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator*(const e_float& u, const unsigned long n)      { return e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator*(const e_float& u, const unsigned long long n) { return e_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator*(const e_float& u, const float f)              { return e_float(u) *= e_float(f); }
  inline e_float operator*(const e_float& u, const double d)             { return e_float(u) *= e_float(d); }
  inline e_float operator*(const e_float& u, const long double ld)       { return e_float(u) *= e_float(ld); }

  inline e_float operator/(const e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).div_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator/(const e_float& u, const signed char n)        { return e_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator/(const e_float& u, const signed short n)       { return e_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator/(const e_float& u, const signed int n)         { return e_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator/(const e_float& u, const signed long n)        { return e_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator/(const e_float& u, const signed long long n)   { return e_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
  inline e_float operator/(const e_float& u, const unsigned char n)      { return e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator/(const e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)) : e_float(u).div_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float operator/(const e_float& u, const unsigned short n)     { return e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator/(const e_float& u, const unsigned int n)       { return e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator/(const e_float& u, const unsigned long n)      { return e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator/(const e_float& u, const unsigned long long n) { return e_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
  inline e_float operator/(const e_float& u, const float f)              { return e_float(u) /= e_float(f); }
  inline e_float operator/(const e_float& u, const double d)             { return e_float(u) /= e_float(d); }
  inline e_float operator/(const e_float& u, const long double ld)       { return e_float(u) /= e_float(ld); }

  // Global add/sub/mul/div of all built-in types with const e_float&.
  inline e_float operator+(const char n, const e_float& u)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).add_unsigned_long_long(n) : e_float(u).add_signed_long_long(n)); }
  inline e_float operator+(const signed char n, const e_float& u)        { return e_float(u).add_signed_long_long(n); }
  inline e_float operator+(const signed short n, const e_float& u)       { return e_float(u).add_signed_long_long(n); }
  inline e_float operator+(const signed int n, const e_float& u)         { return e_float(u).add_signed_long_long(n); }
  inline e_float operator+(const signed long n, const e_float& u)        { return e_float(u).add_signed_long_long(n); }
  inline e_float operator+(const signed long long n, const e_float& u)   { return e_float(u).add_signed_long_long(n); }
  inline e_float operator+(const unsigned char n, const e_float& u)      { return e_float(u).add_unsigned_long_long(n); }
  inline e_float operator+(const wchar_t n, const e_float& u)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).add_unsigned_long_long(n) : e_float(u).add_signed_long_long(n)); }
  inline e_float operator+(const unsigned short n, const e_float& u)     { return e_float(u).add_unsigned_long_long(n); }
  inline e_float operator+(const unsigned int n, const e_float& u)       { return e_float(u).add_unsigned_long_long(n); }
  inline e_float operator+(const unsigned long n, const e_float& u)      { return e_float(u).add_unsigned_long_long(n); }
  inline e_float operator+(const unsigned long long n, const e_float& u) { return e_float(u).add_unsigned_long_long(n); }
  inline e_float operator+(const float f, const e_float& u)              { return e_float(f) += u; }
  inline e_float operator+(const double d, const e_float& u)             { return e_float(d) += u; }
  inline e_float operator+(const long double ld, const e_float& u)       { return e_float(ld) += u; }

  inline e_float operator-(const char n, const e_float& u)               { return e_float(n)  -= u; }
  inline e_float operator-(const signed char n, const e_float& u)        { return e_float(n)  -= u; }
  inline e_float operator-(const signed short n, const e_float& u)       { return e_float(n)  -= u; }
  inline e_float operator-(const signed int n, const e_float& u)         { return e_float(n)  -= u; }
  inline e_float operator-(const signed long n, const e_float& u)        { return e_float(n)  -= u; }
  inline e_float operator-(const signed long long n, const e_float& u)   { return e_float(n)  -= u; }
  inline e_float operator-(const unsigned char n, const e_float& u)      { return e_float(n)  -= u; }
  inline e_float operator-(const wchar_t n, const e_float& u)            { return e_float(n)  -= u; }
  inline e_float operator-(const unsigned short n, const e_float& u)     { return e_float(n)  -= u; }
  inline e_float operator-(const unsigned int n, const e_float& u)       { return e_float(n)  -= u; }
  inline e_float operator-(const unsigned long n, const e_float& u)      { return e_float(n)  -= u; }
  inline e_float operator-(const unsigned long long n, const e_float& u) { return e_float(n)  -= u; }
  inline e_float operator-(const float f, const e_float& u)              { return e_float(f)  -= u; }
  inline e_float operator-(const double d, const e_float& u)             { return e_float(d)  -= u; }
  inline e_float operator-(const long double ld, const e_float& u)       { return e_float(ld) -= u; }

  inline e_float operator*(const char n, const e_float& u)               { return ((!std::numeric_limits<char>::is_signed) ? e_float(u).mul_unsigned_long_long(n) : e_float(u).mul_signed_long_long(n)); }
  inline e_float operator*(const signed char n, const e_float& u)        { return e_float(u).mul_signed_long_long(n); }
  inline e_float operator*(const signed short n, const e_float& u)       { return e_float(u).mul_signed_long_long(n); }
  inline e_float operator*(const signed int n, const e_float& u)         { return e_float(u).mul_signed_long_long(n); }
  inline e_float operator*(const signed long n, const e_float& u)        { return e_float(u).mul_signed_long_long(n); }
  inline e_float operator*(const signed long long n, const e_float& u)   { return e_float(u).mul_signed_long_long(n); }
  inline e_float operator*(const unsigned char n, const e_float& u)      { return e_float(u).mul_unsigned_long_long(n); }
  inline e_float operator*(const wchar_t n, const e_float& u)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? e_float(u).mul_unsigned_long_long(n) : e_float(u).mul_signed_long_long(n)); }
  inline e_float operator*(const unsigned short n, const e_float& u)     { return e_float(u).mul_unsigned_long_long(n); }
  inline e_float operator*(const unsigned int n, const e_float& u)       { return e_float(u).mul_unsigned_long_long(n); }
  inline e_float operator*(const unsigned long n, const e_float& u)      { return e_float(u).mul_unsigned_long_long(n); }
  inline e_float operator*(const unsigned long long n, const e_float& u) { return e_float(u).mul_unsigned_long_long(n); }
  inline e_float operator*(const float f, const e_float& u)              { return e_float(f) *= u; }
  inline e_float operator*(const double d, const e_float& u)             { return e_float(d) *= u; }
  inline e_float operator*(const long double ld, const e_float& u)       { return e_float(ld) *= u; }

  inline e_float operator/(const char n, const e_float& u)               { return e_float(n)  /= u; }
  inline e_float operator/(const signed char n, const e_float& u)        { return e_float(n)  /= u; }
  inline e_float operator/(const signed short n, const e_float& u)       { return e_float(n)  /= u; }
  inline e_float operator/(const signed int n, const e_float& u)         { return e_float(n)  /= u; }
  inline e_float operator/(const signed long n, const e_float& u)        { return e_float(n)  /= u; }
  inline e_float operator/(const signed long long n, const e_float& u)   { return e_float(n)  /= u; }
  inline e_float operator/(const unsigned char n, const e_float& u)      { return e_float(n)  /= u; }
  inline e_float operator/(const wchar_t n, const e_float& u)            { return e_float(n)  /= u; }
  inline e_float operator/(const unsigned short n, const e_float& u)     { return e_float(n)  /= u; }
  inline e_float operator/(const unsigned int n, const e_float& u)       { return e_float(n)  /= u; }
  inline e_float operator/(const unsigned long n, const e_float& u)      { return e_float(n)  /= u; }
  inline e_float operator/(const unsigned long long n, const e_float& u) { return e_float(n)  /= u; }
  inline e_float operator/(const float f, const e_float& u)              { return e_float(f)  /= u; }
  inline e_float operator/(const double d, const e_float& u)             { return e_float(d)  /= u; }
  inline e_float operator/(const long double ld, const e_float& u)       { return e_float(ld) /= u; }

  // Global self add/sub/mul/div of e_float& with all built-in types.
  inline e_float& operator+=(e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.add_unsigned_long_long(static_cast<unsigned long long>(n)) : u.add_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator+=(e_float& u, const signed char n)        { return u.add_signed_long_long(n); }
  inline e_float& operator+=(e_float& u, const signed short n)       { return u.add_signed_long_long(n); }
  inline e_float& operator+=(e_float& u, const signed int n)         { return u.add_signed_long_long(n); }
  inline e_float& operator+=(e_float& u, const signed long n)        { return u.add_signed_long_long(n); }
  inline e_float& operator+=(e_float& u, const signed long long n)   { return u.add_signed_long_long(n); }
  inline e_float& operator+=(e_float& u, const unsigned char n)      { return u.add_unsigned_long_long(n); }
  inline e_float& operator+=(e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.add_unsigned_long_long(static_cast<unsigned long long>(n)) : u.add_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator+=(e_float& u, const unsigned short n)     { return u.add_unsigned_long_long(n); }
  inline e_float& operator+=(e_float& u, const unsigned int n)       { return u.add_unsigned_long_long(n); }
  inline e_float& operator+=(e_float& u, const unsigned long n)      { return u.add_unsigned_long_long(n); }
  inline e_float& operator+=(e_float& u, const unsigned long long n) { return u.add_unsigned_long_long(n); }
  inline e_float& operator+=(e_float& u, const float f)              { return u += e_float(f); }
  inline e_float& operator+=(e_float& u, const double d)             { return u += e_float(d); }
  inline e_float& operator+=(e_float& u, const long double ld)       { return u += e_float(ld); }

  inline e_float& operator-=(e_float& u, const signed char n)        { return ((!std::numeric_limits<char>::is_signed) ? u.sub_unsigned_long_long(static_cast<unsigned long long>(n)) : u.sub_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator-=(e_float& u, const signed short n)       { return u.sub_signed_long_long(n); }
  inline e_float& operator-=(e_float& u, const signed int n)         { return u.sub_signed_long_long(n); }
  inline e_float& operator-=(e_float& u, const signed long n)        { return u.sub_signed_long_long(n); }
  inline e_float& operator-=(e_float& u, const signed long long n)   { return u.sub_signed_long_long(n); }
  inline e_float& operator-=(e_float& u, const unsigned char n)      { return u.sub_unsigned_long_long(n); }
  inline e_float& operator-=(e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.sub_unsigned_long_long(static_cast<unsigned long long>(n)) : u.sub_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator-=(e_float& u, const unsigned short n)     { return u.sub_unsigned_long_long(n); }
  inline e_float& operator-=(e_float& u, const unsigned int n)       { return u.sub_unsigned_long_long(n); }
  inline e_float& operator-=(e_float& u, const unsigned long n)      { return u.sub_unsigned_long_long(n); }
  inline e_float& operator-=(e_float& u, const unsigned long long n) { return u.sub_unsigned_long_long(n); }
  inline e_float& operator-=(e_float& u, const float f)              { return u -= e_float(f); }
  inline e_float& operator-=(e_float& u, const double d)             { return u -= e_float(d); }
  inline e_float& operator-=(e_float& u, const long double ld)       { return u -= e_float(ld); }

  inline e_float& operator*=(e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.mul_unsigned_long_long(static_cast<unsigned long long>(n)) : u.mul_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator*=(e_float& u, const signed char n)        { return u.mul_signed_long_long(n); }
  inline e_float& operator*=(e_float& u, const signed short n)       { return u.mul_signed_long_long(n); }
  inline e_float& operator*=(e_float& u, const signed int n)         { return u.mul_signed_long_long(n); }
  inline e_float& operator*=(e_float& u, const signed long n)        { return u.mul_signed_long_long(n); }
  inline e_float& operator*=(e_float& u, const signed long long n)   { return u.mul_signed_long_long(n); }
  inline e_float& operator*=(e_float& u, const unsigned char n)      { return u.mul_unsigned_long_long(n); }
  inline e_float& operator*=(e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.mul_unsigned_long_long(static_cast<unsigned long long>(n)) : u.mul_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator*=(e_float& u, const unsigned short n)     { return u.mul_unsigned_long_long(n); }
  inline e_float& operator*=(e_float& u, const unsigned int n)       { return u.mul_unsigned_long_long(n); }
  inline e_float& operator*=(e_float& u, const unsigned long n)      { return u.mul_unsigned_long_long(n); }
  inline e_float& operator*=(e_float& u, const unsigned long long n) { return u.mul_unsigned_long_long(n); }
  inline e_float& operator*=(e_float& u, const float f)              { return u *= e_float(f); }
  inline e_float& operator*=(e_float& u, const double d)             { return u *= e_float(d); }
  inline e_float& operator*=(e_float& u, const long double ld)       { return u *= e_float(ld); }

  inline e_float& operator/=(e_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.div_unsigned_long_long(static_cast<unsigned long long>(n)) : u.div_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator/=(e_float& u, const signed char n)        { return u.div_signed_long_long(n); }
  inline e_float& operator/=(e_float& u, const signed short n)       { return u.div_signed_long_long(n); }
  inline e_float& operator/=(e_float& u, const signed int n)         { return u.div_signed_long_long(n); }
  inline e_float& operator/=(e_float& u, const signed long n)        { return u.div_signed_long_long(n); }
  inline e_float& operator/=(e_float& u, const signed long long n)   { return u.div_signed_long_long(n); }
  inline e_float& operator/=(e_float& u, const unsigned char n)      { return u.div_unsigned_long_long(n); }
  inline e_float& operator/=(e_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.div_unsigned_long_long(static_cast<unsigned long long>(n)) : u.div_signed_long_long(static_cast<signed long long>(n))); }
  inline e_float& operator/=(e_float& u, const unsigned short n)     { return u.div_unsigned_long_long(n); }
  inline e_float& operator/=(e_float& u, const unsigned int n)       { return u.div_unsigned_long_long(n); }
  inline e_float& operator/=(e_float& u, const unsigned long n)      { return u.div_unsigned_long_long(n); }
  inline e_float& operator/=(e_float& u, const unsigned long long n) { return u.div_unsigned_long_long(n); }
  inline e_float& operator/=(e_float& u, const float f)              { return u /= e_float(f); }
  inline e_float& operator/=(e_float& u, const double d)             { return u /= e_float(d); }
  inline e_float& operator/=(e_float& u, const long double ld)       { return u /= e_float(ld); }

  // Global comparison operators of const e_float& with const e_float&.
  inline bool operator< (const e_float& u, const e_float& v) { return (u.cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const e_float& v) { return (u.cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const e_float& v) { return (u.cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const e_float& v) { return (u.cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const e_float& v) { return (u.cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const e_float& v) { return (u.cmp(v) >  static_cast<INT32>(0)); }

  // Global comparison operators of const e_float& with all built-in types.
  inline bool operator< (const e_float& u, const char v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const char v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const char v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const char v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const char v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const char v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const wchar_t v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const signed char v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const signed char v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const signed char v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const signed char v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const signed char v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const signed char v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const signed short v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const signed short v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const signed short v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const signed short v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const signed short v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const signed short v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const signed int v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const signed int v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const signed int v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const signed int v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const signed int v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const signed int v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const signed long v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const signed long v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const signed long v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const signed long v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const signed long v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const signed long v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const signed long long v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const unsigned char v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const unsigned short v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const unsigned int v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const unsigned long v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const unsigned long long v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const float v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const float v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const float v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const float v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const float v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const float v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const double v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const double v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const double v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const double v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const double v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const double v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  inline bool operator< (const e_float& u, const long double v) { return (u.cmp(e_float(v)) <  static_cast<INT32>(0)); }
  inline bool operator<=(const e_float& u, const long double v) { return (u.cmp(e_float(v)) <= static_cast<INT32>(0)); }
  inline bool operator==(const e_float& u, const long double v) { return (u.cmp(e_float(v)) == static_cast<INT32>(0)); }
  inline bool operator!=(const e_float& u, const long double v) { return (u.cmp(e_float(v)) != static_cast<INT32>(0)); }
  inline bool operator>=(const e_float& u, const long double v) { return (u.cmp(e_float(v)) >= static_cast<INT32>(0)); }
  inline bool operator> (const e_float& u, const long double v) { return (u.cmp(e_float(v)) >  static_cast<INT32>(0)); }

  // Global comparison operators of all built-in types with const e_float&.
  inline bool operator< (const char u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const char u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const char u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const char u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const char u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const char u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const wchar_t u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const signed char u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const signed char u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const signed char u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const signed char u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const signed char u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const signed char u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const signed short u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const signed short u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const signed short u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const signed short u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const signed short u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const signed short u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const signed int u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const signed int u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const signed int u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const signed int u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const signed int u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const signed int u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const signed long u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const signed long u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const signed long u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const signed long u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const signed long u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const signed long u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const signed long long u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const signed long long u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const signed long long u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const signed long long u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const signed long long u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const signed long long u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const unsigned char u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const unsigned short u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const unsigned int u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const unsigned long u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const unsigned long long u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const float u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const float u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const float u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const float u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const float u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const float u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const double u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const double u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const double u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const double u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const double u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const double u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

  inline bool operator< (const long double u, const e_float& v) { return (e_float(u).cmp(v) <  static_cast<INT32>(0)); }
  inline bool operator<=(const long double u, const e_float& v) { return (e_float(u).cmp(v) <= static_cast<INT32>(0)); }
  inline bool operator==(const long double u, const e_float& v) { return (e_float(u).cmp(v) == static_cast<INT32>(0)); }
  inline bool operator!=(const long double u, const e_float& v) { return (e_float(u).cmp(v) != static_cast<INT32>(0)); }
  inline bool operator>=(const long double u, const e_float& v) { return (e_float(u).cmp(v) >= static_cast<INT32>(0)); }
  inline bool operator> (const long double u, const e_float& v) { return (e_float(u).cmp(v) >  static_cast<INT32>(0)); }

#endif // _E_FLOAT_GLOBAL_MATH_HPP_
