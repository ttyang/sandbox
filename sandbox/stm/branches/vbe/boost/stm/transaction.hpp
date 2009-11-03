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

#ifndef BOOST_STM_TRANSACTION__HPP
#define BOOST_STM_TRANSACTION__HPP

//-----------------------------------------------------------------------------
#include <assert.h>
#include <pthread.h>
//-----------------------------------------------------------------------------
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
//-----------------------------------------------------------------------------
#include <boost/synchro/tss.hpp>
//-----------------------------------------------------------------------------
#include <boost/stm/detail/config.hpp>
//-----------------------------------------------------------------------------
#include <boost/stm/base_transaction.hpp>
#include <boost/stm/datatypes.hpp>
#include <boost/stm/transaction_bookkeeping.hpp>
#include <boost/stm/contention_managers/select_contention_manager.hpp>
#include <boost/stm/memory_managers/base_memory_manager.hpp>
#include <boost/stm/latm.hpp>
//-----------------------------------------------------------------------------
#include <boost/stm/detail/bloom_filter.hpp>
#include <boost/stm/detail/deleters.hpp>
#include <boost/stm/detail/monotonic_storage.hpp>
#include <boost/stm/detail/move.hpp>
#include <boost/stm/detail/transactions_stack.hpp>
#include <boost/stm/detail/vector_map.hpp>
#include <boost/stm/detail/vector_set.hpp>

//-----------------------------------------------------------------------------
namespace boost { namespace stm {

//-----------------------------------------------------------------------------
// boolean which is used to invoke "begin_transaction()" upon transaction
// object construction (so two lines of code aren't needed to make a
// transaction start, in case the client wants to start the transaction
// immediately).
//-----------------------------------------------------------------------------
bool const begin_transaction = true;



typedef std::pair<base_transaction_object*, base_transaction_object*> tx_pair;


///////////////////////////////////////////////////////////////////////////////
// transaction Class
///////////////////////////////////////////////////////////////////////////////
class transaction
{
public:
   //--------------------------------------------------------------------------
   // transaction typedefs
   //--------------------------------------------------------------------------

#if PERFORMING_VALIDATION
   typedef std::map<base_transaction_object*, version_t> ReadContainer;
#else
   typedef std::set<base_transaction_object*> ReadContainer;
#endif
   typedef std::map<thread_id_t, ReadContainer*> ThreadReadContainer;

#ifdef MAP_WRITE_CONTAINER
   typedef std::map<base_transaction_object*, base_transaction_object*> WriteContainer;
#else
   typedef vector_map<base_transaction_object*, base_transaction_object*> WriteContainer;
#endif

#ifndef MAP_NEW_CONTAINER
   typedef vector_set<detail::deleter_type*> MemoryContainerList;
#else
   typedef std::list<detail::deleter_type*> MemoryContainerList;
#endif

   struct transaction_tss_storage {
       TransactionsStack transactions_;
   };

   typedef std::map<thread_id_t, WriteContainer*> ThreadWriteContainer;
   typedef std::map<thread_id_t, TxType*> ThreadTxTypeContainer;

   typedef std::set<transaction*> TContainer;
   typedef std::set<transaction*> InflightTxes;

   typedef std::multimap<clock_t, MemoryContainerList > DeletionBuffer;


   typedef std::set<thread_id_t> ThreadIdSet;

   typedef std::map<thread_id_t, MemoryContainerList*> ThreadMemoryContainerList;

   typedef std::pair<thread_id_t, Mutex*> thread_mutex_pair;
    #ifndef MAP_THREAD_MUTEX_CONTAINER
    typedef vector_map<thread_id_t, Mutex*> ThreadMutexContainer;
    #else
    typedef std::map<thread_id_t, Mutex*> ThreadMutexContainer;
    #endif

   typedef std::map<thread_id_t, bloom_filter*> ThreadBloomFilterList;
    #ifdef BOOST_STM_BLOOM_FILTER_USE_DYNAMIC_BITSET
    typedef std::map<thread_id_t, boost::dynamic_bitset<>*> ThreadBitVectorList;
    #else
    typedef std::map<thread_id_t, bit_vector*> ThreadBitVectorList;
    #endif
   typedef std::pair<thread_id_t, int*> thread_bool_pair;
    #ifndef MAP_THREAD_BOOL_CONTAINER
   typedef vector_map<thread_id_t, int*> ThreadBoolContainer;
    #else
   typedef std::map<thread_id_t, int*> ThreadBoolContainer;
    #endif

   typedef std::set<transaction*> LockedTransactionContainer;

   typedef InflightTxes in_flight_transaction_container;
   typedef in_flight_transaction_container in_flight_trans_cont;

    #ifdef USE_SINGLE_THREAD_CONTEXT_MAP
    struct tx_context
    {
        #if defined(BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER)
        monotonic_storage<6*1000*1000> mstorage_;
        #endif
        MemoryContainerList newMem;
        MemoryContainerList delMem;
        WriteContainer writeMem;
        bloom_filter wbloom;
        bloom_filter bloom;
        TxType txType; // 2 bits

        int abort; // bool 1 bit
    };


    #ifdef BOOST_STM_HAVE_SINGLE_TSS_CONTEXT_MAP

    // thread specific data
    struct tss_context
    {
        inline tss_context()
        : tx_()
        #ifndef BOOST_STM_USE_BOOST_MUTEX
        #if WIN32
        , mutex_(PTHREAD_MUTEX_INITIALIZER)
        #endif
        #else
        , mutex_()
        #endif

        #if PERFORMING_LATM
        , blocked_(false)
        #endif
        {
            #ifndef BOOST_STM_USE_BOOST_MUTEX
            pthread_mutex_init(&mutex_, 0);
            #endif
        }
        inline ~tss_context() {
           pthread_mutex_destroy(&mutex_);
        }

        tx_context tx_;
        Mutex mutex_;
        #if PERFORMING_LATM
        int blocked_;
        #endif
        #if PERFORMING_LATM
        #if USING_TRANSACTION_SPECIFIC_LATM
        latm::mutex_set conflictingMutex_;
        #endif
        latm::mutex_set obtainedLocks_;
        latm::mutex_set currentlyLockedLocks_;
        #endif
    };

    #endif

    #ifndef BOOST_STM_HAVE_SINGLE_TSS_CONTEXT_MAP
    typedef std::map<thread_id_t, tx_context*> tss_context_map_type;
    #else
    typedef std::map<thread_id_t, tss_context*> tss_context_map_type;
    #endif
    #endif

   //--------------------------------------------------------------------------
   // transaction static methods
   //--------------------------------------------------------------------------
   static void initialize();
   static void initialize_thread();
   static void terminate_thread();

   inline static void enableLoggingOfAbortAndCommitSetSize() { bookkeeping_.setIsLoggingAbortAndCommitSize(true); }
   inline static void disableLoggingOfAbortAndCommitSetSize() { bookkeeping_.setIsLoggingAbortAndCommitSize(false); }

   inline static const transaction_bookkeeping & bookkeeping() { return bookkeeping_; }

   inline static bool early_conflict_detection() { return !directLateWriteReadConflict_ && direct_updating(); }
   inline static bool late_conflict_detection() { return directLateWriteReadConflict_ || !direct_updating(); }

   inline static bool enable_dynamic_priority_assignment()
   {
      return dynamicPriorityAssignment_ = true;
   }

   inline static bool disable_dynamic_priority_assignment()
   {
      return dynamicPriorityAssignment_ = false;
   }

   inline static bool using_move_semantics() { return usingMoveSemantics_; }
   inline static bool using_copy_semantics() { return !using_move_semantics(); }

   inline static void enable_move_semantics()
   {
      if (!kDracoMoveSemanticsCompiled)
         throw "move semantics off - rebuild with #define BUILD_MOVE_SEMANTICS 1";
      usingMoveSemantics_ = true;
   }

   inline static void disable_move_semantics()
   {
      usingMoveSemantics_ = false;
   }

   inline static bool doing_dynamic_priority_assignment()
   {
      return dynamicPriorityAssignment_;
   }

   static bool do_early_conflict_detection()
   {
      if (!transactionsInFlight_.empty()) return false;
      if (deferred_updating()) return false;
      else return !(directLateWriteReadConflict_ = false);
   }

   static bool do_late_conflict_detection()
   {
      if (!transactionsInFlight_.empty()) return false;
      else return directLateWriteReadConflict_ = true;
   }

   inline static std::string consistency_checking_string()
   {
      if (validating()) return "val";
      else return "inval";
   }

   inline static bool validating()
   {
    #ifdef PERFORMING_VALIDATION
      return true;
    #endif
      return false;
   }

   inline static bool invalidating() { return !validating(); }

