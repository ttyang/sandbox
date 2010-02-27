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

//-----------------------------------------------------------------------------
//
// LatmDefTxImlp.h
//
// This file contains method implementations for transaction.hpp (specifically for
// enabling lock aware transactions). The main purpose of this file is to reduce
// the complexity of the transaction class by separating its implementation into
// a secondary .h file.
//
// Do NOT place these methods in a .cc/.cpp/.cxx file. These methods must be
// inlined to keep DracoSTM performing fast. If these methods are placed in a
// C++ source file they will incur function call overhead - something we need
// to reduce to keep performance high.
//
//-----------------------------------------------------------------------------
#ifndef BOOST_STM_LATM_DEF_TX_IMPL_H
#define BOOST_STM_LATM_DEF_TX_IMPL_H


#if PERFORMING_LATM

#include <fstream>

namespace boost { namespace stm {

//----------------------------------------------------------------------------
//
// ASSUMPTION: latmMutex_ MUST BE OBTAINED BEFORE CALLING THIS METHOD
//
//----------------------------------------------------------------------------
inline bool transaction::def_do_core_tx_conflicting_lock_pthread_lock_mutex
(latm::mutex_type* mutex, int lockWaitTime, int lockAborted, bool txIsIrrevocable)
{
    //--------------------------------------------------------------------------
    // see if this mutex is part of any of the in-flight transactions conflicting
    // mutex set. if it is, stop that transaction and add it to the latm conflicting
    // set. do not keep in-flight transactions blocked once the transactions have
    // been processed.
    //--------------------------------------------------------------------------
    synchro::lock_guard<Mutex> lk_g(*general_lock());
    synchro::lock_guard<Mutex> lk_i(*inflight_lock());

    std::list<transaction *> txList;
    std::set<thread_id_t> txThreadId;

    for (InflightTxes::iterator i = transactionsInFlight_.begin();
      i != transactionsInFlight_.end(); ++i)
    {
        BOOST_ASSERT(*i!=0);
        (*i)->assert_tx_type();
        transaction *t = *i;

        // if this tx is part of this thread, skip it (it's an LiT)
        if (t->threadId_ == this_thread::get_id()) continue;

        // if this mutex has a conflict with an inflight tx
        if (t->get_tx_conflicting_locks().find(mutex) != t->get_tx_conflicting_locks().end())
        {
            if (txIsIrrevocable || (!t->irrevocable() &&
                cm_allow_lock_to_abort_tx(lockWaitTime, lockAborted, txIsIrrevocable, *t)))
            {
                txList.push_back(t);
            }
            else return false;
        }
    }

    if (!txList.empty())
    {
#if LOGGING_BLOCKS
        logFile_ << "----------------------\nbefore locked mutex: " << mutex << endl << endl;
        logFile_ << outputBlockedThreadsAndLockedLocks() << endl;
#endif

        for (std::list<transaction*>::iterator it = txList.begin(); txList.end() != it; ++it)
        {
            BOOST_ASSERT(*it!=0);

            transaction *t = *it;

            t->force_to_abort();
            t->block();
            txThreadId.insert(t->threadId_);
        }

        try {
            latm::instance().latmLockedLocksAndThreadIdsMap_.insert
                (std::make_pair<latm::mutex_type*, ThreadIdSet>(mutex, txThreadId));
        }
        catch (...)
        {
            for (std::set<thread_id_t>::iterator it = txThreadId.begin();
                txThreadId.end() != it; ++it)
            {
                if (0 == thread_id_occurance_in_locked_locks_map(*it))
                {
                    *blocked_ptr(*it) = false;
                }
            }
            throw;
        }

#if LOGGING_BLOCKS
        logFile_ << "----------------------\nafter locked mutex: " << mutex << endl << endl;
        logFile_ << outputBlockedThreadsAndLockedLocks() << endl;
#endif
    }

    return true;
}

//----------------------------------------------------------------------------
// only allow one thread to execute any of these methods at a time
//----------------------------------------------------------------------------
template <typename M> 
inline void transaction::def_tx_lock(M& m, latm::mutex_type& mutex)
{
   int waitTime = 0, aborted = 0;

   //--------------------------------------------------------------------------
   // this is the most complex code in the entire system. it is highly order
   // dependent.
   //
   // if an in-flight transaction is present when this lock is attempted to be
   // obtained:
   //
   // (1) make sure the lock is in the conflicting set, otherwise throw
   // (2) make the tx irrevocable - THIS MUST BE DONE BEFORE THE LOCK IS OBTAINED
   //                               otherwise the system can deadlock by obtaining
   //                               the lock and then failing to become irrevocable
   //                               while another irrevocable tx needs the lock we
   //                               took.
   // (3) obtain the lock
   // (4) add the lock to the tx's obtained locked list ONLY after it has been
   //     obtained. adding it before the lock is obtained can lead to deadlock
   //     as another thread which is releasing the lock will not unblock txs
   //     that it has blocked due to our claiming to have obtained the lock
   // (5) abort all the in-flight conflicting txes and return
   //--------------------------------------------------------------------------
    if (transaction* t = get_inflight_tx_of_same_thread(false))
    {
        t->must_be_in_conflicting_lock_set(&mutex);
        t->make_irrevocable();

        if (!t->is_currently_locked_lock(&mutex))
        {
            synchro::lock(m);
        }

        t->add_to_currently_locked_locks(&mutex);
        t->add_to_obtained_locks(&mutex);
        t->commit_deferred_update_tx();

        synchro::lock_guard<Mutex> lk_l(latm::instance().latmMutex_);
        def_do_core_tx_conflicting_lock_pthread_lock_mutex(&mutex, 0, 0, true);
        return;
    }

    for (;;)
    {
        {
        synchro::unique_lock<M> lk(m);
        synchro::lock_guard<Mutex> lk_l(latm::instance().latmMutex_);

        //--------------------------------------------------------------------
        // if we are able to do the core lock work, break
        //--------------------------------------------------------------------
        if (def_do_core_tx_conflicting_lock_pthread_lock_mutex(&mutex, waitTime, aborted, false))
        {
            latm::instance().latmLockedLocksOfThreadMap_[&mutex] = this_thread::get_id();
            lk.release();
            return;
        }
        }

        //-----------------------------------------------------------------------
        // we weren't able to do the core lock work, unlock our mutex and sleep
        //-----------------------------------------------------------------------
        SLEEP(cm_lock_sleep_time());
        waitTime += cm_lock_sleep_time();
        ++aborted;
    }

    // note: we do not release the transactionsInFlightMutex - this will prevents
    // new transactions from starting until this lock is released
    return;
}

//----------------------------------------------------------------------------
// only allow one thread to execute any of these methods at a time
//----------------------------------------------------------------------------
template <typename M> 
inline bool transaction::def_tx_try_lock(M& m, latm::mutex_type& mutex)
{
    //--------------------------------------------------------------------------

    BOOST_ASSERT(false&& "might not be possible to implement trylock for this");

    bool txIsIrrevocable = false;

    synchro::unique_lock<M> lk(m, synchro::try_to_lock);
    if (!lk) return false;

    synchro::lock_guard<Mutex> lk_l(latm::instance().latmMutex_);

    if (transaction* t = get_inflight_tx_of_same_thread(false))
    {
        txIsIrrevocable = true;
        t->must_be_in_conflicting_lock_set(&mutex);
        t->make_irrevocable();
        t->add_to_obtained_locks(&mutex);
        t->commit_deferred_update_tx();
    }

    //-----------------------------------------------------------------------
    // if !core done, since trylock, we cannot stall & retry - just exit
    //-----------------------------------------------------------------------
    if (!def_do_core_tx_conflicting_lock_pthread_lock_mutex(&mutex, 0, 0, txIsIrrevocable))
    {
        return false;
    }

    latm::instance().latmLockedLocksOfThreadMap_[&mutex] = this_thread::get_id();

    // note: we do not release the transactionsInFlightMutex - this will prevents
    // new transactions from starting until this lock is released
    lk.release();
    return true;
}

//----------------------------------------------------------------------------
// only allow one thread to execute any of these methods at a time
//----------------------------------------------------------------------------
template <typename M> 
inline void transaction::def_tx_unlock(M& m, latm::mutex_type& mutex)
{
    synchro::lock_guard<Mutex> lk_l(*latm_lock());
    synchro::lock_guard<Mutex> lk_g(*general_lock());
    synchro::lock_guard<Mutex> lk_i(*inflight_lock());
    bool hasLock = true;

    if (transaction* t = get_inflight_tx_of_same_thread(true))
    {
        if (!t->is_on_obtained_locks_list(&mutex))
        {
            // this is illegal, it means the transaction is unlocking a lock
            // it did not obtain (e.g., early release) while the transaction
            // is still in-flight. Throw exception
            BOOST_ASSERT(false&& "lock released for transaction that did not obtain it");
        }

        if (!t->is_currently_locked_lock(&mutex)) hasLock = false;
        t->remove_from_currently_locked_locks(&mutex);
    }

    //--------------------------------------------------------------------------
    // if this mutex is on the tmConflictingLocks_ set, then we need to remove
    // it from the latmLocks and any txs on the full thread list that are
    // blocked because of this lock being locked should be unblocked
    //--------------------------------------------------------------------------
    if (latm::instance().latmLockedLocksAndThreadIdsMap_.find(&mutex) != latm::instance().latmLockedLocksAndThreadIdsMap_.end())
    {
#if LOGGING_BLOCKS
        logFile_ << "----------------------\nbefore unlocked mutex: " << &mutex << endl << endl;
        logFile_ << outputBlockedThreadsAndLockedLocks() << endl;
#endif
        latm::instance().latmLockedLocksAndThreadIdsMap_.erase(&mutex);
        unblock_conflicting_threads(&mutex);

#if LOGGING_BLOCKS
        logFile_ << "----------------------\nafter unlocked mutex: " << &mutex << endl << endl;
        logFile_ << outputBlockedThreadsAndLockedLocks() << endl;
#endif
    }

    latm::instance().latmLockedLocksOfThreadMap_.erase(&mutex);
    unblock_threads_if_locks_are_empty();

    if (hasLock) synchro::unlock(m);
    return;
}

}}
#endif

#endif // LATM_DEF_TX_IMPL_H

