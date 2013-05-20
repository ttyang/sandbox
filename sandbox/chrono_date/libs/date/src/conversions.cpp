//  date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/tuples.hpp>
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
//      return year_month_day(y, m, d);
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
//      return year_month_day_leap(y, m, d, leap);
//
//    }

    void to_ymd(days::rep x_, int& y, int& m, int& d) BOOST_NOEXCEPT
    {
      y = static_cast<year::rep>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      const bool leap = is_leap(y);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }

    void to_ymd(days::rep x_, int_least32_t& y, int_least16_t& m, int_least16_t& d) BOOST_NOEXCEPT
    {
      y = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      const bool leap = is_leap(y);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }

//    int_least16_t to_ymd_leap(days::rep x_, int_least32_t y, int_least16_t& m, int_least16_t& d, bool& leap) BOOST_NOEXCEPT
//    {
//      y = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
//      int doy = x_ - days_before_year(y);
//      if (doy < 0)
//      {
//        --y;
//        doy = x_ - days_before_year(y);
//      }
//      //y += (year::first_-1);
//      y -= 32799;
//      leap = is_leap(y);
//      m = day_of_year_month(leap,doy+1);
//      d = day_of_year_day_of_month(leap,doy+1);
//      return y;
//    }
    void to_ymd_leap(days::rep x_, int_least32_t& y, int_least32_t& m, int_least32_t& d, bool& leap) BOOST_NOEXCEPT
    {
      y = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      leap = is_leap(y);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }
    void to_ymd_leap(days::rep x_, int_least32_t& y, int_least32_t& m, int_least32_t& d, int_least32_t& leap) BOOST_NOEXCEPT
    {
      y = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      leap = is_leap(y);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }
    void to_ymd_leap(days::rep x_, int_least32_t& y, int_least16_t& m, int_least16_t& d, bool& leap) BOOST_NOEXCEPT
    {
      y = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      //y += (year::first_-1);
      y -= 32799;
      leap = is_leap(y);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }
    void to_ymd_leap(days::rep x_, int_least16_t& y, int_least8_t& m, int_least8_t& d, bool& leap) BOOST_NOEXCEPT
    {
      int_least32_t y32 = static_cast<int_least32_t>(static_cast<int64_t>(x_ + 2) * 400 / 146097);
      int doy = x_ - days_before_year(y32);
      if (doy < 0)
      {
        --y32;
        doy = x_ - days_before_year(y32);
      }
      //y += (year::first_-1);
      y32 -= 32799;
      leap = is_leap(y32);
      y  = static_cast<int_least16_t>(y32);
      m = day_of_year_month(leap,doy+1);
      d = day_of_year_day_of_month(leap,doy+1);
    }
    year_month_day to_ymd(days dt) BOOST_NOEXCEPT
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
      return year_month_day(year(y), month(m), day(d, no_check));
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
      return year_month_day_leap(y, m, d, leap);
    }

    days to_days(year_month_day dt) BOOST_NOEXCEPT
    {
      bool leap = year(dt).is_leap();
      //year::rep by = year(dt) - (year::first_-1);
      year::rep by = year(dt) - 32799;
      return days(days_before_year(by) +
          days_in_year_before(leap,month(dt)-1) +
          day(dt));
    }
    days::rep to_days(int_least32_t y, int_least16_t m, int_least16_t d) BOOST_NOEXCEPT
    {
      return days_before_year(y - 32799) +
          days_in_year_before(is_leap(y),m-1) +
          d;
    }
    days::rep to_days(int_least32_t y, int_least16_t m, int_least16_t d, bool leap) BOOST_NOEXCEPT
    {
      return days_before_year(y - 32799) +
          days_in_year_before(leap,m-1) +
          d;
    }
    days::rep to_days(int y, int m, int d) BOOST_NOEXCEPT
    {
      return days_before_year(static_cast<int_least32_t>(y - 32799)) +
          days_in_year_before(is_leap(y),m-1) +
          d;
    }

    days to_days(year_day_of_year dt) BOOST_NOEXCEPT
    {
      return days(days_before_year(year(dt))+day_of_year(dt));
    }

    year_month_day to_ymd(year_day_of_year dt) BOOST_NOEXCEPT
    {
      bool leap=year(dt).is_leap();
      return year_month_day(year(year(dt)), month(day_of_year_month(leap,day_of_year(dt))), day(day_of_year_day_of_month(leap,day_of_year(dt)), no_check));
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
      return year_day_of_year(year(y), day_of_year(doy+1));
    }


    year_day_of_year to_ydoy(year_month_day dt) BOOST_NOEXCEPT
    {
      day_of_year::rep doy = month_day_to_day_of_year(year(dt).is_leap(),month(dt),day(dt));
      return year_day_of_year(year(year(dt)), day_of_year(doy+1));
    }


  } // chrono
} // boost


