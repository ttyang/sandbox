
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
#include <boost/thread/barrier.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility.hpp>

#include <boost/task.hpp>

#include "test_functions.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

class test_bounded_pool
{
public:
	// check size, active, idle
	void test_case_1()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool1(
			tsk::poolsize( 3),
			tsk::high_watermark( 10),
			tsk::low_watermark( 5) );
		BOOST_CHECK_EQUAL( pool1.size(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool1.idle(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool1.active(), std::size_t( 0) );
		BOOST_CHECK_EQUAL( pool1.upper_bound(), std::size_t( 10) );
		BOOST_CHECK_EQUAL( pool1.lower_bound(), std::size_t( 5) );

		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool2;
		BOOST_CHECK_THROW( pool2.size(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool2.idle(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool2.active(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool2.upper_bound(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool2.lower_bound(), tsk::pool_moved);

		pool2 = boost::move( pool1);
		
		BOOST_CHECK_THROW( pool1.size(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool1.idle(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool1.active(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool1.upper_bound(), tsk::pool_moved);
		BOOST_CHECK_THROW( pool1.lower_bound(), tsk::pool_moved);

		BOOST_CHECK_EQUAL( pool2.size(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool2.idle(), std::size_t( 3) );
		BOOST_CHECK_EQUAL( pool2.active(), std::size_t( 0) );
		BOOST_CHECK_EQUAL( pool2.upper_bound(), std::size_t( 10) );
		BOOST_CHECK_EQUAL( pool2.lower_bound(), std::size_t( 5) );

		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h(
			tsk::async( boost::move( t), pool2) );
		BOOST_CHECK_EQUAL( h.get(), 55);
	}

	// check submit
	void test_case_2()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK_EQUAL( h.get(), 55);
	}

	// check assignment
	void test_case_3()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h1;
		tsk::handle< int > h2(
			tsk::async( boost::move( t), pool) );
		h1 = h2;
		BOOST_CHECK_EQUAL( h1.get(), 55);
		BOOST_CHECK_EQUAL( h2.get(), 55);
	}

	// check swap
	void test_case_4()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< int > t1(
			boost::bind(
				fibonacci_fn,
				5) );
		tsk::task< int > t2(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h1(
			tsk::async( boost::move( t1), pool) );
		tsk::handle< int > h2(
			tsk::async( boost::move( t2), pool) );
		BOOST_CHECK_EQUAL( h1.get(), 5);
		BOOST_CHECK_EQUAL( h2.get(), 55);
		BOOST_CHECK_NO_THROW( h1.swap( h2) );
		BOOST_CHECK_EQUAL( h1.get(), 55);
		BOOST_CHECK_EQUAL( h2.get(), 5);
	}
	
	// check runs in pool
	void test_case_5()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< bool > t( runs_in_pool_fn);
		tsk::handle< bool > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK_EQUAL( h.get(), true);
	}

	// check shutdown
	void test_case_6()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h(
			tsk::async( boost::move( t), pool) );
		pool.shutdown();
		BOOST_CHECK( pool.closed() );
		BOOST_CHECK_EQUAL( h.get(), 55);
	}

	// check runtime_error throw inside task
	void test_case_7()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< void > t( throwing_fn);
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		pool.shutdown();
		BOOST_CHECK_THROW( h.get(), std::runtime_error);
	}

	// check shutdown with task_rejected exception
	void test_case_8()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		pool.shutdown();
		BOOST_CHECK( pool.closed() );
		BOOST_CHECK_THROW(
			tsk::async( boost::move( t), pool),
			tsk::task_rejected);
	}

	// check shutdown_now with thread_interrupted exception
	void test_case_9()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::millisec( 500) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK_EQUAL( pool.size(), std::size_t( 1) );
		pool.shutdown_now();
		BOOST_CHECK( pool.closed() );
		BOOST_CHECK_EQUAL( pool.size(), std::size_t( 1) );
		BOOST_CHECK_EQUAL( pool.idle(), std::size_t( 1) );
		BOOST_CHECK_EQUAL( pool.active(), std::size_t( 0) );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check pending
	void test_case_10()
	{
		typedef tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool_type;
		pool_type pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		boost::barrier b( 2);
		tsk::task< void > t1(
			boost::bind(
				barrier_fn,
				boost::ref( b) ) );
		tsk::task< int > t2(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::task< int > t3(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< void > h1(
			tsk::async( boost::move( t1), pool) );
		boost::this_thread::sleep( pt::millisec( 250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 0) );
		tsk::handle< int > h2(
			tsk::async( boost::move( t2), pool) );
		boost::this_thread::sleep( pt::millisec(250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 1) );
		tsk::handle< int > h3(
			tsk::async( boost::move( t3), pool) );
		boost::this_thread::sleep( pt::millisec(250) );
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 2) );
		b.wait();
		h1.get();
		BOOST_CHECK_EQUAL( h2.get(), 55);
		BOOST_CHECK_EQUAL( h3.get(), 55);
		BOOST_CHECK_EQUAL( pool.pending(), std::size_t( 0) );
	}

	// check wait
	void test_case_11()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h(
			tsk::async( boost::move( t), pool) );
		h.wait();
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
		BOOST_CHECK_EQUAL( h.get(), 55);
	}

	// check wait_for
	void test_case_12()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 1) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( h.wait_for( pt::seconds( 3) ) );
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_13()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( ! h.wait_for( pt::seconds( 1) ) );
		BOOST_CHECK( ! h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_14()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 1) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( h.wait_until( boost::get_system_time() + pt::seconds( 3) ) );
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_15()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 1),
			tsk::low_watermark( 1) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( ! h.wait_until( boost::get_system_time() + pt::seconds( 1) ) );
		BOOST_CHECK( ! h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check interrupt
	void test_case_16()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		h.interrupt();
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait
	void test_case_17()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		h.interrupt_and_wait();
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_for
	void test_case_18()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( h.interrupt_and_wait_for( pt::seconds( 3) ) );
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_for
	void test_case_19()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< void > t(
			boost::bind(
				non_interrupt_fn,
				3) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( ! h.interrupt_and_wait_for( pt::seconds( 1) ) );
	}

	// check interrupt_and_wait_until
	void test_case_20()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( h.interrupt_and_wait_until( boost::get_system_time() + pt::seconds( 3) ) );
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_until
	void test_case_21()
	{
		tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool(
			tsk::poolsize( 5),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		tsk::task< void > t(
			boost::bind(
				non_interrupt_fn,
				3) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), pool) );
		BOOST_CHECK( ! h.interrupt_and_wait_until( boost::get_system_time() + pt::seconds( 1) ) );
	}

