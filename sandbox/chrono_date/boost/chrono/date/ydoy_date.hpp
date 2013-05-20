//  ydoy_date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_YDOY_DATE_HPP
#define BOOST_CHRONO_DATE_YDOY_DATE_HPP

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
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/optional_date.hpp>
#include <boost/chrono/date/is_date.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class @c ydoy_date is a model of Date storing
     * - the @c year,
     * - the @c day_of_year
     * and optionally
     * - whether the year is leap or not.
     */
    class ydoy_date
    {

      // Store y/doy + leap. Total 32 bits
      int_least16_t y_;
      uint_least16_t doy_ :9;
      uint_least8_t leap_ :1;
      //uint_least8_t reserved2_ :6;

    public:

//      /**
//       * @Effect Constructs a ydoy_date using the year, month, day stored in the arguments as follows:
//       * If the value stored in d is outside the range of valid dates for this month m and year y,
//       * throws an exception of type bad_date.
//       * Else constructs a ydoy_date for which year() == y, month() == m, day() == d.
//       * @Throws bad_date if the specified ydoy_date is invalid.
//       */
//      ydoy_date(chrono::year y, chrono::month m, day d, check_t);
//      /**
//       * @Effect Constructs a ydoy_date constructor from year, month, day stored in the arguments as follows:
//       * Constructs a ydoy_date so that year() == y, month() = m=, day() == d.
//       */
//      ydoy_date(chrono::year y, chrono::month m, day d)
//BOOST_NOEXCEPT      ;
//      /**
//       * @Effect Constructs a ydoy_date using the year, month_day stored in the arguments as follows:
//       * If the value stored in md is outside the range of valid dates for this year y,
//       * throws an exception of type bad_date.
//       * Else constructs a ydoy_date for which year() == y, month() == md.month(), day() == md.month().
//       *
//       * @Throws bad_date if the specified ydoy_date is invalid.
//       * @Note This constructor can be more efficient as the month_day is already valid.
//       */
//      ydoy_date(chrono::year y, month_day md, check_t);
//      /**
//       * @Effect Constructs a ydoy_date using the year, month_day stored in the arguments as follows:
//       * Constructs a ydoy_date for which year() == y, month() == md.month(), day() == md.month().
//       * @Note This constructor can be more efficient as the month_day is already valid.
//       */
//      ydoy_date(chrono::year, month_day) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a ydoy_date using the year, day_of_year stored in the arguments as follows:
       * If the value stored in doy is 366 and the year.is_leap()
       * throws an exception of type bad_date.
       * Else constructs a ydoy_date for which days_since_epoch() == y.days_since_epoch()+doy
       * @Throws bad_date if the specified ydoy_date is invalid.
       * @Note This constructor can be more efficient as the check is simple.
       */
      ydoy_date(chrono::year y, day_of_year doy, check_t);
      /**
       * @Effect Constructs a ydoy_date using the year, day_of_year stored in the arguments as follows:
       * Constructs a ydoy_date for which days_since_epoch() == y.days_since_epoch()+doy
       * @Throws bad_date if the specified ydoy_date is invalid.
       */
      BOOST_FORCEINLINE BOOST_CHRONO_DATE_CONSTEXPR ydoy_date(chrono::year y, day_of_year doy) BOOST_NOEXCEPT
          : y_(y),
            doy_(doy),
            leap_(is_leap(y_))
          {
          }
//      /**
//       * @Effect Constructs a ydoy_date using the days given as parameter so that:
//       * days_since_epoch() == ds.count()
//       */
//      explicit ydoy_date(days, check_t);
//      /**
//       * Unchecked constructor from days.
//       */
//      ydoy_date(days m) BOOST_NOEXCEPT;
//
//      /**
//       * Unchecked constructor from ymd+leap
//       */
//      ydoy_date(days::rep, year::rep y, month::rep m, day::rep d, bool leap) BOOST_NOEXCEPT
//      : y_(y),
//      doy_(month_day_to_day_of_year(leap,m,d)),
//      leap_(leap)
//      {
//
//      }
//      /**
//       * Unchecked constructor from ymd+leap
//       */
//      ydoy_date(year::rep y, month::rep m, day::rep d, bool leap) BOOST_NOEXCEPT
//      : y_(y),
//      doy_(month_day_to_day_of_year(leap,m,d)),
//      leap_(leap)
//      {
//      }

//      /**
//       * @Return A ydoy_date which represents the current day taking the local time zone into account.
//       */
//      static ydoy_date today() BOOST_NOEXCEPT;

      /**
       * Effects: Constructs a ydoy_date as if by year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of ydoy_date construction when the specific value for that ydoy_date is unimportant.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR ydoy_date() BOOST_NOEXCEPT
          :
          y_(0),
          doy_(1),
          leap_(1)
          {
          }


//      /**
//       * @Effects tp is converted to UTC, and then trucated to 00:00:00 hours.
//       * A ydoy_date is created which reflects this point in time.
//       * @Throws If the conversion from tp overflows the range of ydoy_date, throws
//       * an exception of type bad_date.
//       *
//       */
//      explicit ydoy_date(system_clock::time_point tp);
//      /**
//       * @Returns: A system_clock::time_point which represents the ydoy_date
//       * referred to by *this at 00:00:00 UTC.
//       *
//       * @Throws If the conversion to tp overflows the range of
//       * system_clock::time_point, throws an exception of type bad_date.
//       *
//       */
//      // explicit
//      operator system_clock::time_point () const;

      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_valid() const BOOST_NOEXCEPT
      {
        // @todo add check on valid day_of_year and leap year.
        return chrono::year(y_).is_valid() && day_of_year(doy_).is_valid();
      }

      /**
       * @Returns: the number of days since an undefined epoch.
       */
      BOOST_FORCEINLINE days to_days_since_epoch() const
      {
        return days(days_before_year(y_+32799)+doy_-1);
      }
      /**
       * @Returns: the number of days since an undefined epoch.
       */
      BOOST_FORCEINLINE days days_since_epoch() const
      {
        return days(days_before_year(y_+32799)+doy_-1);
      }

      /**
       * Explicit conversion from @c ymd_date.
       *
       * @Effects stores a year and days_of_year that represents the same date as the @c dt @c days_date parameter.
       */
      explicit BOOST_FORCEINLINE ydoy_date(days_date dt);
//#if ! defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
      /**
       * Explicit conversion to @c days_date.
       *
       * @Returns a @c days_date representing the same date.
       */
      //BOOST_CHRONO_EXPLICIT
      BOOST_FORCEINLINE operator days_date() const
      {
        year::rep by = y_ + 32799;
        return days_date(days(days_before_year(by) + doy_ - 1));
        //return days_date(chrono::year(y_), day_of_year(doy_));
      }
//#endif
      /**
       * Explicit conversion to @c days_date.
       *
       * @Returns a @c days_date representing the same date.
       */
      friend BOOST_FORCEINLINE days_date to_days_date(ydoy_date ydoy)
      {
        year::rep by = ydoy.y_ + 32799;
        return days_date(days(days_before_year(by) + ydoy.doy_ - 1));
        //return days_date(chrono::year(y_), day_of_year(doy_));
      }

      /**
       * Explicit conversion from @c ymd_date.
       *
       * @Effects stores a year and days_of_year that represents the same date as the @c dt @c ymd_date parameter.
       */
      explicit ydoy_date(ymd_date dt);
#if ! defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
      /**
       * Explicit conversion to @c ymd_date.
       *
       * @Returns a @c ymd_date representing the same date.
       */
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE operator ymd_date() const
      {
        //return days_date(chrono::year(y_), day_of_year(doy_));
        return ymd_date(to_days_date(*this));
      }
#endif
      /**
       * Explicit conversion to @c ymd_date.
       *
       * @Returns a @c ymd_date representing the same date.
       */
      friend BOOST_FORCEINLINE ymd_date to_ymd_date(ydoy_date ydoy)
      {
        return ymd_date(to_days_date(ydoy));
      }



      /**
       * @Returns: chrono::day(d_).
       */
//      chrono::day to_day() const BOOST_NOEXCEPT
//      {
//        return chrono::day(day_of_year_day_of_month(leap_,doy_));
//      }
//      /**
//       * @Returns: chrono::day(d_).
//       */
//      chrono::day day() const BOOST_NOEXCEPT
//      {
//        return chrono::day(day_of_year_day_of_month(leap_,doy_));
//      }
      /**
       * @Returns: chrono::month(m_).
       */
      BOOST_FORCEINLINE chrono::month to_month() const BOOST_NOEXCEPT
      {
        return chrono::month(day_of_year_month(leap_,doy_));
      }
//      /**
//       * @Returns: chrono::month(m_).
//       */
//      chrono::month month() const BOOST_NOEXCEPT
//      {
//        return chrono::month(day_of_year_month(leap_,doy_));
//      }
      /**
       * @Returns: chrono::year(y_).
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR chrono::year to_year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_);
      }
      /**
       * @Returns: chrono::year(y_).
       */
      //BOOST_CONSTEXPR chrono::year year() const BOOST_NOEXCEPT
      BOOST_FORCEINLINE BOOST_CHRONO_EXPLICIT BOOST_CONSTEXPR operator chrono::year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_);
      }
      BOOST_FORCEINLINE chrono::month_day month_day() const BOOST_NOEXCEPT
      {
        return chrono::month_day(chrono::month(day_of_year_month(leap_,doy_)), chrono::day(day_of_year_day_of_month(leap_,doy_), no_check));
      }
      BOOST_FORCEINLINE chrono::year_month year_month() const BOOST_NOEXCEPT
      {
        return chrono::year_month(chrono::year(y_),chrono::month(day_of_year_month(leap_,doy_)));
      }
      BOOST_FORCEINLINE chrono::year_month_day year_month_day() const BOOST_NOEXCEPT
      {
        return to_ymd(chrono::year_day_of_year(chrono::year(y_),day_of_year(doy_)));
      }
      /**
       * @Returns: true if year() is a leap year, and otherwise returns false.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool to_is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }
      /**
       * @Returns: true if year() is a leap year, and otherwise returns false.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }

      /**
       * @Returns: A weekday constructed with an int corresponding to *this
       * ydoy_date's day of the week (a value in the range of [0 - 6], 0 is Sunday).
       */
      BOOST_FORCEINLINE chrono::weekday to_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((days_since_epoch()+days(1)).count() % chrono::weekday::size);
      }


