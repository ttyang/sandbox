
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

  // Global arithmetic operators with const ef_complex&, const e_float& and INT32
  inline ef_complex operator+(const ef_complex& u, const ef_complex& v) { return ef_complex(u) += v; }
  inline ef_complex operator-(const ef_complex& u, const ef_complex& v) { return ef_complex(u) -= v; }
  inline ef_complex operator*(const ef_complex& u, const ef_complex& v) { return ef_complex(u) *= v; }
  inline ef_complex operator/(const ef_complex& u, const ef_complex& v) { return ef_complex(u) /= v; }

  inline ef_complex operator+(const ef_complex& u, const e_float& v) { return ef_complex(u.real() + v, u.imag()); }
  inline ef_complex operator-(const ef_complex& u, const e_float& v) { return ef_complex(u.real() - v, u.imag()); }
  inline ef_complex operator*(const ef_complex& u, const e_float& v) { return ef_complex(u.real() * v, u.imag() * v); }
  inline ef_complex operator/(const ef_complex& u, const e_float& v) { return ef_complex(u.real() / v, u.imag() / v); }

  inline ef_complex operator+(const e_float& u, const ef_complex& v) { return ef_complex(u + v.real(), v.imag()); }
  inline ef_complex operator-(const e_float& u, const ef_complex& v) { return ef_complex(u - v.real(), -v.imag()); }
  inline ef_complex operator*(const e_float& u, const ef_complex& v) { return ef_complex(u * v.real(), u * v.imag()); }
  inline ef_complex operator/(const e_float& u, const ef_complex& v) { const e_float norm = (v.real() * v.real()) + (v.imag() * v.imag()); return ef_complex((u * v.real()) / norm, (-u * v.imag()) / norm); }

  inline ef_complex operator+(const INT32 n, const ef_complex& v) { return ef_complex(e_float(n)) += v; }
  inline ef_complex operator-(const INT32 n, const ef_complex& v) { return ef_complex(e_float(n)) -= v; }
  inline ef_complex operator*(const INT32 n, const ef_complex& v) { return ef_complex(v.real() * n, v.imag() * n); }
  inline ef_complex operator/(const INT32 n, const ef_complex& v) { const e_float norm = (v.real() * v.real()) + (v.imag() * v.imag()); return ef_complex((n * v.real()) / norm, (-n * v.imag()) / norm); }

  inline ef_complex operator+(const ef_complex& z, const INT32 n) { return ef_complex(z.real() + n, z.imag()); }
  inline ef_complex operator-(const ef_complex& z, const INT32 n) { return ef_complex(z.real() - n, z.imag()); }
  inline ef_complex operator*(const ef_complex& z, const INT32 n) { return ef_complex(z.real() * n, z.imag() * n); }
  inline ef_complex operator/(const ef_complex& z, const INT32 n) { return ef_complex(z.real() / n, z.imag() / n); }

  inline ef_complex& operator+=(ef_complex& z, const INT32 n) { z.Re += n;            return z; }
  inline ef_complex& operator-=(ef_complex& z, const INT32 n) { z.Re -= n;            return z; }
  inline ef_complex& operator*=(ef_complex& z, const INT32 n) { z.Re *= n; z.Im *= n; return z; }
  inline ef_complex& operator/=(ef_complex& z, const INT32 n) { z.Re /= n; z.Im /= n; return z; }

  inline ef_complex& operator+=(ef_complex& z, const e_float& v) { z.Re += v;            return z; }
  inline ef_complex& operator-=(ef_complex& z, const e_float& v) { z.Re -= v;            return z; }
  inline ef_complex& operator*=(ef_complex& z, const e_float& v) { z.Re *= v; z.Im *= v; return z; }
  inline ef_complex& operator/=(ef_complex& z, const e_float& v) { z.Re /= v; z.Im /= v; return z; }

#endif // _E_FLOAT_ELEMENTARY_COMPLEX_HPP_
