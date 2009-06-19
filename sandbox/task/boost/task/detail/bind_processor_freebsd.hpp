
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TASK_DETAIL_BIND_PROCESSOR_FREEBSD_H
#define BOOST_TASK_DETAIL_BIND_PROCESSOR_FREEBSD_H

extern "C"
{
#include <sys/param.h>
#include <sys/cpuset.h>
}

#include <boost/assert.hpp>
#include <boost/thread.hpp>
#include <boost/system/system_error.hpp>

#include <boost/config/abi_prefix.hpp>

namespace boost { namespace this_thread
{
	inline
	void bind_to_processor( unsigned int n)
	{
		BOOST_ASSERT( n >= 0);
		BOOST_ASSERT( n < boost::thread::hardware_concurrency() );

		cpusetid_t cpusetid;
		CPU_ZERO( & cpusetid);
		CPU_SET( n, & cpusetid);

		if ( ::cpuset_setid( CPU_WHICH_TID, -1, cpusetid) == -1)
			throw boost::system::system_error(
					boost::system::error_code(
						errno,
						boost::system::system_category) );
	}

	inline
	void bind_to_any_processor()
	{
		cpusetid_t cpusetid;
		CPU_ZERO( & cpusetid);

		unsigned int max( boost::thread::hardware_concurrency() );
		for ( unsigned int i( 0); i < max; ++i)
			CPU_SET( i, & cpuset);
		
		if ( ::cpuset_setid( CPU_WHICH_TID, -1, cpusetid) == -1)
			throw boost::system::system_error(
					boost::system::error_code(
						errno,
						boost::system::system_category) );
	}
}}

#include <boost/config/abi_suffix.hpp>

#endif // BOOST_TASK_DETAIL_BIND_PROCESSOR_FREEBSD_H
