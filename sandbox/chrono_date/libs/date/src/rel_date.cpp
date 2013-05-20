//  date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <algorithm>
#include <ctime>
#include <string>
#include <boost/chrono/date/date_generators.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    namespace detail {
      struct weekday
      {
            BOOST_STATIC_CONSTEXPR int not_applicable=7;
      };
      struct nth_week
      {
        BOOST_STATIC_CONSTEXPR int not_applicable=7;
      };
    }

    rel_date::rel_date() BOOST_NOEXCEPT
    : y_(0),
    m_(1),
    leap_(1),
    dow_(detail::weekday::not_applicable),
    d_(1),
    n_(detail::nth_week::not_applicable)
    {
    }

#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

    rel_date::rel_date(chrono::year y, chrono::month m, day d)
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(detail::weekday::not_applicable),
    d_(d),
    n_(detail::nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return throw bad_date("bbbbbbbbbbbb");
      }

    }

    rel_date::rel_date(chrono::year y, chrono::month m, day d)BOOST_NOEXCEPT
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(detail::weekday::not_applicable),
    d_(d),
    n_(detail::nth_week::not_applicable)
    {
    }

    rel_date::rel_date(chrono::year y, chrono::month_day md, check_t)
    :
    y_(y),
    m_(month(md)),
    leap_(is_leap(y)),
    dow_(detail::weekday::not_applicable),
    d_(day(md)),
    n_(detail::nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(d_ <= year_data[m_] - year_data[m_ - 1]))
      {
        return throw bad_date("");
      }

    }

    rel_date::rel_date(year::rep y, chrono::month_day md)
    BOOST_NOEXCEPT    :
    y_(y),
    m_(month(md)),
    leap_(is_leap(y)),
    dow_(detail::weekday::not_applicable),
    d_(day(md)),
    n_(detail::nth_week::not_applicable)
    {
    }

    rel_date::rel_date(days d)
    {
      if (set_if_valid_date(d))
        return;
      throw bad_date("days " + to_string(d.count()) + " is out of range");
    }


    rel_date::rel_date(chrono::year y, day_of_year doy)
    {
      if (set_if_valid_date(y, doy))
        return;
      throw bad_date("doy " + to_string(doy) + " is out of range for year "
          + to_string(y) );
    }


//
//    rel_date::rel_date(year::rep y, day_of_year::rep d)// TODO
//    BOOST_NOEXCEPT
//    {
//
//    }
//
//

    bool rel_date::set_if_valid_date(chrono::year y, chrono::month m, day d) BOOST_NOEXCEPT
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
      dow_=detail::weekday::not_applicable;
      n_=detail::nth_week::not_applicable;
      return true;
    }

    bool rel_date::set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      if (!leap && doy == 366)
         return false;

      y_ = y.value();
      m_ = day_of_year_month(leap,doy);
      d_ = day_of_year_day_of_month(leap,doy);
      leap_ = leap;
      dow_=detail::weekday::not_applicable;
      n_=detail::nth_week::not_applicable;
      return true;
    }

    bool rel_date::set_if_valid_date(days x) BOOST_NOEXCEPT
    {
      if (!(11322 <= x.count() && x.count() <= 23947853))
      {
        return false;
      }
      year_month_day_leap dt = to_ymd_leap(x);
      y_=year(dt);
      m_=month(dt);
      d_=day(dt);
      leap_=dt.is_leap_year();
      dow_=detail::weekday::not_applicable;
      n_=detail::nth_week::not_applicable;
      return true;

    }

    bool rel_date::is_valid() const BOOST_NOEXCEPT
    {
      if (chrono::year(y_).is_valid() && chrono::month(m_).is_valid())
      {
        if (d_!=0 && day(d_).is_valid()) {
          const day_of_year::rep* year_data = days_in_year_before(leap_);

          if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
          {
            return false;
          }
          else
          {
            return true;
          }
        } else return true;
      }
      return false;

    }

    rel_date
    rel_date::today()
    BOOST_NOEXCEPT
    {
      time_t systime;
      time(&systime);
      tm now;
      localtime_r(&systime, &now);
      return rel_date(chrono::year(now.tm_year+1900),
          chrono::month(now.tm_mon+1),
          chrono::day(now.tm_mday));
    }

    rel_date::rel_date(system_clock::time_point tp)
    {
      time_t systime = system_clock::to_time_t(tp);
      tm now;
      gmtime_r(&systime, &now);
      *this
          = rel_date(chrono::year(now.tm_year + 1900), chrono::month(now.tm_mon
              + 1), chrono::day(now.tm_mday));
    }

    rel_date::operator system_clock::time_point() const
    {
      tm now =
      { 0 };
      now.tm_year = year() - 1900;
      now.tm_mon = month() - 1;
      now.tm_mday = day();
      time_t t = timegm(&now);
      return system_clock::from_time_t(t);
    }

