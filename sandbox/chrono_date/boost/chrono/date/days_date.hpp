//  days_date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DAYS_DATE_HPP
#define BOOST_CHRONO_DATE_DAYS_DATE_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/conversions.hpp>
#include <boost/chrono/date/optional_date.hpp>
#include <boost/chrono/date/is_date.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class days_date is a model of Date storing
     * - the number of @c days since an undetermined epoch.
     */
    class days_date
    {
      // Store x. Total 32 bits
      boost::uint_least32_t x_;

    public:
      /**
       * Effects: Constructs a @c days_date as if by @c year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of @c days_date valid construction when the specific value for that @c days_date is unimportant.
       */
      days_date() BOOST_NOEXCEPT
      : x_(11979588)
      {
      }

      /**
       * @Effect Constructs a @c days_date using the @c year, @c month, @c day stored in the arguments as follows:
       * If the value stored in @c d is outside the range of valid dates for the month @c m and year @c y,
       * throws an exception of type @c bad_date.
       * Else constructs a @c days_date for which <c>get_year() == y && get_month() == m && get_day() == d</c>.
       * @Throws bad_date if the specified days_date is invalid.
       */
      days_date(chrono::year y, chrono::month m, chrono::day d);
      /**
       * @Effect Constructs a @c days_date constructor from @c year, @c month, @c day stored in the arguments as follows:
       * Constructs a @c days_date so that <c>get_year() == y && get_month() == m && get_day() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(year::rep y, month::rep m, day::rep d, no_check_t)
BOOST_NOEXCEPT      ;
      /**
       * @Effect Constructs a @c days_date using the @c year, @c month_day stored in the arguments as follows:
       * If the value stored in @c md is outside the range of valid dates for the year @c y,
       * throws an exception of type @c bad_date.
       * Else constructs a @c days_date for which <c>get_year() == y && get_month() == md.get_month() && get_day() == md.get_day()</c>.
       *
       * @Throws @c bad_date if the specified @c days_date is invalid.
       * @Note This constructor can be more efficient as the @c month_day is already valid.
       */
      days_date(chrono::year y, chrono::month_day md);
      /**
       * @Effect Constructs a @c days_date using the @c year, @c month_day stored in the arguments as follows:
       * Constructs a @c days_date for which <c>get_year() == y && get_month() == md.get_month() && get_day() == md.get_day()</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(chrono::year::rep, chrono::month_day, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a @c days_date using the @c year, @c day_of_year stored in the arguments as follows:
       * If the value stored in @c doy is @c 366 and @c year.is_leap()
       * throws an exception of type @c bad_date.
       * Else constructs a @c days_date for which <c>days_since_epoch() == y.days_since_epoch()+doy.value()<c>
       * @Throws @c bad_date if the specified @c days_date is invalid.
       * @Note This constructor can be more efficient as the check is simpler.
       */
      days_date(chrono::year y, chrono::day_of_year doy);
      /**
       * @Effect Constructs a days_date using the year, day_of_year stored in the arguments as follows:
       * Constructs a days_date for which days_since_epoch() == y.days_since_epoch()+doy.value()
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(year::rep y, day_of_year::rep doy, no_check_t) BOOST_NOEXCEPT;

      /**
       * @Effect Constructs a @c days_date using the @c days given as parameter so that:
       * <c>days_since_epoch() == ds.count()</c>.
       * @Throws @bad_date if the days is not in the range [11322,23947853].
       */
      explicit days_date(chrono::days d)
      : x_(d.count())
      {
        if (!is_valid())
        {
          throw bad_date("days " + boost::chrono::to_string(d.count()) + " is out of range");
        }
      }

      /**
       * Unchecked constructor from @c days
       * @Effect Constructs a @c days_date using the @c days given as parameter so that:
       * <c>days_since_epoch() == ds.count()</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(days::rep x, no_check_t) BOOST_NOEXCEPT
      : x_(x)
      {
      }
      /**
       * @Effect Constructs a @c days_date constructor from @c year, @c month, @c day stored in the arguments as follows:
       * Constructs a @c days_date so that <c>get_year() == y @@  get_month() = m &&  get_day() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(days::rep x, year::rep, month::rep, day::rep, bool, no_check_t) BOOST_NOEXCEPT
      : x_(x)
      {
      }
      /**
       * @Effect Constructs a @c days_date constructor from @c year, @c month, @c day stored in the arguments as follows:
       * Constructs a @c days_date so that <c>get_year() == y && get_month() = m && get_day() == d</c>.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      days_date(year::rep, month::rep, day::rep, bool, no_check_t) BOOST_NOEXCEPT;

      // setters
      /**
       * @Effects Update the @c days_date if the parameters @c year, @c month, @c day represents a valid date.
       * @Returns @c true if the parameters represents a valid date.
       */
      bool set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT;
      /**
       * @Effects Update the days_date if the parameters represents a valid date.
       * @Returns @c true if the parameters represents a valid date.
       */
      bool set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT;
      /**
       * @Effects Update the days_date if the parameter represents a valid days_date.
       * @Returns true if the parameters represents a valid days_date.
       */
      bool set_if_valid_date(days d) BOOST_NOEXCEPT;

      // factories
      /**
       * @Return A days_date which represents the current day taking the local time zone into account.
       */
      static days_date today() BOOST_NOEXCEPT;


      // Conversions
      /**
       * @Effects: @c tp is converted to UTC, and then truncated to 00:00:00 hours.
       * A @c days_date is created which reflects this point in time.
       * @Throws If the conversion from @c tp overflows the range of @c days_date, throws
       * an exception of type @c bad_date.
       *
       */
      explicit days_date(boost::chrono::system_clock::time_point tp);
      /**
       * @Returns: A chrono::system_clock::time_point which represents the @c days_date
       * referred to by *this at 00:00:00 UTC.
       *
       * @Throws: If the conversion to @c tp overflows the range of
       * boost::chrono::system_clock::time_point, throws an exception of type @c bad_date.
       *
       */
      // explicit
      operator boost::chrono::system_clock::time_point () const;


      // Observers
      /**
       * @return @c true if the stored days are in the range [11322,23947853].
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return x_ >= 11322 && x_ <= 23947853;
      }

      /**
       * @Returns: the number of days since an undefined epoch.
       */
      days days_since_epoch()
      {
        return days(x_);
      }

      /**
       * Returns: <c>chrono::day(d_,no_check)</c>.
       */
      chrono::day get_day() const BOOST_NOEXCEPT
      {
        return chrono::day(day_from_day_number(),no_check);
      }
      /**
       * Returns: <c>chrono::month(m_,no_check)</c>.
       */
      chrono::month get_month() const BOOST_NOEXCEPT
      {
        return chrono::month(month_from_day_number(),no_check);
      }
      /**
       * Returns: <c>chrono::year(y_,no_check)</c>.
       */
      chrono::year get_year() const BOOST_NOEXCEPT
      {
        return chrono::year(year_from_day_number(),no_check);
      }
      /**
       * Returns: @c true if @c year() is a leap year, and @c false otherwise.
       */
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_from_day_number();
      }
      /**
       * @return the @c month_day built from the @c month and @c day associated to the date.
       */
      month_day get_month_day() const BOOST_NOEXCEPT;
      /**
       * @return the @c year_month built from the @c year and @c month associated to the date.
       */
      year_month get_year_month() const BOOST_NOEXCEPT;
      /**
       * @return the @c year_month_day built from the @c year, @c month and @c day associated to the date.
       */
      year_month_day get_year_month_day() const BOOST_NOEXCEPT;

      /**
       * @Returns: A weekday constructed with an int corresponding to *this
       * days_date's day of the week (a value in the range of [0 - 6], 0 is Sunday).
       */
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((x_ + 1) % weekday::size, no_check);
      }

      // Days Based Arithmetic
      /**
       * @Effects: Adds @c d.count() days to the current @c days_date.
       * @Returns: <c>*this</c>.
       * @Throws: If the addition would create a @c days_date with a year() outside of the
       * range of @c year, throws an exception of type @c bad_date.
       *
       */
      days_date& operator+=(days d);

      /**
       * @Effects: <c>*this += days(1)</c>.
       * @Returns: <c>*this</c>.
       */
      days_date& operator++()
      {
        return *this += days(1);
      }
      /**
       * @Effects: <c>*this += days(1)</c>.
       * @Returns: A copy of @c *this prior to the increment.
       */
      days_date operator++(int)
      {
        days_date tmp(*this);
        ++(*this);
        return tmp;
      }
      /**
       * @Effects: <c>*this += -d</c>.
       * @Returns: <c>*this</c>.
       */
      days_date& operator-=(days d)
      {
        return *this += -d;
      }
      /**
       * @Effects: <c>*this -= days(1)</c>.
       * @Returns: <c>*this</c>.
       */
      days_date& operator--()
      {
        return *this -= days(1);
      }
      /**
       * @Effects: <c>*this -= days(1)</c>.
       * @Returns: A copy of @c *this prior to the increment.
       */
      days_date operator--(int)
      {
        days_date tmp(*this); --(*this); return tmp;
      }

      /**
       * @Returns: <c>dt += d</c>.
       *
       */
      friend days_date operator+(days_date dt, days d)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: <c>dt += d</c>.
       *
       */
      friend days_date operator+(days d, days_date dt)
      {
        dt += d;
        return dt;
      }
      /**
       * @Returns: <c>dt -= d</c>.
       *
       */
      friend days_date operator-(days_date dt, days d)
      {
        dt -= d;
        return dt;
      }
      /**
       * @Returns: Computes the number of days @c x is ahead of @c y in the calendar,
       * and returns that signed integral number @c n as days(n).
       */
      friend days operator-(days_date x, days_date y) BOOST_NOEXCEPT
      {
        return x.days_since_epoch() - y.days_since_epoch();
      }

      // Month Based Arithmetic

      /**
       * @Effects Adds @c m.count() months to the current date.
       * This is accomplished as if by storing temporary values of the days_date's @c year @c y_, @c month @c m_, @c day @c _d.
       * Computing new values for @c y_ and @c m_ based on @c m. And then assigning to
       * @c *this a new @c days_date constructed from the newly computed @c y_ and @c m_, and the
       * original @c d_.
       *
       * @Returns: @c *this.
       *
       * @Throws: If the addition would create a @c days_date with a @c y_ outside of the
       * range of @c year, or a @c d_ outside the range for the newly computed @c y_/@c m_,
       * throws an exception of type @c bad_date.
       *
       */
      days_date& operator+=(months m);

      /**
       * Returns: <c>*this += -m</c>.
       */
      days_date& operator-=(months m)
      {
        return *this += months(-m.count());
      }

      /**
       * @Returns: <c>dt += m</c>.
       *
       */
      friend days_date operator+(days_date dt, months m)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: <c>dt += m</c>.
       *
       */
      friend days_date operator+(months m, days_date dt)
      {
        dt += m;
        return dt;
      }
      /**
       * @Returns: <c>dt += -m</c>.
       *
       */
      friend days_date operator-(days_date dt, months m)
      {
        dt -= m;
        return dt;
      }

      // Years Based Arithmetic

      /*
       * @Effects: Adds @c y.count() years to the current date.
       * This is accomplished as if by storing temporary values of the days_date's
       * @c year @c y_, @c month @c m_, @c day @c d_. Computing a new value for @c y_. And then assigning to @c *this
       * a new @c days_date constructed from the newly computed @c y_, and the original @c m_, @c d_.
       * @Returns: @c *this.
       * @Throws: If the addition would create a @c days_date with a @c y_ outside of the
       * range of @c year, or a @c d_ outside the range for the newly computed @c y_/@c m_,
       * throws an exception of type @c bad_date.
       */
      days_date& operator+=(years y);

      /**
       * @Returns: <c>*this += -y</c>.
       *
       */
      days_date& operator-=(years y)
      {
        return *this += years(-y.count());
      }

      /**
       * @Returns: <c>dt += y</c>.
       *
       */
      friend days_date operator+(days_date dt, years y)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: <c>dt += y</c>.
       *
       */
      friend days_date operator+(years y, days_date dt)
      {
        dt += y;
        return dt;
      }
      /**
       * @Returns: <c>dt -= y</c>.
       *
       */
      friend days_date operator-(days_date dt, years y)
      {
        dt -= y;
        return dt;
      }

      // Relational operators
      /**
       * Returns: <c>x.days_since_epoch() == y.days_since_epoch()</c>.
       */
      friend bool operator==(const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return x.x_ == y.x_;
      }
      /**
       * Returns: <c>x.days_since_epoch() < y.days_since_epoch()</c>.
       */
      friend bool operator< (const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return x.x_ < y.x_;
      }
      /**
       * @Returns: <c>!(x == y)</c>.
       */
      friend bool operator!=(const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      /**
       * @Returns: <c>y < x</c>.
       */
      friend bool operator> (const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      /**
       * @Returns: <c>!(y < x)</c>.
       */
      friend bool operator<=(const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      /**
       * @Returns: <c>!(x < y)</c>.
       */
      friend bool operator>=(const days_date& x, const days_date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }


    private:

      day::rep day_from_day_number() const BOOST_NOEXCEPT;
      month::rep month_from_day_number() const BOOST_NOEXCEPT;
      year::rep year_from_day_number() const BOOST_NOEXCEPT;
      bool leap_from_day_number() const BOOST_NOEXCEPT;
    };

    /**
     * Partial specialization of @c is_date<days_date> as a true type.
     */
    template <>
    struct is_date<days_date> : true_type {};

  } // chrono

} // boost


#endif  // header
