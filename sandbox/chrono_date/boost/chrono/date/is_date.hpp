//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_IS_DATE_HPP
#define BOOST_CHRONO_DATE_IS_DATE_HPP


#include <boost/chrono/date/config.hpp>
#include <boost/type_traits/integral_constant.hpp>


namespace boost
{
  namespace chrono
  {

    /*
     * Trait type for Date classes.
     */template <typename Date>
    struct is_date : false_type {};


  } // chrono

} // boost


#endif  // header