	// check fifo scheduling
	void test_case_22()
	{
		typedef tsk::static_pool<
			tsk::bounded_channel< tsk::fifo >
		> pool_type;
		BOOST_CHECK( ! tsk::has_attribute< pool_type >::value);
		pool_type pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		boost::barrier b( 2);
		std::vector< int > buffer;
		tsk::task< void > t1(
			boost::bind(
				barrier_fn,
				boost::ref( b) ) );
		tsk::task< void > t2(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				10) );
		tsk::task< void > t3(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				0) );
		tsk::async( boost::move( t1), pool);
		tsk::async( boost::move( t2), pool);
		tsk::async( boost::move( t3), pool);
		b.wait();
		pool.shutdown();
		BOOST_CHECK_EQUAL( buffer[0], 55);
		BOOST_CHECK_EQUAL( buffer[1], 0);
		BOOST_CHECK_EQUAL( buffer.size(), std::size_t( 2) );
	}

	// check priority scheduling
	void test_case_23()
	{
		typedef tsk::static_pool<
			tsk::bounded_channel< tsk::priority< int > >
		> pool_type;
		BOOST_CHECK( tsk::has_attribute< pool_type >::value);
		typedef boost::is_same< tsk::attribute_type< pool_type >::type, int > type;
		BOOST_CHECK( type::value);
		pool_type pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		boost::barrier b( 2);
		std::vector< int > buffer;
		tsk::task< void > t1(
			boost::bind(
				barrier_fn,
				boost::ref( b) ) );
		tsk::task< void > t2(
			boost::bind(
			buffer_fibonacci_fn,
			boost::ref( buffer),
			10) );
		tsk::task< void > t3(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				0) );
		tsk::async( boost::move( t1), 0, pool);
		tsk::async( boost::move( t2), 1, pool);
		tsk::async( boost::move( t3), 0, pool);
		b.wait();
		pool.shutdown();
		BOOST_CHECK_EQUAL( buffer[0], 0);
		BOOST_CHECK_EQUAL( buffer[1], 55);
		BOOST_CHECK_EQUAL( buffer.size(), std::size_t( 2) );
	}

	// check smart scheduling
	void test_case_24()
	{
		typedef tsk::static_pool<
			tsk::bounded_channel< tsk::smart< int, std::less< int >, tsk::replace_oldest, tsk::take_oldest > >
		> pool_type;
		BOOST_CHECK( tsk::has_attribute< pool_type >::value);
		typedef boost::is_same< tsk::attribute_type< pool_type >::type, int > type;
		BOOST_CHECK( type::value);
		pool_type pool(
			tsk::poolsize( 1),
			tsk::high_watermark( 10),
			tsk::low_watermark( 10) );
		boost::barrier b( 2);
		std::vector< int > buffer;
		tsk::task< void > t1(
			boost::bind(
				barrier_fn,
				boost::ref( b) ) );
		tsk::task< void > t2(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				10) );
		tsk::task< void > t3(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				0) );
		tsk::task< void > t4(
			boost::bind(
				buffer_fibonacci_fn,
				boost::ref( buffer),
				1) );
		tsk::async( boost::move( t1), 0, pool);
		tsk::async( boost::move( t2), 2, pool);
		tsk::async( boost::move( t3), 1, pool);
		tsk::async( boost::move( t4), 2, pool);
		b.wait();
		pool.shutdown();
		BOOST_CHECK_EQUAL( buffer[0], 0);
		BOOST_CHECK_EQUAL( buffer[1], 1);
		BOOST_CHECK_EQUAL( buffer.size(), std::size_t( 2) );
	}
};

boost::unit_test::test_suite * init_unit_test_suite( int, char* [])
{
	boost::unit_test::test_suite * test( BOOST_TEST_SUITE("Boost.Task: test suite") );

	boost::shared_ptr< test_bounded_pool > instance( new test_bounded_pool() );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_1, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_2, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_3, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_4, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_5, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_6, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_7, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_8, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_9, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_10, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_11, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_12, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_13, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_14, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_15, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_16, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_17, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_18, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_19, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_20, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_21, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_22, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_23, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_bounded_pool::test_case_24, instance) );

	return test;
}

