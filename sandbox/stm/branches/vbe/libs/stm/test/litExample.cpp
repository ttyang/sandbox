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

/* The DRACO Research Group (rogue.colorado.edu/draco) */
/*****************************************************************************\
 *
 * Copyright Notices/Identification of Licensor(s) of
 * Original Software in the File
 *
 * Copyright 2000-2006 The Board of Trustees of the University of Colorado
 * Contact: Technology Transfer Office,
 * University of Colorado at Boulder;
 * https://www.cu.edu/techtransfer/
 *
 * All rights reserved by the foregoing, respectively.
 *
 * This is licensed software.  The software license agreement with
 * the University of Colorado specifies the terms and conditions
 * for use and redistribution.
 *
\*****************************************************************************/

#include <iostream>
#include "litExample.h"
#include <boost/stm/transaction.hpp>
#include <boost/stm/synch.hpp>
#include "main.h"

#ifndef BOOST_STM_T_USE_BOOST_MUTEX
typedef boost::stm::exclusive_lock_adapter<pthread_mutex_t> mutex_type;
#else
typedef boost::stm::exclusive_lock_adapter<boost::mutex> mutex_type;
#endif

static mutex_type L2;
static mutex_type L3;
static mutex_type L4;
//static mutex_type L8;

////////////////////////////////////////////////////////////////////////////
using namespace std; using namespace boost::stm;
using namespace boost;

static native_trans<int> *arr1, *arr2, *arr3, *arr4, *arr5, *arr6, *arr7, *arr8;

static bool work1 = false, work2 = false; //,work3 = false;

static int txFactor = 1;
static int lockFactor = 1;

////////////////////////////////////////////////////////////////////////////
static int iterations = 0;


static void inc2()
{
   stm::lock_guard<mutex_type> lk(L2);
   for (int i = 0; i < kMaxArrSize; ++i)
   {
      ++arr2[i].value();
   }
}

static void inc3()
{
   stm::lock_guard<mutex_type> lk(L3);
   for (int i = 0; i < kMaxArrSize; ++i)
   {
      ++arr3[i].value();
   }
}

static void inc4()
{
   stm::lock_guard<mutex_type> lk(L4);
   for (int i = 0; i < kMaxArrSize; ++i)
   {
      ++arr4[i].value();
   }
}


static void do_work1()
{
   if (work1) return;
   work1 = true;

   if (kBalancedWork == gWorkLoadType || kTxIntenseWork == gWorkLoadType)
   {
      for (int iters = 0; iters < txFactor*iterations; ++iters)
      {
         for (transaction t;;t.restart())
           try {
             for (int i = 0; i < kMaxArrSize; ++i)
             {
               ++t.w(arr6[i]).value();
             }
             t.end(); break;
           } catch (aborted_tx&) {}
      }
   }
}

static void do_work2()
{
   if (work2) return;
   work2 = true;

   if (kBalancedWork == gWorkLoadType || kTxIntenseWork == gWorkLoadType)
   {
      for (int iters = 0; iters < txFactor*iterations; ++iters)
      {
         for (transaction t;;t.restart())
           try {
             for (int i = 0; i < kMaxArrSize; ++i)
             {
               ++t.w(arr7[i]).value();
             }
             t.end(); break;
           } catch (aborted_tx&) {}
      }
   }
}

#if 0
static void do_work3()
{
   if (work3) return;
   work3 = true;

   stm::lock_guard<mutex_type> lk(L8);
   for (int i = 0; i < kMaxArrSize; ++i)
   {
      ++arr8[i].value();
   }
}
#endif
static void* tx1(void *threadId)
{
   transaction::initialize_thread();
   int start = *(int*)threadId;

   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < txFactor*10*iterations; ++iters)
   {
      for (transaction t;;t.restart())
        try {
          for (int i = 0; i < kMaxArrSize; ++i)
          {
            ++t.w(arr1[i]).value();
          }
          t.end(); break;
        } catch (aborted_tx&) {}
   }

   if (!work1) { do_work1(); }
   if (!work2) { do_work2(); }

   endTimer = time(0);
   finishThread(start);

   if (*(int*)threadId != kMainThreadId)
   {
      transaction::terminate_thread();
      pthread_exit(threadId);
   }

   return threadId;
}