//      /**
//       * @Effects Adds d.count() days to the current ydoy_date.
//       * @Returns: *this.
//       * @Throws If the addition would create a ydoy_date with a y_ outside of the
//       * range of year, throws an exception of type bad_date.
//       *
//       */
//      ydoy_date& operator+=(days d);
//
//      /**
//       * @Effects *this += days(1).
//       * @Returns: *this.
//       */
//      ydoy_date& operator++()
//      {
//        return *this += days(1);
//      }
//      /**
//       * @Effects *this += days(1).
//       * @Returns: A copy of *this prior to the increment.
//       */
//      ydoy_date operator++(int)
//      {
//        ydoy_date tmp(*this);
//        ++(*this);
//        return tmp;
//      }
//      /**
//       * @Effects *this += -d.
//       * @Returns: *this.
//       */
//      ydoy_date& operator-=(days d)
//      {
//        return *this += -d;
//      }
//      /**
//       * @Effects *this -= days(1).
//       * @Returns: *this.
//       */
//      ydoy_date& operator--()
//      {
//        return *this -= days(1);
//      }
//      /**
//       * @Effects *this -= days(1).
//       * @Returns: A copy of *this prior to the increment.
//       */
//      ydoy_date operator--(int)
//      {
//        ydoy_date tmp(*this); --(*this); return tmp;
//      }
//
//      /**
//       * @Returns: dt += d.
//       *
//       */
//      friend ydoy_date operator+(ydoy_date dt, days d)
//      {
//        dt += d;
//        return dt;
//      }
//      /**
//       * @Returns: dt += d.
//       *
//       */
//      friend ydoy_date operator+(days d, ydoy_date dt)
//      {
//        dt += d;
//        return dt;
//      }
//      /**
//       * @Returns: dt -= d.
//       *
//       */
//      friend ydoy_date operator-(ydoy_date dt, days d)
//      {
//        dt -= d;
//        return dt;
//      }
//      /**
//       * @Returns: Computes the number of days x is ahead of y in the calendar,
//       * and returns that signed integral number n as days(n).
//       */
//      friend days operator-(ydoy_date x, ydoy_date y) BOOST_NOEXCEPT
//      {
//        return days(x.days_since_epoch() - y.days_since_epoch());
//      }
//
//      friend days operator-(ymd_date x, ydoy_date y) BOOST_NOEXCEPT
//      {
//        return days(x.days_since_epoch() - y.days_since_epoch());
//      }
//
//      friend days operator-(ydoy_date x, ymd_date y) BOOST_NOEXCEPT
//      {
//        return days(x.days_since_epoch() - y.days_since_epoch());
//      }

