
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
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/utility.hpp>

#include <boost/fiber.hpp>

int value = 0;

void wait_fn( boost::fibers::manual_reset_event & ev)
{
	ev.wait();
	++value;
}

void test_case_1()
{
	value = 0;
	boost::fibers::scheduler<> sched;
	boost::fibers::manual_reset_event ev( sched);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	BOOST_CHECK_EQUAL( std::size_t( 2), sched.size() );
	BOOST_CHECK_EQUAL( 0, value);

	BOOST_CHECK( sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 2), sched.size() );
	BOOST_CHECK_EQUAL( 0, value);

	ev.set();

	while ( sched.run() );

	BOOST_CHECK( ! sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 0), sched.size() );
	BOOST_CHECK_EQUAL( 2, value);
}

void test_case_2()
{
	value = 0;
	boost::fibers::scheduler<> sched;
	boost::fibers::manual_reset_event ev( sched);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	BOOST_CHECK_EQUAL( std::size_t( 2), sched.size() );
	BOOST_CHECK_EQUAL( 0, value);

	BOOST_CHECK( sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 2), sched.size() );
	BOOST_CHECK_EQUAL( 0, value);

	ev.set();

	BOOST_CHECK( sched.run() );
	BOOST_CHECK( sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 1), sched.size() );
	BOOST_CHECK_EQUAL( 1, value);

	ev.reset();

	BOOST_CHECK( sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 1), sched.size() );
	BOOST_CHECK_EQUAL( 1, value);

	BOOST_CHECK( ! sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 1), sched.size() );
	BOOST_CHECK_EQUAL( 1, value);

	ev.set();

	BOOST_CHECK( sched.run() );
	BOOST_CHECK( ! sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 0), sched.size() );
	BOOST_CHECK_EQUAL( 2, value);
}

void test_case_3()
{
	value = 0;
	boost::fibers::scheduler<> sched;
	boost::fibers::manual_reset_event ev( sched, true);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	sched.make_fiber(
		wait_fn,
		boost::ref( ev),
		boost::fiber::default_stacksize);

	BOOST_CHECK_EQUAL( std::size_t( 2), sched.size() );
	BOOST_CHECK_EQUAL( 0, value);

	while ( sched.run() );

	BOOST_CHECK( ! sched.run() );
	BOOST_CHECK_EQUAL( std::size_t( 0), sched.size() );
	BOOST_CHECK_EQUAL( 2, value);
}

void test_case_4()
{
	boost::fibers::scheduler<> sched;
	boost::fibers::manual_reset_event ev( sched);

	BOOST_CHECK_EQUAL( false, ev.try_wait() );

	ev.set();

	BOOST_CHECK_EQUAL( true, ev.try_wait() );
	BOOST_CHECK_EQUAL( true, ev.try_wait() );

	ev.reset();

	BOOST_CHECK_EQUAL( false, ev.try_wait() );
}

boost::unit_test::test_suite * init_unit_test_suite( int, char* [])
{
	boost::unit_test::test_suite * test =
		BOOST_TEST_SUITE("Boost.Fiber: manual-reset-event test suite");

	test->add( BOOST_TEST_CASE( & test_case_1) );
	test->add( BOOST_TEST_CASE( & test_case_2) );
	test->add( BOOST_TEST_CASE( & test_case_3) );
	test->add( BOOST_TEST_CASE( & test_case_4) );

	return test;
}
