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
#include <boost/chrono/date/date_generators.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date()
    BOOST_NOEXCEPT
    : x_(11979588),
    y_(0),
    m_(1),
    leap_(1),
    dow_(weekday::not_applicable),
    d_(1),
    n_(nth_week::not_applicable)
    {
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date()
    BOOST_NOEXCEPT
    : x_(11979588),
    n_(nth_week::not_applicable),
    dow_(weekday::not_applicable)
    {
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date() BOOST_NOEXCEPT
    : y_(0),
    m_(1),
    leap_(1),
    dow_(weekday::not_applicable),
    d_(1),
    n_(nth_week::not_applicable)
    {
    }

#endif
#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::day d)
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(d),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return throw bad_date("");
      }
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::day d)
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);
      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return throw bad_date("");
      }
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::day d)
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(d),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(d <= year_data[m] - year_data[m - 1]))
      {
        return throw bad_date("bbbbbbbbbbbb");
      }

    }
#endif
#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year::rep y, chrono::month::rep m, chrono::day::rep d, no_check_t) BOOST_NOEXCEPT
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(d),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year::rep y, chrono::month::rep m, chrono::day::rep d, no_check_t)BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[m - 1] + d;
    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year::rep y, chrono::month::rep m, chrono::day::rep d, no_check_t)BOOST_NOEXCEPT
    :
    y_(y),
    m_(m),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(d),
    n_(nth_week::not_applicable)
    {
    }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year y, chrono::month_day md)
    :
    y_(y),
    m_(md.get_month()),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(md.get_day()),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(md.get_day() <= year_data[md.get_month()] - year_data[md.get_month() - 1]))
      {
        return throw bad_date("");
      }
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + year_data[md.get_month() - 1] + md.get_day();
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year y, chrono::month_day md)
    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);
      if (!(md.get_day() <= year_data[md.get_month()] - year_data[md.get_month() - 1]))
      {
        return throw bad_date("");
      }
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[md.get_month() - 1] + md.get_day();
    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year y, chrono::month_day md)
    :
    y_(y),
    m_(md.get_month()),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(md.get_day()),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (!(d_ <= year_data[m_] - year_data[m_ - 1]))
      {
        return throw bad_date("");
      }

    }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year::rep y, chrono::month_day md, no_check_t)
    BOOST_NOEXCEPT    :
    y_(y),
    m_(md.get_month()),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(md.get_day()),
    n_(nth_week::not_applicable)
    {
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[md.get_month() - 1] + md.get_day();
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year::rep y, chrono::month_day md, no_check_t)
    BOOST_NOEXCEPT    {
      bool leap = is_leap(y);
      const day_of_year::rep* year_data = days_in_year_before(leap);
      year::rep by = y + 32799;
      x_ = days_before_year(by) + year_data[md.get_month() - 1] + md.get_day();
    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year::rep y, chrono::month_day md, no_check_t)
    BOOST_NOEXCEPT    :
    y_(y),
    m_(md.get_month()),
    leap_(is_leap(y)),
    dow_(weekday::not_applicable),
    d_(md.get_day()),
    n_(nth_week::not_applicable)
    {
    }
#endif

    rel_date::rel_date(chrono::days d)
    {
      if (set_if_valid_date(d))
        return;
      throw bad_date("days " + to_string(d.count()) + " is out of range");
    }


    rel_date::rel_date(chrono::year y, chrono::day_of_year doy)
    {
      if (set_if_valid_date(y, doy))
        return;
      throw bad_date("doy " + to_string(doy) + " is out of range for year "
          + to_string(y) );
    }

//#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1
//
//    rel_date::rel_date(year::rep y, day_of_year::rep d, no_check_t) // TODO
//    BOOST_NOEXCEPT
//    {
//
//    }
//
//
//
//#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
//
//    rel_date::rel_date(year::rep y, day_of_year::rep d, no_check_t)// TODO
//    BOOST_NOEXCEPT
//    {
//
//    }
//
//
//#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
//
//    rel_date::rel_date(year::rep y, day_of_year::rep d, no_check_t)// TODO
//    BOOST_NOEXCEPT
//    {
//
//    }
//
//
//#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    bool rel_date::set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT
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
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;
    }


