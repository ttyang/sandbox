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
#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/detail/bounded.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * nth tag
     */
    struct nth_tag
    {
      const int value_;
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_tag(int v) BOOST_NOEXCEPT
      : value_(v)
      {}
    };

    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, last, 0);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, _1st, 1);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, _2nd, 2);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, _3rd, 3);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, _4th, 4);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, _5th, 5);

    /**
     * The class nth is used to specify a small integral value that indicates the nth day of the month (example: last, 1st).
     * Its range is [1, 6].
     */
    class nth: public bounded<nth_tag, 1, 6>
    {
      typedef bounded<nth_tag, 1, 6> base_type;

    public:
      BOOST_STATIC_CONSTEXPR rep not_applicable=7;
      /**
       * @Effects Constructs an object of class @c nth by storing @c s.
       * Throws: if @c s is outside of the range [1, 6], throws an exception of type bad_date.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth(int s, check_t) : base_type(s, check)
      {}
      /**
       * @Effects Constructs an object of class @c nth by storing @c s.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth(int s) BOOST_NOEXCEPT
          : base_type(s)
      {}

      BOOST_FORCEINLINE BOOST_CONSTEXPR nth(nth_tag s) BOOST_NOEXCEPT
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
