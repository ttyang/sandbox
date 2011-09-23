
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cfloat>

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include <boost/multiprecision/utility/util_numeric_cast.hpp>

#include "mp_float_gmp_protos.h"

using boost::multiprecision::mp_float_gmp;

#if defined(__GNUC__)
  static inline boost::int32_t _isnan (float x)       { return static_cast<boost::int32_t>(std::isnan   <float>(x)); }
  static inline boost::int32_t _finite(float x)       { return static_cast<boost::int32_t>(std::isfinite<float>(x)); }
#endif

namespace
{
  const double& d_log2(void)
  {
    static const double value_log2 = 0.3010299956639811952137389;
    return value_log2;
  }

  bool has_exp_or_has_dec_predicate(const char& c)
  {
    return (   (c == static_cast<char>('e'))
            || (c == static_cast<char>('E'))
            || (c == static_cast<char>('.')));
  }
}

void mp_float_gmp::init(void)
{
  static bool precision_is_initialized;

  if(precision_is_initialized == false)
  {
    precision_is_initialized = true;
    ::mpf_set_default_prec(static_cast<unsigned long>(mp_float_digits2 + static_cast<boost::int32_t>(4)));
  }
}

const boost::int64_t& mp_float_gmp::max_exp2(void)
{
  static const boost::int64_t val_max_exp2 = static_cast<boost::int64_t>(static_cast<double>(mp_float_max_exp10) / ::d_log2());
  return val_max_exp2;
}

const boost::int64_t& mp_float_gmp::min_exp2(void)
{
  static const boost::int64_t val_min_exp2 = static_cast<boost::int64_t>(static_cast<double>(mp_float_min_exp10) / ::d_log2());
  return val_min_exp2;
}



mp_float_gmp::mp_float_gmp() : fpclass  (mp_finite),
                               prec_elem(mp_float_max_digits10)
{
  init();
  ::mpf_init(rop);
}

mp_float_gmp::mp_float_gmp(const char n) : fpclass  (mp_finite),
                                           prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (std::numeric_limits<char>::is_signed ? (n < static_cast<char>(0)) : false);
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const wchar_t n) : fpclass  (mp_finite),
                                              prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (std::numeric_limits<wchar_t>::is_signed ? (n < static_cast<wchar_t>(0)) : false);
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const signed char n) : fpclass  (mp_finite),
                                                  prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (n < static_cast<signed char>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const signed short n) : fpclass  (mp_finite),
                                                   prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (n < static_cast<signed short>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const int n) : fpclass  (mp_finite),
                                          prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (n < 0);
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const signed long n) : fpclass  (mp_finite),
                                                  prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (n < static_cast<signed long>(0));
  from_unsigned_long((!b_neg) ? static_cast<unsigned long>(n) : static_cast<unsigned long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const signed long long n) : fpclass  (mp_finite),
                                                       prec_elem(mp_float_max_digits10)
{
  init();
  const bool b_neg = (n < static_cast<signed long long>(0));
  from_unsigned_long_long((!b_neg) ? static_cast<unsigned long long>(n) : static_cast<unsigned long long>(-n));
  if(b_neg) { ::mpf_neg(rop, rop); }
}

mp_float_gmp::mp_float_gmp(const unsigned char n) : fpclass  (mp_finite),
                                                    prec_elem(mp_float_max_digits10)
{
  init();
  from_unsigned_long(static_cast<unsigned long>(n));
}

mp_float_gmp::mp_float_gmp(const unsigned short n) : fpclass  (mp_finite),
                                                     prec_elem(mp_float_max_digits10)
{
  init();
  from_unsigned_long(static_cast<unsigned long>(n));
}

mp_float_gmp::mp_float_gmp(const unsigned int n) : fpclass  (mp_finite),
                                                   prec_elem(mp_float_max_digits10)
{
  init();
  from_unsigned_long(static_cast<unsigned long>(n));
}

mp_float_gmp::mp_float_gmp(const unsigned long n) : fpclass  (mp_finite),
                                                    prec_elem(mp_float_max_digits10)
{
  init();
  from_unsigned_long(static_cast<unsigned long>(n));
}

