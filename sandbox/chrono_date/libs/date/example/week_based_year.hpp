//  week_base_year.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_EXAMPLE_DATE_WEEK_BASED_YEAR_HPP
#define BOOST_CHRONO_EXAMPLE_DATE_WEEK_BASED_YEAR_HPP

#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/date_generators.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/tuple/tuple.hpp>

inline boost::tuple<int, boost::chrono::weekday, boost::chrono::year>
date_to_week(boost::chrono::date d)
{
  std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< std::endl;
  using namespace boost::chrono;
  month_day jan4 = jan / day(4);
  date start = mon <= jan4 / d.get_year();
  std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< start << std::endl;
  if (d < start)
  {
    start = mon <= jan4 / (d.get_year() - 1);
    std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< start << std::endl;
  } else
  {
    date next_start = mon <= jan4 / (start.get_year() + 1);
    std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< next_start << std::endl;
    if (d >= next_start) {
      start = next_start;
      std::cout << __FILE__ <<"["<< __LINE__ <<"]"<< start << std::endl;
    }
  }
  return boost::tuple<int, weekday, year>(
      (d - start).count() / 7 + 1,
      d.get_weekday(),
      (thu > start).get_year()
    );
}

inline boost::chrono::date
week_to_date(int weeknum, boost::chrono::weekday wd, boost::chrono::year y)
{
  using namespace boost::chrono;
  return (mon <= jan / day(4) / y) + days((weeknum - 1) * 7 + (wd == 0 ? 6 : wd - 1));
}

#endif  // header
