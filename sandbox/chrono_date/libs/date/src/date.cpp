//  date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <string>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

#if defined BOOST_CHRONO_DATE_DATE_DESIGN_BUG && BOOST_CHRONO_DATE_DATE_DESIGN == 2
namespace boost
{
  namespace chrono
  {





//    static
//    const int
//        is_leap_table_[400] =
//            { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
//    /**
//     * is_leap could be implemented by using a table indexed by the y % 400.
//     * This table could contain true for y such as
//     * y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)
//     *
//     * is_leap = is_leap_table[y%400]
//     */
//
//    static
//    inline
//    bool
//    is_leap_table(int y)
//    BOOST_NOEXCEPT
//    {
//      return is_leap_table_[y%400];
//    }


    /**
     * from_ymd could be made more efficient by using a table
     * day_count_table indexed by the y%400.
     * This table could contain the day_count
     * by*365 + by/4 - by/100 + by/400
     *
     * from_ymd = (by/400)*days_by_400_years+day_count_table[by%400] +
     * days_in_year_before[is_leap_table[by%400]][m-1] + d;
     */


    days::rep from_ymd(int32_t y, int32_t m, int32_t d)  BOOST_NOEXCEPT
    {
      //days::rep by = y + (-year::first_ +1) + 2;
      days::rep by = y + 32799;
      return days_before_year(by) + days_in_year_before(is_leap(by),m - 1) + d;
    }

    boost::tuple<year::rep, month::rep, day::rep> to_ymd(days::rep x)  BOOST_NOEXCEPT
    {
      year::rep y = static_cast<year::rep> (static_cast<long long> (x + 2) * 400
          / 146097);
      const year::rep ym1 = y - 1;
      day_of_year::rep doy = x - days_before_year(y);
      const day_of_year::rep doy1 = x - days_before_year(ym1);
      const int N = std::numeric_limits<int>::digits - 1;
      const int mask1 = doy >> N; // arithmetic rshift - not portable - but nearly universal
      const int mask0 = ~mask1;
      doy = (doy & mask0) | (doy1 & mask1);
      y = (y & mask0) | (ym1 & mask1);
      //y += (year::first_-1);
      y -= 32799);
      const bool leap = is_leap(y);
      const month::rep m = day_of_year_month(leap,doy);
      const day::rep d = doy - days_in_year_before(leap,m - 1);
      return boost::make_tuple(y, m, d);

    }

    static inline year::rep
    year_of(days::rep x_) BOOST_NOEXCEPT
    {
      int y = to_average_year(x_);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
      }
      y -= 32799;
      return static_cast<year::rep>(y);
    }


#if BOOST_CHRONO_DATE_DATE_DESIGN == 1

    date::date() BOOST_NOEXCEPT
    : x_(11979588),
    y_(0),
    m_(1),
    d_(1),
    leap_(1)
    {
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2

    date::date() BOOST_NOEXCEPT
    : x_(11979588)
    {
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3

    date::date() BOOST_NOEXCEPT
    : y_(0),
    m_(1),
    d_(1),
    leap_(1)
    {
    }

#endif

    date
    date::today() BOOST_NOEXCEPT
    {
      time_t systime;
      time(&systime);
      tm now;
      localtime_r(&systime, &now);
      //return chrono::year(now.tm_year+1900,no_check)/chrono::month(now.tm_mon+1,no_check)/chrono::day(now.tm_mday,no_check);
      return date(chrono::year(now.tm_year+1900),chrono::month(now.tm_mon+1),chrono::day(now.tm_mday));
    }

    date::date(boost::chrono::system_clock::time_point tp)
    {
      time_t systime = boost::chrono::system_clock::to_time_t(tp);
      tm now;
      gmtime_r(&systime, &now);
      *this = date(chrono::year(now.tm_year + 1900)
          , chrono::month(now.tm_mon + 1)
          , chrono::day(now.tm_mday));
//      *this = chrono::year(now.tm_year + 1900, no_check)
//      / chrono::month(now.tm_mon + 1, no_check)
//      / chrono::day(now.tm_mday, no_check);
    }

    date::operator boost::chrono::system_clock::time_point() const
    {
      tm now =
      { 0 };
      now.tm_year = get_year() - 1900;
      now.tm_mon = get_month() - 1;
      now.tm_mday = get_day();
      time_t t = timegm(&now);
      return boost::chrono::system_clock::from_time_t(t);
    }

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 3
    bool date::is_valid() const BOOST_NOEXCEPT
    {
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
#endif

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1
    bool date::set_if_valid_date(year y,month m,day d) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return false;
      }
      y_ = y.value();
      m_ = m.value();
      d_ = d.value();
      leap_ = leap;
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
      return true;
    }


#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
    bool date::set_if_valid_date(year y,month m,day d) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y.value());
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (!(d.value() <= year_data[m.value()] - year_data[m.value()-1]))
      {
        return false;
      }
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + year_data[m.value()-1] + d.value();
      return true;

    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
    bool date::set_if_valid_date(year y,month m,day d) BOOST_NOEXCEPT
    {
      bool leap = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (!(d <= year_data[m] - year_data[m-1]))
      {
        return false;
      }
      y_ = y.value();
      m_ = m.value();
      d_ = d.value();
      leap_ = leap;
      return true;

    }

