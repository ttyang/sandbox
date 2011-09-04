
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_COMPLEX_HPP_
  #define _E_FLOAT_COMPLEX_HPP_

  #include <complex>

  #include <boost/e_float/e_float.hpp>

  // A separate complex class for e_float has been created. Even though
  // a generic template class std::complex<T> exists, the C++ specification
  // ISO7IEC 14882:2003 paragraph 26.2/2 indicates that: "The effect of
  // instantiating the template complex<T> for any type other than float,
  // double or long double is unspecified". The strict interpretation thereof
  // disallows both using the template class std::complex<T> with e_float
  // as well as creating a template specialization for e_float.
  // Therefore the separate class ef_complex is needed.

  class ef_complex;

  inline ef_complex& operator+=(ef_complex&, const char);
  inline ef_complex& operator+=(ef_complex&, const signed char);
  inline ef_complex& operator+=(ef_complex&, const signed short);
  inline ef_complex& operator+=(ef_complex&, const signed int);
  inline ef_complex& operator+=(ef_complex&, const signed long);
  inline ef_complex& operator+=(ef_complex&, const signed long long);
  inline ef_complex& operator+=(ef_complex&, const unsigned char);
  inline ef_complex& operator+=(ef_complex&, const wchar_t);
  inline ef_complex& operator+=(ef_complex&, const unsigned short);
  inline ef_complex& operator+=(ef_complex&, const unsigned int);
  inline ef_complex& operator+=(ef_complex&, const unsigned long);
  inline ef_complex& operator+=(ef_complex&, const unsigned long long);
  inline ef_complex& operator+=(ef_complex&, const float);
  inline ef_complex& operator+=(ef_complex&, const double);
  inline ef_complex& operator+=(ef_complex&, const long double);

  inline ef_complex& operator-=(ef_complex&, const char);
  inline ef_complex& operator-=(ef_complex&, const signed char);
  inline ef_complex& operator-=(ef_complex&, const signed short);
  inline ef_complex& operator-=(ef_complex&, const signed int);
  inline ef_complex& operator-=(ef_complex&, const signed long);
  inline ef_complex& operator-=(ef_complex&, const signed long long);
  inline ef_complex& operator-=(ef_complex&, const unsigned char);
  inline ef_complex& operator-=(ef_complex&, const wchar_t);
  inline ef_complex& operator-=(ef_complex&, const unsigned short);
  inline ef_complex& operator-=(ef_complex&, const unsigned int);
  inline ef_complex& operator-=(ef_complex&, const unsigned long);
  inline ef_complex& operator-=(ef_complex&, const unsigned long long);
  inline ef_complex& operator-=(ef_complex&, const float);
  inline ef_complex& operator-=(ef_complex&, const double);
  inline ef_complex& operator-=(ef_complex&, const long double);

  inline ef_complex& operator*=(ef_complex&, const char);
  inline ef_complex& operator*=(ef_complex&, const signed char);
  inline ef_complex& operator*=(ef_complex&, const signed short);
  inline ef_complex& operator*=(ef_complex&, const signed int);
  inline ef_complex& operator*=(ef_complex&, const signed long);
  inline ef_complex& operator*=(ef_complex&, const signed long long);
  inline ef_complex& operator*=(ef_complex&, const unsigned char);
  inline ef_complex& operator*=(ef_complex&, const wchar_t);
  inline ef_complex& operator*=(ef_complex&, const unsigned short);
  inline ef_complex& operator*=(ef_complex&, const unsigned int);
  inline ef_complex& operator*=(ef_complex&, const unsigned long);
  inline ef_complex& operator*=(ef_complex&, const unsigned long long);
  inline ef_complex& operator*=(ef_complex&, const float);
  inline ef_complex& operator*=(ef_complex&, const double);
  inline ef_complex& operator*=(ef_complex&, const long double);

  inline ef_complex& operator/=(ef_complex&, const char);
  inline ef_complex& operator/=(ef_complex&, const signed char);
  inline ef_complex& operator/=(ef_complex&, const signed short);
  inline ef_complex& operator/=(ef_complex&, const signed int);
  inline ef_complex& operator/=(ef_complex&, const signed long);
  inline ef_complex& operator/=(ef_complex&, const signed long long);
  inline ef_complex& operator/=(ef_complex&, const unsigned char);
  inline ef_complex& operator/=(ef_complex&, const wchar_t);
  inline ef_complex& operator/=(ef_complex&, const unsigned short);
  inline ef_complex& operator/=(ef_complex&, const unsigned int);
  inline ef_complex& operator/=(ef_complex&, const unsigned long);
  inline ef_complex& operator/=(ef_complex&, const unsigned long long);
  inline ef_complex& operator/=(ef_complex&, const float);
  inline ef_complex& operator/=(ef_complex&, const double);
  inline ef_complex& operator/=(ef_complex&, const long double);

  inline ef_complex& operator+=(ef_complex&, const e_float&);
  inline ef_complex& operator-=(ef_complex&, const e_float&);
  inline ef_complex& operator*=(ef_complex&, const e_float&);
  inline ef_complex& operator/=(ef_complex&, const e_float&);

  class ef_complex
  {
  private:
    e_float Re;
    e_float Im;

  public:
    ef_complex(const char n)               : Re(n), Im(ef::zero()) { }
    ef_complex(const signed char n)        : Re(n), Im(ef::zero()) { }
    ef_complex(const unsigned char n)      : Re(n), Im(ef::zero()) { }
    ef_complex(const wchar_t n)            : Re(n), Im(ef::zero()) { }
    ef_complex(const signed short n)       : Re(n), Im(ef::zero()) { }
    ef_complex(const unsigned short n)     : Re(n), Im(ef::zero()) { }
    ef_complex(const signed int n)         : Re(n), Im(ef::zero()) { }
    ef_complex(const unsigned int n)       : Re(n), Im(ef::zero()) { }
    ef_complex(const signed long n)        : Re(n), Im(ef::zero()) { }
    ef_complex(const unsigned long n)      : Re(n), Im(ef::zero()) { }
    ef_complex(const signed long long n)   : Re(n), Im(ef::zero()) { }
    ef_complex(const unsigned long long n) : Re(n), Im(ef::zero()) { }
    ef_complex(const float f)              : Re(f), Im(ef::zero()) { }
    ef_complex(const double d)             : Re(d), Im(ef::zero()) { }
    ef_complex(const long double ld)       : Re(ld), Im(ef::zero()) { }

    explicit ef_complex(const char* const s)    : Re(s), Im(ef::zero()) { }
    explicit ef_complex(const std::string& str) : Re(str), Im(ef::zero()) { }

    ef_complex() : Re(ef::zero()), Im(ef::zero()) { }
    ef_complex(const e_float& re) : Re(re), Im(ef::zero()) { }
    ef_complex(const e_float& re, const e_float& im) : Re(re), Im(im) { }
    ef_complex(const ef_complex& z) : Re(z.Re), Im(z.Im) { }

    e_float real(void) const { return Re; }
    e_float imag(void) const { return Im; }

    static e_float real(const ef_complex& z) { return z.Re; }
    static e_float imag(const ef_complex& z) { return z.Im; }

    e_float norm(void) const { return (Re * Re) + (Im * Im); }

    ef_complex& operator=(const ef_complex& v) { Re = v.Re; Im = v.Im; return *this; }
    ef_complex& operator=(const e_float& v)    { Re = v; Im = ef::zero(); return *this; }

    ef_complex& operator+=(const ef_complex& v) { Re += v.Re; Im += v.Im; return *this; }
    ef_complex& operator-=(const ef_complex& v) { Re -= v.Re; Im -= v.Im; return *this; }

    ef_complex& operator*=(const ef_complex& v)
    {
      const e_float tmp_re = (Re * v.Re) - (Im * v.Im);
      const e_float tmp_im = (Re * v.Im) + (Im * v.Re);
      Re = tmp_re;
      Im = tmp_im;
      return *this;
    }

    ef_complex& operator/=(const ef_complex& v)
    {
      const e_float one_over_denom = ef::one() / v.norm();
      const e_float tmp_re = ((Re * v.Re) + (Im * v.Im)) * one_over_denom;
      const e_float tmp_im = ((Im * v.Re) - (Re * v.Im)) * one_over_denom;
      Re = tmp_re;
      Im = tmp_im;
      return *this;
    }

    // Operators pre-increment and pre-decrement
    const ef_complex& operator++(void) { ++Re; return *this; }
    const ef_complex& operator--(void) { --Re; return *this; }

    bool isnan   (void) const { return Re.isnan()    || Im.isnan(); }
    bool isinf   (void) const { return Re.isinf()    || Im.isinf(); }
    bool isfinite(void) const { return Re.isfinite() && Im.isfinite(); }
    bool isneg   (void) const { return Re.isneg(); }
    bool ispos   (void) const { return Re.ispos(); }
    bool isint   (void) const { return Re.isint()  && Im.iszero(); }
    bool isone   (void) const { return Re.isone()  && Im.iszero(); }
    bool iszero  (void) const { return Re.iszero() && Im.iszero(); }

    friend inline ef_complex& ::operator+=(ef_complex&, const char);
    friend inline ef_complex& ::operator+=(ef_complex&, const signed char);
    friend inline ef_complex& ::operator+=(ef_complex&, const signed short);
    friend inline ef_complex& ::operator+=(ef_complex&, const signed int);
    friend inline ef_complex& ::operator+=(ef_complex&, const signed long);
    friend inline ef_complex& ::operator+=(ef_complex&, const signed long long);
    friend inline ef_complex& ::operator+=(ef_complex&, const unsigned char);
    friend inline ef_complex& ::operator+=(ef_complex&, const wchar_t);
    friend inline ef_complex& ::operator+=(ef_complex&, const unsigned short);
    friend inline ef_complex& ::operator+=(ef_complex&, const unsigned int);
    friend inline ef_complex& ::operator+=(ef_complex&, const unsigned long);
    friend inline ef_complex& ::operator+=(ef_complex&, const unsigned long long);
    friend inline ef_complex& ::operator+=(ef_complex&, const float);
    friend inline ef_complex& ::operator+=(ef_complex&, const double);
    friend inline ef_complex& ::operator+=(ef_complex&, const long double);

    friend inline ef_complex& ::operator-=(ef_complex&, const char);
    friend inline ef_complex& ::operator-=(ef_complex&, const signed char);
    friend inline ef_complex& ::operator-=(ef_complex&, const signed short);
    friend inline ef_complex& ::operator-=(ef_complex&, const signed int);
    friend inline ef_complex& ::operator-=(ef_complex&, const signed long);
    friend inline ef_complex& ::operator-=(ef_complex&, const signed long long);
    friend inline ef_complex& ::operator-=(ef_complex&, const unsigned char);
    friend inline ef_complex& ::operator-=(ef_complex&, const wchar_t);
    friend inline ef_complex& ::operator-=(ef_complex&, const unsigned short);
    friend inline ef_complex& ::operator-=(ef_complex&, const unsigned int);
    friend inline ef_complex& ::operator-=(ef_complex&, const unsigned long);
    friend inline ef_complex& ::operator-=(ef_complex&, const unsigned long long);
    friend inline ef_complex& ::operator-=(ef_complex&, const float);
    friend inline ef_complex& ::operator-=(ef_complex&, const double);
    friend inline ef_complex& ::operator-=(ef_complex&, const long double);

    friend inline ef_complex& ::operator*=(ef_complex&, const char);
    friend inline ef_complex& ::operator*=(ef_complex&, const signed char);
    friend inline ef_complex& ::operator*=(ef_complex&, const signed short);
    friend inline ef_complex& ::operator*=(ef_complex&, const signed int);
    friend inline ef_complex& ::operator*=(ef_complex&, const signed long);
    friend inline ef_complex& ::operator*=(ef_complex&, const signed long long);
    friend inline ef_complex& ::operator*=(ef_complex&, const unsigned char);
    friend inline ef_complex& ::operator*=(ef_complex&, const wchar_t);
    friend inline ef_complex& ::operator*=(ef_complex&, const unsigned short);
    friend inline ef_complex& ::operator*=(ef_complex&, const unsigned int);
    friend inline ef_complex& ::operator*=(ef_complex&, const unsigned long);
    friend inline ef_complex& ::operator*=(ef_complex&, const unsigned long long);
    friend inline ef_complex& ::operator*=(ef_complex&, const float);
    friend inline ef_complex& ::operator*=(ef_complex&, const double);
    friend inline ef_complex& ::operator*=(ef_complex&, const long double);

    friend inline ef_complex& ::operator/=(ef_complex&, const char);
    friend inline ef_complex& ::operator/=(ef_complex&, const signed char);
    friend inline ef_complex& ::operator/=(ef_complex&, const signed short);
    friend inline ef_complex& ::operator/=(ef_complex&, const signed int);
    friend inline ef_complex& ::operator/=(ef_complex&, const signed long);
    friend inline ef_complex& ::operator/=(ef_complex&, const signed long long);
    friend inline ef_complex& ::operator/=(ef_complex&, const unsigned char);
    friend inline ef_complex& ::operator/=(ef_complex&, const wchar_t);
    friend inline ef_complex& ::operator/=(ef_complex&, const unsigned short);
    friend inline ef_complex& ::operator/=(ef_complex&, const unsigned int);
    friend inline ef_complex& ::operator/=(ef_complex&, const unsigned long);
    friend inline ef_complex& ::operator/=(ef_complex&, const unsigned long long);
    friend inline ef_complex& ::operator/=(ef_complex&, const float);
    friend inline ef_complex& ::operator/=(ef_complex&, const double);
    friend inline ef_complex& ::operator/=(ef_complex&, const long double);

    friend inline ef_complex& ::operator+=(ef_complex&, const e_float&);
    friend inline ef_complex& ::operator-=(ef_complex&, const e_float&);
    friend inline ef_complex& ::operator*=(ef_complex&, const e_float&);
    friend inline ef_complex& ::operator/=(ef_complex&, const e_float&);
  };

  inline std::ostream& operator<<(std::ostream& os, const ef_complex& z) { return os << '(' << z.real() << ',' << z.imag() << ')'; }

  // Global unary operators of e_float reference.
  inline       ef_complex  operator-(const ef_complex& u) { return ef_complex(-u.real(), -u.imag()); }
  inline       ef_complex& operator+(      ef_complex& u) { return u; }
  inline const ef_complex& operator+(const ef_complex& u) { return u; }

  // Global operators post-increment and post-decrement
  inline ef_complex operator++(ef_complex& u, int) { const ef_complex v(u); ++u; return v; }
  inline ef_complex operator--(ef_complex& u, int) { const ef_complex v(u); --u; return v; }

  // Global comparison operators
  inline bool operator==(const ef_complex& u, const ef_complex& v) { return (u.real() == v.real()) && (u.imag() == v.imag()); }
  inline bool operator!=(const ef_complex& u, const ef_complex& v) { return (u.real() != v.real()) || (u.imag() != v.imag()); }

  // Global arithmetic operators with const ef_complex& and const ef_complex&.
  inline ef_complex operator+(const ef_complex& u, const ef_complex& v) { return ef_complex(u) += v; }
  inline ef_complex operator-(const ef_complex& u, const ef_complex& v) { return ef_complex(u) -= v; }
  inline ef_complex operator*(const ef_complex& u, const ef_complex& v) { return ef_complex(u) *= v; }
  inline ef_complex operator/(const ef_complex& u, const ef_complex& v) { return ef_complex(u) /= v; }

  // Global arithmetic operators with const ef_complex& and const e_float&.
  inline ef_complex operator+(const ef_complex& u, const e_float& v) { return ef_complex(u.real() + v, u.imag()); }
  inline ef_complex operator-(const ef_complex& u, const e_float& v) { return ef_complex(u.real() - v, u.imag()); }
  inline ef_complex operator*(const ef_complex& u, const e_float& v) { return ef_complex(u.real() * v, u.imag() * v); }
  inline ef_complex operator/(const ef_complex& u, const e_float& v) { return ef_complex(u.real() / v, u.imag() / v); }

  // Global arithmetic operators with const e_float& and const ef_complex&.
  inline ef_complex operator+(const e_float& u, const ef_complex& v) { return ef_complex(u + v.real(), v.imag()); }
  inline ef_complex operator-(const e_float& u, const ef_complex& v) { return ef_complex(u - v.real(), -v.imag()); }
  inline ef_complex operator*(const e_float& u, const ef_complex& v) { return ef_complex(u * v.real(), u * v.imag()); }
  inline ef_complex operator/(const e_float& u, const ef_complex& v) { const e_float v_norm = v.norm(); return ef_complex((u * v.real()) / v_norm, (-u * v.imag()) / v_norm); }

  // Global add/sub/mul/div of const ef_complex& with all built-in types.
  inline ef_complex operator+(const ef_complex& z, const char n)               { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const signed char n)        { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const signed short n)       { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const signed int n)         { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const signed long n)        { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const signed long long n)   { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const unsigned char n)      { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const wchar_t n)            { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const unsigned short n)     { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const unsigned int n)       { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const unsigned long n)      { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const unsigned long long n) { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const float f)              { return ef_complex(z.real() + f, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const double d)             { return ef_complex(z.real() + d, z.imag()); }
  inline ef_complex operator+(const ef_complex& z, const long double ld)       { return ef_complex(z.real() + ld, z.imag()); }

  inline ef_complex operator-(const ef_complex& z, const char n)               { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const signed char n)        { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const signed short n)       { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const signed int n)         { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const signed long n)        { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const signed long long n)   { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const unsigned char n)      { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const wchar_t n)            { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const unsigned short n)     { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const unsigned int n)       { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const unsigned long n)      { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const unsigned long long n) { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const float f)              { return ef_complex(z.real() - f, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const double d)             { return ef_complex(z.real() - d, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const long double ld)       { return ef_complex(z.real() - ld, z.imag()); }

  inline ef_complex operator*(const ef_complex& z, const char n)               { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const signed char n)        { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const signed short n)       { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const signed int n)         { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const signed long n)        { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const signed long long n)   { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const unsigned char n)      { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const wchar_t n)            { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const unsigned short n)     { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const unsigned int n)       { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const unsigned long n)      { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const unsigned long long n) { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator*(const ef_complex& z, const float f)              { return ef_complex(z.real() * f, z.imag() * f); }
  inline ef_complex operator*(const ef_complex& z, const double d)             { return ef_complex(z.real() * d, z.imag() * d); }
  inline ef_complex operator*(const ef_complex& z, const long double ld)       { return ef_complex(z.real() * ld, z.imag() * ld); }

  inline ef_complex operator/(const ef_complex& z, const char n)               { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const signed char n)        { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const signed short n)       { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const signed int n)         { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const signed long n)        { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const signed long long n)   { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const unsigned char n)      { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const wchar_t n)            { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const unsigned short n)     { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const unsigned int n)       { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const unsigned long n)      { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const unsigned long long n) { return ef_complex(z.real() / n, z.imag() / n); }
  inline ef_complex operator/(const ef_complex& z, const float f)              { return ef_complex(z.real() / f, z.imag() / f); }
  inline ef_complex operator/(const ef_complex& z, const double d)             { return ef_complex(z.real() / d, z.imag() / d); }
  inline ef_complex operator/(const ef_complex& z, const long double ld)       { return ef_complex(z.real() / ld, z.imag() / ld); }

  // Global add/sub/mul/div of all built-in types with const ef_complex&.
  inline ef_complex operator+(const char n, const ef_complex& v)               { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const signed char n, const ef_complex& v)        { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const signed short n, const ef_complex& v)       { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const signed int n, const ef_complex& v)         { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const signed long n, const ef_complex& v)        { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const signed long long n, const ef_complex& v)   { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const unsigned char n, const ef_complex& v)      { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const wchar_t n, const ef_complex& v)            { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const unsigned short n, const ef_complex& v)     { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const unsigned int n, const ef_complex& v)       { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const unsigned long n, const ef_complex& v)      { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const unsigned long long n, const ef_complex& v) { return ef_complex(v.real() + n, v.imag()); }
  inline ef_complex operator+(const float f, const ef_complex& v)              { return ef_complex(v.real() + f, v.imag() + f); }
  inline ef_complex operator+(const double d, const ef_complex& v)             { return ef_complex(v.real() + d, v.imag() + d); }
  inline ef_complex operator+(const long double ld, const ef_complex& v)       { return ef_complex(v.real() + ld, v.imag() + ld); }

  inline ef_complex operator-(const char n, const ef_complex& v)               { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const signed char n, const ef_complex& v)        { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const signed short n, const ef_complex& v)       { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const signed int n, const ef_complex& v)         { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const signed long n, const ef_complex& v)        { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const signed long long n, const ef_complex& v)   { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const unsigned char n, const ef_complex& v)      { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const wchar_t n, const ef_complex& v)            { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const unsigned short n, const ef_complex& v)     { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const unsigned int n, const ef_complex& v)       { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const unsigned long n, const ef_complex& v)      { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const unsigned long long n, const ef_complex& v) { return ef_complex(n - v.real(), -v.imag()); }
  inline ef_complex operator-(const float f, const ef_complex& v)              { return ef_complex(f - v.real(), -v.imag()); }
  inline ef_complex operator-(const double d, const ef_complex& v)             { return ef_complex(d - v.real(), -v.imag()); }
  inline ef_complex operator-(const long double ld, const ef_complex& v)       { return ef_complex(ld - v.real(), -v.imag()); }

  inline ef_complex operator*(const char n, const ef_complex& v)               { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const signed char n, const ef_complex& v)        { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const signed short n, const ef_complex& v)       { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const signed int n, const ef_complex& v)         { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const signed long n, const ef_complex& v)        { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const signed long long n, const ef_complex& v)   { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const unsigned char n, const ef_complex& v)      { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const wchar_t n, const ef_complex& v)            { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const unsigned short n, const ef_complex& v)     { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const unsigned int n, const ef_complex& v)       { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const unsigned long n, const ef_complex& v)      { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const unsigned long long n, const ef_complex& v) { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator*(const float f, const ef_complex& v)              { return ef_complex(v.real() * f, v.imag() * f); }
  inline ef_complex operator*(const double d, const ef_complex& v)             { return ef_complex(v.real() * d, v.imag() * d); }
  inline ef_complex operator*(const long double ld, const ef_complex& v)       { return ef_complex(v.real() * ld, v.imag() * ld); }

  inline ef_complex operator/(const char n, const ef_complex& v)               { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const signed char n, const ef_complex& v)        { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const signed short n, const ef_complex& v)       { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const signed int n, const ef_complex& v)         { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const signed long n, const ef_complex& v)        { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const signed long long n, const ef_complex& v)   { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const unsigned char n, const ef_complex& v)      { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const wchar_t n, const ef_complex& v)            { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const unsigned short n, const ef_complex& v)     { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const unsigned int n, const ef_complex& v)       { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const unsigned long n, const ef_complex& v)      { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const unsigned long long n, const ef_complex& v) { const e_float v_norm = v.norm(); return ef_complex((n * v.real()) / v_norm, -(n * v.imag()) / v_norm); }
  inline ef_complex operator/(const float f, const ef_complex& v)              { const e_float v_norm = v.norm(); return ef_complex((f * v.real()) / v_norm, -(f * v.imag()) / v_norm); }
  inline ef_complex operator/(const double d, const ef_complex& v)             { const e_float v_norm = v.norm(); return ef_complex((d * v.real()) / v_norm, -(d * v.imag()) / v_norm); }
  inline ef_complex operator/(const long double ld, const ef_complex& v)       { const e_float v_norm = v.norm(); return ef_complex((ld * v.real()) / v_norm, -(ld * v.imag()) / v_norm); }

  // Global self add/sub/mul/div of ef_complex& with all built-in types.
  inline ef_complex& operator+=(ef_complex& z, const char n)               { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const signed char n)        { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const signed short n)       { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const signed int n)         { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const signed long n)        { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const signed long long n)   { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const unsigned char n)      { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const wchar_t n)            { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const unsigned short n)     { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const unsigned int n)       { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const unsigned long n)      { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const unsigned long long n) { z.Re += n; return z; }
  inline ef_complex& operator+=(ef_complex& z, const float f)              { z.Re += f; return z; }
  inline ef_complex& operator+=(ef_complex& z, const double d)             { z.Re += d; return z; }
  inline ef_complex& operator+=(ef_complex& z, const long double ld)       { z.Re += ld; return z; }

  inline ef_complex& operator-=(ef_complex& z, const char n)               { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const signed char n)        { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const signed short n)       { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const signed int n)         { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const signed long n)        { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const signed long long n)   { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const unsigned char n)      { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const wchar_t n)            { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const unsigned short n)     { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const unsigned int n)       { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const unsigned long n)      { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const unsigned long long n) { z.Re -= n; return z; }
  inline ef_complex& operator-=(ef_complex& z, const float f)              { z.Re -= f; return z; }
  inline ef_complex& operator-=(ef_complex& z, const double d)             { z.Re -= d; return z; }
  inline ef_complex& operator-=(ef_complex& z, const long double ld)       { z.Re -= ld; return z; }

  inline ef_complex& operator*=(ef_complex& z, const char n)               { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const signed char n)        { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const signed short n)       { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const signed int n)         { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const signed long n)        { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const signed long long n)   { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const unsigned char n)      { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const wchar_t n)            { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const unsigned short n)     { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const unsigned int n)       { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const unsigned long n)      { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const unsigned long long n) { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator*=(ef_complex& z, const float f)              { z.Re *= f; z.Im *= f; return z; }
  inline ef_complex& operator*=(ef_complex& z, const double d)             { z.Re *= d; z.Im *= d; return z; }
  inline ef_complex& operator*=(ef_complex& z, const long double ld)       { z.Re *= ld; z.Im *= ld; return z; }

  inline ef_complex& operator/=(ef_complex& z, const char n)               { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const signed char n)        { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const signed short n)       { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const signed int n)         { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const signed long n)        { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const signed long long n)   { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const unsigned char n)      { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const wchar_t n)            { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const unsigned short n)     { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const unsigned int n)       { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const unsigned long n)      { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const unsigned long long n) { z.Re /= n; z.Im /= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const float f)              { z.Re /= f; z.Im /= f; return z; }
  inline ef_complex& operator/=(ef_complex& z, const double d)             { z.Re /= d; z.Im /= d; return z; }
  inline ef_complex& operator/=(ef_complex& z, const long double ld)       { z.Re /= ld; z.Im /= ld; return z; }

  // Global self add/sub/mul/div of ef_complex& with const e_float&.
  inline ef_complex& operator+=(ef_complex& z, const e_float& v) { z.Re += v;            return z; }
  inline ef_complex& operator-=(ef_complex& z, const e_float& v) { z.Re -= v;            return z; }
  inline ef_complex& operator*=(ef_complex& z, const e_float& v) { z.Re *= v; z.Im *= v; return z; }
  inline ef_complex& operator/=(ef_complex& z, const e_float& v) { z.Re /= v; z.Im /= v; return z; }

#endif // _E_FLOAT_COMPLEX_HPP_
