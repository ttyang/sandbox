// (C) Copyright 2006-7 Anthony Williams
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include "util.inl"
#include "shared_mutex_locking_thread.hpp"

#define CHECK_LOCKED_VALUE_EQUAL(mutex_name,value,expected_value)    \
    {                                                                \
        boost::mutex::scoped_lock lock(mutex_name);                  \
        BOOST_CHECK_EQUAL(value,expected_value);                     \
    }

#ifdef BOOST_THREAD_TEST_CHRONO        
    using namespace boost::chrono;
    typedef system_clock::time_point system_time_point;
    system_time_point now() {return system_clock::now();}
    template <typename OSTREAM>
    OSTREAM& operator<<(OSTREAM & os, system_time_point t) {
        os << t.count();
        return os;
    }
#else        
    using namespace boost::posix_time;
    typedef boost::system_time system_time_point;
    system_time_point now() {return boost::get_system_time();}
    template <typename OSTREAM>
    OSTREAM& operator<<(OSTREAM & os, system_time_point t) {
        return os;
    }
#endif    


void test_timed_lock_shared_times_out_if_write_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;
    unsigned unblocked_count=0;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    boost::thread writer(simple_writing_thread(rw_mutex,finish_mutex,unblocked_mutex,unblocked_count));
    boost::thread::sleep(delay(1));
    CHECK_LOCKED_VALUE_EQUAL(unblocked_mutex,unblocked_count,1u);

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_shared_until(timeout);
#else
    bool timed_lock_succeeded=rw_mutex.timed_lock_shared(timeout);
#endif    
    system_time_point const end=now();
    std::cout
        << "timeout = " << timeout
        << "end = " << end
        << "\n";
    std::cout.flush();
    BOOST_CHECK((timeout-timeout_resolution)<end);
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_shared_for(wait_duration);
#else
    timed_lock_succeeded=rw_mutex.timed_lock_shared(wait_duration);
#endif    
    BOOST_CHECK((timeout2-timeout_resolution)<now());
    
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    finish_lock.unlock();
    writer.join();
}

void test_timed_lock_shared_succeeds_if_no_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_shared_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock_shared(timeout);
#endif    
    BOOST_CHECK(now()<timeout);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_shared_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock_shared(wait_duration);
#endif    
    BOOST_CHECK(now()<timeout2);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

}

void test_timed_lock_shared_succeeds_if_read_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;
    unsigned unblocked_count=0;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    boost::thread reader(simple_reading_thread(rw_mutex,finish_mutex,unblocked_mutex,unblocked_count));
    boost::thread::sleep(delay(1));
    CHECK_LOCKED_VALUE_EQUAL(unblocked_mutex,unblocked_count,1u);

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_shared_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock_shared(timeout);
#endif    
    BOOST_CHECK(now()<timeout);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_shared_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock_shared(wait_duration);
#endif    
    BOOST_CHECK(now()<timeout2);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    finish_lock.unlock();
    reader.join();
}

void test_timed_lock_times_out_if_write_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;
    unsigned unblocked_count=0;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    boost::thread writer(simple_writing_thread(rw_mutex,finish_mutex,unblocked_mutex,unblocked_count));
    boost::thread::sleep(delay(1));
    CHECK_LOCKED_VALUE_EQUAL(unblocked_mutex,unblocked_count,1u);

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock(timeout);
#endif    
    system_time_point const end=now();
    std::cout
        << "timeout = " << timeout
        << "end = " << end
        << "\n";
    std::cout.flush();
    BOOST_CHECK((timeout-timeout_resolution)<end);
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock(wait_duration);
#endif    
    BOOST_CHECK((timeout2-timeout_resolution)<now());
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

    finish_lock.unlock();
    writer.join();
}

void test_timed_lock_succeeds_if_no_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock(timeout);
#endif    
    BOOST_CHECK(now()<timeout);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock(wait_duration);
#endif    
    BOOST_CHECK(now()<timeout2);
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

}

void test_timed_lock_times_out_if_read_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;
    unsigned unblocked_count=0;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    boost::thread reader(simple_reading_thread(rw_mutex,finish_mutex,unblocked_mutex,unblocked_count));
    boost::thread::sleep(delay(1));
    CHECK_LOCKED_VALUE_EQUAL(unblocked_mutex,unblocked_count,1u);

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
    milliseconds const timeout_resolution(50);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock(timeout);
#endif    
    system_time_point const end=now();
    std::cout
        << "timeout = " << timeout
        << "end = " << end
        << "\n";
    std::cout.flush();
    BOOST_CHECK((timeout-timeout_resolution)<end);
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

    milliseconds const wait_duration(500);
    system_time_point const timeout2=now()+wait_duration;
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock(wait_duration);
#endif    
    BOOST_CHECK((timeout2-timeout_resolution)<now());
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }

    finish_lock.unlock();
    reader.join();
}

void test_timed_lock_times_out_but_read_lock_succeeds_if_read_lock_held()
{
    boost::shared_mutex rw_mutex;
    boost::mutex finish_mutex;
    boost::mutex unblocked_mutex;
    unsigned unblocked_count=0;
    boost::mutex::scoped_lock finish_lock(finish_mutex);
    boost::thread reader(simple_reading_thread(rw_mutex,finish_mutex,unblocked_mutex,unblocked_count));
#ifdef BOOST_THREAD_TEST_CHRONO        
    boost::this_thread::sleep_for(seconds(1));
#else    
    boost::this_thread::sleep(seconds(1));
#endif    
    CHECK_LOCKED_VALUE_EQUAL(unblocked_mutex,unblocked_count,1u);

    system_time_point const start=now();
    system_time_point const timeout=start+milliseconds(500);
#ifdef BOOST_THREAD_TEST_CHRONO        
    bool timed_lock_succeeded=rw_mutex.try_lock_until(timeout);
#else    
    bool timed_lock_succeeded=rw_mutex.timed_lock(timeout);
#endif    
    BOOST_CHECK(!timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock();
    }
    
    milliseconds const wait_duration(500);
#ifdef BOOST_THREAD_TEST_CHRONO        
    timed_lock_succeeded=rw_mutex.try_lock_shared_for(wait_duration);
#else    
    timed_lock_succeeded=rw_mutex.timed_lock_shared(wait_duration);
#endif    
    BOOST_CHECK(timed_lock_succeeded);
    if(timed_lock_succeeded)
    {
        rw_mutex.unlock_shared();
    }

    finish_lock.unlock();
    reader.join();
}


boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test_framework::test_suite* test =
        BOOST_TEST_SUITE("Boost.Threads: shared_mutex test suite");

    test->add(BOOST_TEST_CASE(&test_timed_lock_shared_times_out_if_write_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_shared_succeeds_if_no_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_shared_succeeds_if_read_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_times_out_if_write_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_times_out_if_read_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_succeeds_if_no_lock_held));
    test->add(BOOST_TEST_CASE(&test_timed_lock_times_out_but_read_lock_succeeds_if_read_lock_held));

    return test;
}
