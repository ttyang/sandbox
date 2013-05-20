//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/nth_week.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

#if defined BOOST_NO_CXX11_CONSTEXPR
  {
    try
    {
      nth_week d(0, check);
      BOOST_TEST(false && "0 is not a valid nth_week");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      nth_week d(6, check);
      BOOST_TEST(false && "7 is not a valid nth_week");
    }
    catch (...)
    {
    }
  }
#endif
  {
    nth_week d(0);
    BOOST_TEST(!d.is_valid() && "0 is not a valid nth_week");
  }
  {
    nth_week d(7);
    BOOST_TEST(!d.is_valid() && "7 is not a valid nth_week");
  }
  {
    nth_week d(-1);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid nth_week");
  }
  {
      nth_week d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid nth_week");
  }
  {
      nth_week d(5);
      BOOST_TEST(d.is_valid() );
  }
  {
      nth_week d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid nth_week");
      nth_week::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      nth_week d(3);
      BOOST_TEST(d.is_valid() && "3 is a valid nth_week");
      nth_week::rep i = d.value();
      BOOST_TEST(i==3);
  }
//  {
//      BOOST_TEST(_1st_week.is_valid() );
//      BOOST_TEST(_1st_week==nth_week(1));
//  }
//  {
//      BOOST_TEST(_2nd_week.is_valid() );
//      BOOST_TEST(_2nd_week==nth_week(2));
//  }
//  {
//      BOOST_TEST(_3rd_week.is_valid() );
//      BOOST_TEST(_3rd_week==nth_week(3));
//  }
//  {
//      BOOST_TEST(_4th_week.is_valid() );
//      BOOST_TEST(_4th_week==nth_week(4));
//  }
//  {
//      BOOST_TEST(_5th_week.is_valid() );
//      BOOST_TEST(_5th_week==nth_week(5));
//  }

  return boost::report_errors();
}
