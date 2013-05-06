//  ymd_date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/chrono/date/conversions.hpp>

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN==2
#else
namespace boost
{
  namespace chrono
  {

//    ymd_date::ymd_date()
//    BOOST_NOEXCEPT
//    :
//#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
//    x_(11979588),
//#endif
//    y_(0),
//    m_(1),
//    d_(1),
//    leap_(1)
//    {
//    }

    ymd_date
    ymd_date::today()
    BOOST_NOEXCEPT
    {
      time_t systime;
      time(&systime);
      tm now;
      localtime_r(&systime, &now);
      return ymd_date(
          year(now.tm_year+1900),
          month(now.tm_mon+1),
          day(now.tm_mday)
      );
    }

    ymd_date::ymd_date(system_clock::time_point tp)
    {
      time_t systime = system_clock::to_time_t(tp);
      tm now;
      gmtime_r(&systime, &now);
      *this
          = ymd_date(year(now.tm_year + 1900), month(now.tm_mon
              + 1), day(now.tm_mday));
    }

    ymd_date::operator system_clock::time_point() const
    {
      tm now = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      now.tm_year = get_year() - 1900;
      now.tm_mon = get_month() - 1;
      now.tm_mday = get_day();
      time_t t = timegm(&now);
      return system_clock::from_time_t(t);
    }

    bool ymd_date::is_valid() const
    BOOST_NOEXCEPT
    {
      if (year(y_).is_valid() && month(m_).is_valid() && day(d_).is_valid()) {
        const day_of_year::rep* year_data = days_in_year_before(leap_);

        if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
        {
          return false;
        }
        else
        {
          return true;
        }
      }
      return false;


    }

    bool ymd_date::set_if_valid_date(year y, month m, day d)
    BOOST_NOEXCEPT
    {
      bool leap = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return false;
      }
      y_ = y;
      m_ = m;
      d_ = d;
      leap_ = leap;
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
#endif
      return true;
    }

    bool ymd_date::set_if_valid_date(year y, day_of_year doy)
    BOOST_NOEXCEPT
    {
      bool leap = y.is_leap();
      if (!leap && doy == 366)
         return false;

      y_ = y;
      m_ = day_of_year_month(leap, doy);
      d_ = day_of_year_day_of_month(leap,doy);
      leap_ = leap;
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      year::rep by = y + 32799;
      x_ = days_before_year(by) + doy -1;
#endif
      return true;
    }

    bool ymd_date::set_if_valid_date(days x)
    BOOST_NOEXCEPT
    {
      if (!(11322 <= x.count() && x.count() <= 23947853))
      {
        return false;
      }
      year_month_day_leap dt = to_ymd_leap(x);
      y_=dt.get_year();
      m_=dt.get_month();
      d_=dt.get_day();
      leap_=dt.is_leap_year();
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      x_=x.count();
#endif
      return true;
    }


#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
    ymd_date::ymd_date(year::rep y, month::rep m, day::rep d, bool leap) BOOST_NOEXCEPT
        :
        y_(y),
        m_(m),
        d_(d),
        leap_(leap)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
    }
#endif

    ymd_date::ymd_date(year y, month m, day d, check_t)
    {
      if (set_if_valid_date(y, m, d))
        return;
      throw bad_date("day " + to_string(d) + " is out of range for "
          + to_string(y) + '-' + to_string(m));
    }

    ymd_date::ymd_date(year y, month_day md, check_t)
    {
      if (set_if_valid_date(y, md.get_month(), md.get_day()))
        return;
      throw bad_date("day " + to_string(md.get_day()) + " is out of range for "
          + to_string(y) + '-' + to_string(md.get_month()));
    }

    ymd_date::ymd_date(year y, month m, day d)
    BOOST_NOEXCEPT
    : y_(y), m_(m), d_(d), leap_(is_leap(y_))
    {


#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      const day_of_year::rep* year_data = days_in_year_before(leap_);

      int_least32_t by = y_ + 32799;
      x_ = days_before_year(by) + year_data[m_ - 1] + d_;
#endif
    }
    ymd_date::ymd_date(year y, month_day md)
    BOOST_NOEXCEPT
    : y_(y), m_(md.get_month()), d_(md.get_day()), leap_(is_leap(y_))
    {
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      const day_of_year::rep* year_data = days_in_year_before(leap_);

      int_least32_t by = y_ + 32799;
      x_ = days_before_year(by) + year_data[m_ - 1] + d_;
#endif
    }

    ymd_date::ymd_date(year y, day_of_year doy) BOOST_NOEXCEPT
    {
      if (set_if_valid_date(y, doy))
        return;

        y_ = y;
        m_ = 0;
        d_ = 0;
        leap_ = false;
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
        x_ = 0;
#endif

    }

    ymd_date::ymd_date(year y, day_of_year doy, check_t)
    {
      if (set_if_valid_date(y, doy))
        return;
      throw bad_date("doy " + to_string(doy) + " is out of range for year "
          + to_string(y) );
    }

    ymd_date::ymd_date(days d, check_t)
    {
      if (set_if_valid_date(d))
        return;
      throw bad_date("days " + to_string(d.count()) + " is out of range");
    }

    ymd_date::ymd_date(days d) BOOST_NOEXCEPT
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
        : x_(d)
#endif
        {
            year_month_day_leap dt = to_ymd_leap(d);
            y_=dt.get_year();
            m_=dt.get_month();
            d_=dt.get_day();
            leap_=dt.is_leap_year();
        }

    ymd_date::ymd_date(days_date dt)
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
        : x_(dt.days_since_epoch().count())
#endif
        {
            y_=dt.get_year();
            m_=dt.get_month();
            d_=dt.get_day();
            leap_=dt.is_leap_year();
        }



    ymd_date&
    ymd_date::operator+=(days d)
    {
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      x_ += d.count();
#elif BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      days::rep x_ = day_number_from_ymd() + d.count();
#endif
      if (!(11322 <= x_ && x_ <= 23947853))
      {
        throw bad_date("year is out of range [-32768, 32767]");
      }
      year::rep y = to_average_year(x_);
      int doy = x_ - (days_before_year(y));
      if (doy < 0)
      {
        --y;
        doy = x_ - (days_before_year(y));
      }
      y_ = static_cast<year::rep> (y - 32799);
      leap_ = is_leap(y_);
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      m_
          = static_cast<month::rep> (std::lower_bound(year_data, year_data + 13, doy)
              - year_data);
      d_ = static_cast<day::rep> (doy - year_data[m_ - 1]);

      return *this;
    }

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
      } else if (m > 12)
      {
        int dy = (m - 1) / 12;
        y += dy;
        m -= 12 * dy;
      }
      *this
          = ymd_date(year(y, check), month(m), day(d_), check);
      return *this;
    }

    ymd_date&
    ymd_date::operator+=(years yr)
    {
      *this
          = ymd_date(year(y_ + yr.count(), check), month(m_, check), day(d_, check), check);
      return *this;
    }

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3

  days::rep
  ymd_date::day_number_from_ymd() const BOOST_NOEXCEPT
  {
    days::rep by = y_ + 32799;
    const day_of_year::rep* year_data = days_in_year_before(leap_);
    return days_before_year(by) + year_data[m_-1] + d_;
  }

#endif

  } // chrono
} // boost

#endif