   inline static bool direct_updating() { return direct_updating_; }
   inline static bool& direct_updating_ref() { return direct_updating_; }
   inline static bool deferred_updating() { return !direct_updating_; }

   //--------------------------------------------------------------------------
   // make all transactions direct as long as no transactions are in flight
   //--------------------------------------------------------------------------
   static bool do_direct_updating()
   {
      if (!transactionsInFlight_.empty()) return false;
      else direct_updating_ref() = true;
      return true;
   }

   //--------------------------------------------------------------------------
   // make all transactions deferred as long as no transactions are in flight
   //--------------------------------------------------------------------------
   static bool do_deferred_updating()
   {
      if (!transactionsInFlight_.empty()) return false;
      else direct_updating_ref() = false;
      return true;
   }

   static std::string update_policy_string()
   {
      return direct_updating() ? "dir" : "def";
   }

   //--------------------------------------------------------------------------
   // Lock Aware Transactional Memory support methods
   //--------------------------------------------------------------------------

   inline static void lock_(latm::mutex_type &lock) { pthread_lock(&lock); }
   inline static void lock_(latm::mutex_type *lock) { pthread_lock(lock); }

   inline static bool trylock_(latm::mutex_type &lock) { return pthread_trylock(&lock); }
   inline static bool trylock_(latm::mutex_type *lock) { return pthread_trylock(lock); }

   inline static void unlock_(latm::mutex_type &lock) { pthread_unlock(&lock); }
   inline static void unlock_(latm::mutex_type *lock) { pthread_unlock(lock); }

   static void pthread_lock(latm::mutex_type* lock);
   static bool pthread_trylock(latm::mutex_type* lock);
   static void pthread_unlock(latm::mutex_type* lock);

   //--------------------------------------------------------------------------
    #if PERFORMING_LATM
   //--------------------------------------------------------------------------
   inline static void tm_lock_conflict(latm::mutex_type &lock)
   {
      tm_lock_conflict(&lock);
   }
   static void tm_lock_conflict(latm::mutex_type* lock);

   static void clear_tm_conflicting_locks();
   //inline static latm::mutex_set get_tm_conflicting_locks() { return tmConflictingLocks_; }

   void must_be_in_conflicting_lock_set(latm::mutex_type* inLock);
   //static void must_be_in_tm_conflicting_lock_set(latm::mutex_type* inLock);

    #if USING_TRANSACTION_SPECIFIC_LATM
   void see_if_tx_must_block_due_to_tx_latm();

   inline void lock_conflict(latm::mutex_type &lock)
   { add_tx_conflicting_lock(&lock); }

   inline void lock_conflict(latm::mutex_type* lock)
   { add_tx_conflicting_lock(lock); }

   inline void add_tx_conflicting_lock(latm::mutex_type &lock)
   {
      add_tx_conflicting_lock(&lock);
   }
   void add_tx_conflicting_lock(latm::mutex_type* lock);

   void clear_tx_conflicting_locks();
   //latm::mutex_set get_tx_conflicting_locks() { return conflictingMutexRef_; }


    #endif

   void add_to_obtained_locks(latm::mutex_type* mutex);
   static void unblock_conflicting_threads(latm::mutex_type* mutex);
   static bool mutex_is_on_obtained_tx_list(latm::mutex_type* mutex);
   static void unblock_threads_if_locks_are_empty();
   void clear_latm_obtained_locks();

   void add_to_currently_locked_locks(latm::mutex_type*  m);
   void remove_from_currently_locked_locks(latm::mutex_type* m);
   bool is_currently_locked_lock(latm::mutex_type* m);
   bool is_on_obtained_locks_list(latm::mutex_type* m);
    #endif

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   transaction();
   ~transaction();


   bool check_throw_before_restart() const
   {
      // if this transaction is in-flight or it committed, just ignore it
      if (in_flight() || committed()) return true;

      //-----------------------------------------------------------------------
      // if there is another in-flight transaction from this thread, and we
      // are using closed nesting with flattened transactions, we should throw
      // an exception here because restarting the transactions will cause it to
      // infinitely fail
      //-----------------------------------------------------------------------
      synchro::lock_guard<Mutex> lock_m(*inflight_lock());
      if (other_in_flight_same_thread_transactions())
      {
         throw aborted_transaction_exception("closed nesting throw");
      }

      return true;
   }

   inline bool committed() const { return state() == e_committed || state() == e_hand_off; }
   inline bool aborted() const { return state() == e_aborted; }
   inline bool in_flight() const { return state() == e_in_flight; }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   template <typename T>
   T& find_original(T& in)
   {
      //-----------------------------------------------------------------------
      // if transactionThread_ is not invalid it means this is the original, so
      // we can return it. Otherwise, we need to search for the original in
      // our write set
      //-----------------------------------------------------------------------
      if (1 == in.new_memory()) return in;
      if (in.transaction_thread() == invalid_thread_id()) return in;

      base_transaction_object *inPtr = (base_transaction_object*)&in;

      for (WriteContainer::iterator i = writeList().begin(); i != writeList().end(); ++i)
      {
         if (i->second == (inPtr))
         {
            return *static_cast<T*>(i->first);
         }
      }

      //-----------------------------------------------------------------------
      // if it's not in our original / new list, then we need to except
      //-----------------------------------------------------------------------
      throw aborted_transaction_exception("original not found");
   }

   //--------------------------------------------------------------------------
   // The below methods change their behavior based on whether the transaction
   // is direct or deferred:
   //
   //    read           - deferred_read or direct_read
   //    write          - deferred_write or direct_write
   //    delete_memory  - deferred_delete_memory or direct_delete_memory
   //    commit         - deferred_commit or direct_commit
   //    abort          - deferred_abort or direct_abort
   //
   // In addition, a number of commit or abort methods must be made deferred or
   // direct as their version / memory management is entirely different if the
   // transaction is direct or deferred.
   //
   //--------------------------------------------------------------------------
    #ifndef DISABLE_READ_SETS
   inline std::size_t const read_set_size() const { return readListRef_.size(); }
    #endif

   inline std::size_t const writes() const { return write_list()->size(); }
   inline bool written() const {return !write_list()->empty();}
   inline std::size_t const reads() const { return reads_; }

   template <typename T> T const * read_ptr(T const * in)
   {
      if (0 == in) return 0;
      return &read(*in);
   }
   template <typename T> T const & r(T const & in) { return read(in); }


   //--------------------------------------------------------------------------
   // attempts to find the written value of T based on
   //--------------------------------------------------------------------------
   template <typename T>
   T* get_written(T const & in)
   {
      if (direct_updating())
      {
         if (in.transaction_thread() == threadId_) return (T*)(&in);
         else return 0;
      }
      else
      {
         WriteContainer::iterator i = writeList().find
            ((base_transaction_object*)(&in));
         if (i == writeList().end()) return 0;
         else return static_cast<T*>(i->second);
      }
   }

    //--------------------------------------------------------------------------
    template <typename T>
    inline bool has_been_read(T const & in)
    {
        #ifndef DISABLE_READ_SETS
        ReadContainer::iterator i = readList().find
            (static_cast<base_transaction_object*>(&in));
        //----------------------------------------------------------------
        // if this object is already in our read list, bail
        //----------------------------------------------------------------
        return i != readList().end();
        #else
        return bloom().exists((std::size_t)&in);
        #endif
    }

   //--------------------------------------------------------------------------
   template <typename T>
   inline T const & read(T const & in)
   {
      if (direct_updating())
      {
#if PERFORMING_VALIDATION
         throw "direct updating not implemented for validation yet";
#else
         return direct_read(in);
#endif
      }
      else
      {
         return deferred_read(in);
      }
   }

   //--------------------------------------------------------------------------
   template <typename T> T* write_ptr(T* in)
   {
      if (0 == in) return 0;
      return &write(*in);
   }
   template <typename T> T& w(T& in) { return write(in); }

   //--------------------------------------------------------------------------
   template <typename T>
   inline T& write(T& in)
   {
      if (direct_updating())
      {
#if PERFORMING_VALIDATION
         throw "direct updating not implemented for validation yet";
#else
         return direct_write(in);
#endif
      }
      else
      {
         return deferred_write(in);
      }
   }

   //--------------------------------------------------------------------------
   template <typename T>
   inline void delete_memory(T &in)
   {
      if (direct_updating())
      {
#if PERFORMING_VALIDATION
         throw "direct updating not implemented for validation yet";
#else
         direct_delete_memory(in);
#endif
      }
      else
      {
         deferred_delete_memory(in);
      }
   }

   template <typename T>
   inline void delete_tx_ptr(T *in) {
       delete_memory(*in);
   }

