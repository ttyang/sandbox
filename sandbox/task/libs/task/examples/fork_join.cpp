#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "boost/task.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

typedef tsk::pool< tsk::unbounded_channel< tsk::fifo > > pool_type;

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
			tsk::launch_in_pool(
				boost::this_task::get_pool< pool_type >(),
				t1);
			tsk::launch_in_pool(
				boost::this_task::get_pool< pool_type >(),
				t2);
			return t1.get() + t2.get();
		}
	}
};

long parallel_fib( long n)
{
	fib_task a( 5);
	return a.execute( n);
}

int main( int argc, char *argv[])
{
	try
	{
		pool_type pool( tsk::poolsize( 5) );

		std::vector< tsk::task< long > > results;
		results.reserve( 20);

		pt::ptime start( pt::microsec_clock::universal_time() );

		for ( int i = 0; i < 26; ++i)
		{
			tsk::task< long > t(
				tsk::make_task(
					& parallel_fib,
					i) );
			results.push_back( t);
			tsk::launch_in_pool( pool, t);
		}

		tsk::waitfor_all( results.begin(), results.end() );

		int k = 0;
		std::vector< tsk::task< long > >::iterator e( results.end() );
		for (
			std::vector< tsk::task< long > >::iterator i( results.begin() );
			i != e;
			++i)
			std::cout << "fibonacci " << k++ << " == " << i->get() << std::endl;

		pt::ptime stop( pt::microsec_clock::universal_time() );
		std::cout << ( stop - start).total_milliseconds() << " milli seconds" << std::endl;

		return EXIT_SUCCESS;
	}
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch ( ... )
	{ std::cerr << "unhandled" << std::endl; }

	return EXIT_FAILURE;
}
