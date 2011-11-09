//  julian
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_CHRONO_EXAMPLE_DATE_JULIAN_HPP
#define BOOST_CHRONO_EXAMPLE_DATE_JULIAN_HPP

/*
 julian synopsis

 namespace julian
 {

 // A date
 class date
 {
 public:
 // construction
 explicit date(boost::chrono::date d);
 explicit operator boost::chrono::date() const;

 // obervers
 day day() const;
 month month() const;
 year year() const;
 weekday weekday();
 bool is_leap_year() const;

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
 bool operator==(const date& x, const date& y);
 bool operator!=(const date& x, const date& y);
 bool operator< (const date& x, const date& y);
 bool operator> (const date& x, const date& y);
 bool operator<=(const date& x, const date& y);
 bool operator>=(const date& x, const date& y);

 // date day arithmetic
 date operator+(date dt, days d);
 date operator+(days d, date dt);
 date operator-(date dt, days d);
 days operator-(date x, date y);

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
 operator int() const;
 };

 // A month specifier
 class month
 {
 public:
 explicit month(int);
 operator int() const;
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
 day(__unnamed);
 operator int() const;
 };

 // A day of the week specifier
 class weekday
 {
 public:
 explicit weekday(int);
 operator int() const;
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

 extern const __unnamed first;
 extern const __unnamed second;
 extern const __unnamed third;
 extern const __unnamed fourth;
 extern const __unnamed fifth;
 extern const __unnamed last;

 // Date generation functions

 date operator/(year_month, day);    // year(2011)/month(8)/day(19)
 date operator/(month_day, year);    // month(8)/day(19)/year(2011)
 // day(19)/month(8)/year(2011)
 date operator/(year_month, int);    // year(2011)/month(8)/19
 date operator/(month_day, int);     // month(8)/day(19)/2011
 // day(19)/month(8)/2011

 year_month operator/(year, month);  // year(2011)/month(8)
 year_month operator/(year, int m);  // year(2011)/8

 month_day operator/(day, month);    // day(19)/month(8)
 month_day operator/(month, day);    // month(8)/day(19)
 month_day operator/(day, int m);    // day(19)/8
 month_day operator/(month, int d);  // month(8)/19
 month_day operator/(int m, day);    // 8/day(19)

 day operator*(__unnamed, weekday);  // last*fri  ->  last*fri/aug/2011
 day operator*(int, weekday);        // 2*tue     ->  2*tue/aug/2011

 // Date durations

 class days
 {
 public:
 typedef std::int32_t rep;
 explicit days(rep x = rep());

 rep count() const;

 days operator+() const;
 days operator-() const;

 days& operator++();
 days  operator++(int);
 days& operator--();
 days  operator--(int);

 days& operator+=(const days& x);
 days& operator-=(const days& x);

 days& operator*=(const rep& rhs);
 days& operator/=(const rep& rhs);
 days& operator%=(const rep& rhs);
 days& operator%=(const days& rhs);
 };

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
 explicit months(rep x = rep());

 rep count() const;

 months operator+() const;
 months operator-() const;

 months& operator++();
 months  operator++(int);
 months& operator--();
 months  operator--(int);

 months& operator+=(const months& x);
 months& operator-=(const months& x);

 months& operator*=(const rep& rhs);
 months& operator/=(const rep& rhs);
 months& operator%=(const rep& rhs);
 months& operator%=(const months& rhs);
 };

 months operator+(months x, months y);
 months operator-(months x, months y);
 months operator*(months x, months::rep y);
 months operator*(months::rep x, months y);
 months operator/(months x, months::rep y);
 months::rep operator/(months x, months y);
 months operator%(months x, months::rep y);
 months operator%(months x, months y);

 bool operator==(months x, months y);
 bool operator!=(months x, months y);
 bool operator< (months x, months y);
 bool operator> (months x, months y);
 bool operator<=(months x, months y);
 bool operator>=(months x, months y);

 class years
 {
 public:
 typedef std::int32_t rep;
 explicit years(rep x = rep());

 rep count() const;

 years operator+() const;
 years operator-() const;

 years& operator++();
 years  operator++(int);
 years& operator--();
 years  operator--(int);

 years& operator+=(const years& x);
 years& operator-=(const years& x);

 years& operator*=(const rep& rhs);
 years& operator/=(const rep& rhs);
 years& operator%=(const rep& rhs);
 years& operator%=(const years& rhs);
 };

 years operator+(years x, years y);
 years operator-(years x, years y);
 years operator*(years x, years::rep y);
 years operator*(years::rep x, years y);
 years operator/(years x, years::rep y);
 years::rep operator/(years x, years y);
 years operator%(years x, years::rep y);
 years operator%(years x, years y);

 bool operator==(years x, years y);
 bool operator!=(years x, years y);
 bool operator< (years x, years y);
 bool operator> (years x, years y);
 bool operator<=(years x, years y);
 bool operator>=(years x, years y);

 class bad_date
 : public std::exception
 {
 public:
 virtual const char* what() const noexcpt();
 };

 template<class CharT>
 unspecified
 date_fmt(std::basic_string<CharT> fmt);

 template<class CharT>
 unspecified
 date_fmt(const CharT* fmt);

 template<class CharT, class Traits>
 std::basic_istream<CharT,Traits>&
 operator>>(std::basic_istream<CharT,Traits>& is, date& d);

 template<class CharT, class Traits>
 std::basic_ostream<CharT, Traits>&
 operator<<(std::basic_ostream<CharT, Traits>& os, const date& d);

 }  // julian

 */

