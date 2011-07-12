
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} © ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <iostream>
#include <string>

#include "imag/test_imag.h"
#include "real/test_real.h"
#include "spot/test_spot.h"
#include "../src/utility/util_timer.h"

namespace
{
  void test_real_imag(void)
  {
    const Util::timer tm;
    const bool test_real_ok = test::real::test_real(true);
    const bool test_imag_ok = test::imag::test_imag(true);
    const double elapsed = tm.elapsed();

    std::string str_real("Real test: ");
    std::string str_imag("Imag test: ");

    str_real += (test_real_ok ? "All tests OK." : "Fail: Not all tests OK.");
    str_imag += (test_imag_ok ? "All tests OK." : "Fail: Not all tests OK.");

    std::cout << str_real << std::endl;
    std::cout << str_imag << std::endl;

    std::cout << "Elapsed time: " << elapsed << " (seconds)" << std::endl;
  }
}

int main(int, char**)
{
//  test::spot::test_spot();

  ::test_real_imag();
}
