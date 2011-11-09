//  ymd_date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_YMD_DATE_HPP
#define BOOST_CHRONO_DATE_YMD_DATE_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/optional_date.hpp>
#include <boost/chrono/date/is_date.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class @c ymd_date is a model of Date storing
     * - the @c year,
     * - the @c month,
     * - the @c day of the month
     * and optionally
     * - the number of @c days since an undetermined epoch.
     * - whether the year is leap or not.
     */
    class ymd_date
    {

#if !defined BOOST_CHRONO_DATE_COMPACT
      // Store x, y/m/d, leap. Total 64 bits
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      uint_least32_t x_;
#endif
      int_least16_t y_;

      uint_least8_t m_ :4;
      uint_least8_t reserved1_ :4;

      uint_least8_t d_ :5;
      uint_least8_t leap_ :1;
      uint_least8_t reserved2_ :2;
#else
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      days x_;
#endif
      year y_;
      month m_;
      day d_;
      bool leap_;
#endif
    public:
      /**
       * @Effect Constructs a @c ymd_date using the @c year, @c month, @c day stored in the arguments as follows:
       * If the value stored in @c d is outside the range of valid dates for this month @c m and year @c y,
       * throws an exception of type @c bad_date.
       * Else constructs a @c ymd_date for which <c>get_year() == y && get_month() == m && get_day() == d</c>.
       * @Throws @c bad_date if the specified @c ymd_date is invalid.
       */
      ymd_date(chrono::year y, chrono::month m, chrono::day d);
      /**
       * @Effect Constructs a @c ymd_date constructor from @c year, @c month, @c day stored in the arguments as follows:
       * Constructs a ymd_date so that <c>get_year() == y && get_month() = m && get_day() == d</c>.
       */
      ymd_date(year::rep y, month::rep m, day::rep d, no_check_t)
BOOST_NOEXCEPT      ;
      /**
       * @Effect Constructs a ymd_date using the year, month_day stored in the arguments as follows:
       * If the value stored in md is outside the range of valid dates for this year y,
       * throws an exception of type bad_date.
       * Else constructs a ymd_date for which get_year() == y, get_month() == md.get_month(), get_day() == md.get_month().
       *
       * @Throws bad_date if the specified ymd_date is invalid.
       * @Note This constructor can be more efficient as the month_day is already valid.
       */
      ymd_date(chrono::year y, chrono::month_day md);
      /**
       * @Effect Constructs a ymd_date using the year, month_day stored in the arguments as follows:
       * Constructs a ymd_date for which get_year() == y, get_month() == md.get_month(), get_day() == md.get_month().
       * @Note This constructor can be more efficient as the month_day is already valid.
       */
      ymd_date(chrono::year::rep, chrono::month_day, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a ymd_date using the year, day_of_year stored in the arguments as follows:
       * If the value stored in doy is 366 and the year.is_leap()
       * throws an exception of type bad_date.
       * Else constructs a ymd_date for which days_since_epoch() == y.days_since_epoch()+doy.value()
       * @Throws bad_date if the specified ymd_date is invalid.
       * @Note This constructor can be more efficient as the check is simple.
       */
      ymd_date(chrono::year y, chrono::day_of_year doy);
      /**
       * @Effect Constructs a ymd_date using the year, day_of_year stored in the arguments as follows:
       * Constructs a ymd_date for which days_since_epoch() == y.days_since_epoch()+doy.value()
       * @Throws bad_date if the specified ymd_date is invalid.
       */
      ymd_date(year::rep y, day_of_year::rep m, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a ymd_date using the days given as parameter so that:
       * days_since_epoch() == ds.count()
       */
      explicit ymd_date(chrono::days);
      /**
       * Unchecked constructor from days.
       */
      ymd_date(days::rep m, no_check_t) BOOST_NOEXCEPT;

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      /**
       * Unchecked constructor from days+ymd+leap
       */
      ymd_date(days::rep x, year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
      : x_(x),
      y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }
      /**
       * Unchecked constructor from ymd+leap
       */
      ymd_date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT;

#elif BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      /**
       * Unchecked constructor from days+ymd+leap
       */
      ymd_date(days::rep, year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
      :
      y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }
      /**
       * Unchecked constructor from ymd+leap
       */
      ymd_date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }
#endif

      /**
       * @Effects Update the ymd_date if the parameters represents a valid ymd_date.
       * @Returns true if the parameters represents a valid ymd_date.
       */
      bool set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT;
      /**
       * @Effects Update the ymd_date if the parameters represents a valid ymd_date.
       * @Returns true if the parameters represents a valid ymd_date.
       */
      bool set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT;

      /**
       * @Effects Update the ymd_date if the parameters represents a valid ymd_date.
       * @Returns true if the parameters represents a valid ymd_date.
       */
      bool set_if_valid_date(days d) BOOST_NOEXCEPT;

      /**
       * @Return A ymd_date which represents the current day taking the local time zone into account.
       */
      static ymd_date today() BOOST_NOEXCEPT;

      /**
       * Effects: Constructs a ymd_date as if by year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of ymd_date construction when the specific value for that ymd_date is unimportant.
       */
      ymd_date() BOOST_NOEXCEPT
      :
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      x_(11979588),
#endif
      y_(0),
      m_(1),
      d_(1),
      leap_(1)
      {
      }
      /**
       * @Effects: tp is converted to UTC, and then trucated to 00:00:00 hours.
       * A ymd_date is created which reflects this point in time.
       * @Throws If the conversion from tp overflows the range of ymd_date, throws
       * an exception of type bad_date.
       *
       */
      explicit ymd_date(boost::chrono::system_clock::time_point tp);
      /**
       * @Returns: A chrono::system_clock::time_point which represents the ymd_date
       * referred to by *this at 00:00:00 UTC.
       *
       * @Throws: If the conversion to tp overflows the range of
       * boost::chrono::system_clock::time_point, throws an exception of type bad_date.
       *
       */
      // explicit
      operator boost::chrono::system_clock::time_point () const;

      bool is_valid() const BOOST_NOEXCEPT;

      /**
       * @Returns: the number of days since an undefined epoch.
       */
#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      days days_since_epoch() const
      {
        return days(x_);
      }
#elif BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      days days_since_epoch() const
      {
        return days(day_number_from_ymd());
      }
#endif

      ymd_date(days_date dt);
      operator days_date() const
      {
        return days_date(days_since_epoch().count(), no_check);
      }

      /**
       * Returns: chrono::day(d_,no_check).
       */
      chrono::day get_day() const BOOST_NOEXCEPT
      {
        return chrono::day(d_,no_check);
      }
      /**
       * Returns: chrono::month(m_,no_check).
       */
      chrono::month get_month() const BOOST_NOEXCEPT
      {
        return chrono::month(m_,no_check);
      }
      /**
       * Returns: chrono::year(y_,no_check).
       */
      chrono::year get_year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_,no_check);
      }
      month_day get_month_day() const BOOST_NOEXCEPT
      {
        return month_day(m_, d_, no_check);
      }
      year_month get_year_month() const BOOST_NOEXCEPT
      {
        return year_month(y_,m_,no_check);
      }
      year_month_day get_year_month_day() const BOOST_NOEXCEPT
      {
        return year_month_day(y_,m_,d_, no_check);
      }
      /**
       * Returns: true if year() is a leap year, and otherwise returns false.
       */
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      /**
       * @Returns: A weekday constructed with an int corresponding to *this
       * ymd_date's day of the week (a value in the range of [0 - 6], 0 is Sunday).
       */
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((x_ + 1) % weekday::size, no_check);
      }
