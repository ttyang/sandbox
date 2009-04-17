#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "boost/task.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

typedef tsk::default_pool pool_type;

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
		if ( n == 7)
			boost::this_task::yield();

		if ( n < cutof_)
			return serial_fib( n);
		else
		{
			tsk::task< long > t1(
				tsk::make_task(
					& fib_task::execute,
					boost::ref( * this),
					n - 1) );
			tsk::task< long > t2(
				tsk::make_task(
					& fib_task::execute,
					boost::ref( * this),
					n - 2) );
			if ( boost::this_task::runs_in_pool() )
			{
				tsk::launch_in_pool( t1);
				tsk::launch_in_pool( t2);
			}
			else
			{
				tsk::launch_in_thread( t1);
				tsk::launch_in_thread( t2);
			}
			return t1.get() + t2.get();
		}
	}
};


void parallel_fib( long n)
{
	fib_task a( 5);
	long result = a.execute( n);
	printf("n == %d, fibonnaci == %d\n", n, result);
}

int main( int argc, char *argv[])
{
	try
	{
		for ( int i = 0; i < 10; ++i)
			tsk::launch_in_thread(
// 			tsk::launch_in_pool(
				tsk::make_task(
					& parallel_fib,
					i) );

		return EXIT_SUCCESS;
	}
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch ( ... )
	{ std::cerr << "unhandled" << std::endl; }

	return EXIT_FAILURE;
}
