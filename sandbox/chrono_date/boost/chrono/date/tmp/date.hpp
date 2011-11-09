//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_HPP
#define BOOST_CHRONO_DATE_DATE_HPP

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
#include <boost/optional.hpp>
#include <boost/chrono/date/config.hpp>

namespace boost
{
  namespace chrono
  {

    class date
    {
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1
      // Store x, y/m/d, leap. Total 64 bits
      uint_least32_t x_;
      int_least16_t y_;

      uint_least8_t m_         : 4;
      uint_least8_t reserved1_ : 4;

      uint_least8_t d_         : 5;
      uint_least8_t leap_      : 1;
      uint_least8_t reserved2_ : 2;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
      // Store x. Total 32 bits
      uint32_t x_;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      // Store y/m/d. Total 32 bits
      int_least16_t y_;
      uint_least8_t m_         : 4;
      uint_least8_t reserved1_ : 4;
      uint_least8_t d_         : 5;
      uint_least8_t leap_      : 1;
      uint_least8_t reserved2_ : 2;
#endif

    public:
      /**
       * @Effect Constructs a date using the year, month, day stored in the arguments as follows:
       * If the value stored in d is outside the range of valid dates for this month m and year y,
       * throws an exception of type bad_date.
       * Else constructs a date for which get_year() == y, get_month() == m, get_day() == d.
       * @Throws bad_date if the specified date is invalid.
       */
      date(chrono::year y, chrono::month m, chrono::day d);
      /**
       * @Effect Constructs a date constructor from year, month, day stored in the arguments as follows:
       * Constructs a date so that get_year() == y, get_month() = m=, get_day() == d.
       */
      date(year::rep y, month::rep m, day::rep d, no_check_t) BOOST_NOEXCEPT;
      /**
       * @Effect Constructs a date using the year, month_day stored in the arguments as follows:
       * If the value stored in md is outside the range of valid dates for this year y,
       * throws an exception of type bad_date.
       * Else constructs a date for which get_year() == y, get_month() == md.get_month(), get_day() == md.get_month().
       *
       * @Throws bad_date if the specified date is invalid.
       * @Note This constructor can be more efficient as the month_day is already valid.
       */
      date(chrono::year y, chrono::month_day md);
      /**
       * @Effect Constructs a date using the year, month_day stored in the arguments as follows:
       * Constructs a date for which get_year() == y, get_month() == md.get_month(), get_day() == md.get_month().
       * @Note This constructor can be more efficient as the month_day is already valid.
       */
      date(chrono::year::rep, chrono::month_day, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a date using the year, day_of_year stored in the arguments as follows:
       * If the value stored in doy is 366 and the year.is_leap()
       * throws an exception of type bad_date.
       * Else constructs a date for which days_since_epoch() == y.days_since_epoch()+doy.value()
       * @Throws bad_date if the specified date is invalid.
       * @Note This constructor can be more efficient as the check is simple.
       */
      date(chrono::year y, chrono::day_of_year doy);
      /**
       * @Effect Constructs a date using the year, day_of_year stored in the arguments as follows:
       * Constructs a date for which days_since_epoch() == y.days_since_epoch()+doy.value()
       * @Throws bad_date if the specified date is invalid.
       */
      date(year::rep y, day_of_year::rep m, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a date using the days given as parameter so that:
       * days_since_epoch() == ds.count()
       */
      date(chrono::days) BOOST_NOEXCEPT;
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 ||  BOOST_CHRONO_DATE_DATE_DESIGN == 3
      /**
       * Unchecked constructor from days.
       */
      date(days::rep m, no_check_t) BOOST_NOEXCEPT;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
      /**
       * Unchecked constructor from days
       */
      date(days::rep x, no_check_t) BOOST_NOEXCEPT
      : x_(x)
      {
      }
#endif

    //private:
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1
      /**
       * Unchecked constructor from ymd+leap
       */
      date(days::rep x, year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
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
      date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
      /**
       * Unchecked constructor from ymd+leap
       */
      date(days::rep x, year::rep, month::rep, day::rep, bool, no_check_t) BOOST_NOEXCEPT
      : x_(x)
      {
      }
      /**
       * Unchecked constructor from ymd+leap
       */
      date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      /**
       * Unchecked constructor from ymd+leap
       */
      date(days::rep , year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
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
      date(year::rep y, month::rep m, day::rep d, bool leap, no_check_t) BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }
#endif
    public:
      /**
       * @Return A date which represents the current day taking the local time zone into account.
       */
      static date today() BOOST_NOEXCEPT;

      /**
       * Effects: Constructs a date as if by year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of date construction when the specific value for that date is unimportant.
       */
      date() BOOST_NOEXCEPT;

      /**
       * @Effects: tp is converted to UTC, and then trucated to 00:00:00 hours.
       * A date is created which reflects this point in time.
       * @Throws If the conversion from tp overflows the range of date, throws
       * an exception of type bad_date.
       *
       */
      explicit date(boost::chrono::system_clock::time_point tp);
      /**
       * @Returns: A chrono::system_clock::time_point which represents the date
       * referred to by *this at 00:00:00 UTC.
       *
       * @Throws: If the conversion to tp overflows the range of
       * boost::chrono::system_clock::time_point, throws an exception of type bad_date.
       *
       */
      // explicit
      operator boost::chrono::system_clock::time_point () const;

#if BOOST_CHRONO_DATE_DATE_DESIGN == 2
      bool is_valid() const BOOST_NOEXCEPT
      {
        return true;
      }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 3
      bool is_valid() const BOOST_NOEXCEPT;
#endif

      /**
       * @Returns: the number of days since an undefined epoch.
       */
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 2
      days days_since_epoch()
      {
        return days(x_);
      }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      days days_since_epoch()
      {
        return days(day_number_from_ymd());
      }
#endif
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 3
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
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
      chrono::day get_day() const BOOST_NOEXCEPT
      {
        return chrono::day(day_from_day_number(),no_check);
      }
      chrono::month get_month() const BOOST_NOEXCEPT
      {
        return chrono::month(month_from_day_number(),no_check);
      }
      chrono::year get_year() const BOOST_NOEXCEPT
      {
        return chrono::year(year_from_day_number(),no_check);
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_from_day_number();
      }
      month_day get_month_day() const BOOST_NOEXCEPT;
      year_month get_year_month() const BOOST_NOEXCEPT;
      year_month_day get_year_month_day() const BOOST_NOEXCEPT;

#endif
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 2
      /**
       * @Returns: A weekday constructed with an int corresponding to *this
       * date's day of the week (a value in the range of [0 - 6], 0 is Sunday).
       */
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((x_ + 1) % weekday::size, no_check);
      }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((day_number_from_ymd()+1) % weekday::size,no_check);
      }
#endif

      /**
       * @Effects: Adds d.count() days to the current date.
       * @Returns: *this.
       * @Throws: If the addition would create a date with a y_ outside of the
       * range of year, throws an exception of type bad_date.
       *
       */
      date& operator+=(days d);

      /**
       * @Effects: *this += days(1).
       * @Returns: *this.
       */
      date& operator++()
      {
        return *this += days(1);
      }
      /**
       * @Effects: *this += days(1).
       * @Returns: A copy of *this prior to the increment.
       */
      date operator++(int)
      {
        date tmp(*this);
        ++(*this);
        return tmp;
      }
      /**
       * @Effects: *this += -d.
       * @Returns: *this.
       */
      date& operator-=(days d)
      {
        return *this += -d;
      }
      /**
       * @Effects: *this -= days(1).
       * @Returns: *this.
       */
      date& operator--()
      {
        return *this -= days(1);
      }
      /**
       * @Effects: *this -= days(1).
       * @Returns: A copy of *this prior to the increment.
       */
      date operator--(int)
      {
        date tmp(*this); --(*this); return tmp;
      }

      /**
       * @Returns: dt += d.
       *
       */
      friend date operator+(date dt, days d)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: dt += d.
       *
       */
      friend date operator+(days d, date dt)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: dt -= d.
       *
       */
      friend date operator-(date dt, days d)
      {
        dt -= d;
        return dt;
      }
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 2
      /**
       * @Returns: Computes the number of days x is ahead of y in the calendar,
       * and returns that signed integral number n as days(n).
       */
      friend days operator-(date x, date y) BOOST_NOEXCEPT
      {
        return days(x.x_ - y.x_);
      }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      friend days operator-(date x, date y) BOOST_NOEXCEPT
      {
        return days(x.day_number_from_ymd() - y.day_number_from_ymd());
      }
#endif

      /**
       * @Effects Adds m.count() months to the current date.
       * This is accomplished as if by storing temporary values of the date's y_, m_, d_.
       * Computing new values for y_ and m_ based on m. And then assigning to
       * *this a new date constructed from the newly computed y_ and m_, and the
       * original d_.
       *
       * @Note Thus for example if a date is constructed as the second Sunday
       * in May, adding two months to this date results in the second Sunday
       * in July.
       *
       * @Returns: *this.
       *
       * @Throws: If the addition would create a date with a y_ outside of the
       * range of year, or a d_ outside the range for the newly computed y_/m_,
       * throws an exception of type bad_date.
       *
       */
      date& operator+=(months m);

      /**
       * Returns: *this += -m.
       */
      date& operator-=(months m)
      {
        return *this += months(-m.count());
      }

      /**
       * @Returns: dt += m.
       *
       */
      friend date operator+(date dt, months m)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: dt += m.
       *
       */
      friend date operator+(months m, date dt)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: dt += -m.
       *
       */
      friend date operator-(date dt, months m)
      {
        dt -= m;
        return dt;
      }

      /*
       * @Effects: Adds y.count() years to the current date.
       * This is accomplished as if by storing temporary values of the date's
       * y_, m_, d_. Computing a new value for y_. And then assigning to *this
       * a new date constructed from the newly computed y_, and the original m_, d_.
       * @Note: Thus for example if a date is constructed as the second Sunday
       * in May 2011, adding two years to this date results in the second Sunday
       * in May 2013.
       * @Returns: *this.
       * @Throws: If the addition would create a date with a y_ outside of the
       * range of year, or a d_ outside the range for the newly computed y_/m_,
       * throws an exception of type bad_date.
       */
      date& operator+=(years y);

      /**
       * @Returns: *this += -y.
       *
       */
      date& operator-=(years y)
      {
        return *this += years(-y.count());
      }

      /**
       * @Returns: dt += y.
       *
       */
      friend date operator+(date dt, years y)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: dt += y.
       *
       */
      friend date operator+(years y, date dt)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: dt -= y.
       *
       */
      friend date operator-(date dt, years y)
      {
        dt -= y;
        return dt;
      }

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_DATE_DESIGN == 2
      /**
       * Returns: x.days_since_epoch() == y.days_since_epoch()
       */
      friend bool operator==(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.x_ == y.x_;
      }
      /**
       * Returns: x.days_since_epoch() < y.days_since_epoch()
       */
      friend bool operator< (const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.x_ < y.x_;
      }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      friend bool operator==(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.m_ == y.m_ && x.d_ == y.d_;
      }
      friend bool operator< (const date& x, const date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.m_ < y.m_ ||
                (!(y.m_ < x.m_) && x.d_ < y.d_)));
      }
#endif
      /**
       * @Returns: !(x == y).
       */
      friend bool operator!=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      /**
       * @Returns: y < x.
       */
      friend bool operator> (const date& x, const date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      /**
       * @Returns: !(y < x).
       */
      friend bool operator<=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      /**
       * @Returns: !(x < y).
       */
      friend bool operator>=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }

      /**
       * @Effects Update the date if the parameters represents a valid date.
       * @Returns true if the parameters represents a valid date.
       */
      bool set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT;
    private:

#if BOOST_CHRONO_DATE_DATE_DESIGN == 2
      day::rep day_from_day_number() const BOOST_NOEXCEPT;
      month::rep month_from_day_number() const BOOST_NOEXCEPT;
      year::rep year_from_day_number() const BOOST_NOEXCEPT;
      bool leap_from_day_number() const BOOST_NOEXCEPT;
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 3
      days::rep day_number_from_ymd() const BOOST_NOEXCEPT;
#endif
    };

    /**
     * A type representing an optional date.
     */
    typedef optional<date> optional_date;
    /**
     * @Returns If the parameters represents a valid date the date,
     * otherwise a none optional.
     */
    optional_date make_valid_date(year,month,day) BOOST_NOEXCEPT;

    date make_ymd_date(year::rep,month::rep,day::rep) BOOST_NOEXCEPT;
    date make_ydoy_date(year::rep,day_of_year::rep) BOOST_NOEXCEPT;
    date make_epoch_date(days::rep) BOOST_NOEXCEPT;


  } // chrono

} // boost


#endif  // header
