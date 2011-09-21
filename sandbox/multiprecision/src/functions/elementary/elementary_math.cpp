
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>

using boost::multiprecision::mp_float;

#if defined(__GNUC__)
  static inline int _isnan (double x) { return std::isnan   <double>(x); }
  static inline int _finite(double x) { return std::isfinite<double>(x); }
#endif

mp_float boost::multiprecision::floor(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x) || boost::multiprecision::isint(x)) { return x; }

  return (boost::multiprecision::isneg(x) ? boost::multiprecision::integer_part(x - boost::multiprecision::one())
                       : boost::multiprecision::integer_part(x));
}

mp_float boost::multiprecision::ceil(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x) || boost::multiprecision::isint(x)) { return x; }

  return (boost::multiprecision::isneg(x) ? boost::multiprecision::integer_part(x)
                       : boost::multiprecision::integer_part(x + boost::multiprecision::one()));
}

boost::int32_t boost::multiprecision::sgn(const mp_float& x)
{
  if(boost::multiprecision::iszero(x))
  {
    return static_cast<boost::int32_t>(0);
  }
  else
  {
    return (boost::multiprecision::isneg(x) ? static_cast<boost::int32_t>(-1) : static_cast<boost::int32_t>(1));
  }
}

mp_float ldexp(const mp_float& v, int e)
{
  return v * boost::multiprecision::pow2(e);
}

mp_float boost::multiprecision::frexp(const mp_float& v, int* expon)
{
  double d;
  boost::int64_t i;

  v.extract_parts(d, i);

  *expon = static_cast<int>(i);

  return v * boost::multiprecision::pow2(static_cast<boost::int64_t>(-i));
}

mp_float boost::multiprecision::fmod(const mp_float& v1, const mp_float& v2)
{
  const mp_float n = (boost::multiprecision::isneg(v1) ? boost::multiprecision::ceil(v1 / v2) : boost::multiprecision::floor(v1 / v2));

  return v1 - (n * v2);
}

bool boost::multiprecision::isfinite(const double x) { return (::_finite(x) != 0); }
bool boost::multiprecision::isnan   (const double x) { return (::_isnan (x) != 0); }

double boost::multiprecision::to_double(const mp_float& x)   { return x.extract_double(); }
double boost::multiprecision::to_double(const mp_complex& z) { return boost::multiprecision::to_double(z.real()); }

boost::int64_t boost::multiprecision::to_int64(const double x)      { return static_cast<boost::int64_t>(x); }
boost::int64_t boost::multiprecision::to_int64(const mp_float& x)    { return static_cast<boost::int64_t>(x.extract_signed_long_long()); }
boost::int64_t boost::multiprecision::to_int64(const mp_complex& z) { return boost::multiprecision::to_int64(z.real()); }

bool boost::multiprecision::isint(const double x)
{
  static const double delta = (std::numeric_limits<double>::min)() * 2.0;

  const double xx = ::fabs(x);

  if((xx - ::floor(xx)) < delta)
  {
    return true;
  }
  else if((::ceil(xx) - xx) < delta)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boost::int32_t boost::multiprecision::to_int32(const double x)
{
  const boost::int64_t n32_max = static_cast<boost::int64_t>((std::numeric_limits<boost::int32_t>::max)());
  const boost::int64_t n32_min = static_cast<boost::int64_t>((std::numeric_limits<boost::int32_t>::min)());

  const boost::int64_t n64 = boost::multiprecision::to_int64(x);

  return static_cast<boost::int32_t>((std::min)((std::max)(n64, n32_min), n32_max));
}

boost::int32_t boost::multiprecision::to_int32(const mp_float& x)
{
  const boost::int64_t n32_max = static_cast<boost::int64_t>((std::numeric_limits<boost::int32_t>::max)());
  const boost::int64_t n32_min = static_cast<boost::int64_t>((std::numeric_limits<boost::int32_t>::min)());

  const boost::int64_t n64 = boost::multiprecision::to_int64(x);

  return static_cast<boost::int32_t>((std::min)((std::max)(n64, n32_min), n32_max));
}

boost::int32_t boost::multiprecision::to_int32(const mp_complex& z)
{
  return boost::multiprecision::to_int32(z.real());
}

void boost::multiprecision::to_parts(const mp_float& x, double& mantissa, boost::int64_t& exponent)
{
  x.extract_parts(mantissa, exponent);
}

mp_float boost::multiprecision::integer_part(const mp_float& x)
{
  return x.extract_integer_part();
}

mp_float boost::multiprecision::decimal_part(const mp_float& x)
{
  return x.extract_decimal_part();
}

bool boost::multiprecision::small_arg(const double x)
{
  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = ::pow(std::numeric_limits<double>::epsilon(), one_sixth);

  return (::fabs(x) < small_tol);
}

bool boost::multiprecision::small_arg(const mp_float& x)
{
  static const double lim_d = static_cast<double>(static_cast<boost::int32_t>(boost::multiprecision::tol())) / 10.0;
  static const boost::int64_t  lim   = (std::max)(static_cast<boost::int64_t>(lim_d), static_cast<boost::int64_t>(6));

  return (x.order() < static_cast<boost::int64_t>(-lim));
}

bool boost::multiprecision::small_arg(const mp_complex& z)
{
  return boost::multiprecision::small_arg(boost::multiprecision::abs(z));
}

bool boost::multiprecision::large_arg(const double x)
{
  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = ::pow(std::numeric_limits<double>::epsilon(), one_sixth);
  static const double large_tol = 1.0 / small_tol;

  return (::fabs(x) > large_tol);
}

bool boost::multiprecision::large_arg(const mp_float& x)
{
  static const double lim_d = static_cast<double>(static_cast<boost::int32_t>(boost::multiprecision::tol())) / 10.0;
  static const boost::int64_t  lim   = (std::max)(static_cast<boost::int64_t>(lim_d), static_cast<boost::int64_t>(6));

  return (x.order() > lim);
}

bool boost::multiprecision::large_arg(const mp_complex& z) { return boost::multiprecision::large_arg(z.real()); }

bool boost::multiprecision::near_one(const double x)      { return boost::multiprecision::small_arg(::fabs(1.0 - x)); }
bool boost::multiprecision::near_one(const mp_float& x)    { return boost::multiprecision::small_arg(boost::multiprecision::fabs(boost::multiprecision::one() - x)); }
bool boost::multiprecision::near_one(const mp_complex& z) { return boost::multiprecision::near_one(z.real()) && boost::multiprecision::iszero(z.imag()); }

bool boost::multiprecision::near_int(const double x)
{
  if(boost::multiprecision::isint(x))
  {
    return true;
  }
  else
  {
    const double xx = ::fabs(x);

    if(boost::multiprecision::small_arg(xx - ::floor(xx)))
    {
      return true;
    }
    else if(boost::multiprecision::small_arg(::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool boost::multiprecision::near_int(const mp_float& x)
{
  if(boost::multiprecision::isint(x))
  {
    return true;
  }
  else
  {
    const mp_float xx = boost::multiprecision::fabs(x);

    if(boost::multiprecision::small_arg(xx - boost::multiprecision::floor(xx)))
    {
      return true;
    }
    else if(boost::multiprecision::small_arg(boost::multiprecision::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool boost::multiprecision::near_int(const mp_complex& z)
{
  if(boost::multiprecision::isint(z))
  {
    return true;
  }
  else
  {
    return boost::multiprecision::iszero(z.imag()) && boost::multiprecision::near_int(z.real());
  }
}
