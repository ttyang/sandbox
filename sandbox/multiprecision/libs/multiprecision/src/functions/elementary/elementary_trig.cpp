
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// *****************************************************************************
// Filename    : elementary_trig.cpp
// 
// Project     : Multiple precision mathematics
// 
// Date        : 28.02.2004
// 
// Description : Real variable mathematics for mp_float.
// 
// *****************************************************************************

#include <boost/multiprecision/mp_float_functions.hpp>

using boost::multiprecision::mp_float;

mp_float boost::multiprecision::sin(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(x.has_its_own_sin())
  {
    return mp_float::my_sin(x);
  }

  // Local copy of the argument
  mp_float xx = x;

  // Analyze and prepare the phase of the argument.
  // Make a local, positive copy of the argument, xx.
  // The argument xx will be reduced to 0 <= xx <= pi/2.
  bool b_negate_sin = false;

  if(boost::multiprecision::isneg(x))
  {
    xx = -xx;
    b_negate_sin = !b_negate_sin;
  }

  // Remove even multiples of pi.
  if(xx > boost::multiprecision::pi())
  {
    mp_float n_pi = boost::multiprecision::integer_part(xx / boost::multiprecision::pi());
    xx -= n_pi * boost::multiprecision::pi();

    // Adjust signs if the multiple of pi is not even.
    const bool b_n_pi_is_even = boost::multiprecision::iszero(boost::multiprecision::decimal_part(n_pi / static_cast<boost::int32_t>(2)));

    if(!b_n_pi_is_even)
    {
      b_negate_sin = !b_negate_sin;
    }
  }

  // Reduce the argument to 0 <= xx <= pi/2.
  if(xx > boost::multiprecision::pi_half())
  {
    xx = boost::multiprecision::pi() - xx;
  }
  
  const bool b_zero    = boost::multiprecision::iszero(xx);
  const bool b_pi_half = boost::multiprecision::iszero(xx - boost::multiprecision::pi_half());

  // Check if the reduced argument is very close to 0 or pi/2.
  const bool    b_near_zero    = boost::multiprecision::small_arg(xx);
  const mp_float delta_pi_half  = boost::multiprecision::pi_half() - xx;
  const bool    b_near_pi_half = boost::multiprecision::small_arg(delta_pi_half);
  
  mp_float sin_val;

  if(b_zero)
  {
    sin_val = boost::multiprecision::zero();
  }
  else if(b_pi_half)
  {
    sin_val = boost::multiprecision::one();
  }
  else if(b_near_zero)
  {
    const mp_float x_squared = xx * xx;

    sin_val = xx * boost::multiprecision::hyp0F1(boost::multiprecision::three_half(), -x_squared / static_cast<boost::int32_t>(4));
  }
  else if(b_near_pi_half)
  {
    sin_val = boost::multiprecision::hyp0F1(boost::multiprecision::half(), -(delta_pi_half * delta_pi_half) / static_cast<boost::int32_t>(4));
  }
  else
  {
    // Scale to a small argument for an efficient Taylor series,
    // implemented as a hypergeometric function. Use a standard
    // divide by three identity a certain number of times.
    // Here we use division by 3^9 --> (19683 = 3^9).

    const bool b_scale = (xx.order() > static_cast<boost::int64_t>(-4));

    static const boost::int32_t n_scale           = static_cast<boost::int32_t>(9);
    static const boost::int32_t n_three_pow_scale = static_cast<boost::int32_t>(static_cast<boost::int64_t>(::pow(3.0, static_cast<double>(n_scale)) + 0.5));
    
    if(b_scale)
    {
      xx /= n_three_pow_scale;
    }

    // Now with small arguments, we are ready for a series expansion.
    sin_val = xx * boost::multiprecision::hyp0F1(boost::multiprecision::three_half(), -(xx * xx) / static_cast<boost::int32_t>(4));

    // Convert back using multiple angle identity.
    if(b_scale)
    {
      for(boost::int32_t k = static_cast<boost::int32_t>(0); k < n_scale; k++)
      {
        // Rescale the cosine value using the multiple angle identity.
        sin_val  = - ((sin_val * (sin_val * sin_val)) * static_cast<boost::int32_t>(4))
                   +  (sin_val * static_cast<boost::int32_t>(3));
      }
    }
  }

  return ((!b_negate_sin) ? sin_val : -sin_val);
}

