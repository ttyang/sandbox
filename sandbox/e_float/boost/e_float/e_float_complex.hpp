
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

#endif // _E_FLOAT_COMPLEX_HPP_
