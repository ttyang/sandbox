//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_YEAR_HPP
#define BOOST_CHRONO_DATE_YEAR_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/date_durations.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * year tag
     */
    struct year_tag
    {
    };

    /**
     * The class year is used to specify the year when constructing a date.
     * It also defines the range of the date class by restricting the value of
     * the year to a range.
     *
     * That range shall be at least [year(-32767)/jan/1 thru year(32767)/dec/31]. Its range is [-32768, 32767].
     */
    class year: public bounded<year_tag, -32768, 32767, year_rep>
    {
      typedef bounded<year_tag, -32768, 32767, year_rep> base_type;
    public:
      /**
       * @Effects Constructs an object of class year by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == y</c>.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit year(int v) :
        base_type(v)
      {
      }

//      /**
//       * @Effects Constructs an object of class year by storing y.
//       * @Postconditions static_cast<int>(*this) == y.
//       * @Throws if y is outside of the supported range, throws an exception of type bad_date.
//       */
//      BOOST_FORCEINLINE BOOST_CONSTEXPR year(int y, check_t) BOOST_NOEXCEPT
//      : base_type(y, check)
//      {}

      /**
       * @Returns the number of days of this year.
       *
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR days days_in() const BOOST_NOEXCEPT
      {
        return days(365+days::rep(is_leap()));
      }

      /**
       * @Returns the number of days of the month @m parameter in this year.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR days days_in_month(month m) const BOOST_NOEXCEPT
      {
        return m.days_in(is_leap());
      }
      /**
       * @Returns the number of days of the month @m parameter in this year.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR days days_in_month(unchecked::month m) const BOOST_NOEXCEPT
      {
        return m.days_in(is_leap());
      }
      /**
       * @Returns the number of days since the epoch until the first day of this year.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR days days_since_epoch() const BOOST_NOEXCEPT
      {
        return days(days_before_year(value()));
      }

      /**
       * @Returns whether this year is leap or not.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_leap() const BOOST_NOEXCEPT
      {
        return chrono::is_leap(value());
      }

      static BOOST_FORCEINLINE BOOST_CONSTEXPR year zero() BOOST_NOEXCEPT
      {
        return year(0);
      }
    };

  } // chrono
} // boost


#endif  // header
