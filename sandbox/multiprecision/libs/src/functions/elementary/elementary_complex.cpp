
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>
#include <boost/multiprecision/utility/util_power_x_pow_n.hpp>

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

bool operator==(const mp_complex& u, const mp_float& v) { return ((u.real() == v) &&  boost::multiprecision::iszero(u.imag())); }
bool operator!=(const mp_complex& u, const mp_float& v) { return ((u.real() != v) || !boost::multiprecision::iszero(u.imag())); }

bool operator==(const mp_float& u, const mp_complex& v) { return ((u == v.real()) &&  boost::multiprecision::iszero(v.imag())); }
bool operator!=(const mp_float& u, const mp_complex& v) { return ((u != v.real()) || !boost::multiprecision::iszero(v.imag())); }

std::ostream& boost::multiprecision::operator<<(std::ostream& os, const mp_complex& z) { return os << '(' << z.real() << ',' << z.imag() << ')'; }

mp_float boost::multiprecision::abs(const mp_complex& z) { return boost::multiprecision::sqrt(boost::multiprecision::norm(z)); }
mp_float boost::multiprecision::arg(const mp_complex& z) { return boost::multiprecision::atan2(z.imag(), z.real()); }

mp_complex boost::multiprecision::polar(const mp_float& mod, const mp_float& arg)
{
  mp_float s, c;
  boost::multiprecision::sincos(arg, &s, &c);
  return mp_complex(c, s) * mod;
}

mp_complex boost::multiprecision::sin(const mp_complex& z)
{
  mp_float sin_x, cos_x, sinh_y, cosh_y;

  boost::multiprecision::sincos  (z.real(), &sin_x, &cos_x);
  boost::multiprecision::sinhcosh(z.imag(), &sinh_y, &cosh_y);

  return mp_complex(sin_x * cosh_y, cos_x * sinh_y);
}

mp_complex boost::multiprecision::cos(const mp_complex& z)
{
  mp_float sin_x, cos_x, sinh_y, cosh_y;

  boost::multiprecision::sincos  (z.real(), &sin_x,  &cos_x);
  boost::multiprecision::sinhcosh(z.imag(), &sinh_y, &cosh_y);

  return mp_complex(cos_x * cosh_y, -(sin_x * sinh_y));
}

void boost::multiprecision::sincos(const mp_complex& z, mp_complex* const p_sin, mp_complex* const p_cos)
{
  mp_float sin_x, cos_x, sinh_y, cosh_y;

  boost::multiprecision::sincos  (z.real(), &sin_x,  &cos_x);
  boost::multiprecision::sinhcosh(z.imag(), &sinh_y, &cosh_y);

  const bool b_wants_sin = (p_sin != static_cast<mp_complex* const>(0u));
  const bool b_wants_cos = (p_cos != static_cast<mp_complex* const>(0u));

  if(b_wants_sin) { *p_sin = mp_complex(sin_x * cosh_y, cos_x * sinh_y); }
  if(b_wants_cos) { *p_cos = mp_complex(cos_x * cosh_y, -(sin_x * sinh_y)); }
}

mp_complex boost::multiprecision::tan(const mp_complex& z)
{
  mp_complex s, c;
  boost::multiprecision::sincos(z, &s, &c);
  return s * boost::multiprecision::inv(c);
}

mp_complex boost::multiprecision::csc(const mp_complex& z) { return boost::multiprecision::inv(boost::multiprecision::sin(z)); }
mp_complex boost::multiprecision::sec(const mp_complex& z) { return boost::multiprecision::inv(boost::multiprecision::cos(z)); }
mp_complex boost::multiprecision::cot(const mp_complex& z) { return boost::multiprecision::inv(boost::multiprecision::tan(z)); }

mp_complex boost::multiprecision::asin(const mp_complex& z)
{
  return -boost::multiprecision::iz(boost::multiprecision::log(boost::multiprecision::iz(z) + boost::multiprecision::sqrt(boost::multiprecision::one() - (z * z))));
}

mp_complex boost::multiprecision::acos(const mp_complex& z)
{
  return mp_complex(boost::multiprecision::pi_half(), boost::multiprecision::zero()) - boost::multiprecision::asin(z);
}

mp_complex boost::multiprecision::atan(const mp_complex& z)
{
  const mp_complex izz = boost::multiprecision::iz(z);
  return boost::multiprecision::iz(boost::multiprecision::log(boost::multiprecision::one() - izz) - boost::multiprecision::log(boost::multiprecision::one() + izz)) / static_cast<boost::int32_t>(2);
}

mp_complex boost::multiprecision::inv(const mp_complex& z)
{
  // Compute inverse 1 / (x + iy) = (x - iy) / (x^2 + y^2)
  return mp_complex(z.real(), -z.imag()) * boost::multiprecision::norm(z).calculate_inv();
}

