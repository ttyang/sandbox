//! \file
// multiprecision_test.cpp

// Copyright Paul A. Bristow 2011.
// Copyright Christopher Kormanyos 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Test of using multiprecision and Boost.Check macro/functions.
// Numerical tests are originals from Christopher Kormanyos,
// here test cases called from Boost.Test.

#define BOOST_TEST_MAIN
#define BOOST_LIB_DIAGNOSTIC "on"// Show library file details.
// Linking to lib file: libboost_unit_test_framework-vc100-mt-gd-1_48.lib  (trunk at Jul 11)

//  #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10 50 as command line using MSVC or in jamfile (but needs b2 -a option?)

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::dec;
using std::hex;
using std::boolalpha;
using std::scientific;
using std::fixed;
using std::defaultfloat;
using std::showpos;
using std::showpoint;

#include <iomanip>
using std::setprecision;
using std::setw;
#include <string>
using std::string;
#include <sstream>
//using std::istringstream;
//using std::ostringstream

#include <boost/test/unit_test.hpp> // Enhanced for unit_test framework autolink.
#include <boost/test/floating_point_comparison.hpp>

#include <boost/multiprecision/mp_float.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>

namespace test
{
  // These are Christopher Kormanyos's original tests, to be run below under Boost.Test.
  namespace real
  {
    // See \boost-sandbox\multiprecision\libs\multiprecision\test\real\test_real.cpp  and /cases/ *.cpp
    // \boost-sandbox\multiprecision\libs\multiprecision\test\real\cases\test_case_0000x_overflow_underflow.cpp
    bool test_case_00001_overflow_mul_x(const bool);
    bool test_case_00002_underflow_mul_x (const bool);
    bool test_case_00003_overflow_x_mul_by_n(const bool);
    bool test_case_00004_underflow_x_div_by_n(const bool);
    // \boost-sandbox\multiprecision\libs\multiprecision\test\real\cases\test_case_0000y_write_to_ostream.cpp
    bool test_case_00006_write_os_floatfield_fixed(const bool);
    bool test_case_00007_write_os_floatfield_scientific(const bool);
    bool test_case_00008_write_os_floatfield_not_set(const bool);
    // \boost-sandbox\multiprecision\libs\multiprecision\test\real\cases\test_case_0000z_global_ops_pod.cpp
    bool test_case_00009_global_ops_pod_equate         (const bool);
    bool test_case_00010_global_ops_pod_operations     (const bool);
    // \boost-sandbox\multiprecision\libs\multiprecision\test\real\cases\test_case_00011_various_elem_math.cpp
    bool test_case_00011_various_elem_math             (const bool);
    bool test_case_00021_bernoulli                     (const bool);
    bool test_case_00051_factorial                     (const bool);
    bool test_case_00052_factorial2                    (const bool);
    bool test_case_00071_various_int_func              (const bool);
    bool test_case_00101_sin                           (const bool);
    bool test_case_00102_cos                           (const bool);
    bool test_case_00103_exp                           (const bool);
    bool test_case_00104_log                           (const bool);
    bool test_case_00105_sqrt                          (const bool);
    bool test_case_00106_rootn                         (const bool);
    bool test_case_00111_sin_small_x                   (const bool);
    bool test_case_00112_cos_x_near_pi_half            (const bool);
    bool test_case_00113_atan_x_small_to_large         (const bool);
    bool test_case_00114_various_trig                  (const bool);
    bool test_case_00115_various_elem_trans            (const bool);
    bool test_case_00121_sinh                          (const bool);
    bool test_case_00122_cosh                          (const bool);
    bool test_case_00123_tanh                          (const bool);
    bool test_case_00124_asinh                         (const bool);
    bool test_case_00125_acosh                         (const bool);
    bool test_case_00126_atanh                         (const bool);
    bool test_case_00201_gamma                         (const bool);
    bool test_case_00202_gamma_medium_x                (const bool);
    bool test_case_00203_gamma_small_x                 (const bool);
    bool test_case_00204_gamma_tiny_x                  (const bool);
    bool test_case_00205_gamma_near_neg_n              (const bool);
    bool test_case_00221_various_gamma_func            (const bool);
    bool test_case_00901_zeta_small_x                  (const bool);
    bool test_case_00902_zeta_all_x                    (const bool);
    bool test_case_00903_zeta_neg_x                    (const bool);
  } // namespace real
} // namespace test


