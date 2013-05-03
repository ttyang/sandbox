//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_HPP
#define BOOST_CHRONO_DATE_NTH_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * nth tag
     */
    struct nth_tag {};

    /**
     * The class nth is used to specify a small integral value that indicates the nth day of the month (example: last, 1st).
     * Its range is [1, 6].
     */
    class nth: public bounded<nth_tag, 1, 6, int_least8_t>
    {
      typedef bounded<nth_tag, 1, 6, int_least8_t> base_type;

    public:
      BOOST_STATIC_CONSTEXPR rep not_applicable=7;
      /**
       * @Effects: Constructs an object of class @c nth by storing @c s.
       * Throws: if @c s is outside of the range [1, 6], throws an exception of type bad_date.
       */
      BOOST_CONSTEXPR nth(irep s) : base_type(s)
      {}
      /**
       * @Effects: Constructs an object of class @c nth by storing @c s.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_CONSTEXPR nth(irep s, no_check_t) BOOST_NOEXCEPT
          : base_type(s, no_check)
      {}

      BOOST_CONSTEXPR bool is_not_applicable() const BOOST_NOEXCEPT
      {
        return value()==not_applicable;
      }
    };

    struct last_t {};
    BOOST_CONSTEXPR_OR_CONST last_t last = {};
    struct _1st_t {};
    BOOST_CONSTEXPR_OR_CONST _1st_t _1st = {};
    struct _2nd_t {};
    BOOST_CONSTEXPR_OR_CONST _2nd_t _2nd = {};
    struct _3rd_t {};
    BOOST_CONSTEXPR_OR_CONST _3rd_t _3rd = {};
    struct _4th_t {};
    BOOST_CONSTEXPR_OR_CONST _4th_t _4th = {};
    struct _5th_t {};
    BOOST_CONSTEXPR_OR_CONST _5th_t _5th = {};



  } // chrono

} // boost

#endif  // header
