//  rel_date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_RELATIVE_DATE_HPP
#define BOOST_CHRONO_DATE_RELATIVE_DATE_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/nth_weekday.hpp>
#include <boost/chrono/date/month_nth_weekday.hpp>
#include <boost/chrono/date/month_nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/nth_tag.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/is_date.hpp>

namespace boost
{
  namespace chrono
  {


    /**
     * The class @c rel_date is a model of Date storing
     * - the @c year,
     * - the @c month,
     * - the @c day of the month
     * and optionally
     * - the number of @c days since an undetermined epoch.
     * - whether the year is leap or not.
     */
    class rel_date
    {

      // Store y/m/d, n, dow. Total 32 bits
      int_least16_t y_;
      uint_least8_t m_    : 4;
      uint_least8_t leap_ : 1;
      uint_least8_t dow_  : 3;
      uint_least8_t d_    : 5;
      uint_least8_t n_    : 3;

    public:

      /**
       * Effects: Constructs a @c rel_date as if by @c year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of @c rel_date valid construction when the specific value for that @c days_date is unimportant.
       */
      rel_date() BOOST_NOEXCEPT;
      rel_date(chrono::year, chrono::month, nth_weekday);
      rel_date(chrono::year, chrono::month, nth_weekday, check_t) BOOST_NOEXCEPT;
      rel_date(chrono::year, chrono::month, last_weekday);
      rel_date(chrono::year, chrono::month, last_weekday, check_t) BOOST_NOEXCEPT;
      rel_date(chrono::year, chrono::month_nth);
      rel_date(chrono::year, chrono::month_nth, check_t)BOOST_NOEXCEPT;
      rel_date(chrono::year, chrono::month, last_tag);
      rel_date(chrono::year, chrono::month, last_tag, check_t)BOOST_NOEXCEPT;
#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE
      rel_date(chrono::year, chrono::month, chrono::day); // TODO
      rel_date(chrono::year, chrono::month, chrono::day, check_t)BOOST_NOEXCEPT;// TODO
      rel_date(chrono::year y, month_day md);// TODO
      rel_date(chrono::year, month_day, check_t) BOOST_NOEXCEPT;// TODO

      explicit rel_date(days d);// TODO

      rel_date(chrono::year y, day_of_year doy);// TODO
      rel_date(chrono::year y, day_of_year doy, check_t) BOOST_NOEXCEPT;// TODO

      bool set_if_valid_date(chrono::year y, chrono::month m, chrono::day d) BOOST_NOEXCEPT;// TODO
      bool set_if_valid_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT;// TODO
      bool set_if_valid_date(days d) BOOST_NOEXCEPT;// TODO

      static rel_date today() BOOST_NOEXCEPT;// TODO

      explicit rel_date(system_clock::time_point tp);// TODO
      // explicit
      operator system_clock::time_point () const;// TODO

#endif
      // conversions
      //explicit rel_date(ymd_date dt);
      operator ymd_date() const;
      //explicit rel_date(days_date dt);
      operator days_date() const;
      //explicit rel_date(ydoy_date dt);
      operator ydoy_date() const;

      // observers
      //bool is_valid() const BOOST_NOEXCEPT;

      chrono::day to_day() const BOOST_NOEXCEPT
      {
        return chrono::day(d_, no_check);
      }
      //chrono::day day() const BOOST_NOEXCEPT
      operator chrono::day() const BOOST_NOEXCEPT
      {
        return to_day();
      }
      chrono::month to_month() const BOOST_NOEXCEPT
      {
        return chrono::month(m_);
      }
      //chrono::month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT operator chrono::month() const BOOST_NOEXCEPT
      {
        return chrono::month(m_);
      }
      chrono::year to_year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_);
      }
      //chrono::year year() const BOOST_NOEXCEPT
      //BOOST_CONSTEXPR
      BOOST_CHRONO_EXPLICIT operator chrono::year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_);
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }

      //chrono::weekday weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT operator chrono::weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((day_number_from_ymd()+1) % weekday::size);
      }

      days days_since_epoch() const
      {
        return days(day_number_from_ymd());
      }

