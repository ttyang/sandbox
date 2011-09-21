
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _MP_COMPLEX_HPP_
  #define _MP_COMPLEX_HPP_

  #include <complex>

  #include <boost/multiprecision/mp_float.hpp>

  // A separate complex class for mp_float has been created. Even though
  // a generic template class std::complex<T> exists, the C++ specification
  // ISO7IEC 14882:2003 paragraph 26.2/2 indicates that: "The effect of
  // instantiating the template complex<T> for any type other than float,
  // double or long double is unspecified". The strict interpretation thereof
  // disallows both using the template class std::complex<T> with mp_float
  // as well as creating a template specialization for mp_float.
  // Therefore the separate class mp_complex is needed.

  namespace boost
  {
    namespace multiprecision
    {
      class mp_complex;

      inline mp_complex& operator+=(mp_complex&, const char);
      inline mp_complex& operator+=(mp_complex&, const signed char);
      inline mp_complex& operator+=(mp_complex&, const signed short);
      inline mp_complex& operator+=(mp_complex&, const signed int);
      inline mp_complex& operator+=(mp_complex&, const signed long);
      inline mp_complex& operator+=(mp_complex&, const signed long long);
      inline mp_complex& operator+=(mp_complex&, const unsigned char);
      inline mp_complex& operator+=(mp_complex&, const wchar_t);
      inline mp_complex& operator+=(mp_complex&, const unsigned short);
      inline mp_complex& operator+=(mp_complex&, const unsigned int);
      inline mp_complex& operator+=(mp_complex&, const unsigned long);
      inline mp_complex& operator+=(mp_complex&, const unsigned long long);
      inline mp_complex& operator+=(mp_complex&, const float);
      inline mp_complex& operator+=(mp_complex&, const double);
      inline mp_complex& operator+=(mp_complex&, const long double);

      inline mp_complex& operator-=(mp_complex&, const char);
      inline mp_complex& operator-=(mp_complex&, const signed char);
      inline mp_complex& operator-=(mp_complex&, const signed short);
      inline mp_complex& operator-=(mp_complex&, const signed int);
      inline mp_complex& operator-=(mp_complex&, const signed long);
      inline mp_complex& operator-=(mp_complex&, const signed long long);
      inline mp_complex& operator-=(mp_complex&, const unsigned char);
      inline mp_complex& operator-=(mp_complex&, const wchar_t);
      inline mp_complex& operator-=(mp_complex&, const unsigned short);
      inline mp_complex& operator-=(mp_complex&, const unsigned int);
      inline mp_complex& operator-=(mp_complex&, const unsigned long);
      inline mp_complex& operator-=(mp_complex&, const unsigned long long);
      inline mp_complex& operator-=(mp_complex&, const float);
      inline mp_complex& operator-=(mp_complex&, const double);
      inline mp_complex& operator-=(mp_complex&, const long double);

      inline mp_complex& operator*=(mp_complex&, const char);
      inline mp_complex& operator*=(mp_complex&, const signed char);
      inline mp_complex& operator*=(mp_complex&, const signed short);
      inline mp_complex& operator*=(mp_complex&, const signed int);
      inline mp_complex& operator*=(mp_complex&, const signed long);
      inline mp_complex& operator*=(mp_complex&, const signed long long);
      inline mp_complex& operator*=(mp_complex&, const unsigned char);
      inline mp_complex& operator*=(mp_complex&, const wchar_t);
      inline mp_complex& operator*=(mp_complex&, const unsigned short);
      inline mp_complex& operator*=(mp_complex&, const unsigned int);
      inline mp_complex& operator*=(mp_complex&, const unsigned long);
      inline mp_complex& operator*=(mp_complex&, const unsigned long long);
      inline mp_complex& operator*=(mp_complex&, const float);
      inline mp_complex& operator*=(mp_complex&, const double);
      inline mp_complex& operator*=(mp_complex&, const long double);

      inline mp_complex& operator/=(mp_complex&, const char);
      inline mp_complex& operator/=(mp_complex&, const signed char);
      inline mp_complex& operator/=(mp_complex&, const signed short);
      inline mp_complex& operator/=(mp_complex&, const signed int);
      inline mp_complex& operator/=(mp_complex&, const signed long);
      inline mp_complex& operator/=(mp_complex&, const signed long long);
      inline mp_complex& operator/=(mp_complex&, const unsigned char);
      inline mp_complex& operator/=(mp_complex&, const wchar_t);
      inline mp_complex& operator/=(mp_complex&, const unsigned short);
      inline mp_complex& operator/=(mp_complex&, const unsigned int);
      inline mp_complex& operator/=(mp_complex&, const unsigned long);
      inline mp_complex& operator/=(mp_complex&, const unsigned long long);
      inline mp_complex& operator/=(mp_complex&, const float);
      inline mp_complex& operator/=(mp_complex&, const double);
      inline mp_complex& operator/=(mp_complex&, const long double);

      inline mp_complex& operator+=(mp_complex&, const mp_float&);
      inline mp_complex& operator-=(mp_complex&, const mp_float&);
      inline mp_complex& operator*=(mp_complex&, const mp_float&);
      inline mp_complex& operator/=(mp_complex&, const mp_float&);
    }
  }

  namespace boost
  {
    namespace multiprecision
    {
      class mp_complex
      {
      private:
        mp_float Re;
        mp_float Im;

      public:
        mp_complex(const char n)               : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const signed char n)        : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const unsigned char n)      : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const wchar_t n)            : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const signed short n)       : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const unsigned short n)     : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const signed int n)         : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const unsigned int n)       : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const signed long n)        : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const unsigned long n)      : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const signed long long n)   : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const unsigned long long n) : Re(n), Im(boost::multiprecision::zero()) { }
        mp_complex(const float f)              : Re(f), Im(boost::multiprecision::zero()) { }
        mp_complex(const double d)             : Re(d), Im(boost::multiprecision::zero()) { }
        mp_complex(const long double ld)       : Re(ld), Im(boost::multiprecision::zero()) { }

        explicit mp_complex(const char* const s)    : Re(s), Im(boost::multiprecision::zero()) { }
        explicit mp_complex(const std::string& str) : Re(str), Im(boost::multiprecision::zero()) { }

        mp_complex() : Re(boost::multiprecision::zero()), Im(boost::multiprecision::zero()) { }
        mp_complex(const mp_float& re) : Re(re), Im(boost::multiprecision::zero()) { }
        mp_complex(const mp_float& re, const mp_float& im) : Re(re), Im(im) { }
        mp_complex(const mp_complex& z) : Re(z.Re), Im(z.Im) { }

        mp_float real(void) const { return Re; }
        mp_float imag(void) const { return Im; }

        static mp_float real(const mp_complex& z) { return z.Re; }
        static mp_float imag(const mp_complex& z) { return z.Im; }

        mp_float norm(void) const { return (Re * Re) + (Im * Im); }

        mp_complex& operator=(const mp_complex& v) { Re = v.Re; Im = v.Im; return *this; }
        mp_complex& operator=(const mp_float& v)    { Re = v; Im = boost::multiprecision::zero(); return *this; }

        mp_complex& operator+=(const mp_complex& v) { Re += v.Re; Im += v.Im; return *this; }
        mp_complex& operator-=(const mp_complex& v) { Re -= v.Re; Im -= v.Im; return *this; }

        mp_complex& operator*=(const mp_complex& v)
        {
          const mp_float tmp_re = (Re * v.Re) - (Im * v.Im);
          const mp_float tmp_im = (Re * v.Im) + (Im * v.Re);
          Re = tmp_re;
          Im = tmp_im;
          return *this;
        }

        mp_complex& operator/=(const mp_complex& v)
        {
          const mp_float one_over_denom = boost::multiprecision::one() / v.norm();
          const mp_float tmp_re = ((Re * v.Re) + (Im * v.Im)) * one_over_denom;
          const mp_float tmp_im = ((Im * v.Re) - (Re * v.Im)) * one_over_denom;
          Re = tmp_re;
          Im = tmp_im;
          return *this;
        }

        // Operators pre-increment and pre-decrement
        const mp_complex& operator++(void) { ++Re; return *this; }
        const mp_complex& operator--(void) { --Re; return *this; }

        bool isnan   (void) const { return Re.isnan()    || Im.isnan(); }
        bool isinf   (void) const { return Re.isinf()    || Im.isinf(); }
        bool isfinite(void) const { return Re.isfinite() && Im.isfinite(); }
        bool isneg   (void) const { return Re.isneg(); }
        bool ispos   (void) const { return Re.ispos(); }
        bool isint   (void) const { return Re.isint()  && Im.iszero(); }
        bool isone   (void) const { return Re.isone()  && Im.iszero(); }
        bool iszero  (void) const { return Re.iszero() && Im.iszero(); }

        friend inline mp_complex& operator+=(mp_complex&, const char);
        friend inline mp_complex& operator+=(mp_complex&, const signed char);
        friend inline mp_complex& operator+=(mp_complex&, const signed short);
        friend inline mp_complex& operator+=(mp_complex&, const signed int);
        friend inline mp_complex& operator+=(mp_complex&, const signed long);
        friend inline mp_complex& operator+=(mp_complex&, const signed long long);
        friend inline mp_complex& operator+=(mp_complex&, const unsigned char);
        friend inline mp_complex& operator+=(mp_complex&, const wchar_t);
        friend inline mp_complex& operator+=(mp_complex&, const unsigned short);
        friend inline mp_complex& operator+=(mp_complex&, const unsigned int);
        friend inline mp_complex& operator+=(mp_complex&, const unsigned long);
        friend inline mp_complex& operator+=(mp_complex&, const unsigned long long);
        friend inline mp_complex& operator+=(mp_complex&, const float);
        friend inline mp_complex& operator+=(mp_complex&, const double);
        friend inline mp_complex& operator+=(mp_complex&, const long double);

        friend inline mp_complex& operator-=(mp_complex&, const char);
        friend inline mp_complex& operator-=(mp_complex&, const signed char);
        friend inline mp_complex& operator-=(mp_complex&, const signed short);
        friend inline mp_complex& operator-=(mp_complex&, const signed int);
        friend inline mp_complex& operator-=(mp_complex&, const signed long);
        friend inline mp_complex& operator-=(mp_complex&, const signed long long);
        friend inline mp_complex& operator-=(mp_complex&, const unsigned char);
        friend inline mp_complex& operator-=(mp_complex&, const wchar_t);
        friend inline mp_complex& operator-=(mp_complex&, const unsigned short);
        friend inline mp_complex& operator-=(mp_complex&, const unsigned int);
        friend inline mp_complex& operator-=(mp_complex&, const unsigned long);
        friend inline mp_complex& operator-=(mp_complex&, const unsigned long long);
        friend inline mp_complex& operator-=(mp_complex&, const float);
        friend inline mp_complex& operator-=(mp_complex&, const double);
        friend inline mp_complex& operator-=(mp_complex&, const long double);

        friend inline mp_complex& operator*=(mp_complex&, const char);
        friend inline mp_complex& operator*=(mp_complex&, const signed char);
        friend inline mp_complex& operator*=(mp_complex&, const signed short);
        friend inline mp_complex& operator*=(mp_complex&, const signed int);
        friend inline mp_complex& operator*=(mp_complex&, const signed long);
        friend inline mp_complex& operator*=(mp_complex&, const signed long long);
        friend inline mp_complex& operator*=(mp_complex&, const unsigned char);
        friend inline mp_complex& operator*=(mp_complex&, const wchar_t);
        friend inline mp_complex& operator*=(mp_complex&, const unsigned short);
        friend inline mp_complex& operator*=(mp_complex&, const unsigned int);
        friend inline mp_complex& operator*=(mp_complex&, const unsigned long);
        friend inline mp_complex& operator*=(mp_complex&, const unsigned long long);
        friend inline mp_complex& operator*=(mp_complex&, const float);
        friend inline mp_complex& operator*=(mp_complex&, const double);
        friend inline mp_complex& operator*=(mp_complex&, const long double);

        friend inline mp_complex& operator/=(mp_complex&, const char);
        friend inline mp_complex& operator/=(mp_complex&, const signed char);
        friend inline mp_complex& operator/=(mp_complex&, const signed short);
        friend inline mp_complex& operator/=(mp_complex&, const signed int);
        friend inline mp_complex& operator/=(mp_complex&, const signed long);
        friend inline mp_complex& operator/=(mp_complex&, const signed long long);
        friend inline mp_complex& operator/=(mp_complex&, const unsigned char);
        friend inline mp_complex& operator/=(mp_complex&, const wchar_t);
        friend inline mp_complex& operator/=(mp_complex&, const unsigned short);
        friend inline mp_complex& operator/=(mp_complex&, const unsigned int);
        friend inline mp_complex& operator/=(mp_complex&, const unsigned long);
        friend inline mp_complex& operator/=(mp_complex&, const unsigned long long);
        friend inline mp_complex& operator/=(mp_complex&, const float);
        friend inline mp_complex& operator/=(mp_complex&, const double);
        friend inline mp_complex& operator/=(mp_complex&, const long double);

        friend inline mp_complex& operator+=(mp_complex&, const mp_float&);
        friend inline mp_complex& operator-=(mp_complex&, const mp_float&);
        friend inline mp_complex& operator*=(mp_complex&, const mp_float&);
        friend inline mp_complex& operator/=(mp_complex&, const mp_float&);
      };
    }
  }

  namespace boost
  {
    namespace multiprecision
    {
      inline std::ostream& operator<<(std::ostream& os, const mp_complex& z) { return os << '(' << z.real() << ',' << z.imag() << ')'; }

      // Global unary operators of mp_float reference.
      inline       mp_complex  operator-(const mp_complex& u) { return mp_complex(-u.real(), -u.imag()); }
      inline       mp_complex& operator+(      mp_complex& u) { return u; }
      inline const mp_complex& operator+(const mp_complex& u) { return u; }

      // Global operators post-increment and post-decrement
      inline mp_complex operator++(mp_complex& u, int) { const mp_complex v(u); ++u; return v; }
      inline mp_complex operator--(mp_complex& u, int) { const mp_complex v(u); --u; return v; }

      // Global comparison operators
      inline bool operator==(const mp_complex& u, const mp_complex& v) { return (u.real() == v.real()) && (u.imag() == v.imag()); }
      inline bool operator!=(const mp_complex& u, const mp_complex& v) { return (u.real() != v.real()) || (u.imag() != v.imag()); }

      // Global arithmetic operators with const mp_complex& and const mp_complex&.
      inline mp_complex operator+(const mp_complex& u, const mp_complex& v) { return mp_complex(u) += v; }
      inline mp_complex operator-(const mp_complex& u, const mp_complex& v) { return mp_complex(u) -= v; }
      inline mp_complex operator*(const mp_complex& u, const mp_complex& v) { return mp_complex(u) *= v; }
      inline mp_complex operator/(const mp_complex& u, const mp_complex& v) { return mp_complex(u) /= v; }

      // Global arithmetic operators with const mp_complex& and const mp_float&.
      inline mp_complex operator+(const mp_complex& u, const mp_float& v) { return mp_complex(u.real() + v, u.imag()); }
      inline mp_complex operator-(const mp_complex& u, const mp_float& v) { return mp_complex(u.real() - v, u.imag()); }
      inline mp_complex operator*(const mp_complex& u, const mp_float& v) { return mp_complex(u.real() * v, u.imag() * v); }
      inline mp_complex operator/(const mp_complex& u, const mp_float& v) { return mp_complex(u.real() / v, u.imag() / v); }

      // Global arithmetic operators with const mp_float& and const mp_complex&.
      inline mp_complex operator+(const mp_float& u, const mp_complex& v) { return mp_complex(u + v.real(), v.imag()); }
      inline mp_complex operator-(const mp_float& u, const mp_complex& v) { return mp_complex(u - v.real(), -v.imag()); }
      inline mp_complex operator*(const mp_float& u, const mp_complex& v) { return mp_complex(u * v.real(), u * v.imag()); }
      inline mp_complex operator/(const mp_float& u, const mp_complex& v) { const mp_float v_norm = v.norm(); return mp_complex((u * v.real()) / v_norm, (-u * v.imag()) / v_norm); }

      // Global add/sub/mul/div of const mp_complex& with all built-in types.
      inline mp_complex operator+(const mp_complex& z, const char n)               { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const signed char n)        { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const signed short n)       { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const signed int n)         { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const signed long n)        { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const signed long long n)   { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const unsigned char n)      { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const wchar_t n)            { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const unsigned short n)     { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const unsigned int n)       { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const unsigned long n)      { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const unsigned long long n) { return mp_complex(z.real() + n, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const float f)              { return mp_complex(z.real() + f, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const double d)             { return mp_complex(z.real() + d, z.imag()); }
      inline mp_complex operator+(const mp_complex& z, const long double ld)       { return mp_complex(z.real() + ld, z.imag()); }

      inline mp_complex operator-(const mp_complex& z, const char n)               { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const signed char n)        { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const signed short n)       { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const signed int n)         { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const signed long n)        { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const signed long long n)   { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const unsigned char n)      { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const wchar_t n)            { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const unsigned short n)     { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const unsigned int n)       { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const unsigned long n)      { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const unsigned long long n) { return mp_complex(z.real() - n, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const float f)              { return mp_complex(z.real() - f, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const double d)             { return mp_complex(z.real() - d, z.imag()); }
      inline mp_complex operator-(const mp_complex& z, const long double ld)       { return mp_complex(z.real() - ld, z.imag()); }

      inline mp_complex operator*(const mp_complex& z, const char n)               { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const signed char n)        { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const signed short n)       { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const signed int n)         { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const signed long n)        { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const signed long long n)   { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const unsigned char n)      { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const wchar_t n)            { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const unsigned short n)     { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const unsigned int n)       { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const unsigned long n)      { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const unsigned long long n) { return mp_complex(z.real() * n, z.imag() * n); }
      inline mp_complex operator*(const mp_complex& z, const float f)              { return mp_complex(z.real() * f, z.imag() * f); }
      inline mp_complex operator*(const mp_complex& z, const double d)             { return mp_complex(z.real() * d, z.imag() * d); }
      inline mp_complex operator*(const mp_complex& z, const long double ld)       { return mp_complex(z.real() * ld, z.imag() * ld); }

      inline mp_complex operator/(const mp_complex& z, const char n)               { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const signed char n)        { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const signed short n)       { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const signed int n)         { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const signed long n)        { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const signed long long n)   { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const unsigned char n)      { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const wchar_t n)            { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const unsigned short n)     { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const unsigned int n)       { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const unsigned long n)      { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const unsigned long long n) { return mp_complex(z.real() / n, z.imag() / n); }
      inline mp_complex operator/(const mp_complex& z, const float f)              { return mp_complex(z.real() / f, z.imag() / f); }
      inline mp_complex operator/(const mp_complex& z, const double d)             { return mp_complex(z.real() / d, z.imag() / d); }
      inline mp_complex operator/(const mp_complex& z, const long double ld)       { return mp_complex(z.real() / ld, z.imag() / ld); }

      // Global add/sub/mul/div of all built-in types with const mp_complex&.
      inline mp_complex operator+(const char n, const mp_complex& v)               { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const signed char n, const mp_complex& v)        { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const signed short n, const mp_complex& v)       { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const signed int n, const mp_complex& v)         { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const signed long n, const mp_complex& v)        { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const signed long long n, const mp_complex& v)   { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const unsigned char n, const mp_complex& v)      { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const wchar_t n, const mp_complex& v)            { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const unsigned short n, const mp_complex& v)     { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const unsigned int n, const mp_complex& v)       { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const unsigned long n, const mp_complex& v)      { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const unsigned long long n, const mp_complex& v) { return mp_complex(v.real() + n, v.imag()); }
      inline mp_complex operator+(const float f, const mp_complex& v)              { return mp_complex(v.real() + f, v.imag() + f); }
      inline mp_complex operator+(const double d, const mp_complex& v)             { return mp_complex(v.real() + d, v.imag() + d); }
      inline mp_complex operator+(const long double ld, const mp_complex& v)       { return mp_complex(v.real() + ld, v.imag() + ld); }

      inline mp_complex operator-(const char n, const mp_complex& v)               { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const signed char n, const mp_complex& v)        { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const signed short n, const mp_complex& v)       { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const signed int n, const mp_complex& v)         { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const signed long n, const mp_complex& v)        { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const signed long long n, const mp_complex& v)   { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const unsigned char n, const mp_complex& v)      { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const wchar_t n, const mp_complex& v)            { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const unsigned short n, const mp_complex& v)     { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const unsigned int n, const mp_complex& v)       { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const unsigned long n, const mp_complex& v)      { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const unsigned long long n, const mp_complex& v) { return mp_complex(n - v.real(), -v.imag()); }
      inline mp_complex operator-(const float f, const mp_complex& v)              { return mp_complex(f - v.real(), -v.imag()); }
      inline mp_complex operator-(const double d, const mp_complex& v)             { return mp_complex(d - v.real(), -v.imag()); }
      inline mp_complex operator-(const long double ld, const mp_complex& v)       { return mp_complex(ld - v.real(), -v.imag()); }

      inline mp_complex operator*(const char n, const mp_complex& v)               { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const signed char n, const mp_complex& v)        { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const signed short n, const mp_complex& v)       { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const signed int n, const mp_complex& v)         { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const signed long n, const mp_complex& v)        { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const signed long long n, const mp_complex& v)   { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const unsigned char n, const mp_complex& v)      { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const wchar_t n, const mp_complex& v)            { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const unsigned short n, const mp_complex& v)     { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const unsigned int n, const mp_complex& v)       { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const unsigned long n, const mp_complex& v)      { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const unsigned long long n, const mp_complex& v) { return mp_complex(v.real() * n, v.imag() * n); }
      inline mp_complex operator*(const float f, const mp_complex& v)              { return mp_complex(v.real() * f, v.imag() * f); }
      inline mp_complex operator*(const double d, const mp_complex& v)             { return mp_complex(v.real() * d, v.imag() * d); }
      inline mp_complex operator*(const long double ld, const mp_complex& v)       { return mp_complex(v.real() * ld, v.imag() * ld); }

      inline mp_complex operator/(const char n, const mp_complex& v)               { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const signed char n, const mp_complex& v)        { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const signed short n, const mp_complex& v)       { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const signed int n, const mp_complex& v)         { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const signed long n, const mp_complex& v)        { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const signed long long n, const mp_complex& v)   { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const unsigned char n, const mp_complex& v)      { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const wchar_t n, const mp_complex& v)            { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const unsigned short n, const mp_complex& v)     { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const unsigned int n, const mp_complex& v)       { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const unsigned long n, const mp_complex& v)      { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const unsigned long long n, const mp_complex& v) { const mp_float v_norm = v.norm(); return mp_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
      inline mp_complex operator/(const float f, const mp_complex& v)              { const mp_float v_norm = v.norm(); return mp_complex((f * v.real()) / v_norm, -(f * v.imag()) / v_norm); }
      inline mp_complex operator/(const double d, const mp_complex& v)             { const mp_float v_norm = v.norm(); return mp_complex((d * v.real()) / v_norm, -(d * v.imag()) / v_norm); }
      inline mp_complex operator/(const long double ld, const mp_complex& v)       { const mp_float v_norm = v.norm(); return mp_complex((ld * v.real()) / v_norm, -(ld * v.imag()) / v_norm); }

      // Global self add/sub/mul/div of mp_complex& with all built-in types.
      inline mp_complex& operator+=(mp_complex& z, const char n)               { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const signed char n)        { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const signed short n)       { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const signed int n)         { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const signed long n)        { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const signed long long n)   { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const unsigned char n)      { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const wchar_t n)            { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const unsigned short n)     { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const unsigned int n)       { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const unsigned long n)      { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const unsigned long long n) { z.Re += n; return z; }
      inline mp_complex& operator+=(mp_complex& z, const float f)              { z.Re += f; return z; }
      inline mp_complex& operator+=(mp_complex& z, const double d)             { z.Re += d; return z; }
      inline mp_complex& operator+=(mp_complex& z, const long double ld)       { z.Re += ld; return z; }

      inline mp_complex& operator-=(mp_complex& z, const char n)               { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const signed char n)        { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const signed short n)       { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const signed int n)         { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const signed long n)        { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const signed long long n)   { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const unsigned char n)      { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const wchar_t n)            { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const unsigned short n)     { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const unsigned int n)       { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const unsigned long n)      { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const unsigned long long n) { z.Re -= n; return z; }
      inline mp_complex& operator-=(mp_complex& z, const float f)              { z.Re -= f; return z; }
      inline mp_complex& operator-=(mp_complex& z, const double d)             { z.Re -= d; return z; }
      inline mp_complex& operator-=(mp_complex& z, const long double ld)       { z.Re -= ld; return z; }

      inline mp_complex& operator*=(mp_complex& z, const char n)               { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const signed char n)        { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const signed short n)       { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const signed int n)         { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const signed long n)        { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const signed long long n)   { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const unsigned char n)      { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const wchar_t n)            { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const unsigned short n)     { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const unsigned int n)       { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const unsigned long n)      { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const unsigned long long n) { z.Re *= n; z.Im *= n; return z; }
      inline mp_complex& operator*=(mp_complex& z, const float f)              { z.Re *= f; z.Im *= f; return z; }
      inline mp_complex& operator*=(mp_complex& z, const double d)             { z.Re *= d; z.Im *= d; return z; }
      inline mp_complex& operator*=(mp_complex& z, const long double ld)       { z.Re *= ld; z.Im *= ld; return z; }

      inline mp_complex& operator/=(mp_complex& z, const char n)               { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const signed char n)        { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const signed short n)       { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const signed int n)         { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const signed long n)        { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const signed long long n)   { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const unsigned char n)      { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const wchar_t n)            { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const unsigned short n)     { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const unsigned int n)       { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const unsigned long n)      { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const unsigned long long n) { z.Re /= n; z.Im /= n; return z; }
      inline mp_complex& operator/=(mp_complex& z, const float f)              { z.Re /= f; z.Im /= f; return z; }
      inline mp_complex& operator/=(mp_complex& z, const double d)             { z.Re /= d; z.Im /= d; return z; }
      inline mp_complex& operator/=(mp_complex& z, const long double ld)       { z.Re /= ld; z.Im /= ld; return z; }

      // Global self add/sub/mul/div of mp_complex& with const mp_float&.
      inline mp_complex& operator+=(mp_complex& z, const mp_float& v) { z.Re += v;            return z; }
      inline mp_complex& operator-=(mp_complex& z, const mp_float& v) { z.Re -= v;            return z; }
      inline mp_complex& operator*=(mp_complex& z, const mp_float& v) { z.Re *= v; z.Im *= v; return z; }
      inline mp_complex& operator/=(mp_complex& z, const mp_float& v) { z.Re /= v; z.Im /= v; return z; }
    }
  }

#endif // _MP_COMPLEX_HPP_
