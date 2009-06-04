
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "boost/task/detail/config.hpp"

# if defined(BOOST_POSIX_API)
extern "C"
{
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
}
# endif

#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

#include "boost/task.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

long serial_fib( long n)
{
	if( n < 2)
		return n;
	else
		return serial_fib( n - 1) + serial_fib( n - 2);
}

class fib_task
{
private:
	long	cutof_;

public:
	fib_task( long cutof)
	: cutof_( cutof)
	{}

	long execute( long n)
	{
		if ( n < cutof_) return serial_fib( n);
		else
		{
			BOOST_ASSERT( boost::this_task::runs_in_pool() );
			tsk::handle< long > h1(
				tsk::async(
					tsk::make_task(
						& fib_task::execute,
						boost::ref( * this),
						n - 1),
					tsk::as_sub_task() ) );
			tsk::handle< long > h2(
				tsk::async(
					tsk::make_task(
						& fib_task::execute,
						boost::ref( * this),
						n - 2),
					tsk::as_sub_task() ) );
			return h1.get() + h2.get();
		}
	}
};

void parallel_fib( long n)
{
	fib_task a( 5);
	printf("fibonacci(%d) == %ld\n", n, a.execute( n) );
}

# if defined(BOOST_POSIX_API)
bool has_bytes( int fd)
{
	char buffer[1];

	int n = ::recv(
		fd,
		& buffer,
		sizeof buffer,
		MSG_PEEK | MSG_DONTWAIT);
	if ( n == -1 && errno != EWOULDBLOCK)
	{
		printf("::recv() failed: %s(%d)\n", std::strerror( errno), errno);
		::exit( 1);
	}

	return n > 0;
}

void do_read( int fd)
{
	int nread = 0;
	do
	{
		boost::this_task::reschedule_until(
			boost::bind(
				has_bytes,
				fd) );
	
		char buffer[4096];
		int n = ::read( fd, buffer, sizeof( buffer) );
		if ( n < 0)
		{
			printf("::read() failed: %s(%d)\n", std::strerror( errno), errno);
			::exit( 1);
		}
		nread += n;
		printf("%s\n", std::string( buffer, n).c_str() );
	}
	while ( nread < 12);
}

void do_write( int fd, std::string const& msg)
{
	if ( ::write( fd, msg.c_str(), msg.size() ) < 0)
	{
		printf("::write() failed: %s(%d)\n", std::strerror( errno), errno);
		::exit( 1);
	}
}

void create_sockets( int fd[2])
{
	if ( ::socketpair( PF_LOCAL, SOCK_STREAM, 0, fd) < 0)
	{
		printf("::pipe() failed: %s(%d)\n", std::strerror( errno), errno);
		::exit( 1);
	}
}
# endif

int main( int argc, char *argv[])
{
# if defined(BOOST_POSIX_API)
	try
	{
		int fd[2];
		create_sockets( fd);

		tsk::async(
			tsk::make_task(
				& do_read,
				fd[0]),
			tsk::default_pool() );

		do_write( fd[1], "Hello ");
		boost::this_thread::sleep( pt::seconds( 1) );

		for ( int i = 0; i < 10; ++i)
			tsk::async(
				tsk::make_task(
					& parallel_fib,
					i),
				tsk::default_pool() );

		do_write( fd[1], "World!");

		return EXIT_SUCCESS;
	}
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch ( ... )
	{ std::cerr << "unhandled" << std::endl; }

# endif

	return EXIT_FAILURE;
}
