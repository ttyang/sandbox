//  Copyright 2010 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <boost/chrono/date/relative_date.hpp>
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

  std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl;
  { // construct from ymd: 0/1/1
    rel_date dt(year(0),jan,day(1));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.days_since_epoch().count()==11979588);
  }
  std::cerr << __FILE__ << ":" << __LINE__ << " " << std::endl;
  { // unchecked construct from bad ymd: 0/0/0 results in valid date
    rel_date dt(0,0,0,no_check);
    std::cout <<"0/0/0 days "<< dt.days_since_epoch().count() << std::endl;
    //BOOST_TEST( dt.is_valid());
  }
  std::cout <<"***********"<< std::endl;

  { // unchecked construct from bad ymd: 0/0/0 results in valid date
    rel_date dt(40000,1,1,no_check);
    //BOOST_TEST( ! dt.is_valid());
  }
  std::cout <<"***********"<< std::endl;
  { // bad construction from bad days: 0
    try {
      rel_date dt(days(0));
      BOOST_TEST( false );
    } catch (...) {}
  }
  std::cout <<"***********"<< std::endl;
  { // construct from days: 0/1/1
    rel_date dt(days(11979588));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.days_since_epoch().count()==11979588);
    BOOST_TEST(dt.get_year()==0);
    BOOST_TEST(dt.get_month()==1);
    BOOST_TEST(dt.get_day()==1);
  }
  std::cout <<"***********"<< std::endl;
  { // default constructor
    rel_date dt;
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==0);
    BOOST_TEST(dt.get_month()==1);
    BOOST_TEST(dt.get_day()==1);
  }
  std::cout <<"***********"<< std::endl;
  { // construct from ymd: 2011/oct/22
    rel_date dt(year(2011),oct,day(22));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  std::cout <<"***********"<< std::endl;
  { // no_check construct from bad ymd: 2011/oct/22
    rel_date dt(2011,10,22, no_check);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }

  { // construct from ymd: 2011/jan_01
    rel_date dt(year(2011),jan_01);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // no_check construct from ymd: 2011/jan_01
    rel_date dt(2011,jan_01, no_check);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // construct from ymd: first day: -32768/jan_01
    rel_date dt(year(-32768),jan_01);
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==-32768);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
    BOOST_TEST(dt.days_since_epoch().count()==11322);

    std::cout <<"-32768/jan/01 days "<< dt.days_since_epoch().count() << std::endl;
  }
  { // construct from ymd: last day: 32767/dec/31
    rel_date dt(year(32767),dec,day(31));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==32767);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
    BOOST_TEST(dt.days_since_epoch().count()==23947853);
    std::cout <<"32767/12/31 days "<< dt.days_since_epoch().count() << std::endl;
  }
  { // construct from days: first day: -32768/jan_01
    rel_date dt(days(11322));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==-32768);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);

  }
  { // construct from days: last day: 32767/dec/31
    rel_date dt(days(23947853));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==32767);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }


  { // construct from year + doy:
    rel_date dt(year(2011), day_of_year(1));
    std::cout << dt << '\n';
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }

  { // construct from year + doy:
    rel_date dt(year(2011), day_of_year(365));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }
  { // construct from year + doy:
    BOOST_TEST( year(2012).is_leap());
    rel_date dt(year(2012), day_of_year(366));
    BOOST_TEST( dt.is_valid());
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }

  { // construct from bad (year + doy):
    try {
    rel_date dt(year(2011), day_of_year(366));
    BOOST_TEST(  false );
    } catch (...) {}
  }

  // TODO Add construct from year + week + weekday

  { // construct from today
    rel_date dt = rel_date::today();
    BOOST_TEST( dt.is_valid());
  }
  { // conversions to/from system_clock::time_point
    rel_date dt(2011,10,22, no_check);
    boost::chrono::system_clock::time_point tp=boost::chrono::system_clock::time_point(dt);
    rel_date dt2(tp);
    BOOST_TEST( dt == dt2);
  }
  // is_leap_year
  {
    rel_date dt(2011,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    rel_date dt(0,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    rel_date dt(4,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    rel_date dt(400,10,22, no_check);
    BOOST_TEST( dt.is_leap_year());
  }
  {
    rel_date dt(100,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    rel_date dt(200,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  {
    rel_date dt(300,10,22, no_check);
    BOOST_TEST( ! dt.is_leap_year());
  }
  // get_weekday
  {
    BOOST_TEST( rel_date(2011,10,23, no_check).get_weekday()==sun);
    BOOST_TEST( rel_date(2011,10,24, no_check).get_weekday()==mon);
    BOOST_TEST( rel_date(2011,10,25, no_check).get_weekday()==tue);
    BOOST_TEST( rel_date(2011,10,26, no_check).get_weekday()==wed);
    BOOST_TEST( rel_date(2011,10,27, no_check).get_weekday()==thu);
    BOOST_TEST( rel_date(2011,10,28, no_check).get_weekday()==fri);
    BOOST_TEST( rel_date(2011,10,29, no_check).get_weekday()==sat);
  }
  // day based arithmetic
  { //+=
    rel_date dt(days(1000000));
    dt+=days(10);
    BOOST_TEST( dt.days_since_epoch()==days(1000010));
  }
  { // += feb/28 no leap
    rel_date dt(year(2011),feb,day(28));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==mar);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += feb/28 leap
    rel_date dt(year(2012),feb,day(28));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  { // += feb/29 leap
    rel_date dt(year(2012),feb,day(29));
    dt+=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==mar);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += month change
    rel_date dt(year(2011),oct,day(22));
    dt+=days(10);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==1);
  }
  { // += month+year change
    rel_date dt(year(2011),dec,day(22));
    dt+=days(10);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==1);
  }
  { // dt++
    rel_date dt(days(1000000));
    rel_date dt2= dt++;
    BOOST_TEST(  dt.days_since_epoch()==days(1000001));
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  { // ++dt
    rel_date dt(days(1000000));
    rel_date dt2 = ++dt;
    BOOST_TEST(  dt.days_since_epoch()==days(1000001));
    BOOST_TEST( dt2.days_since_epoch()==days(1000001));
  }

  { // -=
    rel_date dt(days(1000010));
    dt-=days(10);
    BOOST_TEST( dt.days_since_epoch()==days(1000000));
  }
  { // dt--
    rel_date dt(days(1000001));
    rel_date dt2= dt--;
    BOOST_TEST(  dt.days_since_epoch()==days(1000000));
    BOOST_TEST( dt2.days_since_epoch()==days(1000001));
  }
  { // --dt
    rel_date dt(days(1000001));
    rel_date dt2 = --dt;
    BOOST_TEST(  dt.days_since_epoch()==days(1000000));
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  { // -= month + year change
    rel_date dt(year(2011),jan,day(10));
    dt-=days(10);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==31);
  }

  { // -= month change
    rel_date dt(year(2011),oct,day(10));
    dt-=days(10);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==30);
  }
  {
    rel_date dt(year(2011),mar,day(1));
    dt-=days(1);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==28);
  }
  {
    rel_date dt(year(2012),mar,day(1));
    dt-=days(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }

  {
    rel_date dt(days(1000000));
    rel_date dt2=dt+days(10);
    BOOST_TEST( dt2.days_since_epoch()==days(1000010));
  }
  {
    rel_date dt(days(1000000));
    rel_date dt2=days(10)+dt;
    BOOST_TEST( dt2.days_since_epoch()==days(1000010));
  }
  {
    rel_date dt(days(1000010));
    rel_date dt2=dt-days(10);
    BOOST_TEST( dt2.days_since_epoch()==days(1000000));
  }
  {
    rel_date dt(days(1000010));
    rel_date dt2(days(1000000));
    BOOST_TEST( dt-dt2==days(10));
  }
  {
    rel_date dt(days(1000010));
    rel_date dt2(days(1000000));
    BOOST_TEST( dt2-dt==days(-10));
  }
  std::cout <<"==========="<< std::endl;

  // month based arithmetic
  {
    rel_date dt(year(2011),oct,day(22));
    std::cout <<dt<< std::endl;
    dt+=months(1);
    std::cout <<dt<< std::endl;

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  std::cout <<"==========="<< std::endl;
  {
    rel_date dt(year(2011),oct,day(22));
    dt = dt + months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  std::cout <<"==========="<< std::endl;
  {
    rel_date dt(year(2011),oct,day(22));
    dt = months(1) + dt;

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==nov);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt+=months(3);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==jan);
    BOOST_TEST(dt.get_day()==22);
  }
  std::cout <<"/////////"<< std::endl;
  {
    rel_date dt(year(2011),jan,day(29));
    try {
      dt+=months(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    rel_date dt(year(2012),jan,day(29));
    dt+=months(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()=feb);
    BOOST_TEST(dt.get_day()==29);
  }
  std::cout <<"/////////"<< std::endl;

  {
    rel_date dt(year(2011),oct,day(22));
    dt-=months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2012),mar,day(22));
    dt-=months(3);
    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==dec);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt= dt-months(1);

    BOOST_TEST(dt.get_year()==2011);
    BOOST_TEST(dt.get_month()==sep);
    BOOST_TEST(dt.get_day()==22);
  }

  // year based arithmetic
  {
    rel_date dt(year(2011),oct,day(22));
    dt+=years(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2012),feb,day(29));
    dt+=years(4);
    BOOST_TEST(dt.get_year()==2016);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  {
    rel_date dt(year(2012),feb,day(29));
    try {
      dt+=years(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt = dt + years(1);
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt = years(1) + dt;
    BOOST_TEST(dt.get_year()==2012);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt-=years(1);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  std::cout <<"/////////"<< std::endl;

  {
    rel_date dt(year(2012),feb,day(29));
    dt-=years(4);
    BOOST_TEST(dt.get_year()==2008);
    BOOST_TEST(dt.get_month()==feb);
    BOOST_TEST(dt.get_day()==29);
  }
  {
    rel_date dt(year(2012),feb,day(29));
    try {
      dt-=years(1);
      BOOST_TEST(false);
    } catch (...) {}
  }
  {
    rel_date dt(year(2011),oct,day(22));
    dt = dt - years(1);
    BOOST_TEST(dt.get_year()==2010);
    BOOST_TEST(dt.get_month()==oct);
    BOOST_TEST(dt.get_day()==22);
  }
  // TODO add exceptional cases bad result year

  // Relational operators
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt1 == dt2 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt1 >= dt2 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),oct,day(22));
    BOOST_TEST( dt2 <= dt2 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 >= dt2 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 > dt2 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt2 <= dt1 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt2 < dt1 );
  }
  {
    rel_date dt1(year(2011),oct,day(22));
    rel_date dt2(year(2011),sep,day(22));
    BOOST_TEST( dt1 != dt2 );
  }

  // optional
  {
    optional<rel_date> odt = make_optional<rel_date>(year(2011),oct,day(22));
    BOOST_TEST( odt );
  }
  {
    optional<rel_date> odt = make_optional<rel_date>(year(2011),nov,day(31));
    BOOST_TEST( ! odt );
  }

  return boost::report_errors();
}