//Macros to Check using manips output expected string result, for example:
// CHECK_OUT(hex << showbase << setw(10) << i, "       0xf")
// CHECK_OUT(scientific << setw(20) << d, "       1.234568e+001");

// Compare a output with expected result.
#define CHECK_OUT(manips, result)\
{ \
  std::ostringstream oss;\
  oss << manips;\
  BOOST_CHECK_EQUAL(oss.str(), result);\
}

#define  CHECK_LENGTH(manips, result)\
{\
  BOOST_CHECK_EQUAL(oss.str().length(), strlen(result));\
}\

// Compare results of reading string in,
#define  CHECK_IN(in, value)\
{\
  boost::multiprecision::mp_float r;\
  std::istringstream iss(in);\
  iss >> r;\
  BOOST_CHECK_CLOSE_FRACTION(r, value, std::numeric_limits<boost::multiprecision::mp_float>::epsilon());\
} // #define  CHECK_IN(in, value, sd, df, types)

// CHECK_OUT_IN Output via manips, and read back in, check is same. 'Loopback'.
#define  CHECK_OUT_IN(manips, result, value)\
{\
  std::stringstream ss;\
  ss << manips;\
  BOOST_CHECK_EQUAL(ss.str(), result);\
  boost::multiprecision::mp_float r;\
  ss >> r;\
  BOOST_CHECK_CLOSE_FRACTION(r, value, std::numeric_limits<boost::multiprecision::mp_float>::epsilon());\
}// #define  CHECK_OUT_IN(manips, result)
// Must #define BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_TYPE_EFX; in project properties.

// Note: exact double means exactly representable as double, for example: 0.5,
// but NOT 0.1.
// Integral may be an integer or a double having an integral value.

