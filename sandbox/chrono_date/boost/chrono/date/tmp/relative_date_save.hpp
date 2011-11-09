//  date
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_HPP
#define BOOST_CHRONO_DATE_DATE_HPP

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
 day day() const noexcept;
 month month() const noexcept;
 year year() const noexcept;
 weekday weekday() const noexcept;
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

#include <exception>
#include <istream>
#include <ostream>
#include <locale>
#include <stdexcept>
#include <boost/cstdint.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/config.hpp>

#ifndef DESIGN
#define DESIGN 1
#endif

namespace boost
{
  namespace chrono
  {

    typedef duration<boost::int_least32_t, boost::ratio<86400> > days;
    typedef duration<boost::int_least32_t, boost::ratio<7*86400> > weeks;
    typedef duration<boost::int_least32_t, boost::ratio<2629746>  >  average_months;
    typedef duration<boost::int_least32_t, boost::ratio<31556952>  >  average_years;
    typedef duration<boost::int_least32_t, boost::ratio<400*31556952>  >  _400_years;

    class BOOST_CHRONO_DECL days_count_clock
    {
    public:
        typedef days                                  duration;
        typedef duration::rep                         rep;
        typedef duration::period                      period;
        typedef chrono::time_point<days_count_clock>  time_point;
        BOOST_STATIC_CONSTEXPR bool is_steady = true;

        static BOOST_CHRONO_INLINE time_point  now() BOOST_NOEXCEPT;
  #if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
        static BOOST_CHRONO_INLINE time_point  now(system::error_code & ec);
  #endif

        static BOOST_CHRONO_INLINE std::time_t to_time_t(const time_point& t) BOOST_NOEXCEPT;
        static BOOST_CHRONO_INLINE time_point  from_time_t(std::time_t t) BOOST_NOEXCEPT;
    };

    struct no_check_t {};
    const no_check_t no_check = { };

    class bad_date: public std::runtime_error
    {
    public:
      explicit bad_date(const std::string& s) :
        std::runtime_error(s)
      {
      }
      explicit bad_date(const char* s) :
        std::runtime_error(s)
      {
      }
    };

    class date;
    class year;
    class month;
    class day;
    class weekday;
    class year_month;
    class month_day;

    namespace detail
    {
      class day_spec;
    }

    month_day operator/(day, month) BOOST_NOEXCEPT;
    month_day operator/(month, day) BOOST_NOEXCEPT;
    year_month operator/(year, month) BOOST_NOEXCEPT;

    date operator/(year_month, day);
    date operator/(year_month, int);
    date operator/(month_day, year);
    date operator/(month_day, int);

    class year
    {
      int32_t y_;
    public:
      explicit year(int32_t v)  : y_(v)
      {
        if (!(-32768 <= v && v <= 32767))
        {
          throw bad_date("year  is out of range");
        }
      }

      year(int32_t y,no_check_t):y_(y) {}
      operator int() const BOOST_NOEXCEPT
      {
        return y_;
      }

      friend date operator/(month_day, year);
      friend class date;
    };

    class month
    {
      int8_t m_;
    public:
      explicit month(int);
      explicit month(int y,no_check_t):m_(y) {}
      operator int() const BOOST_NOEXCEPT
      {
        return m_;
      }

      friend class date;
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

    class day
    {
      uint16_t d_ :5;
      uint16_t n_ :3;
      uint16_t dow_ :3;

      day(uint8_t, uint8_t, uint8_t) BOOST_NOEXCEPT;
    public:
      explicit day(int);
      day(int d,no_check_t):d_(d),n_(7),dow_(7) {}
      day(detail::day_spec) BOOST_NOEXCEPT;
      operator int() const BOOST_NOEXCEPT
      {
        return d_;
      }

      friend date operator/(year_month, day);
      friend class date;
      friend class weekday;
    };

    namespace detail
    {

