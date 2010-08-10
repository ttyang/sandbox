//  posix/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//


#include <time.h>  // for clock_gettime

namespace boost
{
namespace chrono
{

  system_clock::time_point system_clock::now()
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
      boost::throw_exception(
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
        system::system_error( errno, system::system_category, "chrono::system_clock" ));
#else
        system::system_error( errno, system::system_category(), "chrono::system_clock" ));
#endif          
    }

    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

  system_clock::time_point system_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
      ec.assign( errno, system::system_category );
#else
      ec.assign( errno, system::system_category() );
#endif          
      return time_point();
    }

    ec.clear();
    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

  std::time_t system_clock::to_time_t(const system_clock::time_point& t)
  {
      return static_cast<std::time_t>( t.time_since_epoch().count() / 1000000000 );
  }

  system_clock::time_point system_clock::from_time_t(std::time_t t)
  {
      return time_point(duration(static_cast<system_clock::rep>(t) * 1000000000));
  }

#ifdef BOOST_CHRONO_HAS_CLOCK_MONOTONIC

  monotonic_clock::time_point monotonic_clock::now()
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
    {
      boost::throw_exception(
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
        system::system_error( errno, system::system_category, "chrono::monotonic_clock" ));
#else
        system::system_error( errno, system::system_category(), "chrono::monotonic_clock" ));
#endif          
    }

    return time_point(duration(
      static_cast<monotonic_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

  monotonic_clock::time_point monotonic_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
    {
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
      ec.assign( errno, system::system_category );
#else
      ec.assign( errno, system::system_category() );
#endif          
      return time_point();
    }

    ec.clear();
    return time_point(duration(
      static_cast<monotonic_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }
#endif

}  // namespace chrono
}  // namespace boost