BOOST_AUTO_TEST_CASE(multiprecision_test_template)
{ // These are just examples of using Boost.Test.
  // Need to be removed when no longer helpful.
  BOOST_TEST_MESSAGE("Test Boost.multiprecision"); // Only appears if command line has --log_level="message"

  string m = "Test with ";
  m+= __FILE__;
  m+= " edited ";
  m += __TIMESTAMP__ ".\n";
  BOOST_TEST_MESSAGE(m);
  BOOST_CHECK(true);
  BOOST_CHECK_EQUAL(1, 1);
  BOOST_CHECK_NE(1, -1);
  BOOST_CHECK_CLOSE_FRACTION(1.0, 1.0+std::numeric_limits<double>::epsilon(), std::numeric_limits<double>::epsilon());
  double d = 123.456789;
  // cout << scientific << d << endl; //  Outputs: "1.234568e+003"
  CHECK_OUT(d, "123.457"); // Default. == << std::defaultfloat
  CHECK_OUT(defaultfloat << d, "123.457"); // Default. == << std::defaultfloat
  string ddef = "123.457"; // default float output.
  CHECK_OUT(d, ddef); // Default. == << std::defaultfloat
  CHECK_OUT(defaultfloat << d, ddef); // Default. == << std::defaultfloat
  CHECK_OUT(scientific << d, "1.234568e+002");
  CHECK_OUT(fixed << d, "123.456789");
  int m1 = -1; // negative variable.
  CHECK_OUT(m1, "-1"); //  negative constant.
  CHECK_OUT(hex << m1, "ffffffff"); // with hex manipulator.
  // Checking input with inline.
  boost::multiprecision::mp_float r;
  std::istringstream iss("123.456");
  iss >> r;
  BOOST_CHECK_CLOSE_FRACTION(r, boost::multiprecision::mp_float("123.456"), std::numeric_limits<boost::multiprecision::mp_float>::epsilon());
  BOOST_CHECK_EQUAL(r, boost::multiprecision::mp_float("123.456")); // Also works.
  // Repeat same test using CHECK_IN macro defined above.
  CHECK_IN("123.456", boost::multiprecision::mp_float("123.456"));

  //CHECK_IN("123.456", boost::multiprecision::mp_float(123.456)); // Mistaken conversion from less accurate double.
  // Fails r{123.456} and boost::multiprecision::mp_float(123.456){123.4560000000000030695446184836328029632568359375}
  // differ by more than 1e-49.

  // CHECK_OUT_IN Output via manips, and read back in, check is same. 'Loopback'.
  // #define  CHECK_OUT_IN(manips, result, value)
  { // Integer example.
    int i = 255;
    std::string result = "ff";
    int value = 255;
    std::stringstream ss;
    ss << hex << i;
    BOOST_CHECK_EQUAL(ss.str(), result);
    int read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
  }
  { // double example
    double w = 123.456;
    std::string result = "123.456000";
    double value = 123.456;
    std::stringstream ss;
    ss << std::fixed << w;
    //cout << ss.str() << endl;
    BOOST_CHECK_EQUAL(ss.str(), result);
    double read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
    BOOST_CHECK_CLOSE_FRACTION(read, value, std::numeric_limits<double>::epsilon());
  }
  { // mp_float example
    boost::multiprecision::mp_float w("123.456");
    std::string result = "123.456000";  // double result was "123.456000";
    boost::multiprecision::mp_float value("123.456");
    std::stringstream ss;
    ss << std::fixed << w;
    //cout << ss.str() << endl;
    BOOST_CHECK_EQUAL(ss.str(), result);
    boost::multiprecision::mp_float read;
    ss >> read;
    BOOST_CHECK_EQUAL(read, value);
    BOOST_CHECK_CLOSE_FRACTION(read, value, std::numeric_limits<boost::multiprecision::mp_float>::epsilon());

    CHECK_OUT_IN(std::fixed << w, result, value);
  }

} // BOOST_AUTO_TEST_CASE(mp_float_template)



BOOST_AUTO_TEST_CASE(multiprecision_test_macros)
{ // Check some macro values.
  BOOST_CHECK_EQUAL(BOOST_MULTIPRECISION_BACKEND_MP_FLOAT_DIGITS10, 50); // Assumes we are testing at 50 digits, NOT the default.
} // BOOST_AUTO_TEST_CASE(multiprecision_test_macros)


BOOST_AUTO_TEST_CASE(multiprecision_test_ios)
{ // Check some IOS defaults.
  BOOST_CHECK_EQUAL(cout.precision(), 6);   // Default precision for stream = 6.
  std::ostringstream oss;
  BOOST_CHECK_EQUAL(oss.precision(), 6); // Default precision for string stream = 6.
  }

BOOST_AUTO_TEST_CASE(multiprecision_test_input)
{ //
  BOOST_TEST_MESSAGE("Test Boost.multiprecision input.");
   using boost::multiprecision::mp_float;
   CHECK_IN("2", mp_float("2"));
   CHECK_IN("-2", mp_float("-2"));
   CHECK_IN("+2", mp_float("+2"));
   CHECK_IN("-2.", mp_float("-2."));

   CHECK_IN("123.456", mp_float("123.456"));
   CHECK_IN("0.0123456", mp_float("0.0123456"));
   CHECK_IN("1e-6", mp_float("1e-6"));
   CHECK_IN("-1e-6", mp_float("-1e-6"));
} // BOOST_AUTO_TEST_CASE(multiprecision_test_input)