#elif BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((day_number_from_ymd()+1) % weekday::size,no_check);
      }
#endif

      /**
       * @Effects: Adds d.count() days to the current ymd_date.
       * @Returns: *this.
       * @Throws: If the addition would create a ymd_date with a y_ outside of the
       * range of year, throws an exception of type bad_date.
       *
       */
      ymd_date& operator+=(days d);

      /**
       * @Effects: *this += days(1).
       * @Returns: *this.
       */
      ymd_date& operator++()
      {
        return *this += days(1);
      }
      /**
       * @Effects: *this += days(1).
       * @Returns: A copy of *this prior to the increment.
       */
      ymd_date operator++(int)
      {
        ymd_date tmp(*this);
        ++(*this);
        return tmp;
      }
      /**
       * @Effects: *this += -d.
       * @Returns: *this.
       */
      ymd_date& operator-=(days d)
      {
        return *this += -d;
      }
      /**
       * @Effects: *this -= days(1).
       * @Returns: *this.
       */
      ymd_date& operator--()
      {
        return *this -= days(1);
      }
      /**
       * @Effects: *this -= days(1).
       * @Returns: A copy of *this prior to the increment.
       */
      ymd_date operator--(int)
      {
        ymd_date tmp(*this); --(*this); return tmp;
      }

      /**
       * @Returns: dt += d.
       *
       */
      friend ymd_date operator+(ymd_date dt, days d)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: dt += d.
       *
       */
      friend ymd_date operator+(days d, ymd_date dt)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: dt -= d.
       *
       */
      friend ymd_date operator-(ymd_date dt, days d)
      {
        dt -= d;
        return dt;
      }
      /**
       * @Returns: Computes the number of days x is ahead of y in the calendar,
       * and returns that signed integral number n as days(n).
       */
      friend days operator-(ymd_date x, ymd_date y) BOOST_NOEXCEPT
      {
        return days(x.days_since_epoch() - y.days_since_epoch());
      }
      friend days operator-(days_date x, ymd_date y) BOOST_NOEXCEPT
      {
        return days(x.days_since_epoch() - y.days_since_epoch());
      }
      friend days operator-(ymd_date x, days_date y) BOOST_NOEXCEPT
      {
        return days(x.days_since_epoch() - y.days_since_epoch());
      }

      /**
       * @Effects Adds m.count() months to the current ymd_date.
       * This is accomplished as if by storing temporary values of the ymd_date's y_, m_, d_.
       * Computing new values for y_ and m_ based on m. And then assigning to
       * *this a new ymd_date constructed from the newly computed y_ and m_, and the
       * original d_.
       *
       * @Note Thus for example if a ymd_date is constructed as the second Sunday
       * in May, adding two months to this ymd_date results in the second Sunday
       * in July.
       *
       * @Returns: *this.
       *
       * @Throws: If the addition would create a ymd_date with a y_ outside of the
       * range of year, or a d_ outside the range for the newly computed y_/m_,
       * throws an exception of type bad_date.
       *
       */
      ymd_date& operator+=(months m);

      /**
       * Returns: *this += -m.
       */
      ymd_date& operator-=(months m)
      {
        return *this += months(-m.count());
      }

      /**
       * @Returns: dt += m.
       *
       */
      friend ymd_date operator+(ymd_date dt, months m)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: dt += m.
       *
       */
      friend ymd_date operator+(months m, ymd_date dt)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: dt += -m.
       *
       */
      friend ymd_date operator-(ymd_date dt, months m)
      {
        dt -= m;
        return dt;
      }

      /*
       * @Effects: Adds y.count() years to the current ymd_date.
       * This is accomplished as if by storing temporary values of the ymd_date's
       * y_, m_, d_. Computing a new value for y_. And then assigning to *this
       * a new ymd_date constructed from the newly computed y_, and the original m_, d_.
       * @Note: Thus for example if a ymd_date is constructed as the second Sunday
       * in May 2011, adding two years to this ymd_date results in the second Sunday
       * in May 2013.
       * @Returns: *this.
       * @Throws: If the addition would create a ymd_date with a y_ outside of the
       * range of year, or a d_ outside the range for the newly computed y_/m_,
       * throws an exception of type bad_date.
       */
      ymd_date& operator+=(years y);

      /**
       * @Returns: *this += -y.
       *
       */
      ymd_date& operator-=(years y)
      {
        return *this += years(-y.count());
      }

      /**
       * @Returns: dt += y.
       *
       */
      friend ymd_date operator+(ymd_date dt, years y)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: dt += y.
       *
       */
      friend ymd_date operator+(years y, ymd_date dt)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: dt -= y.
       *
       */
      friend ymd_date operator-(ymd_date dt, years y)
      {
        dt -= y;
        return dt;
      }

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      /**
       * Returns: x.days_since_epoch() == y.days_since_epoch()
       */
      friend bool operator==(const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return x.x_ == y.x_;
      }
      /**
       * Returns: x.days_since_epoch() < y.days_since_epoch()
       */
      friend bool operator< (const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return x.x_ < y.x_;
      }
