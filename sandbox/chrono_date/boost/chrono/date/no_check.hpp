//  date
//
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NO_CHECK_HPP
#define BOOST_CHRONO_DATE_NO_CHECK_HPP

#include <boost/chrono/date/config.hpp>

namespace boost
{
  namespace chrono
  {

    struct no_check_t
    {};
    BOOST_CONSTEXPR_OR_CONST no_check_t no_check =
    {};

    struct check_t
    {};
    BOOST_CONSTEXPR_OR_CONST check_t check =
    {};


  } // chrono

} // boost

#endif  // header
