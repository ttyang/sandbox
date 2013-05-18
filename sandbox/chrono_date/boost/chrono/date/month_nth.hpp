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
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/exceptions.hpp>
#include <boost/chrono/date/detail/to_string.hpp>
#include <boost/chrono/date/detail/helpers.hpp>
#include <boost/throw_exception.hpp>

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
       * @Effects Constructs an object of class @c month_nth by storing @c m and @c d.
       * @Postconditions month() == m && nth() == d && is_valid().
       * @Throws: if d is outside of the valid range of days of month @c m, throws an exception of type bad_date.
       */
      month_nth(month m, nth d, check_t)
      : m_(m),
      d_(d)
      {
        if (!(is_valid()))
        {
          throw_exception( bad_date("nth " + boost::chrono::to_string(int(d)) + "is out of range respect to month" + boost::chrono::to_string(m)) );
        }
      }
      /**
       * @Effects Constructs an object of class @c month_nth by storing @c m and @c d.
       * @Postconditions month() == m && nth() == d.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide the valid ones.
       */
      BOOST_CONSTEXPR month_nth(month m, nth d) BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      /**
       * @Return the @c month component.
       */
      //BOOST_CONSTEXPR month month() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_CONSTEXPR operator chrono::month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the @c nth component.
       */
      //BOOST_CONSTEXPR nth nth() const BOOST_NOEXCEPT
      BOOST_CHRONO_EXPLICIT BOOST_CONSTEXPR operator chrono::nth() const BOOST_NOEXCEPT
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
    inline BOOST_CONSTEXPR month_nth operator/(chrono::month m, nth d)
    BOOST_NOEXCEPT
    {
      return month_nth(m, d);
    }

    /**
     * @Returns the @c month_nth with the associated parameters.
     * @Throws if @c d is outside of the valid range of days of month @c m, throws an exception of type bad_date.
     */
    inline BOOST_CONSTEXPR month_nth operator/(nth d, chrono::month m)
BOOST_NOEXCEPT  {
    return month_nth(m, d);
  }


} // chrono

} // boost


#endif  // header