#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

      rel_date& operator+=(days d);
      rel_date& operator++()
      {
        return *this += days(1);
      }
      rel_date operator++(int)
      {
        rel_date tmp(*this);
        ++(*this);
        return tmp;
      }
      rel_date& operator-=(days d)
      {
        return *this += -d;
      }
      rel_date& operator--()
      {
        return *this -= days(1);
      }
      rel_date operator--(int)
      {
        rel_date tmp(*this);
        --(*this); return tmp;
      }

      friend rel_date operator+(rel_date dt, days d)
      {
        dt += d;
        return dt;
      }
      friend rel_date operator+(days d, rel_date dt)
      {
        dt += d;
        return dt;
      }
      friend rel_date operator-(rel_date dt, days d)
      {
        dt -= d;
        return dt;
      }
#endif
      friend days operator-(rel_date x, rel_date y) BOOST_NOEXCEPT
      {
        return days_date(x).days_since_epoch() - days_date(y).days_since_epoch();
      }
      friend days operator-(rel_date x, ymd_date y) BOOST_NOEXCEPT
      {
        return days_date(x).days_since_epoch() - days_date(y).days_since_epoch();
      }

      friend days operator-(ymd_date x, rel_date y) BOOST_NOEXCEPT
      {
        return days_date(x).days_since_epoch() - days_date(y).days_since_epoch();
      }

      rel_date& operator+=(months m);
      rel_date& operator-=(months m)
      {
        return *this += months(-m.count());
      }

      friend rel_date operator+(rel_date dt, months m)
      {
        dt += m;
        return dt;
      }
      friend rel_date operator+(months m, rel_date dt)
      {
        dt += m;
        return dt;
      }
      friend rel_date operator-(rel_date dt, months m)
      {
        dt -= m;
        return dt;
      }

      rel_date& operator+=(years y);
      rel_date& operator-=(years y)
      {
        return *this += years(-y.count());
      }

      friend rel_date operator+(rel_date dt, years y)
      {
        dt += y;
        return dt;
      }
      friend rel_date operator+(years y, rel_date dt)
      {
        dt += y;
        return dt;
      }
      friend rel_date operator-(rel_date dt, years y)
      {
        dt -= y;
        return dt;
      }

      friend bool operator==(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.m_ == y.m_ && x.d_ == y.d_;
      }
      friend bool operator< (const rel_date& x, const rel_date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.m_ < y.m_ ||
                (!(y.m_ < x.m_) && x.d_ < y.d_)));
      }
      friend bool operator!=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      friend bool operator> (const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      friend bool operator<=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      friend bool operator>=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }

      uint32_t day_number_from_ymd() const BOOST_NOEXCEPT;
    };

    template <>
    struct is_date<rel_date> : true_type {};

    BOOST_FORCEINLINE rel_date operator/(year_month ym, nth_weekday d)
    {
      return rel_date(year(ym), month(ym), d);
    }
    BOOST_FORCEINLINE rel_date operator/(year_month ym, last_weekday d)
    {
      return rel_date(year(ym), month(ym), d);
    }
    BOOST_FORCEINLINE rel_date operator/(year_month ym, last_tag)
    {
      return rel_date(year(ym), month(ym), last);
    }

    BOOST_FORCEINLINE rel_date operator/(month_nth_weekday md, chrono::year y)
    {
      return rel_date(y, month(md), nth_weekday(md));
    }
    BOOST_FORCEINLINE rel_date operator/(month_last_weekday md, chrono::year y)
    {
      return rel_date(y, month(md), last_weekday(md));
    }

    BOOST_FORCEINLINE rel_date operator/(month_nth_weekday md, year::rep y)
    {
      return md / chrono::year(y);
    }
    BOOST_FORCEINLINE rel_date operator/(month_last_weekday md, year::rep y)
    {
      return md / chrono::year(y);
    }

    BOOST_FORCEINLINE rel_date operator/(month_nth md, chrono::year y)
    {
      return rel_date(y, month(md), last);
    }

    BOOST_FORCEINLINE rel_date operator/(month_nth md, year::rep y)
    {
      return md / chrono::year(y);
    }

  } // chrono

} // boost

#endif  // header
