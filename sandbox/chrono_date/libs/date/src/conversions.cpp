//  date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {


//    year_month_day to_ymd2(days dt)  BOOST_NOEXCEPT
//    {
//      days::rep x=dt.count();
//      year::rep y = static_cast<year::rep>(static_cast<int64_t> (x + 2) * 400 / 146097);
//      const year::rep ym1 = y - 1;
//      day_of_year::rep doy = x - days_before_year(y);
//      const day_of_year::rep doy1 = x - days_before_year(ym1);
//      const int N = std::numeric_limits<int>::digits - 1;
//      const int mask1 = doy >> N; // arithmetic rshift - not portable - but nearly universal
//      const int mask0 = ~mask1;
//      doy = (doy & mask0) | (doy1 & mask1);
//      y = (y & mask0) | (ym1 & mask1);
//      y += (year::first_-1);
//      const bool leap = is_leap(y);
//      const month::rep m = day_of_year_month(leap,doy);
//      const day::rep d = day_of_year_day_of_month(leap,doy);
//      return year_month_day(y, m, d, no_check);
//
//    }
//    year_month_day_leap to_ymd_leap2(days dt)  BOOST_NOEXCEPT
//    {
//      days::rep x=dt.count();
//      year::rep y = static_cast<year::rep>(static_cast<int64_t> (x + 2) * 400 / 146097);
//      const year::rep ym1 = y - 1;
//      day_of_year::rep doy = x - days_before_year(y);
//      const day_of_year::rep doy1 = x - days_before_year(ym1);
//      const int N = std::numeric_limits<int>::digits - 1;
//      const int mask1 = doy >> N; // arithmetic rshift - not portable - but nearly universal
//      const int mask0 = ~mask1;
//      doy = (doy & mask0) | (doy1 & mask1);
//      y = (y & mask0) | (ym1 & mask1);
//      y += (year::first_-1);
//      const bool leap = is_leap(y);
//      const month::rep m = day_of_year_month(leap,doy);
//      const day::rep d = day_of_year_day_of_month(leap,doy);
//      return year_month_day_leap(y, m, d, leap, no_check);
//
//    }
    year_month_day to_ymd(days dt) BOOST_NOEXCEPT
    {
      days::rep x_ = dt.count();
//      std::cout <<"days " << x_ << std::endl;
      year::rep y = static_cast<year::rep>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
//      std::cout <<"y " << y << std::endl;
      int doy = x_ - days_before_year(y);
//      std::cout <<"doy " << doy << std::endl;
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
//        std::cout <<"y " << y << std::endl;
//        std::cout <<"doy " << doy << std::endl;
      }
      //y += (year::first_-1);
      y -= 32799;
//      std::cout <<"y " << y << std::endl;
      const bool leap = is_leap(y);
      const month::rep m = day_of_year_month(leap,doy+1);
//      std::cout <<"m " << int(m) << std::endl;
      const day::rep d = day_of_year_day_of_month(leap,doy+1);
//      std::cout <<"d " << int(d) << std::endl;
      return year_month_day(y, m, d, no_check);
    }
    year_month_day_leap to_ymd_leap(days dt) BOOST_NOEXCEPT
    {
      days::rep x_ = dt.count();
      year::rep y = static_cast<year::rep>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      const bool leap = is_leap(y);
      const month::rep m = day_of_year_month(leap,doy+1);
      const day::rep d = day_of_year_day_of_month(leap,doy+1);
      return year_month_day_leap(y, m, d, leap, no_check);
    }

    days to_days(year_month_day dt) BOOST_NOEXCEPT
    {
      bool leap = dt.get_year().is_leap();
      //year::rep by = dt.get_year().value() - (year::first_-1);
      year::rep by = dt.get_year().value() - 32799;
      return days(days_before_year(by) +
          days_in_year_before(leap,dt.get_month().value()-1) +
          dt.get_day().value());
    }

    days to_days(year_day_of_year dt) BOOST_NOEXCEPT
    {
      return days(days_before_year(dt.get_year())+dt.get_day_of_year());
    }

    year_month_day to_ymd(year_day_of_year dt) BOOST_NOEXCEPT
    {
      bool leap=dt.get_year().is_leap();
      return year_month_day(dt.get_year(), day_of_year_month(leap,dt.get_day_of_year()), day_of_year_day_of_month(leap,dt.get_day_of_year()), no_check);
    }


    year_day_of_year to_ydoy(days dt) BOOST_NOEXCEPT
    {

      days::rep x_=dt.count();
      int y = to_average_year(x_);
      int doy = x_ - (days_before_year(y));
      if (doy < 0)
      {
        --y;
        doy = x_ - (days_before_year(y));
      }
      y -= 32799;
      return year_day_of_year(y, doy+1, no_check);
    }


    year_day_of_year to_ydoy(year_month_day dt) BOOST_NOEXCEPT
    {
      day_of_year::rep doy = month_day_to_day_of_year(dt.get_year().is_leap(),dt.get_month(),dt.get_day());
      return year_day_of_year(dt.get_year(), doy+1, no_check);
    }


  } // chrono
} // boost


