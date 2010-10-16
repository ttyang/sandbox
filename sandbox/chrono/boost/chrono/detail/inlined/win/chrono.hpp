//  win/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP

#include <boost/detail/win/time.hpp>

namespace boost
{
namespace chrono
{
namespace chrono_detail
{
  
  BOOST_CHRONO_INLINE double get_nanosecs_per_tic()
  {
	  boost::detail::win32::LARGE_INTEGER_ freq;
	  if ( !boost::detail::win32::QueryPerformanceFrequency( &freq ) )
		  return 0.0L;
	  return double(1000000000.0L / freq.QuadPart);
  }

}
  
  monotonic_clock::time_point monotonic_clock::now()
  {
	static double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

	boost::detail::win32::LARGE_INTEGER_ pcount;
    if ( (nanosecs_per_tic <= 0.0L) || (!boost::detail::win32::QueryPerformanceCounter( &pcount )) )
    {
    	boost::detail::win32::DWORD_ cause = 
    		(nanosecs_per_tic <= 0.0L 
    				? ERROR_NOT_SUPPORTED 
    				: boost::detail::win32::GetLastError());
      boost::throw_exception(
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
        system::system_error( cause, system::system_category, "chrono::monotonic_clock" ));
#else
        system::system_error( cause, system::system_category(), "chrono::monotonic_clock" ));
#endif          
    }

    return monotonic_clock::time_point(monotonic_clock::duration(
      static_cast<monotonic_clock::rep>((nanosecs_per_tic) * pcount.QuadPart) ));
  }

  
  monotonic_clock::time_point monotonic_clock::now( system::error_code & ec )
  {
    static double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

    boost::detail::win32::LARGE_INTEGER_ pcount;
    if ( (nanosecs_per_tic <= 0.0L) || (!boost::detail::win32::QueryPerformanceCounter( &pcount )) )
    {
    	boost::detail::win32::DWORD_ cause = ((nanosecs_per_tic <= 0.0L) ? ERROR_NOT_SUPPORTED : boost::detail::win32::GetLastError());
#if ((BOOST_VERSION / 100000) < 2) && ((BOOST_VERSION / 100 % 1000) < 44)
      ec.assign( cause, system::system_category );
#else
      ec.assign( cause, system::system_category() );
#endif          
      return monotonic_clock::time_point(duration(0));
    }

    ec.clear();
    return time_point(duration(
      static_cast<monotonic_clock::rep>(nanosecs_per_tic * pcount.QuadPart) ));
  }

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now()
  {
	boost::detail::win32::FILETIME_ ft;
	boost::detail::win32::GetSystemTimeAsFileTime( &ft );  // never fails
    return system_clock::time_point(system_clock::duration(
      (static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime));
  }

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now( system::error_code & ec )
  {
	boost::detail::win32::FILETIME_ ft;
    boost::detail::win32::GetSystemTimeAsFileTime( &ft );  // never fails
    ec.clear();
    return time_point(duration(
      (static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime));
  }

  BOOST_CHRONO_INLINE
  std::time_t system_clock::to_time_t(const system_clock::time_point& t)
  {
      __int64 temp = t.time_since_epoch().count();

  #   if (!defined( BOOST_MSVC )) || (BOOST_MSVC > 1300) // > VC++ 7.0
      temp -= 116444736000000000LL;  // delta from epoch in microseconds
  #   else
      temp -= 116444736000000000;
  #   endif

      temp /= 10000000;
      return static_cast<std::time_t>( temp );
  }

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::from_time_t(std::time_t t)
  {
      __int64 temp = t;
      temp *= 10000000;

  #   if (!defined( BOOST_MSVC )) || (BOOST_MSVC > 1300) // > VC++ 7.0
      temp += 116444736000000000LL;
  #   else
      temp += 116444736000000000;
  #   endif

      return time_point(duration(temp));
  }

}  // namespace chrono
}  // namespace boost

#endif
