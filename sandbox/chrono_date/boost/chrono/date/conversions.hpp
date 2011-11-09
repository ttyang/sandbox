//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_CONVERSIONS_HPP
#define BOOST_CHRONO_DATE_CONVERSIONS_HPP

#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/date/config.hpp>

//! @file Conversion between the different date formats

namespace boost
{
  namespace chrono
  {

    /**
     * days to ymd conversion.
     * @param d the days to convert.
     * @pre d is a valid number of days.
     * @return the ymd calculated from the parameter d.
     */
    year_month_day to_ymd(days d) BOOST_NOEXCEPT;
    year_month_day_leap to_ymd_leap(days) BOOST_NOEXCEPT;
    year_month_day to_ymd(year_day_of_year) BOOST_NOEXCEPT;
    year_month_day to_ymd(year_week_weekday) BOOST_NOEXCEPT;

    year_day_of_year to_ydoy(days) BOOST_NOEXCEPT;
    year_day_of_year to_ydoy(year_month_day) BOOST_NOEXCEPT;
    year_day_of_year to_ydoy(year_week_weekday) BOOST_NOEXCEPT;

    days to_days(year_month_day) BOOST_NOEXCEPT;
    days to_days(year_day_of_year) BOOST_NOEXCEPT;
    days to_days(year_week_weekday) BOOST_NOEXCEPT;

    year_week_weekday to_ywwd(year_month_day) BOOST_NOEXCEPT;
    year_week_weekday to_ywwd(year_day_of_year) BOOST_NOEXCEPT;
    year_week_weekday to_ywwd(days) BOOST_NOEXCEPT;

  } // chrono

} // boost


#endif  // header
