//  date
//
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_DAY_OF_YEAR_HPP
#define BOOST_CHRONO_DATE_DATE_DAY_OF_YEAR_HPP

#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * day_of_year tag
     */
    struct day_of_year_tag
    {
    };

    /**
     * The class day_of_year is used to specify the day of the year when constructing a date. Its range is [1,366].
     */
    typedef bounded<day_of_year_tag, 1, 366, day_of_year_rep> day_of_year;

  } // chrono

} // boost

#endif  // header

