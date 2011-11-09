//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/weekday.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      weekday d(-1);
      BOOST_TEST(false && "-1 is not a valid weekday");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      weekday d(7);
      BOOST_TEST(false && "7 is not a valid weekday");
    }
    catch (...)
    {
    }
  }
  {
    weekday d(-1, no_check);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid weekday");
  }
  {
    weekday d(7, no_check);
    BOOST_TEST(!d.is_valid() && "7 is not a valid weekday");
  }
  {
      weekday d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid weekday");
  }
  {
      weekday d(5);
      BOOST_TEST(d.is_valid() );
  }
  {
      weekday d(6);
      BOOST_TEST(d.is_valid() );
  }
  {
      weekday d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid weekday");
      weekday::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      weekday d(3);
      BOOST_TEST(d.is_valid() && "3 is a valid weekday");
      weekday::rep i = d.value();
      BOOST_TEST(i==3);
  }
  {
      BOOST_TEST(sun.is_valid() );
      BOOST_TEST(sun==weekday(0));
  }
  {
      BOOST_TEST(mon.is_valid() );
      BOOST_TEST(mon==weekday(1));
  }
  {
      BOOST_TEST(tue.is_valid() );
      BOOST_TEST(tue==weekday(2));
  }
  {
      BOOST_TEST(wed.is_valid() );
      BOOST_TEST(wed==weekday(3));
  }
  {
      BOOST_TEST(thu.is_valid() );
      BOOST_TEST(thu==weekday(4));
  }
  {
      BOOST_TEST(fri.is_valid() );
      BOOST_TEST(fri==weekday(5));
  }
  {
      BOOST_TEST(sat.is_valid() );
      BOOST_TEST(sat==weekday(6));
  }
  return boost::report_errors();
}
