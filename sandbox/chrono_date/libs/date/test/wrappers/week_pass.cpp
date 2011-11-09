//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/week.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

  {
    try
    {
      week d(0);
      BOOST_TEST(false && "0 is not a valid week");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      week d(54);
      BOOST_TEST(false && "54 is not a valid week");
    }
    catch (...)
    {
    }
  }
  {
    week d(0, no_check);
    BOOST_TEST(!d.is_valid() && "0 is not a valid week");
  }
  {
    week d(54, no_check);
    BOOST_TEST(!d.is_valid() && "54 is not a valid week");
  }
  {
    week d(-1, no_check);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid week");
  }
  {
      week d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid week");
  }
  {
      week d(53);
      BOOST_TEST(d.is_valid() );
  }
  {
      week d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid week");
      week::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      week d(3);
      BOOST_TEST(d.is_valid() && "2 is a valid week");
      week::rep i = d.value();
      BOOST_TEST(i==3);
  }
  return boost::report_errors();
}
