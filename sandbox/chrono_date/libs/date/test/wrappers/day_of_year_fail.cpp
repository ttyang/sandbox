//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/day_of_year.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  using namespace boost::chrono;

#if ! defined BOOST_CHRONO_DATE_NO_CXX11_CONSTEXPR
  {
    try
    {
      day_of_year doy(0, check);
      BOOST_TEST(false && "0 is not a valid day of year");
    }
    catch (...)
    {
    }
  }
  {
    try
    {
      day_of_year doy(367, check);
      BOOST_TEST(false && "367 is not a valid day of year");
    }
    catch (...)
    {
    }
  }
  return boost::report_errors();
#else
  // "Test non applicable when BOOST_NO_CXX11_CONSTEXPR is defined"
  return 1;
#endif //BOOST_NO_CXX11_CONSTEXPR

}