#endif //BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

//    rel_date::rel_date(ymd_date dt) :
//    y_(year(dt).value()),
//    m_(month(dt).value()),
//    leap_(dt.is_leap_year()),
//    dow_(detail::weekday::not_applicable),
//    d_(day(dt).value()),
//    n_(detail::nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ymd_date() const
    {
      return ymd_date(y_,m_,d_,leap_);

    }

//    rel_date::rel_date(days_date dt) :
//    y_(year(dt).value()),
//    m_(month(dt).value()),
//    leap_(dt.is_leap_year()),
//    dow_(detail::weekday::not_applicable),
//    d_(day(dt).value()),
//    n_(detail::nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator days_date() const
    {
      // @todo improve this
      return days_date(ymd_date(y_,m_,d_,leap_));

    }

//    rel_date::rel_date(ydoy_date dt) :
//    y_(year(dt).value()),
//    m_(month(dt).value()),
//    leap_(dt.is_leap_year()),
//    dow_(detail::weekday::not_applicable),
//    d_(day(dt).value()),
//    n_(detail::nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ydoy_date() const
    {
      // @todo improve this
      return ydoy_date(ymd_date(y_,m_,d_,leap_));

    }

    rel_date::rel_date(chrono::year y, chrono::month m, nth_weekday rd)
    : y_(y.value()),
    m_(m.value()),
    leap_(0),
    dow_(weekday(rd)),
    //d_(rd.d_),
    d_(0),
    n_(nth_week(rd))
    {
      leap_ = chrono::year(y).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      {

        // dow_ = [0 - 5] 0 means last
        // n_ = [0 - 5] 0 means last
        int32_t by = y.value() + 32799;
        int32_t fy = by*365 + by/4 - by/100 + by/400;
        int n_days_in_month = year_data[m_] - year_data[m_-1];
        int d;
        int fdow = (fy + year_data[m_-1] + 2) % weekday::size;
        d = 1 + (n_-1) * weekday::size;
        if (dow_ < fdow)
        {
          d += weekday::size - (fdow - dow_);
        }
        else if (dow_ > fdow)
        {
          d += dow_ - fdow;
        }
        if (d > n_days_in_month)
        {
          throw bad_date("day " + to_string(int(d)) +
              " is out of range for " + to_string(y_) +
              '-' + to_string(int(m_)));
        }
        d_ = d;
      }
    }

    rel_date::rel_date(chrono::year y, chrono::month m, last_weekday rd)
    : y_(y.value()),
    m_(m.value()),
    leap_(0),
    dow_(weekday(rd)),
    //d_(rd.d_),
    d_(0),
    n_(0)
    {
      leap_ = chrono::year(y).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      // dow_ = [0 - 5] 0 means last
      // n_ = [0 - 5] 0 means last
      int32_t by = y.value() + 32799;
      int32_t fy = by*365 + by/4 - by/100 + by/400;
      int n_days_in_month = year_data[m_] - year_data[m_-1];
      int d;

      int ldow = (fy + year_data[m_] + 1) % weekday::size;
      d = n_days_in_month;
      if (dow_ < ldow)
      {
        d -= ldow - dow_;
      }
      else if (dow_ > ldow)
      {
        d -= weekday::size - (dow_ - ldow);
      }
      d_ = d;
    }

    rel_date::rel_date(chrono::year y, chrono::month m, last_tag)
    : y_(y.value()),
    m_(m.value()),
    leap_(0),
    dow_(detail::weekday::not_applicable),
    d_(0),
    n_(0)
    {
      leap_ = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      d_ = year_data[m_] - year_data[m_-1];
    }