   template <typename T>
   inline void delete_tx_array(T *in) {
      if (direct_updating())
      {
#if PERFORMING_VALIDATION
         throw "direct updating not implemented for validation yet";
#else
         direct_delete_tx_array(in);
#endif
      }
      else
      {
         deferred_delete_tx_array(in);
      }
   }

   //--------------------------------------------------------------------------
   // allocation of new memory behaves the same for both deferred and direct
   // transaction implementations
   //--------------------------------------------------------------------------

   //--------------------------------------------------------------------------
    void throw_if_forced_to_abort_on_new() {
        if (forced_to_abort()) {
            if (!direct_updating()) {
                deferred_abort(true);
                throw aborted_tx("");
            }
#ifndef DELAY_INVALIDATION_DOOMED_TXS_UNTIL_COMMIT
            cm_abort_on_new(*this);
#endif
        }
    }

   //--------------------------------------------------------------------------
   template <typename T>
   T* as_new(T *newNode)
   {
      newNode->transaction_thread(threadId_);
      newNode->new_memory(1);
      newMemoryList().push_back(detail::make(newNode));

      return newNode;
   }

   //--------------------------------------------------------------------------
   template <typename T>
   T* as_new_array(T *newNode, std::size_t size)
   {
      //newNode->transaction_thread(threadId_);
      //newNode->new_memory(1);
      newMemoryList().push_back(detail::make_array(newNode, size));

      return newNode;
   }

   //--------------------------------------------------------------------------
   template <typename T>
   T* new_shared_memory(T*)
   {
      throw_if_forced_to_abort_on_new();
      make_irrevocable();
      return as_new(new T());
   }

   //--------------------------------------------------------------------------
   template <typename T>
   T* new_memory(T*)
   {
      throw_if_forced_to_abort_on_new();
      return as_new(new T());
   }

   //--------------------------------------------------------------------------
   template <typename T>
   T* new_memory_copy(T const &rhs)
   {
      throw_if_forced_to_abort_on_new();
      return as_new(new T(rhs));
   }

   //--------------------------------------------------------------------------
   void begin();
   bool restart();

   inline bool restart_if_not_inflight()
   {
      if (in_flight()) return true;
      else return restart();
   }

   void end();
   bool commit() {end(); return true;}
   void no_throw_end();

   void force_to_abort()
   {
      // can't abort irrevocable transactions
      if (irrevocable()) return;

      forced_to_abort_ref() = true;

#ifdef PERFORMING_COMPOSITION
#ifndef USING_SHARED_FORCED_TO_ABORT
      // now set all txes of this threadid that are in-flight to force to abort
      for (InflightTxes::iterator j = transactionsInFlight_.begin();
      j != transactionsInFlight_.end(); ++j)
      {
         transaction *t = (transaction*)*j;

         // if this is a parent or child tx, it must abort too
         if (t->threadId_ == this->threadId_) t->forced_to_abort_ref() = true;
      }
#endif
#endif
   }
   inline void unforce_to_abort() { forced_to_abort_ref() = false; }

   //--------------------------------------------------------------------------
   void lock_and_abort();

   inline std::size_t writeListSize() const { return write_list()->size(); }

   inline priority_t const &priority() const { return priority_; }
   inline void set_priority(priority_t const &rhs) const { priority_ = rhs; }
   inline void raise_priority()
   {
      if (priority_ < priority_t(-1))
      {
         ++priority_;
      }
   }

   inline static InflightTxes const & in_flight_transactions() { return transactionsInFlight_; }

   void make_irrevocable();
   void make_isolated();
   bool irrevocable() const;
   bool isolated() const;

   inline thread_id_t const & thread_id() const { return threadId_; }

private:


#ifdef LOGGING_BLOCKS
   static std::string outputBlockedThreadsAndLockedLocks();
#endif
   //--------------------------------------------------------------------------
   //inline int const& hasLock() const { return hasMutex_; }
   void lock_tx();
   void unlock_tx();

   //inline static latm_mutex* latm_lock() { return &latmMutex_; }
   inline static Mutex* latm_lock() { return &latm::instance().latmMutex_; }
   inline static Mutex* general_lock() { return &transactionMutex_; }
   inline static Mutex* inflight_lock() { return &transactionsInFlightMutex_; }

   bool irrevocableTxInFlight();
   bool isolatedTxInFlight();
   void commit_deferred_update_tx();

   bool canAbortAllInFlightTxs();
   bool abortAllInFlightTxs();
   void put_tx_inflight();
   //static bool can_go_inflight();
   static transaction* get_inflight_tx_of_same_thread(bool);

#if !PERFORMING_VALIDATION
   //--------------------------------------------------------------------------
   //                      DIRECT UPDATING SECTION
   //--------------------------------------------------------------------------
   template <typename T>
   T const & direct_read(T const & in)
   {
      if (in.transaction_thread() == threadId_) return in;

      if (forced_to_abort())
      {
#ifndef DELAY_INVALIDATION_DOOMED_TXS_UNTIL_COMMIT
         // let the contention manager decide to throw or not
         cm_abort_on_write(*this, (base_transaction_object&)(in));
#endif
      }

      //--------------------------------------------------------------------
      // otherwise, see if its in our read list
      //--------------------------------------------------------------------
#ifndef DISABLE_READ_SETS
      ReadContainer::iterator i = readList().find((base_transaction_object*)&in);
      if (i != readList().end()) return in;
#endif
#if USE_BLOOM_FILTER
      if (bloom().exists((size_t)&in)) return in;
#endif

      //--------------------------------------------------------------------
      // if we want direct write-read conflict to be done late (commit time)
      // perform the following section of code
      //--------------------------------------------------------------------
      if (directLateWriteReadConflict_)
      {
         //--------------------------------------------------------------------
         // if transaction_thread() is not invalid (and not us), we get original
         // object from the thread that is changing it
         //--------------------------------------------------------------------
         //lock(&transactionMutex_);
         synchro::lock_guard<Mutex> guard_transactionMutex(transactionMutex_);
         //lock_tx();
         synchro::lock_guard<Mutex> lock(*mutex());


         if (in.transaction_thread() != invalid_thread_id())
         {
            synchro::lock_guard<Mutex> guard(mutex(in.transaction_thread()));
            //Mutex& m=mutex(in.transaction_thread());
            //stm::lock(m);

            WriteContainer* c = write_lists(in.transaction_thread());
            WriteContainer::iterator readMem = c->find((base_transaction_object*)&in);
            if (readMem == c->end())
            {
               std::cout << "owner did not contain item in write list" << std::endl;
            }

#ifndef DISABLE_READ_SETS
            readList().insert((base_transaction_object*)readMem->second);
#endif
#if USE_BLOOM_FILTER
            bloom().insert((std::size_t)readMem->second);
#endif
            //unlock_tx();

            ++reads_;
            return *static_cast<T*>(readMem->second);
         }

         // already have locked us above - in both if / else
#ifndef DISABLE_READ_SETS
         readList().insert((base_transaction_object*)&in);
#endif
#if USE_BLOOM_FILTER
         bloom().insert((std::size_t)&in);
#endif
         //unlock_tx();
         ++reads_;
         return in;
      }
      else
      {
         //--------------------------------------------------------------------
         // if we want direct write-read conflict to be done early, bail
         // if someone owns this
         //--------------------------------------------------------------------
         if (in.transaction_thread() != invalid_thread_id())
         {
            // let the contention manager decide to throw or not
            cm_abort_on_write(*this, (base_transaction_object&)(in));
         }

         synchro::lock_guard<Mutex> lock(*mutex());
         //lock_tx();
         // already have locked us above - in both if / else
#ifndef DISABLE_READ_SETS
         readList().insert((base_transaction_object*)&in);
#endif
#if USE_BLOOM_FILTER
         bloom().insert((std::size_t)&in);
#endif
         //unlock_tx();
         ++reads_;
      }
      return in;
   }

   //--------------------------------------------------------------------------
   template <typename T>
   T& direct_write(T& in)
   {
      // if this is our memory (new or mod global) just return
      if (in.transaction_thread() == threadId_) return in;

      if (forced_to_abort())
      {
#ifndef DELAY_INVALIDATION_DOOMED_TXS_UNTIL_COMMIT
         cm_abort_on_write(*this, static_cast<base_transaction_object&>(in));
#endif
      }
      //-----------------------------------------------------------------------
      // first we globally lock all threads before we poke at this global
      // memory - since we need to ensure other threads don't try to
      // manipulate this at the same time we are going to
      //-----------------------------------------------------------------------
      synchro::lock_guard<Mutex> lock_m(transactionMutex_);

      // we currently don't allow write stealing in direct update. if another
      // tx beat us to the memory, we abort
      if (in.transaction_thread() != invalid_thread_id())
      {
         throw aborted_tx("direct writer already exists.");
      }

      in.transaction_thread(threadId_);
      writeList().insert(tx_pair((base_transaction_object*)&in, in.clone(this)));
#if USE_BLOOM_FILTER
      bloom().insert((std::size_t)&in);
#endif
      return in;
   }