mp_float boost::multiprecision::cos(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(x.has_its_own_cos())
  {
    return mp_float::my_cos(x);
  }

  // Local copy of the argument
  mp_float xx = x;

  // Analyze and prepare the phase of the argument.
  // Make a local, positive copy of the argument, xx.
  // The argument xx will be reduced to 0 <= xx <= pi/2.
  bool b_negate_cos = false;

  if(boost::multiprecision::isneg(x))
  {
    xx = -xx;
  }

  // Remove even multiples of pi.
  if(xx > boost::multiprecision::pi())
  {
    mp_float n_pi = boost::multiprecision::integer_part(xx / boost::multiprecision::pi());
    xx -= n_pi * boost::multiprecision::pi();

    // Adjust signs if the multiple of pi is not even.
    const bool b_n_pi_is_even = boost::multiprecision::iszero(boost::multiprecision::decimal_part(n_pi / static_cast<boost::int32_t>(2)));

    if(!b_n_pi_is_even)
    {
      b_negate_cos = !b_negate_cos;
    }
  }

  // Reduce the argument to 0 <= xx <= pi/2.
  if(xx > boost::multiprecision::pi_half())
  {
    xx = boost::multiprecision::pi() - xx;
    b_negate_cos = !b_negate_cos;
  }
  
  const bool b_zero    = boost::multiprecision::iszero(xx);
  const bool b_pi_half = boost::multiprecision::iszero(xx - boost::multiprecision::pi_half());

  // Check if the reduced argument is very close to 0 or pi/2.
  const bool    b_near_zero    = boost::multiprecision::small_arg(xx);
  const mp_float delta_pi_half = boost::multiprecision::pi_half() - xx;
  const bool    b_near_pi_half = boost::multiprecision::small_arg(delta_pi_half);
  
  mp_float cos_val;

  if(b_zero)
  {
    cos_val = boost::multiprecision::one();
  }
  else if(b_pi_half)
  {
    cos_val = boost::multiprecision::zero();
  }
  else if(b_near_zero)
  {
    const mp_float x_squared = xx * xx;

    cos_val = boost::multiprecision::hyp0F1(boost::multiprecision::half(), -x_squared / static_cast<boost::int32_t>(4));
  }
  else if(b_near_pi_half)
  {
    cos_val = delta_pi_half * boost::multiprecision::hyp0F1(boost::multiprecision::three_half(), -(delta_pi_half * delta_pi_half) / static_cast<boost::int32_t>(4));
  }
  else
  {
    // Scale to a small argument for an efficient Taylor series,
    // implemented as a hypergeometric function. Use a standard
    // divide by three identity a certain number of times.
    // Here we use division by 3^9 --> (19683 = 3^9).

    const bool b_scale = (xx.order() > static_cast<boost::int64_t>(-4));

    static const boost::int32_t n_scale           = static_cast<boost::int32_t>(9);
    static const boost::int32_t n_three_pow_scale = static_cast<boost::int32_t>(static_cast<boost::int64_t>(::pow(3.0, static_cast<double>(n_scale)) + 0.5));
    
    if(b_scale)
    {
      xx /= n_three_pow_scale;
    }

    // Now with small arguments, we are ready for a series expansion.
    cos_val = boost::multiprecision::hyp0F1(boost::multiprecision::half(), -(xx * xx) / static_cast<boost::int32_t>(4));

    // Convert back using multiple angle identity.
    if(b_scale)
    {
      for(boost::int32_t k = static_cast<boost::int32_t>(0); k < n_scale; k++)
      {
        // Rescale the cosine value using the multiple angle identity.
        cos_val  =   ((cos_val * (cos_val * cos_val)) * static_cast<boost::int32_t>(4))
                   -  (cos_val * static_cast<boost::int32_t>(3));
      }
    }
  }

  return ((!b_negate_cos) ? cos_val : -cos_val);
}

void boost::multiprecision::sincos(const mp_float& x, mp_float* const p_sin, mp_float* const p_cos)
{
  if(p_sin != static_cast<mp_float*>(0u)) { *p_sin = boost::multiprecision::sin(x); }
  if(p_cos != static_cast<mp_float*>(0u)) { *p_cos = boost::multiprecision::cos(x); }
}

mp_float boost::multiprecision::tan(const mp_float& x)
{
  if(x.has_its_own_tan())
  {
    return mp_float::my_tan(x);
  }
  else
  {
    return boost::multiprecision::sin(x) / boost::multiprecision::cos(x);
  }
}

mp_float boost::multiprecision::csc(const mp_float& x) { return boost::multiprecision::one()  / boost::multiprecision::sin(x); }
mp_float boost::multiprecision::sec(const mp_float& x) { return boost::multiprecision::one()  / boost::multiprecision::cos(x); }
mp_float boost::multiprecision::cot(const mp_float& x) { return boost::multiprecision::cos(x) / boost::multiprecision::sin(x); }

