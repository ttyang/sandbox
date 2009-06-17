
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
#include <boost/utility.hpp>

#include <boost/task.hpp>

#include "test_functions.hpp"

namespace pt = boost::posix_time;
namespace tsk = boost::task;

class test_new_thread
{
public:
	// check assignment
	void test_case_1()
	{
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h1;
		tsk::handle< int > h2(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		h1 = h2;
		BOOST_CHECK_EQUAL( h1.get(), 55);
		BOOST_CHECK_EQUAL( h2.get(), 55);
	}

	// check swap
	void test_case_2()
	{
		tsk::task< int > t1(
			boost::bind(
				fibonacci_fn,
				5) );
		tsk::task< int > t2(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h1(
			tsk::async( boost::move( t1), tsk::new_thread() ) );
		tsk::handle< int > h2(
			tsk::async( boost::move( t2), tsk::new_thread() ) );
		BOOST_CHECK_EQUAL( h1.get(), 5);
		BOOST_CHECK_EQUAL( h2.get(), 55);
		BOOST_CHECK_NO_THROW( h1.swap( h2) );
		BOOST_CHECK_EQUAL( h1.get(), 55);
		BOOST_CHECK_EQUAL( h2.get(), 5);
	}

	// check runs not in pool
	void test_case_3()
	{
		tsk::task< bool > t( runs_in_pool_fn);
		tsk::handle< bool > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK_EQUAL( h.get(), false);
	}

	// check runtime_error throw inside task
	void test_case_4()
	{
		tsk::task< void > t( throwing_fn);
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK_THROW( h.get(), std::runtime_error);
	}

	// check wait
	void test_case_5()
	{
		tsk::task< int > t(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< int > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		h.wait();
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
		BOOST_CHECK_EQUAL( h.get(), 55);
	}

	// check wait_for
	void test_case_6()
	{
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 1) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( h.wait_for( pt::seconds( 3) ) );
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_7()
	{
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( ! h.wait_for( pt::seconds( 1) ) );
		BOOST_CHECK( ! h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_8()
	{
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 1) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( h.wait_until( boost::get_system_time() + pt::seconds( 3) ) );
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check wait_for
	void test_case_9()
	{
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( ! h.wait_until( boost::get_system_time() + pt::seconds( 1) ) );
		BOOST_CHECK( ! h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( ! h.has_exception() );
	}

	// check interrupt
	void test_case_10()
	{
		tsk::task< void > t(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		h.interrupt();
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait
	void test_case_11()
	{
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		h.interrupt_and_wait();
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_for
	void test_case_12()
	{
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( h.interrupt_and_wait_for( pt::seconds( 3) ) );
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_for
	void test_case_13()
	{
		tsk::task< void > t(
			boost::bind(
				non_interrupt_fn,
				3) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( ! h.interrupt_and_wait_for( pt::seconds( 1) ) );
	}

	// check interrupt_and_wait_until
	void test_case_14()
	{
		bool finished( false);
		tsk::task< void > t(
			boost::bind(
				interrupt_fn,
				pt::seconds( 1),
				boost::ref( finished) ) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( h.interrupt_and_wait_until( boost::get_system_time() + pt::seconds( 3) ) );
		BOOST_CHECK( finished);
		BOOST_CHECK( h.is_ready() );
		BOOST_CHECK( ! h.has_value() );
		BOOST_CHECK( h.has_exception() );
		BOOST_CHECK( h.interruption_requested() );
		BOOST_CHECK_THROW( h.get(), tsk::task_interrupted);
	}

	// check interrupt_and_wait_until
	void test_case_15()
	{
		tsk::task< void > t(
			boost::bind(
				non_interrupt_fn,
				3) );
		tsk::handle< void > h(
			tsk::async( boost::move( t), tsk::new_thread() ) );
		BOOST_CHECK( ! h.interrupt_and_wait_until( boost::get_system_time() + pt::seconds( 1) ) );
	}

	// check waitfor_all()
	void test_case_16()
	{
		std::vector< tsk::handle< int > > vec;
		for ( int i = 0; i <= 5; ++i)
		{
			tsk::task< int > t(
				boost::bind(
					fibonacci_fn,
					i) );
			vec.push_back(
				tsk::async( boost::move( t), tsk::new_thread() ) );
		}
		tsk::waitfor_all( vec.begin(), vec.end() );
		BOOST_CHECK( vec[0].is_ready() );
		BOOST_CHECK( vec[1].is_ready() );
		BOOST_CHECK( vec[2].is_ready() );
		BOOST_CHECK( vec[3].is_ready() );
		BOOST_CHECK( vec[4].is_ready() );
		BOOST_CHECK( vec[5].is_ready() );
		BOOST_CHECK_EQUAL( vec[0].get(), 0);
		BOOST_CHECK_EQUAL( vec[1].get(), 1);
		BOOST_CHECK_EQUAL( vec[2].get(), 1);
		BOOST_CHECK_EQUAL( vec[3].get(), 2);
		BOOST_CHECK_EQUAL( vec[4].get(), 3);
		BOOST_CHECK_EQUAL( vec[5].get(), 5);
	}

	// check waitfor_any()
	void test_case_17()
	{
		tsk::task< void > t1(
			boost::bind(
				delay_fn,
				pt::seconds( 3) ) );
		tsk::task< int > t2(
			boost::bind(
				fibonacci_fn,
				10) );
		tsk::handle< void > h1(
			tsk::async( boost::move( t1), tsk::new_thread() ) );
		tsk::handle< int > h2(
			tsk::async( boost::move( t2), tsk::new_thread() ) );
		tsk::waitfor_any( h1, h2);
		BOOST_CHECK( ! h1.is_ready() );
		BOOST_CHECK( h2.is_ready() );
		BOOST_CHECK_EQUAL( h2.get(), 55);
	}
};

boost::unit_test::test_suite * init_unit_test_suite( int, char* [])
{
	boost::unit_test::test_suite * test( BOOST_TEST_SUITE("Boost.Task: test suite") );

	boost::shared_ptr< test_new_thread > instance( new test_new_thread() );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_1, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_2, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_3, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_4, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_5, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_6, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_7, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_8, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_9, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_10, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_11, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_12, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_13, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_14, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_15, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_16, instance) );
	test->add( BOOST_CLASS_TEST_CASE( & test_new_thread::test_case_17, instance) );

	return test;
}
