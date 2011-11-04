
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_FLOAT_2004_02_08_HPP_
  #define _MP_FLOAT_2004_02_08_HPP_

  #include <limits>

  // Select the mp_float back-end big-number type
  // by defining BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_xxx, for example,
  // as a compiler defined preprocessor macro.

  #if defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX)
    #include <boost/multiprecision/mp_float_efx.hpp>
  #elif defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_GMP)
    #include <boost/multiprecision/mp_float_gmp.hpp>
  #elif defined(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_MPFR)
    #include <boost/multiprecision/mp_float_mpfr.hpp>
  #else
    #error mp_float type undefined!
  #endif

  namespace boost
  {
    namespace multiprecision
    {
      const mp_float& zero     (void);
      const mp_float& one      (void);
      const mp_float& half     (void);
      const mp_float& value_min(void);
      const mp_float& value_max(void);
      const mp_float& value_eps(void);
      const mp_float& value_inf(void);
      const mp_float& value_nan(void);
    }
  }

  // Specialization of std::numeric_limits<mp_float>.
  namespace std
  {
    template <> class numeric_limits<boost::multiprecision::mp_float>
    {
    public:
      static const bool                    is_specialized    = true;
      static const bool                    is_signed         = true;
      static const bool                    is_integer        = false;
      static const bool                    is_exact          = false;
      static const bool                    is_bounded        = true;
      static const bool                    is_modulo         = false;
      static const bool                    is_iec559         = false;
      static const int                     digits            = boost::multiprecision::mp_float::mp_float_digits;
      static const int                     digits10          = boost::multiprecision::mp_float::mp_float_digits10;
      static const int                     max_digits10      = boost::multiprecision::mp_float::mp_float_digits10 + 1;
      static const boost::int64_t          min_exponent      = boost::multiprecision::mp_float::mp_float_min_exp;      // Type differs from int.
      static const boost::int64_t          min_exponent10    = boost::multiprecision::mp_float::mp_float_min_exp10;    // Type differs from int.
      static const boost::int64_t          max_exponent      = boost::multiprecision::mp_float::mp_float_max_exp;      // Type differs from int.
      static const boost::int64_t          max_exponent10    = boost::multiprecision::mp_float::mp_float_max_exp10;    // Type differs from int.
      static const int                     radix             = boost::multiprecision::mp_float::mp_radix;
      static const std::float_round_style  round_style       = std::round_to_nearest;
      static const bool                    has_infinity      = true;
      static const bool                    has_quiet_NaN     = true;
      static const bool                    has_signaling_NaN = false;
      static const std::float_denorm_style has_denorm        = std::denorm_absent;
      static const bool                    has_denorm_loss   = false;
      static const bool                    traps             = false;
      static const bool                    tinyness_before   = false;

      static const boost::multiprecision::mp_float& (min)        (void) throw() { return boost::multiprecision::value_min(); }
      static const boost::multiprecision::mp_float& (max)        (void) throw() { return boost::multiprecision::value_max(); }
      static const boost::multiprecision::mp_float& lowest       (void) throw() { return boost::multiprecision::zero(); }
      static const boost::multiprecision::mp_float& epsilon      (void) throw() { return boost::multiprecision::value_eps(); }
      static const boost::multiprecision::mp_float& round_error  (void) throw() { return boost::multiprecision::half(); }
      static const boost::multiprecision::mp_float& infinity     (void) throw() { return boost::multiprecision::value_inf(); }
      static const boost::multiprecision::mp_float& quiet_NaN    (void) throw() { return boost::multiprecision::value_nan(); }
      static const boost::multiprecision::mp_float& signaling_NaN(void) throw() { return boost::multiprecision::zero(); }
      static const boost::multiprecision::mp_float& denorm_min   (void) throw() { return boost::multiprecision::zero(); }
    };
  }

  namespace boost
  {
    namespace multiprecision
    {
      // Global operators post-increment and post-decrement.
      inline mp_float operator++(mp_float& u, int) { const mp_float v(u); ++u; return v; }
      inline mp_float operator--(mp_float& u, int) { const mp_float v(u); --u; return v; }

      // Global unary operators of mp_float reference.
      inline       mp_float  operator-(const mp_float& u) { return mp_float(u).negate(); }
      inline       mp_float& operator+(      mp_float& u) { return u; }
      inline const mp_float& operator+(const mp_float& u) { return u; }

      // Global add/sub/mul/div of const mp_float& with const mp_float&.
      inline mp_float operator+(const mp_float& u, const mp_float& v) { return mp_float(u) += v; }
      inline mp_float operator-(const mp_float& u, const mp_float& v) { return mp_float(u) -= v; }
      inline mp_float operator*(const mp_float& u, const mp_float& v) { return mp_float(u) *= v; }
      inline mp_float operator/(const mp_float& u, const mp_float& v) { return mp_float(u) /= v; }

      // Global add/sub/mul/div of const mp_float& with all built-in types.
      inline mp_float operator+(const mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).add_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator+(const mp_float& u, const signed char n)        { return mp_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator+(const mp_float& u, const signed short n)       { return mp_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator+(const mp_float& u, const int n)                { return mp_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator+(const mp_float& u, const signed long n)        { return mp_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator+(const mp_float& u, const signed long long n)   { return mp_float(u).add_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator+(const mp_float& u, const unsigned char n)      { return mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator+(const mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).add_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator+(const mp_float& u, const unsigned short n)     { return mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator+(const mp_float& u, const unsigned int n)       { return mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator+(const mp_float& u, const unsigned long n)      { return mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator+(const mp_float& u, const unsigned long long n) { return mp_float(u).add_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator+(const mp_float& u, const float f)              { return mp_float(u) += mp_float(f); }
      inline mp_float operator+(const mp_float& u, const double d)             { return mp_float(u) += mp_float(d); }
      inline mp_float operator+(const mp_float& u, const long double ld)       { return mp_float(u) += mp_float(ld); }

      inline mp_float operator-(const mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).sub_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator-(const mp_float& u, const signed char n)        { return mp_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator-(const mp_float& u, const signed short n)       { return mp_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator-(const mp_float& u, const int n)                { return mp_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator-(const mp_float& u, const signed long n)        { return mp_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator-(const mp_float& u, const signed long long n)   { return mp_float(u).sub_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator-(const mp_float& u, const unsigned char n)      { return mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator-(const mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).sub_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator-(const mp_float& u, const unsigned short n)     { return mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator-(const mp_float& u, const unsigned int n)       { return mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator-(const mp_float& u, const unsigned long n)      { return mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator-(const mp_float& u, const unsigned long long n) { return mp_float(u).sub_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator-(const mp_float& u, const float f)              { return mp_float(u) -= mp_float(f); }
      inline mp_float operator-(const mp_float& u, const double d)             { return mp_float(u) -= mp_float(d); }
      inline mp_float operator-(const mp_float& u, const long double ld)       { return mp_float(u) -= mp_float(ld); }

      inline mp_float operator*(const mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).mul_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator*(const mp_float& u, const signed char n)        { return mp_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator*(const mp_float& u, const signed short n)       { return mp_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator*(const mp_float& u, const int n)                { return mp_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator*(const mp_float& u, const signed long n)        { return mp_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator*(const mp_float& u, const signed long long n)   { return mp_float(u).mul_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator*(const mp_float& u, const unsigned char n)      { return mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator*(const mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).mul_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator*(const mp_float& u, const unsigned short n)     { return mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator*(const mp_float& u, const unsigned int n)       { return mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator*(const mp_float& u, const unsigned long n)      { return mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator*(const mp_float& u, const unsigned long long n) { return mp_float(u).mul_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator*(const mp_float& u, const float f)              { return mp_float(u) *= mp_float(f); }
      inline mp_float operator*(const mp_float& u, const double d)             { return mp_float(u) *= mp_float(d); }
      inline mp_float operator*(const mp_float& u, const long double ld)       { return mp_float(u) *= mp_float(ld); }

      inline mp_float operator/(const mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).div_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator/(const mp_float& u, const signed char n)        { return mp_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator/(const mp_float& u, const signed short n)       { return mp_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator/(const mp_float& u, const int n)                { return mp_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator/(const mp_float& u, const signed long n)        { return mp_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator/(const mp_float& u, const signed long long n)   { return mp_float(u).div_signed_long_long(static_cast<signed long long>(n)); }
      inline mp_float operator/(const mp_float& u, const unsigned char n)      { return mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator/(const mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)) : mp_float(u).div_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float operator/(const mp_float& u, const unsigned short n)     { return mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator/(const mp_float& u, const unsigned int n)       { return mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator/(const mp_float& u, const unsigned long n)      { return mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator/(const mp_float& u, const unsigned long long n) { return mp_float(u).div_unsigned_long_long(static_cast<unsigned long long>(n)); }
      inline mp_float operator/(const mp_float& u, const float f)              { return mp_float(u) /= mp_float(f); }
      inline mp_float operator/(const mp_float& u, const double d)             { return mp_float(u) /= mp_float(d); }
      inline mp_float operator/(const mp_float& u, const long double ld)       { return mp_float(u) /= mp_float(ld); }

      // Global add/sub/mul/div of all built-in types with const mp_float&.
      inline mp_float operator+(const char n, const mp_float& u)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).add_unsigned_long_long(n) : mp_float(u).add_signed_long_long(n)); }
      inline mp_float operator+(const signed char n, const mp_float& u)        { return mp_float(u).add_signed_long_long(n); }
      inline mp_float operator+(const signed short n, const mp_float& u)       { return mp_float(u).add_signed_long_long(n); }
      inline mp_float operator+(const int n, const mp_float& u)                { return mp_float(u).add_signed_long_long(n); }
      inline mp_float operator+(const signed long n, const mp_float& u)        { return mp_float(u).add_signed_long_long(n); }
      inline mp_float operator+(const signed long long n, const mp_float& u)   { return mp_float(u).add_signed_long_long(n); }
      inline mp_float operator+(const unsigned char n, const mp_float& u)      { return mp_float(u).add_unsigned_long_long(n); }
      inline mp_float operator+(const wchar_t n, const mp_float& u)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).add_unsigned_long_long(n) : mp_float(u).add_signed_long_long(n)); }
      inline mp_float operator+(const unsigned short n, const mp_float& u)     { return mp_float(u).add_unsigned_long_long(n); }
      inline mp_float operator+(const unsigned int n, const mp_float& u)       { return mp_float(u).add_unsigned_long_long(n); }
      inline mp_float operator+(const unsigned long n, const mp_float& u)      { return mp_float(u).add_unsigned_long_long(n); }
      inline mp_float operator+(const unsigned long long n, const mp_float& u) { return mp_float(u).add_unsigned_long_long(n); }
      inline mp_float operator+(const float f, const mp_float& u)              { return mp_float(f) += u; }
      inline mp_float operator+(const double d, const mp_float& u)             { return mp_float(d) += u; }
      inline mp_float operator+(const long double ld, const mp_float& u)       { return mp_float(ld) += u; }

      inline mp_float operator-(const char n, const mp_float& u)               { return mp_float(n)  -= u; }
      inline mp_float operator-(const signed char n, const mp_float& u)        { return mp_float(n)  -= u; }
      inline mp_float operator-(const signed short n, const mp_float& u)       { return mp_float(n)  -= u; }
      inline mp_float operator-(const int n, const mp_float& u)                { return mp_float(n)  -= u; }
      inline mp_float operator-(const signed long n, const mp_float& u)        { return mp_float(n)  -= u; }
      inline mp_float operator-(const signed long long n, const mp_float& u)   { return mp_float(n)  -= u; }
      inline mp_float operator-(const unsigned char n, const mp_float& u)      { return mp_float(n)  -= u; }
      inline mp_float operator-(const wchar_t n, const mp_float& u)            { return mp_float(n)  -= u; }
      inline mp_float operator-(const unsigned short n, const mp_float& u)     { return mp_float(n)  -= u; }
      inline mp_float operator-(const unsigned int n, const mp_float& u)       { return mp_float(n)  -= u; }
      inline mp_float operator-(const unsigned long n, const mp_float& u)      { return mp_float(n)  -= u; }
      inline mp_float operator-(const unsigned long long n, const mp_float& u) { return mp_float(n)  -= u; }
      inline mp_float operator-(const float f, const mp_float& u)              { return mp_float(f)  -= u; }
      inline mp_float operator-(const double d, const mp_float& u)             { return mp_float(d)  -= u; }
      inline mp_float operator-(const long double ld, const mp_float& u)       { return mp_float(ld) -= u; }

      inline mp_float operator*(const char n, const mp_float& u)               { return ((!std::numeric_limits<char>::is_signed) ? mp_float(u).mul_unsigned_long_long(n) : mp_float(u).mul_signed_long_long(n)); }
      inline mp_float operator*(const signed char n, const mp_float& u)        { return mp_float(u).mul_signed_long_long(n); }
      inline mp_float operator*(const signed short n, const mp_float& u)       { return mp_float(u).mul_signed_long_long(n); }
      inline mp_float operator*(const int n, const mp_float& u)                { return mp_float(u).mul_signed_long_long(n); }
      inline mp_float operator*(const signed long n, const mp_float& u)        { return mp_float(u).mul_signed_long_long(n); }
      inline mp_float operator*(const signed long long n, const mp_float& u)   { return mp_float(u).mul_signed_long_long(n); }
      inline mp_float operator*(const unsigned char n, const mp_float& u)      { return mp_float(u).mul_unsigned_long_long(n); }
      inline mp_float operator*(const wchar_t n, const mp_float& u)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? mp_float(u).mul_unsigned_long_long(n) : mp_float(u).mul_signed_long_long(n)); }
      inline mp_float operator*(const unsigned short n, const mp_float& u)     { return mp_float(u).mul_unsigned_long_long(n); }
      inline mp_float operator*(const unsigned int n, const mp_float& u)       { return mp_float(u).mul_unsigned_long_long(n); }
      inline mp_float operator*(const unsigned long n, const mp_float& u)      { return mp_float(u).mul_unsigned_long_long(n); }
      inline mp_float operator*(const unsigned long long n, const mp_float& u) { return mp_float(u).mul_unsigned_long_long(n); }
      inline mp_float operator*(const float f, const mp_float& u)              { return mp_float(f) *= u; }
      inline mp_float operator*(const double d, const mp_float& u)             { return mp_float(d) *= u; }
      inline mp_float operator*(const long double ld, const mp_float& u)       { return mp_float(ld) *= u; }

      inline mp_float operator/(const char n, const mp_float& u)               { return mp_float(n)  /= u; }
      inline mp_float operator/(const signed char n, const mp_float& u)        { return mp_float(n)  /= u; }
      inline mp_float operator/(const signed short n, const mp_float& u)       { return mp_float(n)  /= u; }
      inline mp_float operator/(const int n, const mp_float& u)                { return mp_float(n)  /= u; }
      inline mp_float operator/(const signed long n, const mp_float& u)        { return mp_float(n)  /= u; }
      inline mp_float operator/(const signed long long n, const mp_float& u)   { return mp_float(n)  /= u; }
      inline mp_float operator/(const unsigned char n, const mp_float& u)      { return mp_float(n)  /= u; }
      inline mp_float operator/(const wchar_t n, const mp_float& u)            { return mp_float(n)  /= u; }
      inline mp_float operator/(const unsigned short n, const mp_float& u)     { return mp_float(n)  /= u; }
      inline mp_float operator/(const unsigned int n, const mp_float& u)       { return mp_float(n)  /= u; }
      inline mp_float operator/(const unsigned long n, const mp_float& u)      { return mp_float(n)  /= u; }
      inline mp_float operator/(const unsigned long long n, const mp_float& u) { return mp_float(n)  /= u; }
      inline mp_float operator/(const float f, const mp_float& u)              { return mp_float(f)  /= u; }
      inline mp_float operator/(const double d, const mp_float& u)             { return mp_float(d)  /= u; }
      inline mp_float operator/(const long double ld, const mp_float& u)       { return mp_float(ld) /= u; }

      // Global self add/sub/mul/div of mp_float& with all built-in types.
      inline mp_float& operator+=(mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.add_unsigned_long_long(static_cast<unsigned long long>(n)) : u.add_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator+=(mp_float& u, const signed char n)        { return u.add_signed_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const signed short n)       { return u.add_signed_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const int n)                { return u.add_signed_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const signed long n)        { return u.add_signed_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const signed long long n)   { return u.add_signed_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const unsigned char n)      { return u.add_unsigned_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.add_unsigned_long_long(static_cast<unsigned long long>(n)) : u.add_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator+=(mp_float& u, const unsigned short n)     { return u.add_unsigned_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const unsigned int n)       { return u.add_unsigned_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const unsigned long n)      { return u.add_unsigned_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const unsigned long long n) { return u.add_unsigned_long_long(n); }
      inline mp_float& operator+=(mp_float& u, const float f)              { return u += mp_float(f); }
      inline mp_float& operator+=(mp_float& u, const double d)             { return u += mp_float(d); }
      inline mp_float& operator+=(mp_float& u, const long double ld)       { return u += mp_float(ld); }

      inline mp_float& operator-=(mp_float& u, const signed char n)        { return ((!std::numeric_limits<char>::is_signed) ? u.sub_unsigned_long_long(static_cast<unsigned long long>(n)) : u.sub_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator-=(mp_float& u, const signed short n)       { return u.sub_signed_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const int n)                { return u.sub_signed_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const signed long n)        { return u.sub_signed_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const signed long long n)   { return u.sub_signed_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const unsigned char n)      { return u.sub_unsigned_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.sub_unsigned_long_long(static_cast<unsigned long long>(n)) : u.sub_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator-=(mp_float& u, const unsigned short n)     { return u.sub_unsigned_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const unsigned int n)       { return u.sub_unsigned_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const unsigned long n)      { return u.sub_unsigned_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const unsigned long long n) { return u.sub_unsigned_long_long(n); }
      inline mp_float& operator-=(mp_float& u, const float f)              { return u -= mp_float(f); }
      inline mp_float& operator-=(mp_float& u, const double d)             { return u -= mp_float(d); }
      inline mp_float& operator-=(mp_float& u, const long double ld)       { return u -= mp_float(ld); }

      inline mp_float& operator*=(mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.mul_unsigned_long_long(static_cast<unsigned long long>(n)) : u.mul_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator*=(mp_float& u, const signed char n)        { return u.mul_signed_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const signed short n)       { return u.mul_signed_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const int n)                { return u.mul_signed_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const signed long n)        { return u.mul_signed_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const signed long long n)   { return u.mul_signed_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const unsigned char n)      { return u.mul_unsigned_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.mul_unsigned_long_long(static_cast<unsigned long long>(n)) : u.mul_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator*=(mp_float& u, const unsigned short n)     { return u.mul_unsigned_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const unsigned int n)       { return u.mul_unsigned_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const unsigned long n)      { return u.mul_unsigned_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const unsigned long long n) { return u.mul_unsigned_long_long(n); }
      inline mp_float& operator*=(mp_float& u, const float f)              { return u *= mp_float(f); }
      inline mp_float& operator*=(mp_float& u, const double d)             { return u *= mp_float(d); }
      inline mp_float& operator*=(mp_float& u, const long double ld)       { return u *= mp_float(ld); }

      inline mp_float& operator/=(mp_float& u, const char n)               { return ((!std::numeric_limits<char>::is_signed) ? u.div_unsigned_long_long(static_cast<unsigned long long>(n)) : u.div_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator/=(mp_float& u, const signed char n)        { return u.div_signed_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const signed short n)       { return u.div_signed_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const int n)                { return u.div_signed_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const signed long n)        { return u.div_signed_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const signed long long n)   { return u.div_signed_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const unsigned char n)      { return u.div_unsigned_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const wchar_t n)            { return ((!std::numeric_limits<wchar_t>::is_signed) ? u.div_unsigned_long_long(static_cast<unsigned long long>(n)) : u.div_signed_long_long(static_cast<signed long long>(n))); }
      inline mp_float& operator/=(mp_float& u, const unsigned short n)     { return u.div_unsigned_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const unsigned int n)       { return u.div_unsigned_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const unsigned long n)      { return u.div_unsigned_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const unsigned long long n) { return u.div_unsigned_long_long(n); }
      inline mp_float& operator/=(mp_float& u, const float f)              { return u /= mp_float(f); }
      inline mp_float& operator/=(mp_float& u, const double d)             { return u /= mp_float(d); }
      inline mp_float& operator/=(mp_float& u, const long double ld)       { return u /= mp_float(ld); }

      // Global comparison operators of const mp_float& with const mp_float&.
      inline bool operator< (const mp_float& u, const mp_float& v) { return (u.cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const mp_float& v) { return (u.cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const mp_float& v) { return (u.cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const mp_float& v) { return (u.cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const mp_float& v) { return (u.cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const mp_float& v) { return (u.cmp(v) >  static_cast<boost::int32_t>(0)); }

      // Global comparison operators of const mp_float& with all built-in types.
      inline bool operator< (const mp_float& u, const char v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const char v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const char v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const char v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const char v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const char v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const wchar_t v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const signed char v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const signed short v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const int v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const int v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const int v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const int v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const int v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const int v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const signed long v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const signed long long v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const unsigned char v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const unsigned short v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const unsigned int v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const unsigned long v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const unsigned long long v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const float v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const float v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const float v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const float v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const float v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const float v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const double v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const double v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const double v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const double v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const double v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const double v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const mp_float& u, const long double v) { return (u.cmp(mp_float(v)) >  static_cast<boost::int32_t>(0)); }

      // Global comparison operators of all built-in types with const mp_float&.
      inline bool operator< (const char u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const char u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const char u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const char u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const char u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const char u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const wchar_t u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const signed char u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const signed short u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const int u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const int u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const int u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const int u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const int u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const int u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const signed long u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const signed long long u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const unsigned char u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const unsigned short u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const unsigned int u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const unsigned long u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const unsigned long long u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const float u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const float u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const float u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const float u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const float u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const float u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const double u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const double u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const double u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const double u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const double u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const double u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }

      inline bool operator< (const long double u, const mp_float& v) { return (mp_float(u).cmp(v) <  static_cast<boost::int32_t>(0)); }
      inline bool operator<=(const long double u, const mp_float& v) { return (mp_float(u).cmp(v) <= static_cast<boost::int32_t>(0)); }
      inline bool operator==(const long double u, const mp_float& v) { return (mp_float(u).cmp(v) == static_cast<boost::int32_t>(0)); }
      inline bool operator!=(const long double u, const mp_float& v) { return (mp_float(u).cmp(v) != static_cast<boost::int32_t>(0)); }
      inline bool operator>=(const long double u, const mp_float& v) { return (mp_float(u).cmp(v) >= static_cast<boost::int32_t>(0)); }
      inline bool operator> (const long double u, const mp_float& v) { return (mp_float(u).cmp(v) >  static_cast<boost::int32_t>(0)); }
    }
  }

#endif // _MP_FLOAT_2004_02_08_HPP_
