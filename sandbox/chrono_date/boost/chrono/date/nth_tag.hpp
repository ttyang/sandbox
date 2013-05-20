//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_TAG_HPP
#define BOOST_CHRONO_DATE_NTH_TAG_HPP

#include <boost/chrono/date/config.hpp>

namespace boost
{
  namespace chrono
  {

    struct last_tag {};
    BOOST_CONSTEXPR_OR_CONST last_tag last = {};

    /**
     * nth 1..5 tag
     */
    struct nth_1_5_tag
    {
      const int value_;
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_1_5_tag(int v) BOOST_NOEXCEPT
      : value_(v)
      {}
      BOOST_FORCEINLINE BOOST_CONSTEXPR int value() BOOST_NOEXCEPT {return value_;};
    };
    /**
     * nth 6..31 tag
     */
    struct nth_6_31_tag
    {
      const int value_;
      BOOST_FORCEINLINE BOOST_CONSTEXPR nth_6_31_tag(int v) BOOST_NOEXCEPT
      : value_(v)
      {}
      BOOST_FORCEINLINE BOOST_CONSTEXPR int value() BOOST_NOEXCEPT {return value_;};

    };
    //BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_tag, last, 0);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_1_5_tag, _1st, 1);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_1_5_tag, _2nd, 2);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_1_5_tag, _3rd, 3);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_1_5_tag, _4th, 4);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_1_5_tag, _5th, 5);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _6th, 6);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _7th, 7);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _8th, 8);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _9th, 9);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _10th, 10);
    BOOST_CONSTEXPR_OR_EXTERN_CONST_DCL(nth_6_31_tag, _29th, 29);

  } // chrono

} // boost

#endif  // header