mp_complex boost::multiprecision::sqrt(const mp_complex& z)
{
  // Equation from MPFUN documentation page 12.
  // See: http://www.nersc.gov/~dhb/mpdist/mpdist.html

  // Pure zero?
  if(boost::multiprecision::iszero(z))
  {
    return boost::multiprecision::zero();
  }
  else
  {
    // sqrt(*this) = (s, I / 2s)     for R >= 0
    //               (|I| / 2s, +-s) for R <  0
    // where s = sqrt{ [ |R| + sqrt(R^2 + I^2) ] / 2 },
    // and the +- sign is the same as the sign of I.
    const mp_float s = boost::multiprecision::sqrt((boost::multiprecision::fabs(z.real()) + boost::multiprecision::abs(z)) / static_cast<boost::int32_t>(2));
    
    if(boost::multiprecision::iszero(z.real()) || !boost::multiprecision::isneg(z.real()))
    {
      return mp_complex(s, (z.imag() / s) / static_cast<boost::int32_t>(2));
    }
    else
    {
      const bool imag_is_pos = boost::multiprecision::iszero(z.imag()) || (!boost::multiprecision::isneg(z.imag()));

      return mp_complex((boost::multiprecision::fabs(z.imag()) / s) / static_cast<boost::int32_t>(2), (imag_is_pos ? s : -s));
    }
  }
}

mp_complex boost::multiprecision::exp(const mp_complex& z)
{
  mp_float s, c;
  boost::multiprecision::sincos(z.imag(), &s, &c);
  return mp_complex(c , s) * boost::multiprecision::exp(z.real());
}

mp_complex boost::multiprecision::log(const mp_complex& z)
{
  return mp_complex(boost::multiprecision::log(boost::multiprecision::norm(z)) / static_cast<boost::int32_t>(2), boost::multiprecision::atan2(z.imag(), z.real()));
}

mp_complex boost::multiprecision::log10(const mp_complex& z)
{
  return boost::multiprecision::log(z) / boost::multiprecision::ln10();
}

mp_complex boost::multiprecision::loga(const mp_complex& a, const mp_complex& z)
{
  return boost::multiprecision::log(z) / boost::multiprecision::log(a);
}

mp_complex boost::multiprecision::pown(const mp_complex& z, const boost::int64_t p)
{
  return boost::multiprecision::utility::x_pow_n_template<mp_complex>(z, p);
}

mp_complex boost::multiprecision::pow(const mp_complex& z, const mp_complex& a)
{
  return (boost::multiprecision::isint(a) ? boost::multiprecision::pown(z, boost::multiprecision::to_int64(a.real()))
                       : boost::multiprecision::exp(a * boost::multiprecision::log(z)));
}

mp_complex boost::multiprecision::rootn(const mp_complex& z, const boost::int32_t p)
{
  if(p < static_cast<boost::int32_t>(0))
  {
    return boost::multiprecision::pown(boost::multiprecision::one() / z, static_cast<boost::int64_t>(-p));
  }
  else if(p == static_cast<boost::int32_t>(0))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }
  else if(p == static_cast<boost::int32_t>(1))
  {
    return z;
  }
  else
  {
    return boost::multiprecision::polar(boost::multiprecision::rootn(boost::multiprecision::norm(z), static_cast<boost::int32_t>(2) * p), boost::multiprecision::arg(z) / p);
  }
}

mp_complex boost::multiprecision::sinh(const mp_complex& z)
{
  mp_float sin_y, cos_y, sinh_x, cosh_x;

  boost::multiprecision::sincos  (z.imag(), &sin_y,  &cos_y);
  boost::multiprecision::sinhcosh(z.real(), &sinh_x, &cosh_x);

  return mp_complex(cos_y * sinh_x, cosh_x * sin_y);
}

mp_complex boost::multiprecision::cosh(const mp_complex& z)
{
  mp_float sin_y, cos_y, sinh_x, cosh_x;
  
  boost::multiprecision::sincos  (z.imag(), &sin_y,  &cos_y);
  boost::multiprecision::sinhcosh(z.real(), &sinh_x, &cosh_x);

  return mp_complex(cos_y * cosh_x, sin_y * sinh_x);
}

void boost::multiprecision::sinhcosh(const mp_complex& z, mp_complex* const p_sinh, mp_complex* const p_cosh)
{
  mp_float sin_y, cos_y, sinh_x, cosh_x;

  boost::multiprecision::sincos  (z.imag(), &sin_y,  &cos_y);
  boost::multiprecision::sinhcosh(z.real(), &sinh_x, &cosh_x);

  const bool b_wants_sinh = (p_sinh != static_cast<mp_complex* const>(0u));
  const bool b_wants_cosh = (p_cosh != static_cast<mp_complex* const>(0u));

  if(b_wants_sinh) { *p_sinh = mp_complex(cos_y * sinh_x, cosh_x * sin_y); }
  if(b_wants_cosh) { *p_cosh = mp_complex(cos_y * cosh_x, sin_y  * sinh_x); }
}

mp_complex boost::multiprecision::tanh(const mp_complex& z)
{
  mp_complex sh, ch;
  boost::multiprecision::sinhcosh(z, &sh, &ch);
  return sh * boost::multiprecision::inv(ch);
}

mp_complex boost::multiprecision::asinh(const mp_complex& z)
{
  return boost::multiprecision::log(z + boost::multiprecision::sqrt((z * z) + boost::multiprecision::one()));
}

mp_complex boost::multiprecision::acosh(const mp_complex& z)
{
  const mp_complex zp(z.real() + boost::multiprecision::one(), z.imag());
  const mp_complex zm(z.real() - boost::multiprecision::one(), z.imag());

  return boost::multiprecision::log(z + (zp * boost::multiprecision::sqrt(zm / zp)));
}

mp_complex boost::multiprecision::atanh(const mp_complex& z)
{
  return (boost::multiprecision::log(boost::multiprecision::one() + z) - boost::multiprecision::log(boost::multiprecision::one() - z)) / static_cast<boost::int32_t>(2);
}