static void* tx2(void *threadId)
{
   transaction::initialize_thread();
   int start = *(int*)threadId;

   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < txFactor*10*iterations; ++iters)
   {
      for (transaction t;;t.restart())
        try {
          t.lock_conflict(L2);
          inc2();
          t.end(); break;
        } catch (aborted_tx&) {}
   }

   if (!work1) { do_work1(); }
   if (!work2) { do_work2(); }

   endTimer = time(0);
   finishThread(start);

   if (*(int*)threadId != kMainThreadId)
   {
      transaction::terminate_thread();
      pthread_exit(threadId);
   }

   return threadId;
}

static void* tx3(void *threadId)
{
   transaction::initialize_thread();

   int start = *(int*)threadId;

   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < txFactor*10*iterations; ++iters)
   {
      for (transaction t;;t.restart())
        try {

          t.lock_conflict(L3);
          inc3();
          t.end(); break;
        } catch (aborted_tx&) {}
   }

   if (!work1) { do_work1(); }
   if (!work2) { do_work2(); }

   endTimer = time(0);
   finishThread(start);

   if (*(int*)threadId != kMainThreadId)
   {
      transaction::terminate_thread();
      pthread_exit(threadId);
   }

   return threadId;
}

static void* lock1(void *threadId)
{
   transaction::initialize_thread();
   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < lockFactor*1000*iterations; ++iters)
   {
      inc2();
   }

   endTimer = time(0);
   finishThread();

   if (*(int*)threadId != kMainThreadId)
   {
      pthread_exit(threadId);
   }

   return threadId;
}

static void* lock2(void *threadId)
{
   transaction::initialize_thread();
   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < lockFactor*1000*iterations; ++iters)
   {
      inc3();
   }

   endTimer = time(0);
   finishThread();

   if (*(int*)threadId != kMainThreadId)
   {
      pthread_exit(threadId);
   }

   return threadId;
}

static void* lock3(void *threadId)
{
   transaction::initialize_thread();
   idleUntilAllThreadsHaveReached(*(int*)threadId);
   startTimer = time(0);

   for (int iters = 0; iters < lockFactor*2000*iterations; ++iters)
   {
      inc4();
   }

   endTimer = time(0);
   finishThread();

   if (*(int*)threadId != kMainThreadId)
   {
      pthread_exit(threadId);
   }

   return threadId;
}

///////////////////////////////////////////////////////////////////////////////
void TestLitExample()
{
   iterations = kMaxArrIter;

   pthread_t *threads = new pthread_t[kMaxThreads];
   int *threadId = new int[kMaxThreads];

   arr1 = new native_trans<int>[kMaxArrSize];
   arr2 = new native_trans<int>[kMaxArrSize];
   arr3 = new native_trans<int>[kMaxArrSize];
   arr4 = new native_trans<int>[kMaxArrSize];
   arr5 = new native_trans<int>[kMaxArrSize];
   arr6 = new native_trans<int>[kMaxArrSize];
   arr7 = new native_trans<int>[kMaxArrSize];
   arr8 = new native_trans<int>[kMaxArrSize];

   transaction::initialize();
   //transaction::tm_lock_conflict(L2);
   //transaction::tm_lock_conflict(L3);

   if (kTxIntenseWork == gWorkLoadType) txFactor = 5;
   if (kLockIntenseWork == gWorkLoadType) lockFactor = 10;

   //--------------------------------------------------------------------------
   // Reset barrier variables before creating any threads. Otherwise, it is
   // possible for the first thread
   //--------------------------------------------------------------------------
   threadsFinished.value() = 0;
   threadsStarted.value() = 0;
   startTimer = 0;
   endTimer = 0;

   threadId[0] = 0;
   pthread_create(&threads[0], 0, tx1, (void *)&threadId[0]);

   threadId[1] = 1;
   pthread_create(&threads[1], 0, tx2, (void *)&threadId[1]);

   threadId[2] = 2;
   pthread_create(&threads[2], 0, tx3, (void *)&threadId[2]);

   threadId[3] = 3;
   pthread_create(&threads[3], 0, lock1, (void *)&threadId[3]);

   threadId[4] = 4;
   pthread_create(&threads[4], 0, lock2, (void *)&threadId[4]);

   int mainThreadId = kMaxThreads-1;
   lock3((void*)&mainThreadId);

   while (true)
   {
      if (threadsFinished.value() == kMaxThreads) break;
      SLEEP(10);
   }

   if (latm::instance().doing_full_lock_protection()) cout << "full_";
   else if (latm::instance().doing_tm_lock_protection()) cout << "tm_";
   else if (latm::instance().doing_tx_lock_protection()) cout << "tx_";

   cout << "run_time\t" << endTimer - startTimer << endl;
}



