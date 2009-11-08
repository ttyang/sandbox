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

#ifndef BOOST_STM_SYNC_AUTO_LOCK_H
#define BOOST_STM_SYNC_AUTO_LOCK_H

//---------------------------------------------------------------------------
#include <pthread.h>
#include <stdexcept>
//---------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <map>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/stm/detail/config.hpp>
//---------------------------------------------------------------------------
#include <boost/stm/datatypes.hpp>
#ifdef PERFORMING_LATM
#include <boost/stm/transaction.hpp>
#include <boost/stm/latm.hpp>
#else
#endif
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#ifdef PERFORMING_LATM
#define BOOST_STM_LOCK(a, b) boost::stm::lock(a,b)
#define BOOST_STM_UNLOCK(a, b) boost::stm::unlock(a, b)
#else
#define BOOST_STM_LOCK(a, b) boost::synchro::lock(a)
#define BOOST_STM_UNLOCK(a, b) boost::synchro::unlock(a)
#endif

//---------------------------------------------------------------------------
namespace boost { namespace stm {


//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class timer_lock_exception : public std::exception
{
public:
   timer_lock_exception(char const * const what) : what_(what) {}

   //virtual char const * what() const { return what_; }

private:
   char const * const what_;
};


typedef timer_lock_exception timer_err;

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class auto_lock
{
public:
   typedef std::pair<thread_id_t const, latm::mutex_type*> ThreadedLockPair;
   typedef std::multimap<thread_id_t const, latm::mutex_type*> ThreadedLockContainer;
   typedef ThreadedLockContainer::iterator ThreadedLockIter;

   auto_lock(latm::mutex_type &mutex) : hasLock_(false), lock_(mutex)
   {
      do_auto_lock();
   }

   auto_lock(latm::mutex_type *mutex) : hasLock_(false), lock_(*mutex)
   {
      do_auto_lock();
   }


   auto_lock(milliseconds_t timeOut, latm::mutex_type &mutex) : hasLock_(false), lock_(mutex)
   {
      do_timed_auto_lock(timeOut);
   }

   auto_lock(milliseconds_t timeOut, latm::mutex_type *mutex) : hasLock_(false), lock_(*mutex)
   {
      do_timed_auto_lock(timeOut);
   }

   ~auto_lock() { do_auto_unlock(); }

   bool has_lock() { return hasLock_; }

   void release_lock() { do_auto_unlock(); }

   static int VC6_fix()
   {
      static int VC6_fix = 0;
      return VC6_fix;
   }

private:

   void do_timed_auto_lock(milliseconds_t timeOut)
   {
      //lock_ = mutex;

      if (thread_has_lock(lock_)) return;

      for (milliseconds_t i = 0; i < timeOut; ++i)
      {
         if (synchro::try_lock(lock_))
         {
            hasLock_ = true;
            insert_into_threaded_lock_map(lock_);
            return;
         }

         SLEEP(1);
      }

      throw timer_lock_exception( "lock timed out" );
   }

   void insert_into_threaded_lock_map(latm::mutex_type& mutex)
   {
      synchro::lock_guard<Mutex> lock_i(*global_lock());
      threaded_locks().insert(ThreadedLockPair(this_thread::get_id(), &mutex));
   }

   void do_auto_lock()
   {
      //lock_ = mutex;
      if (thread_has_lock(lock_)) return;

      BOOST_STM_LOCK(lock_, lock_);
      hasLock_ = true;

      insert_into_threaded_lock_map(lock_);
   }

   void do_auto_unlock()
   {
      if (hasLock_)
      {
         hasLock_ = false;
         BOOST_STM_UNLOCK(lock_, lock_);
         remove_thread_has_lock(lock_);
      }
   }

   bool thread_has_lock(latm::mutex_type &rhs)
   {
      synchro::lock_guard<Mutex> lock_g(*global_lock());

      for (ThreadedLockIter i = threaded_locks().begin();
      i != threaded_locks().end(); ++i)
      {
         if (i->first == this_thread::get_id() && i->second == &rhs)
         {
            return true;
         }
      }

      return false;
   }

   void remove_thread_has_lock(latm::mutex_type &rhs)
   {
      synchro::lock_guard<Mutex> lock_g(*global_lock());

      for (ThreadedLockIter i = threaded_locks().begin();
      i != threaded_locks().end(); ++i)
      {
         if (i->first == this_thread::get_id() && i->second == &rhs)
         {
            threaded_locks().erase(i);
            break;
         }
      }
   }

   static Mutex *global_lock()
   {
#ifndef BOOST_STM_USE_BOOST_MUTEX
      static Mutex globalLock = PTHREAD_MUTEX_INITIALIZER;
#else
      static Mutex globalLock;
#endif
      return &globalLock;
   }

   static ThreadedLockContainer &threaded_locks()
   {
      static ThreadedLockContainer localThreadedLocks;
      return localThreadedLocks;
   }

   //auto_lock(auto_lock const &);
   //auto_lock& operator=(auto_lock const &);

   bool hasLock_;
   latm::mutex_type &lock_;
};

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#define use_lock(L) if (bool __end=false); else \
    for (boost::stm::auto_lock ___l(L); !__end; __end=true)
#define use_timed_lock(T, L) if (bool __end=false); else \
    for (boost::stm::auto_lock ___l(T, L); !__end; __end=false)
#define try_timed_lock(T, L)  if (bool __end=false); else \
    try { for (boost::stm::auto_lock ___l(T, L); !__end; __end=false)

#define catch_lock_timeout(E) } catch (std::timer_lock_exception &E)
#define lock_timeout } catch (std::timer_lock_exception &E)

}}

#endif // BOOST_STM_AUTO_LOCK_H