   //--------------------------------------------------------------------------
   template <typename T>
   void direct_delete_memory(T &in)
   {
      if (in.transaction_thread() == threadId_)
      {
         deletedMemoryList().push_back(detail::make(in));
         return;
      }

      //-----------------------------------------------------------------------
      // if we're here this item isn't in our writeList - get the global lock
      // and see if anyone else is writing to it. if not, we add the item to
      // our write list and our deletedList
      //-----------------------------------------------------------------------
      synchro::unique_lock<Mutex> lock_m(transactionMutex_);

      if (in.transaction_thread() != invalid_thread_id())
      {
         cm_abort_on_write(*this, (base_transaction_object&)(in));
      }
      else
      {
         in.transaction_thread(threadId_);
         lock_m.unlock();
         // is this really necessary? in the deferred case it is, but in direct it
         // doesn't actually save any time for anything
         //writeList()[(base_transaction_object*)&in] = 0;

         deletedMemoryList().push_back(detail::make(in));
      }
   }

   //--------------------------------------------------------------------------
   template <typename T>
   void direct_delete_tx_array(T *in)
   {
      if (in.transaction_thread() == threadId_)
      {
         deletedMemoryList().push_back(detail::make(in));
         return;
      }

      //-----------------------------------------------------------------------
      // if we're here this item isn't in our writeList - get the global lock
      // and see if anyone else is writing to it. if not, we add the item to
      // our write list and our deletedList
      //-----------------------------------------------------------------------
      synchro::unique_lock<Mutex> lock_m(transactionMutex_);

      if (in.transaction_thread() != invalid_thread_id())
      {
         cm_abort_on_write(*this, (base_transaction_object&)(in));
      }
      else
      {
         in.transaction_thread(threadId_);
         lock_m.unlock();
         // is this really necessary? in the deferred case it is, but in direct it
         // doesn't actually save any time for anything
         //writeList()[(base_transaction_object*)&in] = 0;

         deletedMemoryList().push_back(detail::make(in));
      }
   }
#endif


   //--------------------------------------------------------------------------
   //                      DEFERRED UPDATING SECTION
   //--------------------------------------------------------------------------
   template <typename T>
   T const & deferred_read(T const & in)
   {
      if (forced_to_abort())
      {
         deferred_abort(true);
         throw aborted_tx("");
      }

      //----------------------------------------------------------------
      // always check if the writeList size is 0 first, since if it is
      // it can save construction of an iterator and search setup.
      //----------------------------------------------------------------
#if PERFORMING_WRITE_BLOOM
      if (writeList().empty() ||
         (writeList().size() > 16 &&
         !wbloom().exists((std::size_t)&in))) return insert_and_return_read_memory(in);
#else
      if (writeList().empty()) return insert_and_return_read_memory(in);
#endif

      WriteContainer::iterator i = writeList().find
         ((base_transaction_object*)(&in));
      //----------------------------------------------------------------
      // always check to see if read memory is in write list since it is
      // possible to have already written to memory being read now
      //----------------------------------------------------------------
      if (i == writeList().end()) return insert_and_return_read_memory(in);
      else return *static_cast<T*>(i->second);
   }

public:
   //-------------------------------------------------------------------
   template <typename T>
   T& insert_and_return_read_memory(T& in)
   {
#ifndef DISABLE_READ_SETS
      ReadContainer::iterator i = readList().find
         (static_cast<base_transaction_object*>(&in));
      //----------------------------------------------------------------
      // if this object is already in our read list, bail
      //----------------------------------------------------------------
      if (i != readList().end()) return in;
#else
      if (bloom().exists((std::size_t)&in)) return in;
#endif
      synchro::lock_guard<Mutex> lock(*mutex());
      //lock_tx();
#ifndef DISABLE_READ_SETS
#if PERFORMING_VALIDATION
      readList()[(base_transaction_object*)&in] = in.version_;
#else
      readList().insert((base_transaction_object*)&in);
#endif
#endif
#if USE_BLOOM_FILTER
      bloom().insert((std::size_t)&in);
#endif
      //unlock_tx();
      ++reads_;
      return in;
   }

private:
   template <typename T>
   T& deferred_write(T& in)
   {
      if (forced_to_abort())
      {
         deferred_abort(true);
         throw aborted_tx("");
      }
      //----------------------------------------------------------------
      // if transactionThread_ is not invalid, then already writing to
      // non-global memory - so succeed.
      //----------------------------------------------------------------
      if (in.transaction_thread() != invalid_thread_id()) return in;

      WriteContainer::iterator i = writeList().find
         (static_cast<base_transaction_object*>(&in));
      //----------------------------------------------------------------
      // if !in write set, add. lock first, for version consistency
      //----------------------------------------------------------------
      if (i == writeList().end())
      {
         // get the lock before we make a copy of this object
         synchro::unique_lock<Mutex> lock(*mutex());
#if USE_BLOOM_FILTER
         bloom().insert((std::size_t)&in);
         lock.unlock();
#else

#endif
#if PERFORMING_WRITE_BLOOM
         wbloom().set_bv1(bloom().h1());
         wbloom().set_bv2(bloom().h2());
         //sm_wbv().set_bit((size_t)&in % sm_wbv().size());
#endif
         base_transaction_object* returnValue = in.clone(this);
         returnValue->transaction_thread(threadId_);
         writeList().insert(tx_pair((base_transaction_object*)&in, returnValue));
         return *static_cast<T*>(returnValue);
      }
      else {
          return *static_cast<T*>(i->second);
      }
   }

   //--------------------------------------------------------------------------
   template <typename T>
   void deferred_delete_memory(T &in)
   {
      if (forced_to_abort())
      {
         deferred_abort(true);
         throw aborted_tx("");
      }
      //-----------------------------------------------------------------------
      // if this memory is true memory, not transactional, we add it to our
      // deleted list and we're done
      //-----------------------------------------------------------------------
      if (in.transaction_thread() != invalid_thread_id())
      {
         { synchro::lock_guard<Mutex> lock(*mutex());
         //lock_tx();
         bloom().insert((std::size_t)&in);
         //unlock_tx();
         }
         writeList().insert(tx_pair((base_transaction_object*)&in, 0));
      }
      //-----------------------------------------------------------------------
      // this isn't real memory, it's transactional memory. But the good news is,
      // the real version has to be in our write list somewhere, find it, add
      // both items to the deletion list and exit
      //-----------------------------------------------------------------------
      else
      {
         { synchro::lock_guard<Mutex> lock(*mutex());
         //lock_tx();
         bloom().insert((std::size_t)&in);
         //unlock_tx();
         }
         // check the ENTIRE write container for this piece of memory in the
         // second location. If it's there, it means we made a copy of a piece
         for (WriteContainer::iterator j = writeList().begin(); writeList().end() != j; ++j)
         {
            if (j->second == (base_transaction_object*)&in)
            {
               writeList().insert(tx_pair(j->first, 0));
               deletedMemoryList().push_back(detail::make(j->first));
            }
         }
      }

      deletedMemoryList().push_back(detail::make(in));
   }

   //--------------------------------------------------------------------------
   void verifyReadMemoryIsValidWithGlobalMemory();
   void verifyWrittenMemoryIsValidWithGlobalMemory();

   //--------------------------------------------------------------------------
   inline void abort() throw() { direct_updating() ? direct_abort() : deferred_abort(); }
   inline void deferred_abort(bool const &alreadyRemovedFromInflightList = false) throw();
   inline void direct_abort(bool const &alreadyRemovedFromInflightList = false) throw();

   //--------------------------------------------------------------------------
   void validating_deferred_commit();
   void invalidating_deferred_commit();
   void validating_direct_commit();
   void invalidating_direct_commit();

   //--------------------------------------------------------------------------
   static void lock_all_mutexes_but_this(thread_id_t threadId);
   static void unlock_all_mutexes_but_this(thread_id_t threadId);

   //--------------------------------------------------------------------------
   // side-effect: this unlocks all mutexes including its own. this is a slight
   // optimization over unlock_all_mutexes_but_this() as it doesn't have an
   // additional "if" to slow down performance. however, as it will be
   // releasing its own mutex, it must reset hasMutex_
   //--------------------------------------------------------------------------
   void lock_all_mutexes();
   void unlock_all_mutexes();


#ifndef DISABLE_READ_SETS
   inline bool isReading() const { return !readListRef_.empty(); }
#endif
   inline bool isWriting() const { return !write_list()->empty(); }
   inline bool is_only_reading() const { return !isWriting(); }

   // undefined and hidden - never allow these - bad things would happen
   transaction& operator=(transaction const &);
   transaction(transaction const &);

