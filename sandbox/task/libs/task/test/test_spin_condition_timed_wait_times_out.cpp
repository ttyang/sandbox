// Copyright (C) 2007-8 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/thread.hpp>

#include <boost/test/unit_test.hpp>

#include <boost/task.hpp>

#include <libs/task/test/util.ipp>

namespace tsk = boost::task;

bool fake_predicate()
{
    return false;
}

unsigned const timeout_seconds=2;
unsigned const timeout_grace=1;
boost::posix_time::milliseconds const timeout_resolution(100);


void do_test_timed_wait_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();
    boost::system_time const timeout=start+delay;

    while(cond.timed_wait(lock,timeout));

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_timed_wait_with_predicate_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();
    boost::system_time const timeout=start+delay;

    bool const res=cond.timed_wait(lock,timeout,fake_predicate);

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK(!res);
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_relative_timed_wait_with_predicate_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();

    bool const res=cond.timed_wait(lock,delay,fake_predicate);

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK(!res);
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_timed_wait_relative_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();

    while(cond.timed_wait(lock,delay));

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_cv_any_timed_wait_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();
    boost::system_time const timeout=start+delay;

    while(cond.timed_wait(lock,timeout));

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_cv_any_timed_wait_with_predicate_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();
    boost::system_time const timeout=start+delay;

    bool const res=cond.timed_wait(lock,timeout,fake_predicate);

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK(!res);
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_cv_any_relative_timed_wait_with_predicate_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();

    bool const res=cond.timed_wait(lock,delay,fake_predicate);

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK(!res);
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}

void do_test_cv_any_timed_wait_relative_times_out()
{
    tsk::spin_condition cond;
    tsk::spin_mutex m;

    boost::posix_time::seconds const delay(timeout_seconds);
    tsk::spin_mutex::scoped_lock lock(m);
    boost::system_time const start=boost::get_system_time();

    while(cond.timed_wait(lock,delay));

    boost::system_time const end=boost::get_system_time();
    BOOST_CHECK((delay-timeout_resolution)<=(end-start));
}


void test_timed_wait_times_out()
{
    timed_test(&do_test_timed_wait_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_timed_wait_with_predicate_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_relative_timed_wait_with_predicate_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_timed_wait_relative_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_cv_any_timed_wait_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_cv_any_timed_wait_with_predicate_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_cv_any_relative_timed_wait_with_predicate_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
    timed_test(&do_test_cv_any_timed_wait_relative_times_out, timeout_seconds+timeout_grace, execution_monitor::use_mutex);
}

boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test_framework::test_suite* test =
        BOOST_TEST_SUITE("Boost.Task: condition test suite");

    test->add(BOOST_TEST_CASE(&test_timed_wait_times_out));

    return test;
}