mp_float boost::multiprecision::asin(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(x.has_its_own_asin())
  {
    return mp_float::my_asin(x);
  }

  const bool b_neg = boost::multiprecision::isneg(x);

  const mp_float xx = !b_neg ? x : -x;

  if(xx > boost::multiprecision::one())
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(boost::multiprecision::iszero(x))
  {
    return boost::multiprecision::zero();
  }

  if(boost::multiprecision::isone(xx))
  {
    return ((!b_neg) ? boost::multiprecision::pi_half() : -boost::multiprecision::pi_half());
  }

  if(boost::multiprecision::small_arg(xx))
  {
    // http://functions.wolfram.com/ElementaryFunctions/ArcSin/26/01/01/
    return x * boost::multiprecision::hyp2F1(boost::multiprecision::half(),
                                             boost::multiprecision::half(),
                                             boost::multiprecision::three_half(),
                                             (x * x));
  }
  else if(boost::multiprecision::near_one(xx))
  {
    const mp_float dx1 = boost::multiprecision::one() - xx;

    const mp_float asin_value =     boost::multiprecision::pi_half()
                               - (  boost::multiprecision::sqrt(dx1 * static_cast<boost::int32_t>(2))
                                  * boost::multiprecision::hyp2F1(boost::multiprecision::half(),
                                    boost::multiprecision::half(),
                                    boost::multiprecision::three_half(),
                                    dx1 / static_cast<boost::int32_t>(2)));

    return ((!b_neg) ? asin_value : -asin_value);
  }

  // Get initial estimate using standard math function asin.
  double dd;
  boost::int64_t  ne;
  boost::multiprecision::to_parts(xx, dd, ne);

  static const boost::int64_t p10_min = static_cast<boost::int64_t>(std::numeric_limits<double>::min_exponent10);
  static const boost::int64_t p10_max = static_cast<boost::int64_t>(std::numeric_limits<double>::max_exponent10);

  const double de = static_cast<double>(ne < static_cast<boost::int64_t>(0) ? static_cast<boost::int32_t>((std::max)(ne, p10_min))
                                                                            : static_cast<boost::int32_t>((std::min)(ne, p10_max)));

  mp_float value = mp_float(::asin(dd * ::pow(10.0, de)));

  // Newton-Raphson iteration

  static const boost::int32_t double_digits10_minus_one = static_cast<boost::int32_t>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) - static_cast<boost::int32_t>(1));

  for(boost::int32_t digits = double_digits10_minus_one; digits <= static_cast<boost::int32_t>(boost::multiprecision::tol()); digits *= static_cast<boost::int32_t>(2))
  {
    mp_float s, c;
    boost::multiprecision::sincos(value, &s, &c);
    value -= (s - xx) / c;
  }

  return ((!b_neg) ? value : -value);
}

mp_float boost::multiprecision::acos(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(x.has_its_own_acos())
  {
    return mp_float::my_acos(x);
  }

  if(boost::multiprecision::fabs(x) > boost::multiprecision::one()) { return std::numeric_limits<mp_float>::quiet_NaN(); }

  return (boost::multiprecision::iszero(x) ?  boost::multiprecision::pi_half()
                                           : (boost::multiprecision::pi_half() - boost::multiprecision::asin(x)));
}

namespace
{
  mp_float my_atan_series_at_zero(const mp_float& x)
  {
    // http://functions.wolfram.com/ElementaryFunctions/ArcTan/26/01/01/
    return x * boost::multiprecision::hyp2F1(boost::multiprecision::one(),
                                             boost::multiprecision::half(),
                                             boost::multiprecision::three_half(),
                                             -(x * x));
  }

  mp_float my_atan_series_at_infinity(const mp_float& x)
  {
    // http://functions.wolfram.com/ElementaryFunctions/ArcTan/26/01/01/
    return boost::multiprecision::pi_half() - boost::multiprecision::hyp2F1( boost::multiprecision::half(),
                                                                             boost::multiprecision::one(),
                                                                             boost::multiprecision::three_half(),
                                                                            -boost::multiprecision::one() / (x * x)) / x;
  }
}