   bool otherInFlightTransactionsWritingThisMemory(base_transaction_object *obj);
   bool other_in_flight_same_thread_transactions() const throw();
   bool otherInFlightTransactionsOfSameThreadNotIncludingThis(transaction const * const);

   void removeAllSharedValuesOfThread(base_transaction_object *key);
   void copyOtherInFlightComposableTransactionalMemoryOfSameThread();
   bool setAllInFlightComposableTransactionsOfThisThreadToAbort();

   //--------------------------------------------------------------------------
   void forceOtherInFlightTransactionsWritingThisWriteMemoryToAbort();
   void forceOtherInFlightTransactionsReadingThisWriteMemoryToAbort();
   bool forceOtherInFlightTransactionsAccessingThisWriteMemoryToAbort(bool, transaction* &);

   void unlockAllLockedThreads(LockedTransactionContainer &);

   //--------------------------------------------------------------------------
   // direct and deferred transaction method for version / memory management
   //--------------------------------------------------------------------------
   void directCommitTransactionDeletedMemory() throw();
   clock_t earliest_start_time_of_inflight_txes();
   void doIntervalDeletions();

   void deferredCommitTransactionDeletedMemory() throw();
   void directCommitTransactionNewMemory() { deferredCommitTransactionNewMemory(); }
   void deferredCommitTransactionNewMemory();

   void directAbortTransactionDeletedMemory() throw();
   void deferredAbortTransactionDeletedMemory() throw() {
#ifdef BOOST_STM_ALLOWS_DELETERS
        for (MemoryContainerList::iterator i = deletedMemoryList().begin();
            i != deletedMemoryList().end(); ++i)
        {
            delete *i;
        }
#endif
       deletedMemoryList().clear();
    }
   void directAbortTransactionNewMemory() throw() { deferredAbortTransactionNewMemory(); }
   void deferredAbortTransactionNewMemory() throw();

   void directCommitWriteState();
   void deferredCommitWriteState();

#ifndef DISABLE_READ_SETS
   void directCommitReadState() { readList().clear(); }
   void deferredCommitReadState() { readList().clear(); }
#endif

   void directAbortWriteList();
   void deferredAbortWriteList() throw();

#ifndef DISABLE_READ_SETS
   void directAbortReadList() { readList().clear(); }
   void deferredAbortReadList() throw() { readList().clear(); }
#endif

   void validating_direct_end_transaction();
   void invalidating_direct_end_transaction();

   void validating_deferred_end_transaction();
   void invalidating_deferred_end_transaction();

   //--------------------------------------------------------------------------
   //
   // Lock Aware Transactional Memory (LATM) support methods
   //
   //--------------------------------------------------------------------------

   //--------------------------------------------------------------------------
   // deferred updating methods
   //--------------------------------------------------------------------------
   static bool def_do_core_tm_conflicting_lock_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted);
   static bool def_do_core_tx_conflicting_lock_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted, bool txIsIrrevocable);
   static bool def_do_core_full_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted);

   //--------------------------------------------------------------------------
   // direct updating methods
   //--------------------------------------------------------------------------
   static bool dir_do_core_tm_conflicting_lock_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted);
   static bool dir_do_core_tx_conflicting_lock_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted, bool txIsIrrevocable);
   static bool dir_do_core_full_pthread_lock_mutex
      (latm::mutex_type* mutex, int lockWaitTime, int lockAborted);

   static int thread_id_occurance_in_locked_locks_map(thread_id_t threadId);

   static void wait_until_all_locks_are_released();
   static void wait_until_all_locks_are_released_and_set(latm::mutex_type* mutex);

   //--------------------------------------------------------------------------
   // deferred updating locking methods
   //--------------------------------------------------------------------------
   static void def_full_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool def_full_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void def_full_pthread_unlock_mutex(latm::mutex_type* mutex);

   static void def_tm_conflicting_lock_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool def_tm_conflicting_lock_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void def_tm_conflicting_lock_pthread_unlock_mutex(latm::mutex_type* mutex);

   static void def_tx_conflicting_lock_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool def_tx_conflicting_lock_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void def_tx_conflicting_lock_pthread_unlock_mutex(latm::mutex_type* mutex);

   //--------------------------------------------------------------------------
   // direct updating locking methods
   //--------------------------------------------------------------------------
   static void dir_full_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool dir_full_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void dir_full_pthread_unlock_mutex(latm::mutex_type* mutex);

   static void dir_tm_conflicting_lock_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool dir_tm_conflicting_lock_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void dir_tm_conflicting_lock_pthread_unlock_mutex(latm::mutex_type* mutex);

   static void dir_tx_conflicting_lock_pthread_lock_mutex(latm::mutex_type* mutex);
   static bool dir_tx_conflicting_lock_pthread_trylock_mutex(latm::mutex_type* mutex);
   static void dir_tx_conflicting_lock_pthread_unlock_mutex(latm::mutex_type* mutex);

   //--------------------------------------------------------------------------

   //--------------------------------------------------------------------------
   static DeletionBuffer deletionBuffer_;
   static std::ofstream logFile_;

   //static latm::mutex_set tmConflictingLocks_;
   //static latm::mutex_set latmLockedLocks_;
   //static latm::mutex_thread_id_set_map latmLockedLocksAndThreadIdsMap_;
   //static latm::mutex_thread_id_map latmLockedLocksOfThreadMap_;
   //static LatmType eLatmType_;
   static InflightTxes transactionsInFlight_;

   static Mutex deletionBufferMutex_;
   static Mutex transactionMutex_;
   static Mutex transactionsInFlightMutex_;
   //static Mutex latmMutex_;
   //static pthread_mutexattr_t transactionMutexAttribute_;

   static bool initialized_;
   static bool directLateWriteReadConflict_;
   static bool dynamicPriorityAssignment_;
   static bool usingMoveSemantics_;
   static transaction_bookkeeping bookkeeping_;


#ifndef USE_SINGLE_THREAD_CONTEXT_MAP
    static ThreadWriteContainer threadWriteLists_;
    inline static WriteContainer* write_lists(thread_id_t id) {
        ThreadWriteContainer::iterator iter = threadWriteLists_.find(id);
        return iter->second;
    }
   static ThreadReadContainer threadReadLists_;
   static ThreadBloomFilterList threadBloomFilterLists_;
   static ThreadBloomFilterList threadWBloomFilterLists_;
   static ThreadMemoryContainerList threadNewMemoryLists_;
   static ThreadMemoryContainerList threadDeletedMemoryLists_;
   static ThreadTxTypeContainer threadTxTypeLists_;
   static ThreadBoolContainer threadForcedToAbortLists_;
#else
    static tss_context_map_type tss_context_map_;
#ifndef BOOST_STM_HAVE_SINGLE_TSS_CONTEXT_MAP
    inline static WriteContainer* write_lists(thread_id_t thid) {
        tss_context_map_type::iterator iter = tss_context_map_.find(thid);
        return &(iter->second->writeMem);
    }
#else
    inline static WriteContainer* write_lists(thread_id_t thid) {
        tss_context_map_type::iterator iter = tss_context_map_.find(thid);
        return &(iter->second->tx_.writeMem);
    }
#endif
#endif

   //--------------------------------------------------------------------------
   static bool direct_updating_;
   static clock_t global_clock_;
   inline static clock_t& global_clock() {return global_clock_;}

   static size_t stalls_;

   //--------------------------------------------------------------------------
   // must be mutable because in cases where reads collide with other txs
   // modifying the same memory location in-flight, we add that memory
   // location ourselves to the modifiedList for us since performing a read
   // when another in-flight transaction is modifying the same location can
   // cause us to end up reading stale data if the other tx commits with
   // its newly modified data that we were reading.
   //
   // thus, we promote our read to a write and therefore need this map to
   // be mutable - see the read() interface for more documentation
   //--------------------------------------------------------------------------

   //--------------------------------------------------------------------------
   // ******** WARNING ******** MOVING threadId_ WILL BREAK TRANSACTION.
   // threadId_ MUST ALWAYS THE FIRST MEMBER OF THIS CLASS. THE MEMBER
   // INITIALIZATION IS ORDER DEPENDENT UPON threadId_!!
   // ******** WARNING ******** MOVING threadId_ WILL BREAK TRANSACTION
   //--------------------------------------------------------------------------
   thread_id_t threadId_;

   synchro::unique_lock<Mutex> auto_general_lock_;

   //--------------------------------------------------------------------------
   // ******** WARNING ******** MOVING threadId_ WILL BREAK TRANSACTION.
   // threadId_ MUST ALWAYS THE FIRST MEMBER OF THIS CLASS. THE MEMBER
   // INITIALIZATION IS ORDER DEPENDENT UPON threadId_!!
   // ******** WARNING ******** MOVING threadId_ WILL BREAK TRANSACTION
   //--------------------------------------------------------------------------

