//  julian.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include "julian.hpp"
#include <boost/chrono/date/detail/to_string.hpp>

namespace julian
{

  const weekday sun(0);
  const weekday mon(1);
  const weekday tue(2);
  const weekday wed(3);
  const weekday thu(4);
  const weekday fri(5);
  const weekday sat(6);

  const month jan(1);
  const month feb(2);
  const month mar(3);
  const month apr(4);
  const month may(5);
  const month jun(6);
  const month jul(7);
  const month aug(8);
  const month sep(9);
  const month oct(10);
  const month nov(11);
  const month dec(12);

  namespace detail
  {
    day_spec make_day_spec(uint8_t s)
    {
      return day_spec(s);
    }
  }
  const detail::day_spec first = detail::make_day_spec(1);
  const detail::day_spec second = detail::make_day_spec(2);
  const detail::day_spec third = detail::make_day_spec(3);
  const detail::day_spec fourth = detail::make_day_spec(4);
  const detail::day_spec fifth = detail::make_day_spec(5);
  const detail::day_spec last = detail::make_day_spec(6);

  static
  int db[2][13] =
  {
  { -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364 },
  { -1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 } };

  static
  inline
  bool is_civil_leap(int y)
  {
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
  }

  static
  inline
  bool is_leap(int y)
  {
    return y % 4 == 0;
  }

  year::year(int32_t v) :
    y_(v)
  {
    if (!(-32768 <= v && v <= 32767))
      throw bad_date("year " + boost::chrono::to_string(v) + " is out of range");
  }

  month::month(int v) :
    m_(v)
  {
    if (!(1 <= v && v <= 12))
      throw bad_date("month " + boost::chrono::to_string(v) + " is out of range");
  }

  day::day(int d) :
    d_(d), n_(7), dow_(7)
  {
    if (d < 1 || d > 31)
      throw bad_date("day " + boost::chrono::to_string(d) + " is out of range");
  }

  day::day(uint8_t d, uint8_t n, uint8_t dow) :
    d_(d), n_(n), dow_(dow)
  {
  }

  day::day(detail::day_spec s) :
    d_(1), n_(s.s_), dow_(7)
  {
  }

  weekday::weekday(int v) :
    wd_(v)
  {
    if (v < 0 || v > 6)
      throw bad_date("week day " + boost::chrono::to_string(v) + " is out of range");
  }

  day operator*(int n, weekday wd)
  {
    if (n < 1 || n > 5)
      throw bad_date("week day multiplier " + boost::chrono::to_string(n)
          + " is out of range");
    return detail::day_spec(n) * wd;
  }

  date::date(boost::chrono::date d)
  {
    uint32_t by = d.get_year() + 32799;
    int* year_data = db[is_civil_leap(by)];
    x_ = by * 365 + by / 4 - by / 100 + by / 400 + 248 + year_data[d.get_month()
        - 1] + d.get_day();
    int y = static_cast<int> (static_cast<int64_t> (x_ + 1) * 4 / 1461);
    int doy = x_ - (y * 365 + y / 4);
    if (doy < 0)
    {
      --y;
      doy = x_ - (y * 365 + y / 4);
    }
    y_ = static_cast<int16_t> (y - 32799);
    leap_ = is_leap(y_);
    year_data = db[leap_];
    m_
        = static_cast<uint16_t> (std::lower_bound(year_data, year_data + 13, doy)
            - year_data);
    d_ = static_cast<uint16_t> (doy - year_data[m_ - 1]);
    n_ = 7;
    dow_ = 7;
  }

  date::operator boost::chrono::date() const
  {
    int y = static_cast<int> (static_cast<int64_t> (x_ + (-248 + 2)) * 400
        / 146097);
    int doy = x_ - 248 - (y * 365 + y / 4 - y / 100 + y / 400);
    if (doy < 0)
    {
      --y;
      doy = x_ - 248 - (y * 365 + y / 4 - y / 100 + y / 400);
    }
    y -= 32799;
    int* year_data = db[is_civil_leap(y)];
    int m = std::lower_bound(year_data, year_data + 13, doy) - year_data;
    int d = doy - year_data[m - 1];
    return boost::chrono::year(y) / boost::chrono::month(m) / d;
  }

  date::date(julian::year y, julian::month m, julian::day d) :
    y_(y.y_), m_(m.m_), d_(d.d_), n_(d.n_), dow_(d.dow_)
  {
    leap_ = is_leap(y_);
    int* year_data = db[leap_];
    if (n_ != 7) // if a detail::day_spec is involved

    {
      if (dow_ == 7) // if we want nth day of month

      {
        if (n_ == 6) // want last day of month
          d_ = year_data[m_] - year_data[m_ - 1];
        else
          d_ = n_; // want nth day of month
      } else // we want nth weekday of month

      {
        // dow_ = [0 - 6]
        // n_ = [1 - 6] 6 means last
        int32_t by = y.y_ + 32799;
        int32_t fy = by * 365 + by / 4;
        int n_days_in_month = year_data[m_] - year_data[m_ - 1];
        int d;
        if (n_ == 6)
        {
          int ldow = (fy + year_data[m_] + 1) % 7;
          d = n_days_in_month;
          if (dow_ < ldow)
            d -= ldow - dow_;
          else if (dow_ > ldow)
            d -= 7 - (dow_ - ldow);
        } else
        {
          int fdow = (fy + year_data[m_ - 1] + 2) % 7;
          d = 1 + (n_ - 1) * 7;
          if (dow_ < fdow)
            d += 7 - (fdow - dow_);
          else if (dow_ > fdow)
            d += dow_ - fdow;
          if (d > n_days_in_month)
            throw bad_date("day " + boost::chrono::to_string(d) + " is out of range for "
                + boost::chrono::to_string(y_) + '-' + boost::chrono::to_string(m_));
        }
        d_ = d;
        x_ = fy + year_data[m_ - 1] + d_;
        return;
      }
    }
    if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
      throw bad_date("day " + boost::chrono::to_string(d) + " is out of range for "
          + boost::chrono::to_string(y_) + '-' + boost::chrono::to_string(m_));
    int32_t by = y.y_ + 32799;
    x_ = by * 365 + by / 4 + year_data[m_ - 1] + d_;
  }

  date&
  date::operator+=(days d)
  {
    x_ += d.x_;
    if (!(11322 <= x_ && x_ <= 23947853))
      throw bad_date("year is out of range [-32768, 32767]");
    int y = static_cast<int> (static_cast<int64_t> (x_ + 1) * 4 / 1461);
    int doy = x_ - (y * 365 + y / 4);
    if (doy < 0)
    {
      --y;
      doy = x_ - (y * 365 + y / 4);
    }
    y_ = static_cast<int16_t> (y - 32799);
    leap_ = is_leap(y_);
    int* year_data = db[leap_];
    m_
        = static_cast<uint16_t> (std::lower_bound(year_data, year_data + 13, doy)
            - year_data);
    d_ = static_cast<uint16_t> (doy - year_data[m_ - 1]);
    n_ = 7;
    dow_ = 7;
    return *this;
  }

  date&
  date::operator+=(months mn)
  {
    int32_t y = y_;
    int32_t m = m_;
    m += mn.x_;
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
    *this = julian::day(d_, n_, dow_) / m / y;
    return *this;
  }

  date&
  date::operator+=(years yr)
  {
    *this = julian::day(d_, n_, dow_) / m_ / (y_ + yr.x_);
    return *this;
  }

} // julian
