
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <boost/array.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include "../test_case_real.h"

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

namespace test
{
  namespace real
  {
    class TestCase_case_00011_various_elem_math : public TestCaseReal
    {
    public:
      TestCase_case_00011_various_elem_math() { }
      virtual ~TestCase_case_00011_various_elem_math() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00011_various_elem_math");
        return str;
      }
      virtual void e_float_test(std::vector<mp_float>& data) const
      {
        data.clear();
        data.push_back(boost::multiprecision::floor(boost::multiprecision::pi()));
        data.push_back(boost::multiprecision::ceil (boost::multiprecision::pi()));
        data.push_back(boost::multiprecision::floor(-100 - boost::multiprecision::euler_gamma()));
        data.push_back(boost::multiprecision::ceil (-100 - boost::multiprecision::euler_gamma()));
        data.push_back(mp_float(boost::multiprecision::to_int32(mp_float("1e9"))));
        data.push_back(mp_float(boost::multiprecision::to_int64(mp_float("1e18"))));
        data.push_back(mp_float(boost::multiprecision::to_int32(mp_float("1e29"))));
        data.push_back(mp_float(boost::multiprecision::to_int64(mp_float("1e29"))));
        data.push_back(mp_float(boost::multiprecision::to_int32(mp_complex(boost::multiprecision::pi(), boost::multiprecision::euler_gamma()))));
        data.push_back(mp_float(boost::multiprecision::to_int64(mp_complex(boost::multiprecision::pi(), boost::multiprecision::euler_gamma()))));
      }
      virtual const std::vector<mp_float>& control_data(void) const
      {
        static const boost::array<mp_float, 10u> a =
        {{
           mp_float("3"),
           mp_float("4"),
           mp_float("-101"),
           mp_float("-100"),
           mp_float("1000000000"),
           mp_float("1000000000000000000"),
           mp_float("2147483647"),
           mp_float("9223372036854775807"),
           mp_float("3"),
           mp_float("3"),
        }};
        static const std::vector<mp_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00011_various_elem_math(const bool b_write_output)
    {
      return TestCase_case_00011_various_elem_math().execute(b_write_output);
    }
  }
}