#ifdef USE_SINGLE_THREAD_CONTEXT_MAP
////////////////////////////////////////
#ifndef BOOST_STM_HAVE_SINGLE_TSS_CONTEXT_MAP
////////////////////////////////////////
    tx_context &context_;

#ifdef BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
    mutable WriteContainer *write_list_ref_;
    inline WriteContainer *write_list() {return write_list_ref_;}
    inline const WriteContainer *write_list() const {return write_list_ref_;}

    mutable bloom_filter *bloomRef_;
#if PERFORMING_WRITE_BLOOM
    mutable bloom_filter *wbloomRef_;
    //mutable bit_vector &sm_wbv_;
#endif

    inline bloom_filter& bloom() { return *bloomRef_; }
#if PERFORMING_WRITE_BLOOM
    inline bloom_filter& wbloom() { return *wbloomRef_; }
    //bit_vector& sm_wbv() { return sm_wbv_; }
#endif
    MemoryContainerList *newMemoryListRef_;
    inline MemoryContainerList& newMemoryList() { return *newMemoryListRef_; }

    MemoryContainerList *deletedMemoryListRef_;
    inline MemoryContainerList& deletedMemoryList() { return *deletedMemoryListRef_; }

    TxType *txTypeRef_;
    inline TxType const tx_type() const { return *txTypeRef_; }
    inline void tx_type(TxType const &rhs) { *txTypeRef_ = rhs; }
    inline TxType&  tx_type_ref() { return *txTypeRef_; }
#else // BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
    inline WriteContainer *write_list() {return &context_.writeMem;}
    inline const WriteContainer *write_list() const {return &context_.writeMem;}

    inline bloom_filter& bloom() { return context_.bloom; }
#if PERFORMING_WRITE_BLOOM
    inline bloom_filter& wbloom() { return context_.wbloom; }
    //bit_vector& sm_wbv() { return sm_wbv_; }
#endif
    inline MemoryContainerList& newMemoryList() { return context_.newMem; }
    inline MemoryContainerList& deletedMemoryList() { return context_.delMem; }
    inline TxType const tx_type() const { return context_.txType; }
    inline void tx_type(TxType const &rhs) { context_.txType = rhs; }
    inline TxType&  tx_type_ref() { return context_.txType; }
#endif

#ifdef USING_SHARED_FORCED_TO_ABORT
#ifdef BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
    int *forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return *forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return *forcedToAbortRef_; }
#else
public:
    inline int const forced_to_abort() const { return context_.abort; }
private:
    inline int& forced_to_abort_ref() { return context_.abort; }
#endif
#else
   int forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return forcedToAbortRef_; }
#endif

    static ThreadMutexContainer threadMutexes_;
    Mutex *mutexRef_;
    inline Mutex * mutex() { return mutexRef_; }
    inline static Mutex& mutex(thread_id_t id) {
        ThreadMutexContainer::iterator i = threadMutexes_.find(id);
        return *(i->second);
    }

   static ThreadBoolContainer threadBlockedLists_;
#if PERFORMING_LATM
   int &blockedRef_;
   inline void block() { blockedRef_ = true; }
   inline void unblock() { blockedRef_ = false; }
   inline int const blocked() const { return blockedRef_; }
   inline static int& blocked(thread_id_t id) { return *threadBlockedLists_.find(id)->second; }
#endif


#if PERFORMING_LATM
    static latm::thread_id_mutex_set_map threadConflictingMutexes_;
    static latm::thread_id_mutex_set_map threadObtainedLocks_;
    static latm::thread_id_mutex_set_map threadCurrentlyLockedLocks_;

#if USING_TRANSACTION_SPECIFIC_LATM
    latm::mutex_set &conflictingMutexRef_;
    inline latm::mutex_set& get_tx_conflicting_locks() { return conflictingMutexRef_; }
    inline latm::mutex_set& get_tx_conflicting_locks(thread_id_t id) {
       return *threadConflictingMutexes_.find(threadId_)->second;
    }
    static void thread_conflicting_mutexes_set_all(int b) {
        for (latm::thread_id_mutex_set_map::iterator iter = threadConflictingMutexes_.begin();
            threadConflictingMutexes_.end() != iter; ++iter)
        {
            blocked(iter->first) = b;
        }
    }

    static void thread_conflicting_mutexes_set_all_cnd(Mutex *mutex, int b) {
        for (latm::thread_id_mutex_set_map::iterator iter = threadConflictingMutexes_.begin();
            threadConflictingMutexes_.end() != iter; ++iter)
        {
        // if this mutex is found in the transaction's conflicting mutexes
        // list, then allow the thread to make forward progress again
        // by turning its "blocked" but only if it does not appear in the
        // locked_locks_thread_id_map
            if (iter->second->find(mutex) != iter->second->end() &&
                0 == thread_id_occurance_in_locked_locks_map(iter->first))
            {
                blocked(iter->first) = false;
            }
        }
   }
#endif

    latm::mutex_set &obtainedLocksRef_;
    inline latm::mutex_set &obtainedLocksRef() {return obtainedLocksRef_;}
    inline static latm::mutex_set &obtainedLocksRef(thread_id_t id) {return *threadObtainedLocks_.find(id)->second;}

    void block_if_conflict_mutex() {
        //--------------------------------------------------------------------------
        // iterate through all currently locked locks
        //--------------------------------------------------------------------------
        for (latm::thread_id_mutex_set_map::iterator i = threadObtainedLocks_.begin();
        threadObtainedLocks_.end() != i; ++i)
        {
            // if these are locks obtained by this thread (in a parent tx), don't block
            if (i->first == this_thread::get_id()) continue;

            for (latm::mutex_set::iterator j = i->second->begin(); j != i->second->end(); ++j)
            {
                //-----------------------------------------------------------------------
                // iterate through this transaction's conflicting mutex ref - if one of
                // the obtained locked locks is in this tx's conflicting mutex set,
                // we need to block this tx
                //-----------------------------------------------------------------------
                if (get_tx_conflicting_locks().find(*j) != get_tx_conflicting_locks().end())
                {
                    this->block(); break;
                }
            }
        }
   }

   latm::mutex_set &currentlyLockedLocksRef_;
   inline latm::mutex_set &currentlyLockedLocksRef() {return currentlyLockedLocksRef_;}
   inline static latm::mutex_set &currentlyLockedLocksRef(thread_id_t id) {return *threadCurrentlyLockedLocks_.find(id)->second;}
#endif


////////////////////////////////////////
#else //BOOST_STM_HAVE_SINGLE_TSS_CONTEXT_MAP
////////////////////////////////////////
    tss_context &context_;

#ifdef BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
    mutable WriteContainer *write_list_ref_;
    inline WriteContainer *write_list() {return write_list_ref_;}
    inline const WriteContainer *write_list() const {return write_list_ref_;}

    mutable bloom_filter *bloomRef_;
#if PERFORMING_WRITE_BLOOM
    mutable bloom_filter *wbloomRef_;
    //mutable bit_vector &sm_wbv_;
#endif

    inline bloom_filter& bloom() { return *bloomRef_; }
#if PERFORMING_WRITE_BLOOM
    inline bloom_filter& wbloom() { return *wbloomRef_; }
    //bit_vector& sm_wbv() { return sm_wbv_; }
#endif
    MemoryContainerList *newMemoryListRef_;
    inline MemoryContainerList& newMemoryList() { return *newMemoryListRef_; }

    MemoryContainerList *deletedMemoryListRef_;
    inline MemoryContainerList& deletedMemoryList() { return *deletedMemoryListRef_; }

    TxType *txTypeRef_;
    inline TxType const tx_type() const { return *txTypeRef_; }
    inline void tx_type(TxType const &rhs) { *txTypeRef_ = rhs; }
    inline TxType&  tx_type_ref() { return *txTypeRef_; }
#else // BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
    inline WriteContainer *write_list() {return &context_.tx_.writeMem;}
    inline const WriteContainer *write_list() const {return &context_.tx_.writeMem;}

    inline bloom_filter& bloom() { return context_.tx_.bloom; }
#if PERFORMING_WRITE_BLOOM
   inline bloom_filter& wbloom() { return context_.tx_.wbloom; }
   //bit_vector& sm_wbv() { return sm_wbv_; }
#endif
   inline MemoryContainerList& newMemoryList() { return context_.tx_.newMem; }
   inline MemoryContainerList& deletedMemoryList() { return context_.tx_.delMem; }
   inline TxType const tx_type() const { return context_.tx_.txType; }
   inline void tx_type(TxType const &rhs) { context_.tx_.txType = rhs; }
   inline TxType&  tx_type_ref() { return context_.tx_.txType; }
