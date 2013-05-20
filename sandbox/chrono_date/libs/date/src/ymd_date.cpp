//  ymd_date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/date/conversions.hpp>

namespace boost
{
  namespace chrono
  {
    namespace unchecked
    {
      ymd_date ymd_date::today() BOOST_NOEXCEPT
      {
        time_t systime;
        time(&systime);
        tm now;
        localtime_r(&systime, &now);
        return ymd_date(chrono::year(now.tm_year + 1900), month(now.tm_mon + 1), day(now.tm_mday));
      }

      ymd_date::ymd_date(system_clock::time_point tp)
      {
        time_t systime = system_clock::to_time_t(tp);
        tm now;
        gmtime_r(&systime, &now);
        *this = ymd_date(chrono::year(now.tm_year + 1900), month(now.tm_mon + 1), day(now.tm_mday));
      }

      ymd_date::operator system_clock::time_point() const
      {
        tm now =
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        now.tm_year = year(*this) - 1900;
        now.tm_mon = month(*this) - 1;
        now.tm_mday = day(*this);
        time_t t = timegm(&now);
        return system_clock::from_time_t(t);
      }

  //    bool ymd_date::is_valid() const BOOST_NOEXCEPT
  //    {
  //      //if (chrono::year(y_).is_valid() && chrono::month(m_).is_valid() && chrono::day(d_).is_valid())
  //      {
  //        const day_of_year::rep* year_data = days_in_year_before(is_leap_year());
  //
  //        if (! (1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
  //        {
  //          return false;
  //        }
  //        else
  //        {
  //          return true;
  //        }
  //      }
  //      return false;
  //
  //    }

      bool ymd_date::set_if_valid_date(chrono::year y, month m, day d) BOOST_NOEXCEPT
      {
        bool leap = y.is_leap();
        const day_of_year::rep* year_data = days_in_year_before(leap);

        if (! (d <= year_data[m] - year_data[m - 1]))
        {
          return false;
        }
        y_ = y;
        m_ = m;
        d_ = d;
  #if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
        leap_ = leap;
  #endif
        return true;
      }

  //    bool ymd_date::set_if_valid_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT
  //    {
  //      bool leap = y.is_leap();
  //      if (!leap && doy == 366) return false;
  //
  //      y_ = y;
  //      m_ = day_of_year_month(leap, doy);
  //      d_ = day_of_year_day_of_month(leap, doy);
  //      leap_ = leap;
  //      return true;
  //    }

  //    bool ymd_date::set_if_valid_date(days x) BOOST_NOEXCEPT
  //    {
  //      if (! (11322 <= x.count() && x.count() <= 23947853))
  //      {
  //        return false;
  //      }
  //      year_month_day_leap dt = to_ymd_leap(x);
  //      y_ = year(dt);
  //      m_ = month(dt);
  //      d_ = day(dt);
  //      leap_ = dt.is_leap_year();
  //      return true;
  //    }


  //    ymd_date::ymd_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT
  //    {
  //      if (set_if_valid_date(y, doy))
  //      return;
  //
  //      y_ = y;
  //      m_ = 0;
  //      d_ = 0;
  //      leap_ = false;
  //    }
  //
  //    ymd_date::ymd_date(chrono::year y, day_of_year doy, check_t)
  //    {
  //      if (set_if_valid_date(y, doy))
  //      return;
  //      throw bad_date("doy " + to_string(doy) + " is out of range for year "
  //          + to_string(y) );
  //    }
  //
  //    ymd_date::ymd_date(days d, check_t)
  //    {
  //      if (set_if_valid_date(d))
  //      return;
  //      throw bad_date("days " + to_string(d.count()) + " is out of range");
  //    }
  //
  //    ymd_date::ymd_date(days d) BOOST_NOEXCEPT
  //    {
  //      year_month_day_leap dt = to_ymd_leap(d);
  //      y_=year(dt);
  //      m_=month(dt);
  //      d_=day(dt);
  //      leap_=dt.is_leap_year();
  //    }

      ymd_date::ymd_date(days_date dt)
      {
  #if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
  //#if ! defined __clang__
  #if 0
        year_month_day_leap ymdl = to_ymd_leap(dt.days_since_epoch());
        y_=year(ymdl);
        m_=month(ymdl);
        d_=day(ymdl);
        leap_=ymdl.is_leap_year();
  #else
        to_ymd_leap(dt.days_since_epoch().count(), y_,m_,d_,leap_);
  #endif
  #else
        to_ymd(dt.days_since_epoch().count(), y_,m_,d_);
  #endif
      }

