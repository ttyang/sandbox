//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_MONTH_NTH_HPP
#define BOOST_CHRONO_DATE_MONTH_NTH_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class @c month_nth is a tuple of @c month and @c nth that is useful when constructing dates.
     */
    class month_nth
    {
      month m_; // :4
      nth d_; // :6
    public:
      /**
       * @Effects: Constructs an object of class @c month_nth by storing @c m and @c d.
       * @Postconditions: get_month() == m && get_nth() == d && is_valid().
       * @Throws: if d is outside of the valid range of days of month @c m, throws an exception of type bad_date.
       */
      month_nth(month m, nth d)BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
        if (!(d_<= days_in_month(1,m_)))
        {
          throw bad_date("nth " + boost::chrono::to_string(int(d)) + "is out of range respect to month" + boost::chrono::to_string(m));
        }
      }
      /**
       * @Effects: Constructs an object of class @c month_nth by storing @c m and @c d.
       * @Postconditions: get_month() == m && get_nth() == d.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      month_nth(month::rep m, nth::rep d, no_check_t)BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      /**
       * @Return the @c month component.
       */
      month get_month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the @c nth component.
       */
      nth get_nth() const BOOST_NOEXCEPT
      {
        return d_;
      }
      /**
       * @Return if the stored value is a valid one.
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (m_.is_valid() && d_.is_valid() && d_<= days_in_month(1,m_));
      }
    };
    /**
     * @Return a the @c month_nth with the associated parameters.
     * @Throws if d is outside of the valid range of days of month @c m, throws an exception of type bad_date.
     */
    inline month_nth operator/(month m, nth d)
    BOOST_NOEXCEPT
    {
      return month_nth(m, d);
    }
    inline month_nth operator/(month m, last_t)
    BOOST_NOEXCEPT
    {
      return month_nth(m, nth(6,no_check));
    }
    inline month_nth operator/(month m, _1st_t) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(1,no_check));
    }
    inline month_nth operator/(month m, _2nd_t) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(2,no_check));
    }
    inline month_nth operator/(month m, _3rd_t) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(3,no_check));
    }
    inline month_nth operator/(month m, _4th_t) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(4,no_check));
    }
    inline month_nth operator/(month m, _5th_t) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(5,no_check));
    }
    /**
     * @Return a the @c month_nth with the associated parameters.
     * @Throws if d is outside of the valid range of days of month @c m, throws an exception of type bad_date.
     */
    inline month_nth operator/(nth d, month m)
BOOST_NOEXCEPT  {
    return month_nth(m, d);
  }
    inline month_nth operator/(last_t, month m)
BOOST_NOEXCEPT  {
    return month_nth(m, nth(6,no_check));
  }

    inline month_nth operator/(_1st_t, month m) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(1,no_check));
    }
    inline month_nth operator/(_2nd_t, month m) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(2,no_check));
    }
    inline month_nth operator/(_3rd_t, month m) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(3,no_check));
    }
    inline month_nth operator/(_4th_t, month m) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(4,no_check));
    }
    inline month_nth operator/(_5th_t, month m) BOOST_NOEXCEPT
    {
      return month_nth(m, nth(5,no_check));
    }


} // chrono

} // boost


#endif  // header
