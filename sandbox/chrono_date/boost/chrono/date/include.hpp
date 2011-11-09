//  date  --------------------------------------------------------------//

//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DATE_INCLUDE_HPP
#define BOOST_CHRONO_DATE_INCLUDE_HPP

#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/exceptions.hpp>

#include <boost/chrono/date/date_durations.hpp>

#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/month_nth.hpp>
#include <boost/chrono/date/month_nth_weekday.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/nth_weekday.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/tuples.hpp>
#include <boost/chrono/date/conversions.hpp>

#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/date/date_generators.hpp>

#include <boost/chrono/date/relative_date.hpp>


/*
 date synopsis

 namespace boost
 {
 namespace chrono
 {

 // A date
 class date
 {
 public:
 static date today();

 // system_clock::time_point conversions
 explicit date(boost::chrono::system_clock::time_point tp);
 explicit operator boost::chrono::system_clock::time_point () const;

 // obervers
 day get_day() const noexcept;
 month get_month() const noexcept;
 year get_year() const noexcept;
 weekday get_weekday() const noexcept;
 bool is_leap_year() const noexcept;

 // day arithmetic
 date& operator+=(days d);
 date& operator++();
 date  operator++(int);
 date& operator-=(days d);
 date& operator--();
 date  operator--(int);

 // month arithmetic
 date& operator+=(months m);
 date& operator-=(months m);

 // year arithmetic
 date& operator+=(years y);
 date& operator-=(years y);
 };

 // date relational
 bool operator==(const date& x, const date& y) noexcept;
 bool operator!=(const date& x, const date& y) noexcept;
 bool operator< (const date& x, const date& y) noexcept;
 bool operator> (const date& x, const date& y) noexcept;
 bool operator<=(const date& x, const date& y) noexcept;
 bool operator>=(const date& x, const date& y) noexcept;

 // date day arithmetic
 date operator+(date dt, days d);
 date operator+(days d, date dt);
 date operator-(date dt, days d);
 days operator-(date x, date y) noexcept;

 // date month arithmetic
 date operator+(date dt, months m);
 date operator+(months m, date dt);
 date operator-(date dt, months m);

 // date year arithmetic
 date operator+(date dt, years y);
 date operator+(years y, date dt);
 date operator-(date dt, years y);

 // Specifiers

 // A year specifier
 class year
 {
 public:
 explicit year(std::int16_t y);
 operator int() const noexcept;
 };

 // A month specifier
 class month
 {
 public:
 explicit month(int);
 operator int() const noexcept;
 };

 extern const month jan;
 extern const month feb;
 extern const month mar;
 extern const month apr;
 extern const month may;
 extern const month jun;
 extern const month jul;
 extern const month aug;
 extern const month sep;
 extern const month oct;
 extern const month nov;
 extern const month dec;

 // A day specifier
 class day
 {
 public:
 explicit day(int);
 day(__unnamed) noexcept;
 operator int() const noexcept;
 };

 // A day of the week specifier
 class weekday
 {
 public:
 explicit weekday(int);
 operator int() const noexcept;
 };

 extern const weekday sun;
 extern const weekday mon;
 extern const weekday tue;
 extern const weekday wed;
 extern const weekday thu;
 extern const weekday fri;
 extern const weekday sat;

 // A year + month specifier
 class year_month
 {
 // no public members
 };

 // A month + day specifier
 class month_day
 {
 // no public members
 };

 class __unnamed
 {
 // no public members
 };

 extern const __unnamed _1st;
 extern const __unnamed _2nd;
 extern const __unnamed _3rd;
 extern const __unnamed _4th;
 extern const __unnamed _5th;
 extern const __unnamed last;

 // Date generation functions

 date operator/(year_month, day);    // year(2011)/month(8)/day(19)
 date operator/(month_day, year);    // month(8)/day(19)/year(2011)
 // day(19)/month(8)/year(2011)

 year_month operator/(year, month) noexcept;  // year(2011)/month(8)

 month_day operator/(day, month) noexcept;    // day(19)/month(8)
 month_day operator/(month, day) noexcept;    // month(8)/day(19)

 // Date durations

 typedef duration<int_least32_t, ratio<86400>> days;

 days operator+(days x, days y);
 days operator-(days x, days y);
 days operator*(days x, days::rep y);
 days operator*(days::rep x, days y);
 days operator/(days x, days::rep y);
 days::rep operator/(days x, days y);
 days operator%(days x, days::rep y);
 days operator%(days x, days y);

 bool operator==(days x, days y);
 bool operator!=(days x, days y);
 bool operator< (days x, days y);
 bool operator> (days x, days y);
 bool operator<=(days x, days y);
 bool operator>=(days x, days y);

 class months
 {
 public:
 typedef std::int32_t rep;
 months() = default;
 explicit months(rep x) noexcept;

 rep count() const noexcept;

 months operator+() const noexcept;
 months operator-() const noexcept;

 months& operator++() noexcept;
 months  operator++(int) noexcept;
 months& operator--() noexcept;
 months  operator--(int) noexcept;

 months& operator+=(const months& x) noexcept;
 months& operator-=(const months& x) noexcept;

 months& operator*=(const rep& rhs) noexcept;
 months& operator/=(const rep& rhs) noexcept;
 months& operator%=(const rep& rhs) noexcept;
 months& operator%=(const months& rhs) noexcept;
 };

 months operator+(months x, months y) noexcept;
 months operator-(months x, months y) noexcept;
 months operator*(months x, months::rep y) noexcept;
 months operator*(months::rep x, months y) noexcept;
 months operator/(months x, months::rep y) noexcept;
 months::rep operator/(months x, months y) noexcept;
 months operator%(months x, months::rep y) noexcept;
 months operator%(months x, months y) noexcept;

 bool operator==(months x, months y) noexcept;
 bool operator!=(months x, months y) noexcept;
 bool operator< (months x, months y) noexcept;
 bool operator> (months x, months y) noexcept;
 bool operator<=(months x, months y) noexcept;
 bool operator>=(months x, months y) noexcept;

 class years
 {
 public:
 typedef std::int32_t rep;
 years() = default;
 explicit years(rep x) noexcept;

 rep count() const noexcept;

 years operator+() const noexcept;
 years operator-() const noexcept;

 years& operator++() noexcept;
 years  operator++(int) noexcept;
 years& operator--() noexcept;
 years  operator--(int) noexcept;

 years& operator+=(const years& x) noexcept;
 years& operator-=(const years& x) noexcept;

 years& operator*=(const rep& rhs) noexcept;
 years& operator/=(const rep& rhs) noexcept;
 years& operator%=(const rep& rhs) noexcept;
 years& operator%=(const years& rhs) noexcept;
 };

 years operator+(years x, years y) noexcept;
 years operator-(years x, years y) noexcept;
 years operator*(years x, years::rep y) noexcept;
 years operator*(years::rep x, years y) noexcept;
 years operator/(years x, years::rep y) noexcept;
 years::rep operator/(years x, years y) noexcept;
 years operator%(years x, years::rep y) noexcept;
 years operator%(years x, years y) noexcept;

 bool operator==(years x, years y) noexcept;
 bool operator!=(years x, years y) noexcept;
 bool operator< (years x, years y) noexcept;
 bool operator> (years x, years y) noexcept;
 bool operator<=(years x, years y) noexcept;
 bool operator>=(years x, years y) noexcept;

 date operator< (weekday wd, date x) noexcept;
 date operator<=(weekday wd, date x) noexcept;
 date operator> (weekday wd, date x) noexcept;
 date operator>=(weekday wd, date x) noexcept;

 class bad_date
 : public std::exception
 {
 public:
 virtual const char* what() const noexcpt();
 };

 }  // chrono
 }  // std

 */
#endif // BOOST_CHRONO_DATE_INCLUDE_HPP
