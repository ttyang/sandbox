// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "prerequisite.hpp"

// We mostly test from/to string conversions here since most other test cases
// depend on these. If they are broken and senseless data gets into an integer
// or we have wrong output then we need to fix this quickly.

BOOST_AUTO_TEST_CASE_TEMPLATE(default_ctor, int_type, IntTypes)
{
  const int_type x;
  BOOST_CHECK_EQUAL(x.size(), 0U);
  BOOST_CHECK_EQUAL(x.is_initialized(), false);
  BOOST_CHECK_EQUAL(x.is_uninitialized(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_empty_string1, int_type, IntTypes)
{
  const int_type x("");
  BOOST_CHECK_EQUAL(x.size(), 0U);
  BOOST_CHECK_EQUAL(x.is_initialized(), false);
  BOOST_CHECK_EQUAL(x.is_uninitialized(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string1, int_type, IntTypes)
{
  const int_type x("0");
  BOOST_CHECK(x.is_positive());
  BOOST_CHECK_EQUAL(x.is_initialized(), true);
  BOOST_CHECK_EQUAL(x.is_uninitialized(), false);
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string2, int_type, IntTypes)
{
  const int_type x("12");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "12");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string3, int_type, IntTypes)
{
  const int_type x("123456789");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "123456789");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string4, int_type, IntTypes)
{
  const int_type x("1000000000");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "1000000000");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string5, int_type, IntTypes)
{
  const int_type x("+1");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "1");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string6, int_type, IntTypes)
{
  const int_type x("-1");
  BOOST_CHECK(x.is_negative());
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "-1");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string7, int_type, IntTypes)
{
  const int_type x("8888000000009", std::ios_base::dec |
                                     std::ios_base::showbase);
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "8888000000009");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string8, int_type, IntTypes)
{
  BOOST_CHECK_THROW(int_type("1234567890a456456"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_decimal_string9, int_type, IntTypes)
{
  BOOST_CHECK_THROW(
      int_type("1230", std::ios_base::showpos),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string1, int_type, IntTypes)
{
  const int_type x("0", std::ios_base::oct);
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string2, int_type, IntTypes)
{
  const int_type x("0", std::ios_base::oct | std::ios_base::showbase);
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string3, int_type, IntTypes)
{
  const int_type x("012");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "10");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string4, int_type, IntTypes)
{
  const int_type x("000000000000000000000000000000000");
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string5, int_type, IntTypes)
{
  const int_type x("0123456777");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "21913087");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string6, int_type, IntTypes)
{
  BOOST_CHECK_THROW(int_type("012345678"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_octal_string7, int_type, IntTypes)
{
  BOOST_CHECK_THROW(
      int_type("1234567", std::ios_base::oct | std::ios_base::showbase),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string1, int_type, IntTypes)
{
  const int_type x("0x0");
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string2, int_type, IntTypes)
{
  const int_type x("0X0");
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string3, int_type, IntTypes)
{
  const int_type x("0", std::ios_base::hex);
  BOOST_REQUIRE_EQUAL(x.size(), 1U);
  BOOST_CHECK_EQUAL(x[0], 0U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string4, int_type, IntTypes)
{
  const int_type x("0xF");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "15");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string5, int_type, IntTypes)
{
  const int_type x("0xa0");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "160");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string6, int_type, IntTypes)
{
  const int_type x("0xA0000000");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "2684354560");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string7, int_type, IntTypes)
{
  const int_type x("0x");
  BOOST_CHECK_EQUAL(x.is_uninitialized(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string8, int_type, IntTypes)
{
  const int_type x("-0x");
  BOOST_CHECK_EQUAL(x.is_uninitialized(), true);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string9, int_type, IntTypes)
{
  BOOST_CHECK_THROW(int_type("0x15656abg56"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string10, int_type, IntTypes)
{
  BOOST_CHECK_THROW(
      int_type("156afc56", std::ios_base::hex | std::ios_base::showbase),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_hexadecimal_string11, int_type, IntTypes)
{
  BOOST_CHECK_THROW(
      int_type("015656ABDEE0", std::ios_base::hex | std::ios_base::showbase |
                               std::ios_base::uppercase),
      std::invalid_argument);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_long_string, int_type, IntTypes)
{
  const int_type x(
      "875004025190050300612679044488093050295124399425061612342608525876458563"
      "36946409871074842737283625535525153833045575858681216");
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(),
      "875004025190050300612679044488093050295124399425061612342608525876458563"
      "36946409871074842737283625535525153833045575858681216");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_iterators1, int_type, IntTypes)
{
  const std::string s("123456789");
  const int_type x(s.begin(), s.end());
  BOOST_CHECK_EQUAL(x.template to_string<std::string>(), "123456789");
}

#ifndef BOOST_NO_CWCHAR
BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_wchar_t1, int_type, IntTypes)
{
  const int_type x(L"0xA0000000");
  BOOST_CHECK_EQUAL(x, "2684354560");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_wstring1, int_type, IntTypes)
{
  const std::wstring s(L"0xA0000000");
  const int_type x(s);
  BOOST_CHECK_EQUAL(x, "2684354560");
}
#endif

BOOST_AUTO_TEST_CASE_TEMPLATE(cctor1, int_type, IntTypes)
{
  const int_type x("0xabddd00012134f");
  const int_type y(x);
  BOOST_CHECK_EQUAL(x, y);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(cctor2, int_type, IntTypes)
{
  const int_type x("-0xabddd00012134f");
  const int_type y(x);
  BOOST_CHECK_EQUAL(x, y);
}

/*
BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_unsigned_integral_type1, int_type, IntTypes)
{
  const int_type x(9999999U);
  BOOST_CHECK_EQUAL(x, "9999999");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_unsigned_integral_type2, int_type, IntTypes)
{
  const int_type x(123456U);
  BOOST_CHECK_EQUAL(x, "123456");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ctor_from_integral_type_unsigned_char, int_type, IntTypes)
{
  unsigned char c = 42;
  const int_type x(c);
  BOOST_CHECK_EQUAL(x, "42");
}
*/
