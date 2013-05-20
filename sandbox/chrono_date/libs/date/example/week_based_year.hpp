//  week_base_year.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_EXAMPLE_DATE_WEEK_BASED_YEAR_HPP
#define BOOST_CHRONO_EXAMPLE_DATE_WEEK_BASED_YEAR_HPP

#include <boost/chrono/date/date_generators.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/tuple/tuple.hpp>

inline boost::tuple<int, boost::chrono::weekday, boost::chrono::year>
date_to_week(boost::chrono::days_date d)
{
  using namespace boost::chrono;
  const month_day jan4 = jan / day(4);
  days_date start = mon <= jan4 / d.to_year();
  if (d < start)
  {
    start = mon <= (jan4 / (d.to_year() - 1));
  } else
  {
    days_date next_start = mon <= (jan4 / (start.to_year() + 1));
    if (d >= next_start) {
      start = next_start;
    }
  }
  return boost::tuple<int, weekday, year>(
      (d - start).count() / 7 + 1,
      weekday(d),
      (thu > start).to_year()
    );
}

inline boost::chrono::days_date
week_to_date(int weeknum, boost::chrono::weekday wd, boost::chrono::year y)
{
  using namespace boost::chrono;
  return (mon <= (jan/day(4)/y)) + days((weeknum - 1) * 7 + (wd == 0 ? 6 : wd - 1));
}

#endif  // header
