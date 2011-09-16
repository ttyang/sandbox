//  boost/chrono/stopwatches/stopwatch_reporter2.hpp
//  Copyright 2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or
//   copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_REPORTERS_STOPWATCH_REPORTER_HPP
#define BOOST_CHRONO_STOPWATCHES_REPORTERS_STOPWATCH_REPORTER_HPP

#if !defined(BOOST_ENABLE_WARNINGS) && !defined(BOOST_STOPWATCHES_ENABLE_WARNINGS) 
#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif
#endif

#include <boost/chrono/chrono.hpp>
#include <boost/chrono/stopwatches/stopwatch_scoped.hpp>
#include <boost/system/error_code.hpp>
#include <boost/chrono/stopwatches/clock_suspender.hpp>
#include <boost/cstdint.hpp>
#include <cassert>

namespace boost
{
  namespace chrono
  {

    template<class Stopwatch, class Formatter>
    class basic_stopwatch_reporter2: public Stopwatch
    {
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      basic_stopwatch_reporter2() :
        formatter_(), reported_(false)
      {
      }

      explicit basic_stopwatch_reporter2(const typename Formatter::char_type* fmt) :
        formatter_(fmt), reported_(false)
      {
      }
      explicit basic_stopwatch_reporter2(typename Formatter::string_type const& fmt) :
        formatter_(fmt), reported_(false)
      {
      }
      explicit basic_stopwatch_reporter2(formatter_type const& fmt) :
        formatter_(fmt), reported_(false)
      {
      }

      ~basic_stopwatch_reporter2() // never throws
      {
        system::error_code ec;
        if (!reported())
        {
          this->report(ec);
        }
      }

      inline void report(system::error_code & /*ec*/= BOOST_CHRONO_THROWS);
      bool reported() const
      {
        return reported_;
      }

      typedef stopwatch_runner<basic_stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_run;
      typedef stopwatch_stopper<basic_stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_stop;
      typedef stopwatch_suspender<basic_stopwatch_reporter2<Stopwatch,
          Formatter> > scoped_suspend;
      typedef stopwatch_resumer<basic_stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_resume;

    protected:
      formatter_type formatter_;
      bool reported_;

      basic_stopwatch_reporter2(const basic_stopwatch_reporter2&); // = delete;
      basic_stopwatch_reporter2& operator=(const basic_stopwatch_reporter2&); // = delete;
    };

    template<class Stopwatch, class Formatter>
    void basic_stopwatch_reporter2<Stopwatch, Formatter>::report(system::error_code & ec)
    {
      chrono::clock_suspender<typename Stopwatch::clock> _(ec);
      if (!BOOST_CHRONO_IS_THROWS(ec))
      {
        if (ec)
          return;
      }

      reported_ = true;
      formatter_(*this, ec);
    }

    template<class Stopwatch>
    struct stopwatch_reporter2_default_formatter;

    template<class Stopwatch,
        class Formatter = typename stopwatch_reporter2_default_formatter<
            Stopwatch>::type>
    class stopwatch_reporter2;

    template<class Stopwatch, class Formatter>
    struct stopwatch_reporter2_default_formatter<stopwatch_reporter2<Stopwatch,
        Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class stopwatch_reporter2: public basic_stopwatch_reporter2<Stopwatch,
        Formatter>
    {
      typedef basic_stopwatch_reporter2<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      stopwatch_reporter2()
      //: base_type()
      {
      }
      explicit stopwatch_reporter2(formatter_type const& fmt) :
        base_type(fmt)
      {
      }
      explicit stopwatch_reporter2(const typename Formatter::char_type* fmt) :
        base_type(fmt)
      {
      }
      explicit stopwatch_reporter2(typename Formatter::string_type const& fmt) :
        base_type(fmt)
      {
      }
      typedef stopwatch_runner<stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_run;
      typedef stopwatch_stopper<stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_stop;
      typedef stopwatch_suspender<stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_suspend;
      typedef stopwatch_resumer<stopwatch_reporter2<Stopwatch, Formatter> >
          scoped_resume;

    protected:

      stopwatch_reporter2(const stopwatch_reporter2&); // = delete;
      stopwatch_reporter2& operator=(const stopwatch_reporter2&); // = delete;
    };

    template<class Stopwatch>
    struct wstopwatch_reporter2_default_formatter;

    template<class Stopwatch,
        class Formatter = typename wstopwatch_reporter2_default_formatter<
            Stopwatch>::type>
    class wstopwatch_reporter2;

    template<class Stopwatch, class Formatter>
    struct wstopwatch_reporter2_default_formatter<wstopwatch_reporter2<
        Stopwatch, Formatter> >
    {
      typedef Formatter type;
    };

    template<class Stopwatch, class Formatter>
    class wstopwatch_reporter2: public basic_stopwatch_reporter2<Stopwatch,
        Formatter>
    {
      typedef basic_stopwatch_reporter2<Stopwatch, Formatter> base_type;
    public:
      typedef typename Stopwatch::clock clock;
      typedef Stopwatch stopwatch;
      typedef Formatter formatter_type;

      wstopwatch_reporter2() :
        base_type()
      {
      }
      explicit wstopwatch_reporter2(formatter_type const& fmt) :
        base_type(fmt)
      {
      }

      typedef stopwatch_runner<wstopwatch_reporter2<Stopwatch, Formatter> >
          scoped_run;
      typedef stopwatch_stopper<wstopwatch_reporter2<Stopwatch, Formatter> >
          scoped_stop;
      typedef stopwatch_suspender<wstopwatch_reporter2<Stopwatch, Formatter> >
          scoped_suspend;
      typedef stopwatch_resumer<wstopwatch_reporter2<Stopwatch, Formatter> >
          scoped_resume;

    protected:

      //wstopwatch_reporter2(); // = delete;
      wstopwatch_reporter2(const wstopwatch_reporter2&); // = delete;
      wstopwatch_reporter2& operator=(const wstopwatch_reporter2&); // = delete;
    };

  } // namespace chrono
} // namespace boost


#if !defined(BOOST_ENABLE_WARNINGS) && !defined(BOOST_STOPWATCHES_ENABLE_WARNINGS)
#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif
#endif

#endif


