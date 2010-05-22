// Copyright (C) 2001-2003
// William E. Kempf
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/thread/detail/config.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/thread/condition.hpp>

#include <boost/test/unit_test.hpp>

#define DEFAULT_EXECUTION_MONITOR_TYPE execution_monitor::use_sleep_only
#include <libs/thread/test/util.inl>

#ifdef BOOST_THREAD_TEST_CHRONO        
    using namespace boost::chrono;
    typedef system_clock::time_point system_time_point;
    system_time_point now() {return system_clock::now();}
#else        
    using namespace boost::posix_time;
    typedef boost::system_time system_time_point;
    system_time_point now() {return boost::get_system_time();}
#endif    

template <typename M>
struct test_lock
{
    typedef M mutex_type;
    typedef typename M::scoped_lock lock_type;

    void operator()()
    {
        mutex_type mutex;
        boost::condition condition;

        // Test the lock's constructors.
        {
            lock_type lock(mutex, boost::defer_lock);
            BOOST_CHECK(!lock);
        }
        lock_type lock(mutex);
        BOOST_CHECK(lock ? true : false);

#ifdef BOOST_THREAD_TEST_CHRONO        
        // Test the lock and the mutex with condition variables.
        // No one is going to notify this condition variable.  We expect to
        // time out.
        BOOST_CHECK(!condition.wait_for(lock, milliseconds(100)));
#else
        // Construct and initialize an xtime for a fast time out.
        boost::xtime xt = delay(0, 100);

        // Test the lock and the mutex with condition variables.
        // No one is going to notify this condition variable.  We expect to
        // time out.
        BOOST_CHECK(!condition.timed_wait(lock, xt));
#endif        
        BOOST_CHECK(lock ? true : false);
        
        // Test the lock and unlock methods.
        lock.unlock();
        BOOST_CHECK(!lock);
        lock.lock();
        BOOST_CHECK(lock ? true : false);
    }
};

template <typename M>
struct test_trylock
{
    typedef M mutex_type;
    typedef typename M::scoped_try_lock try_lock_type;

    void operator()()
    {
        mutex_type mutex;
        boost::condition condition;

        // Test the lock's constructors.
        {
            try_lock_type lock(mutex);
            BOOST_CHECK(lock ? true : false);
        }
        {
            try_lock_type lock(mutex, boost::defer_lock);
            BOOST_CHECK(!lock);
        }
        try_lock_type lock(mutex);
        BOOST_CHECK(lock ? true : false);

#ifdef BOOST_THREAD_TEST_CHRONO        
        BOOST_CHECK(!condition.wait_for(lock, milliseconds(100)));
#else
        // Construct and initialize an xtime for a fast time out.
        boost::xtime xt = delay(0, 100);

        // Test the lock and the mutex with condition variables.
        // No one is going to notify this condition variable.  We expect to
        // time out.
        BOOST_CHECK(!condition.timed_wait(lock, xt));
#endif        
        BOOST_CHECK(lock ? true : false);

        // Test the lock, unlock and trylock methods.
        lock.unlock();
        BOOST_CHECK(!lock);
        lock.lock();
        BOOST_CHECK(lock ? true : false);
        lock.unlock();
        BOOST_CHECK(!lock);
        BOOST_CHECK(lock.try_lock());
        BOOST_CHECK(lock ? true : false);
    }
};

template<typename Mutex>
struct test_lock_times_out_if_other_thread_has_lock
{
    typedef boost::unique_lock<Mutex> Lock;
    
    Mutex m;
    boost::mutex done_mutex;
    bool done;
    bool locked;
    boost::condition_variable done_cond;
    
    test_lock_times_out_if_other_thread_has_lock():
        done(false),locked(false)
    {}

    void locking_thread()
    {
        Lock lock(m,boost::defer_lock);
#ifdef BOOST_THREAD_TEST_CHRONO        
        lock.try_lock_for(milliseconds(50));
#else
        lock.timed_lock(milliseconds(50));
#endif        

        boost::lock_guard<boost::mutex> lk(done_mutex);
        locked=lock.owns_lock();
        done=true;
        done_cond.notify_one();
    }

    void locking_thread_through_constructor()
    {
        Lock lock(m,milliseconds(50));

        boost::lock_guard<boost::mutex> lk(done_mutex);
        locked=lock.owns_lock();
        done=true;
        done_cond.notify_one();
    }

    bool is_done() const
    {
        return done;
    }

    typedef test_lock_times_out_if_other_thread_has_lock<Mutex> this_type;
    
    void do_test(void (this_type::*test_func)())
    {
        Lock lock(m);

        locked=false;
        done=false;
        
        boost::thread t(test_func,this);

        try
        {
            {
                boost::mutex::scoped_lock lk(done_mutex);
#ifdef BOOST_THREAD_TEST_CHRONO        
                BOOST_CHECK(done_cond.wait_for(lk,seconds(2),
                                                 boost::bind(&this_type::is_done,this)));
#else
                BOOST_CHECK(done_cond.timed_wait(lk,seconds(2),
                                                 boost::bind(&this_type::is_done,this)));
#endif                
                BOOST_CHECK(!locked);
            }
            
            lock.unlock();
            t.join();
        }
        catch(...)
        {
            lock.unlock();
            t.join();
            throw;
        }
    }
    

