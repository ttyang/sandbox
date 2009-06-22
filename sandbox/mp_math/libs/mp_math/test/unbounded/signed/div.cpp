// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "prerequisite.hpp"

BOOST_AUTO_TEST_CASE_TEMPLATE(division_by_zero, int_type, IntTypes)
{
  const int_type x("0x201abcff00aaffffff");
  const int_type y("0");
  BOOST_CHECK_THROW(x / y, std::domain_error);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide1, int_type, IntTypes)
{
  const int_type x("987777");
  const int_type y("123456");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "8");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide2, int_type, IntTypes)
{
  const int_type x("263825472");
  const int_type y("123456");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "2137");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide3, int_type, IntTypes)
{
  const int_type x("-0xaf000001100008");
  const int_type y("0x100000");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "-0xaf0000011");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide4, int_type, IntTypes)
{
  const int_type x("0x8005000000ffffff");
  const int_type y("-0x155ff");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "-0x5fd41dd02f04");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide5, int_type, IntTypes)
{
  const int_type x("-0x8005000000ffffff");
  const int_type y("-0x155ff");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "0x5fd41dd02f04");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide6, int_type, IntTypes)
{
  const int_type x("0x89ab89745cc653de58eecc8f8a874120065ea545f6f5f");
  const int_type y("0x1889ba8a789456adfc8005b1");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "0x59c48aa7a1446110b31f70");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide7, int_type, IntTypes)
{
  const int_type x("0x1889ba8a789456adfc8005b1");
  const int_type y("0x1889ba8a789456adfc8005b2");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "0");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide8, int_type, IntTypes)
{
  const int_type x("0x201abcff00aaffffff");
  const int_type y("0x1fffffffffffffff");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "256");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide9, int_type, IntTypes)
{
  const int_type x(
      "0xffffffffffffffff00000000000000000000000ffffffffffff00000000000000000000"
      "000000000000000eeeeeeeeeeeeee0");
  const int_type y("0xffffffff00000000000");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z,
      "0x100000001000000000000000000000000000000100000000ffff0000ffff0000ffff00"
      "00ffff0000fff");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide10, int_type, IntTypes)
{
  const int_type x("0x7fffffff800000010000000000000000");
  const int_type y("0x800000008000000200000005");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "0xfffffffd");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(divide11, int_type, IntTypes)
{
  const int_type x("0x1581b6d300d0225a000000");
  const int_type y("0x449f21");
  const int_type z = x / y;
  BOOST_CHECK_EQUAL(z, "0x503ba38a5226b3aa");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(shift_right1, int_type, IntTypes)
{
  int_type x("263825472");
  x >>= 3;
  BOOST_CHECK_EQUAL(x, "32978184");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod_zero, int_type, IntTypes)
{
  const int_type x("987777");
  const int_type y("0");
  BOOST_CHECK_THROW(x % y, std::domain_error);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod1, int_type, IntTypes)
{
  const int_type x("987777");
  const int_type y("123456");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "129");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod2, int_type, IntTypes)
{
  const int_type x("0");
  const int_type y("0x55464565");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "0");
}
BOOST_AUTO_TEST_CASE_TEMPLATE(mod3, int_type, IntTypes)
{
  const int_type x("-987777");
  const int_type y("123456");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "-129");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod4, int_type, IntTypes)
{
  const int_type x("987777");
  const int_type y("-123456");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "129");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod5, int_type, IntTypes)
{
  const int_type x("-987777");
  const int_type y("-123456");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "-129");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(mod6, int_type, IntTypes)
{
  const int_type x("-123456");
  const int_type y("123456");
  const int_type z = x % y;
  BOOST_CHECK_EQUAL(z, "0");
}

