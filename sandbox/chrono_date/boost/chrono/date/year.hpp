//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_YEAR_HPP
#define BOOST_CHRONO_DATE_DATE_YEAR_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class year is used to specify the year when constructing a date.
     * It also defines the range of the date class by restricting the value of
     * the year to a range.
     *
     * That range shall be at least [year(-32767)/jan/1 thru year(32767)/dec/31].
     */
    class year
    {
    public:
      /**
       * Internal representation of a year.
       *
       * In order for year to detect overflow, the integral type used to construct the year must have a range greater than that of year.
       */
      typedef int_least32_t rep;
      static const rep last_ = 32767;
      static const rep first_ = -32768;
      static const std::size_t size = last_ - first_ + 1; // :16 bits

      /**
       * @Effects: Constructs an object of class year by storing y.
       * @Postconditions: static_cast<int>(*this) == y.
       * @Throws: if y is outside of the supported range, throws an exception of type bad_date.
       */
      explicit year(rep v) :
        value_(v)
      {
        if (!is_valid())
        {
          throw bad_date("year " + to_string(v) + " is out of range");
        }
      }

      /**
       * @Effects: Constructs an object of class year by storing y.
       * @Postconditions: static_cast<int>(*this) == y.
       */
      BOOST_CONSTEXPR year(rep y, no_check_t)BOOST_NOEXCEPT
      :value_(y)
      {}
      /**
       * @Return if the stored value is a valid one.
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (first_ <= value_ && value_ <= last_);
      }

      /**
       * Returns: the value of the stored int.
       */
      operator rep() const BOOST_NOEXCEPT
      {
        return value_;
      }
      /**
       * Returns: the value of the stored int.
       */
      rep value() const BOOST_NOEXCEPT
      {
        return value_;
      }

      //      year& operator++() BOOST_NOEXCEPT
      //      {
      //        ++value_;
      //        return *this;
      //      }
      //      year& operator--() BOOST_NOEXCEPT
      //      {
      //        --value_;
      //        return *this;
      //      }

      /**
       * @Return the number of days of this year.
       */
      days days_in() const BOOST_NOEXCEPT
      {
        return days(365+days::rep(is_leap()));
      }

      /**
       * @Return the number of days of the month parameter in this year.
       */
      days days_in(month m) const
BOOST_NOEXCEPT      ;

      /**
       * @Return the number of days since the epoch until the fist day of this year.
       */
      inline days days_since_epoch() const BOOST_NOEXCEPT
      {
        return days(days_before_year(value_));
      }

      /**
       * @Return whether this year is leap or not.
       */
      bool is_leap() const BOOST_NOEXCEPT
      {
        int32_t y = value_;
        return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
      }

      static BOOST_CONSTEXPR year zero()
      {
        return year(0);
      }
      static BOOST_CONSTEXPR year min BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
        return year(first_);
      }static BOOST_CONSTEXPR year max BOOST_PREVENT_MACRO_SUBSTITUTION ()
      {
        return year(last_);
      }

    private:
      rep value_;

    };

  } // chrono
} // boost


#endif  // header