BOOST_AUTO_TEST_CASE(multiprecision_tests)
{ // Christopher Kormanyos's original real tests from \multiprecision\libs\multiprecision\test\real\cases
  BOOST_TEST_MESSAGE("Test Boost.multiprecision numerical.");

  BOOST_CHECK(test::real::test_case_00001_overflow_mul_x                 (false));
  BOOST_CHECK(test::real::test_case_00002_underflow_mul_x                (false));
  BOOST_CHECK(test::real::test_case_00003_overflow_x_mul_by_n            (false));
  BOOST_CHECK(test::real::test_case_00004_underflow_x_div_by_n           (false));
  BOOST_CHECK(test::real::test_case_00006_write_os_floatfield_fixed      (false));
  BOOST_CHECK(test::real::test_case_00007_write_os_floatfield_scientific (false));
  BOOST_CHECK(test::real::test_case_00008_write_os_floatfield_not_set    (false));
  BOOST_CHECK( test::real::test_case_00001_overflow_mul_x                (false));
  BOOST_CHECK( test::real::test_case_00002_underflow_mul_x               (false));
  BOOST_CHECK( test::real::test_case_00003_overflow_x_mul_by_n           (false));
  BOOST_CHECK( test::real::test_case_00004_underflow_x_div_by_n          (false));
  BOOST_CHECK( test::real::test_case_00006_write_os_floatfield_fixed     (false));
  BOOST_CHECK( test::real::test_case_00007_write_os_floatfield_scientific(false));
  BOOST_CHECK( test::real::test_case_00008_write_os_floatfield_not_set   (false));
  BOOST_CHECK( test::real::test_case_00009_global_ops_pod_equate         (false));
  BOOST_CHECK( test::real::test_case_00010_global_ops_pod_operations     (false));
  BOOST_CHECK( test::real::test_case_00011_various_elem_math             (false));
  BOOST_CHECK( test::real::test_case_00021_bernoulli                     (false));
  BOOST_CHECK( test::real::test_case_00051_factorial                     (false));
  BOOST_CHECK( test::real::test_case_00052_factorial2                    (false));
  BOOST_CHECK( test::real::test_case_00071_various_int_func              (false));
  BOOST_CHECK( test::real::test_case_00101_sin                           (false));
  BOOST_CHECK( test::real::test_case_00102_cos                           (false));
  BOOST_CHECK( test::real::test_case_00103_exp                           (false));
  BOOST_CHECK( test::real::test_case_00104_log                           (false));
  BOOST_CHECK( test::real::test_case_00105_sqrt                          (false));
  BOOST_CHECK( test::real::test_case_00106_rootn                         (false));
  BOOST_CHECK( test::real::test_case_00111_sin_small_x                   (false));
  BOOST_CHECK( test::real::test_case_00112_cos_x_near_pi_half            (false));
  BOOST_CHECK( test::real::test_case_00113_atan_x_small_to_large         (false));
  BOOST_CHECK( test::real::test_case_00114_various_trig                  (false));
  BOOST_CHECK( test::real::test_case_00115_various_elem_trans            (false));
  BOOST_CHECK( test::real::test_case_00121_sinh                          (false));
  BOOST_CHECK( test::real::test_case_00122_cosh                          (false));
  BOOST_CHECK( test::real::test_case_00123_tanh                          (false));
  BOOST_CHECK( test::real::test_case_00124_asinh                         (false));
  BOOST_CHECK( test::real::test_case_00125_acosh                         (false));
  BOOST_CHECK( test::real::test_case_00126_atanh                         (false));
  BOOST_CHECK( test::real::test_case_00201_gamma                         (false));
  BOOST_CHECK( test::real::test_case_00202_gamma_medium_x                (false));
  BOOST_CHECK( test::real::test_case_00203_gamma_small_x                 (false));
  BOOST_CHECK( test::real::test_case_00204_gamma_tiny_x                  (false));
  BOOST_CHECK( test::real::test_case_00205_gamma_near_neg_n              (false));
  BOOST_CHECK( test::real::test_case_00221_various_gamma_func            (false));
  BOOST_CHECK( test::real::test_case_00901_zeta_small_x                  (false));
  BOOST_CHECK( test::real::test_case_00902_zeta_all_x                    (false));
  BOOST_CHECK( test::real::test_case_00903_zeta_neg_x                    (false));

} //  BOOST_AUTO_TEST_CASE(multiprecision_tests)

