
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <algorithm>
#include <numeric>
#include <functional>

#include <boost/multiprecision/mp_float_functions.hpp>

using boost::multiprecision::mp_float;

mp_float boost::multiprecision::hyp0F0(const mp_float& x)
{
  // Compute the series representation of Hypergeometric0F0 taken from
  // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  
  mp_float H0F0 = boost::multiprecision::one() + x_pow_n_div_n_fact;

  boost::int32_t n;

  // Series expansion of hyperg_0f0(; ; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(x_pow_n_div_n_fact.order() - H0F0.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H0F0 += x_pow_n_div_n_fact;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H0F0 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hyp0F1(const mp_float& b, const mp_float& x)
{
  // Compute the series representation of Hypergeometric0F1 taken from
  // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F1/06/01/01/
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  mp_float pochham_b         (b);
  mp_float bp                (b);

  mp_float H0F1 = boost::multiprecision::one() + (x_pow_n_div_n_fact / pochham_b);

  boost::int32_t n;

  // Series expansion of hyperg_0f1(; b; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    pochham_b *= ++bp;

    const mp_float term = x_pow_n_div_n_fact / pochham_b;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - H0F1.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H0F1 += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H0F1 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hyp1F0(const mp_float& a, const mp_float& x)
{
  // Compute the series representation of Hypergeometric1F0 taken from
  // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F0/06/01/01/
  // and also see the corresponding section for the power function (i.e. x^a).
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  mp_float pochham_a         (a);
  mp_float ap                (a);

  mp_float H1F0 = boost::multiprecision::one() + (pochham_a * x_pow_n_div_n_fact);

  boost::int32_t n;

  // Series expansion of hyperg_1f0(a; ; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    pochham_a *= ++ap;

    const mp_float term = pochham_a * x_pow_n_div_n_fact;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - H1F0.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H1F0 += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H1F0 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hyp1F1(const mp_float& a, const mp_float& b, const mp_float& x)
{
  // Compute the series representation of hyperg_1f1 taken from
  // Abramowitz and Stegun 13.1.2, page 504.
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  mp_float pochham_a         (a);
  mp_float pochham_b         (b);
  mp_float ap                (a);
  mp_float bp                (b);
  
  mp_float H1F1 = boost::multiprecision::one() + ((pochham_a / pochham_b) * x_pow_n_div_n_fact);

  boost::int32_t n;

  // Series expansion of hyperg_1f1(a, b ; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    pochham_a *= ++ap;
    pochham_b *= ++bp;

    const mp_float term = (pochham_a / pochham_b) * x_pow_n_div_n_fact;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - H1F1.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H1F1 += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H1F1 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hyp2F0(const mp_float& a, const mp_float& b, const mp_float& x)
{
  // Compute the series representation of hyperg_2f0.
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  mp_float pochham_a         (a);
  mp_float pochham_b         (b);
  mp_float ap                (a);
  mp_float bp                (b);

  mp_float H2F0 = boost::multiprecision::one() + ((pochham_a * pochham_b) * x_pow_n_div_n_fact);

  boost::int32_t n;

  // Series expansion of hyperg_2f0(a, b; ; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    pochham_a *= ++ap;
    pochham_b *= ++bp;

    const mp_float term = (pochham_a * pochham_b) * x_pow_n_div_n_fact;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - H2F0.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H2F0 += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H2F0 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hyp2F1(const mp_float& a, const mp_float& b, const mp_float& c, const mp_float& x)
{
  // Compute the series representation of hyperg_2f1 taken from
  // Abramowitz and Stegun 15.1.1.
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);
  mp_float pochham_a         (a);
  mp_float pochham_b         (b);
  mp_float pochham_c         (c);
  mp_float ap                (a);
  mp_float bp                (b);
  mp_float cp                (c);

  mp_float H2F1 = boost::multiprecision::one() + (((pochham_a * pochham_b) / pochham_c) * x_pow_n_div_n_fact);

  boost::int32_t n;

  // Series expansion of hyperg_2f1(a, b; c; x).
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    pochham_a *= ++ap;
    pochham_b *= ++bp;
    pochham_c *= ++cp;

    const mp_float term = ((pochham_a * pochham_b) / pochham_c) * x_pow_n_div_n_fact;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - H2F1.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    H2F1 += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? H2F1 : std::numeric_limits<mp_float>::quiet_NaN());
}

mp_float boost::multiprecision::hypPFQ(const std::deque<mp_float>& a, const  std::deque<mp_float>& b, const mp_float& x)
{
  // Compute the series representation of hyperg_pfq.
  // There are no checks on input range or parameter boundaries.

  mp_float x_pow_n_div_n_fact(x);

  // The pochhammer symbols for the multiplications in the series expansion
  // will be stored in STL-containers.
  std::vector<mp_float> ap(a.begin(), a.end());
  std::vector<mp_float> bp(b.begin(), b.end());

  // Initialize the pochhammer product terms with the products of the form:
  // [(a0)_1 * (a1)_1 * (a2)_1 * ...], or [(b0)_1 * (b1)_1 * (b2)_1 * ...].
  mp_float pochham_a = std::accumulate(ap.begin(), ap.end(), boost::multiprecision::one(), std::multiplies<mp_float>());
  mp_float pochham_b = std::accumulate(bp.begin(), bp.end(), boost::multiprecision::one(), std::multiplies<mp_float>());

  mp_float HPFQ = boost::multiprecision::one() + ((pochham_a / pochham_b) * x_pow_n_div_n_fact);

  boost::int32_t n;

  // Series expansion of hyperg_pfq[{a0, a1, a2, ...}; {b0, b1, b2, ...}; x].
  for(n = static_cast<boost::int32_t>(2); n < boost::multiprecision::max_iteration(); n++)
  {
    x_pow_n_div_n_fact *= x;
    x_pow_n_div_n_fact /= n;

    // Increment each of the pochhammer elements in a and b.
    std::transform(ap.begin(), ap.end(), ap.begin(), std::bind1st(std::plus<mp_float>(), boost::multiprecision::one()));
    std::transform(bp.begin(), bp.end(), bp.begin(), std::bind1st(std::plus<mp_float>(), boost::multiprecision::one()));

    // Multiply the pochhammer product terms with the products of the incremented
    // pochhammer elements. These are products of the form:
    // [(a0)_k * (a1)_k * (a2)_k * ...], or [(b0)_k * (b1)_k * (b2)_k * ...].
    pochham_a *= std::accumulate(ap.begin(), ap.end(), boost::multiprecision::one(), std::multiplies<mp_float>());
    pochham_b *= std::accumulate(bp.begin(), bp.end(), boost::multiprecision::one(), std::multiplies<mp_float>());

    const mp_float term = (pochham_a / pochham_b) * x_pow_n_div_n_fact;

    if(n > static_cast<boost::int32_t>(20))
    {
      const boost::int64_t order_check = static_cast<boost::int64_t>(term.order() - HPFQ.order());

      if(order_check < -boost::multiprecision::tol())
      {
        break;
      }
    }

    HPFQ += term;
  }

  return ((n < boost::multiprecision::max_iteration()) ? HPFQ : std::numeric_limits<mp_float>::quiet_NaN());
}