#elif BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      friend bool operator==(const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.m_ == y.m_ && x.d_ == y.d_;
      }
      friend bool operator< (const ymd_date& x, const ymd_date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.m_ < y.m_ ||
                (!(y.m_ < x.m_) && x.d_ < y.d_)));
      }
#endif
      /**
       * @Returns: !(x == y).
       */
      friend bool operator!=(const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      /**
       * @Returns: y < x.
       */
      friend bool operator> (const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      /**
       * @Returns: !(y < x).
       */
      friend bool operator<=(const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      /**
       * @Returns: !(x < y).
       */
      friend bool operator>=(const ymd_date& x, const ymd_date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }



    private:

#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 3
      days::rep day_number_from_ymd() const BOOST_NOEXCEPT;
#endif
      //#if BOOST_CHRONO_DATE_YMD_DATE_DESIGN == 1
      //      day::rep day_from_day_number() const BOOST_NOEXCEPT;
      //      month::rep month_from_day_number() const BOOST_NOEXCEPT;
      //      year::rep year_from_day_number() const BOOST_NOEXCEPT;
      //      bool leap_from_day_number() const BOOST_NOEXCEPT;
      //#endif

    };

    template <>
    struct is_date<ymd_date> : true_type {};

//    /**
//     * A type representing an optional ymd_date.
//     */
//    typedef optional<ymd_date> optional_ymd_date;
//    /**
//     * @Returns If the parameters represents a valid ymd_date the ymd_date,
//     * otherwise a none optional.
//     */
//    inline optional_ymd_date make_valid_ymd_date(year y,month m,day d) BOOST_NOEXCEPT
//    {
//      ymd_date res;
//      if (res.set_if_valid_date(y,m,d)) return optional_ymd_date(res);
//      else return optional_ymd_date();
//
//    }

    //    ymd_date make_ymd_date(year::rep,month::rep,day::rep) BOOST_NOEXCEPT;
    //    ymd_date make_ydoy_date(year::rep,day_of_year::rep) BOOST_NOEXCEPT;
    //    ymd_date make_epoch_date(days::rep) BOOST_NOEXCEPT;

    inline ymd_date operator/(year_month ym, day d)
    {
      return ymd_date(ym.get_year(), ym.get_month(), d);
    }
    inline ymd_date operator/(year_month ym, day::rep d)
    {
      return ym / day(d);
    }
    inline ymd_date operator/(month_day md, year y)
    {
      return ymd_date(y, md.get_month(), md.get_day());
    }
    inline ymd_date operator/(year y, month_day md)
    {
      return ymd_date(y, md.get_month(), md.get_day());
    }
    inline ymd_date operator/(month_day md, year::rep y)
    {
      return md / year(y);
    }

  } // chrono

} // boost


#endif  // header
