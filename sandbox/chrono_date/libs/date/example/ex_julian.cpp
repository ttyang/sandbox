//  ex_julian.cpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <iostream>
#include <boost/chrono/date/date_io.hpp>
#include "julian.hpp"

int main()
{
    std::cout << boost::chrono::date_fmt("%a %b %e, %Y");
    boost::chrono::date cd = boost::chrono::date::today();
    julian::date jd(cd);
    std::cout << "Today is:\n"
              << cd << " in the boost::chrono calendar and\n"
              << jd << " in the Julian calendar\n";
    jd -= julian::years(1800);
    cd = boost::chrono::date(jd);
    std::cout << "1800 years ago the two calendars were aligned:\n"
              << cd << " in the boost::chrono calendar and\n"
              << jd << " in the Julian calendar\n";

    return 0;
}

//Today is:
//Wed Oct 12, 2011 in the boost::chrono calendar and
//Wed Sep 29, 2011 in the Julian calendar
//1800 years ago the two calendars were aligned:
//Sun Sep 29, 0211 in the boost::chrono calendar and
//Sun Sep 29, 0211 in the Julian calendar