#endif

    optional_date make_valid_date(year y, month m, day d) BOOST_NOEXCEPT
    {
      date res;
      if (res.set_if_valid_date(y,m,d)) return optional_date(res);
      else return optional_date();

    }

    date::date(chrono::year y, chrono::month m, chrono::day d)
    {
      if (set_if_valid_date(y,m,d)) return;
      throw bad_date("day " + to_string(d) + " is out of range for "
          + to_string(y) + '-' + to_string(m));
    }
    date::date(chrono::year y, chrono::month_day md)
    {
      if (set_if_valid_date(y,md.get_month(), md.get_day())) return;
      throw bad_date("day " + to_string(md.get_day()) + " is out of range for "
          + to_string(y) + '-' + to_string(md.get_month()));
    }

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1

    date::date(year::rep y, month::rep m, day::rep d, no_check_t) BOOST_NOEXCEPT
        : y_(y), m_(m), d_(d)
    {
      leap_ = is_leap(y_);
      const day_of_year::rep* year_data = days_in_year_before(leap_);

      int32_t by = y_ + 32799;
      x_ = days_before_year(by) + year_data[m_ - 1] + d_;
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2

    date::date(year::rep y, month::rep m, day::rep d, no_check_t) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);

      int32_t by = y + 32799;
      x_ = days_before_year(by) + year_data[m-1] + d;
    }

    date::date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
    {
      const day_of_year::rep* year_data = days_in_year_before(leap);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m-1] + d;
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3

    date::date(year::rep y, month::rep m, day::rep d, no_check_t) BOOST_NOEXCEPT
    : y_(y),
    m_(m),
    d_(d),
    leap_(is_leap(y_))
    {
    }

