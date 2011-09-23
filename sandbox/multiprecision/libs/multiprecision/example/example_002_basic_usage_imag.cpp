
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include <boost/multiprecision/utility/util_timer.hpp>
#include "examples.h"

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

void examples::nr_002::basic_usage_imag(void)
{
  // Print 21 values of the function riemann_zeta[(1/2) + (((1234/10) + k) I)]
  // for 0 <= k < 21 to the standard output using mp_float. Also compute the
  // computation time for the calculation using mp_float in [ms].
  // A comparable Mathematica code is:
  // Timing[Table[N[Zeta[(1/2) + (((1234/10) + k) I)], 100],{k, 0, 20, 1}]].

  static const mp_float y(1234 / boost::multiprecision::ten());

  std::vector<mp_complex> values(static_cast<std::size_t>(21u));

  const boost::multiprecision::utility::timer tm;
  for(boost::int32_t k = static_cast<boost::int32_t>(0); k < static_cast<boost::int32_t>(values.size()); k++)
  {
    const mp_complex z(boost::multiprecision::half(), y + k);

    values[static_cast<std::size_t>(k)] = riemann_zeta(z);
  }
  const double elapsed = tm.elapsed();

  std::cout << "Elapsed time: " << elapsed << "\n";

  const std::streamsize    original_prec = std::cout.precision(std::numeric_limits<mp_float>::digits10);
  const std::ios::fmtflags original_flag = std::cout.setf(std::ios::showpos | std::ios::scientific);

  std::copy(values.begin(), values.end(), std::ostream_iterator<mp_complex>(std::cout, "\n"));

  std::cout.precision(original_prec);
  std::cout.unsetf(std::ios::showpos | std::ios::scientific);
  std::cout.setf(original_flag);
}
