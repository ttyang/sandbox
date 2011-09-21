
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iomanip>
#include <iostream>

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

#include "test_spot.h"

/*
extern "C" int MAIN__(void);
namespace
{
  void linpack_benchmark(void) { MAIN__(); }
}
*/

void test::spot::test_spot(void)
{
//  ::linpack_benchmark();

  using boost::multiprecision::mp_float;
  using boost::multiprecision::mp_complex;

  const std::streamsize original_prec = std::cout.precision(std::numeric_limits<mp_float>::digits10);

  const mp_float x = boost::multiprecision::sqrt(boost::multiprecision::euler_gamma());
  std::cout << x << std::endl;

  const mp_float p = boost::multiprecision::log(boost::multiprecision::pi() * 100);
  std::cout << p << std::endl;

  std::cout.precision(original_prec);
}