#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    bool rel_date::set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y.value());
      const day_of_year::rep* year_data = days_in_year_before(leap);

      if (!(d.value() <= year_data[m.value()] - year_data[m.value()-1]))
      {
        return false;
      }
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + year_data[m.value()-1] + d.value();
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    bool rel_date::set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT
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
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;
    }

#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    bool rel_date::set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT

    {
      bool leap = is_leap(y);
      if (!leap && doy == 366)
         return false;

      y_ = y.value();
      m_ = day_of_year_month(leap,doy);
      d_ = day_of_year_day_of_month(leap,doy);
      leap_ = leap;
      year::rep by = y.value() + 32799;
      x_ = days_before_year(by) + doy -1;
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;
    }


#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    bool rel_date::set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT// TODO
    {
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return false;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    bool rel_date::set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT
    {
      bool leap = is_leap(y);
      if (!leap && doy == 366)
         return false;

      y_ = y.value();
      m_ = day_of_year_month(leap,doy);
      d_ = day_of_year_day_of_month(leap,doy);
      leap_ = leap;
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;
    }

#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    bool rel_date::set_if_valid_date(days x) BOOST_NOEXCEPT
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
      x_=x.count();
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;

    }


#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    bool rel_date::set_if_valid_date(days x) BOOST_NOEXCEPT// TODO
    {
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return false;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    bool rel_date::set_if_valid_date(days x) BOOST_NOEXCEPT
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
      dow_=weekday::not_applicable;
      n_=nth_week::not_applicable;
      return true;

    }

#endif



