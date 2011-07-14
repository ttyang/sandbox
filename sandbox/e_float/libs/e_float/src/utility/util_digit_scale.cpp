
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <vector>

#include <e_float/e_float.hpp>

#include "util_digit_scale.h"
#include "util_interpolate.h"

const double& Util::DigitScale(void)
{
  static const std::tr1::array<Util::point<double>, static_cast<std::size_t>(4u)> scale_data =
  {{
    Util::point<double>( 50.0, 1.0 / 6.0),
    Util::point<double>(100.0, 1.0 / 3.0),
    Util::point<double>(200.0, 1.0 / 2.0),
    Util::point<double>(300.0, 1.0),
  }};

  static const std::vector<Util::point<double> > scale(scale_data.begin(), scale_data.end());

  static const double the_scale = Util::linear_interpolate<double>::interpolate(static_cast<double>(std::numeric_limits<e_float>::digits10), scale);

  return the_scale;
}