//      /**
//       * @Effects Adds m.count() months to the current ydoy_date.
//       * This is accomplished as if by storing temporary values of the ydoy_date's y_, doy_.
//       * Computing new values for y_ and doy_ based on m. And then assigning to
//       * *this a new ydoy_date constructed from the newly computed y_ and doy_.
//       *
//       * @Returns: *this.
//       *
//       * @Throws If the addition would create a ydoy_date with a y_ outside of the
//       * range of year, or a doy_ outside the range for the newly computed y_,
//       * throws an exception of type bad_date.
//       *
//       */
//      ydoy_date& operator+=(months m);
//
//      /**
//       * @Returns: *this += -m.
//       */
//      ydoy_date& operator-=(months m)
//      {
//        return *this += months(-m.count());
//      }
//
//      /**
//       * @Returns: dt += m.
//       *
//       */
//      friend ydoy_date operator+(ydoy_date dt, months m)
//      {
//        dt += m;
//        return dt;
//      }
//      /**
//       * @Returns: dt += m.
//       *
//       */
//      friend ydoy_date operator+(months m, ydoy_date dt)
//      {
//        dt += m;
//        return dt;
//      }
//      /**
//       * @Returns: dt += -m.
//       *
//       */
//      friend ydoy_date operator-(ydoy_date dt, months m)
//      {
//        dt -= m;
//        return dt;
//      }
//
//      /**
//       * @Effects Adds y.count() years to the current ydoy_date.
//       * This is accomplished as if by storing temporary values of the ydoy_date's
//       * y_, doy_. Computing a new value for y_. And then assigning to *this
//       * a new ydoy_date constructed from the newly computed y_, and the original doy_.
//       * @Returns: *this.
//       * @Throws If the addition would create a ydoy_date with a y_ outside of the
//       * range of year, or a doy_ outside the range for the newly computed y_,
//       * throws an exception of type bad_date.
//       */
//      ydoy_date& operator+=(years y);
//
//      /**
//       * @Returns: *this += -y.
//       *
//       */
//      ydoy_date& operator-=(years y)
//      {
//        return *this += years(-y.count());
//      }
//
//      /**
//       * @Returns: dt += y.
//       *
//       */
//      friend ydoy_date operator+(ydoy_date dt, years y)
//      {
//        dt += y;
//        return dt;
//      }
//      /**
//       * @Returns: dt += y.
//       *
//       */
//      friend ydoy_date operator+(years y, ydoy_date dt)
//      {
//        dt += y;
//        return dt;
//      }
//      /**
//       * @Returns: dt -= y.
//       *
//       */
//      friend ydoy_date operator-(ydoy_date dt, years y)
//      {
//        dt -= y;
//        return dt;
//      }

      /**
       * @Returns: x.days_since_epoch() == y.days_since_epoch()
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator==(const ydoy_date& x, const ydoy_date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.doy_ == y.doy_;
      }
      /**
       * @Returns: x.days_since_epoch() < y.days_since_epoch()
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator< (const ydoy_date& x, const ydoy_date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.doy_ < y.doy_));
      }
      /**
       * @Returns: !(x == y).
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator!=(const ydoy_date& x, const ydoy_date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      /**
       * @Returns: y < x.
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator> (const ydoy_date& x, const ydoy_date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      /**
       * @Returns: !(y < x).
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator<=(const ydoy_date& x, const ydoy_date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      /**
       * @Returns: !(x < y).
       */
      friend BOOST_FORCEINLINE BOOST_CONSTEXPR bool operator>=(const ydoy_date& x, const ydoy_date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }

//      /**
//       * @Effects Update the ydoy_date if the parameters represents a valid ydoy_date.
//       * @Returns true if the parameters represents a valid ydoy_date.
//       */
//      bool set_if_valid_date(chrono::year y, chrono::month m, chrono::day d) BOOST_NOEXCEPT;

    };

    /**
     * Partial specialization of @c is_date<days_date> as @c true_type.
     */
    template <>
    struct is_date<ydoy_date> : true_type {};

//    /**
//     * A type representing an optional ydoy_date.
//     */
//    typedef optional<ydoy_date> optional_ydoy_date;
//    /**
//     * @Returns If the parameters represents a valid ydoy_date the ydoy_date,
//     * otherwise a none optional.
//     */
//    optional_ydoy_date make_valid_ydoy_date(year,month,day) BOOST_NOEXCEPT;

    /**
     * @c ydoy_date factory.
     * @Returns @c ydoy_date(y,d)
     */
    BOOST_FORCEINLINE  BOOST_CHRONO_DATE_CONSTEXPR ydoy_date operator/(chrono::year y, day_of_year d)
    {
      return ydoy_date(y, d);
    }
    /**
     * @c ydoy_date factory.
     * @Returns @c ydoy_date(y,d)
     */
    BOOST_FORCEINLINE  BOOST_CHRONO_DATE_CONSTEXPR ydoy_date operator/(day_of_year d, chrono::year y)
    {
      return ydoy_date(y, d);
    }
    /**
     * @c ydoy_date factory.
     * @Returns @c y/day_of_year(d)
     */
    BOOST_FORCEINLINE  BOOST_CHRONO_DATE_CONSTEXPR ydoy_date operator/(chrono::year y, int d)
    {
      return y / day_of_year(d);
    }
    /**
     * @c ydoy_date factory.
     * @Returns @c d/chrono::year(y)
     */
    BOOST_FORCEINLINE  BOOST_CHRONO_DATE_CONSTEXPR ydoy_date operator/(day_of_year d, int y)
    {
      return d / chrono::year(y);
    }

  } // chrono

} // boost


#endif  // header