      ymd_date::ymd_date(days d)
      {
  #if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
  #if 0
        year_month_day_leap ymdl = to_ymd_leap(d);
        leap_=ymdl.is_leap_year();
        y_=year(ymdl);
        m_=month(ymdl);
        d_=day(ymdl);
  #else
        to_ymd_leap(d.count(), y_,m_,d_,leap_);
  #endif

  #else
        to_ymd(d.count(), y_,m_,d_);
  #endif
      }

  //    ymd_date&
  //    ymd_date::operator+=(days d)
  //    {
  //      days::rep x_ = day_number_from_ymd() + d.count();
  //      if (!(11322 <= x_ && x_ <= 23947853))
  //      {
  //        throw bad_date("year is out of range [-32768, 32767]");
  //      }
  //      year::rep y = to_average_year(x_);
  //      int doy = x_ - (days_before_year(y));
  //      if (doy < 0)
  //      {
  //        --y;
  //        doy = x_ - (days_before_year(y));
  //      }
  //      y_ = static_cast<year::rep> (y - 32799);
  //      leap_ = is_leap(y_);
  //      const day_of_year::rep* year_data = days_in_year_before(leap_);
  //      m_
  //      = static_cast<month::rep> (std::lower_bound(year_data, year_data + 13, doy)
  //          - year_data);
  //      d_ = static_cast<day::rep> (doy - year_data[m_ - 1]);
  //
  //      return *this;
  //    }

      ymd_date&
      ymd_date::operator+=(months mn)
      {
        int_least32_t y = y_;
        int32_t m = m_;
        m += mn.count();
        if (m < 1)
        {
          int dy = (12 - m) / 12;
          y -= dy;
          m += 12 * dy;
        }
        else if (m > 12)
        {
          int dy = (m - 1) / 12;
          y += dy;
          m -= 12 * dy;
        }
        *this = ymd_date(chrono::year(y), month(m), day(d_));
        return *this;
      }

      ymd_date&
      ymd_date::operator+=(years yr)
      {
        *this
        = ymd_date(chrono::year(y_ + yr.count()), month(m_), day(d_));
        //      y_ += yr.count();
        return *this;
      }

      days::rep
      ymd_date::day_number_from_ymd() const BOOST_NOEXCEPT
      {

        days::rep by = y_ + 32799;
        //const day_of_year::rep* year_data = days_in_year_before(is_leap_year());
        //return days_before_year(by) + year_data[m_-1] + d_;
        return days_before_year(by) + days_in_year_before(is_leap_year(), m_-1) + d_;

      }
    }
    ymd_date ymd_date::today() BOOST_NOEXCEPT
    {
      time_t systime;
      time(&systime);
      tm now;
      localtime_r(&systime, &now);
      return ymd_date(chrono::year(now.tm_year + 1900), chrono::month(now.tm_mon + 1), chrono::day(now.tm_mday, no_check));
    }

    ymd_date::ymd_date(system_clock::time_point tp)
    {
      time_t systime = system_clock::to_time_t(tp);
      tm now;
      gmtime_r(&systime, &now);
      *this = ymd_date(chrono::year(now.tm_year + 1900), chrono::month(now.tm_mon + 1), chrono::day(now.tm_mday, no_check));
    }

    ymd_date::operator system_clock::time_point() const
    {
      tm now =
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      now.tm_year = year(*this) - 1900;
      now.tm_mon = month(*this) - 1;
      now.tm_mday = day(*this);
      time_t t = timegm(&now);
      return system_clock::from_time_t(t);
    }

//    bool ymd_date::is_valid() const BOOST_NOEXCEPT
//    {
//      //if (chrono::year(y_).is_valid() && chrono::month(m_).is_valid() && chrono::day(d_).is_valid())
//      {
//        const day_of_year::rep* year_data = days_in_year_before(is_leap_year());
//
//        if (! (1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
//        {
//          return false;
//        }
//        else
//        {
//          return true;
//        }
//      }
//      return false;
//
//    }