//
//    rel_date&
//    rel_date::operator+=(days d)
//    {
//      uint32_t x = day_number_from_ymd() + d.count();
//      if (!(11322 <= x && x <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//
//      year::rep y = to_average_year(x);
//      int doy = x - (y*365 + y/4 - y/100 + y/400);
//      if (doy < 0)
//      {
//        --y;
//        doy = x - (y*365 + y/4 - y/100 + y/400);
//      }
//      y_ = static_cast<int16_t>(y - 32799);
//      leap_ = year(y_).is_leap();
//      const day_of_year::rep* year_data = days_in_year_before(leap_);
//      m_ = static_cast<uint16_t>(std::lower_bound(year_data, year_data+13, doy)
//          - year_data);
//      d_ = static_cast<uint16_t>(doy - year_data[m_-1]);
//
//
//      n_ = detail::nth_week::not_applicable;
//      dow_ = detail::weekday::not_applicable;
//      return *this;
//    }
//

    rel_date&
    rel_date::operator+=(months mn)
    {
      int32_t y = y_;
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

      if (dow_==detail::weekday::not_applicable)
        *this = last/chrono::month(m)/y;
      else if (n_==0)
        *this = last_weekday(chrono::weekday(dow_)) / chrono::month(m) / y;
      else
        *this = nth_weekday(nth_week(n_), chrono::weekday(dow_)) / chrono::month(m) / y;
      return *this;
    }

    rel_date&
    rel_date::operator+=(years yr)
    {
      //if (d_==0)
        *this = nth_weekday(nth_week(n_), chrono::weekday(dow_)) / chrono::month(m_) / (y_ + yr.count());
      //else
        //*this = rel_date(year(y_+ yr.count()), chrono::month(m_), day(d_));
      return *this;

    }

    uint32_t
    rel_date::day_number_from_ymd() const BOOST_NOEXCEPT
    {
      uint32_t by = y_ + 32799;
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      return by*365 + by/4 - by/100 + by/400 + year_data[m_-1] + d_;
    }

    year_month_day to_ymd(year_week_weekday p)
    BOOST_NOEXCEPT
    {
      return to_ymd(
          (  (mon <= jan / day(4, no_check) / year(p))
           + days(
                  (week(p) - 1) * weekday::size + (weekday(p) == 0 ? weekday::size-1 : weekday(p) - 1)
             )
          ).days_since_epoch()
      );
    }

    year_day_of_year to_ydoy(year_week_weekday dt)
    BOOST_NOEXCEPT
    {
      return to_ydoy(to_ymd(dt));
    }

    days to_days(year_week_weekday dt)
    BOOST_NOEXCEPT
    {
      return to_days(to_ymd(dt));
    }

    year_week_weekday to_ywwd(year_month_day ymd)
    BOOST_NOEXCEPT
    {
      days_date dt(month(ymd)/day(ymd)/year(ymd));
      chrono::month_day jan4 = jan / day(4, no_check);
      days_date jan4_y(jan4 / year(ymd));
      days_date jan4_y_m_1(jan4 / (year(ymd)-1));
      days_date jan4_y_p_1(jan4 / (year(ymd)+1));
      // @todo improve the jan4 / year(ymd) conversion
      days_date start = mon <= jan4_y;
      if (dt < start)
      {
        // @todo improve the jan4 / year(ymd) conversion
        start = mon <= jan4_y_m_1;
      }
      else
      {
        days_date next_start = mon <= jan4_y_p_1;
        if (dt >= next_start)
        start = next_start;
      }
      return year_week_weekday(
          (thu > start).to_year(),
          week((dt - start).count() / weekday::size + 1),
          weekday(dt)
      );
    }

    year_week_weekday to_ywwd(year_day_of_year dt)
    BOOST_NOEXCEPT
    {
      return to_ywwd(to_ymd(dt));

    }

    year_week_weekday to_ywwd(days dt) BOOST_NOEXCEPT
    {
      return to_ywwd(to_ymd(dt));
    }

} // chrono
} // boost


