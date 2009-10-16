//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/synchro for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifdef BOOST_STM_LL_USES_NODE
const char* exe_name="***CN***";
#else
#ifdef BOOST_STM_USES_AS_NEW
#ifdef BOOST_STM_USES_PARAM
const char* exe_name="***NV***";
#else
const char* exe_name="***NR***";
#endif
#else
#ifdef BOOST_STM_USES_PARAM
const char* exe_name="***CV***";
#else
const char* exe_name="***CR***";
#endif
#endif
#endif

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

#include <sstream>
#include "testLinkedList.h"

typedef int list_node_type;

LinkedList< list_node_type > *llist = 0;

////////////////////////////////////////////////////////////////////////////
using namespace std; using namespace boost::stm;
using namespace nMain;

///////////////////////////////////////////////////////////////////////////////
static void* TestLinkedListInserts(void *threadId)
{
#ifdef BOOST_STM_LL_USES_NODE
    //list_node<list_node_type> node;
#endif
   transaction::initialize_thread();

   int start = *(int*)threadId;
   //cout << "started " << start <<endl;
   int startingValue = start * kMaxInserts;

   if (kInsertSameValues) startingValue = 0;

   int endingValue = startingValue + kMaxInserts;

   idleUntilAllThreadsHaveReached(*(int*)threadId);

   //cout << "real started " << start <<endl;
   if (kStartingTime == startTimer) startTimer = time(0);

   //--------------------------------------------------------------------------
   // do the transactional inserts. this is the main transactional loop.
   //--------------------------------------------------------------------------

   int i;
   for (i = startingValue; i < endingValue; ++i)
   {
#ifdef BOOST_STM_LL_USES_NODE
      list_node<list_node_type> node(i);
      //node.value() = i;
      llist->insert(node);
#else
      llist->insert(i);
#endif
   }

   if (kDoMove)
   {
      list_node<list_node_type> node1, node2;

      for (int j = startingValue; j < endingValue; ++j)
      {
         node1.value() = j;
         //node2.value() = -j;
         llist->move(node1, node2);

      }

   }

   if (kDoLookup)
   {
      bool allFound = true;

      for (i = startingValue; i < endingValue; ++i)
      {
         if (!llist->lookup(i))
         {
            allFound = false;
            std::cout << "Element not found: " << i << endl;
         }
      }
   }

   if (kDoRemoval)
   {
      for (i = startingValue; i < endingValue; ++i)
      {
#ifdef BOOST_STM_LL_USES_NODE
         list_node<list_node_type> node(i);
         //node.value() = i;
         llist->remove(node);
#else
         llist->remove(i);
#endif
      }
   }

   //--------------------------------------------------------------------------
   // last thread out sets the endTimer
   //--------------------------------------------------------------------------
   endTimer = time(0);
   //finishThread(start);

   //if (*(int*)threadId != kMainThreadId)
   {
      transaction::terminate_thread();
      pthread_exit(threadId);
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
void TestLinkedListWithMultipleThreads()
{
   static std::vector<int> runVector;

   llist = new LinkedList<list_node_type>;
   transaction::initialize();
   transaction::initialize_thread();
   //transaction::do_direct_updating();

#if LOGGING_COMMITS_AND_ABORTS
   transaction::enableLoggingOfAbortAndCommitSetSize();
#endif

   pthread_t *threads = new pthread_t[kMaxThreads];
   int *threadId = new int[kMaxThreads];

   //--------------------------------------------------------------------------
   // Reset barrier variables before creating any threads. Otherwise, it is
   // possible for the first thread
   //--------------------------------------------------------------------------
   threadsFinished.value() = 0;
   threadsStarted.value() = 0;
   startTimer = kStartingTime;
   endTimer = 0;

   for (int j = 0; j < kMaxThreads ; ++j)
   {
      threadId[j] = j;
      pthread_create(&threads[j], 0, TestLinkedListInserts, (void *)&threadId[j]);
   }


   //int mainThreadId = kMaxThreads-1;
   //TestLinkedListInserts((void*)&mainThreadId);
   #if 0
   while (true)
   {
      if (threadsFinished.value() == kMaxThreads) break;
      SLEEP(10);
   }
   #else
   //SLEEP(1);
   for (int j = 0; j < kMaxThreads ; ++j)
   {
   //cout << "joining " << threadId[j] <<endl;
      pthread_join(threads[j], 0);
   }
   #endif

   int totalInserts = llist->walk_size();

   int averageRunTime = endTimer - startTimer;
   if (averageRunTime < 1) averageRunTime = 1;
   runVector.push_back(averageRunTime);

   int totalAverageRunTime = 0;
   for (int i = 0; i < (int)runVector.size(); ++i) totalAverageRunTime += runVector[i];

   totalAverageRunTime /= (int)runVector.size();


#ifdef DELAY_INVALIDATION_DOOMED_TXS_UNTIL_COMMIT
   cout << "DEL_INVAL_";
#endif
   cout << "LL: DSTM_" << transaction::update_policy_string() << "   ";
   cout << "THRD: " << kMaxThreads << "   ";
   cout << "SIZE: " << totalInserts << "   ";
   cout << "TIME: " << averageRunTime << "   " << "AVE: " << totalAverageRunTime;
   cout << " TX_SEC: " << transaction::bookkeeping().commits() / (totalAverageRunTime * runVector.size()) << endl;
   cout << transaction::bookkeeping() << endl;

   if ((kInsertSameValues && totalInserts != kMaxInserts) ||
      (!kInsertSameValues && totalInserts != kMaxInserts * kMaxThreads))
   {
      std::cout << std::endl << std::endl << "###########################################################";
      std::cout << std::endl << "LOST ITEMS IN LINKED LIST - HALTING: " << totalInserts << std::endl;
      std::cout << "###########################################################" << std::endl << std::endl;

      ofstream out("testOutput.txt");
      llist->outputList(out);
      out.close();
   }

#if LOGGING_COMMITS_AND_ABORTS
   std::ostringstream out;
   out << kMaxThreads << "_" << kMaxInserts;
   std::string typeOfRun = "linkedList_" + out.str();
   logCommitsAndAborts(typeOfRun);
#endif

   delete llist;
   delete threads;
   delete threadId;
}