    bool ymd_date::set_if_valid_date(chrono::year y, chrono::month m, chrono::day d) BOOST_NOEXCEPT
    {
      bool leap = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (! (d <= year_data[m] - year_data[m - 1]))
      {
        return false;
      }
      y_ = y;
      m_ = m;
      d_ = d;
#if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
      leap_ = leap;
#endif
      return true;
    }

//    bool ymd_date::set_if_valid_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT
//    {
//      bool leap = y.is_leap();
//      if (!leap && doy == 366) return false;
//
//      y_ = y;
//      m_ = day_of_year_month(leap, doy);
//      d_ = day_of_year_day_of_month(leap, doy);
//      leap_ = leap;
//      return true;
//    }

//    bool ymd_date::set_if_valid_date(days x) BOOST_NOEXCEPT
//    {
//      if (! (11322 <= x.count() && x.count() <= 23947853))
//      {
//        return false;
//      }
//      year_month_day_leap dt = to_ymd_leap(x);
//      y_ = year(dt);
//      m_ = month(dt);
//      d_ = day(dt);
//      leap_ = dt.is_leap_year();
//      return true;
//    }


//    ymd_date::ymd_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT
//    {
//      if (set_if_valid_date(y, doy))
//      return;
//
//      y_ = y;
//      m_ = 0;
//      d_ = 0;
//      leap_ = false;
//    }
//
//    ymd_date::ymd_date(chrono::year y, day_of_year doy, check_t)
//    {
//      if (set_if_valid_date(y, doy))
//      return;
//      throw bad_date("doy " + to_string(doy) + " is out of range for year "
//          + to_string(y) );
//    }
//
//    ymd_date::ymd_date(days d, check_t)
//    {
//      if (set_if_valid_date(d))
//      return;
//      throw bad_date("days " + to_string(d.count()) + " is out of range");
//    }
//
//    ymd_date::ymd_date(days d) BOOST_NOEXCEPT
//    {
//      year_month_day_leap dt = to_ymd_leap(d);
//      y_=year(dt);
//      m_=month(dt);
//      d_=day(dt);
//      leap_=dt.is_leap_year();
//    }

    ymd_date::ymd_date(days_date dt)
    {
#if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
//#if ! defined __clang__
#if 0
      year_month_day_leap ymdl = to_ymd_leap(dt.days_since_epoch());
      y_=year(ymdl);
      m_=month(ymdl);
      d_=day(ymdl);
      leap_=ymdl.is_leap_year();
#else
      to_ymd_leap(dt.days_since_epoch().count(), y_,m_,d_,leap_);
#endif
#else
      to_ymd(dt.days_since_epoch().count(), y_,m_,d_);
#endif
    }

    ymd_date::ymd_date(days d)
    {
#if defined  BOOST_CHRONO_DATE_YMD_DATE_HAS_LEAP_FIELD
#if 0
      year_month_day_leap ymdl = to_ymd_leap(d);
      leap_=ymdl.is_leap_year();
      y_=year(ymdl);
      m_=month(ymdl);
      d_=day(ymdl);
#else
      to_ymd_leap(d.count(), y_,m_,d_,leap_);
#endif

#else
      to_ymd(d.count(), y_,m_,d_);
#endif
    }

//    ymd_date&
//    ymd_date::operator+=(days d)
//    {
//      days::rep x_ = day_number_from_ymd() + d.count();
//      if (!(11322 <= x_ && x_ <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//      year::rep y = to_average_year(x_);
//      int doy = x_ - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x_ - (days_before_year(y));
//      }
//      y_ = static_cast<year::rep> (y - 32799);
//      leap_ = is_leap(y_);
//      const day_of_year::rep* year_data = days_in_year_before(leap_);
//      m_
//      = static_cast<month::rep> (std::lower_bound(year_data, year_data + 13, doy)
//          - year_data);
//      d_ = static_cast<day::rep> (doy - year_data[m_ - 1]);
//
//      return *this;
//    }

    ymd_date&
    ymd_date::operator+=(months mn)
    {
      int_least32_t y = y_;
      int32_t m = m_;
      m += mn.count();
      if (m < 1)
      {
        int dy = (12 - m) / 12;
        y -= dy;
        m += 12 * dy;
      }
      else if (m > 12)
      {
        int dy = (m - 1) / 12;
        y += dy;
        m -= 12 * dy;
      }
      *this
      = ymd_date(chrono::year(y), month(m, no_check), day(d_, no_check));
      return *this;
    }

    ymd_date&
    ymd_date::operator+=(years yr)
    {
      *this
      = ymd_date(chrono::year(y_ + yr.count()), chrono::month(m_, no_check), chrono::day(d_, no_check));
      return *this;
    }

    days::rep
    ymd_date::day_number_from_ymd() const BOOST_NOEXCEPT
    {

      days::rep by = y_ + 32799;
      //const day_of_year::rep* year_data = days_in_year_before(is_leap_year());
      //return days_before_year(by) + year_data[m_-1] + d_;
      return days_before_year(by) + days_in_year_before(is_leap_year(), m_-1) + d_;

    }

  } // chrono
} // boost


