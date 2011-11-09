//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

/**
 * @file Includes the date generators form several date formats.
 */

#error
#ifndef BOOST_CHRONO_DATE_DATE_FACTORIES_HPP
#define BOOST_CHRONO_DATE_DATE_FACTORIES_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/tuples.hpp>

namespace boost
{
  namespace chrono
  {





//    inline date operator/(year_week yw, weekday wd)
//    {
//      return date(ym.get_year(), ym.get_week(), wd);
//    }
//    inline date operator/(week_weekday md, year y)
//    {
//      return date(y, md.get_week(), md.get_weekday());
//    }
//    inline date operator/(year_week yw, weekday::rep wd)
//    {
//      return ym / weekday(wd);
//    }
//    inline date operator/(week_weekday wwd, year::rep y)
//    {
//      return wwd / year(y);
//    }




  } // chrono

} // boost

#endif  // header
