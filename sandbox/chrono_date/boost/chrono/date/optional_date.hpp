//  date_generators.hpp
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_OPTIONAL_DATE_HPP
#define BOOST_CHRONO_DATE_OPTIONAL_DATE_HPP

#include <boost/chrono/date/config.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/optional.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * @Returns If the parameters represents a valid Date the Date,
     * otherwise a none optional.
     */

    template < typename Date>
    optional<Date> make_optional(year y, month m, day d)
    BOOST_NOEXCEPT
    {
      Date res;
      if (res.set_if_valid_date(y,m,d)) return optional<Date>(res);
      else return optional<Date>();
    }

    template < typename Date>
    optional<Date> make_optional(year y, day_of_year doy)
    BOOST_NOEXCEPT
    {
      Date res;
      if (res.set_if_valid_date(y,doy)) return optional<Date>(res);
      else return optional<Date>();
    }

  } // chrono

} // boost

#endif  // header
