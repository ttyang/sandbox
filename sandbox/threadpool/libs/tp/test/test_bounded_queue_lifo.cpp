//  Copyright (c) 2008 Oliver Kowalke. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/future.hpp>
#include <boost/ref.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/utility.hpp>

#include <boost/tp/bounded_channel.hpp>
#include <boost/tp/exceptions.hpp>
#include <boost/tp/lifo.hpp>
#include <boost/tp/pool.hpp>
#include <boost/tp/poolsize.hpp>
#include <boost/tp/task.hpp>
#include <boost/tp/watermark.hpp>

#include "test_functions.hpp"

namespace pt = boost::posix_time;
namespace tp = boost::tp;

class fixed_bounded_channel_lifo
{
public:
	// check size, active, idle
	void test_case_1()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 3),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		BOOST_CHECK_EQUAL( pool.size(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool.idle(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool.active(), std::size_t( 0) );
	}

	// check submit
	void test_case_2()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		tp::task< int > f(
			pool.submit(
				boost::bind(
					fibonacci_fn,
					10) ) );
		BOOST_CHECK_EQUAL( f.get(), 55);
	}

	// check shutdown
	void test_case_3()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		tp::task< int > t(
			pool.submit(
				boost::bind(
					fibonacci_fn,
					10) ) );
		pool.shutdown();
		BOOST_CHECK( pool.terminated() );
		BOOST_CHECK_EQUAL( t.get(), 55);
	}

	// check runtime_error throw inside task
	void test_case_4()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		tp::task< void > f(
			pool.submit(
				boost::bind(
					throwing_fn) ) );
		pool.shutdown();
		bool thrown( false);
		try
		{ f.get(); }
		catch ( std::runtime_error const&)
		{ thrown = true; }
		BOOST_CHECK( thrown);
	}

	// check shutdown with task_rejected exception
	void test_case_5()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		pool.shutdown();
		BOOST_CHECK( pool.terminated() );
		bool thrown( false);
		try
		{
			pool.submit(
				boost::bind(
					fibonacci_fn,
					10) );
		}
		catch ( tp::task_rejected const&)
		{ thrown = true; }
		BOOST_CHECK( thrown);
	}

	// check shutdown_now with thread_interrupted exception
	void test_case_6()
	{
		tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool(
			tp::poolsize( 1),
			tp::high_watermark( 1),
			tp::low_watermark( 1) );
		boost::function< int() > fn(
			boost::bind(
				fibonacci_fn,
				10) );
		tp::task< int > f(
			pool.submit(
				boost::bind(
					( int ( *)( boost::function< int() > const&, pt::time_duration const&) ) delay_fn,
					fn,
					pt::millisec( 500) ) ) );
		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK_EQUAL( pool.size(), std::size_t( 1) );
		pool.shutdown_now();
		BOOST_CHECK( pool.terminated() );
		BOOST_CHECK_EQUAL( pool.size(), std::size_t( 1) );
		BOOST_CHECK_EQUAL( pool.idle(), std::size_t( 1) );
		BOOST_CHECK_EQUAL( pool.active(), std::size_t( 0) );
		bool thrown( false);
		try
		{ f.get(); }
		catch ( boost::thread_interrupted const&)
		{ thrown = true; }
		BOOST_CHECK( thrown);
	}

	// check pending
	void test_case_7()
	{
		typedef tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool_type;
		pool_type pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		boost::barrier b( 2);
		boost::function< int() > fn(
			boost::bind(
				fibonacci_fn,
				10) );
		tp::task< int > f1(
			pool.submit(
				boost::bind(
					( int ( *)( boost::function< int() > const&, boost::barrier &) ) barrier_fn,
					fn,
					boost::ref( b) ) ) );
		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 0) );
		tp::task< int > f2( pool.submit( fn) );
		boost::this_thread::sleep( pt::millisec(250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 1) );
		tp::task< int > f3( pool.submit( fn) );
		boost::this_thread::sleep( pt::millisec(250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 2) );
		b.wait();
		BOOST_CHECK_EQUAL( f1.get(), 55);
		BOOST_CHECK_EQUAL( f2.get(), 55);
		BOOST_CHECK_EQUAL( f3.get(), 55);
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 0) );
	}

	// check lifo scheduling
	void test_case_8()
	{
		typedef tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool_type;
		pool_type pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		boost::barrier b( 2);
		boost::function< int() > fn(
			boost::bind(
				fibonacci_fn,
				10) );
		tp::task< int > f1(
			pool.submit(
				boost::bind(
					( int ( *)( boost::function< int() > const&, boost::barrier &) ) barrier_fn,
					fn,
					boost::ref( b) ) ) );
		std::vector< int > buffer;
		pool.submit(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				10) );
		pool.submit(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				0) );
		b.wait();
		pool.shutdown();
		BOOST_CHECK_EQUAL( buffer[0], 0);
		BOOST_CHECK_EQUAL( buffer[1], 55);
		BOOST_CHECK_EQUAL( buffer.size(), std::size_t( 2) );
	}

	// check cancelation
	void test_case_9()
	{
		typedef tp::pool<
			tp::bounded_channel< tp::lifo >
		> pool_type;
		pool_type pool(
			tp::poolsize( 1),
			tp::high_watermark( 10),
			tp::low_watermark( 10) );
		boost::barrier b( 2);
		boost::function< int() > fn(
			boost::bind(
				fibonacci_fn,
				10) );
		pool.submit(
			boost::bind(
				( int ( *)( boost::function< int() > const&, boost::barrier &) ) barrier_fn,
				fn,
				boost::ref( b) ) );
		std::vector< int > buffer;
		tp::task< void > f(
			pool.submit(
				boost::bind(
					buffer_fibonacci_fn,
					boost::ref( buffer),
					10) ) );
		pool.submit(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				0) );
		f.interrupt();
		b.wait();
		pool.shutdown();
		BOOST_CHECK_EQUAL( buffer[0], 0);
		BOOST_CHECK_EQUAL( buffer.size(), std::size_t( 1) );
		bool thrown( false);
		try
		{ f.get(); }
		catch ( boost::thread_interrupted const&)
		{ thrown = true; }
		BOOST_CHECK( thrown);
	}
};

boost::unit_test::test_suite * init_unit_test_suite( int, char* [])
{
	boost::unit_test::test_suite * test( BOOST_TEST_SUITE("Boost.ThreadPool: fixed bounded_channel< lifo > pool test suite") );

	boost::shared_ptr< fixed_bounded_channel_lifo > instance( new fixed_bounded_channel_lifo() );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_1, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_2, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_3, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_4, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_5, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_6, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_7, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_8, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & fixed_bounded_channel_lifo::test_case_9, instance) );

	return test;
}

