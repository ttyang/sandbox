//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/month.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      month d(0);
      BOOST_TEST(false && "0 is not a valid month");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      month d(13);
      BOOST_TEST(false && "13 is not a valid month");
    }
    catch (...)
    {
    }
  }
  {
    month d(0, no_check);
    BOOST_TEST(!d.is_valid() && "0 is not a valid month");
  }
  {
    month d(13, no_check);
    BOOST_TEST(!d.is_valid() && "13 is not a valid month");
  }
  {
    month d(-1, no_check);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid month");
  }
  {
      month d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid month");
  }
  {
      month d(12);
      BOOST_TEST(d.is_valid() );
  }
  {
      month d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid month");
      month::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      month d(3);
      BOOST_TEST(d.is_valid() && "2 is a valid month");
      month::rep i = d.value();
      BOOST_TEST(i==3);
  }
  return boost::report_errors();
}