#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    bool rel_date::is_valid() const BOOST_NOEXCEPT
    {
      return x_ >= 11322 && x_ <= 23947853;

    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    bool rel_date::is_valid() const
    BOOST_NOEXCEPT
    {
      return x_ >= 11322 && x_ <= 23947853;

    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    bool rel_date::is_valid() const BOOST_NOEXCEPT
    {
      if (year(y_,no_check).is_valid() && month(m_,no_check).is_valid())
      {
        if (d_!=0 && day(d_, no_check).is_valid()) {
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
#endif

    rel_date
    rel_date::today()
    BOOST_NOEXCEPT
    {
      time_t systime;
      time(&systime);
      tm now;
      localtime_r(&systime, &now);
      return rel_date(chrono::year(now.tm_year+1900,no_check),
          chrono::month(now.tm_mon+1,no_check),
          chrono::day(now.tm_mday,no_check));
    }

    rel_date::rel_date(boost::chrono::system_clock::time_point tp)
    {
      time_t systime = boost::chrono::system_clock::to_time_t(tp);
      tm now;
      gmtime_r(&systime, &now);
      *this
          = rel_date(chrono::year(now.tm_year + 1900, no_check), chrono::month(now.tm_mon
              + 1, no_check), chrono::day(now.tm_mday, no_check));
    }

    rel_date::operator boost::chrono::system_clock::time_point() const
    {
      tm now =
      { 0 };
      now.tm_year = get_year() - 1900;
      now.tm_mon = get_month() - 1;
      now.tm_mday = get_day();
      time_t t = timegm(&now);
      return boost::chrono::system_clock::from_time_t(t);
    }

#endif //BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1
//    rel_date::rel_date(ymd_date dt) :
//    x_(dt.days_since_epoch().count()),
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ymd_date() const
    {
      return date(x_, y_, m_, d_, leap_, no_check);
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

//    rel_date::rel_date(ymd_date dt) :
//      x_(dt.days_since_epoch().count())
//    {
//
//    }
    rel_date::operator ymd_date() const
    {
      return date(x_, no_check);

    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

//    rel_date::rel_date(ymd_date dt) :
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ymd_date() const
    {
      return date(y_,m_,d_,leap_,no_check);

    }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

//    rel_date::rel_date(days_date dt) :
//    x_(dt.days_since_epoch().count()),
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator days_date() const
    {
      return date(x_, no_check);
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

//    rel_date::rel_date(days_date dt) :
//      x_(dt.days_since_epoch().count())
//    {
//
//    }
    rel_date::operator days_date() const
    {
      return date(x_, no_check);

    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

//    rel_date::rel_date(days_date dt) :
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator days_date() const
    {
      return date(y_,m_,d_,leap_,no_check);

    }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

//    rel_date::rel_date(ydoy_date dt) :
//    x_(dt.days_since_epoch().count()),
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ydoy_date() const
    {
      return date(x_, y_, m_, d_, leap_, no_check);
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

//    rel_date::rel_date(ydoy_date dt) :
//      x_(dt.days_since_epoch().count())
//    {
//
//    }
    rel_date::operator ydoy_date() const
    {
      return date(x_, no_check);

    }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

//    rel_date::rel_date(ydoy_date dt) :
//    y_(dt.get_year().value()),
//    m_(dt.get_month().value()),
//    leap_(dt.is_leap_year()),
//    dow_(weekday::not_applicable),
//    d_(dt.get_day().value()),
//    n_(nth_week::not_applicable)
//    {
//
//    }
    rel_date::operator ydoy_date() const
    {
      return date(y_,m_,d_,leap_,no_check);

    }
#endif
#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth_weekday d) :
    y_(y.value()),
    m_(m.value()),
    dow_(d.get_weekday()),
    d_(0),
    n_(d.get_nth())
    {
      leap_ = year(y_).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (n_ != nth_week::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          if (n_ == 6) // want last day of month

          {
            d_ = year_data[m_] - year_data[m_ - 1];
          }
          else
          {
            d_ = n_; // want nth day of month
          }
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by * 365 + by / 4 - by / 100 + by / 400;
          int n_days_in_month = year_data[m_] - year_data[m_ - 1];
          int d;
          if (n_ == 6)
          {
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
          }
          else
          {
            int fdow = (fy + year_data[m_ - 1] + 2) % weekday::size;
            d = 1 + (n_ - 1) * weekday::size;
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
              throw bad_date("day " + to_string(d) + " is out of range for "
                  + to_string(y_) + '-' + to_string(m_));
            }
          }
          d_ = d;
          x_ = fy + year_data[m_ - 1] + d_;
          return;
        }
      }
      if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
      {
        throw bad_date("day " + to_string(d_) + " is out of range for "
            + to_string(y_) + '-' + to_string(m_));
      }
      int32_t by = y.value() + 32799;
      x_ = by * 365 + by / 4 - by / 100 + by / 400 + year_data[m_ - 1] + d_;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth_weekday nwd) :
      n_(nwd.get_nth()), dow_(nwd.get_weekday())
    {
      bool leap = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);
      if (n_ != nth_week::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          int d;
          if (n_ == 6) // want last day of month

          {
            d = year_data[m.value()] - year_data[m.value() - 1];
          }
          else
          {
            d = n_; // want nth day of month
          }
          if (!(1 <= d && d <= year_data[m.value()] - year_data[m.value() - 1]))
          {
            throw bad_date("day " + to_string(d) + " is out of range for "
                + to_string(y.value()) + '-' + to_string(m.value()));
          }
          int32_t by = y.value() + 32799;
          x_ = by * 365 + by / 4 - by / 100 + by / 400 + year_data[m.value()
              - 1] + d;
          return;
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by * 365 + by / 4 - by / 100 + by / 400;
          int n_days_in_month = year_data[m.value()] - year_data[m.value() - 1];
          int d;
          if (n_ == 6)
          {
            int ldow = (fy + year_data[m.value()] + 1) % weekday::size;
            d = n_days_in_month;
            if (dow_ < ldow)
            {
              d -= ldow - dow_;
            }
            else if (dow_ > ldow)
            {
              d -= weekday::size - (dow_ - ldow);
            }
          }
          else
          {
            int fdow = (fy + year_data[m.value() - 1] + 2) % weekday::size;
            d = 1 + (n_ - 1) * weekday::size;
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
              throw bad_date("day " + to_string(d) + " is out of range for "
                  + to_string(y.value()) + '-' + to_string(m.value()));
            }
          }
          x_ = fy + year_data[m.value() - 1] + d;
          return;
        }
      }
      //      if (!(1 <= d.d_ && d.d_ <= year_data[m.value()] - year_data[m.value()-1]))
      //      {
      //        throw bad_date("day " + to_string(d.d_) +
      //            " is out of range for " + to_string(y.value()) +
      //            '-' + to_string(m.value()));
      //      }
      //      int32_t by = y.value() + 32799;
      //      x_ = by*365 + by/4 - by/100 + by/400 + year_data[m.value()-1] + d.d_;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth_weekday rd)
    : y_(y.value()),
    m_(m.value()),
    leap_(0),
    dow_(rd.get_weekday()),
    //d_(rd.d_),
    d_(0),
    n_(rd.get_nth())
    {
      std::cout <<" =========== d= "<< int(d_) << std::endl;

      leap_ = year(y,no_check).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (n_ != nth_week::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          if (n_ == 6) // want last day of month

          {
            d_ = year_data[m_] - year_data[m_-1];
            std::cout <<"  =========== d= "<< int(d_) << std::endl;
          }
          else
          {
            d_ = n_; // want nth day of month
            std::cout <<"   =========== d= "<< int(d_) << std::endl;
          }
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by*365 + by/4 - by/100 + by/400;
          int n_days_in_month = year_data[m_] - year_data[m_-1];
          int d;
          if (n_ == 6)
          {
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
          }
          else
          {
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
          }
          d_ = d;
          std::cout <<"    =========== d= "<< int(d_) << std::endl;
        }
      }
      if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_-1]))
      {
        std::cout <<"===== ====== d= "<< int(d_) << std::endl;
        throw bad_date("day " + to_string(int(d_)) +
            " is out of range for " + to_string(y_) +
            '-' + to_string(int(m_)));
      }
    }

#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth n) :
    y_(y.value()),
    m_(m.value()),
    dow_(weekday::not_applicable),
    d_(0),
    n_(n.value())
    {
      leap_ = year(y_).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (n_ != nth::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          if (n_ == 6) // want last day of month

          {
            d_ = year_data[m_] - year_data[m_ - 1];
          }
          else
          {
            d_ = n_; // want nth day of month
          }
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by * 365 + by / 4 - by / 100 + by / 400;
          int n_days_in_month = year_data[m_] - year_data[m_ - 1];
          int d;
          if (n_ == 6)
          {
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
          }
          else
          {
            int fdow = (fy + year_data[m_ - 1] + 2) % weekday::size;
            d = 1 + (n_ - 1) * weekday::size;
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
              throw bad_date("day " + to_string(d) + " is out of range for "
                  + to_string(y_) + '-' + to_string(m_));
            }
          }
          d_ = d;
          x_ = fy + year_data[m_ - 1] + d_;
          return;
        }
      }
      if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_ - 1]))
      {
        throw bad_date("day " + to_string(d_) + " is out of range for "
            + to_string(y_) + '-' + to_string(m_));
      }
      int32_t by = y.value() + 32799;
      x_ = by * 365 + by / 4 - by / 100 + by / 400 + year_data[m_ - 1] + d_;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth n) :
      n_(n.value()), dow_(weekday::not_applicable)
    {
      bool leap = y.is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);
      if (n_ != nth::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          int d;
          if (n_ == 6) // want last day of month

          {
            d = year_data[m.value()] - year_data[m.value() - 1];
          }
          else
          {
            d = n_; // want nth day of month
          }
          if (!(1 <= d && d <= year_data[m.value()] - year_data[m.value() - 1]))
          {
            throw bad_date("day " + to_string(d) + " is out of range for "
                + to_string(y.value()) + '-' + to_string(m.value()));
          }
          int32_t by = y.value() + 32799;
          x_ = by * 365 + by / 4 - by / 100 + by / 400 + year_data[m.value()
              - 1] + d;
          return;
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by * 365 + by / 4 - by / 100 + by / 400;
          int n_days_in_month = year_data[m.value()] - year_data[m.value() - 1];
          int d;
          if (n_ == 6)
          {
            int ldow = (fy + year_data[m.value()] + 1) % weekday::size;
            d = n_days_in_month;
            if (dow_ < ldow)
            {
              d -= ldow - dow_;
            }
            else if (dow_ > ldow)
            {
              d -= weekday::size - (dow_ - ldow);
            }
          }
          else
          {
            int fdow = (fy + year_data[m.value() - 1] + 2) % weekday::size;
            d = 1 + (n_ - 1) * weekday::size;
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
              throw bad_date("day " + to_string(d) + " is out of range for "
                  + to_string(y.value()) + '-' + to_string(m.value()));
            }
          }
          x_ = fy + year_data[m.value() - 1] + d;
          return;
        }
      }
      //      if (!(1 <= d.d_ && d.d_ <= year_data[m.value()] - year_data[m.value()-1]))
      //      {
      //        throw bad_date("day " + to_string(d.d_) +
      //            " is out of range for " + to_string(y.value()) +
      //            '-' + to_string(m.value()));
      //      }
      //      int32_t by = y.value() + 32799;
      //      x_ = by*365 + by/4 - by/100 + by/400 + year_data[m.value()-1] + d.d_;
    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    rel_date::rel_date(chrono::year y, chrono::month m, chrono::nth n)
    : y_(y.value()),
    m_(m.value()),
    leap_(0),
    dow_(weekday::not_applicable),
    //d_(rd.d_),
    d_(0),
    n_(n.value())
    {
      leap_ = year(y,no_check).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      if (n_ != nth::not_applicable) // if a nth is involved

      {
        if (dow_ == weekday::not_applicable) // if we want nth day of month

        {
          if (n_ == 6) // want last day of month

          {
            d_ = year_data[m_] - year_data[m_-1];
          }
          else
          {
            d_ = n_; // want nth day of month
          }
        }
        else // we want nth weekday of month

        {
          // dow_ = [0 - 6]
          // n_ = [1 - 6] 6 means last
          int32_t by = y.value() + 32799;
          int32_t fy = by*365 + by/4 - by/100 + by/400;
          int n_days_in_month = year_data[m_] - year_data[m_-1];
          int d;
          if (n_ == 6)
          {
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
          }
          else
          {
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
          }
          d_ = d;
        }
      }
      if (!(1 <= d_ && d_ <= year_data[m_] - year_data[m_-1]))
      {
        throw bad_date("day " + to_string(int(d_)) +
            " is out of range for " + to_string(y_) +
            '-' + to_string(int(m_)));
      }
    }