#endif

#ifdef USING_SHARED_FORCED_TO_ABORT
#ifdef BOOST_STM_TX_CONTAINS_REFERENCES_TO_TSS_FIELDS
   int *forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return *forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return *forcedToAbortRef_; }
#else
public:
    inline int const forced_to_abort() const { return context_.tx_.abort; }
private:
    inline int& forced_to_abort_ref() { return context_.tx_.abort; }
#endif
#else
   int forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return forcedToAbortRef_; }
#endif

    inline Mutex * mutex() { return &context_.mutex_; }
    inline static Mutex& mutex(thread_id_t id) {
        //tss_context_map_type::iterator i = tss_context_map_.find(id);
        return tss_context_map_.find(id)->second->mutex_;
    }

#if PERFORMING_LATM
   inline void block() { context_.blocked_ = true; }
   inline void unblock() { context_.blocked_ = false; }
   inline int const blocked() const { return context_.blocked_; }
   inline static int& blocked(thread_id_t id)  {
        tss_context_map_type::iterator i = tss_context_map_.find(id);
        return i->second->blocked_;
    }
#endif


#if PERFORMING_LATM

#if USING_TRANSACTION_SPECIFIC_LATM
    inline latm::mutex_set& get_tx_conflicting_locks() { return context_.conflictingMutex_; }
    inline latm::mutex_set& get_tx_conflicting_locks(thread_id_t id) {
        tss_context_map_type::iterator i = tss_context_map_.find(id);
        return i->second->conflictingMutex_;
    }
    static void thread_conflicting_mutexes_set_all(int b) {
        for (tss_context_map_type::iterator iter = tss_context_map_.begin();
            tss_context_map_.end() != iter; ++iter)
        {
            blocked(iter->first) = b;
        }
    }

    static void thread_conflicting_mutexes_set_all_cnd(latm::mutex_type* mutex, int b) {
        for (tss_context_map_type::iterator iter = tss_context_map_.begin();
            tss_context_map_.end() != iter; ++iter)
        {
        // if this mutex is found in the transaction's conflicting mutexes
        // list, then allow the thread to make forward progress again
        // by turning its "blocked" but only if it does not appear in the
        // locked_locks_thread_id_map
            if (iter->second->conflictingMutex_.find(mutex) != iter->second->conflictingMutex_.end() &&
                0 == thread_id_occurance_in_locked_locks_map(iter->first))
            {
                blocked(iter->first) = false;
            }
        }
   }
#endif

    inline latm::mutex_set &obtainedLocksRef() {return context_.obtainedLocks_;}
    inline static latm::mutex_set &obtainedLocksRef(thread_id_t id) {
        tss_context_map_type::iterator i = tss_context_map_.find(id);
        return i->second->obtainedLocks_;
    }

    void block_if_conflict_mutex() {
        //--------------------------------------------------------------------------
        // iterate through all currently locked locks
        //--------------------------------------------------------------------------
        for (tss_context_map_type::iterator i = tss_context_map_.begin();
        tss_context_map_.end() != i; ++i)
        {
            // if these are locks obtained by this thread (in a parent tx), don't block
            if (i->first == this_thread::get_id()) continue;

            for (latm::mutex_set::iterator j = i->second->obtainedLocks_.begin(); j != i->second->obtainedLocks_.end(); ++j)
            {
                //-----------------------------------------------------------------------
                // iterate through this transaction's conflicting mutex ref - if one of
                // the obtained locked locks is in this tx's conflicting mutex set,
                // we need to block this tx
                //-----------------------------------------------------------------------
                if (get_tx_conflicting_locks().find(*j) != get_tx_conflicting_locks().end())
                {
                    this->block(); break;
                }
            }
        }
   }


   inline latm::mutex_set &currentlyLockedLocksRef() {return context_.currentlyLockedLocks_;}
   inline static latm::mutex_set &currentlyLockedLocksRef(thread_id_t id) {
        tss_context_map_type::iterator i = tss_context_map_.find(id);
        return i->second->currentlyLockedLocks_;
    }
#endif

#endif

////////////////////////////////////////
#else   // USE_SINGLE_THREAD_CONTEXT_MAP
////////////////////////////////////////

   mutable WriteContainer *write_list_ref_;
   inline WriteContainer *write_list() {return write_list_ref_;}
   inline const WriteContainer *write_list() const {return write_list_ref_;}
#ifndef DISABLE_READ_SETS
   mutable ReadContainer &readListRef_;
#endif
   mutable bloom_filter *bloomRef_;
#if PERFORMING_WRITE_BLOOM
   mutable bloom_filter *wbloomRef_;
   //mutable bit_vector &sm_wbv_;
#endif

   inline bloom_filter& bloom() { return *bloomRef_; }
#if PERFORMING_WRITE_BLOOM
   inline bloom_filter& wbloom() { return *wbloomRef_; }
   //bit_vector& sm_wbv() { return sm_wbv_; }
#endif
   MemoryContainerList *newMemoryListRef_;
   inline MemoryContainerList& newMemoryList() { return *newMemoryListRef_; }

   MemoryContainerList *deletedMemoryListRef_;
   inline MemoryContainerList& deletedMemoryList() { return *deletedMemoryListRef_; }

   TxType *txTypeRef_;
   inline TxType const tx_type() const { return *txTypeRef_; }
   inline void tx_type(TxType const &rhs) { *txTypeRef_ = rhs; }
   inline TxType&  tx_type_ref() { return *txTypeRef_; }

#ifdef USING_SHARED_FORCED_TO_ABORT
   int *forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return *forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return *forcedToAbortRef_; }
#else
   int forcedToAbortRef_;
public:
    inline int const forced_to_abort() const { return forcedToAbortRef_; }
private:
    inline int& forced_to_abort_ref() { return forcedToAbortRef_; }
#endif

    static ThreadMutexContainer threadMutexes_;
    Mutex *mutexRef_;
    inline Mutex * mutex() { return mutexRef_; }
    inline static Mutex& mutex(thread_id_t id) {
        ThreadMutexContainer::iterator i = threadMutexes_.find(id);
        return *(i->second);
    }

   static ThreadBoolContainer threadBlockedLists_;
#if PERFORMING_LATM
   int &blockedRef_;
   inline void block() { blockedRef_ = true; }
   inline void unblock() { blockedRef_ = false; }
   inline int const blocked() const { return blockedRef_; }
   inline static int& blocked(thread_id_t id) { return *threadBlockedLists_.find(id)->second; }
#endif


#if PERFORMING_LATM
    static latm::thread_id_mutex_set_map threadConflictingMutexes_;
    static latm::thread_id_mutex_set_map threadObtainedLocks_;
    static latm::thread_id_mutex_set_map threadCurrentlyLockedLocks_;

#if USING_TRANSACTION_SPECIFIC_LATM
    latm::mutex_set &conflictingMutexRef_;
    inline latm::mutex_set& get_tx_conflicting_locks() { return conflictingMutexRef_; }
    inline latm::mutex_set& get_tx_conflicting_locks(thread_id_t id) {
       return *threadConflictingMutexes_.find(threadId_)->second;
    }
    static void thread_conflicting_mutexes_set_all(int b) {
        for (latm::thread_id_mutex_set_map::iterator iter = threadConflictingMutexes_.begin();
            threadConflictingMutexes_.end() != iter; ++iter)
        {
            blocked(iter->first) = b;
        }
    }

    static void thread_conflicting_mutexes_set_all_cnd(latm::mutex_type* mutex, int b) {
        for (latm::thread_id_mutex_set_map::iterator iter = threadConflictingMutexes_.begin();
            threadConflictingMutexes_.end() != iter; ++iter)
        {
        // if this mutex is found in the transaction's conflicting mutexes
        // list, then allow the thread to make forward progress again
        // by turning its "blocked" but only if it does not appear in the
        // locked_locks_thread_id_map
            if (iter->second->find(mutex) != iter->second->end() &&
                0 == thread_id_occurance_in_locked_locks_map(iter->first))
            {
                blocked(iter->first) = false;
            }
        }
   }