mp_float_gmp::mp_float_gmp(const unsigned long long n) : fpclass  (mp_finite),
                                                         prec_elem(mp_float_max_digits10)
{
  init();
  from_unsigned_long_long(static_cast<unsigned long long>(n));
}

mp_float_gmp::mp_float_gmp(const float f) : fpclass  (mp_finite),
                                            prec_elem(mp_float_max_digits10)
{
  init();

  const bool b_neg = (f < 0.0f);

  if(::_finite(f) == 0)
  {
    operator=((::_isnan(f) != 0) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));
    return;
  }

  const built_in_float_parts<float> fb((!b_neg) ? f : -f);

  // Create an mp_float_gmp from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(fb.get_mantissa());

  // Scale the unsigned long long representation to the fractional
  // part of the float and multiply with the base-2 exponent.
  const int p2 = fb.get_exponent() - (std::numeric_limits<float>::digits - 1);

  if(p2 != 0) { operator*=(boost::multiprecision::pow2(static_cast<boost::int64_t>(p2))); }

  if(b_neg)
  {
    ::mpf_neg(rop, rop);
  }
}

mp_float_gmp::mp_float_gmp(const double d) : fpclass  (mp_finite),
                                        prec_elem(mp_float_max_digits10)
{
  init();
  ::mpf_init_set_d(rop, d);
}

mp_float_gmp::mp_float_gmp(const long double ld) : fpclass  (mp_finite),
                                              prec_elem(mp_float_max_digits10)
{
  init();

  const bool b_neg = (ld < static_cast<long double>(0.0));

  if(::_finite(static_cast<double>(ld)) == 0)
  {
    operator=(::_isnan(static_cast<double>(ld)) ? my_value_nan() : ((!b_neg) ? my_value_inf() : -my_value_inf()));
    return;
  }

  const built_in_float_parts<long double> fb((!b_neg) ? ld : -ld);

  // Create an mp_float_gmp from the fractional part of the
  // mantissa expressed as an unsigned long long.
  from_unsigned_long_long(fb.get_mantissa());

  // Scale the unsigned long long representation to the fractional
  // part of the long double and multiply with the base-2 exponent.
  const int p2 = fb.get_exponent() - (std::numeric_limits<long double>::digits - 1);

  if(p2 != 0) { operator*=(boost::multiprecision::pow2(static_cast<boost::int64_t>(p2))); }

  if(b_neg)
  {
    ::mpf_neg(rop, rop);
  }
}

mp_float_gmp::mp_float_gmp(const char* const s) : fpclass  (mp_finite),
                                             prec_elem(mp_float_max_digits10)
{
  init();
  static_cast<void>(rd_string(s));
}

mp_float_gmp::mp_float_gmp(const std::string& str) : fpclass  (mp_finite),
                                                prec_elem(mp_float_max_digits10)
{
  init();
  static_cast<void>(rd_string(str.c_str()));
}

mp_float_gmp::mp_float_gmp(const mp_float_gmp& mp) : fpclass  (mp.fpclass),
                                           prec_elem(mp.prec_elem)
{
  init();
  ::mpf_init_set(rop, mp.rop);
}

mp_float_gmp::mp_float_gmp(const double mantissa, const boost::int64_t exponent) : fpclass  (mp_finite),
                                                                     prec_elem(mp_float_max_digits10)
{
  init();

  const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * 2.0));

  if(mantissa_is_iszero)
  {
    if(exponent == static_cast<boost::int64_t>(0))
    {
      ::mpf_init_set(rop, boost::multiprecision::one().rop);
    }
    else
    {
      ::mpf_init_set(rop, boost::multiprecision::zero().rop);
    }
  }
  else
  {
    ::mpf_init_set(rop, boost::multiprecision::zero().rop);
    operator=(mp_float_gmp(mantissa));
    operator*=(mp_float_gmp("1E" + boost::lexical_cast<std::string>(exponent)));
  }
}

mp_float_gmp::mp_float_gmp(const ::mpf_t& op) : fpclass  (mp_finite),
                                           prec_elem(mp_float_max_digits10)
{
  init();
  ::mpf_init_set(rop, op);
}

mp_float_gmp::~mp_float_gmp()
{
  ::mpf_set_prec_raw(rop, static_cast<unsigned long int>(mp_float_digits2));
  ::mpf_clear(rop);
}

