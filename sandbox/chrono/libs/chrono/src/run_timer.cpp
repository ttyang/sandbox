//  boost run_timer.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

// define BOOST_CHRONO_SOURCE so that <boost/chrono/config.hpp> knows
// the library is being built (possibly exporting rather than importing code)
#define BOOST_CHRONO_SOURCE

#include <boost/chrono/detail/inlined/run_timer.hpp>

#if 0

#include <boost/version.hpp>
#include <boost/chrono/process_times.hpp>
#include <boost/system/system_error.hpp>
#include <boost/io/ios_state.hpp>
#include <cstring>
#include <cassert>

using boost::chrono::nanoseconds;
using boost::chrono::duration;

namespace
{
  const char * default_format =
    "\nreal %rs, cpu %cs (%p%), user %us, system %ss\n";

  void show_time( const boost::chrono::process_times & times,
                  const char * format, int places, std::ostream & os )
  //  NOTE WELL: Will truncate least-significant digits to LDBL_DIG, which may
  //  be as low as 10, although will be 15 for many common platforms.
  {
    if ( times.real < nanoseconds(0) ) return;
    if ( places > 9 )
      places = 9;  // sanity check
    else if ( places < 0 )
      places = 0;

    boost::io::ios_flags_saver ifs( os );
    os.setf( std::ios_base::fixed, std::ios_base::floatfield );
    boost::io::ios_precision_saver ips( os );
    os.precision( places );

    nanoseconds total = times.system + times.user;

    for ( ; *format; ++format )
    {
      if ( *format != '%' || !*(format+1) || !std::strchr("rcpus", *(format+1)) )
        os << *format;
      else
      {
        ++format;
        switch ( *format )
        {
        case 'r':
          os << duration<double>(times.real).count();
          break;
        case 'u':
          os << duration<double>(times.user).count();
          break;
        case 's':
          os << duration<double>(times.system).count();
          break;
        case 'c':
          os << duration<double>(total).count();
          break;
        case 'p':
          {
            boost::io::ios_precision_saver ips( os );
            os.precision( 1 );
            if ( times.real.count() && total.count() )
              os << duration<double>(total).count()
                   /duration<double>(times.real).count() * 100.0;
            else
              os << 0.0;
          }
          break;
        default:
          assert(0 && "run_timer internal logic error");
        }
      }
    }
  }

}  // unnamed namespace

namespace boost
{
  namespace chrono
  {


      run_timer::run_timer( system::error_code & ec  )
        : m_places(m_default_places), m_os(m_cout()) { start(ec); }
      run_timer::run_timer( std::ostream & os,
        system::error_code & ec  )
        : m_places(m_default_places), m_os(os) { start(ec); }

      run_timer::run_timer( const std::string & format,
        system::error_code & ec  )
        : m_places(m_default_places), m_os(m_cout()), m_format(format) { start(ec); }
      run_timer::run_timer( std::ostream & os, const std::string & format,
        system::error_code & ec  )
        : m_places(m_default_places), m_os(os), m_format(format) { start(ec); }

      run_timer::run_timer( const std::string & format, int places,
        system::error_code & ec  )
        : m_places(places), m_os(m_cout()), m_format(format) { start(ec); }
      run_timer::run_timer( std::ostream & os, const std::string & format,
        int places, system::error_code & ec  )
        : m_places(places), m_os(os), m_format(format) { start(ec); }

      run_timer::run_timer( int places,
        system::error_code & ec  )
        : m_places(places), m_os(m_cout()) { start(ec); }
      run_timer::run_timer( std::ostream & os, int places,
        system::error_code & ec  )
        : m_places(places), m_os(os) { start(ec); }

      run_timer::run_timer( int places, const std::string & format,
        system::error_code & ec  )
        : m_places(places), m_os(m_cout()), m_format(format) { start(ec); }
      run_timer::run_timer( std::ostream & os, int places, const std::string & format,
        system::error_code & ec  )
        : m_places(places), m_os(os), m_format(format) { start(ec); }

    //  run_timer::report  -------------------------------------------------------------//

    void run_timer::report( system::error_code & ec )
    {
      m_reported = true;
      if ( m_format.empty() ) m_format = default_format;

      process_times times;
      elapsed( times, ec );
      if (ec) return;

      if ( &ec == &system::throws )
      {
        show_time( times, m_format.c_str(), m_places, m_os );
      }
      else // non-throwing
      {
        try
        {
          show_time( times, m_format.c_str(), m_places, m_os );
          ec.clear();
        }

        catch (...) // eat any exceptions
        {
          assert( 0 && "error reporting not fully implemented yet" );
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
          ec.assign(system::errc::success, system::generic_category);
#else
          ec.assign(system::errc::success, system::generic_category());
#endif
            //ec = error_code( EIO, errno_ecat );
        }
      }
    }

    //  run_timer::test_report  --------------------------------------------------------//

    void run_timer::test_report( duration real_, duration user_, duration system_ )
    {
      if ( m_format.empty() ) m_format = default_format;

      process_times times;
      times.real = real_;
      times.user = user_;
      times.system = system_;

      show_time( times, m_format.c_str(), m_places, m_os );
    }

  } // namespace chrono
} // namespace boost

#endif