/*

Output

 numerical_test.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\numerical_test.exe
  Running 5 test cases...
  Test Boost.multiprecision
  Test with ..\numerical_test.cpp edited Fri Oct 14 13:24:40 2011.

  Test Boost.multiprecision input.
  Test Boost.multiprecision numerical.
  TestCase_case_00001_overflow_mul_x : Numerical compare OK: PASS
  TestCase_case_00002_underflow_mul_x : Numerical compare OK: PASS
  TestCase_case_00003_overflow_x_mul_by_n : Numerical compare OK: PASS
  TestCase_case_00004_underflow_x_div_by_n : Numerical compare OK: PASS
  TestCase_case_00006_write_os_floatfield_fixed : Numerical compare OK: PASS
  TestCase_case_00007_write_os_floatfield_scientific : Numerical compare OK: PASS
  TestCase_case_00008_write_os_floatfield_not_set : Numerical compare OK: PASS
  TestCase_case_00001_overflow_mul_x : Numerical compare OK: PASS
  TestCase_case_00002_underflow_mul_x : Numerical compare OK: PASS
  TestCase_case_00003_overflow_x_mul_by_n : Numerical compare OK: PASS
  TestCase_case_00004_underflow_x_div_by_n : Numerical compare OK: PASS
  TestCase_case_00006_write_os_floatfield_fixed : Numerical compare OK: PASS
  TestCase_case_00007_write_os_floatfield_scientific : Numerical compare OK: PASS
  TestCase_case_00008_write_os_floatfield_not_set : Numerical compare OK: PASS
  TestCase_case_00009_global_ops_pod_equate : Numerical compare OK: PASS
  TestCase_case_00010_global_ops_pod_operations : Numerical compare OK: PASS
  TestCase_case_00011_various_elem_math : Numerical compare OK: PASS
  TestCase_case_00021_bernoulli : Numerical compare OK: PASS
  TestCase_case_00051_factorial : Numerical compare OK: PASS
  TestCase_case_00052_factorial2 : Numerical compare OK: PASS
  TestCase_case_00071_various_int_func : Numerical compare OK: PASS
  TestCase_case_00101_sin : Numerical compare OK: PASS
  TestCase_case_00102_cos : Numerical compare OK: PASS
  TestCase_case_00103_exp : Numerical compare OK: PASS
  TestCase_case_00104_log : Numerical compare OK: PASS
  TestCase_case_00105_sqrt : Numerical compare OK: PASS
  TestCase_case_00106_rootn : Numerical compare OK: PASS
  TestCase_case_00111_sin_small_x : Numerical compare OK: PASS
  TestCase_case_00112_cos_x_near_pi_half : Numerical compare OK: PASS
  TestCase_case_00113_atan_x_small_to_large : Numerical compare OK: PASS
  TestCase_case_00114_various_trig : Numerical compare OK: PASS
  TestCase_case_00115_various_elem_trans : Numerical compare OK: PASS
  TestCase_case_00121_sinh : Numerical compare OK: PASS
  TestCase_case_00122_cosh : Numerical compare OK: PASS
  TestCase_case_00123_tanh : Numerical compare OK: PASS
  TestCase_case_00124_asinh : Numerical compare OK: PASS
  TestCase_case_00125_acosh : Numerical compare OK: PASS
  TestCase_case_00126_atanh : Numerical compare OK: PASS
  TestCase_case_00201_gamma : Numerical compare OK: PASS
  TestCase_case_00202_gamma_medium_x : Numerical compare OK: PASS
  TestCase_case_00203_gamma_small_x : Numerical compare OK: PASS
  TestCase_case_00204_gamma_tiny_x : Numerical compare OK: PASS
  TestCase_case_00205_gamma_near_neg_n : Numerical compare OK: PASS
  TestCase_case_00221_various_gamma_func : Numerical compare OK: PASS
  TestCase_case_00901_zeta_small_x : Numerical compare OK: PASS
  TestCase_case_00902_zeta_all_x : Numerical compare OK: PASS
  TestCase_case_00903_zeta_neg_x : Numerical compare OK: PASS

  *** No errors detected

  */