void mp_float_gmp::from_unsigned_long_long(const unsigned long long u)
{
  if(u <= static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    from_unsigned_long(static_cast<unsigned long>(u));
  }
  else
  {
    ::mpf_init_set_str(rop, boost::lexical_cast<std::string>(u).c_str(), 10);
  }
}

void mp_float_gmp::from_unsigned_long(const unsigned long u)
{
  ::mpf_init_set_ui(rop, u);
}

void mp_float_gmp::precision(const boost::int32_t prec_digits)
{
  const unsigned long int digits2_request = static_cast<unsigned long int>(static_cast<boost::uint64_t>(static_cast<double>(prec_digits) / ::d_log2()));
  const unsigned long int d2              = static_cast<unsigned long int>(mp_float_digits2);
  const unsigned long int digits2_set     = (std::min)(digits2_request, d2);

  prec_elem = static_cast<boost::int32_t>(static_cast<boost::int64_t>(static_cast<double>(digits2_set) * ::d_log2()));

  ::mpf_set_prec_raw(rop, digits2_set);
}

mp_float_gmp& mp_float_gmp::operator=(const mp_float_gmp& v)
{
  fpclass   = v.fpclass;
  prec_elem = v.prec_elem;

  ::mpf_set         (rop, v.rop);
  ::mpf_set_prec_raw(rop, static_cast<unsigned long>(static_cast<boost::uint64_t>(static_cast<double>(prec_elem) / ::d_log2())));

  return *this;
}

mp_float_gmp& mp_float_gmp::operator+=(const mp_float_gmp& v)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    if(v.isinf() && (isneg() != v.isneg()))
    {
      *this = std::numeric_limits<mp_float>::quiet_NaN();
    }

    return *this;
  }

  ::mpf_add(rop, rop, v.rop);

  // Check for overflow.
  long u_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed, rop));

  if(   (u_exp2_signed >= std::numeric_limits<mp_float>::max_exponent)
     && (boost::multiprecision::fabs(*this) > (std::numeric_limits<mp_float>::max)())
    )
  {
    const bool b_result_is_neg = isneg();

    *this = ((!b_result_is_neg) ?  std::numeric_limits<mp_float>::infinity()
                                : -std::numeric_limits<mp_float>::infinity());
  }

  return *this;
}

mp_float_gmp& mp_float_gmp::operator-=(const mp_float_gmp& v)
{
  // Use *this - v = -(-*this + v).
  return (negate().operator+=(v)).negate();
}

mp_float_gmp& mp_float_gmp::operator*=(const mp_float_gmp& v)
{
  const bool b_u_is_inf =   isinf();
  const bool b_v_is_inf = v.isinf();

  if(   (isnan() || v.isnan())
     || (b_u_is_inf && v.iszero())
     || (b_v_is_inf &&   iszero())
    )
  {
    return *this = std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(b_u_is_inf || b_v_is_inf)
  {
    const bool b_result_is_neg = (isneg() != v.isneg());

    *this = ((!b_result_is_neg) ?  std::numeric_limits<mp_float>::infinity()
                                : -std::numeric_limits<mp_float>::infinity());

    return *this;
  }

  // Get the base-2 exponent of *this and v and...
  long u_exp2_signed;
  long v_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed,   rop));
  static_cast<void>(::mpf_get_d_2exp(&v_exp2_signed, v.rop));

  // Check for overflow or underflow.
  const bool u_exp2_is_neg = (u_exp2_signed < static_cast<long>(0));
  const bool v_exp2_is_neg = (v_exp2_signed < static_cast<long>(0));

  if(u_exp2_is_neg == v_exp2_is_neg)
  {
    // Get the unsigned base-2 exponents of *this and v and...
    const boost::int64_t u_exp2 = ((!u_exp2_is_neg) ? u_exp2_signed : -u_exp2_signed);
    const boost::int64_t v_exp2 = ((!v_exp2_is_neg) ? v_exp2_signed : -v_exp2_signed);

    // Check the range of the upcoming multiplication.
    const bool b_result_is_out_of_range = (v_exp2 >= static_cast<long>(static_cast<long>(mp_float_max_exp) - u_exp2));

    if(b_result_is_out_of_range)
    {
      if(u_exp2_is_neg)
      {
        *this = boost::multiprecision::zero();
      }
      else
      {
        const bool b_result_is_neg = (isneg() != v.isneg());

        *this = ((!b_result_is_neg) ?  std::numeric_limits<mp_float>::infinity()
                                    : -std::numeric_limits<mp_float>::infinity());
      }

      return *this;
    }
  }

  // Multiply *this by v.
  ::mpf_mul(rop, rop, v.rop);

  return *this;
}

