//  rel_date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_RELATIVE_DATE_HPP
#define BOOST_CHRONO_DATE_RELATIVE_DATE_HPP



#include <boost/cstdint.hpp>
#include <boost/chrono/config.hpp>
#include <boost/chrono/date/date.hpp>
#include <boost/chrono/date/nth_weekday.hpp>
#include <boost/chrono/date/month_nth_weekday.hpp>
#include <boost/chrono/date/month_nth.hpp>
#include <boost/chrono/date/nth_week.hpp>
#include <boost/chrono/date/nth.hpp>
#include <boost/chrono/date/days_date.hpp>
#include <boost/chrono/date/ymd_date.hpp>
#include <boost/chrono/date/ydoy_date.hpp>
#include <boost/chrono/date/is_date.hpp>

namespace boost
{
  namespace chrono
  {


    /**
     * The class @c rel_date is a model of Date storing
     * - the @c year,
     * - the @c month,
     * - the @c day of the month
     * and optionally
     * - the number of @c days since an undetermined epoch.
     * - whether the year is leap or not.
     */
    class rel_date
    {
#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1
      // Store x, y/m/d, n, dow. Total 64 bits
      uint_least32_t x_;
      int_least16_t y_;

      uint_least8_t m_    : 4;
      uint_least8_t leap_ : 1;
      uint_least8_t dow_  : 3;

      uint_least8_t d_    : 5; // :5
      uint_least8_t n_    : 3; // :3
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      // Store x, n, dow. Total 64 bits
      uint_least32_t x_;
      uint_least8_t n_    :5;
      uint_least8_t dow_  :3;
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      // Store y/m/d, n, dow. Total 32 bits
      int_least16_t y_;
      uint_least8_t m_    : 4;
      uint_least8_t leap_ : 1;
      uint_least8_t dow_  : 3;
      uint_least8_t d_    : 5;
      uint_least8_t n_    : 3;
#endif

    public:

      /**
       * Effects: Constructs a @c rel_date as if by @c year(0)/jan/1.
       * Note: the purpose of this constructor is to have a very efficient means
       * of @c rel_date valid construction when the specific value for that @c days_date is unimportant.
       */
      rel_date() BOOST_NOEXCEPT;
      rel_date(year, month, nth_weekday);
      rel_date(year, month, nth_weekday, check_t) BOOST_NOEXCEPT;
      rel_date(year, month, nth);
      rel_date(year, month, nth, check_t)BOOST_NOEXCEPT;
#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE
      rel_date(year, month, day); // TODO
      rel_date(year, month, day, check_t)BOOST_NOEXCEPT;// TODO
      rel_date(year y, month_day md);// TODO
      rel_date(year, month_day, check_t) BOOST_NOEXCEPT;// TODO

      explicit rel_date(days d);// TODO

      rel_date(year y, day_of_year doy);// TODO
      rel_date(year y, day_of_year doy, check_t) BOOST_NOEXCEPT;// TODO

      bool set_if_valid_date(year y, month m, day d) BOOST_NOEXCEPT;// TODO
      bool set_if_valid_date(year y, day_of_year doy) BOOST_NOEXCEPT;// TODO
      bool set_if_valid_date(days d) BOOST_NOEXCEPT;// TODO

      static rel_date today() BOOST_NOEXCEPT;// TODO

      explicit rel_date(system_clock::time_point tp);// TODO
      // explicit
      operator system_clock::time_point () const;// TODO

#endif
      // conversions
      //explicit rel_date(ymd_date dt);
      operator ymd_date() const;
      //explicit rel_date(days_date dt);
      operator days_date() const;
      //explicit rel_date(ydoy_date dt);
      operator ydoy_date() const;