#endif

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1

    date&
    date::operator+=(days d)
    {
      x_ += d.count();
      if (!(11322 <= x_ && x_ <= 23947853))
      {
        throw bad_date("year is out of range [-32768, 32767]");
      }
      year::rep y = to_average_year(x_);
      int doy = x_ - days_before_year(y);
      if (doy < 0)
      {
        --y;
        doy = x_ - days_before_year(y);
      }
      y_ = static_cast<int16_t> (y - 32799);
      leap_ = is_leap(y_);
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      m_
          = static_cast<uint16_t> (std::lower_bound(year_data, year_data + 13, doy)
              - year_data);
      d_ = static_cast<uint16_t> (doy - year_data[m_ - 1]);

      return *this;
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2

    date&
    date::operator+=(days d)
    {
      x_ += d.count();
      if (!(11322 <= x_ && x_ <= 23947853))
      {
        throw bad_date("year is out of range [-32768, 32767]");
      }

      return *this;
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3

    date&
    date::operator+=(days d)
    {
      days::rep x = day_number_from_ymd() + d.count();
      if (!(11322 <= x && x <= 23947853))
      {
        throw bad_date("year is out of range [-32768, 32767]");
      }
      year::rep y = to_average_year(x);
      int doy = x - (days_before_year(y));
      if (doy < 0)
      {
        --y;
        doy = x - (days_before_year(y));
      }
      y_ = static_cast<int16_t>(y - 32799);
      leap_ = is_leap(y_);
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      m_ = static_cast<uint16_t>(std::lower_bound(year_data, year_data+13, doy)
          - year_data);
      d_ = static_cast<uint16_t>(doy - year_data[m_-1]);

      return *this;
    }

#endif

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 3

    date&
    date::operator+=(months mn)
    {
      int32_t y = y_;
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
      *this = chrono::day(d_) / chrono::month(m, no_check) / y;
      return *this;
    }

    date&
    date::operator+=(years yr)
    {
      *this = chrono::day(d_) / chrono::month(m_, no_check) / (y_ + yr.count());
      return *this;
    }

#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2

  date&
  date::operator+=(months mn)
  {
    int y = to_average_year(x_);
    int doy = x_ - (days_before_year(y));
    if (doy < 0)
    {
      --y;
      doy = x_ - (days_before_year(y));
    }
    y -= 32799;
    bool leap = is_leap(y);
    const day_of_year::rep* year_data = days_in_year_before(leap);
    int m = std::lower_bound(year_data, year_data+13, doy) - year_data;
    int d = doy - year_data[m-1];
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
    *this = chrono::day(d)/chrono::month(m)/y;
    return *this;
  }

  date&
  date::operator+=(years yr)
  {
    int y = to_average_year(x_);
    int doy = x_ - (days_before_year(y));
    if (doy < 0)
    {
      --y;
      doy = x_ - (days_before_year(y));
    }
    y -= 32799;
    bool leap = is_leap(y);
    const day_of_year::rep* year_data = days_in_year_before(leap);
    int m = std::lower_bound(year_data, year_data+13, doy) - year_data;
    int d = doy - year_data[m-1];
    *this = date(y + yr.count(), m, d, no_check);
    return *this;
  }

#endif

#if BOOST_CHRONO_DATE_DATE_DESIGN == 2

  day::rep
  date::day_from_day_number() const BOOST_NOEXCEPT
  {
    year_day_of_year ydoy = to_ydoy(days(x_));
    return day_of_year_day_of_month(is_leap(ydoy.get_year()),ydoy.get_day_of_year());
//    int m = std::lower_bound(year_data, year_data+13, ydoy.get_day_of_year()) - year_data;
//    return static_cast<uint16_t>(ydoy.get_day_of_year() - year_data[m-1]);

//    int y = to_average_year(x_);
//    int doy = x_ - (days_before_year(y));
//    if (doy < 0)
//    {
//      --y;
//      doy = x_ - (days_before_year(y));
//    }
//    y -= 32799;
//    const day_of_year::rep* year_data = days_in_year_before(is_leap(y));
//    int m = std::lower_bound(year_data, year_data+13, doy) - year_data;
//    return static_cast<uint16_t>(doy - year_data[m-1]);
  }

  month::rep
  date::month_from_day_number() const BOOST_NOEXCEPT
  {
    year_day_of_year ydoy = to_ydoy(days(x_));
    return day_of_year_month(is_leap(ydoy.get_year()),ydoy.get_day_of_year());

//    int y = to_average_year(x_);
//    int doy = x_ - (days_before_year(y));
//    if (doy < 0)
//    {
//      --y;
//      doy = x_ - (days_before_year(y));
//    }
//    y -= 32799;
//    const day_of_year::rep* year_data = days_in_year_before(is_leap(y));
//    return std::lower_bound(year_data, year_data+13, doy) - year_data;
  }

  year::rep
  date::year_from_day_number() const BOOST_NOEXCEPT
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
  date::leap_from_day_number() const BOOST_NOEXCEPT
  {
    return is_leap(year_from_day_number());
  }

#endif

#if BOOST_CHRONO_DATE_DATE_DESIGN == 3

  days::rep
  date::day_number_from_ymd() const BOOST_NOEXCEPT
  {
    days::rep by = y_ + 32799;
    const day_of_year::rep* year_data = days_in_year_before(leap_);
    return days_before_year(by) + year_data[m_-1] + d_;
  }

#endif

  } // chrono
} // boost
#endif


