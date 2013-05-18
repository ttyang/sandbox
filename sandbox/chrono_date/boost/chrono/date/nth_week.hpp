//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_WEEK_HPP
#define BOOST_CHRONO_DATE_NTH_WEEK_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>
#include <boost/chrono/date/nth.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * nth_week tag
     */
    struct nth_week_tag {};

    /**
     * The class nth_week is used to specify a small integral value that indicates the nth week of the month
     * (example: last_week, 1st_week).  Its range is [1,6].
     */
    class nth_week : public bounded<nth_week_tag, 1, 6, int_least8_t>
    {
      typedef bounded<nth_week_tag, 1, 6, int_least8_t> base_type;

    public:
      BOOST_STATIC_CONSTEXPR rep not_applicable=7;
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_week() : base_type(not_applicable) {}

      /**
       * @Effects Constructs an object of class @c nth_week by storing @c s.
       * Throws: if @c s is outside of the range [1, 6], throws an exception of type bad_date.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_week(int s, check_t) : base_type(s, check)
      {}
      /**
       * @Effects Constructs an object of class @c nth_week by storing @c s.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_week(int s) BOOST_NOEXCEPT
          : base_type(s)
      {}
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_week(nth_tag s) BOOST_NOEXCEPT
          : base_type(s.value_)
      {}

      BOOST_FORCEINLINE BOOST_CONSTEXPR bool is_not_applicable() const BOOST_NOEXCEPT
      {
        return value()==not_applicable;
      }
    };

  } // chrono

} // boost

#endif  // header
