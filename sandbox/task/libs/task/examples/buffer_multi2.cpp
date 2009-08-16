
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <utility>

#include <boost/assert.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>

#include "boost/task.hpp"

namespace tsk = boost::task;

typedef tsk::static_pool< tsk::unbounded_channel< tsk::fifo > > pool_type;

int serial_fib( int n)
{
	if( n < 2)
		return n;
	else
		return serial_fib( n - 1) + serial_fib( n - 2);
}

int parallel_fib( int n, int cutof)
{
	if ( n < cutof) return serial_fib( n);
	else
	{
		BOOST_ASSERT( boost::this_task::runs_in_pool() );
		tsk::task< int > t1(
			parallel_fib,
			n - 1,
			cutof);
		tsk::task< int > t2(
			parallel_fib,
			n - 2,
			cutof);
		tsk::handle< int > h1(
			tsk::async(
				boost::move( t1),
				tsk::as_sub_task() ) ) ;
		tsk::handle< int > h2(
			tsk::async(
				boost::move( t2),
				tsk::as_sub_task() ) );
		return h1.get() + h2.get();
	}
}

inline
void submit(
		tsk::unbounded_buffer< int > & send,
		tsk::unbounded_buffer< std::pair< int , int > > & recv,
		int n)
{
	send.put( n);
	boost::optional< std::pair< int , int > > r;
	recv.take( r);
	BOOST_ASSERT( r);
	printf("fib(%d) == %d\n", r->first, r->second);
}

inline
void calculate(
		tsk::unbounded_buffer< int > & recv,
		tsk::unbounded_buffer< std::pair< int , int > > & send)
{
	boost::optional< int > n;
	recv.take( n);
	BOOST_ASSERT( n);
	int r = parallel_fib( * n, 5);
	send.put( std::make_pair( * n, r) );
}


int main( int argc, char *argv[])
{
	try
	{
		pool_type pool( tsk::poolsize( 2) );

		tsk::unbounded_buffer< int > buf1;
		tsk::unbounded_buffer< std::pair< int , int > > buf2;
		
		tsk::async(
			tsk::make_task( submit, buf1, buf2, 5),
			pool);
		tsk::async(
			tsk::make_task( submit, buf1, buf2, 10),
			pool);
		tsk::async(
			tsk::make_task( submit, buf1, buf2, 15),
			pool);

		tsk::async(
			tsk::make_task( calculate, buf1, buf2),
			pool);
		tsk::async(
			tsk::make_task( calculate, buf1, buf2),
			pool);
		tsk::async(
			tsk::make_task( calculate, buf1, buf2),
			pool);

		return EXIT_SUCCESS;
	}
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch ( ... )
	{ std::cerr << "unhandled" << std::endl; }

	return EXIT_FAILURE;
}
