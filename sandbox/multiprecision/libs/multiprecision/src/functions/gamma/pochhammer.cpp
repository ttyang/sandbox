
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float_functions.hpp>

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

namespace boost
{
  namespace multiprecision
  {
    namespace pochhammer_series
    {
      template<typename T,
               typename TR>
      T my_pochhammer(const T& x, const boost::uint32_t n)
      {
        using boost::multiprecision::real;
        using boost::multiprecision::real;
        using boost::multiprecision::gamma;
        using boost::multiprecision::gamma;
        using boost::multiprecision::one;

        if(n == static_cast<boost::uint32_t>(0u))
        {
          return one();
        }
        else if(n == static_cast<boost::uint32_t>(1u))
        {
          return x;
        }
        else
        {
          if(n < static_cast<boost::uint32_t>(50u))
          {
            T val (x);
            T term(x);

            for(boost::uint32_t i = static_cast<boost::uint32_t>(1u); i < n; i++)
            {
              val *= ++term;
            }

            return val;
          }
          else
          {
            const TR nr(n);

            return gamma(x + nr) / gamma(x);
          }
        }
      }
    }
  }
}

mp_float boost::multiprecision::pochhammer(const mp_float& x, const boost::uint32_t n)
{
  return boost::multiprecision::pochhammer_series::my_pochhammer<mp_float, mp_float>(x, n);
}

mp_complex boost::multiprecision::pochhammer(const mp_complex& x, const boost::uint32_t n)
{
  return boost::multiprecision::pochhammer_series::my_pochhammer<mp_complex, mp_float>(x, n);
}

mp_float boost::multiprecision::pochhammer(const mp_float& x, const mp_float& a)
{
  return boost::multiprecision::gamma(x + a) / boost::multiprecision::gamma(x);
}

mp_complex boost::multiprecision::pochhammer(const mp_complex& z, const mp_complex& a)
{
  return boost::multiprecision::gamma(z + a) / boost::multiprecision::gamma(z);
}

