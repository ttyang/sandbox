//  boost/chrono/stopwatches/stopwatch_formatter.hpp  ------------------------------------------------------------//
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_STOPWATCHES_FORMATTERS_ONESHOT_HPP
#define BOOST_STOPWATCHES_FORMATTERS_ONESHOT_HPP

#include <boost/chrono/chrono.hpp>
#include <boost/system/error_code.hpp>
#include <boost/current_function.hpp>
#include <boost/chrono/stopwatches/detail/adaptive_string.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <iostream>
#include <boost/io/ios_state.hpp>
#include <cstring>
#include <cassert>
#include <boost/assert.hpp>
#include <boost/chrono/duration_style.hpp>
#include <boost/chrono/chrono_io.hpp>

#define BOOST_CHRONO_STOPWATCHES_ONESHOOT_FORMAT_DEFAULT "%d\n"

namespace boost
{
  namespace chrono
  {

    template<typename CharT = char, typename Traits = std::char_traits<CharT>,
        class Alloc = std::allocator<CharT> >
    class basic_oneshot_formatter
    {
    public:
      typedef std::basic_string<CharT, Traits, Alloc> string_type;
      typedef CharT char_type;
      typedef std::basic_ostream<CharT, Traits> ostream_type;

      basic_oneshot_formatter() :
        format_(BOOST_CHRONO_STOPWATCHES_ONESHOOT_FORMAT_DEFAULT),
            precision_(3), os_(std::cout)
      {
      }
      basic_oneshot_formatter(ostream_type& os) :
        format_(BOOST_CHRONO_STOPWATCHES_ONESHOOT_FORMAT_DEFAULT),
            precision_(3), os_(os)
      {
      }
      basic_oneshot_formatter(const char_type* fmt, ostream_type& os =
          std::cout) :
        format_(fmt), precision_(3), os_(os)
      {
      }
      basic_oneshot_formatter(string_type const& fmt, ostream_type& os =
          std::cout) :
        str_(fmt), format_(str_.c_str()), precision_(3), os_(os)
      {
      }
      void set_precision(std::size_t precision)
      {
        precision_ = precision;
        if (precision_ > 9)
          precision_ = 9; // sanity check
      }
      void set_os(ostream_type os)
      {
        os_ = os;
      }
      static string_type format(const char* s)
      {
        string_type res(s);
        res += boost::chrono::detail::adaptive_string(" : ");
        res += BOOST_CHRONO_STOPWATCHES_ONESHOOT_FORMAT_DEFAULT;
        return res;
      }

      template<class Stopwatch>
      void operator()(Stopwatch & stopwatch_, system::error_code & ec)
      {
        typedef typename Stopwatch::duration duration_t;
        duration_t d = stopwatch_.elapsed(ec);

        if (d < duration_t::zero())
          return;

        boost::io::ios_flags_saver ifs(os_);
        os_.setf(std::ios_base::fixed, std::ios_base::floatfield);
        boost::io::ios_precision_saver ips(os_);
        os_.precision(precision_);

        for (; *format_; ++format_)
        {
          if ((*format_ != '%') || (!*(format_ + 1))
              || (!std::strchr("d", *(format_ + 1))))
          {
            os_ << *format_;
          } else
          {
            ++format_;
            switch (*format_)
            {
            case 'd':
              os_ << boost::chrono::duration<double>(d).count();
              break;
            default:
              // todo this should be replaced by a ec or an exception.
              BOOST_ASSERT(0
                  && "basic_stopwatch_formatter internal logic error");
            }
          }
        }
      }
    private:
      string_type str_;
      const char_type* format_;
      std::size_t precision_;
      ostream_type & os_;
    };

    typedef basic_oneshot_formatter<char> oneshot_formatter;
    typedef basic_oneshot_formatter<wchar_t> woneshot_formatter;

  } // namespace chrono
} // namespace boost

#define BOOST_CHRONO_STOPWATCHES_ONESHOT_FORMAT(F) \
  boost::chrono::detail::adaptive_string(F " : " BOOST_CHRONO_STOPWATCHES_ONESHOOT_FORMAT_DEFAULT)
#ifdef __GNUC__
#define BOOST_CHRONO_STOPWATCHES_ONESHOT_FUNCTION_FORMAT \
  boost::chrono::oneshot_formatter::format(BOOST_CURRENT_FUNCTION)
#else
#define BOOST_CHRONO_STOPWATCHES_ONESHOT_FUNCTION_FORMAT \
    BOOST_CHRONO_STOPWATCHES_ONESHOT_FORMAT(BOOST_CURRENT_FUNCTION)
#endif

#endif
