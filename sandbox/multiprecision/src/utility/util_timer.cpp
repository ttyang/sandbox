
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <ctime>
#include <boost/multiprecision/utility/util_timer.hpp>

double boost::multiprecision::utility::timer::get_sec(void)
{
  return static_cast<double>(::clock()) / static_cast<double>(CLOCKS_PER_SEC);
}

double boost::multiprecision::utility::timer::elapsed(void) const
{
  const double delta = static_cast<double>(get_sec() - start);

  return static_cast<double>(delta - offset);
}
