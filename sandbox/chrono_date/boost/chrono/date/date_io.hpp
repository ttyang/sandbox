//  date_io.hpp
//
//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_DATE_DATE_IO_HPP
#define BOOST_CHRONO_DATE_DATE_IO_HPP

/*
 Date i/o synopsis

 namespace boost
 {
 namespace chrono
 {


 template <class CharT>
 class datepunct
 : public std::locale::facet
 {
 public:
 typedef std::basic_string<CharT> string_type;

 private:
 string_type fmt_;  // exposition only

 public:
 static std::locale::id id;

 explicit datepunct(std::size_t refs = 0,
 const string_type& fmt = string_type("%F"));
 explicit datepunct(std::size_t refs,
 string_type&& fmt);

 const string_type& fmt() const noexcept;
 };

 template<class CharT>
 unspecified
 date_fmt(std::basic_string<CharT> fmt);

 template<class CharT>
 unspecified
 date_fmt(const CharT* fmt);

 template<class CharT, class Traits>
 std::basic_istream<CharT,Traits>&
 operator>>(std::basic_istream<CharT,Traits>& is, Date& d);

 template<class CharT, class Traits>
 std::basic_ostream<CharT, Traits>&
 operator<<(std::basic_ostream<CharT, Traits>& os, const Date& d);

 }  // chrono
 }  // std

 */

