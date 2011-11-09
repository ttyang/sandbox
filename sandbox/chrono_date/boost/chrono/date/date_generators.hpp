//  date_generators.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
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
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/date_io.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * Generates a date satisfying the constraint parameter gt the Date parameter.
     * @tparam Date any model of a Date (is_date<Date> is true_type).
     * @param wd the constraint applied to the date @c x parameter.
     * @param x the reference date.
     * @return Let @c a be @c wd converted to an @c int, and @c b be @c x.weekday()
     * converted to an @c int. If <c>a < b</c>, returns <c>x - days(b-a)</c>, else returns <c>x - days(7 - (a-b))</c>.
     */
    template <typename Date>
    inline Date
    operator<(weekday wd, Date x)
    {
      const week::rep a = static_cast<week::rep>(wd);
      const week::rep b = static_cast<week::rep>(x.get_weekday());
      if (a < b)
      {
        return x - days(b-a);
      }
      return x - days(weekday::size - (a-b));
    }

    template <typename Date>
    inline Date
    operator<=(weekday wd, Date x)
    {
      const week::rep a = static_cast<week::rep>(wd);
      const week::rep b = static_cast<week::rep>(x.get_weekday());
      if (a <= b)
      {
        return x - days(b-a);
      }
      return x - days(weekday::size - (a-b));
    }

    template <typename Date>
    inline Date
    operator>(weekday wd, Date x)
    {
      const week::rep a = static_cast<week::rep>(x.get_weekday());
      const week::rep b = static_cast<week::rep>(wd);
      if (a < b)
      {
        return x + days(b-a);
      }
      return x + days(weekday::size - (a-b));
    }

    template <typename Date>
    inline Date
    operator>=(weekday wd, Date x)
    {
      const week::rep a = static_cast<week::rep>(x.get_weekday());
      const week::rep b = static_cast<week::rep>(wd);
      if (a <= b)
      {
        return x + days(b-a);
      }
      return x + days(weekday::size - (a-b));
    }

    template <typename Date>
    inline Date
    operator >(month_day md, Date d)
    {
      Date res;
      if (res.set_if_valid_date(d.get_year(),md.get_month(),md.get_day()) &&  res > d ) return res;
      if (res.set_if_valid_date(year(d.get_year()+1),md.get_month(),md.get_day()) &&  res > d ) return res;
      res=Date(d.get_year()+2,md.get_month(),md.get_day(),no_check);
      return res;
    }
    template <typename Date>
    inline Date
    operator >=(month_day md, Date d)
    {
      Date res;
      if (res.set_if_valid_date(d.get_year(),md.get_month(),md.get_day()) && res >= d) return  res;
      if (res.set_if_valid_date(year(d.get_year()+1),md.get_month(),md.get_day()) && res >= d) return  res;
      res=Date(d.get_year()+2,md.get_month(),md.get_day(),no_check);
      return res;
    }

    template <typename Date>
    inline Date
    operator >(nth n, Date d)
    {
      std::cout << __FILE__<<"["<<__LINE__ <<"] "<< d << '\n';
      Date res;
      if (d.get_month()==dec)
      {  // dec and jan have 31 days
        res = Date(d.get_year(),d.get_month(),n.value(),no_check);
        std::cout << __FILE__<<"["<<__LINE__ <<"] "<< res << '\n';

        if (res > d) return res;
        return Date(d.get_year(),jan,n.value(),no_check);
      }

      if (n.value()>28)
      { // As feb could have 29,30 and 31, we need to validate the two first dates
        if (res.set_if_valid_date(d.get_year(),d.get_month(),day(n.value())) && res > d) return res;
        if (res.set_if_valid_date(d.get_year(),month(d.get_month()+1),day(n.value())) && res > d) return res;
        return Date(d.get_year(),d.get_month()+2,n.value(),no_check) ;
      }
      // nth <= 28 is always valid, so the next is either in this month or the next one
      res = Date(d.get_year(),d.get_month(),n.value(),no_check);
      std::cout << __FILE__<<"["<<__LINE__ <<"] "<< res << '\n';
      if (res > d) return res;
      std::cout << __FILE__<<"["<<__LINE__ <<"] "<< int(d.get_month()+1) << '\n';
      return Date(d.get_year(),d.get_month()+1,n.value(),no_check);
    }
    template <typename Date>
    inline Date
    operator >=(nth n, Date d)
    {
      Date res;
      if (d.get_month()==dec)
      {  // dec and jan have 31 days
        res = Date(d.get_year(),d.get_month(),n.value(),no_check);
        if (res >= d) return res;
        return Date(d.get_year(),jan,n.value(),no_check);
      }

      if (n.value()>28)
      { // As feb could have 29,30 and 31, we need to validate the two first dates
        if (res.set_if_valid_date(d.get_year(),d.get_month(),day(n.value())) && res >= d) return res;
        if (res.set_if_valid_date(d.get_year(),month(d.get_month()+1),day(n.value())) && res >= d) return res;
        return Date(d.get_year(),d.get_month()+2,n.value(),no_check) ;
      }
      // nth <= 28 is always valid, so the next is either in this month or the next one
      res = Date(d.get_year(),d.get_month(),n.value(),no_check);
      if (res >= d) return res;
      return Date(d.get_year(),month(d.get_month()+1,no_check),n.value(),no_check);
    }


    template <typename Constraint>
    class forward_generator
    {
    private:
      Constraint constraint_;
    public:
      explicit forward_generator(Constraint constraint)
      : constraint_(constraint)
      {
      }
      template <typename Date>
      Date operator()(Date d)
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
      explicit forward_range(Constraint constraint, Date dt)
      : constraint_(constraint),
        dt_(dt)
      {
      }
      Date operator()()
      {
        dt_ = constraint_ > dt_;
        return dt_;
      }
    };
  } // chrono

} // boost

#endif  // header
