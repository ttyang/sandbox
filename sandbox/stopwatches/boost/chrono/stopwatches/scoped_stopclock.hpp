//  boost/chrono/stopwatches/stopclock.hpp  ------------------------------------------------------------//
//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//  See http://www.boost.org/libs/chrono/stopwatches for documentation.

#ifndef BOOST_CHRONO_STOPWATCHES_SCOPED_STOPCLOCK_HPP
#define BOOST_CHRONO_STOPWATCHES_SCOPED_STOPCLOCK_HPP

#include <boost/chrono/stopwatches/stopwatch_reporter.hpp>
#include <boost/chrono/stopwatches/stopwatch.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/chrono/stopwatches/time_formatter.hpp>
#include <boost/chrono/stopwatches/stopwatch_accumulator_time_formatter.hpp>
#include <boost/chrono/stopwatches/stopclock.hpp>

namespace boost
{
  namespace chrono
  {

    template<class Clock = chrono::process_cpu_clock,
        class Formatter = typename stopwatch_reporter_default_formatter<
            chrono::stopwatch<Clock> >::type>
    class scoped_stopclock: public stopwatch_reporter<chrono::stopwatch<Clock>,
        Formatter>
    {
      typedef stopwatch_reporter<chrono::stopwatch<Clock>, Formatter> base_type;
    public:
      typedef Clock clock;
      typedef chrono::stopwatch<Clock> stopwatch;
      typedef Formatter formatter;
      typedef typename Formatter::string_type string_type;
      typedef typename Formatter::char_type char_type;
      typedef typename Formatter::ostream_type ostream_type;

      explicit scoped_stopclock(const string_type& func, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(ec), func_(func)
      {
        begin();
      }
      scoped_stopclock(const string_type& func, ostream_type & os, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(os, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, const string_type & format, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(format, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, int places, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(places, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, ostream_type & os, const string_type & format, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(os, format, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, const string_type & format, int places, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(format, places, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, ostream_type & os, int places, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(os, places, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, int places, const string_type & format, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(places, format, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, ostream_type & os, const string_type & format, int places, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(os, format, places, ec), func_(func)
      {
        begin();
      }

      scoped_stopclock(const string_type& func, ostream_type & os, int places, const string_type & format, system::error_code & ec =
          BOOST_CHRONO_THROWS) :
        base_type(os, places, format, ec), func_(func)
      {
        begin();
      }

      ~scoped_stopclock()
      {
        this->m_os << "}}} " << func_ << " : ";
      }
      typedef typename base_type::scoped_run scoped_run;
      typedef typename base_type::scoped_suspend scoped_suspend;
      typedef typename base_type::scoped_resume scoped_resume;
    private:
      void begin()
      {
        this->m_os << "{{{ " << func_ << std::endl;
      }
      string_type func_;

    };

  } // namespace chrono
} // namespace boost

#endif // BOOST_STOPWATCHES_STOPCLOCK_HPP