    void operator()()
    {
        do_test(&this_type::locking_thread);
        do_test(&this_type::locking_thread_through_constructor);
    }
};

template <typename M>
struct test_timedlock
{
    typedef M mutex_type;
    typedef typename M::scoped_timed_lock timed_lock_type;

    static bool fake_predicate()
    {
        return false;
    }

    void operator()()
    {
        test_lock_times_out_if_other_thread_has_lock<mutex_type>()();
        
        mutex_type mutex;
        boost::condition condition;

        // Test the lock's constructors.
        {

            // Construct and initialize an xtime for a fast time out.
            system_time_point xt = now()+milliseconds(100);
            
            timed_lock_type lock(mutex, xt);
            
            BOOST_CHECK(lock ? true : false);
        }
        {
            timed_lock_type lock(mutex, boost::defer_lock);
            BOOST_CHECK(!lock);
        }
        timed_lock_type lock(mutex);
        BOOST_CHECK(lock ? true : false);

        // Construct and initialize an xtime for a fast time out.
        system_time_point timeout = now()+milliseconds(100);
        // Test the lock and the mutex with condition variables.
        // No one is going to notify this condition variable.  We expect to
        // time out.
#ifdef BOOST_THREAD_TEST_CHRONO        
        BOOST_CHECK(!condition.wait_until(lock, timeout, fake_predicate));
#else
        BOOST_CHECK(!condition.timed_wait(lock, timeout, fake_predicate));
#endif        
        BOOST_CHECK(lock ? true : false);

        system_time_point now2=now();
        milliseconds const timeout_resolution(50);
        BOOST_CHECK((timeout-timeout_resolution)<now2);

        // Test the lock, unlock and timedlock methods.
        lock.unlock();
        BOOST_CHECK(!lock);
        lock.lock();
        BOOST_CHECK(lock ? true : false);
        lock.unlock();
        BOOST_CHECK(!lock);
        system_time_point target = now()+milliseconds(100);
#ifdef BOOST_THREAD_TEST_CHRONO        
        BOOST_CHECK(lock.try_lock_until(target));
#else
        BOOST_CHECK(lock.timed_lock(target));
#endif
        BOOST_CHECK(lock ? true : false);
        lock.unlock();
        BOOST_CHECK(!lock);

#ifdef BOOST_THREAD_TEST_CHRONO        
        BOOST_CHECK(mutex.try_lock_for(milliseconds(100)));
        mutex.unlock();

        BOOST_CHECK(lock.try_lock_for(milliseconds(100)));
#else
        BOOST_CHECK(mutex.timed_lock(milliseconds(100)));
        mutex.unlock();

        BOOST_CHECK(lock.timed_lock(milliseconds(100)));
#endif
        BOOST_CHECK(lock ? true : false);
        lock.unlock();
        BOOST_CHECK(!lock);
        
    }
};

template <typename M>
struct test_recursive_lock
{
    typedef M mutex_type;
    typedef typename M::scoped_lock lock_type;

    void operator()()
    {
        mutex_type mx;
        lock_type lock1(mx);
        lock_type lock2(mx);
    }
};


void do_test_mutex()
{
    test_lock<boost::mutex>()();
}

void test_mutex()
{
    timed_test(&do_test_mutex, 3);
}

void do_test_try_mutex()
{
    test_lock<boost::try_mutex>()();
    test_trylock<boost::try_mutex>()();
}

void test_try_mutex()
{
    timed_test(&do_test_try_mutex, 3);
}

void do_test_timed_mutex()
{
    test_lock<boost::timed_mutex>()();
    test_trylock<boost::timed_mutex>()();
    test_timedlock<boost::timed_mutex>()();
}

void test_timed_mutex()
{
    timed_test(&do_test_timed_mutex, 3);
}

void do_test_recursive_mutex()
{
    test_lock<boost::recursive_mutex>()();
    test_recursive_lock<boost::recursive_mutex>()();
}

void test_recursive_mutex()
{
    timed_test(&do_test_recursive_mutex, 3);
}

void do_test_recursive_try_mutex()
{
    test_lock<boost::recursive_try_mutex>()();
    test_trylock<boost::recursive_try_mutex>()();
    test_recursive_lock<boost::recursive_try_mutex>()();
}

void test_recursive_try_mutex()
{
    timed_test(&do_test_recursive_try_mutex, 3);
}

void do_test_recursive_timed_mutex()
{
    test_lock<boost::recursive_timed_mutex>()();
    test_trylock<boost::recursive_timed_mutex>()();
    test_timedlock<boost::recursive_timed_mutex>()();
    test_recursive_lock<boost::recursive_timed_mutex>()();
}

void test_recursive_timed_mutex()
{
    timed_test(&do_test_recursive_timed_mutex, 3);
}

boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test_framework::test_suite* test =
        BOOST_TEST_SUITE("Boost.Threads: mutex test suite");

    test->add(BOOST_TEST_CASE(&test_mutex));
    test->add(BOOST_TEST_CASE(&test_try_mutex));
    test->add(BOOST_TEST_CASE(&test_timed_mutex));
    test->add(BOOST_TEST_CASE(&test_recursive_mutex));
    test->add(BOOST_TEST_CASE(&test_recursive_try_mutex));
    test->add(BOOST_TEST_CASE(&test_recursive_timed_mutex));

    return test;
}