mp_float_gmp& mp_float_gmp::operator/=(const mp_float_gmp& v)
{
  return operator*=(mp_float_gmp(v).calculate_inv());
}

// TBD: This needs an overflow and underflow check.
mp_float_gmp& mp_float_gmp::add_unsigned_long_long(const unsigned long long n)
{
  if(n <= (std::numeric_limits<unsigned long>::max)())
  {
    ::mpf_add_ui(rop, rop, static_cast<unsigned long>(n));
    return *this;
  }
  else
  {
    return operator+=(mp_float_gmp(n));
  }
}

// TBD: This needs an overflow and underflow check.
mp_float_gmp& mp_float_gmp::sub_unsigned_long_long(const unsigned long long n)
{
  if(n <= (std::numeric_limits<unsigned long>::max)())
  {
    ::mpf_sub_ui(rop, rop, static_cast<unsigned long>(n));
    return *this;
  }
  else
  {
    return operator+=(mp_float_gmp(n));
  }
}

mp_float_gmp& mp_float_gmp::mul_unsigned_long_long(const unsigned long long n)
{
  // Multiply *this with a constant unsigned long long.

  const bool b_u_is_inf  = isinf();
  const bool b_n_is_zero = (n == static_cast<boost::int32_t>(0));

  if(isnan() || (b_u_is_inf && b_n_is_zero))
  {
    return (*this = std::numeric_limits<mp_float>::quiet_NaN());
  }

  if(b_u_is_inf)
  {
    *this = ((!isneg()) ?  std::numeric_limits<mp_float>::infinity()
                        : -std::numeric_limits<mp_float>::infinity());
    return *this;
  }

  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator*=(mp_float_gmp(n));
  }
  else
  {
    ::mpf_mul_ui(rop, rop, static_cast<unsigned long>(n));
  }

  // Check for overflow.
  long u_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed, rop));

  if(   (u_exp2_signed >= std::numeric_limits<mp_float>::max_exponent)
     && (boost::multiprecision::fabs(*this) > (std::numeric_limits<mp_float>::max)())
    )
  {
    *this = ((!isneg()) ?  std::numeric_limits<mp_float>::infinity()
                        : -std::numeric_limits<mp_float>::infinity());
  }

  return *this;
}

mp_float_gmp& mp_float_gmp::div_unsigned_long_long(const unsigned long long n)
{
  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    *this = ((!isneg()) ?  std::numeric_limits<mp_float>::infinity()
                        : -std::numeric_limits<mp_float>::infinity());
    return *this;
  }

  if(n == static_cast<boost::int32_t>(0))
  {
    // Divide by 0.
    if(iszero())
    {
      return (*this = std::numeric_limits<mp_float>::quiet_NaN());
    }
    else
    {
      *this = ((!isneg()) ?  std::numeric_limits<mp_float>::infinity()
                          : -std::numeric_limits<mp_float>::infinity());
      return *this;
    }
  }

  if(iszero())
  {
    return *this;
  }

  if(n > static_cast<unsigned long long>((std::numeric_limits<unsigned long>::max)()))
  {
    operator/=(mp_float_gmp(n));
  }
  else
  {
    ::mpf_div_ui(rop, rop, static_cast<unsigned long>(n));
  }

  // Check for underflow.
  long u_exp2_signed;
  static_cast<void>(::mpf_get_d_2exp(&u_exp2_signed, rop));

  if(   (u_exp2_signed <= std::numeric_limits<mp_float>::min_exponent)
     && (boost::multiprecision::fabs(*this) < (std::numeric_limits<mp_float>::min)())
    )
  {
    return (*this = boost::multiprecision::zero());
  }

  return *this;
}

