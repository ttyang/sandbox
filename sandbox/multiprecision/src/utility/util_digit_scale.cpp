
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <vector>

#include <boost/array.hpp>
#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/utility/util_digit_scale.hpp>
#include <boost/multiprecision/utility/util_interpolate.hpp>

using boost::multiprecision::mp_float;

const double& boost::multiprecision::utility::digit_scale(void)
{
  static const boost::array<boost::multiprecision::utility::point<double>, static_cast<std::size_t>(4u)> scale_data =
  {{
    boost::multiprecision::utility::point<double>( 50.0, 1.0 / 6.0),
    boost::multiprecision::utility::point<double>(100.0, 1.0 / 3.0),
    boost::multiprecision::utility::point<double>(200.0, 1.0 / 2.0),
    boost::multiprecision::utility::point<double>(300.0, 1.0),
  }};

  static const std::vector<boost::multiprecision::utility::point<double> > scale(scale_data.begin(), scale_data.end());

  static const double the_scale = boost::multiprecision::utility::linear_interpolate<double>::interpolate(static_cast<double>(std::numeric_limits<mp_float>::digits10), scale);

  return the_scale;
}
