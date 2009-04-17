
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include <boost/bind.hpp>

#include "boost/task.hpp"

namespace tsk = boost::task;

inline
int fibonacci_fn( int n)
{
	if ( n == 0) return 0;
	if ( n == 1) return 1;
	int k1( 1), k2( 0);
	for ( int i( 2); i <= n; ++i)
	{
		boost::this_thread::interruption_point();
		int tmp( k1);
		k1 = k1 + k2;
		k2 = tmp;
	}
	boost::this_thread::interruption_point();
	return k1;
}

int main( int argc, char *argv[])
{
	try
	{
		tsk::task< int > t1(
			tsk::make_task(
				fibonacci_fn,
				10) );
		tsk::task< int > t2(
			tsk::make_task(
				fibonacci_fn,
				10) );
		tsk::task< int > t3(
			tsk::make_task(
				fibonacci_fn,
				10) );
 		tsk::launch_in_pool( t1);
  		tsk::launch_in_thread( t2);
		tsk::launch_local( t3);
		std::cout << t1.get() << std::endl;
		std::cout << t2.get() << std::endl;
		std::cout << t3.get() << std::endl;

		return EXIT_SUCCESS;
	}
	catch ( std::exception const& e)
	{ std::cerr << "exception: " << e.what() << std::endl; }
	catch ( ... )
	{ std::cerr << "unhandled" << std::endl; }

	return EXIT_FAILURE;
}