      //day_spec make_day_spec(uint8_t) BOOST_NOEXCEPT;
      class day_spec
      {
        uint8_t s_;
        day_spec(uint8_t s) BOOST_NOEXCEPT : s_(s)
        {
        }
        friend day_spec make_day_spec(uint8_t) BOOST_NOEXCEPT;
        friend class boost::chrono::day;
        friend class boost::chrono::weekday;
      };
    }
    extern const detail::day_spec last;
    extern const detail::day_spec _1st;
    extern const detail::day_spec _2nd;
    extern const detail::day_spec _3rd;
    extern const detail::day_spec _4th;
    extern const detail::day_spec _5th;

    class weekday
    {
      uint8_t wd_;

    public:
      explicit weekday(int);
      explicit weekday(int wd,no_check_t):wd_(wd){};
      operator int() const BOOST_NOEXCEPT
      {
        return wd_;
      }

      day operator[](int) const;
      day operator[](detail::day_spec s) const BOOST_NOEXCEPT
      {
        return day(0, s.s_, wd_);
      }
    };

    extern const weekday sun;
    extern const weekday mon;
    extern const weekday tue;
    extern const weekday wed;
    extern const weekday thu;
    extern const weekday fri;
    extern const weekday sat;

    class year_month
    {
      year y_;
      month m_;
      year_month(year y, month m) BOOST_NOEXCEPT
      : y_(y),
      m_(m)
      {
      }

      friend year_month operator/(year y, month m) BOOST_NOEXCEPT
      {
        return year_month(y, m);
      }
      friend date operator/(year_month, day);
      int days_in() BOOST_NOEXCEPT;
    };

    class month_day
    {
      month m_;
      day d_;
      month_day(month m, day d) BOOST_NOEXCEPT
      : m_(m),
      d_(d)
      {
      }
      friend month_day make_month_day(month m, day d) BOOST_NOEXCEPT;

      friend month_day operator/(month m, day d) BOOST_NOEXCEPT;
      friend month_day operator/(day d, month m) BOOST_NOEXCEPT;
      friend date operator/(month_day, year);
    };

    extern const month_day
    jan_01, jan_02, jan_03, jan_04, jan_05, jan_06, jan_07, jan_08, jan_09,
    jan_10, jan_11, jan_12, jan_13, jan_14, jan_15, jan_16, jan_17, jan_18,
    jan_19, jan_20, jan_21, jan_22, jan_23, jan_24, jan_25, jan_26, jan_27,
    jan_28, jan_29, jan_30, jan_31
    // ...
    ;


    inline month_day operator/(month m, day d) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }
    inline month_day operator/(day d, month m) BOOST_NOEXCEPT
    {
      return month_day(m, d);
    }

    namespace detail
    {
      template <class T, int>
      class duration_type
      {
      public:
        typedef T rep;
      private:
      public:
        rep x_;
      public:
        explicit duration_type(rep x = rep()) BOOST_NOEXCEPT : x_(x)
        {
        }

        rep count() const BOOST_NOEXCEPT
        {
          return x_;
        }

        duration_type operator+() const BOOST_NOEXCEPT
        {
          return *this;
        }
        duration_type operator-() const BOOST_NOEXCEPT
        {
          return duration_type(-x_);
        }

        duration_type& operator++() BOOST_NOEXCEPT
        {
          ++x_;
          return *this;
        }
        duration_type operator++(int) BOOST_NOEXCEPT
        {
          return duration_type(x_++);
        }
        duration_type& operator--() BOOST_NOEXCEPT
        {
          --x_;
          return *this;
        }
        duration_type operator--(int) BOOST_NOEXCEPT
        {
          return duration_type(x_--);
        }

        duration_type& operator+=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ += rhs.x_;
          return *this;
        }
        duration_type& operator-=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ -= rhs.x_;
          return *this;
        }

        friend duration_type operator+(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x += y;
          return x;
        }
        friend duration_type operator-(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x -= y;
          return x;
        }

