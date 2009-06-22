// Copyright Tom St Denis 2002 - 2007.
// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_MATH_INTEGER_DETAIL_ROOT_HPP
#define BOOST_MP_MATH_INTEGER_DETAIL_ROOT_HPP

#include <boost/mp_math/integer/detail/multiplier.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace boost {
namespace mp_math {
namespace detail {

// Newton-Raphson approximation
template<class ApInt, typename IntegerT>
void
newton_raphson_loop(ApInt& a, ApInt& b, const IntegerT& n, const ApInt& x)
{
  //std::cout << "initial = " << b.template to_string<std::string>(std::ios::hex) << std::endl;
  // a is going to hold the result
  // b holds the initial approximation
  // c is just another temporary
  ApInt c;

  // improve the initial approximation b
  do
  {
    a = b;

    // b = a - (a^n - x) / (n * a^(n-1))

    c = pow(a, n-1);

    //std::cout << "c = " << c.template to_string<std::string>(std::ios::hex) << std::endl;
    //std::cout << "a = " << a.template to_string<std::string>(std::ios::hex) << std::endl;
    //std::cout << "x = " << x.template to_string<std::string>(std::ios::hex) << std::endl;
    // numerator
    b = c * a;  // b = a^n
    //std::cout << "b = " << b.template to_string<std::string>(std::ios::hex) << std::endl;
    b -= x;     // b = a^n - x
    //std::cout << "b = " << b.template to_string<std::string>(std::ios::hex) << std::endl;

    // denominator
    c *= n;     // c = a^(n-1) * n
    c = b / c;  // c = (a^n - x) / (n * a^(n-1))

    //std::cout << "c = " << c.template to_string<std::string>(std::ios::hex) << std::endl;
    //std::cout << " ok " << std::endl;
    b = a - c;
    //std::cout << " ok2 " << std::endl;
  } while (a != b);

  // result can be off by a few so check
  for (;;)
  {
    b = pow(a, n);

    if (b > x)
      --a;
    else
      break;
  }
}


template<
  class ApInt,
  bool IsApIntSigned = ApInt::is_signed
>
struct root;


template<class ApInt>
struct root<ApInt,false>
{
  typedef typename ApInt::size_type size_type;

  static void sqrt    (ApInt& z, const ApInt& x);
  template<typename IntegerT>
  static void nth_root(ApInt& z, const IntegerT& n, const ApInt& x);
};


template<class ApInt>
void
root<ApInt,false>::sqrt(ApInt& z, const ApInt& x)
{
  if (!x)
  {
    z = typename ApInt::digit_type(0);
    return;
  }

  z = x;

  // first approx. (not very bad for large arg)
  shifter<ApInt>::shift_digits_right(z, z.size() / 2);

  ApInt a = x / z;

  z += a;
  base::divider<ApInt>::divide_by_2(z);

  // and now z > sqrt(x)
  do
  {
    a = x / z;
    z += a;
    base::divider<ApInt>::divide_by_2(z);
    // z >= sqrt(x) >= a at this point
  } while (z > a);
}

template<class ApInt>
template<typename IntegerT>
void
root<ApInt,false>::nth_root(ApInt& z, const IntegerT& n, const ApInt& x)
{
  if (n == 0U)
    throw std::domain_error("nth_root: n must not be zero");
  else if (n == 1U)
  {
    z = x;
    return;
  }

  static const size_type digit_bits = ApInt::traits_type::digit_bits;

  // create initial approximation
  z = x.precision() - 1;
  z /= n;
  const size_type result_precision = z.template to_integral<size_type>() + 1;

  const size_type result_digits = (result_precision + (digit_bits - 1))
                                / digit_bits;
  ApInt initial_approximation;
  initial_approximation.reserve (result_digits);
  initial_approximation.set_size(result_digits);

  initial_approximation[result_digits - 1] = 0;
  initial_approximation.set_bits(0, result_precision + 1);

  newton_raphson_loop(z, initial_approximation, n, x);
}


template<class ApInt>
struct root<ApInt,true>
{
  typedef typename ApInt::size_type size_type;

  static void sqrt    (ApInt& z, const ApInt& x);
  static void nth_root(ApInt& z, size_type n, const ApInt& x);
  static void nth_root(ApInt& z, const ApInt& n, const ApInt& x);
};


template<class ApInt>
void
root<ApInt,true>::sqrt(ApInt& z, const ApInt& x)
{
  if (x.is_negative())
    throw std::domain_error("sqrt: radicand must be positive");

  root<ApInt,false>::sqrt(z, x);
}

template<class ApInt>
void
root<ApInt,true>::nth_root(ApInt& z, size_type n, const ApInt& x)
{
  if ((n & 1) == 0 && x.is_negative())
    throw std::domain_error("nth_root: radicand must be positive if n is even");

  // x must be positive for the algorithm to work
  const bool s = x.sign_bit();
  const_cast<ApInt&>(x).set_sign_bit(0);

  try
  {
    root<ApInt,false>::nth_root(z, n, x);
  }
  catch (const std::exception&)
  {
    const_cast<ApInt&>(x).set_sign_bit(s);
    throw;
  }

  const_cast<ApInt&>(x).set_sign_bit(s);
  z.set_sign_bit(s);
}

template<class ApInt>
void
root<ApInt,true>::nth_root(ApInt& z, const ApInt& n, const ApInt& x)
{
  if (n.is_even() && x.is_negative())
    throw std::domain_error("nth_root: radicand must be positive if n is even");

  // x must be positive for the algorithm to work
  const bool s = x.sign_bit();
  const_cast<ApInt&>(x).set_sign_bit(0);

  try
  {
    root<ApInt,false>::nth_root(z, n, x);
  }
  catch (const std::exception&)
  {
    const_cast<ApInt&>(x).set_sign_bit(s);
    throw;
  }

  const_cast<ApInt&>(x).set_sign_bit(s);
  z.set_sign_bit(s);
}


} // namespace detail
} // namespace mp_math
} // namespace boost

#endif

