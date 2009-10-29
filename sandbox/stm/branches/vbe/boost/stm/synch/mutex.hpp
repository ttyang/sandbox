//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/stm for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_STM_SYNCH_MUTEX__HPP
#define BOOST_STM_SYNCH_MUTEX__HPP

#include <boost/synchro/exceptions.hpp>
#include <boost/synchro/time.hpp>
#include <boost/synchro/detail/deleted_functions.hpp>
#include <boost/synchro/poly/lock.hpp>

namespace boost { namespace stm {

template <typename Lockable>
class latm_exclusive_lock_adapter : public boost::synchro::poly::exclusive_lock
{
public:
    typedef Lockable lockable_type;

    BOOST_COPY_CONSTRUCTOR_DELETE(latm_exclusive_lock_adapter) /*< disable copy construction >*/
    BOOST_COPY_ASSIGNEMENT_DELETE(latm_exclusive_lock_adapter) /*< disable copy asignement >*/   
    latm_exclusive_lock_adapter() {}
    ~latm_exclusive_lock_adapter() {}

    void lock() {stm::lock(lock_);}
    void unlock() {stm::unlock(lock_);}
    bool try_lock() { return stm::try_lock(lock_);}

protected:
    lockable_type* the_lock() { return &lock_; }
    mutable lockable_type lock_;
};

template <typename Lockable>
void lock(latm_exclusive_lock_adapter<Lockable>& lock) {transaction::pthread_lock(&lock);}
template <typename Lockable>
bool try_lock(latm_exclusive_lock_adapter<Lockable>& lock) {return transaction::pthread_trylock(&lock);} 
template <typename Lockable>
void unlock(latm_exclusive_lock_adapter<Lockable>& lock) {transaction::pthread_unlock(&lock);}

#if 0
template <typename TimedLock>
class latm_timed_lock_adapter
    : public latm_exclusive_lock_adapter<TimedLock>
{
public:
    typedef TimedLock lockable_base_type;

    timed_lockable_adapter() {}

    template<typename Clock, typename Duration>
    bool try_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {return transaction::try_lock_until(the_lock(), abs_time);}
    template<typename Rep, typename Period>
    bool try_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {return transaction::try_lock_for(the_lock(), rel_time);}
    

    template<typename Clock, typename Duration>
    void lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {transaction::lock_until(the_lock(), abs_time);}
    template<typename Rep, typename Period>
    void lock_for(chrono::duration<Rep, Period> const & rel_time)
    {transaction::::lock_for(the_lock(), rel_time);}
    
protected:
    //TimedLock& the_lock() {return *static_cast<TimedLock*>(&this->lock_);}
};

#endif

}
}
#endif
