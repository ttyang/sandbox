//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/day.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      day d(0);
      BOOST_TEST(false && "0 is not a valid day");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      day d(32);
      BOOST_TEST(false && "32 is not a valid day");
    }
    catch (...)
    {
    }
  }
  {
    day d(0, no_check);
    BOOST_TEST(!d.is_valid() && "0 is not a valid day");
  }
  {
    day d(32, no_check);
    BOOST_TEST(!d.is_valid() && "32 is not a valid day");
  }
  {
    day d(-1, no_check);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid day");
  }
  {
      day d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid day");
  }
  {
      day d(31);
      BOOST_TEST(d.is_valid() );
  }
  {
      day d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid day");
      day::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      day d(3);
      BOOST_TEST(d.is_valid() && "2 is a valid day");
      day::rep i = d.value();
      BOOST_TEST(i==3);
  }
  return boost::report_errors();
}
