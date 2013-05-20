//  date_generators.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011-2013 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_GENERATORS_HPP
#define BOOST_CHRONO_DATE_DATE_GENERATORS_HPP



#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/relative_date.hpp>
#include <boost/chrono/date/nth_weekday.hpp>
#include <boost/chrono/date/month_nth_weekday.hpp>
#include <boost/chrono/date/month_nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/nth_tag.hpp>
#include <boost/chrono/date/date_io.hpp>

namespace boost
{
  namespace chrono
  {
    namespace detail
    {
      BOOST_FORCEINLINE days_date
      generate_lt(weekday::rep a, weekday::rep b, days_date x)
      {
        return (a < b)
            ? (x - days(b-a))
            : (x - days(weekday::size - (a-b)));
      }
      BOOST_FORCEINLINE days_date
      generate_le(weekday::rep a, weekday::rep b, days_date x)
      {
        return (a <= b)
            ? (x - days(b-a))
            : (x - days(weekday::size - (a-b)));
      }
      BOOST_FORCEINLINE days_date
      generate_gt(weekday::rep a, weekday::rep b, days_date x)
      {
        return (a < b)
            ? (x + days(b-a))
            : (x + days(weekday::size - (a-b)));
      }
      BOOST_FORCEINLINE days_date
      generate_ge(weekday::rep a, weekday::rep b, days_date x)
      {
        return (a <= b)
            ? (x + days(b-a))
            : (x + days(weekday::size - (a-b)));
      }
    }
    /**
     * Generates a date satisfying the constraint parameter gt the Date parameter.
     * @tparam Date any model of a Date (is_date<Date> is true_type).
     * @param wd the constraint applied to the date @c x parameter.
     * @param x the reference date.
     * @return Let @c a be @c wd converted to an @c int, and @c b be @c weekday(x)
     * converted to an @c int. If <c>a < b</c>, returns <c>x - days(b-a)</c>, else returns <c>x - days(7 - (a-b))</c>.
     */
    //template <typename Date>
    BOOST_FORCEINLINE days_date
    operator<(weekday wd, days_date x)
    {
      return detail::generate_lt(wd, weekday(x), x);
    }

    //template <typename Date>
    BOOST_FORCEINLINE days_date
    operator<=(weekday wd, days_date x)
    {
      return detail::generate_le(wd, weekday(x), x);
    }

    //template <typename Date>
    BOOST_FORCEINLINE days_date
    operator>(weekday wd, days_date x)
    {
      return detail::generate_gt(wd, weekday(x), x);
    }

    //template <typename Date>
    BOOST_FORCEINLINE days_date
    operator>=(weekday wd, days_date x)
    {
      return detail::generate_ge(wd, weekday(x), x);
    }

    template <typename Date>
    BOOST_FORCEINLINE Date
    operator >(month_day md, Date d)
    {
      Date res;
      if (res.set_if_valid_date(year(d),month(md),day(md)) &&  res > d ) return res;
      if (res.set_if_valid_date(year(year(d)+1),month(md),day(md)) &&  res > d ) return res;
      res=Date(year(year(d)+2),month(md),day(md));
      return res;
    }
    template <typename Date>
    BOOST_FORCEINLINE Date
    operator >=(month_day md, Date d)
    {
      Date res;
      if (res.set_if_valid_date(year(d),month(md),day(md)) && res >= d) return  res;
      if (res.set_if_valid_date(year(year(d)+1),month(md),day(md)) && res >= d) return  res;
      res=Date(year(year(d)+2),month(md),day(md));
      return res;
    }

    //template <typename Date>
    BOOST_FORCEINLINE ymd_date
    operator >(day n, ymd_date d)
    {
      ymd_date res;
      if (month(d)==dec)
      {  // dec and jan have 31 days
        res = ymd_date(year(d),month(d),n);

        if (res > d) return res;
        return ymd_date(year(d),jan,n);
      }

      if (n.value()>28)
      { // As feb could have 29,30 and 31, we need to validate the two first dates
        if (res.set_if_valid_date(year(d),month(d),day(n.value(), no_check)) && res > d) return res;
        if (res.set_if_valid_date(year(d),month(month(d)+1),day(n.value(), no_check)) && res > d) return res;
        return ymd_date(year(d),month(month(d)+2),day(n.value(), no_check)) ;
      }
      // day <= 28 is always valid, so the next is either in this month or the next one
      res = ymd_date(year(d),month(d),day(n.value()));
      if (res > d) return res;
      return ymd_date(year(d),month(month(d)+1),day(n.value(), no_check));
    }
    //template <typename Date>
    BOOST_FORCEINLINE ymd_date
    operator >=(day n, ymd_date d)
    {
      ymd_date res;
      if (month(d)==dec)
      {  // dec and jan have 31 days
        res = ymd_date(year(d),month(d),n);
        if (res >= d) return res;
        return ymd_date(year(d),jan,n);
      }

      if (n.value()>28)
      { // As feb could have 29,30 and 31, we need to validate the two first dates
        if (res.set_if_valid_date(year(d),month(d),n) && res >= d) return res;
        if (res.set_if_valid_date(year(d),month(month(d)+1),n) && res >= d) return res;
        return ymd_date(year(d),month(month(d)+2),n, no_check) ;
      }
      // day <= 28 is always valid, so the next is either in this month or the next one
      res = ymd_date(year(d),month(d),n);
      if (res >= d) return res;
      return ymd_date(year(d),month(month(d)+1),n, no_check);
    }


    template <typename Constraint>
    class forward_generator
    {
    private:
      Constraint constraint_;
    public:
      explicit BOOST_FORCEINLINE forward_generator(Constraint constraint)
      : constraint_(constraint)
      {
      }
      template <typename Date>
      BOOST_FORCEINLINE Date operator()(Date d)
      {
        return constraint_ > d;
      }
    };
    template <typename Constraint, typename Date>
    class forward_range
    {
    private:
      Constraint constraint_;
      Date dt_;
    public:
      BOOST_FORCEINLINE explicit forward_range(Constraint constraint, Date dt)
      : constraint_(constraint),
        dt_(dt)
      {
      }
      BOOST_FORCEINLINE Date operator()()
      {
        dt_ = constraint_ > dt_;
        return dt_;
      }
    };
  } // chrono

} // boost

#endif  // header
