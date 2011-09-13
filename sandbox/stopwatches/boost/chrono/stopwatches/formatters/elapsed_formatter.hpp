//  boost/chrono/stopwatches/stopwatch_formatter.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_STOPWATCHES_FORMATTERS_ELAPSED_HPP
#define BOOST_STOPWATCHES_FORMATTERS_ELAPSED_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>
#include <boost/current_function.hpp>
#include <boost/chrono/stopwatches/detail/adaptive_string.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/format.hpp>
#include <boost/format/group.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <string>
#include <iostream>
#include <cassert>
#include <iomanip>
#define BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT_DEFAULT "%1%"

namespace boost
{
  namespace chrono
  {

    enum duration_style {text, symbol};

    template<typename Ratio=micro, typename CharT = char, typename Traits = std::char_traits<CharT>,
        class Alloc = std::allocator<CharT> >
    class basic_elapsed_formatter
    {

    public:
      typedef basic_format<CharT, Traits> format_type;
      typedef std::basic_string<CharT, Traits, Alloc> string_type;
      typedef CharT char_type;
      typedef std::basic_ostream<CharT, Traits> ostream_type;

      basic_elapsed_formatter() :
        internal_fmt_(BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT_DEFAULT),
            fmt_(internal_fmt_), precision_(3), os_(std::cout),
            style_(basic_elapsed_formatter::symbol_manip)
      {
      }
      basic_elapsed_formatter(const char* fmt, ostream_type& os=std::cout) :
        internal_fmt_(fmt), fmt_(internal_fmt_), precision_(3), os_(os),
            style_(basic_elapsed_formatter::symbol_manip)
      {
      }
      basic_elapsed_formatter(string_type const& fmt) :
        internal_fmt_(fmt), fmt_(internal_fmt_), precision_(3), os_(std::cout),
            style_(basic_elapsed_formatter::symbol_manip)
      {
      }
      basic_elapsed_formatter(format_type & fmt) :
        fmt_(fmt), precision_(3), os_(std::cout),
            style_(basic_elapsed_formatter::symbol_manip)
      {
      }

      void set_precision(std::size_t precision)
      {
        precision_=precision;
        if (precision_ > 9)
          precision_ = 9; // sanity check
      }
      void set_os(ostream_type& os)
      {
        os_=os;
      }
      void set_duration_style(duration_style style)
      {
        if (style==symbol) style_=symbol_manip;
        else if (style==text) style_=text_manip;
      }
      static string_type format(const char* s)
      {
        string_type res(s);
        res += boost::chrono::detail::adaptive_string(" : ");
        res += BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT_DEFAULT;
        return res;
      }

      template<class Stopwatch>
      void operator()(Stopwatch & stopwatch_, system::error_code & ec)
      {
        typedef typename Stopwatch::duration duration_t;
        duration_t d = stopwatch_.elapsed(ec);

        if (d < duration_t::zero())
          return;

        os_
            << fmt_
                % io::group(std::fixed, std::setprecision(precision_), style_, boost::chrono::duration<
                    double, Ratio>(d)) << std::endl;

      }
    private:
      boost::format internal_fmt_;
      boost::format& fmt_;
      std::size_t precision_;
      ostream_type & os_;
      ostream_type& (*style_)(ostream_type& os);

      static ostream_type&
      symbol_manip(ostream_type& os)
      {
        return boost::chrono::duration_short(os);
      }
      static ostream_type&
      text_manip(ostream_type& os)
      {
        return boost::chrono::duration_long(os);
      }

    };



    typedef basic_elapsed_formatter<micro, char> elapsed_formatter;
    typedef basic_elapsed_formatter<micro, wchar_t> welapsed_formatter;

  } // namespace chrono
} // namespace boost

#define BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT(F) \
  boost::chrono::detail::adaptive_string(F " : " BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT_DEFAULT)
#ifdef __GNUC__
#define BOOST_CHRONO_STOPWATCHES_ELAPSED_FUNCTION_FORMAT \
  boost::chrono::elapsed_formatter::format(BOOST_CURRENT_FUNCTION)
#else
#define BOOST_CHRONO_STOPWATCHES_ELAPSED_FUNCTION_FORMAT \
    BOOST_CHRONO_STOPWATCHES_ELAPSED_FORMAT(BOOST_CURRENT_FUNCTION)
#endif

#endif