        duration_type& operator*=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ *= rhs;
          return *this;
        }
        duration_type& operator/=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ /= rhs;
          return *this;
        }
        duration_type& operator%=(const rep& rhs) BOOST_NOEXCEPT
        {
          x_ %= rhs;
          return *this;
        }
        duration_type& operator%=(const duration_type& rhs) BOOST_NOEXCEPT
        {
          x_ %= rhs.x_;
          return *this;
        }

        friend duration_type operator*(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x *= y;
          return x;
        }
        friend duration_type operator*(rep x, duration_type y) BOOST_NOEXCEPT
        {
          y *= x;
          return y;
        }
        friend duration_type operator/(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x /= y;
          return x;
        }
        friend rep operator/(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ / y.x_;
        }
        friend duration_type operator%(duration_type x, rep y) BOOST_NOEXCEPT
        {
          x %= y;
          return x;
        }
        friend duration_type operator%(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          x %= y.x_;
          return x;
        }

        friend bool operator==(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ == y.x_;
        }
        friend bool operator!=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(x == y);
        }
        friend bool operator< (duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return x.x_ < y.x_;
        }
        friend bool operator> (duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return y < x;
        }
        friend bool operator<=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(y < x);
        }
        friend bool operator>=(duration_type x, duration_type y) BOOST_NOEXCEPT
        {
          return !(x < y);
        }

        friend class date;
      };
    }

    typedef detail::duration_type<int32_t, 1> months;
    typedef detail::duration_type<int32_t, 2> years;

    class date
    {
#if DESIGN == 1
      // Store x, y/m/d, n, dow
      uint32_t x_;
      int16_t y_;
      uint16_t m_ : 4;
      uint16_t d_ : 5;
      uint16_t leap_ : 1;
      uint16_t n_ : 3;
      uint16_t dow_ : 3;
#elif DESIGN == 2
      // Store x, n, dow
      uint32_t x_ : 26;
      uint32_t n_ : 3;
      uint32_t dow_ : 3;
#elif DESIGN == 3
      // Store y/m/d, n, dow
      int16_t y_;
      uint16_t m_ : 4;
      uint16_t d_ : 5;
      uint16_t leap_ : 1;
      uint16_t n_ : 3;
      uint16_t dow_ : 3;
#endif


      friend date operator/(year_month ym, day d);
      friend date operator/(month_day md, year y);
    public:
      date(chrono::year, chrono::month, chrono::day);
      date(chrono::year, chrono::month, chrono::day, no_check_t);

      static date today() BOOST_NOEXCEPT;

      date() BOOST_NOEXCEPT;

      explicit date(boost::chrono::system_clock::time_point tp);
      // explicit
      operator boost::chrono::system_clock::time_point () const;

#if DESIGN == 1 || DESIGN == 3
      chrono::day get_day() const BOOST_NOEXCEPT
      {
        return chrono::day(d_,no_check);
      }
      chrono::month get_month() const BOOST_NOEXCEPT
      {
        return chrono::month(m_,no_check);
      }
      chrono::year get_year() const BOOST_NOEXCEPT
      {
        return chrono::year(y_,no_check);
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_;
      }
#elif DESIGN == 2
      chrono::day get_day() const BOOST_NOEXCEPT
      {
        return chrono::day(day_from_day_number(),no_check);
      }
      chrono::month get_month() const BOOST_NOEXCEPT
      {
        return chrono::month(month_from_day_number(),no_check);
      }
      chrono::year get_year() const BOOST_NOEXCEPT
      {
        return chrono::year(year_from_day_number(),no_check);
      }
      bool is_leap_year() const BOOST_NOEXCEPT
      {
        return leap_from_day_number();
      }
#endif
#if DESIGN == 1 || DESIGN == 2
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((x_+1) % 7,no_check);
      }
#elif DESIGN == 3
      chrono::weekday get_weekday() const BOOST_NOEXCEPT
      {
        return chrono::weekday((day_number_from_ymd()+1) % 7,no_check);
      }
#endif

      date& operator+=(days d);
      date& operator++()
      {
        return *this += days(1);
      }
      date operator++(int)
      {
        date tmp(*this);
        ++(*this);
        return tmp;
      }
      date& operator-=(days d)
      {
        return *this += -d;
      }
      date& operator--()
      {
        return *this -= days(1);
      }
      date operator--(int)
      {
        date tmp(*this); --(*this); return tmp;
      }

      friend date operator+(date dt, days d)
      {
        dt += d;
        return dt;
      }
      friend date operator+(days d, date dt)
      {
        dt += d;
        return dt;
      }
      friend date operator-(date dt, days d)
      {
        dt -= d;
        return dt;
      }
