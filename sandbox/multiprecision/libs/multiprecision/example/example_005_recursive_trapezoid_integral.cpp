
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include "examples.h"
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/utility/util_trapezoid.hpp>

using boost::multiprecision::mp_float;

namespace examples
{
  namespace nr_005
  {
    class RecursiveTrapezoidJ0 : public boost::multiprecision::utility::recursive_trapezoid_rule<mp_float>
    {
    private:

      static const mp_float& my_tol(void)
      {
        static const mp_float val("1E-" + boost::lexical_cast<std::string>((std::numeric_limits<mp_float>::digits10 + 1) / 2));
        return val;
      }

    private:

      const mp_float my_z;

    public:

      RecursiveTrapezoidJ0(const mp_float& z) : boost::multiprecision::utility::recursive_trapezoid_rule<mp_float>(boost::multiprecision::zero(), boost::multiprecision::pi(), my_tol()),
                                                my_z(z) { }

      virtual ~RecursiveTrapezoidJ0() { }

    private:

      virtual mp_float my_function(const mp_float& x) const
      {
        return cos(my_z * sin(x));
      }
    };
  }
}

mp_float examples::nr_005::recursive_trapezoid_j0(const mp_float& x)
{
  const RecursiveTrapezoidJ0 rtj0(x);

  return rtj0.operation() / boost::multiprecision::pi();
}

mp_float examples::nr_005::recursive_trapezoid_j0_test(void)
{
  static const mp_float x = 12 + boost::multiprecision::euler_gamma();

  return recursive_trapezoid_j0(x);
}
