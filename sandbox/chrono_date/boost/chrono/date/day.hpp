//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DAY_HPP
#define BOOST_CHRONO_DATE_DAY_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/chrono/date/nth_tag.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * day tag
     */
    struct day_tag {};

    namespace unchecked
    {
      class day: public bounded<day_tag, 1, 31, day_rep>
      {
        typedef bounded<day_tag, 1, 31, day_rep> base_type;
      public:
        /**
         * @Effects Constructs an object of class day by storing y.
         * @Postconditions <c>static_cast<rep>(*this) == v</c>.
         */
        BOOST_FORCEINLINE BOOST_CONSTEXPR explicit day(int v) BOOST_NOEXCEPT:
          base_type(v, no_check)
        {
        }
      };
      /**
       * synonym of day.
       */
      typedef day day_of_month;
    }
    /**
     * The class @c day is used to specify the day of the month when constructing dates. Its range is [1,31].
     */

    class day: public bounded<day_tag, 1, 31, day_rep>
    {
      typedef bounded<day_tag, 1, 31, day_rep> base_type;
    public:
      /**
       * @Effects Constructs an object of class day by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == y</c>.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit day(int v, no_check_t) BOOST_NOEXCEPT:
        base_type(v, no_check)
      {
      }
      /**
       * @Effects Constructs an object of class day by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == y</c>.
       * @Throws if @c v is outside of the range [1,31], throws an exception of type @c std::out_of_range.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit day(int v) :
        base_type(v, check)
      {
      }

      /**
       * @Effects Constructs an object of class day by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == v.value()</c>.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR day(nth_1_5_tag v) :
        base_type(v.value(), no_check)
      {
      }

      /**
       * @Effects Constructs an object of class day by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == v.value()</c>.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR day(nth_6_31_tag v) :
        base_type(v.value(), no_check)
      {
      }

      /**
       * @Effects Constructs an object of class day by storing y.
       * @Postconditions <c>static_cast<rep>(*this) == v.value()</c>.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR explicit day(unchecked::day v) :
        base_type(v.value(), check)
      {
      }

      /**
       * Explicit
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR operator unchecked::day() BOOST_NOEXCEPT
      {
        return unchecked::day(value());
      }

    };
    /**
     * synonym of day.
     */
    typedef day day_of_month;


  } // chrono
} // boost

#endif  // header