#endif

//#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1
//
//    rel_date&
//    rel_date::operator+=(days d)
//    {
//      x_ += d.count();
//      if (!(11322 <= x_ && x_ <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//      year::rep y = to_average_year(x_);
//      int doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
//      if (doy < 0)
//      {
//        --y;
//        doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
//      }
//      y_ = static_cast<int16_t> (y - 32799);
//      leap_ = year(y, no_check).is_leap();
//      const day_of_year::rep* year_data = days_in_year_before(leap_);
//      m_ = static_cast<uint16_t> (std::lower_bound(year_data, year_data + 13, doy)
//          - year_data);
//      d_ = static_cast<uint16_t> (doy - year_data[m_ - 1]);
//      n_ = nth_week::not_applicable;
//      dow_ = weekday::not_applicable;
//      return *this;
//    }
//
//#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
//
//    rel_date&
//    rel_date::operator+=(days d)
//    {
//      x_ += d.count();
//      if (!(11322 <= x_ && x_ <= 23947853))
//      {
//        throw bad_date("year is out of range [-32768, 32767]");
//      }
//      n_ = nth_week::not_applicable;
//      dow_ = weekday::not_applicable;
//      return *this;
//    }
//
//#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
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
//      n_ = nth_week::not_applicable;
//      dow_ = weekday::not_applicable;
//      return *this;
//    }
//
//#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

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
      //if (d_==0)
        *this = chrono::nth_weekday(nth_week(n_,no_check), weekday(dow_,no_check)) / chrono::month(m, no_check) / y;
      //else
        //*this = rel_date(year(y), chrono::month(m, no_check), chrono::day(d_,no_check));
      return *this;
    }

    rel_date&
    rel_date::operator+=(years yr)
    {
      //if (d_==0)
        *this = chrono::nth_weekday(nth_week(n_,no_check), weekday(dow_,no_check)) / chrono::month(m_, no_check) / (y_ + yr.count());
      //else
        //*this = rel_date(year(y_+ yr.count()), chrono::month(m_, no_check), chrono::day(d_,no_check));
      return *this;

    }

