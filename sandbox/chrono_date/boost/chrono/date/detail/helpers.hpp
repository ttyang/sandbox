//  days_date.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_HELPERS_HPP
#define BOOST_CHRONO_DATE_HELPERS_HPP

#include <boost/cstdint.hpp>

namespace boost
{
  namespace chrono
  {
    typedef boost::int_least64_t days_rep;
    typedef int day_rep;
    typedef int month_rep;
    typedef int day_of_year_rep;
    typedef boost::int_least32_t year_rep;
//#ifdef __clang__
//    typedef boost::int_least32_t day_rep;
//    typedef boost::int_least32_t month_rep;
//    typedef boost::int_least32_t day_of_year_rep;
//    typedef boost::int_least32_t year_rep;
//#else
//    typedef boost::int_least32_t day_rep;
//    typedef boost::int_least32_t month_rep;
//    typedef boost::int_least32_t day_of_year_rep;
//    typedef boost::int_least32_t year_rep;
//#endif
    BOOST_FORCEINLINE BOOST_CONSTEXPR bool
    is_leap(year_rep y)
    BOOST_NOEXCEPT
    {
      return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR days_rep days_before_year(year_rep y)
    {
      return y * 365 + y / 4 - y / 100 + y / 400;
    }

    BOOST_FORCEINLINE BOOST_CONSTEXPR year_rep
    to_average_year(days_rep ds)
    BOOST_NOEXCEPT
    {
      return static_cast<year_rep>(static_cast<int64_t>(ds+2) * 400 / 146097);
    }

    //BOOST_CONSTEXPR
    day_rep days_in_month(bool, month_rep)
    BOOST_NOEXCEPT;
    //BOOST_CONSTEXPR
    day_of_year_rep days_in_year_before(bool, month_rep)
    BOOST_NOEXCEPT;
    //BOOST_CONSTEXPR
    const day_of_year_rep* days_in_year_before(bool)
    BOOST_NOEXCEPT;
    //BOOST_CONSTEXPR
    month_rep day_of_year_month(bool, day_of_year_rep)
    BOOST_NOEXCEPT;
    //BOOST_CONSTEXPR
    day_rep day_of_year_day_of_month(bool, day_of_year_rep)
    BOOST_NOEXCEPT;
    //BOOST_CONSTEXPR
    day_of_year_rep month_day_to_day_of_year(bool, month_rep, day_rep)
BOOST_NOEXCEPT  ;

  } // chrono
} // boost

#endif

