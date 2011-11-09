//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/day_of_year.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      day_of_year doy(0);
      BOOST_TEST(false && "0 is not a valid day of year");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      day_of_year doy(367);
      BOOST_TEST(false && "367 is not a valid day of year");
    }
    catch (...)
    {
    }
  }
  {
    day_of_year doy(0, no_check);
    BOOST_TEST(!doy.is_valid() && "0 is not a valid day of year");
  }
  {
    day_of_year doy(367, no_check);
    BOOST_TEST(!doy.is_valid() && "367 is not a valid day of year");
  }
  {
    day_of_year doy(-1, no_check);
    BOOST_TEST(!doy.is_valid() && "-1 is not a valid day of year");
  }
  {
      day_of_year doy(1);
      BOOST_TEST(doy.is_valid() && "1 is a valid day of year");
  }
  {
      day_of_year doy(366);
      BOOST_TEST(doy.is_valid() && "366 is a valid day of year");
  }
  {
      day_of_year doy(2);
      BOOST_TEST(doy.is_valid() && "2 is a valid day of year");
      day_of_year::rep i = doy;
      BOOST_TEST(i==2);
  }
  {
      day_of_year doy(3);
      BOOST_TEST(doy.is_valid() && "2 is a valid day of year");
      day_of_year::rep i = doy.value();
      BOOST_TEST(i==3);
  }
  return boost::report_errors();
}