#include <istream>
#include <ostream>
#include <locale>
#include <boost/cstdint.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/date/year.hpp>
#include <boost/chrono/date/month.hpp>
#include <boost/chrono/date/day.hpp>
#include <boost/chrono/date/is_date.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/chrono/config.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * @c datepunct is a facet which holds a string of formatting characters to be used with @c time_get and @c time_put.
     */
    template<class charT>
    class datepunct: public std::locale::facet
    {
    public:
      typedef std::basic_string<charT> string_type;

      static std::locale::id id;

      /**
       *
       * @param refs
       * @Effects Constructs a @c datepunct by constructing the base class with @c refs.
       * @Postconditions <c>fmt() == "%F"</c>.
       */
      explicit datepunct(std::size_t refs = 0) :
        std::locale::facet(refs)
      {
        fmt_.push_back('%');
        fmt_.push_back('F');
      }

      /**
       *
       * @param fmt
       * @param refs
       * @Effects: Constructs a @c datepunct by constructing the base class with @c refs.
       * @Postconditions: <c>fmt() == frmt</c>.
       */
      explicit datepunct(string_type fmt, std::size_t refs = 0) :
        std::locale::facet(refs),
        //#if ! defined BOOST_NO_RVALUE_DEFERENCES
            //      fmt_(std::move(fmt))
            //#else
            fmt_(fmt)
      //#endif
      {
      }

      /**
       * @Returns: the stored format.
       */
      const string_type& fmt() const BOOST_NOEXCEPT
      {
        return fmt_;
      }
    private:
      string_type fmt_;

    };

    template<class CharT>
    std::locale::id datepunct<CharT>::id;

    template<class charT>
    struct date_manip
    {
      std::basic_string<charT> fmt_;

      explicit date_manip(std::basic_string<charT> fmt)
      //#if ! defined BOOST_NO_RVALUE_DEFERENCES
      //      : fmt_(std::move(fmt))
      //      {
      //      }
      //#else
      :
        fmt_(fmt)
      {
      }
      //#endif
    };

    template<class charT, class traits>
    std::basic_ostream<charT, traits>&
    operator <<(std::basic_ostream<charT, traits>& os, date_manip<charT> m)
    {
      //#if ! defined BOOST_NO_RVALUE_DEFERENCES
      //      os.imbue(std::locale(os.getloc(), new datepunct<charT>(std::move(m.fmt_))));
      //#else
      os.imbue(std::locale(os.getloc(), new datepunct<charT> (m.fmt_)));
      //#endif
      return os;
    }

    template<class charT, class traits>
    std::basic_istream<charT, traits>&
    operator >>(std::basic_istream<charT, traits>& is, date_manip<charT> m)
    {
      //#if ! defined BOOST_NO_RVALUE_DEFERENCES
      //      is.imbue(std::locale(is.getloc(), new datepunct<charT>(std::move(m.fmt_))));
      //#else
      is.imbue(std::locale(is.getloc(), new datepunct<charT> (m.fmt_)));
      //#endif
      return is;
    }

    /**
     * Date format manipulator
     * @param fmt the format following the syntax in specified in $.
     * @Returns: An object of unspecified type such that if @c out is an object
     * of type @c basic_ostream<CharT,Traits> then the expression
     * <c>out << date_fmt(fmt)</c> behaves as if it called
     * <c>f(out, fmt)</c>, or if @c in is an object of type
     * <c>basic_istream<charT, traits></c> then the expression
     * <c>in >> date_fmt(fmt)</c> behaves as if it called <c>f(in, fmt)</c>,
     * where the function @c f is defined as:
     * @code
     *   template<class charT, class traits>
     *   void f(basic_ios<charT, traits>& str, basic_string<charT> fmt)
     *   {
     *     str.imbue(locale(str.getloc(), new datepunct<charT>(move(fmt))));
     *   }
     * @endcode
     */
    template<class charT>
    inline date_manip<charT> date_fmt(std::basic_string<charT> fmt)
    {
      //#if ! defined BOOST_NO_RVALUE_DEFERENCES
      //      return date_manip<charT>(std::move(fmt));
      //#else
      return date_manip<charT> (fmt);
      //#endif
    }

    /**
     * Date format manipulator
     * @param fmt the format following the syntax in specified in $.
     * @return <c>date_fmt(std::string(fmt))</c>
     */
    template<class charT>
    inline date_manip<charT> date_fmt(const charT* fmt)
    {
      return date_manip<charT> (fmt);
    }

    /**
     *
     * @param is
     * @param item
     * @Effects: Behaves as a formatted input function. After constructing a
     * @c sentry object, if the @c sentry converts to @c true, acquires the
     * @c time_get facet from the stream's locale. If the locale has a
     * @c datepunct facet,obtains the conversion specifier string from that
     * facet, otherwise sets the conversion specifier string to @c "%F".
     * Then extracts a @c tm from is as if:
     * @code
     *   tg.get(is, 0, is, err, &t, fmt, fmtend);
     * @endcode
     *
     * Where @c tg is the @c time_get facet, @c err is a local variable of type
     * @c ios_base::iostate, @c t is a local variable of type @c tm, and
     * [@cfmt, @cfmtend) are local variables of type @c charT* which delimit
     * the conversion specifier string.
     *
     * If <c>(err & ios_base::failbit)</c> is @c false, assigns a date to @c d
     * which is constructed from the @c year, @c month and @c day information
     * stored within t. In any case, then calls <c>is.setstate(err)</c>.

    Returns: is.

     */
    template<class charT, class traits, typename Date>
    typename enable_if<is_date<Date> , std::basic_istream<charT, traits>&>::type
    operator >>(std::basic_istream<
        charT, traits>& is, Date& item)
    {
      typename std::basic_istream<charT, traits>::sentry ok(is);
      if (ok)
      {
        std::ios_base::iostate err = std::ios_base::goodbit;
        try
        {
          const std::time_get<charT>& tg =
              std::use_facet<std::time_get<charT> >(is.getloc());
          std::tm t;
          charT pattern[] =
          { '%', 'F' };
          const charT* pb = pattern;
          const charT* pe = pb + 2;
          typedef datepunct<charT> F;
          std::locale loc = is.getloc();
          if (std::has_facet<F>(loc))
          {
            const F& f = std::use_facet<F>(loc);
            pb = f.fmt().data();
            pe = pb + f.fmt().size();
          }
          tg.get(is, 0, is, err, &t, pb, pe);
          if (!(err & std::ios_base::failbit))
          {
            item
                = Date(year(t.tm_year + 1900), month(t.tm_mon + 1), day(t.tm_mday));
          }
        }
        catch (...)
        {
          err |= std::ios_base::badbit | std::ios_base::failbit;
        }
        is.setstate(err);
      }
      return is;
    }

    /**
     *
     * @param os
     * @param item
     * @Effects: Behaves as a formatted output function. After constructing a
     * @c sentry object, if the @c sentry converts to @c true, acquires the
     * @c time_put facet from the stream's locale. If the locale has a
     * @c datepunct facet, obtains the formatting string from that facet,
     * otherwise sets the formatting string to @c "%F". Then creates a local
     * variable @c t of type @c tm. The variable @c t is filled with the @c year,
     * @c month, @c day and @c weekday information contained in @c d. @c t is
     * then inserted into @c os as if:
     * @code
     *   bool failed = tp.put(os, os, os.fill(), &t, pattern, pat_end).failed();
     * @endcode
     *
     * Where @c tp is the @c time_put facet, and <c>[pattern, pat_end)<c> are
     * local variables of type @c charT* which delimit the formatting string.
     *
     * If @c failed is @c true, calls <c>os.setstate(ios_base::failbit | ios_base::badbit)</c>.
     *
     * @Returns: os.
     */
    template<class charT, class traits, typename Date>
    typename enable_if<is_date<Date> , std::basic_ostream<charT, traits>&>::type
    operator <<(std::basic_ostream<
        charT, traits>& os, const Date& item)
    {
      typename std::basic_ostream<charT, traits>::sentry ok(os);
      if (ok)
      {
        bool failed;
        try
        {
          const std::time_put<charT>& tp =
              std::use_facet<std::time_put<charT> >(os.getloc());
          std::tm t;
          t.tm_mday = item.get_day();
          t.tm_mon = item.get_month() - 1;
          t.tm_year = item.get_year() - 1900;
          t.tm_wday = item.get_weekday();
          charT pattern[] =
          { '%', 'F' };
          const charT* pb = pattern;
          const charT* pe = pb + 2;
          typedef datepunct<charT> F;
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
        {
          os.setstate(std::ios_base::failbit | std::ios_base::badbit);
        }
      }
      return os;
    }

  } // chrono

} // boost

#endif  // header
