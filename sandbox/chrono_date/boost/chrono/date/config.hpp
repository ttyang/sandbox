//  config.hpp
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_CONFIG_HPP
#define BOOST_CHRONO_DATE_CONFIG_HPP

#include <boost/chrono/config.hpp>


// 1 => days +ymd +leap
// 2 => days
// 3 => ymd +leap
// 4 => ydoy +leap
#ifndef BOOST_CHRONO_DATE_DATE_DESIGN
#define BOOST_CHRONO_DATE_DATE_DESIGN 4
#endif

// 1 => days +ymd +leap
// 3 => ymd +leap
#ifndef BOOST_CHRONO_DATE_YMD_DATE_DESIGN
#define BOOST_CHRONO_DATE_YMD_DATE_DESIGN 3
#endif

// 1 => days +ymd +leap
// 2 => days
// 3 => ymd +leap
#ifndef BOOST_CHRONO_DATE_REL_DATE_DESIGN
#define BOOST_CHRONO_DATE_REL_DATE_DESIGN 2
#endif


//#define BOOST_CHRONO_DATE_DATE_DESIGN_BUG


#endif  // header
