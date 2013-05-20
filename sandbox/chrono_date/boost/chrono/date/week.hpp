//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_WEEK_HPP
#define BOOST_CHRONO_DATE_WEEK_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/date/detail/bounded.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * day tag
     */
    struct week_tag {};
    /**
     * The class week is used to specify the week of the year. Its range is [1,53].
     */
    typedef bounded<week_tag, 1, 53> week;

    /**
     * week pseudo-literals.
     */
    extern const week
         w_01, w_02, w_03, w_04, w_05, w_06, w_07, w_08, w_09,
         w_10, w_11, w_12, w_13, w_14, w_15, w_16, w_17, w_18, w_19,
         w_20, w_21, w_22, w_23, w_24, w_25, w_26, w_27, w_28, w_29,
         w_30, w_31, w_32, w_33, w_34, w_35, w_36, w_37, w_38, w_39,
         w_40, w_41, w_42, w_43, w_44, w_45, w_46, w_47, w_48, w_49,
         w_50, w_51, w_52, w_53;

  } // chrono

} // boost

#endif  // header
