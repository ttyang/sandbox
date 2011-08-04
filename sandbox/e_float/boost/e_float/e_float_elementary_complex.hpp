
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_ELEMENTARY_COMPLEX_HPP_
  #define _E_FLOAT_ELEMENTARY_COMPLEX_HPP_

  #include <complex>

  #include <e_float/e_float_complex.hpp>

  namespace efz
  {
    std::complex<double> to_double(const ef_complex& z);

    inline e_float norm(const ef_complex& z) { return z.norm(); }
           e_float abs (const ef_complex& z);
           e_float arg (const ef_complex& z);
    inline e_float real(const ef_complex& z) { return z.real(); }
    inline e_float imag(const ef_complex& z) { return z.imag(); }

    inline ef_complex conj(const ef_complex& z) { return ef_complex(z.real(), -z.imag()); }
    inline ef_complex iz  (const ef_complex& z) { const e_float tmp(z.real()); return ef_complex(-z.imag(), tmp); }

    ef_complex polar   (const e_float& mod, const e_float& arg);
    ef_complex sin     (const ef_complex& z);
    ef_complex cos     (const ef_complex& z);
    ef_complex tan     (const ef_complex& z);
    void       sincos  (const ef_complex& z, ef_complex* const p_sin, ef_complex* const p_cos);
    ef_complex csc     (const ef_complex& z);
    ef_complex sec     (const ef_complex& z);
    ef_complex cot     (const ef_complex& z);
    ef_complex asin    (const ef_complex& z);
    ef_complex acos    (const ef_complex& z);
    ef_complex atan    (const ef_complex& z);
    ef_complex inv     (const ef_complex& z);
    ef_complex sqrt    (const ef_complex& z);
    ef_complex exp     (const ef_complex& z);
    ef_complex log     (const ef_complex& z);
    ef_complex log10   (const ef_complex& z);
    ef_complex loga    (const ef_complex& a, const ef_complex& z);
    ef_complex pown    (const ef_complex& z, const INT64 p);
    ef_complex pow     (const ef_complex& z, const ef_complex& a);
    ef_complex rootn   (const ef_complex& z, const INT32 p);
    ef_complex sinh    (const ef_complex& z);
    ef_complex cosh    (const ef_complex& z);
    ef_complex tanh    (const ef_complex& z);
    void       sinhcosh(const ef_complex& z, ef_complex* const p_sinh, ef_complex* const p_cosh);
    ef_complex asinh   (const ef_complex& z);
    ef_complex acosh   (const ef_complex& z);
    ef_complex atanh   (const ef_complex& z);
  }

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

#endif // _E_FLOAT_ELEMENTARY_COMPLEX_HPP_
