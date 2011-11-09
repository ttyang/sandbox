//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_NTH_WEEKDAY_HPP
#define BOOST_CHRONO_DATE_NTH_WEEKDAY_HPP


#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/no_check.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * The class nth_weekday is used to specify the nth weekday of a month (example: 2nd Sunday).
     */
    class nth_weekday
    {
      nth_week n_; // :3
      weekday dow_; // :3

    public:
      /**
       * @param n the nth week
       * @param dow the day of the year
       * @Effects: Constructs a pair of nth-weekday.
       * Throws: if nth.value() is outside of the range [1, 5], throws an exception of type bad_date.
       */
      nth_weekday(nth_week n, weekday dow) BOOST_NOEXCEPT
      :
      n_(n),
      dow_(dow)
      {
        // No invalid condition
      }
      /**
       * @param n the nth week
       * @param dow the day of the year
       * @param tag to state that no check is performed.
       * @Effects: Constructs a pair of nth-weekday.
       * @Note This function doesn't check the parameters validity.
       * It is up to the user to provide a valid ones.
       */
      nth_weekday(nth_week::rep n, weekday::rep dow, no_check_t) BOOST_NOEXCEPT
      :
      n_(n),
      dow_(dow)
      {
      }

      /**
       * @Return if the stored value is a valid one.
       */
      bool is_valid() const BOOST_NOEXCEPT
      {
        return (n_.is_valid() && dow_.is_valid());
      }
      /**
       * @Return The nth stored component.
       */
      nth_week get_nth() const BOOST_NOEXCEPT
      {
        return n_;
      }
      /**
       * @Return The weekday stored component.
       */
      weekday get_weekday() const BOOST_NOEXCEPT
      {
        return dow_;
      }
    };

    /**
     *
     * @param nw the nth week
     * @param wd the weekday
     * @return a nth_weekday with the given parameters
     */
    inline nth_weekday operator*(nth_week nw, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nw, wd);
    }

    inline nth_weekday operator*(last_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(6,no_check), wd);
    }
    inline nth_weekday operator*(_1st_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(1,no_check), wd);
    }
    inline nth_weekday operator*(_2nd_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(2,no_check), wd);
    }
    inline nth_weekday operator*(_3rd_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(3,no_check), wd);
    }
    inline nth_weekday operator*(_4th_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(4,no_check), wd);
    }
    inline nth_weekday operator*(_5th_t, weekday wd) BOOST_NOEXCEPT
    {
      return nth_weekday(nth_week(5,no_check), wd);
    }

    extern const nth_weekday last_sun;
    extern const nth_weekday last_mon;
    extern const nth_weekday last_tue;
    extern const nth_weekday last_wed;
    extern const nth_weekday last_thu;
    extern const nth_weekday last_fri;
    extern const nth_weekday last_sat;
    extern const nth_weekday _1st_sun;
    extern const nth_weekday _1st_mon;
    extern const nth_weekday _1st_tue;
    extern const nth_weekday _1st_wed;
    extern const nth_weekday _1st_thu;
    extern const nth_weekday _1st_fri;
    extern const nth_weekday _1st_sat;
    extern const nth_weekday _2nd_sun;
    extern const nth_weekday _2nd_mon;
    extern const nth_weekday _2nd_tue;
    extern const nth_weekday _2nd_wed;
    extern const nth_weekday _2nd_thu;
    extern const nth_weekday _2nd_fri;
    extern const nth_weekday _2nd_sat;
    extern const nth_weekday _3rd_sun;
    extern const nth_weekday _3rd_mon;
    extern const nth_weekday _3rd_tue;
    extern const nth_weekday _3rd_wed;
    extern const nth_weekday _3rd_thu;
    extern const nth_weekday _3rd_fri;
    extern const nth_weekday _3rd_sat;
    extern const nth_weekday _4th_sun;
    extern const nth_weekday _4th_mon;
    extern const nth_weekday _4th_tue;
    extern const nth_weekday _4th_wed;
    extern const nth_weekday _4th_thu;
    extern const nth_weekday _4th_fri;
    extern const nth_weekday _4th_sat;
    extern const nth_weekday _5th_sun;
    extern const nth_weekday _5th_mon;
    extern const nth_weekday _5th_tue;
    extern const nth_weekday _5th_wed;
    extern const nth_weekday _5th_thu;
    extern const nth_weekday _5th_fri;
    extern const nth_weekday _5th_sat;

  } // chrono

} // boost

#endif  // header
