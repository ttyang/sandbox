//  days_date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <boost/chrono/date/days_date.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

//    days_date
//    days_date::today()
//    BOOST_NOEXCEPT
//    {
//      time_t systime;
//      time(&systime);
//      tm now;
//      localtime_r(&systime, &now);
//      return days_date(chrono::year(now.tm_year+1900),chrono::month(now.tm_mon+1), chrono::day(now.tm_mday));
//    }
//
//    days_date::days_date(system_clock::time_point tp)
//    {
//      time_t systime = system_clock::to_time_t(tp);
//      tm now;
//      gmtime_r(&systime, &now);
//      *this
//          = days_date(chrono::year(now.tm_year + 1900), chrono::month(now.tm_mon + 1), chrono::day(now.tm_mday));
//    }
//
//    days_date::operator system_clock::time_point() const
//    {
//      tm now = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
//      now.tm_year = year() - 1900;
//      now.tm_mon = month() - 1;
//      now.tm_mday = day();
//      time_t t = timegm(&now);
//      return system_clock::from_time_t(t);
//    }

    days_date::days_date(chrono::year y, chrono::month m, chrono::day d) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);

//      if (!(d <= year_data[m] - year_data[m-1]))
//      {
//        x_ = 0;
//      }
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m-1] + d;
    }

//    bool days_date::set_if_valid_date(chrono::year y, chrono::month m, chrono::day d)
//    BOOST_NOEXCEPT
//    {
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//
//      if (!(d <= year_data[m] - year_data[m-1]))
//      {
//        return false;
//      }
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + year_data[m-1] + d;
//      return true;
//
//    }
//
//    days_date::days_date(chrono::year y, chrono::month m, chrono::day d, check_t)
//    {
//      if (set_if_valid_date(y, m, d))
//        return;
//      throw bad_date("day " + to_string(d) + " is out of range for "
//          + to_string(y) + '-' + to_string(m));
//    }
//    days_date::days_date(chrono::year y, chrono::month_day md, check_t)
//    {
//      if (set_if_valid_date(y, md.month(), day(md)))
//        return;
//      throw bad_date("day " + to_string(day(md)) + " is out of range for "
//          + to_string(y) + '-' + to_string(md.month()));
//    }
//
//    days_date::days_date(chrono::year y, chrono::month_day md)
//    BOOST_NOEXCEPT
//    {
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + year_data[md.month()-1] + day(md);
//    }
//    days_date::days_date(chrono::year y, chrono::month m, chrono::day d)
//    BOOST_NOEXCEPT
//    {
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + year_data[m-1] + d;
//    }
//
//    days_date::days_date(year::rep y, month::rep m, day::rep d, bool leap)
//    BOOST_NOEXCEPT
//    {
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + year_data[m-1] + d;
//    }
//
//    days_date::days_date(chrono::year y, day_of_year doy, check_t)
//    {
//      if (!y.is_leap() && doy == 366)
//        throw bad_date("doy " + to_string(doy) + " is out of range for year "
//          + to_string(y) );
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + doy - 1;
//    }
//    days_date::days_date(chrono::year y, day_of_year doy)
//    BOOST_NOEXCEPT
//    {
//      year::rep by = y + 32799;
//      x_ = days_before_year(by) + doy - 1;
//    }

    days_date&
    days_date::operator+=(days d)
    {
      x_ += d.count();
      if (!(11322 <= x_ && x_ <= 23947853))
      {
        throw bad_date("year is out of range [-32768, 32767]");
      }

      return *this;
    }

//    days_date&
//    days_date::operator+=(months mn)
//    {
//      //std::cout <<__FILE__<<"["<< __LINE__ <<"]"<< *this << '\n';
//      // to_ymd
//      int y = to_average_year(x_);
//      int doy = x_ - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x_ - (days_before_year(y));
//      }
//      y -= 32799;
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//      int m = std::lower_bound(year_data, year_data + 13, doy) - year_data;
//      int d = doy - year_data[m - 1];
//      //      std::cout <<__FILE__<<"["<< __LINE__ <<":"<< y<<"]"<<m<<":"<<d << '\n';
//
//      // increase month
//      m += mn.count();
//      if (m < 1)
//      {
//        int dy = (12 - m) / 12;
//        y -= dy;
//        m += 12 * dy;
//      }
//      else if (m > 12)
//      {
//        int dy = (m - 1) / 12;
//        y += dy;
//        m -= 12 * dy;
//      }
//      //      std::cout <<__FILE__<<"["<< __LINE__ <<"]"<< y<<":"<<m<<":"<<d << '\n';
//      // validity check and assignment
//      *this
//          = days_date(chrono::year(y, check), chrono::month(m, check), chrono::day(d, check), check);
//
//      return *this;
//    }
//
//    days_date&
//    days_date::operator+=(years yr)
//    {
//      int y = to_average_year(x_);
//      int doy = x_ - (days_before_year(y));
//      if (doy < 0)
//      {
//        --y;
//        doy = x_ - (days_before_year(y));
//      }
//      y -= 32799;
//      bool leap = is_leap(y);
//      const day_of_year::rep* year_data = days_in_year_before(leap);
//      int m = std::lower_bound(year_data, year_data + 13, doy) - year_data;
//      int d = doy - year_data[m - 1];
//      //      std::cout <<__FILE__<<"["<< __LINE__ <<"]"<< y<<":"<<m<<":"<<d << '\n';
//      *this
//          = days_date(chrono::year(y + yr.count(), check), chrono::month(m, check), chrono::day(d, check), check);
//      return *this;
//    }

    day::rep
    days_date::day_from_day_number() const
    BOOST_NOEXCEPT
    {
      year_day_of_year ydoy = to_ydoy(days(x_));
      return day_of_year_day_of_month(is_leap(year(ydoy)),day_of_year(ydoy));
      //      int y = to_average_year(x_);
      //      int doy = x_ - (days_before_year(y));
      //      if (doy < 0)
      //      {
      //        --y;
      //        doy = x_ - (days_before_year(y));
      //      }
      //      y -= 32799;
      //      const day_of_year::rep* year_data = days_in_year_before(is_leap(y));
      //      int m = std::lower_bound(year_data, year_data+13, doy) - year_data;
      //      return static_cast<uint16_t>(doy - year_data[m-1]);
    }

    month::rep
    days_date::month_from_day_number() const
    BOOST_NOEXCEPT
    {
      year_day_of_year ydoy = to_ydoy(days(x_));
      return day_of_year_month(is_leap(year(ydoy)),day_of_year(ydoy));

      //      int y = to_average_year(x_);
      //      int doy = x_ - (days_before_year(y));
      //      if (doy < 0)
      //      {
      //        --y;
      //        doy = x_ - (days_before_year(y));
      //      }
      //      y -= 32799;
      //      const day_of_year::rep* year_data = days_in_year_before(is_leap(y));
      //      return std::lower_bound(year_data, year_data+13, doy) - year_data;
    }

    year::rep
    days_date::year_from_day_number() const
    BOOST_NOEXCEPT
    {
      int y = to_average_year(x_);
      int doy = x_ - (days_before_year(y));
      if (doy < 0)
      {
        --y;
      }
      y -= 32799;
      return static_cast<int16_t>(y);
    }

    bool
    days_date::leap_from_day_number() const
BOOST_NOEXCEPT  {
    return is_leap(year_from_day_number());
  }

} // chrono
} // boost


