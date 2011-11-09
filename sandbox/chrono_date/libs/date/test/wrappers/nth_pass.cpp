//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/nth.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
#if 0
  using namespace boost::chrono;

  {
    try
    {
      nth d(0);
      BOOST_TEST(false && "0 is not a valid nth");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      nth d(7);
      BOOST_TEST(false && "7 is not a valid nth");
    }
    catch (...)
    {
    }
  }
  {
    nth d(0, no_check);
    BOOST_TEST(!d.is_valid() && "0 is not a valid nth");
  }
  {
    nth d(7, no_check);
    BOOST_TEST(!d.is_valid() && "7 is not a valid nth");
  }
  {
    nth d(-1, no_check);
    BOOST_TEST(!d.is_valid() && "-1 is not a valid nth");
  }
  {
      nth d(1);
      BOOST_TEST(d.is_valid() && "1 is a valid nth");
  }
  {
      nth d(5);
      BOOST_TEST(d.is_valid() );
  }
  {
      nth d(6);
      BOOST_TEST(d.is_valid() );
  }
  {
      nth d(2);
      BOOST_TEST(d.is_valid() && "2 is a valid nth");
      nth::rep i = d;
      BOOST_TEST(i==2);
  }
  {
      nth d(3);
      BOOST_TEST(d.is_valid() && "3 is a valid nth");
      nth::rep i = d.value();
      BOOST_TEST(i==3);
  }
#endif
//  {
//      BOOST_TEST(_1st.is_valid() );
//      BOOST_TEST(_1st==nth(1));
//  }
//  {
//      BOOST_TEST(_2nd.is_valid() );
//      BOOST_TEST(_2nd==nth(2));
//  }
//  {
//      BOOST_TEST(_3rd.is_valid() );
//      BOOST_TEST(_3rd==nth(3));
//  }
//  {
//      BOOST_TEST(_4th.is_valid() );
//      BOOST_TEST(_4th==nth(4));
//  }
//  {
//      BOOST_TEST(_5th.is_valid() );
//      BOOST_TEST(_5th==nth(5));
//  }
//  {
//      BOOST_TEST(last.is_valid() );
//      BOOST_TEST(last==nth(6));
//  }
  return boost::report_errors();
}
