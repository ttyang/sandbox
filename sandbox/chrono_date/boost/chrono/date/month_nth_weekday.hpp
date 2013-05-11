//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_MONTH_NTH_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_MONTH_NTH_WEEKDAY_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/nth.hpp>
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
//       * @Effects: Constructs an object of class @c month_nth_weekday by storing @c m and @c nwd.
//       * @Postconditions: month() == m && nth_weekday() == nwd && is_valid().
//       */
//      month_nth_weekday(month m, nth_weekday nwd, check_t) BOOST_NOEXCEPT
//      : m_(m, check),
//      d_(nwd, check)
//      {
//        // There is no bad combination, so no exception is thrown
//      }
      /**
       * @Effects: Constructs an object of class @c month_nth_weekday by storing @c m and @c nwd.
       * @Postconditions: month() == m && nth_weekday() == nwd.
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
      BOOST_CHRONO_EXPLICT BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the @c nth_weekday component.
       */
      //BOOST_CONSTEXPR nth_weekday nth_weekday() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICT BOOST_CONSTEXPR operator chrono::nth_weekday() const BOOST_NOEXCEPT
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
    inline BOOST_CONSTEXPR month_nth_weekday operator/(month m, nth_weekday d) BOOST_NOEXCEPT
    {
      return month_nth_weekday(m, d);
    }
    /**
     * @return a @c month_nth_weekday build with the given parameters.
     */
    inline BOOST_CONSTEXPR month_nth_weekday operator/(nth_weekday d, month m) BOOST_NOEXCEPT
    {
      return month_nth_weekday(m, d);
    }

    /**
     *
     * The class dom is used to specify a small integral value that indicates the nth day of the month (example: last, 1st).
     * valid from -32..31,
     * 1..31 means the nth day of the month,
     * 0 means last and
     * -30..-1 means last but -nth.
     * -32 means not_applicable
     */
    class dom
    {
    public:
      typedef int_least8_t rep;
      static const rep not_applicable=-31;

      BOOST_CONSTEXPR dom(rep s) BOOST_NOEXCEPT : value_(s)
      {
      }
      BOOST_CONSTEXPR rep value() const BOOST_NOEXCEPT
      {
        return value_;
      }
      BOOST_CONSTEXPR bool is_not_applicable() const BOOST_NOEXCEPT
      {
        return value_==not_applicable;
      }
    private:
      rep value_; // :6 bits
    };

    class month_dom
    {
      month m_; // :4
      dom d_; // :6
    public:
      BOOST_CONSTEXPR month_dom(month m, dom d) BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      //month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICT BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      //BOOST_CONSTEXPR dom dom() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICT BOOST_CONSTEXPR operator chrono::dom() const BOOST_NOEXCEPT
      {
        return d_;
      }
    };

    inline BOOST_CONSTEXPR month_dom operator/(month m, dom d) BOOST_NOEXCEPT
    {
      return month_dom(m, d);
    }
    inline BOOST_CONSTEXPR month_dom operator/(dom d, month m) BOOST_NOEXCEPT
    {
      return month_dom(m, d);
    }



  } // chrono

} // boost

#endif  // header