mp_float_gmp& mp_float_gmp::calculate_inv(void)
{
  // Compute the inverse of *this.

  bool b_result_is_neg = isneg();

  if(iszero())
  {
    *this = ((!b_result_is_neg) ?  std::numeric_limits<mp_float>::infinity()
                                : -std::numeric_limits<mp_float>::infinity());

    return *this;
  }

  if(isnan())
  {
    return *this;
  }

  if(isinf())
  {
    return (*this = boost::multiprecision::zero());
  }

  if(isone())
  {
    *this = ((!b_result_is_neg) ? boost::multiprecision::one() : -boost::multiprecision::one());

    return *this;
  }

  ::mpf_ui_div(rop, static_cast<unsigned long int>(1u), rop);

  return *this;
}

mp_float_gmp& mp_float_gmp::calculate_sqrt(void)
{
  // Compute the square root of *this.

  if(isneg() || !isfinite())
  {
    return *this = std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(iszero() || isone())
  {
    return *this;
  }

  ::mpf_sqrt(rop, rop);

  return *this;
}

boost::int32_t mp_float_gmp::cmp(const mp_float_gmp& v) const
{
  // Handle all non-finite cases.
  if((!isfinite()) || (!v.isfinite()))
  {
    // NaN can never equal NaN. Return an implementation-dependent
    // signed result. Also note that comparison of NaN with NaN
    // using operators greater-than or less-than is undefined.
    if(isnan() || v.isnan()) { return (isnan() ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(-1)); }

    if(isinf() && v.isinf())
    {
      // Both *this and v are infinite. They are equal if they have the same sign.
      // Otherwise, *this is less than v if and only if *this is negative.
      return ((isneg() == v.isneg()) ? static_cast<boost::int32_t>(0) : (isneg() ? static_cast<boost::int32_t>(-1) : static_cast<boost::int32_t>(1)));
    }

    if(isinf())
    {
      // *this is infinite, but v is finite.
      // So negative infinite *this is less than any finite v.
      // Whereas positive infinite *this is greater than any finite v.
      return (isneg() ? static_cast<boost::int32_t>(-1) : static_cast<boost::int32_t>(1));
    }
    else
    {
      // *this is finite, and v is infinite.
      // So any finite *this is greater than negative infinite v.
      // Whereas any finite *this is less than positive infinite v.
      return (v.isneg() ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(-1));
    }
  }

  // And now handle all *finite* cases.
  if(iszero() && v.iszero())
  {
    return static_cast<boost::int32_t>(0);
  }
  else
  {
    const int result = ::mpf_cmp(rop, v.rop);

    if     (result > 0) { return static_cast<boost::int32_t>(1); }
    else if(result < 0) { return static_cast<boost::int32_t>(-1); }
    else { return static_cast<boost::int32_t>(0); }
  }
}

bool mp_float_gmp::iszero(void) const
{
  return (::mpf_sgn(rop) == 0);
}

bool mp_float_gmp::isone(void) const
{
  // Check if the value of *this is identically 1 or very close to 1.
  return (isint() && (cmp(boost::multiprecision::one()) == static_cast<boost::int32_t>(0)));
}

bool mp_float_gmp::isint(void) const
{
  // Check if the value of *this is pure integer or very close to pure integer.
  return (::mpf_integer_p(rop) != 0);
}

bool mp_float_gmp::isneg(void) const
{
  if(isinf())
  {
    return (fpclass == mp_inf_neg);
  }
  else
  {
    return (::mpf_sgn(rop) < 0);
  }
}

const mp_float_gmp& mp_float_gmp::my_value_nan(void) const
{
  static mp_float_gmp val(0u);
  val.fpclass = mp_NaN;
  static const mp_float_gmp qnan(val);
  return qnan;
}

const mp_float_gmp& mp_float_gmp::my_value_inf(void) const
{
  static mp_float_gmp val(0u);
  val.fpclass = mp_inf_pos;
  static const mp_float_gmp inf(val);
  return inf;
}

mp_float_gmp& mp_float_gmp::negate(void)
{
  if(fpclass == mp_inf_pos)
  {
    fpclass = mp_inf_neg;
  }
  else if(fpclass == mp_inf_neg)
  {
    fpclass = mp_inf_pos;
  }
  else
  {
    ::mpf_neg(rop, rop);
  }

  return *this;
}

mp_float_gmp& mp_float_gmp::operator++(void) { ::mpf_add_ui(rop, rop, static_cast<unsigned long>(1u)); return *this; }
mp_float_gmp& mp_float_gmp::operator--(void) { ::mpf_sub_ui(rop, rop, static_cast<unsigned long>(1u)); return *this; }

void mp_float_gmp::extract_parts(double& mantissa, boost::int64_t& exponent) const
{
  const bool b_neg = isneg();

  long n2;
  const double d2    = ::mpf_get_d_2exp(&n2, (boost::multiprecision::fabs(*this)).rop);
  const double x_exp = static_cast<double>(static_cast<double>(n2) * ::d_log2());

  const double  x_exp_integer_part = static_cast<double>(static_cast<long>(x_exp));
  const double  x_exp_decimal_part = static_cast<double>(x_exp - x_exp_integer_part);

  double m = d2 * ::pow(10.0, x_exp_decimal_part);
  boost::int64_t  e = static_cast<boost::int64_t>(x_exp_integer_part);

  if(m < 1.0)
  {
    m *= 10.0;
    e -= static_cast<boost::int64_t>(1);
  }

  mantissa = ((!b_neg) ? m : -m);
  exponent = e;
}

double mp_float_gmp::extract_double(void) const
{
  const bool b_neg = isneg();

  // Check for non-normal mp_float_gmp.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                       : -std::numeric_limits<double>::infinity());
    }
  }

  const mp_float_gmp xx(boost::multiprecision::fabs(*this));

  // Check for zero mp_float_gmp.
  if(iszero() || (xx < boost::multiprecision::double_min()))
  {
    return 0.0;
  }

  // Check if mp_float_gmp exceeds the maximum of double.
  if(xx > boost::multiprecision::double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<double>::infinity()
                     : -std::numeric_limits<double>::infinity());
  }

  const double dx = ::mpf_get_d(xx.rop);

  return ((!b_neg) ? dx : -dx);
}