#endif

    latm::mutex_set &obtainedLocksRef_;
    inline latm::mutex_set &obtainedLocksRef() {return obtainedLocksRef_;}
    inline static latm::mutex_set &obtainedLocksRef(thread_id_t id) {return *threadObtainedLocks_.find(id)->second;}

    void block_if_conflict_mutex() {
        //--------------------------------------------------------------------------
        // iterate through all currently locked locks
        //--------------------------------------------------------------------------
        for (latm::thread_id_mutex_set_map::iterator i = threadObtainedLocks_.begin();
        threadObtainedLocks_.end() != i; ++i)
        {
            // if these are locks obtained by this thread (in a parent tx), don't block
            if (i->first == this_thread::get_id()) continue;

            for (latm::mutex_set::iterator j = i->second->begin(); j != i->second->end(); ++j)
            {
                //-----------------------------------------------------------------------
                // iterate through this transaction's conflicting mutex ref - if one of
                // the obtained locked locks is in this tx's conflicting mutex set,
                // we need to block this tx
                //-----------------------------------------------------------------------
                if (get_tx_conflicting_locks().find(*j) != get_tx_conflicting_locks().end())
                {
                    this->block(); break;
                }
            }
        }
   }



   latm::mutex_set &currentlyLockedLocksRef_;
   inline latm::mutex_set &currentlyLockedLocksRef() {return currentlyLockedLocksRef_;}
   inline static latm::mutex_set &currentlyLockedLocksRef(thread_id_t id) {return *threadCurrentlyLockedLocks_.find(id)->second;}
#endif


////////////////////////////////////////
#endif


    static synchro::implicit_thread_specific_ptr<transaction_tss_storage> transaction_tss_storage_;
    transaction_tss_storage & transaction_tss_storage_ref_;
   public:
    inline TransactionsStack& transactions() {return transaction_tss_storage_ref_.transactions_;}

   // transaction specific data
   //int hasMutex_; // bool - 1 bit
   mutable priority_t priority_;
   transaction_state state_; // 2bits
   std::size_t reads_;
   mutable clock_t startTime_;

   inline transaction_state const & state() const { return state_; }

   inline WriteContainer& writeList() { return *write_list(); }
    #ifndef DISABLE_READ_SETS
   inline ReadContainer& readList() { return readListRef_; }
    #endif

public:
    inline static transaction* current_transaction() {return transaction_tss_storage_->transactions_.top();}

};

inline transaction* current_transaction() {return transaction::current_transaction();}

inline void lock(latm::mutex_type& lock) {transaction::pthread_lock(&lock);}
inline bool try_lock(latm::mutex_type& lock) {return transaction::pthread_trylock(&lock);}
inline void unlock(latm::mutex_type& lock) {transaction::pthread_unlock(&lock);}


template <class T> T* cache_allocate(transaction* t) {
    #if defined(BOOST_STM_CACHE_USE_MEMORY_MANAGER) && defined (USE_STM_MEMORY_MANAGER)
    return  reinterpret_cast<T*>(base_memory_manager::retrieve_mem(sizeof(T)));
    #elif defined(BOOST_STM_CACHE_USE_MALLOC)
    return  reinterpret_cast<T*>(malloc(sizeof(T)));
    #elif defined(BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER)
    return reinterpret_cast<T*>(t->context_.mstorage_.allocate<T>());
    #else
    #error "BOOST_STM_CACHE_USE_MEMORY_MANAGER, BOOST_STM_CACHE_USE_MALLOC or BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER must be defined"
    #endif
}

// this function must be specialized for objects that are non transactional
// by deleting the object

#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {
template <class T>
struct cache_deallocate;

template <class T>
struct cache_deallocate {
    static void apply(T* ptr) {
        if (ptr) {
        #if defined(BOOST_STM_CACHE_USE_MEMORY_MANAGER) && defined (USE_STM_MEMORY_MANAGER)
            base_memory_manager::return_mem(ptr,sizeof(T));
        #elif defined(BOOST_STM_CACHE_USE_MALLOC)
            free(ptr);
        #elif defined(BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER)
        #else
        #error "BOOST_STM_CACHE_USE_MEMORY_MANAGER, BOOST_STM_CACHE_USE_MALLOC or BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER must be defined"
        #endif
        }
    }
};

}

template <class T> void cache_deallocate(T*ptr) {
    partial_specialization_workaround::cache_deallocate<T>::apply(ptr);
}

#else //!BOOST_STM_NO_PARTIAL_SPECIALIZATION

template <class T>
inline void cache_deallocate(T* ptr) {
    if (ptr) {
    #if defined(BOOST_STM_CACHE_USE_MEMORY_MANAGER)  && defined (USE_STM_MEMORY_MANAGER
        base_memory_manager::return_mem(ptr,sizeof(T));
    #elif defined(BOOST_STM_CACHE_USE_MALLOC)
        free(ptr);
    #elif defined(BOOST_STM_CACHE_USE_TSS_MONOTONIC_MEMORY_MANAGER)
    #else
    #error "BOOST_STM_CACHE_USE_MEMORY_MANAGER or BOOST_STM_CACHE_USE_MALLOC must be defined"#endif
    #endif
    }
}
#endif //BOOST_STM_NO_PARTIAL_SPECIALIZATION

inline void cache_release(base_transaction_object* ptr) {
    if (ptr==0) return ;
    ptr->cache_deallocate();
}

#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {
template <class T>
struct cache_clone;

template <class T>
struct cache_clone {
    static inline T* apply(transaction* t, const T& val) {
        T* p = cache_allocate<T>(t);
        if (p==0) {
            throw std::bad_alloc();
        }
        boost::stm::cache_copy(&val, p);
        return p;
    }
};

} // partial_specialization_workaround

template <class T>
inline T* cache_clone(transaction* t, const T& val) {
    return partial_specialization_workaround::cache_clone<T>::apply(t, val);
}
#else //BOOST_STM_NO_PARTIAL_SPECIALIZATION

template <class T>
inline T* cache_clone(transaction* t, const T& val) {
    T* p = cache_allocate<T>(t);
    if (p==0) {
        throw std::bad_alloc();
    }
    cache_copy(&val, p);
    return p;
}
#endif // BOOST_STM_NO_PARTIAL_SPECIALIZATION


template <class T> void cache_copy(const T* const ori, T* target);

#ifdef BOOST_STM_NO_PARTIAL_SPECIALIZATION
namespace partial_specialization_workaround {
template <class T> struct cache_copy;


template <class T>
struct cache_copy {
    static inline void apply(const T* const ori, T* target) {
        memcpy(target, ori, sizeof(T));
    }
};

} // partial_specialization_workaround

template <class T> void cache_copy(const T* const ori, T* target) {
    partial_specialization_workaround::cache_copy<T>::apply(ori, target);
}

#else

template <class T> void cache_copy(const T* const ori, T* target) {
    memcpy(target, ori, sizeof(T));
}
#endif

//-----------------------------------------------------------------------------
// scoped thread initializer calling transaction::initialize_thread() in the
// constructor and transaction::terminate_thread() in the destructor
//-----------------------------------------------------------------------------
struct thread_initializer {
    thread_initializer() {transaction::initialize_thread();}
    ~thread_initializer() {transaction::terminate_thread();}
};


//---------------------------------------------------------------------------
// do not remove if (). It is necessary a necessary fix for compilers
// that do not destroy index variables of for loops. In addition, the
// rand()+1 check is necessarily complex so smart compilers can't
// optimize the if away
//---------------------------------------------------------------------------

#ifdef BOOST_STM_COMPILER_DONT_DESTROY_FOR_VARIABLES
#define use_atomic(T) if (0==rnd()+1) {} else for (boost::stm::transaction T; !T.committed() && T.restart(); T.end())
#define try_atomic(T) if (0==rnd()+1) {} else for (boost::stm::transaction T; !T.committed() && T.restart(); T.no_throw_end()) try
#define atomic(T)     if (0==rnd()+1) {} else for (boost::stm::transaction T; !T.committed() && T.check_throw_before_restart() && T.restart_if_not_inflight(); T.no_throw_end()) try
#else
#define use_atomic(T) for (boost::stm::transaction T; !T.committed() && T.restart(); T.end())
#define try_atomic(T) for (boost::stm::transaction T; !T.committed() && T.restart(); T.no_throw_end()) try
#define atomic(T)     for (boost::stm::transaction T; !T.committed() && T.check_throw_before_restart() && T.restart_if_not_inflight(); T.no_throw_end()) try
#endif


#define catch_before_retry(E) catch (boost::stm::aborted_tx &E)
#define before_retry catch (boost::stm::aborted_tx &)
#define end_atom catch (boost::stm::aborted_tx &) {}

#define BOOST_STM_NEW(T, P) \
    ((T).throw_if_forced_to_abort_on_new(), \
    (T).as_new(new P))

#define BOOST_STM_NEW_1(P) \
    ((boost::stm::current_transaction()!=0)?BOOST_STM_NEW(*boost::stm::current_transaction(), P):new P)

} // stm  namespace
} // boost namespace

#include <boost/stm/detail/transaction_impl.hpp>
#include <boost/stm/detail/latm_general_impl.hpp>
//#include <boost/stm/synch/auto_lock.hpp>
//#include <boost/stm/tx_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
#endif // BOOST_STM_TRANSACTION__HPP