#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    rel_date&
    rel_date::operator+=(months mn)
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
      }
      y -= 32799;
      bool leap = year(y).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);
      int m = std::lower_bound(year_data, year_data + 13, doy) - year_data;
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
      *this = chrono::nth_weekday(nth_week(n_), weekday(dow_, no_check))
          / chrono::month(m, no_check) / y;
      return *this;
    }

    rel_date&
    rel_date::operator+=(years yr)
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y * 365 + y / 4 - y / 100 + y / 400);
      }
      y -= 32799;
      bool leap = year(y).is_leap();
      const day_of_year::rep* year_data = days_in_year_before(leap);
      int m = std::lower_bound(year_data, year_data + 13, doy) - year_data;
      *this = chrono::nth_weekday(nth_week(n_), weekday(dow_, no_check))
          / chrono::month(m, no_check) / (y + yr.count());
      return *this;
    }

#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2

    uint16_t
    rel_date::day_from_day_number() const
    BOOST_NOEXCEPT
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y*365 + y/4 - y/100 + y/400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y*365 + y/4 - y/100 + y/400);
      }
      y -= 32799;
      const day_of_year::rep* year_data = days_in_year_before(year(y).is_leap());
      int m = std::lower_bound(year_data, year_data+13, doy) - year_data;
      return static_cast<uint16_t>(doy - year_data[m-1]);
    }

    uint16_t
    rel_date::month_from_day_number() const
    BOOST_NOEXCEPT
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y*365 + y/4 - y/100 + y/400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y*365 + y/4 - y/100 + y/400);
      }
      y -= 32799;
      const day_of_year::rep* year_data = days_in_year_before(year(y).is_leap());
      return std::lower_bound(year_data, year_data+13, doy) - year_data;
    }

    int16_t
    rel_date::year_from_day_number() const
    BOOST_NOEXCEPT
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y*365 + y/4 - y/100 + y/400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y*365 + y/4 - y/100 + y/400);
      }
      y -= 32799;
      return static_cast<int16_t>(y);
    }

    bool
    rel_date::leap_from_day_number() const
    BOOST_NOEXCEPT
    {
      year::rep y = to_average_year(x_);
      int doy = x_ - (y*365 + y/4 - y/100 + y/400);
      if (doy < 0)
      {
        --y;
        doy = x_ - (y*365 + y/4 - y/100 + y/400);
      }
      y -= 32799;
      return year(y).is_leap();
    }