long double mp_float_gmp::extract_long_double(void) const
{
  // Returns the long double conversion of a mp_float_gmp.

  const bool b_neg = isneg();

  // Check for non-normal mp_float_gmp.
  if(!isfinite())
  {
    if(isnan())
    {
      return std::numeric_limits<long double>::quiet_NaN();
    }
    else
    {
      return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                       : -std::numeric_limits<long double>::infinity());
    }
  }

  const mp_float_gmp xx(boost::multiprecision::fabs(*this));

  // Check for zero mp_float_gmp.
  if(iszero() || (xx < boost::multiprecision::long_double_min()))
  {
    return static_cast<long double>(0.0);
  }

  // Check if mp_float_gmp exceeds the maximum of double.
  if(xx > boost::multiprecision::long_double_max())
  {
    return ((!b_neg) ?  std::numeric_limits<long double>::infinity()
                     : -std::numeric_limits<long double>::infinity());
  }

  std::stringstream ss;

  ss << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<long double>::digits10 + (2 + 1)))
     << std::scientific
     << *this;

  long double ld;
  ss >> ld;

  return ld;
}

signed long long mp_float_gmp::extract_signed_long_long(void) const
{
  const bool b_neg = isneg();

  // Make a rounded copy.
  mp_float_gmp xr = *this;

  if(isint())
  {
    ((!b_neg) ? xr += boost::multiprecision::half() : xr -= boost::multiprecision::half());
  }

  const mp_float_gmp nx = boost::multiprecision::fabs(xr.extract_integer_part());

  if(nx > boost::multiprecision::signed_long_long_max())
  {
    return ((!b_neg) ?  (std::numeric_limits<signed long long>::max)()
                     : -(std::numeric_limits<signed long long>::max)());
  }
  
  if(nx < boost::multiprecision::one())
  {
    return static_cast<signed long long>(0);
  }

  if(nx.isone())
  {
    return ((!b_neg) ? static_cast<signed long long>(1) : static_cast<signed long long>(-1));
  }

  // Extract a signed long long-type string from mp_float_gmp.
  static const char c0 = static_cast<char>('\0');
  std::vector<char> str(64u, c0);
  mp_exp_t p10;

  static_cast<void>(::mpf_get_str(&str[0], &p10, 10, str.size() - 1u, nx.rop));

  std::string str_sll(static_cast<std::size_t>(p10), static_cast<char>('0'));
  std::copy(str.begin(), std::find(str.begin(), str.end(), c0), str_sll.begin());

  // Get the signed long long result.
  const signed long long n = boost::multiprecision::utility::numeric_cast<signed long long>(str_sll);

  return ((!b_neg) ? n : -n);
}