      // observers
      //bool is_valid() const BOOST_NOEXCEPT;

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      day get_day() const BOOST_NOEXCEPT
      {
        std::cout << "KKKKKKKKKKKKK" << std::endl;
        if (d_!=0)
        return day(d_);
        else {
          std::cout << "KKKKKKKKKKKKK" << std::endl;
          return day(d_);
        }

      }
      month get_month() const BOOST_NOEXCEPT
      {
        return month(m_);
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return year(y_);
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      day get_day() const BOOST_NOEXCEPT
      {
        return day(day_from_day_number());
      }
      month get_month() const BOOST_NOEXCEPT
      {
        return month(month_from_day_number());
      }
      year get_year() const BOOST_NOEXCEPT
      {
        return year(year_from_day_number());
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_from_day_number();
      }
#endif
#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      weekday get_weekday() const BOOST_NOEXCEPT
      {
        return weekday((x_+1) % weekday::size);
      }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      weekday get_weekday() const BOOST_NOEXCEPT
      {
        return weekday((day_number_from_ymd()+1) % weekday::size);
      }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      days days_since_epoch() const
      {
        return days(x_);
      }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      days days_since_epoch() const
      {
        return days(day_number_from_ymd());
      }
#endif

#if BOOST_CHRONO_DATE_REL_DATE_IS_A_MODEL_OF_DATE

      rel_date& operator+=(days d);
      rel_date& operator++()
      {
        return *this += days(1);
      }
      rel_date operator++(int)
      {
        rel_date tmp(*this);
        ++(*this);
        return tmp;
      }
      rel_date& operator-=(days d)
      {
        return *this += -d;
      }
      rel_date& operator--()
      {
        return *this -= days(1);
      }
      rel_date operator--(int)
      {
        rel_date tmp(*this);
        --(*this); return tmp;
      }

      friend rel_date operator+(rel_date dt, days d)
      {
        dt += d;
        return dt;
      }
      friend rel_date operator+(days d, rel_date dt)
      {
        dt += d;
        return dt;
      }
      friend rel_date operator-(rel_date dt, days d)
      {
        dt -= d;
        return dt;
      }
#endif
#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      friend days operator-(rel_date x, rel_date y) BOOST_NOEXCEPT
      {
        return x.days_since_epoch() - y.days_since_epoch();
      }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      friend days operator-(rel_date x, rel_date y) BOOST_NOEXCEPT
      {
        return x.days_since_epoch() - y.days_since_epoch();
      }
#endif
      friend days operator-(rel_date x, ymd_date y) BOOST_NOEXCEPT
      {
        return x.days_since_epoch() - y.days_since_epoch();
      }

      friend days operator-(ymd_date x, rel_date y) BOOST_NOEXCEPT
      {
        return x.days_since_epoch() - y.days_since_epoch();
      }

      rel_date& operator+=(months m);
      rel_date& operator-=(months m)
      {
        return *this += months(-m.count());
      }

      friend rel_date operator+(rel_date dt, months m)
      {
        dt += m;
        return dt;
      }
      friend rel_date operator+(months m, rel_date dt)
      {
        dt += m;
        return dt;
      }
      friend rel_date operator-(rel_date dt, months m)
      {
        dt -= m;
        return dt;
      }

      rel_date& operator+=(years y);
      rel_date& operator-=(years y)
      {
        return *this += years(-y.count());
      }

      friend rel_date operator+(rel_date dt, years y)
      {
        dt += y;
        return dt;
      }
      friend rel_date operator+(years y, rel_date dt)
      {
        dt += y;
        return dt;
      }
      friend rel_date operator-(rel_date dt, years y)
      {
        dt -= y;
        return dt;
      }

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 1 || BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
      friend bool operator==(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return x.x_ == y.x_;
      }
      friend bool operator< (const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return x.x_ < y.x_;
      }
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      friend bool operator==(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.m_ == y.m_ && x.d_ == y.d_;
      }
      friend bool operator< (const rel_date& x, const rel_date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.m_ < y.m_ ||
                (!(y.m_ < x.m_) && x.d_ < y.d_)));
      }
#endif
      friend bool operator!=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      friend bool operator> (const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      friend bool operator<=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      friend bool operator>=(const rel_date& x, const rel_date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }

#if BOOST_CHRONO_DATE_REL_DATE_DESIGN == 2
    private:
      uint16_t day_from_day_number() const BOOST_NOEXCEPT;
      uint16_t month_from_day_number() const BOOST_NOEXCEPT;
      int16_t year_from_day_number() const BOOST_NOEXCEPT;
      bool leap_from_day_number() const BOOST_NOEXCEPT;
#elif BOOST_CHRONO_DATE_REL_DATE_DESIGN == 3
      uint32_t day_number_from_ymd() const BOOST_NOEXCEPT;
#endif
    };

    template <>
    struct is_date<rel_date> : true_type {};

    inline rel_date operator/(year_month ym, nth_weekday d)
    {
      return rel_date(ym.get_year(), ym.get_month(), d);
    }
    inline rel_date operator/(year_month ym, nth d)
    {
      return rel_date(ym.get_year(), ym.get_month(), d);
    }
    inline rel_date operator/(year_month ym, last_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(6));
    }
    inline rel_date operator/(year_month ym, _1st_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(1));
    }
    inline rel_date operator/(year_month ym, _2nd_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(2));
    }
    inline rel_date operator/(year_month ym, _3rd_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(3));
    }
    inline rel_date operator/(year_month ym, _4th_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(4));
    }
    inline rel_date operator/(year_month ym, _5th_t)
    {
      return rel_date(ym.get_year(), ym.get_month(), nth(5));
    }
    inline rel_date operator/(month_nth_weekday md, year y)
    {
      return rel_date(y, md.get_month(), md.get_nth_weekday());
    }

    inline rel_date operator/(month_nth_weekday md, year::rep y)
    {
      return md / year(y);
    }

    inline rel_date operator/(month_nth md, year y)
    {
      return rel_date(y, md.get_month(), md.get_nth());
    }

    inline rel_date operator/(month_nth md, year::rep y)
    {
      return md / year(y);
    }

  } // chrono

} // boost

#endif  // header
