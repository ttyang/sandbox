
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} © ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_complex.hpp>
#include <e_float/e_float_elementary.hpp>

#if defined(__GNUC__)
  static inline INT32 _isnan (double x) { return static_cast<INT32>(std::isnan   <double>(x)); }
  static inline INT32 _finite(double x) { return static_cast<INT32>(std::isfinite<double>(x)); }
#endif

e_float ef::floor(const e_float& x)
{
  if(!ef::isfinite(x) || ef::isint(x)) { return x; }

  return ef::isneg(x) ? ef::integer_part(x - ef::one())
                      : ef::integer_part(x);
}

e_float ef::ceil(const e_float& x)
{
  if(!ef::isfinite(x) || ef::isint(x)) { return x; }

  return ef::isneg(x) ? ef::integer_part(x)
                      : ef::integer_part(x + ef::one());
}

INT32 ef::sgn(const e_float& x)
{
  if(ef::iszero(x))
  {
    return static_cast<INT32>(0);
  }
  else
  {
    return (ef::isneg(x) ? static_cast<INT32>(-1) : static_cast<INT32>(1));
  }
}

bool ef::isfinite(const double x) { return static_cast<INT32>(::_finite(x)) == static_cast<INT32>(1); }
bool ef::isnan   (const double x) { return static_cast<INT32>(::_isnan (x)) == static_cast<INT32>(1); }

double ef::to_double(const e_float& x)    { return x.extract_double(); }
double ef::to_double(const ef_complex& z) { return ef::to_double(z.real()); }

INT64 ef::to_int64(const double x)      { return static_cast<INT64>(x); }
INT64 ef::to_int64(const e_float& x)    { return x.extract_int64(); }
INT64 ef::to_int64(const ef_complex& z) { return ef::to_int64(z.real()); }

bool ef::isint(const double x)
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

INT32 ef::to_int32(const double x)
{
  static const INT64 n32_max = static_cast<INT64>((std::numeric_limits<INT32>::max)());
  static const INT64 n32_min = static_cast<INT64>((std::numeric_limits<INT32>::min)());

  INT64 n64 = ef::to_int64(x);

  if(n64 < n32_min) { n64 = n32_min; }
  if(n64 > n32_max) { n64 = n32_max; }

  return static_cast<INT32>(n64);
}

INT32 ef::to_int32(const e_float& x)
{
  static const INT64 n32_max = static_cast<INT64>((std::numeric_limits<INT32>::max)());
  static const INT64 n32_min = static_cast<INT64>((std::numeric_limits<INT32>::min)());

  INT64 n64 = ef::to_int64(x);

  if(n64 < n32_min) { n64 = n32_min; }
  if(n64 > n32_max) { n64 = n32_max; }

  return static_cast<INT32>(n64);
}

INT32 ef::to_int32(const ef_complex& z)
{
  return ef::to_int32(z.real());
}

void ef::to_parts(const e_float& x, double& mantissa, INT64& exponent)
{
  x.extract_parts(mantissa, exponent);
}

e_float ef::integer_part(const e_float& x)
{
  return x.extract_integer_part();
}

e_float ef::decimal_part(const e_float& x)
{
  return x.extract_decimal_part();
}

bool ef::small_arg(const double x)
{
  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = ::pow(std::numeric_limits<double>::epsilon(), one_sixth);

  return (::fabs(x) < small_tol);
}

bool ef::small_arg(const e_float& x)
{
  static const double lim_d = static_cast<double>(static_cast<INT32>(ef::tol())) / 10.0;
  static const INT64  lim_n = static_cast<INT64>(lim_d);
  static const INT64  lim   = (lim_n < 6 ? 6 : lim_n);

  return x.order() < -lim;
}

bool ef::small_arg(const ef_complex& z)
{
  return ef::small_arg(efz::abs(z));
}

bool ef::large_arg(const double x)
{
  static const double one_sixth = 1.0 / 6.0;
  static const double small_tol = ::pow(std::numeric_limits<double>::epsilon(), one_sixth);
  static const double large_tol = 1.0 / small_tol;

  return ::fabs(x) > large_tol;
}

bool ef::large_arg(const e_float& x)
{
  static const double lim_d = static_cast<double>(static_cast<INT32>(ef::tol())) / 10.0;
  static const INT64  lim_n = static_cast<INT64>(lim_d);
  static const INT64  lim   = (lim_n < 6 ? 6 : lim_n);

  return x.order() > lim;
}

bool ef::large_arg(const ef_complex& z) { return ef::large_arg(z.real()); }

bool ef::near_one(const double x)      { return ef::small_arg(::fabs(1.0 - x)); }
bool ef::near_one(const e_float& x)    { return ef::small_arg(ef::fabs(ef::one() - x)); }
bool ef::near_one(const ef_complex& z) { return ef::near_one(z.real()) && ef::iszero(z.imag()); }

bool ef::near_int(const double x)
{
  if(ef::isint(x))
  {
    return true;
  }
  else
  {
    const double xx = ::fabs(x);

    if(ef::small_arg(xx - ::floor(xx)))
    {
      return true;
    }
    else if(ef::small_arg(::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool ef::near_int(const e_float& x)
{
  if(ef::isint(x))
  {
    return true;
  }
  else
  {
    const e_float xx = ef::fabs(x);

    if(ef::small_arg(xx - ef::floor(xx)))
    {
      return true;
    }
    else if(ef::small_arg(ef::ceil(xx) - xx))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool ef::near_int(const ef_complex& z)
{
  if(ef::isint(z))
  {
    return true;
  }
  else
  {
    return ef::iszero(z.imag()) && ef::near_int(z.real());
  }
}
