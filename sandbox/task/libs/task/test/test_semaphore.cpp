
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include <boost/task.hpp>

#include "test_functions.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

namespace {
uint32_t wait_fn( uint32_t n, tsk::semaphore & sem)
{
	sem.wait();
	return n;
}
}

class test_semaphore
{
public:
	// check wait in new thread
	void test_case_1()
	{
		uint32_t n = 3;
		tsk::semaphore sem( 0);

		tsk::handle< uint32_t > h1(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					tsk::new_thread() ) );
		tsk::handle< uint32_t > h2(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					tsk::new_thread() ) );

		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK( ! h1.is_ready() );
		BOOST_CHECK( ! h2.is_ready() );

		sem.post();

		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK( h1.is_ready() || h2.is_ready() );
		if ( h1.is_ready() )
		{
			BOOST_CHECK_EQUAL( h1.get(), n);
			BOOST_CHECK( ! h2.is_ready() );

			sem.post();

			boost::this_thread::sleep( pt::millisec( 250) );
			BOOST_CHECK( h2.is_ready() );
			BOOST_CHECK_EQUAL( h2.get(), n);
		}
		else
		{
			BOOST_CHECK( h2.is_ready() );
			BOOST_CHECK_EQUAL( h2.get(), n);
			BOOST_CHECK( ! h1.is_ready() );

			sem.post();

			boost::this_thread::sleep( pt::millisec( 250) );
			BOOST_CHECK( h1.is_ready() );
			BOOST_CHECK_EQUAL( h1.get(), n);
		
		}
	}

	// check wait in pool
	void test_case_2()
	{
		tsk::static_pool<
			tsk::unbounded_onelock_fifo
		> pool( tsk::poolsize( 3) );

		uint32_t n = 3;
		tsk::semaphore sem( 0);

		tsk::handle< uint32_t > h1(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					pool) );
		tsk::handle< uint32_t > h2(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					pool) );
		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK( ! h1.is_ready() );
		BOOST_CHECK( ! h2.is_ready() );

		sem.post();

		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK( h1.is_ready() || h2.is_ready() );
		if ( h1.is_ready() )
		{
			BOOST_CHECK_EQUAL( h1.get(), n);
			BOOST_CHECK( ! h2.is_ready() );

			sem.post();

			boost::this_thread::sleep( pt::millisec( 250) );
			BOOST_CHECK( h2.is_ready() );
			BOOST_CHECK_EQUAL( h2.get(), n);
		}
		else
		{
			BOOST_CHECK( h2.is_ready() );
			BOOST_CHECK_EQUAL( h2.get(), n);
			BOOST_CHECK( ! h1.is_ready() );

			sem.post();

			boost::this_thread::sleep( pt::millisec( 250) );
			BOOST_CHECK( h1.is_ready() );
			BOOST_CHECK_EQUAL( h1.get(), n);
		
		}
	}

	void test_case_3()
	{
		uint32_t n = 3;
		tsk::semaphore sem( 2);

		tsk::handle< uint32_t > h1(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					tsk::new_thread() ) );
		tsk::handle< uint32_t > h2(
				tsk::async(
					tsk::make_task(
						wait_fn,
						n, boost::ref( sem) ),
					tsk::new_thread() ) );

		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK( h1.is_ready() );
		BOOST_CHECK( h2.is_ready() );
		BOOST_CHECK_EQUAL( h1.get(), n);
		BOOST_CHECK_EQUAL( h2.get(), n);
	}
};

boost::unit_test::test_suite * init_unit_test_suite( int, char* [])
{
	boost::unit_test::test_suite * test( BOOST_TEST_SUITE("Boost.Task: test suite") );

	boost::shared_ptr< test_semaphore > instance( new test_semaphore() );
	test->add( BOOST_CLASS_TEST_CASE( & test_semaphore::test_case_1, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_semaphore::test_case_2, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_semaphore::test_case_3, instance) );

	return test;
}
