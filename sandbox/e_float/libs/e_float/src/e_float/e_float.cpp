
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} © ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include <e_float/e_float.hpp>
#include "../utility/util_lexical_cast.h"

const e_float& ef::value_nan(void) { static const e_float val = e_float().my_value_nan(); return val; }
const e_float& ef::value_inf(void) { static const e_float val = e_float().my_value_inf(); return val; }
const e_float& ef::value_max(void) { static const e_float val = e_float().my_value_max(); return val; }
const e_float& ef::value_min(void) { static const e_float val = e_float().my_value_min(); return val; }

const e_float& ef::value_eps(void)
{
  static const e_float val("1E-" + Util::lexical_cast(std::numeric_limits<e_float>::digits10 - 1));
  return val;
}

const e_float& ef::zero(void) { static const e_float val(0u);    return val; }
const e_float& ef::one (void) { static const e_float val(1u);    return val; }
const e_float& ef::half(void) { static const e_float val("0.5"); return val; }