unsigned long long mp_float_gmp::extract_unsigned_long_long(void) const
{
  if(isneg())
  {
    return static_cast<unsigned long long>(extract_signed_long_long());
  }

  // Make a rounded copy.
  mp_float_gmp xr = *this;

  if(isint())
  {
    xr += boost::multiprecision::half();
  }

  const mp_float_gmp nx = xr.extract_integer_part();

  if(nx > boost::multiprecision::unsigned_long_long_max())
  {
    return (std::numeric_limits<unsigned long long>::max)();
  }
  
  if(nx < boost::multiprecision::one())
  {
    return static_cast<unsigned long long>(0u);
  }

  if(nx.isone())
  {
    return static_cast<unsigned long long>(1u);
  }

  // Extract an unsigned long long-type string from mp_float_gmp.
  static const char c0 = static_cast<char>('\0');
  std::vector<char> str(64u, c0);
  mp_exp_t p10;

  static_cast<void>(::mpf_get_str(&str[0], &p10, 10, str.size() - 1u, nx.rop));

  std::string str_ull(static_cast<std::size_t>(p10), static_cast<char>('0'));
  std::copy(str.begin(), std::find(str.begin(), str.end(), c0), str_ull.begin());

  // Get the unsigned long long result.
  const unsigned long long n = boost::multiprecision::utility::numeric_cast<unsigned long long>(str_ull);

  return n;
}

mp_float_gmp mp_float_gmp::extract_integer_part(void) const
{
  const bool b_neg = isneg();

  const mp_float_gmp xx = boost::multiprecision::fabs(*this);

  mp_float_gmp nx(xx);
  ::mpf_floor(nx.rop, xx.rop);

  return ((!b_neg) ? nx : -nx);
}

mp_float_gmp mp_float_gmp::extract_decimal_part(void) const
{
  const bool b_neg = isneg();

  const mp_float_gmp xx = boost::multiprecision::fabs(*this);

  const mp_float_gmp dx = xx - xx.extract_integer_part();

  return ((!b_neg) ? dx : -dx);
}

boost::int64_t mp_float_gmp::get_order_exact(void) const
{
  // Get the order-10 of the mp_float_gmp. This is done using a partial
  // string extraction with 10 decimal digits.

  // Create a format string for 10-digits and scientific notation.
  std::string str_fmt = std::string("%.10Fe");

  // Get the ten digits.
  boost::array<char, 64u> buf = {{ static_cast<char>('0') }};

  static_cast<void>(gmp_sprintf(buf.data(), str_fmt.c_str(), rop));

  const std::string str = std::string(buf.data());

  // Extract the base-10 exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  const boost::int64_t my_exp = ((pos_letter_e != std::string::npos) ? boost::multiprecision::utility::numeric_cast<boost::int64_t>(static_cast<const char* const>(str.c_str() + (pos_letter_e + 1u)))
                                                            : static_cast<boost::int64_t>(0));

  return my_exp;
}

boost::int64_t mp_float_gmp::get_order_fast(void) const
{
  const mp_float_gmp xx = boost::multiprecision::fabs(*this);

  if(xx.iszero() || xx.isone())
  {
    return static_cast<boost::int64_t>(0);
  }
  else
  {
    signed long int n2;
    const double d2    = ::mpf_get_d_2exp(&n2, xx.rop);
    const double lg10x = static_cast<double>(::log10(d2) + (static_cast<double>(n2) * ::d_log2()));

    return ((lg10x < 0.0) ? static_cast<boost::int64_t>(lg10x - 0.5)
                          : static_cast<boost::int64_t>(lg10x + 0.5));
  }
}