#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3

    uint32_t
    rel_date::day_number_from_ymd() const BOOST_NOEXCEPT
    {
      uint32_t by = y_ + 32799;
      const day_of_year::rep* year_data = days_in_year_before(leap_);
      return by*365 + by/4 - by/100 + by/400 + year_data[m_-1] + d_;
    }

#endif

    year_month_day to_ymd(year_week_weekday p)
    BOOST_NOEXCEPT
    {
      date dt = (mon <= jan / day(4,no_check) / p.get_year()) + days((p.get_week().value() - 1) * weekday::size + (p.get_weekday().value() == 0 ? weekday::size-1 : p.get_weekday().value() - 1));
      return year_month_day(dt.get_year(), dt.get_month(), dt.get_day(), no_check);
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
      date dt(ymd.get_year(), ymd.get_month(), ymd.get_day(), no_check);
      month_day jan4 = jan / day(4);
      date start = mon <= jan4 / ymd.get_year();
      if (dt < start)
      {
        start = mon <= jan4 / (ymd.get_year() - 1);
      }
      else
      {
        date next_start = mon <= jan4 / (start.get_year() + 1);
        if (dt >= next_start)
        start = next_start;
      }
      return year_week_weekday(
          (thu > start).get_year(),
          (dt - start).count() / weekday::size + 1,
          dt.get_weekday(),
          no_check
      );
    }

    year_week_weekday to_ywwd(year_day_of_year dt)
    BOOST_NOEXCEPT
    {
      return to_ywwd(to_ymd(dt));

    }

    year_week_weekday to_ywwd(days dt)
BOOST_NOEXCEPT  {
    return to_ywwd(to_ymd(dt));

  }

} // chrono
} // boost


