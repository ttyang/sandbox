//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DAY_HPP
#define BOOST_CHRONO_DATE_DAY_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>

namespace boost
{
  namespace chrono
  {
    /**
     * day tag
     */
    struct day_tag {};
    /**
     * The class @c day is used to specify the day of the month when constructing dates. Its range is [1,31].
     */
    typedef bounded<day_tag, 1, 31, int_least8_t> day;

    /**
     * synonym of day.
     */
    typedef day day_of_month;

  } // chrono
} // boost

#endif  // header