mp_float boost::multiprecision::atan(const mp_float& x)
{
  if(!boost::multiprecision::isfinite(x))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

  if(x.has_its_own_atan())
  {
    return mp_float::my_atan(x);
  }

  const boost::int64_t order = x.order();

  if(x.isinf() || order > boost::multiprecision::tol())
  {
    return (boost::multiprecision::ispos(x) ? boost::multiprecision::pi_half() : -boost::multiprecision::pi_half());
  }
  else if(boost::multiprecision::iszero(x))
  {
    return boost::multiprecision::zero();
  }
  
  if(boost::multiprecision::small_arg(x))
  {
    return ::my_atan_series_at_zero(x);
  }

  if(boost::multiprecision::large_arg(x))
  {
    return ::my_atan_series_at_infinity(x);
  }

  const bool b_neg = boost::multiprecision::isneg(x);

  const mp_float xx = ((!b_neg) ? x : -x);

  // Get initial estimate using standard math function atan or a series
  // expansion for rather large arguments having order 3 or larger.
  double dd;
  boost::int64_t  ne;
  boost::multiprecision::to_parts(xx, dd, ne);

  static const boost::int64_t p10_min = static_cast<boost::int64_t>(std::numeric_limits<double>::min_exponent10);
  static const boost::int64_t p10_max = static_cast<boost::int64_t>(std::numeric_limits<double>::max_exponent10);

  const double de = static_cast<double>(ne < static_cast<boost::int64_t>(0) ? static_cast<boost::int32_t>((std::max)(ne, p10_min))
                                                                            : static_cast<boost::int32_t>((std::min)(ne, p10_max)));

  mp_float value = order < static_cast<boost::int64_t>(2) ? mp_float(::atan(dd * ::pow(10.0, de)))
                                                          : ::my_atan_series_at_infinity(xx);

  // Newton-Raphson iteration
  static const boost::int32_t double_digits10_minus_one = static_cast<boost::int32_t>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) - static_cast<boost::int32_t>(1));

  for(boost::int32_t digits = double_digits10_minus_one; digits <= static_cast<boost::int32_t>(boost::multiprecision::tol()); digits *= static_cast<boost::int32_t>(2))
  {
    mp_float s, c;
    boost::multiprecision::sincos(value, &s, &c);
    value += c * ((xx * c) - s);
  }

  return !b_neg ? value : -value;
}

mp_float boost::multiprecision::atan2(const mp_float& y, const mp_float& x)
{
  // Either x or y is NaN, or both are.
  if(boost::multiprecision::isnan(x) || boost::multiprecision::isnan(y))
  {
    return std::numeric_limits<mp_float>::quiet_NaN();
  }

 const bool x_is_neg = boost::multiprecision::isneg(x);
 const bool y_is_neg = boost::multiprecision::isneg(y);

  // Both x and y are infinite.
  if(boost::multiprecision::isinf(x) && boost::multiprecision::isinf(y))
  {
    if(x_is_neg)
    {
      static const mp_float three_pi_quarter = boost::multiprecision::pi_quarter() * static_cast<boost::int32_t>(3);
      return ((!y_is_neg) ? three_pi_quarter : -three_pi_quarter);
    }
    else
    {
      return ((!y_is_neg) ? boost::multiprecision::pi_quarter() : -boost::multiprecision::pi_quarter());
    }
  }

  if(boost::multiprecision::isinf(y)) // AND !isinf(x) and neither x nor y isnan...
  {
    return ((!y_is_neg) ? boost::multiprecision::pi_half() : -boost::multiprecision::pi_half());
  }

  if(boost::multiprecision::isinf(x)) // AND !isinf(y) and neither x nor y isnan...
  {
    return ((!x_is_neg) ? boost::multiprecision::zero() : boost::multiprecision::pi());
  }

  if(boost::multiprecision::iszero(x)) // AND !isnan(y)...
  {
    return (boost::multiprecision::iszero(y) ? boost::multiprecision::zero()
                                             : ((!y_is_neg) ? boost::multiprecision::pi_half() : -boost::multiprecision::pi_half()));
  }

  if(boost::multiprecision::iszero(y)) // AND !iszero(x)...
  {
    return ((!x_is_neg) ? boost::multiprecision::zero() : boost::multiprecision::pi());
  }

  // And finally after all these checks... Compute atan(y / x).
  // Disregard the signs of x and y at the moment.
  const mp_float atan_term(boost::multiprecision::atan(y / x));

  // Determine the quadrant and the corresponding sign of the
  // result based on the signs of x and y.
  if(y_is_neg == x_is_neg)
  {
    // Both y and y are negative or both are positive.
    return (x_is_neg ? (atan_term - boost::multiprecision::pi()) : atan_term);
  }
  else
  {
    // There signs of x and y differ.
    return (x_is_neg ? (atan_term + boost::multiprecision::pi()) : atan_term);
  }
}
