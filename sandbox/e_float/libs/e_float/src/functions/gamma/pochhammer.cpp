
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float_complex.hpp>
#include <e_float/e_float_elementary.hpp>
#include <e_float/e_float_gamma.hpp>

namespace Pochhammer_Series
{
  template<typename T,
           typename TR>
  T Pochhammer_Template(const T& x, const UINT32 n)
  {
    using ef::real;
    using efz::real;
    using ef::gamma;
    using efz::gamma;
    using ef::one;

    if(n == static_cast<UINT32>(0u))
    {
      return one();
    }
    else if(n == static_cast<UINT32>(1u))
    {
      return x;
    }
    else
    {
      if(n < static_cast<UINT32>(50u))
      {
        T val (x);
        T term(x);

        for(UINT32 i = static_cast<UINT32>(1u); i < n; i++)
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

e_float ef::pochhammer(const e_float& x, const UINT32 n)
{
  return Pochhammer_Series::Pochhammer_Template<e_float, e_float>(x, n);
}

ef_complex efz::pochhammer(const ef_complex& x, const UINT32 n)
{
  return Pochhammer_Series::Pochhammer_Template<ef_complex, e_float>(x, n);
}

e_float ef::pochhammer(const e_float& x, const e_float& a)
{
  return ef::gamma(x + a) / ef::gamma(x);
}

ef_complex efz::pochhammer(const ef_complex& z, const ef_complex& a)
{
  return efz::gamma(z + a) / efz::gamma(z);
}

