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
  enum Result {
    LESS = -1,
    EQUAL = 0,
    MORE = 1
  };  

  Result operator()(fpt80 a, fpt80 b, unsigned int maxUlps) const {
    if (a == b)
      return EQUAL;
    if (a > b) {
      Result res = operator()(b, a, maxUlps);
      if (res == EQUAL) return res;
      return (res == LESS) ? MORE : LESS;
    }
    ieee854_long_double lhs, rhs;
    lhs.d = a;
    rhs.d = b;
    if (lhs.ieee.negative ^ rhs.ieee.negative)
      return lhs.ieee.negative ? LESS : MORE;
    boost::uint64_t le = lhs.ieee.exponent; le = (le << 32) + lhs.ieee.mantissa0;
    boost::uint64_t re = rhs.ieee.exponent; re = (re << 32) + rhs.ieee.mantissa0;
    if (lhs.ieee.negative) {
      if (le - 1 > re)
        return LESS;
      le = (le == re) ? 0 : 1; le = (le << 32) + lhs.ieee.mantissa1;
      re = rhs.ieee.mantissa1;
      return (re + maxUlps < le) ? LESS : EQUAL;
    } else {
      if (le + 1 < re)
        return LESS;
      le = lhs.ieee.mantissa0;
      re = (le == re) ? 0 : 1; re = (re << 32) + rhs.ieee.mantissa1;
      return (le + maxUlps < re) ? LESS : EQUAL;
    }
  }
};

struct my_fpt_converter {
  template <typename T>
  fpt80 operator()(const T& that) const {
    return static_cast<fpt80>(that);
  }

  template <size_t N>
  fpt80 operator()(const typename detail::extended_int<N> &that) const {
    fpt80 result = 0.0;
    for (size_t i = 1; i <= (std::min)((size_t)3, that.size()); ++i) {
      if (i != 1)
        result *= static_cast<fpt80>(0x100000000ULL);
      result += that.chunks()[that.size() - i];
    }
    return (that.count() < 0) ? -result : result;
  }
};

// Voronoi diagram traits.
struct my_voronoi_diagram_traits {
  typedef fpt80 coordinate_type;
  typedef struct {
    template <typename CT>
    fpt80 operator()(const CT& that) const {
      return static_cast<fpt80>(that);
    }
  } ctype_converter_type;
  typedef detail::point_2d<coordinate_type> point_type;
  typedef voronoi_cell<coordinate_type> cell_type;
  typedef voronoi_vertex<coordinate_type> vertex_type;
  typedef voronoi_edge<coordinate_type> edge_type;
  typedef struct {
  public:
    enum { ULPS = 128 };
    bool operator()(const point_type &v1, const point_type &v2) const {
      return (ulp_cmp(v1.x(), v2.x(), ULPS) == my_ulp_comparison::EQUAL &&
              ulp_cmp(v1.y(), v2.y(), ULPS) == my_ulp_comparison::EQUAL);
    }
  private:
    my_ulp_comparison ulp_cmp;
  } vertex_equality_predicate_type;
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

#include <iostream>
int main () {
  voronoi_diagram<fpt80, my_voronoi_diagram_traits> vd;
  voronoi_builder<boost::int64_t, my_voronoi_ctype_traits> vb;
  vb.construct(&vd);
  return 0;
}
