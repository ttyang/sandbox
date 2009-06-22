// Copyright Kevin Sopp 2008 - 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "prerequisite.hpp"


BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer1, int_type, IntTypes)
{
  const int_type min(0), max(128);
  boost::mp_math::uniform_integer<int_type> g(min, max);
  boost::mt19937 e;
  for (int i = 0; i < 128; ++i)
  {
    const int_type x = g(e);
    BOOST_REQUIRE_GE(x, min);
    BOOST_REQUIRE_LE(x, max);
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer2, int_type, IntTypes)
{
  const int_type min(11), max("26546549");
  boost::mp_math::uniform_integer<int_type> g(min, max);
  boost::mt19937 e;
  for (int i = 0; i < 1000; ++i)
  {
    const int_type x = g(e);
    BOOST_REQUIRE_GE(x, min);
    BOOST_REQUIRE_LE(x, max);
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits1, int_type, IntTypes)
{
  BOOST_CHECK_EQUAL(
      boost::mp_math::uniform_integer_bits<int_type>::has_fixed_range, false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits2, int_type, IntTypes)
{
  boost::mp_math::uniform_integer_bits<int_type> g(512);
  boost::mt19937 e;
  const int_type x = g(e);
  BOOST_CHECK_EQUAL(x.precision(), 512U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits3, int_type, IntTypes)
{
  boost::mp_math::uniform_integer_bits<int_type> g(71);
  boost::mt19937 e;
  const int_type x = g(e);
  BOOST_CHECK_EQUAL(x.precision(), 71U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits4, int_type, IntTypes)
{
  boost::mp_math::uniform_integer_bits<int_type> g(1001);
  boost::mt19937 e;
  const int_type x = g(e);
  BOOST_CHECK_EQUAL(x.precision(), 1001U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits5, int_type, IntTypes)
{
  boost::mp_math::uniform_integer_bits<int_type> g(8);
  BOOST_CHECK_EQUAL(g.min(), 128U);
  BOOST_CHECK_EQUAL(g.max(), 255U);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(uniform_integer_bits6, int_type, IntTypes)
{
  boost::mp_math::uniform_integer_bits<int_type> g(11);
  BOOST_CHECK_EQUAL(g.min(), 1024U);
  BOOST_CHECK_EQUAL(g.max(), 2047U);
}


