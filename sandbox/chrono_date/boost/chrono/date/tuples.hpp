//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_TUPLES_HPP
#define BOOST_CHRONO_DATE_DATE_TUPLES_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/date/no_check.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/weekday.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/day_of_year.hpp>
#include <boost/chrono/date/week.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/detail/helpers.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * Class year_month is a tuple-like class of year-month.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_month
    {
      year y_;
      month m_;
    public:
      year_month(year y, month m) BOOST_NOEXCEPT
      : y_(y),
      m_(m)
      {
      }
      year_month(year::rep y, month::rep m, no_check_t) BOOST_NOEXCEPT
      : y_(y, no_check),
      m_(m, no_check)
      {
      }
      /**
       * @Return the year stored component.
       */
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }

      /**
       * @Return the month stored component.
       */
      month get_month() const BOOST_NOEXCEPT
      {
        return m_;
      }

      /**
       * @Return the number of days of this month in this year.
       */
      days days_in() const BOOST_NOEXCEPT
      {
        return y_.days_in(m_);
      }
    };

    inline year_month operator/(year y, month m) BOOST_NOEXCEPT
    {
      return year_month(y, m);
    }
    inline year_month operator/(month m, year y) BOOST_NOEXCEPT
    {
      return year_month(y, m);
    }

    /**
     * Class year_week is a tuple-like class of year-week.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_week
    {
      year y_;
      week w_;
    public:
      year_week(year y, week w) BOOST_NOEXCEPT
      : y_(y),
      w_(w)
      {
      }
      year_week(year::rep y, week::rep w, no_check_t) BOOST_NOEXCEPT
      : y_(y, no_check),
      w_(w, no_check)
      {
      }

      /**
       * @Return the year stored component.
       */
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      /**
       * @Return the week stored component.
       */
      week get_week() const BOOST_NOEXCEPT
      {
        return w_;
      }

    };

    inline year_week operator/(year y, week w) BOOST_NOEXCEPT
    {
      return year_week(y, w);
    }

    inline year_week operator/(week w, year y) BOOST_NOEXCEPT
    {
      return year_week(y, w);
    }

    /**
     * Class month_day is a tuple-like class of month-day.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     *
     * This class is useful while generating dates, allowing to generate dates
     * that are quasi literals (e.g. jan_01/2012).
     */
    class month_day
    {
      month m_;
      day d_;
    public:
      month_day(month m, day d)BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
        // check validity of day relative to month.
      }
      month_day(month::rep m, day::rep d, no_check_t)BOOST_NOEXCEPT
      : m_(m,no_check),
      d_(d,no_check)
      {
      }
      /**
       * @Return the month stored component.
       */
      month get_month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      /**
       * @Return the day stored component.
       */
      day get_day() const BOOST_NOEXCEPT
      {
        return d_;
      }
    };

    inline month_day operator/(month m, day d) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }


    inline month_day operator/(day d, month m) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }


    extern const month_day
        jan_01, jan_02, jan_03, jan_04, jan_05, jan_06, jan_07,
        jan_08, jan_09, jan_10, jan_11, jan_12, jan_13, jan_14,
        jan_15, jan_16, jan_17, jan_18, jan_19, jan_20, jan_21,
        jan_22, jan_23, jan_24, jan_25, jan_26, jan_27, jan_28, jan_29, jan_30, jan_31,
        feb_01, feb_02, feb_03, feb_04, feb_05, feb_06, feb_07,
        feb_08, feb_09, feb_10, feb_11, feb_12, feb_13, feb_14,
        feb_15, feb_16, feb_17, feb_18, feb_19, feb_20, feb_21,
        feb_22, feb_23, feb_24, feb_25, feb_26, feb_27, feb_28, feb_29,
        mar_01, mar_02, mar_03, mar_04, mar_05, mar_06, mar_07,
        mar_08, mar_09, mar_10, mar_11, mar_12, mar_13, mar_14,
        mar_15, mar_16, mar_17, mar_18, mar_19, mar_20, mar_21,
        mar_22, mar_23, mar_24, mar_25, mar_26, mar_27, mar_28, mar_29, mar_30, mar_31,
        apr_01, apr_02, apr_03, apr_04, apr_05, apr_06, apr_07,
        apr_08, apr_09, apr_10, apr_11, apr_12, apr_13, apr_14,
        apr_15, apr_16, apr_17, apr_18, apr_19, apr_20, apr_21,
        apr_22, apr_23, apr_24, apr_25, apr_26, apr_27, apr_28, apr_29, apr_30,
        may_01, may_02, may_03, may_04, may_05, may_06, may_07,
        may_08, may_09, may_10, may_11, may_12, may_13, may_14,
        may_15, may_16, may_17, may_18, may_19, may_20, may_21,
        may_22, may_23, may_24, may_25, may_26, may_27, may_28, may_29, may_30, may_31,
        jun_01, jun_02, jun_03, jun_04, jun_05, jun_06, jun_07,
        jun_08, jun_09, jun_10, jun_11, jun_12, jun_13, jun_14,
        jun_15, jun_16, jun_17, jun_18, jun_19, jun_20, jun_21,
        jun_22, jun_23, jun_24, jun_25, jun_26, jun_27, jun_28, jun_29, jun_30,
        jul_01, jul_02, jul_03, jul_04, jul_05, jul_06, jul_07,
        jul_08, jul_09, jul_10, jul_11, jul_12, jul_13, jul_14,
        jul_15, jul_16, jul_17, jul_18, jul_19, jul_20, jul_21,
        jul_22, jul_23, jul_24, jul_25, jul_26, jul_27, jul_28, jul_29, jul_30, jul_31,
        aug_01, aug_02, aug_03, aug_04, aug_05, aug_06, aug_07,
        aug_08, aug_09, aug_10, aug_11, aug_12, aug_13, aug_14,
        aug_15, aug_16, aug_17, aug_18, aug_19, aug_20, aug_21,
        aug_22, aug_23, aug_24, aug_25, aug_26, aug_27, aug_28, aug_29, aug_30, aug_31,
        sep_01, sep_02, sep_03, sep_04, sep_05, sep_06, sep_07,
        sep_08, sep_09, sep_10, sep_11, sep_12, sep_13, sep_14,
        sep_15, sep_16, sep_17, sep_18, sep_19, sep_20, sep_21,
        sep_22, sep_23, sep_24, sep_25, sep_26, sep_27, sep_28, sep_29, sep_30,
        oct_01, oct_02, oct_03, oct_04, oct_05, oct_06, oct_07,
        oct_08, oct_09, oct_10, oct_11, oct_12, oct_13, oct_14,
        oct_15, oct_16, oct_17, oct_18, oct_19, oct_20, oct_21,
        oct_22, oct_23, oct_24, oct_25, oct_26, oct_27, oct_28, oct_29, oct_30, oct_31,
        nov_01, nov_02, nov_03, nov_04, nov_05, nov_06, nov_07,
        nov_08, nov_09, nov_10, nov_11, nov_12, nov_13, nov_14,
        nov_15, nov_16, nov_17, nov_18, nov_19, nov_20, nov_21,
        nov_22, nov_23, nov_24, nov_25, nov_26, nov_27, nov_28, nov_29, nov_30,
        dec_01, dec_02, dec_03, dec_04, dec_05, dec_06, dec_07,
        dec_08, dec_09, dec_10, dec_11, dec_12, dec_13, dec_14,
        dec_15, dec_16, dec_17, dec_18, dec_19, dec_20, dec_21,
        dec_22, dec_23, dec_24, dec_25, dec_26, dec_27, dec_28, dec_29, dec_30, dec_31
    ;

    /**
     * Class week_weekday is a tuple-like class of week-weekday.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     *
     * It is useful when generation week based dates.
     */
    class week_weekday
    {
      week w_;
      weekday wd_;
    public:
      week_weekday(week w, weekday wd)BOOST_NOEXCEPT
      : w_(w),
      wd_(wd)
      {
      }

      week_weekday(week::rep w, weekday::rep wd, no_check_t)BOOST_NOEXCEPT
      : w_(w, no_check),
      wd_(wd, no_check)
      {
      }
      week get_week() const BOOST_NOEXCEPT
      {
        return w_;
      }
      weekday get_weekday() const BOOST_NOEXCEPT
      {
        return wd_;
      }

    };

    inline week_weekday operator/(week w, weekday wd) BOOST_NOEXCEPT
    {
      return week_weekday(w, wd);
    }

    inline week_weekday operator/(weekday wd, week w) BOOST_NOEXCEPT
    {
      return week_weekday(w, wd);
    }

    /**
     * Class year_month_day is a tuple-like class of year-month-day.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_month_day
    {
      year y_;
      month m_;
      day d_;
    public:
      year_month_day(year y, month m, day d)BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d)
      {
      }

      year_month_day(year::rep y, month::rep m, day::rep d, no_check_t)BOOST_NOEXCEPT
      : y_(y, no_check),
      m_(m, no_check),
      d_(d, no_check)
      {
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      month get_month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      day get_day() const BOOST_NOEXCEPT
      {
        return d_;
      }

    };

    /**
     * Class year_month_day is a tuple-like class of year-month-day.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_month_day_leap
    {
      year y_;
      month m_;
      day d_;
      bool leap_;
    public:
      year_month_day_leap(year y, month m, day d, bool leap)BOOST_NOEXCEPT
      : y_(y),
      m_(m),
      d_(d),
      leap_(leap)
      {
      }

      year_month_day_leap(year::rep y, month::rep m, day::rep d, bool leap, no_check_t)BOOST_NOEXCEPT
      : y_(y, no_check),
      m_(m, no_check),
      d_(d, no_check),
      leap_(leap)
      {
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      month get_month() const BOOST_NOEXCEPT
      {
        return m_;
      }
      day get_day() const BOOST_NOEXCEPT
      {
        return d_;
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }

    };
    /**
     * Class year_day_of_year is a tuple-like class of year-day_of_year.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_day_of_year
    {
      year y_;
      day_of_year d_;
    public:
      year_day_of_year(year y, day_of_year d)BOOST_NOEXCEPT
      : y_(y),
      d_(d)
      {
      }
      year_day_of_year(year::rep y, day_of_year::rep d, no_check_t) BOOST_NOEXCEPT
      : y_(y, no_check),
      d_(d, no_check)
      {
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      day_of_year get_day_of_year() const BOOST_NOEXCEPT
      {
        return d_;
      }

    };


    /**
     * Class year_week_weekday is a tuple-like class of year-week-weekday.
     *
     * It is CopyConstructible, CopyAssignable, and Destructible.
     */
    class year_week_weekday
    {
      year y_;
      week w_;
      weekday wd_;
    public:
      year_week_weekday(year y, week w, weekday wd)BOOST_NOEXCEPT
      : y_(y),
      w_(w),
      wd_(wd)
      {
      }
          year_week_weekday(year::rep y, week::rep w, weekday::rep wd, no_check_t)BOOST_NOEXCEPT
      : y_(y, no_check),
      w_(w, no_check),
      wd_(wd, no_check)
      {
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return y_;
      }
      week get_week() const BOOST_NOEXCEPT
      {
        return w_;
      }
      weekday get_weekday() const BOOST_NOEXCEPT
      {
        return wd_;
      }

    };










  } // chrono

} // boost

#endif  // header
