//  week_base_year.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <iostream>
#include <boost/chrono/date/date_io.hpp>
#include "week_based_year.hpp"

int main()
{
  using namespace boost::chrono;

  date d = oct / day(12) / 2011;
  std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< d << '\n';
  int weeknum;
  weekday wd(0);
  year y(0);
  boost::tie(weeknum, wd, y) = date_to_week(d);

  std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< weeknum << " " << wd << " " << y << '\n';

  d = week_to_date(weeknum, wd, y);
  std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< d << '\n';

  return 0;
}