#include <exception>
#include <istream>
#include <ostream>
#include <locale>
#include <stdexcept>
#include <boost/cstdint.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/date/date_io.hpp>
#include <boost/chrono/date/relative_date.hpp>

namespace julian
{

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
    day operator*(detail::day_spec, weekday);

  }
  month_day operator/(day, month);
  month_day operator/(day, int);
  month_day operator/(month, day);
  month_day operator/(int, day);
  month_day operator/(month, int);
  year_month operator/(year, month);
  year_month operator/(year, int);

  day operator*(int, weekday);

  date operator/(year_month, day);
  date operator/(year_month, int);
  date operator/(month_day, year);
  date operator/(month_day, int);

  class year
  {
    int32_t y_;
  public:
    explicit year(int32_t y);
    operator int() const
    {
      return y_;
    }

    friend date operator/(month_day, year);
    friend class date;
  };

  class month
  {
    uint8_t m_;
  public:
    explicit month(int);
    operator int() const
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

    day(uint8_t, uint8_t, uint8_t);
  public:
    explicit day(int);
    day(detail::day_spec);
    operator int() const
    {
      return d_;
    }

    friend date operator/(year_month, day);
    friend day detail::operator*(detail::day_spec, weekday);
    friend day operator*(int, weekday);
    friend class date;
  };

  class weekday
  {
    int wd_;

  public:
    explicit weekday(int);
    operator int() const
    {
      return wd_;
    }
    int value() const BOOST_NOEXCEPT
    {
      return wd_;
    }
    friend day detail::operator*(detail::day_spec, weekday);
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
    year_month(year y, month m) :
      y_(y), m_(m)
    {
    }

    friend year_month operator/(year y, month m)
    {
      return year_month(y, m);
    }
    friend year_month operator/(year y, int m)
    {
      return year_month(y, month(m));
    }
    friend date operator/(year_month, day);
  };

  class month_day
  {
    month m_;
    day d_;
    month_day(month m, day d) :
      m_(m), d_(d)
    {
    }

    friend month_day operator/(month m, day d);
    friend month_day operator/(int m, day d);
    friend month_day operator/(month m, int d);
    friend month_day operator/(day d, month m);
    friend month_day operator/(day d, int m);
    friend date operator/(month_day, year);
  };

  inline month_day operator/(month m, day d)
  {
    return month_day(m, d);
  }
  inline month_day operator/(int m, day d)
  {
    return month_day(month(m), d);
  }
  inline month_day operator/(month m, int d)
  {
    return month_day(m, day(d));
  }
  inline month_day operator/(day d, month m)
  {
    return month_day(m, d);
  }
  inline month_day operator/(day d, int m)
  {
    return month_day(month(m), d);
  }
  day operator*(int, weekday);

  namespace detail
  {
    class day_spec
    {
      uint8_t s_;
      day_spec(uint8_t s) :
        s_(s)
      {
      }
      int value() const BOOST_NOEXCEPT
      {
        return s_;
      }
      friend day detail::operator*(day_spec s, weekday wd);
      friend day julian::operator*(int, weekday);
      friend day_spec make_day_spec(uint8_t);
      friend class julian::day;
    };
    inline day operator*(day_spec s, weekday wd)
    {
      return day(1, s.s_, wd.value());
    }
  }

  extern const detail::day_spec last;
  extern const detail::day_spec first;
  extern const detail::day_spec second;
  extern const detail::day_spec third;
  extern const detail::day_spec fourth;
  extern const detail::day_spec fifth;

