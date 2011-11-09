//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/chrono_io.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{

  using std::cout;
  using namespace boost;
  using namespace boost::chrono;

  typedef boost::chrono::high_resolution_clock Clock;
  typedef boost::chrono::duration<double, boost::micro> micros;

  { // construct from ymd: 0/1/1
    ydoy_date dt(year(0),jan,day(1));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.days_since_epoch().count()==11979588);
  }
  { // unchecked construct from bad ymd: 0/0/0 results in valid date
    ydoy_date dt(0,0,0,no_check);
    std::cout <<"0/0/0 days "<< dt.days_since_epoch().count() << std::endl;
    BOOST_TEST( ! dt.is_valid());
  }
  { // unchecked construct from bad ymd: 0/0/0 results in valid date
    ydoy_date dt(40000,1,1,no_check);
    BOOST_TEST( ! year(40000,no_check).is_valid());
    //BOOST_TEST( ! dt.is_valid());
  }
  { // bad construction from bad days: 0
    try {
      ydoy_date dt(days(0));
      BOOST_TEST( false );
    } catch (...) {}
  }
  std::cout <<"******* "<<  std::endl;

  { // construct from days: 0/1/1
    ydoy_date dt(days(11979588));
    std::cout <<dt<<  std::endl;
    std::cout <<"******* "<<  std::endl;
    std::cout <<dt.days_since_epoch().count()<<  std::endl;

    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.days_since_epoch().count()==11979588);
    BOOST_TEST(dt.get_year()==0);
    BOOST_TEST(dt.get_month()==1);
    BOOST_TEST(dt.get_day()==1);
  }
  { // default constructor
    ydoy_date dt;
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==0);
    BOOST_TEST(dt.get_month()==1);
    BOOST_TEST(dt.get_day()==1);
  }
  { // construct from ymd: 2011/oct/22
    ydoy_date dt(year(2011),oct,day(22));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  { // no_check construct from bad ymd: 2011/oct/22
    ydoy_date dt(2011,10,22, no_check);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  { // construct from ymd: 2011/jan_01
    ydoy_date dt(year(2011),jan_01);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // no_check construct from ymd: 2011/jan_01
    ydoy_date dt(2011,jan_01, no_check);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // construct from ymd: first day: -32768/jan_01
    ydoy_date dt(year(-32768),jan_01);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==-32768);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
    BOOST_TEST(dt.days_since_epoch().count()==11322);

    std::cout <<"-32768/jan/01 days "<< dt.days_since_epoch().count() << std::endl;
  }
  { // construct from ymd: last day: 32767/dec/31
    ydoy_date dt(year(32767),dec,day(31));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==32767);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
    BOOST_TEST(dt.days_since_epoch().count()==23947853);
    std::cout <<"32767/12/31 days "<< dt.days_since_epoch().count() << std::endl;
  }
  { // construct from days: first day: -32768/jan_01
    ydoy_date dt(days(11322));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==-32768);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);

  }
  { // construct from days: last day: 32767/dec/31
    ydoy_date dt(days(23947853));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==32767);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }


  { // construct from year + doy:
    ydoy_date dt(year(2011), day_of_year(1));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }

  { // construct from year + doy:
    ydoy_date dt(year(2011), day_of_year(365));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }
  { // construct from year + doy:
    BOOST_TEST( year(2012).is_leap());
    ydoy_date dt(year(2012), day_of_year(366));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }

  { // construct from bad (year + doy):
    try {
    ydoy_date dt(year(2011), day_of_year(366));
    BOOST_TEST(  false );
    } catch (...) {}
  }

  // TODO Add construct from year + week + weekday

  { // construct from today
    ydoy_date dt = ydoy_date::today();
    BOOST_TEST( dt.is_valid());
  }
  { // conversions to/from system_clock::time_point
    ydoy_date dt(2011,10,22, no_check);
    boost::chrono::system_clock::time_point tp=boost::chrono::system_clock::time_point(dt);
    ydoy_date dt2(tp);
    BOOST_TEST( dt == dt2);
  }
  // is_leap_year
  {
    ydoy_date dt(2011,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    ydoy_date dt(0,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    ydoy_date dt(4,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    ydoy_date dt(400,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    ydoy_date dt(100,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    ydoy_date dt(200,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    ydoy_date dt(300,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  // get_weekday
  {
    BOOST_TEST( ydoy_date(2011,10,23, no_check).get_weekday()==sun);
    BOOST_TEST( ydoy_date(2011,10,24, no_check).get_weekday()==mon);
    BOOST_TEST( ydoy_date(2011,10,25, no_check).get_weekday()==tue);
    BOOST_TEST( ydoy_date(2011,10,26, no_check).get_weekday()==wed);
    BOOST_TEST( ydoy_date(2011,10,27, no_check).get_weekday()==thu);
    BOOST_TEST( ydoy_date(2011,10,28, no_check).get_weekday()==fri);
    BOOST_TEST( ydoy_date(2011,10,29, no_check).get_weekday()==sat);
  }
  // day based arithmetic
  { //+=
    ydoy_date dt(days(1000000));
    dt+=days(10);
    BOOST_TEST( dt.days_since_epoch()==days(1000010));
  }
  { // += feb/28 no leap
    ydoy_date dt(year(2011),feb,day(28));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==mar);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += feb/28 leap
    ydoy_date dt(year(2012),feb,day(28));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  { // += feb/29 leap
    ydoy_date dt(year(2012),feb,day(29));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==mar);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += month change
    ydoy_date dt(year(2011),oct,day(22));
    dt+=days(10);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += month+year change
    ydoy_date dt(year(2011),dec,day(22));
    dt+=days(10);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // dt++
    ydoy_date dt(days(1000000));
    ydoy_date dt2= dt++;
    BOOST_TEST(  dt.days_since_epoch()==days(1000001));
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  { // ++dt
    ydoy_date dt(days(1000000));
    ydoy_date dt2 = ++dt;
    BOOST_TEST(  dt.days_since_epoch()==days(1000001));
    BOOST_TEST( dt2.days_since_epoch()==days(1000001));
  }

  { // -=
    ydoy_date dt(days(1000010));
    dt-=days(10);
    BOOST_TEST( dt.days_since_epoch()==days(1000000));
  }
  { // dt--
    ydoy_date dt(days(1000001));
    ydoy_date dt2= dt--;
    BOOST_TEST(  dt.days_since_epoch()==days(1000000));
    BOOST_TEST( dt2.days_since_epoch()==days(1000001));
  }
  { // --dt
    ydoy_date dt(days(1000001));
    ydoy_date dt2 = --dt;
    BOOST_TEST(  dt.days_since_epoch()==days(1000000));
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  { // -= month + year change
    ydoy_date dt(year(2011),jan,day(10));
    dt-=days(10);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }

  { // -= month change
    ydoy_date dt(year(2011),oct,day(10));
    dt-=days(10);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==30);
  }
  {
    ydoy_date dt(year(2011),mar,day(1));
    dt-=days(1);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==28);
  }
  {
    ydoy_date dt(year(2012),mar,day(1));
    dt-=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }

  {
    ydoy_date dt(days(1000000));
    ydoy_date dt2=dt+days(10);
    BOOST_TEST( dt2.days_since_epoch()==days(1000010));
  }
  {
    ydoy_date dt(days(1000000));
    ydoy_date dt2=days(10)+dt;
    BOOST_TEST( dt2.days_since_epoch()==days(1000010));
  }
  {
    ydoy_date dt(days(1000010));
    ydoy_date dt2=dt-days(10);
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  {
    ydoy_date dt(days(1000010));
    ydoy_date dt2(days(1000000));
    BOOST_TEST( dt-dt2==days(10));
  }
  {
    ydoy_date dt(days(1000010));
    ydoy_date dt2(days(1000000));
    BOOST_TEST( dt2-dt==days(-10));
  }
  // month based arithmetic
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt+=months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt = dt + months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt = months(1) + dt;

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt+=months(3);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),jan,day(29));
    try {
      dt+=months(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    ydoy_date dt(year(2012),jan,day(29));
    dt+=months(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()=feb);
    BOOST_TEST(dt.get_day()==29);
  }

  {
    ydoy_date dt(year(2011),oct,day(22));
    dt-=months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2012),mar,day(22));
    dt-=months(3);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt= dt-months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==22);
  }

  // year based arithmetic
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt+=years(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2012),feb,day(29));
    dt+=years(4);
    BOOST_TEST(dt.get_year()==2016);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  {
    ydoy_date dt(year(2012),feb,day(29));
    try {
      dt+=years(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt = dt + years(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt = years(1) + dt;
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt-=years(1);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    ydoy_date dt(year(2012),feb,day(29));
    dt-=years(4);
    BOOST_TEST(dt.get_year()==2008);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  {
    ydoy_date dt(year(2012),feb,day(29));
    try {
      dt-=years(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    ydoy_date dt(year(2011),oct,day(22));
    dt = dt - years(1);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  // TODO add exceptional cases bad result year

  // Relational operators
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt1 == dt2 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt1 >= dt2 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt2 <= dt2 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 >= dt2 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 > dt2 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt2 <= dt1 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt2 < dt1 );
  }
  {
    ydoy_date dt1(year(2011),oct,day(22));
    ydoy_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 != dt2 );
  }

  // optional
  {
    optional<ydoy_date> odt = make_optional<ydoy_date>(year(2011),oct,day(22));
    BOOST_TEST( odt );
  }
  {
    optional<ydoy_date> odt = make_optional<ydoy_date>(year(2011),nov,day(31));
    BOOST_TEST( ! odt );
  }


#if 0
  std::cout << jan / day(2) / 2011 << '\n'; // 2011-01-02
  std::cout << month(1, no_check) / day(2) / 2011 << '\n'; // 2011-01-02
  std::cout << ydoy_date(2011, 1, 2, no_check) << '\n'; // 2011-01-02
  std::cout << '\n';

  std::cout << jan / day(1) / 2011 << '\n'; // 2011-01-02
  std::cout << jan / day(2) / 2011 << '\n'; // 2011-01-02
  std::cout << feb / day(1) / 2011 << '\n'; // 2011-01-02

  // Print Feb. 28 for each year in the decade
  for (ydoy_date d = feb / day(28) / 2010, e = feb / day(28) / 2020; d <= e; d
      += years(1))
    std::cout << d << '\n';
  std::cout << '\n';

  // Print the day after Feb. 28 for each year in the decade
  for (ydoy_date d = feb / day(28) / 2010, e = feb / day(28) / 2020; d <= e; d
      += years(1))
    std::cout << d + days(1) << '\n';
  std::cout << '\n';

  // Print the 28th of every month in 2011
  for (ydoy_date d = jan / day(28) / 2011, e = dec / day(28) / 2011; d <= e; d
      += months(1))
    std::cout << d << '\n';
  std::cout << '\n';

  {
    // How many days between may/1/2011 and jan/1/2011?
    std::cout << "How many days between may/1/2011 and jan/1/2011? " << (may
        / day(01) / 2011 - jan / day(01) / 2011) << '\n'; // x == 120

    std::cout << '\n';
  }

  {
    ydoy_date dt = aug / day(16) / 2011;
    int d = dt.get_day(); // d == 16
    int m = dt.get_month(); // m == 8
    int y = dt.get_year(); // y == 2011
    std::cout << dt << '\n';
    std::cout << y << " " << m << " " << d << '\n';
    std::cout << '\n';
  }

  {
    ydoy_date dt = aug / day(16) / 2011;
    // ...
    // Create ydoy_date with the same month and year but on the 5th
    ydoy_date dt2 = dt.get_year() / dt.get_month() / 5; // aug/5/2011
    int d = dt.get_day(); // d == 5
    int m = dt.get_month(); // m == 8
    int y = dt.get_year(); // y == 2011
    std::cout << dt << '\n';
    std::cout << y << " " << m << " " << d << '\n';
    std::cout << '\n';
  }

  {
    ydoy_date dt = aug / day(16) / 2011;
    // What day of the week is this?
    int wd = dt.get_weekday(); // 2 (Tuesday)
    std::cout << dt << '\n';
    std::cout << wd << '\n';
  }

  {
    std::cout << date_fmt("%a %b %e, %Y");
    // Print the odd fridays of every month in 2011
    for (ydoy_date d = jan / day(28) / 2011, e = dec / day(28) / 2011; d <= e; d
        += months(1))
    {
      std::cout << d << '\n'; // first Friday of the month
    }
  }
  {
    Clock::time_point t0 = Clock::now();
    for (ydoy_date d = feb / day(28) / 2010, e = feb / day(28) / 2020; d != e; d
        += years(1))
      ;
    Clock::time_point t1 = Clock::now();
    std::cout << "   iterate: " << micros(t1 - t0) << "\n";
  }

  {
    ydoy_date d1 = jan / _2nd / 2011; // jan/2/2011
    ydoy_date d2 = year(2011) / jan / _2nd; // jan/2/2011
    ydoy_date d3 = _2nd / jan / 2011; // jan/2/2011
    std::cout << d1 << '\n';
    std::cout << d2 << '\n';
    std::cout << d3 << '\n';
  }

  {
    ydoy_date d1 = last / jan / 2011; // jan/31/2011
    std::cout << d1 << '\n';
  }

  {
    //      ydoy_date MothersDay = _sun[2]/may/2011;     // may/8/2011
    //      ydoy_date MothersDay2 = _sun[_2nd]/may/2011;  // may/8/2011
    ydoy_date MothersDay2 = _2nd_week * sun / may / 2011; // may/8/2011
    std::cout << "MothersDay " << MothersDay2 << '\n';
  }

  {
    //      ydoy_date d1 = _fri[last]/may/2011;  // may/27/2011
    ydoy_date d1 = last_week * fri / may / 2011; // may/27/2011
    std::cout << d1 << '\n';
  }

  {
    //      int num_fri_in_may = (_fri[last]/may/2011).get_day() > 28 ? 5 : 4;  // 4
    int num_fri_in_may = (last_week * fri / may / 2011).get_day() > 28 ? 5 : 4; // 4
    std::cout << "Number of fridays in May" << num_fri_in_may << '\n';

    //      ydoy_date d1 = rel_weekday(5)[_1st]/may/2011;
    ydoy_date d1 = _1st_week * weekday(5) / may / 2011;
    std::cout << d1 << '\n';

  }

  {
    // Print the last day in  Feb. for each year in the decade
    for (ydoy_date d = feb / last / 2010, e = feb / last / 2020; d <= e; d
        += years(1))
      std::cout << d << '\n';
    std::cout << feb / last / 2020 << '\n';
  }

  //    {
  //      // Print last day of every month in 2011
  //      for (ydoy_date d = jan/last/2011, e = dec/last/2011; d <= e; d += months(1))
  //          std::cout << d << '\n';
  //    }
  ////////////////////////
  std::cout << "***************" << '\n';

  {
    rel_date d1 = jan / _2nd / 2011; // jan/2/2011
    rel_date d2 = year(2011) / jan / _2nd; // jan/2/2011
    rel_date d3 = _2nd / jan / 2011; // jan/2/2011

    std::cout << d1 << '\n';
    std::cout << d2 << '\n';
    std::cout << d3 << '\n';
  }
  {
    rel_date d1 = last / jan / 2011; // jan/31/2011
    std::cout << d1 << '\n';
  }
  {
    int i = 0;
    // Print the last day in  Feb. for each year in the decade
    for (rel_date d = feb / last / 2010, e = feb / last / 2020; i < 20 && d
        <= e; d += years(1))
    {
      std::cout << d << '\n';
      ++i;
    }
    std::cout << feb / last / 2012 << '\n';
    std::cout << feb / last / 2016 << '\n';
    std::cout << feb / last / 2020 << '\n';
  }
  {
    int i = 0;
    // Print the 29th of every month in 2011
    for (rel_date d = last / jan / 2011, e = last / dec / 2011; i < 20 && d
        <= e; d += months(1))
    {
      if (d.get_day() >= 29)
        std::cout << d.get_year() / d.get_month() / 29 << '\n';
      ++i;
    }
  }
  {
    // Print the 2nd Tuesday of every odd month in 2011
    //      for (rel_date d = _tue[2]/jan/2011, e = dec/last/2011; d <= e; d += months(2))
    for (rel_date d = _2nd_week * tue / jan / 2011, e = dec / last / 2011; d
        <= e; d += months(2))
      std::cout << d << '\n';
  }
  {
    // Print out every monday between jan/1/2011 and mar/1/2011;
    //for (ydoy_date d = _mon[_1st]/jan/2011, e = mar/_1st/2011; d <= e; d += days(7))
    for (ydoy_date d = _1st_week * mon / jan / 2011, e = mar / _1st / 2011; d <= e; d
        += days(7))
      std::cout << d << '\n';
  }
  {
    ydoy_date dt = aug / day(16) / 2011;
    // ...
    // Get the ydoy_date that is the first occurrence of the same day of the week
    //   in the same month of the next year
    //rel_date dt2 = dt.get_weekday()[_1st]/dt.get_month()/(dt.get_year() + 1);  // aug/7/2012, first Tuesday of Aug 2012
    rel_date dt2 = _1st_week * dt.get_weekday() / dt.get_month()
        / (dt.get_year() + 1); // aug/7/2012, first Tuesday of Aug 2012
    std::cout << dt << '\n';
    std::cout << dt2 << '\n';
  }
  {
    ydoy_date ISO_week_start = mon <= jan / _4th / 2012;
    std::cout << "ISO_week_start " << ISO_week_start << '\n';
  }

  {
    // How many weeks until Christmas?
    ydoy_date dt = dec / day(25) / 2011;
    days d = dt - ydoy_date::today();
    std::cout << duration_cast<weeks> (d) << '\n';
  }
  {
    // How many average months until Christmas?
    days d = (dec / day(25) / 2011) - ydoy_date::today();
    std::cout << duration_cast<average_months> (d) << '\n';
  }
  {
    // How many weeks until Christmas?
    days d = (dec / day(25) > ydoy_date::today()) - ydoy_date::today();
    std::cout << duration_cast<weeks> (d) << '\n';
  }
  {
    // How many days until next 28th?
    days d = (nth(28) > ydoy_date::today()) - ydoy_date::today();
    std::cout << d << '\n';
  }
  {
    day::rep r = day(2) - day(6);
    std::cout << int(r) << '\n';
  }
#endif
  return boost::report_errors();
}
