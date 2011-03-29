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

#include <boost/stm/detail/config.hpp>
//-----------------------------------------------------------------------------
#include <boost/synchro/exceptions.hpp>
#include <boost/synchro/time.hpp>
#include <boost/synchro/detail/deleted_functions.hpp>
#include <boost/synchro/poly/lock.hpp>
#include <boost/synchro/poly/ref_lock_adapter.hpp>

namespace boost { namespace stm {

template <typename Lockable, typename Base=boost::synchro::poly::exclusive_lock
        , template <class, class> class Poly = boost::synchro::poly::exclusive_ref_lock_adapter >
class exclusive_lock_adapter;
    
template <typename Lockable, typename Base, template <class, class> class Poly >
class exclusive_lock_adapter
{
public:
    typedef Lockable lockable_type;

    BOOST_COPY_CONSTRUCTOR_DELETE(exclusive_lock_adapter) /*< disable copy construction >*/
    BOOST_COPY_ASSIGNEMENT_DELETE(exclusive_lock_adapter) /*< disable copy asignement >*/
    exclusive_lock_adapter() 
        : st_lock_()
        , dyn_lock_(st_lock_) 
    {}

    ~exclusive_lock_adapter() {}

    void lock() {stm::lock(st_lock_, dyn_lock_);}
    void unlock() {stm::unlock(st_lock_, dyn_lock_);}
    bool try_lock() { return stm::try_lock(st_lock_, dyn_lock_);}

    lockable_type& the_lock() { return st_lock_; }
    boost::synchro::poly::exclusive_lock& the_poly_lock() { return dyn_lock_; }
protected:
    mutable lockable_type               st_lock_;
    mutable Poly<lockable_type, Base>   dyn_lock_;
};

#if !defined(BOOST_STM_USE_BOOST_MUTEX) || !defined(BOOST_STM_T_USE_BOOST_MUTEX)
template <typename Base, template <class, class> class Poly >
class exclusive_lock_adapter<pthread_mutex_t, Base, Poly>
{
public:
    typedef pthread_mutex_t lockable_type;

    BOOST_COPY_CONSTRUCTOR_DELETE(exclusive_lock_adapter) /*< disable copy construction >*/
    BOOST_COPY_ASSIGNEMENT_DELETE(exclusive_lock_adapter) /*< disable copy asignement >*/
    exclusive_lock_adapter() 
        : st_lock_(PTHREAD_MUTEX_INITIALIZER)
        , dyn_lock_(st_lock_) 
    {}
    ~exclusive_lock_adapter() {}

    void lock() {stm::lock(st_lock_, dyn_lock_);}
    void unlock() {stm::unlock(st_lock_, dyn_lock_);}
    bool try_lock() { return stm::try_lock(st_lock_, dyn_lock_);}

    lockable_type& the_lock() { return st_lock_; }
    boost::synchro::poly::exclusive_lock& the_poly_lock() { return dyn_lock_; }
    
protected:
    mutable lockable_type               st_lock_;
    mutable Poly<lockable_type, Base>   dyn_lock_;
};
#endif
#if 0
#if BOOST_STM_LATM_GENERIC    

template <typename Lockable, typename Base=boost::synchro::poly::exclusive_lock
        , template <class, class> class Poly = boost::synchro::poly::exclusive_ref_lock_adapter >
class exclusive_ref_lock_adapter
{
public:
    typedef Lockable lockable_type;

    exclusive_ref_lock_adapter(lockable_type& lock)
        : st_lock_(lock)
        , dyn_lock_(lock) 
    {}
    ~exclusive_ref_lock_adapter() {}

    void lock() {stm::lock(st_lock_, dyn_lock_);}
    void unlock() {stm::unlock(st_lock_, dyn_lock_);}
    bool try_lock() { return stm::try_lock(st_lock_, dyn_lock_);}

protected:
    lockable_type* the_lock() { return &st_lock_; }
    mutable lockable_type& st_lock_;
    mutable Poly<lockable_type, Base> dyn_lock_;
};
#else
template <typename Lockable >
class exclusive_ref_lock_adapter
{
public:
    typedef Lockable lockable_type;

    exclusive_ref_lock_adapter(lockable_type& lock): st_lock_(lock) {}
    ~exclusive_ref_lock_adapter() {}

    void lock() {stm::lock(st_lock_, st_lock_);}
    void unlock() {stm::unlock(st_lock_, st_lock_);}
    bool try_lock() { return stm::try_lock(st_lock_, st_lock_);}

protected:
    lockable_type* the_lock() { return &st_lock_; }
    mutable lockable_type& st_lock_;
};

#endif
#endif
#if 0
template <typename Lockable>
void lock(exclusive_lock_adapter<Lockable>& lock) {transaction::lock(lock, lock);}
template <typename Lockable>
bool try_lock(exclusive_lock_adapter<Lockable>& lock) {return transaction::try_lock(lock, lock);}
template <typename Lockable>
void unlock(exclusive_lock_adapter<Lockable>& lock) {transaction::unlock(lock, lock);}

template <typename TimedLock>
class timed_lock_adapter
    : public exclusive_lock_adapter<TimedLock>
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

};

#endif

}
}
#endif