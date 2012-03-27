// Boost.Polygon library voronoi_advanced_tutorial.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#include <cmath>

// This will work properly only with GCC compiler.
#include <ieee754.h>
typedef long double fpt80;

#include "boost/polygon/voronoi.hpp"
using namespace boost::polygon;

struct my_ulp_comparison {
  int operator()(fpt80 a, fpt80 b, unsigned int maxUlps) const {
    if (a == b)
      return 0;
    if (a > b)
      return -operator()(b, a, maxUlps);
    ieee854_long_double lhs, rhs;
    lhs.d = a;
    rhs.d = b;
    if (lhs.ieee.negative ^ rhs.ieee.negative)
      return lhs.ieee.negative ? -1 : 1;
    boost::uint64_t le = lhs.ieee.exponent; le = (le << 32) + lhs.ieee.mantissa0;
    boost::uint64_t re = rhs.ieee.exponent; re = (re << 32) + rhs.ieee.mantissa0;
    if (lhs.ieee.negative) {
      if (le - 1 > re)
        return -1;
      le = (le == re) ? 0 : 1; le = (le << 32) + lhs.ieee.mantissa1;
      re = rhs.ieee.mantissa1;
      return (re + maxUlps < le) ? -1 : 0;
    } else {
      if (le + 1 < re)
        return -1;
      le = lhs.ieee.mantissa0;
      re = (le == re) ? 0 : 1; re = (re << 32) + rhs.ieee.mantissa1;
      return (le + maxUlps < re) ? -1 : 0;
    }
  }
};

struct my_fpt_converter {
  template <typename T>
  fpt80 operator()(const T& that) const {
    return static_cast<fpt80>(that);
  }

  template <size_t N>
  fpt80 operator()(const detail::extended_int<N>& that) const {
    fpt80 result = 0.0;
    for (int i = 1; i <= (std::min)(3u, that.size()); ++i) {
      if (i != 1)
        result *= static_cast<fpt80>(0x100000000ULL);
      result += that.chunks[that.size() - i];
    }
    return (that.count < 0) ? -result : result;
  }
};

// Voronoi ctype traits for 43-bit signed integer input coordinates.
struct my_voronoi_ctype_traits {
  typedef boost::int64_t int_type;
  typedef detail::extended_int<3> int_x2_type;
  typedef detail::extended_int<3> uint_x2_type;
  typedef detail::extended_int<128> big_int_type;
  typedef fpt80 fpt_type;
  typedef fpt80 efpt_type;
  typedef my_ulp_comparison ulp_cmp_type;
  typedef my_fpt_converter to_fpt_converter_type;
  typedef my_fpt_converter to_efpt_converter_type;
};

int main () {
  voronoi_diagram<fpt80> vd;
  voronoi_builder<boost::int64_t, my_voronoi_ctype_traits> vb;
  vb.construct(&vd);
  return 0;
}
