//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_MONTH_NTH_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_MONTH_NTH_WEEKDAY_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/no_check.hpp>
//#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/nth_weekday.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class @c month_nth_weekday is a tuple of @c month and @c nth_weekday that is useful when constructing dates.
     */
    class month_nth_weekday
    {
      month m_; // :4
      nth_weekday d_; // :6
    public:
//      /**
//       * @Effects Constructs an object of class @c month_nth_weekday by storing @c m and @c nwd.
//       * @Postconditions month() == m && nth_weekday() == nwd && is_valid().
//       */
//      month_nth_weekday(month m, nth_weekday nwd, check_t) BOOST_NOEXCEPT
//      : m_(m, check),
//      d_(nwd, check)
//      {
//        // There is no bad combination, so no exception is thrown
//      }
      /**
       * @Effects Constructs an object of class @c month_nth_weekday by storing @c m and @c nwd.
       * @Postconditions month() == m && nth_weekday() == nwd.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_CONSTEXPR month_nth_weekday(month::rep m, nth_weekday d) BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      /**
       * @Return the @c month component.
       */
      //month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the @c nth_weekday component.
       */
      //BOOST_CONSTEXPR nth_weekday nth_weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_CONSTEXPR operator chrono::nth_weekday() const BOOST_NOEXCEPT
      {
        return d_;
      }
      /**
       * @Return if the stored value is a valid one.
       */
      BOOST_CONSTEXPR  bool is_valid() const BOOST_NOEXCEPT
      {
        return ( m_.is_valid() &&  d_.is_valid() );
      }
    };

    /**
     * @return a @c month_nth_weekday build with the given parameters.
     */
    BOOST_FORCEINLINE BOOST_CONSTEXPR month_nth_weekday operator/(month m, nth_weekday d) BOOST_NOEXCEPT
    {
      return month_nth_weekday(m, d);
    }
    /**
     * @return a @c month_nth_weekday build with the given parameters.
     */
    BOOST_FORCEINLINE BOOST_CONSTEXPR month_nth_weekday operator/(nth_weekday d, month m) BOOST_NOEXCEPT
    {
      return month_nth_weekday(m, d);
    }

    /**
     * The class @c month_nth_weekday is a tuple of @c month and @c nth_weekday that is useful when constructing dates.
     */
    class month_last_weekday
    {
      month m_; // :4
      last_weekday d_; // :6
    public:
      /**
       * @Effects Constructs an object of class @c month_last_weekday by storing @c m and @c nwd.
       * @Postconditions month() == m && last_weekday() == nwd.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR month_last_weekday(month::rep m, last_weekday d) BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      /**
       * @Return the @c month component.
       */
      //month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the @c last_weekday component.
       */
      //BOOST_CONSTEXPR last_weekday last_weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_FORCEINLINE BOOST_CONSTEXPR operator chrono::last_weekday() const BOOST_NOEXCEPT
      {
        return d_;
      }
      /**
       * @Return if the stored value is a valid one.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR  bool is_valid() const BOOST_NOEXCEPT
      {
        return ( m_.is_valid() &&  d_.is_valid() );
      }
    };

    /**
     * @return a @c month_last_weekday build with the given parameters.
     */
    BOOST_FORCEINLINE BOOST_CONSTEXPR month_last_weekday operator/(month m, last_weekday d) BOOST_NOEXCEPT
    {
      return month_last_weekday(m, d);
    }
    /**
     * @return a @c month_last_weekday build with the given parameters.
     */
    BOOST_FORCEINLINE BOOST_CONSTEXPR month_last_weekday operator/(last_weekday d, month m) BOOST_NOEXCEPT
    {
      return month_last_weekday(m, d);
    }

  } // chrono

} // boost

#endif  // header