#if DESIGN == 1 || DESIGN == 2
      friend days operator-(date x, date y) BOOST_NOEXCEPT
      {
        return days(x.x_ - y.x_);
      }
#elif DESIGN == 3
      friend days operator-(date x, date y) BOOST_NOEXCEPT
      {
        return days(x.day_number_from_ymd() - y.day_number_from_ymd());
      }
#endif

      date& operator+=(months m);
      date& operator-=(months m)
      {
        return *this += months(-m.x_);
      }

      friend date operator+(date dt, months m)
      {
        dt += m;
        return dt;
      }
      friend date operator+(months m, date dt)
      {
        dt += m;
        return dt;
      }
      friend date operator-(date dt, months m)
      {
        dt -= m;
        return dt;
      }

      date& operator+=(years y);
      date& operator-=(years y)
      {
        return *this += years(-y.x_);
      }

      friend date operator+(date dt, years y)
      {
        dt += y;
        return dt;
      }
      friend date operator+(years y, date dt)
      {
        dt += y;
        return dt;
      }
      friend date operator-(date dt, years y)
      {
        dt -= y;
        return dt;
      }

#if DESIGN == 1 || DESIGN == 2
      friend bool operator==(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.x_ == y.x_;
      }
      friend bool operator< (const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.x_ < y.x_;
      }
#elif DESIGN == 3
      friend bool operator==(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return x.y_ == y.y_ && x.m_ == y.m_ && x.d_ == y.d_;
      }
      friend bool operator< (const date& x, const date& y)
      {
        return x.y_ < y.y_ ||
        (!(y.y_ < x.y_) && (x.m_ < y.m_ ||
                (!(y.m_ < x.m_) && x.d_ < y.d_)));
      }
#endif
      friend bool operator!=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(x == y);
      }
      friend bool operator> (const date& x, const date& y) BOOST_NOEXCEPT
      {
        return y < x;
      }
      friend bool operator<=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(y < x);
      }
      friend bool operator>=(const date& x, const date& y) BOOST_NOEXCEPT
      {
        return !(x < y);
      }

#if DESIGN == 2
    private:
      uint16_t day_from_day_number() const BOOST_NOEXCEPT;
      uint16_t month_from_day_number() const BOOST_NOEXCEPT;
      int16_t year_from_day_number() const BOOST_NOEXCEPT;
      bool leap_from_day_number() const BOOST_NOEXCEPT;
#elif DESIGN == 3
      uint32_t day_number_from_ymd() const BOOST_NOEXCEPT;
#endif
    };

    inline date operator/(year_month ym, day d)
    {
      return date(ym.y_, ym.m_, d);
    }
    inline date operator/(month_day md, year y)
    {
      return date(y, md.m_, md.d_);
    }
    inline date operator/(year_month ym, int d)
    {
      return ym / day(d);
    }
    inline date operator/(month_day md, int y)
    {
      return md / year(y);
    }

    inline
    date
    operator<(weekday wd, date x)
    {
      const int a = static_cast<int>(wd);
      const int b = static_cast<int>(x.get_weekday());
      if (a < b)
      {
        return x - days(b-a);
      }
      return x - days(7 - (a-b));
    }

    inline
    date
    operator<=(weekday wd, date x)
    {
      const int a = static_cast<int>(wd);
      const int b = static_cast<int>(x.get_weekday());
      if (a <= b)
      {
        return x - days(b-a);
      }
      return x - days(7 - (a-b));
    }

    inline
    date
    operator>(weekday wd, date x)
    {
      const int a = static_cast<int>(x.get_weekday());
      const int b = static_cast<int>(wd);
      if (a < b)
      {
        return x + days(b-a);
      }
      return x + days(7 - (a-b));
    }

    inline
    date
    operator>=(weekday wd, date x)
    {
      const int a = static_cast<int>(x.get_weekday());
      const int b = static_cast<int>(wd);
      if (a <= b)
      {
        return x + days(b-a);
      }
      return x + days(7 - (a-b));
    }



  } // chrono

} // boost

#endif  // header