void mp_float_gmp::get_output_string(std::string& str, boost::int64_t& my_exp, const std::size_t number_of_digits) const
{
  static_cast<void>(my_exp);

  // Create a format string such as "%+.99Fe" in order to extract 100 digits
  // in scientific notation with the lowercase and noshowpos flags.
  const std::size_t the_number_of_digits_scientific = static_cast<std::size_t>((std::max)(number_of_digits, static_cast<std::size_t>(1u)) - static_cast<std::size_t>(1u));

  const std::string str_fmt = std::string("%.") + (boost::lexical_cast<std::string>(the_number_of_digits_scientific) + "Fe");

  // Get the string representation of the mp_float_gmp in scientific notation (lowercase, noshowpos).
  boost::array<char, static_cast<std::size_t>(mp_float_gmp::mp_float_max_digits10 + 32)> buf = {{ static_cast<char>('0') }};

  static_cast<void>(gmp_sprintf(buf.data(), str_fmt.c_str(), rop));

  str = std::string(buf.data());

  // Obtain the raw digits from the scientific notation string.

  // TBD: Well, this is a bit silly. First get the string in
  // scientific notation, then reduce it to raw digits.
  // Perhaps this can be improved.
  // Get the raw digits from a string in scientific notation (lowercase, showpos).

  // Erase the negative sign, if present.
  if(str.at(0u) == static_cast<char>('-'))
  {
    str.erase(str.begin(), str.begin() + 1u);
  }

  // Erase the exponent.
  const std::size_t pos_letter_e = str.rfind(static_cast<char>('e'));

  if(pos_letter_e != std::string::npos)
  {
    str.erase(str.begin() + pos_letter_e, str.end());
  }

  // Erase the decimal point.
  const std::size_t pos_decimal_point = str.rfind(static_cast<char>('.'));

  if(pos_decimal_point != std::string::npos)
  {
    str.erase(str.begin() + pos_decimal_point, str.begin() + (pos_decimal_point + 1u));
  }
}

bool mp_float_gmp::rd_string(const char* const s)
{
  std::string str(s);

  // Remove spaces and tabs
  static const char spc = static_cast<char>(' ');
  static const char tab = static_cast<char>('\t');

  str.erase(std::remove(str.begin(), str.end(), spc), str.end());
  str.erase(std::remove(str.begin(), str.end(), tab), str.end());

  // Get possible + sign and remove it
  
  if(   (!str.empty())
     &&   str.at(static_cast<std::size_t>(0u)) == static_cast<char>('+')
    )
  {
    str.erase(static_cast<std::size_t>(0u),
              static_cast<std::size_t>(1u));
  }

  // Get possible - sign and remove it
  
  bool b_negate = false;

  if(   (!str.empty())
     &&   str.at(static_cast<std::size_t>(0u)) == static_cast<char>('-')
    )
  {
    b_negate = true;
    str.erase(static_cast<std::size_t>(0u),
              static_cast<std::size_t>(1u));
  }

  // Remove leading zeros for all input types
  while(   (!str.empty())
        &&   str.at(static_cast<std::size_t>(0u)) == static_cast<char>('0')
       )
  {
    str.erase(static_cast<std::size_t>(0u), static_cast<std::size_t>(1u));
  }

  // Scale very long pure integer input strings. Convert these into a string with
  // a decimal point and an exponent.

  const std::string::const_iterator it = std::find_if(str.begin(), str.end(), ::has_exp_or_has_dec_predicate);

  const bool is_pure_integer = (it == str.end());

  bool b_scaled = false;

  if(is_pure_integer && (str.length() > static_cast<std::size_t>(boost::multiprecision::tol())))
  {
    b_scaled = true;

    const std::size_t exp = static_cast<std::size_t>(str.length() - static_cast<std::size_t>(1u));

    const std::string str_exp = "E" + boost::lexical_cast<std::string>(exp);

    str = str.substr(static_cast<std::size_t>(0u),
                     static_cast<std::size_t>(static_cast<std::size_t>(boost::multiprecision::tol()) - 1u));

    str.insert(static_cast<std::size_t>(1u), ".");

    str += str_exp;
  }

  // Set the mp_float_gmp value.
  const boost::int32_t n_set_result = static_cast<boost::int32_t>(::mpf_init_set_str(rop, str.c_str(), 10));

  if(b_negate) { negate(); }

  return (n_set_result == static_cast<boost::int32_t>(0));
}
