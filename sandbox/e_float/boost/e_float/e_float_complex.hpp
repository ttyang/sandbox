
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifndef _E_FLOAT_COMPLEX_HPP_
  #define _E_FLOAT_COMPLEX_HPP_

  #include <e_float/e_float.hpp>

  // A separate complex class for e_float has been created. Even though
  // a generic template class std::complex<T> exists, the C++ specification
  // ISO7IEC 14882:2003 paragraph 26.2/2 indicates that: "The effect of
  // instantiating the template complex<T> for any type other than float,
  // double or long double is unspecified". The strict interpretation thereof
  // disallows both using the template class std::complex<T> with e_float
  // as well as creating a template specialization for e_float.
  // Therefore the separate class ef_complex is needed.

  class ef_complex
  {
  private:

    e_float Re;
    e_float Im;

  public:

    explicit ef_complex(const  INT32 n) : Re(n), Im(ef::zero()) { }
    explicit ef_complex(const  INT64 n) : Re(n), Im(ef::zero()) { }
    explicit ef_complex(const UINT32 u) : Re(u), Im(ef::zero()) { }
    explicit ef_complex(const UINT64 u) : Re(u), Im(ef::zero()) { }
    explicit ef_complex(const double d) : Re(d), Im(ef::zero()) { }

    ef_complex(const e_float& re = ef::zero(), const e_float& im = ef::zero()) : Re(re), Im(im) { }

    ef_complex(const ef_complex& z) : Re(z.Re), Im(z.Im) { }

    e_float real(void) const { return Re; }
    e_float imag(void) const { return Im; }

    static e_float real(const ef_complex& z) { return z.Re; }
    static e_float imag(const ef_complex& z) { return z.Im; }

    e_float norm(void) const { return (Re * Re) + (Im * Im); }

    ef_complex& operator=(const ef_complex& v) { Re  = v.Re; Im  = v.Im;       return *this; }
    ef_complex& operator=(const e_float& v)    { Re  = v;    Im  = ef::zero(); return *this; }

    ef_complex& operator+=(const ef_complex& v) { Re += v.Re; Im += v.Im; return *this; }
    ef_complex& operator-=(const ef_complex& v) { Re -= v.Re; Im -= v.Im; return *this; }

    ef_complex& operator*=(const ef_complex& v)
    {
      const e_float re = (Re * v.Re) - (Im * v.Im);
      const e_float im = (Re * v.Im) + (Im * v.Re);

      Re = re;
      Im = im;

      return *this;
    }

    ef_complex& operator/=(const ef_complex& v)
    {
      const e_float one_over_denom = ef::one() / v.norm();

      const e_float re = ((Re * v.Re) + (Im * v.Im)) * one_over_denom;
      const e_float im = ((Im * v.Re) - (Re * v.Im)) * one_over_denom;

      Re = re;
      Im = im;

      return *this;
    }

    ef_complex& operator+=(const e_float& v) { Re += v;          return *this; }
    ef_complex& operator-=(const e_float& v) { Re -= v;          return *this; }
    ef_complex& operator*=(const e_float& v) { Re *= v; Im *= v; return *this; }
    ef_complex& operator/=(const e_float& v) { Re /= v; Im /= v; return *this; }

    // Operators pre-increment and post-increment
    const ef_complex& operator++(void) { ++Re; return *this; }
          ef_complex  operator++(int)  { const ef_complex w(*this); ++Re; return w; }

    // Operators pre-decrement and post-decrement
    const ef_complex& operator--(void) { --Re; return *this; }
          ef_complex  operator--(int)  { const ef_complex w(*this); --Re; return w; }

    // Unary operators.
    ef_complex  operator-(void) const { return ef_complex(-Re, -Im); }
    ef_complex& operator+(void)       { return *this; }

    // Operators with integer.
    ef_complex& operator+=(const INT32 n) { Re += n; return *this; }
    ef_complex& operator-=(const INT32 n) { Re -= n; return *this; }
    ef_complex& operator*=(const INT32 n) { Re *= n; Im *= n; return *this; }
    ef_complex& operator/=(const INT32 n) { Re /= n; Im /= n; return *this; }

    bool isnan   (void) const { return Re.isnan()    || Im.isnan(); }
    bool isinf   (void) const { return Re.isinf()    || Im.isinf(); }
    bool isfinite(void) const { return Re.isfinite() && Im.isfinite(); }
    bool isneg   (void) const { return Re.isneg(); }
    bool ispos   (void) const { return Re.ispos(); }
    bool isint   (void) const { return Re.isint()  && Im.iszero(); }
    bool isone   (void) const { return Re.isone()  && Im.iszero(); }
    bool iszero  (void) const { return Re.iszero() && Im.iszero(); }
  };

  inline std::ostream& operator<<(std::ostream& os, const ef_complex& z) { return os << '(' << z.real() << ',' << z.imag() << ')'; }

#endif // _E_FLOAT_COMPLEX_HPP_
