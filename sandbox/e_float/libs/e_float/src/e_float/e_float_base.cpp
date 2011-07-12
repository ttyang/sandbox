
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.hpp>
#include "../utility/util_lexical_cast.h"

std::ostream& operator<<(std::ostream& os, const e_float_base& f)
{
  std::string str;
  f.wr_string(str, os);
  return (os << str);
}

std::istream& operator>>(std::istream& is, e_float_base& f)
{
  std::string str;
  static_cast<void>(is >> str);
  const bool b_read = f.rd_string(str.c_str());
  static_cast<void>(b_read);
  return is;
}

const std::string::size_type& e_float_base::width_of_exponent_field(void)
{
  static const std::string::size_type width_of_e_n64 =
      Util::lexical_cast((std::numeric_limits<INT64>::max)()).length();

  static const std::string::size_type width_of_e_long =
      Util::lexical_cast((std::numeric_limits<long>::max)()).length();

  static const std::string::size_type width_of_e =
      (std::max)(width_of_e_n64, width_of_e_long);

  return width_of_e;
}

e_float e_float_base::my_cbrt         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_rootn        (const e_float&, const UINT32) { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_exp          (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_log          (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_sin          (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cos          (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_tan          (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_asin         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_acos         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_atan         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_sinh         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cosh         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_tanh         (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_asinh        (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_acosh        (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_atanh        (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_gamma        (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_riemann_zeta (const e_float&)               { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cyl_bessel_jn(const INT32, const e_float&)  { return std::numeric_limits<e_float>::quiet_NaN(); }
e_float e_float_base::my_cyl_bessel_yn(const INT32, const e_float&)  { return std::numeric_limits<e_float>::quiet_NaN(); }