//  inline day operator*(detail::day_spec s, weekday wd)
//  {
//    return day(1, s.s_, wd.wd_);
//  }

  template<class T, int>
  class duration_type
  {
  public:
    typedef T rep;
  private:
    rep x_;
  public:
    explicit duration_type(rep x = rep()) :
      x_(x)
    {
    }

    rep count() const
    {
      return x_;
    }

    duration_type operator+() const
    {
      return *this;
    }
    duration_type operator-() const
    {
      return duration_type(-x_);
    }

    duration_type& operator++()
    { ++x_; return *this;}
    duration_type operator++(int)
    { return duration_type(x_++);}
    duration_type& operator--()
    { --x_; return *this;}
    duration_type operator--(int)
    { return duration_type(x_--);}

    duration_type& operator+=(const duration_type& d)
    { x_ += d.x_; return *this;}
    duration_type& operator-=(const duration_type& d)
    { x_ -= d.x_; return *this;}

    friend duration_type operator+(duration_type x, duration_type y)
    { x += y; return x;}
    friend duration_type operator-(duration_type x, duration_type y)
    { x -= y; return x;}

    duration_type& operator*=(const rep& rhs)
    { x_ *= rhs; return *this;}
    duration_type& operator/=(const rep& rhs)
    { x_ /= rhs; return *this;}
    duration_type& operator%=(const rep& rhs)
    { x_ %= rhs; return *this;}
    duration_type& operator%=(const duration_type& rhs)
    { x_ %= rhs.x_; return *this;}

    friend duration_type operator*(duration_type x, rep y)
    { x *= y; return x;}
    friend duration_type operator*(rep x, duration_type y)
    { y *= x; return y;}
    friend duration_type operator/(duration_type x, rep y)
    { x /= y; return x;}
    friend rep operator/(duration_type x, duration_type y)
    { return x.x_ / y.x_;}
    friend duration_type operator%(duration_type x, rep y)
    { x %= y; return x;}
    friend duration_type operator%(duration_type x, duration_type y)
    { x %= y.x_; return x;}

    friend bool operator==(duration_type x, duration_type y)
    { return x.x_ == y.x_;}
    friend bool operator!=(duration_type x, duration_type y)
    { return !(x == y);}
    friend bool operator< (duration_type x, duration_type y)
    { return x.x_ < y.x_;}
    friend bool operator> (duration_type x, duration_type y)
    { return y < x;}
    friend bool operator<=(duration_type x, duration_type y)
    { return !(y < x);}
    friend bool operator>=(duration_type x, duration_type y)
    { return !(x < y);}

    friend class date;
  };

  typedef duration_type<int32_t, 0> days;
  typedef duration_type<int32_t, 1> months;
  typedef duration_type<int32_t, 2> years;

  class date
  {
    uint32_t x_;
    int16_t y_;
    uint16_t m_ : 4;
    uint16_t d_ : 5;
    uint16_t leap_ : 1;
    uint16_t n_ : 3;
    uint16_t dow_ : 3;

    date(julian::year, julian::month, julian::day);

    friend date operator/(year_month ym, day d);
    friend date operator/(month_day md, year y);
  public:

    explicit date(boost::chrono::date d);
    //    explicit
    operator boost::chrono::date() const;

    julian::day get_day() const
    { return julian::day(d_);}
    julian::month get_month() const
    { return julian::month(m_);}
    julian::year get_year() const
    { return julian::year(y_);}
    bool is_leap_year() const
    { return leap_;}
    julian::weekday get_weekday() const
    { return julian::weekday((x_+5) % 7);}

    date& operator+=(days d);
    date& operator++()
    { return *this += days(1);}
    date operator++(int)
    { date tmp(*this); ++(*this); return tmp;}
    date& operator-=(days d)
    { return *this += days(-d.x_);}
    date& operator--()
    { return *this -= days(1);}
    date operator--(int)
    { date tmp(*this); --(*this); return tmp;}

    friend date operator+(date dt, days d)
    { dt += d; return dt;}
    friend date operator+(days d, date dt)
    { dt += d; return dt;}
    friend date operator-(date dt, days d)
    { dt -= d; return dt;}
    friend days operator-(date x, date y)
    { return days(x.x_ - y.x_);}

    date& operator+=(months m);
    date& operator-=(months m)
    { return *this += months(-m.x_);}

    friend date operator+(date dt, months m)
    { dt += m; return dt;}
    friend date operator+(months m, date dt)
    { dt += m; return dt;}
    friend date operator-(date dt, months m)
    { dt -= m; return dt;}

    date& operator+=(years y);
    date& operator-=(years y)
    { return *this += years(-y.x_);}

    friend date operator+(date dt, years y)
    { dt += y; return dt;}
    friend date operator+(years y, date dt)
    { dt += y; return dt;}
    friend date operator-(date dt, years y)
    { dt -= y; return dt;}

    friend bool operator==(const date& x, const date& y)
    { return x.x_ == y.x_;}
    friend bool operator< (const date& x, const date& y)
    { return x.x_ < y.x_;}
    friend bool operator!=(const date& x, const date& y)
    { return !(x == y);}
    friend bool operator> (const date& x, const date& y)
    { return y < x;}
    friend bool operator<=(const date& x, const date& y)
    { return !(y < x);}
    friend bool operator>=(const date& x, const date& y)
    { return !(x < y);}
  };

  inline date operator/(year_month ym, day d)
  { return date(ym.y_, ym.m_, d);}
  inline date operator/(month_day md, year y)
  { return date(y, md.m_, md.d_);}
  inline date operator/(year_month ym, int d)
  { return ym / day(d);}
  inline date operator/(month_day md, int y)
  { return md / year(y);}

  template<class charT, class traits>
  std::basic_istream<charT,traits>&
  operator >>(std::basic_istream<charT,traits>& is, date& item)
  {
    typename std::basic_istream<charT,traits>::sentry ok(is);
    if (ok)
    {
      std::ios_base::iostate err = std::ios_base::goodbit;
      try
      {
        const std::time_get<charT>& tg = std::use_facet<std::time_get<charT> >
        (is.getloc());
        std::tm t;
        charT pattern[] =
        { '%', 'F'};
        const charT* pb = pattern;
        const charT* pe = pb + 2;
        typedef boost::chrono::datepunct<charT> F;
        std::locale loc = is.getloc();
        if (std::has_facet<F>(loc))
        {
          const F& f = std::use_facet<F>(loc);
          pb = f.get().data();
          pe = pb + f.get().size();
        }
        tg.get(is, 0, is, err, &t, pb, pe);
        if (!(err & std::ios_base::failbit))
        item = month(t.tm_mon+1) / t.tm_mday / year(t.tm_year+1900);
      }
      catch (...)
      {
        err |= std::ios_base::badbit | std::ios_base::failbit;
      }
      is.setstate(err);
    }
    return is;
  }

  template<class charT, class traits>
  std::basic_ostream<charT, traits>&
  operator <<(std::basic_ostream<charT, traits>& os, const date& item)
  {
    typename std::basic_ostream<charT, traits>::sentry ok(os);
    if (ok)
    {
      bool failed;
      try
      {
        const std::time_put<charT>& tp = std::use_facet<std::time_put<charT> >
        (os.getloc());
        std::tm t;
        t.tm_mday = item.get_day();
        t.tm_mon = item.get_month() - 1;
        t.tm_year = item.get_year() - 1900;
        t.tm_wday = item.get_weekday();
        charT pattern[] =
        { '%', 'F'};
        const charT* pb = pattern;
        const charT* pe = pb + 2;
        typedef boost::chrono::datepunct<charT> F;
        std::locale loc = os.getloc();
        if (std::has_facet<F>(loc))
        {
          const F& f = std::use_facet<F>(loc);
          pb = f.fmt().data();
          pe = pb + f.fmt().size();
        }
        failed = tp.put(os, os, os.fill(), &t, pb, pe).failed();
      }
      catch (...)
      {
        failed = true;
      }
      if (failed)
      os.setstate(std::ios_base::failbit | std::ios_base::badbit);
    }
    return os;
  }

} // julian

#endif  // header
