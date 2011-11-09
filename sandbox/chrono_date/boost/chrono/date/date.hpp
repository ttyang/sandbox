//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_TMP_DATE_HPP
#define BOOST_CHRONO_DATE_TMP_DATE_HPP


#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 | BOOST_CHRONO_DATE_DATE_DESIGN == 3
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
#include <boost/chrono/date/days_date.hpp>
#if defined BOOST_CHRONO_DATE_DATE_DESIGN_BUG
#include <boost/chrono/date/tmp/date.hpp>
#endif
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 4
#include <boost/chrono/date/ydoy_date.hpp>
#endif

namespace boost
{
  namespace chrono
  {

#if BOOST_CHRONO_DATE_DATE_DESIGN == 1 | BOOST_CHRONO_DATE_DATE_DESIGN == 3

    /**
     * A type representing the default date.
     */
    typedef ymd_date date;
//    /**
//     * A type representing an optional of the default date.
//     */
//    typedef optional_ymd_date optional_date;
//    /**
//     * @Returns If the parameters represents a valid date the date,
//     * otherwise a none optional.
//     */
//    inline optional_date make_valid_date(year y,month m,day d) BOOST_NOEXCEPT
//    {
//      return  make_valid_ymd_date(y,m,d);
//    }
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 2
#if ! defined BOOST_CHRONO_DATE_DATE_DESIGN_BUG
    typedef days_date date;
//    typedef optional_days_date optional_date;
//
//
//    inline optional_date make_valid_date(year y,month m,day d) BOOST_NOEXCEPT
//    {
//      return  make_valid_days_date(y,m,d);
//    }

#endif
#elif BOOST_CHRONO_DATE_DATE_DESIGN == 4
    typedef ydoy_date date;
//    typedef optional_ydoy_date optional_date;
//
//
//    inline optional_date make_valid_date(year y,month m,day d) BOOST_NOEXCEPT
//    {
//      return  make_valid_ydoy_date(y,m,d);
//    }
#endif

  } // chrono

} // boost


#endif  // header
