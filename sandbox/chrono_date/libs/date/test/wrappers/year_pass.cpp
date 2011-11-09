//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/year.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      year d(-32769);
      BOOST_TEST(false && "-32769 is not a valid year");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      year d(32768);
      BOOST_TEST(false && "32768 is not a valid year");
    }
    catch (...)
    {
    }
  }
  {
    year d(-32769, no_check);
    BOOST_TEST(!d.is_valid() && "-32769 is not a valid year");
  }
  {
    year d(32768, no_check);
    BOOST_TEST(!d.is_valid() && "32768 is not a valid year");
  }
  {
      year d(0);
      BOOST_TEST(d.is_valid() && "0 is a valid year");
  }
  {
      year d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid year");
  }
  {
      year d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid year");
      year::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      year d(3);
      BOOST_TEST(d.is_valid() && "2 is a valid year");
      year::rep i = d.value();
      BOOST_TEST(i==3);
  }
  return boost::report_errors();
}
