//  hello_world.cpp  ----------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include <iostream>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/chrono/date/date_generators.hpp>
#include <boost/chrono/date.hpp>

int main()
{

    using std::cout;
    //using namespace boost;
    using namespace boost::chrono;
    typedef boost::chrono::high_resolution_clock Clock;
    typedef boost::chrono::duration<double,boost::micro> micros;

    std::cout << jan/day(2)/2011 << '\n';  // 2011-01-02
    std::cout << month(1,no_check)/day(2)/2011 << '\n';  // 2011-01-02
    std::cout << date(2011, 1, 2, no_check) << '\n';  // 2011-01-02
    std::cout << '\n';

    std::cout << jan/day(1)/2011 << '\n';  // 2011-01-02
    std::cout << jan/day(2)/2011 << '\n';  // 2011-01-02
    std::cout << feb/day(1)/2011 << '\n';  // 2011-01-02

    // Print Feb. 28 for each year in the decade
    for (date d = feb/day(28)/2010, e = feb/day(28)/2020; d <= e; d += years(1))
        std::cout << d << '\n';
    std::cout << '\n';


    // Print the day after Feb. 28 for each year in the decade
    for (date d = feb/day(28)/2010, e = feb/day(28)/2020; d <= e; d += years(1))
        std::cout << d + days(1) << '\n';
    std::cout << '\n';

    // Print the 28th of every month in 2011
    for (date d = jan/day(28)/2011, e = dec/day(28)/2011; d <= e; d += months(1))
        std::cout << d << '\n';
    std::cout << '\n';

    {
    // How many days between may/1/2011 and jan/1/2011?
    std::cout <<"How many days between may/1/2011 and jan/1/2011? "<<  (may/day(01)/2011 - jan/day(01)/2011) << '\n';  // x == 120

    std::cout << '\n';
    }

    {
    date dt = aug/day(16)/2011;
    int d = dt.get_day();   // d == 16
    int m = dt.get_month(); // m == 8
    int y = dt.get_year();  // y == 2011
    std::cout <<  dt << '\n';
    std::cout <<  y << " "  << m << " " << d << '\n';
    std::cout << '\n';
    }

    {
    date dt = aug/day(16)/2011;
    // ...
    // Create date with the same month and year but on the 5th
    date dt2 = dt.get_year()/dt.get_month()/5;  // aug/5/2011
    int d = dt.get_day();   // d == 5
    int m = dt.get_month(); // m == 8
    int y = dt.get_year();  // y == 2011
    std::cout <<  dt << '\n';
    std::cout <<  y << " "  << m << " " << d << '\n';
    std::cout << '\n';
    }

    {
      date dt = aug/day(16)/2011;
      // What day of the week is this?
      int wd = dt.get_weekday();  // 2 (Tuesday)
      std::cout <<  dt << '\n';
      std::cout <<  wd <<  '\n';
    }

    {
      std::cout << date_fmt("%a %b %e, %Y");
      // Print the odd fridays of every month in 2011
      for (date d = jan/day(28)/2011, e = dec/day(28)/2011; d <= e; d += months(1))
      {
          std::cout << d << '\n';             // first Friday of the month
      }
    }
    {
      Clock::time_point t0 = Clock::now();
      for (date d = feb/day(28)/2010, e = feb/day(28)/2020; d != e; d += years(1))
        ;
      Clock::time_point t1 = Clock::now();
      std::cout << "   iterate: " << micros(t1 - t0)  << "\n";
    }

    {
      date d1 =  jan/_2nd/2011;          // jan/2/2011
      date d2 =  year(2011)/jan/_2nd;    // jan/2/2011
      date d3 =  _2nd/jan/2011;          // jan/2/2011
      std::cout << d1 << '\n';
      std::cout << d2 << '\n';
      std::cout << d3 << '\n';
    }

    {
      date d1 = last/jan/2011;  // jan/31/2011
      std::cout << d1 << '\n';
    }

    {
//      date MothersDay = _sun[2]/may/2011;     // may/8/2011
//      date MothersDay2 = _sun[_2nd]/may/2011;  // may/8/2011
      date MothersDay2 = _2nd*sun/may/2011;  // may/8/2011
      std::cout <<"MothersDay "<< MothersDay2 << '\n';
    }

    {
//      date d1 = _fri[last]/may/2011;  // may/27/2011
      date d1 = last*fri/may/2011;  // may/27/2011
      std::cout << d1 << '\n';
    }

    {
//      int num_fri_in_may = (_fri[last]/may/2011).get_day() > 28 ? 5 : 4;  // 4
      int num_fri_in_may = (last*fri/may/2011).get_day() > 28 ? 5 : 4;  // 4
      std::cout <<"Number of fridays in May"<< num_fri_in_may << '\n';

//      date d1 = rel_weekday(5)[_1st]/may/2011;
      //rel_date d1 = _1st_week*weekday(5)/may/2011;
      rel_date d1 = _1st*fri/may/2011;
      std::cout << d1 << '\n';
     //date d2 = d1;
      //std::cout << d2 << '\n';

    }

    {
      // Print the last day in  Feb. for each year in the decade
      for (date d = feb/last/2010, e = feb/last/2020; d <= e; d += years(1))
          std::cout << d << '\n';
      std::cout << feb/last/2020 << '\n';
    }

//    {
//      // Print last day of every month in 2011
//      for (date d = jan/last/2011, e = dec/last/2011; d <= e; d += months(1))
//          std::cout << d << '\n';
//    }

    {
      rel_date d1 =  jan/_2nd/2011;          // jan/2/2011
      rel_date d2 =  year(2011)/jan/_2nd;    // jan/2/2011
      rel_date d3 =  _2nd/jan/2011;          // jan/2/2011

      std::cout << d1 << '\n';
      std::cout << d2 << '\n';
      std::cout << d3 << '\n';
    }
    {
      rel_date d1 = last/jan/2011;  // jan/31/2011
      std::cout << d1 << '\n';
    }
    {
      // Print the last day in  Feb. for each year in the decade
      for (rel_date d = feb/last/2010, e = feb/last/2020; d <= e; d += years(1))
      {
          std::cout << d << '\n';
      }
      std::cout << feb/last/2012 << '\n';
      std::cout << feb/last/2016 << '\n';
      std::cout << feb/last/2020 << '\n';
    }
    {
      // Print the 29th of every month in 2011
      for (rel_date d = last/jan/2011, e = last/dec/2011; d <= e; d += months(1))
      {
          if (d.get_day() >= 29)
              std::cout << d.get_year()/d.get_month()/29 << '\n';
      }
    }
    {
      // Print the 2nd Tuesday of every odd month in 2011
//      for (rel_date d = _tue[2]/jan/2011, e = dec/last/2011; d <= e; d += months(2))
      for (rel_date d = _2nd*tue/jan/2011, e = dec/last/2011; d <= e; d += months(2))
          std::cout << d << '\n';
    }
    {
      // Print out every monday between jan/1/2011 and mar/1/2011;
      //for (date d = _mon[_1st]/jan/2011, e = mar/_1st/2011; d <= e; d += days(7))
      for (date d = _1st*mon/jan/2011, e = mar/_1st/2011; d <= e; d += days(7))
          std::cout << d << '\n';
    }
    {
      // Print out the 1st and 3rd friday of the month from 1st/jan/2011 to last/dec/2011;
      for (rel_date d1 = _1st*fri/jan/2011, d3 = _3rd*fri/jan/2011, e = last/dec/2011; d1 <= e; d1 += months(1), d3 += months(1))
      {
        std::cout << d1 << '\n';
        std::cout << d3 << '\n';
      }
    }
    {
      date dt = aug/day(16)/2011;
      // ...
      // Get the date that is the first occurrence of the same day of the week
      //   in the same month of the next year
      //rel_date dt2 = dt.get_weekday()[_1st]/dt.get_month()/(dt.get_year() + 1);  // aug/7/2012, first Tuesday of Aug 2012
      rel_date dt2 = _1st*dt.get_weekday()/dt.get_month()/(dt.get_year() + 1);  // aug/7/2012, first Tuesday of Aug 2012
      std::cout << dt << '\n';
      std::cout << dt2 << '\n';
    }
    {
      date ISO_week_start = mon <= jan/day(4)/2012;
      std::cout << "ISO_week_start " << ISO_week_start << '\n';
    }

    {
      // How many weeks until Christmas?
      date dt = dec/day(25)/2011;
      days d=dt- date::today();
      std::cout << duration_cast<weeks>(d)<< '\n';
    }
    {
      // How many average months until Christmas?
      days d = (dec/day(25)/2011) - date::today();
      std::cout << duration_cast<average_months>(d)<< '\n';
    }
    {
      // How many weeks until Christmas?
      days d=(dec/day(25)>date::today())- date::today();
      std::cout << duration_cast<weeks>(d)<< '\n';
    }
    {
      std::cout << __FILE__<<"["<<__LINE__ <<"] "<< "How many days until next 28th?" << '\n';
      // How many days until next 28th?
      days d=(nth(28)>date::today())- date::today();
      std::cout << d << '\n';
    }
    {
      day::rep r = day(2) -day(6);
      std::cout << int(r) << '\n';
    }
    return 0;
}
