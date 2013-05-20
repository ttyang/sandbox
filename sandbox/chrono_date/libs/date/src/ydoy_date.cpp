//  ydoy_date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/chrono/date/conversions.hpp>

namespace boost
{
  namespace chrono
  {

//    ydoy_date
//    ydoy_date::today()
//    BOOST_NOEXCEPT
//    {
//      time_t systime;
//      time(&systime);
//      tm now;
//      localtime_r(&systime, &now);
//      return ydoy_date(
//          chrono::year(now.tm_year+1900),
//          chrono::month(now.tm_mon+1),
//          chrono::day(now.tm_mday)
//      );
//    }

//    ydoy_date::ydoy_date(system_clock::time_point tp)
//    {
//      time_t systime = system_clock::to_time_t(tp);
//      tm now;
//      gmtime_r(&systime, &now);
//      *this
//          = ydoy_date(chrono::year(now.tm_year + 1900), chrono::month(now.tm_mon
//              + 1), chrono::day(now.tm_mday));
//    }
//
//    ydoy_date::operator system_clock::time_point() const
//    {
//      tm now = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//      now.tm_year = year() - 1900;
//      now.tm_mon = month() - 1;
//      now.tm_mday = day();
//      time_t t = timegm(&now);
//      return system_clock::from_time_t(t);
//    }

//    bool ydoy_date::set_if_valid_date(chrono::year y, chrono::month m, chrono::day d)
//    BOOST_NOEXCEPT
//    {
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//
//      if (!(d <= year_data[m] - year_data[m - 1]))
//      {
//        return false;
//      }
//      y_ = y;
//      doy_ = month_day_to_day_of_year(leap,m,d);
//      leap_ = leap;
//      return true;
//    }

//    ydoy_date::ydoy_date(year::rep y, month::rep m, day::rep d, bool leap) BOOST_NOEXCEPT
//        :
//        y_(y),
//        doy_(month_day_to_day_of_year(leap,m,d)),
//        leap_(leap)
//    {
//    }

//    optional_ydoy_date make_valid_ydoy_date(year y, chrono::month m, chrono::day d)
//    BOOST_NOEXCEPT
//    {
//      ydoy_date res;
//      if (res.set_if_valid_date(y,m,d)) return optional_ydoy_date(res);
//      else return optional_ydoy_date();
//
//    }

//    ydoy_date::ydoy_date(chrono::year y, chrono::month m, chrono::day d, check_t)
//    {
//      if (set_if_valid_date(y, m, d))
//        return;
//      throw bad_date("day " + to_string(d) + " is out of range for "
//          + to_string(y) + '-' + to_string(m));
//    }
//
//    ydoy_date::ydoy_date(chrono::year y, chrono::month_day md, check_t)
//    {
//      if (set_if_valid_date(y, md.month(), day(md)))
//        return;
//      throw bad_date("day " + to_string(day(md)) + " is out of range for "
//          + to_string(y) + '-' + to_string(md.month()));
//    }
//
//    ydoy_date::ydoy_date(chrono::year y, chrono::month m, chrono::day d)
//    BOOST_NOEXCEPT
//    :
//    y_(y),
//    doy_(month_day_to_day_of_year(is_leap(y),m,d)),
//    leap_(is_leap(y))
//    {
//    }
//
//    ydoy_date::ydoy_date(chrono::year y, chrono::month_day md)
//    BOOST_NOEXCEPT
//    :
//    y_(y),
//    doy_(month_day_to_day_of_year(is_leap(y),md.month(),md.month())),
//    leap_(is_leap(y))
//    {
//    }

    ydoy_date::ydoy_date(ymd_date dt)
      :
      y_(year(dt)),
      doy_(month_day_to_day_of_year(dt.is_leap_year(),month(dt),day(dt))),
      leap_(dt.is_leap_year())
    {
    }

    ydoy_date::ydoy_date(days_date dt)
    {
      year_day_of_year ydoy = to_ydoy(dt.days_since_epoch());
      y_ = year(ydoy);
      doy_ = day_of_year(ydoy);
      leap_ = is_leap(y_);
    }

//    ydoy_date::ydoy_date(days d, check_t)
//    {
//      days::rep x = d.count();
//      if (!(11322 <= x && x <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//      year::rep y = to_average_year(x);
//      int doy = x - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x - (days_before_year(y));
//      }
//      y -= 32799;
//      ++doy;
//      leap_ = is_leap(y);
//      y_ = y;
//      doy_ = doy;
//    }

//    ydoy_date::ydoy_date(days d) BOOST_NOEXCEPT
//    {
//      days::rep x = d.count();
//      year::rep y = to_average_year(x);
//      int doy = x - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x - (days_before_year(y));
//      }
//      y -= 32799;
//      ++doy;
//      leap_=is_leap(y);
//      y_ = y;
//      doy_ = doy;
//    }

    ydoy_date::ydoy_date(chrono::year y, day_of_year doy, check_t)
    : y_(y),
      doy_(doy),
      leap_(is_leap(y_))
    {
      if (! leap_ && doy_==366)
        throw bad_date("non leap years have no 366 days");
    }

//    ydoy_date&
//    ydoy_date::operator+=(days d)
//    {
//      days::rep x = (days_since_epoch() + d).count();
//      if (!(11322 <= x && x <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//      year::rep y = to_average_year(x);
//      int doy = x - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x - (days_before_year(y));
//      }
//      y -= 32799;
//      ++doy;
//      y_ = y;
//      doy_ = doy;
//      leap_ = is_leap(y);
//      return *this;
//    }
//
//    ydoy_date&
//    ydoy_date::operator+=(months mn)
//    {
//      int32_t y = y_;
//      int32_t m = month();
//      std::cout << __LINE__ <<": "<<m<<  std::endl;
//      m += mn.count();
//      std::cout << __LINE__ <<": "<<m<<  std::endl;
//      if (m < 1)
//      {
//        int dy = (12 - m) / 12;
//        y -= dy;
//        m += 12 * dy;
//      } else if (m > 12)
//      {
//        int dy = (m - 1) / 12;
//        y += dy;
//        m -= 12 * dy;
//      }
//      std::cout << __LINE__ <<": "<<m<<  std::endl;
//      *this = ydoy_date(chrono::year(y, check), chrono::month(m), day(), check);
//      return *this;
//    }
//
//    ydoy_date&
//    ydoy_date::operator+=(years yr)
//    {
//      *this = ymd_date(chrono::year(y_ + yr.count(), check), month(), day(), check);
//      return *this;
//    }

  } // chrono
} // boost



