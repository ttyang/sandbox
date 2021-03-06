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

///////////////////////////////////////////////////////////////////////////////
#ifndef TEST_LINKED_LIST_WITH_LOCKS_H
#define TEST_LINKED_LIST_WITH_LOCKS_H

#include "main.h"
#include <boost/stm.hpp>
//~ #include <boost/stm/synch.hpp>
#include <pthread.h>

#include <fstream>

#ifndef BOOST_STM_T_USE_BOOST_MUTEX
typedef boost::stm::exclusive_lock_adapter<pthread_mutex_t> mutex_type;
#else
typedef boost::stm::exclusive_lock_adapter<boost::mutex> mutex_type;
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
namespace LATM
{

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
class list_node : public boost::stm::transaction_object< list_node<T> >
{
public:

   list_node() : next_(0), value_(0) {}
   explicit list_node(int const &rhs) : next_(0), value_(rhs) {}

   // zero initialization for native types
   void clear() { value_ = T(); next_ = 0; }

   T &value() { return value_; }
   T const &value() const { return value_; }

   list_node *next() { return next_; }
   list_node const *next() const { return next_; }

   void next(list_node const *rhs) { next_ = (list_node*)rhs; }

   void next(list_node const *rhs, boost::stm::transaction &t)
   {
      if (0 == rhs) next_ = 0;
      else next_ = (list_node*)&t.find_original(*rhs);
   }

   void next_for_new_mem(list_node *rhs, boost::stm::transaction &t)
   {
      if (0 == rhs) next_ = 0;
      else next_ = &t.find_original(*rhs);
   }

#if BUILD_MOVE_SEMANTICS
   list_node& operator=(list_node const & rhs)
   {
      value_ = rhs.value_;
      next_ = rhs.next_;
      return *this;
   }

   list_node(list_node &&rhs) : next_(rhs.next_), value_(boost::stm::draco_move(rhs.value_))
   { rhs.next_ = 0; }

   list_node& operator=(list_node&& rhs)
   {
      value_ = boost::stm::draco_move(rhs.value_);
      std::swap(next_, rhs.next_);
      return *this;
   }
#endif


private:

   list_node *next_;
   T value_;
};

////////////////////////////////////////////////////////////////////////////
template <typename T>
class LinkedList
{
public:

   LinkedList()
   {
//#ifndef BOOST_STM_T_USE_BOOST_MUTEX
//      pthread_mutex_init (&list_lock_, 0);
//#endif
      head_.value() = T();
   }

   ~LinkedList() { 
        try {       
       quick_clear(); 
        } catch (...) {
            BOOST_STM_ERROR;
        }   
    }

   mutex_type* get_list_lock() { return &list_lock_; }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool move(list_node<T> const &node1, list_node<T> const &node2)
   {
      using namespace boost::stm;
      bool succeeded1 = true, succeeded2 = true;
      transaction_state state = e_no_state;

      do
      {
         try
         {
            transaction t;
            succeeded1 = internal_remove(node1);
            succeeded2 = internal_insert(node2);
            t.end();
         }
         catch (aborted_transaction_exception&) {}

         if (!succeeded1 || !succeeded2)
         {
            return false; // auto abort of t
         }

      } while (e_committed != state);

      return true;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool insert(list_node<T> const &node)
   {
      using namespace boost::stm;

      transaction t;

      if (eTxConflictingLockLatmProtection == latm::instance().protection())
      {
         t.add_tx_conflicting_lock(&list_lock_);
      }

      for (; ;t.restart())
      {
         try { return internal_insert(node, t); }
         catch (aborted_transaction_exception&) {}
      }
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool lookup(T const &val)
   {
      using namespace boost::stm;

      transaction t;

      if (eTxConflictingLockLatmProtection == latm::instance().protection())
      {
         t.add_tx_conflicting_lock(&list_lock_);
      }

      for (; ; t.restart())
      {
         try { return internal_lookup(val, t); }
         catch (aborted_transaction_exception&) {}
      }
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool lock_insert(list_node<T> const &rhs)
   {
      using namespace boost::stm;
      using namespace boost;
      stm::lock_guard<mutex_type> lk(list_lock_);

      list_node<T> *headP = &head_;

      if (0 != headP->next())
      {
         list_node<T> *prev = headP;
         list_node<T> *cur = headP->next();
         T val = rhs.value();

         while (true)
         {
            if (cur->value() == val)
            {
               return false;
            }
            else if (cur->value() > val || !cur->next()) break;

            prev = cur;

            list_node<T> *curNext = cur->next();

            if (0 == curNext) break;

            cur = curNext;
         }

         list_node<T> *newNode = new list_node<T>(rhs);

         //--------------------------------------------------------------------
         // if cur->next() is null it means our newNode value is greater than
         // cur, so insert ourselves after cur.
         //--------------------------------------------------------------------
         if (0 == cur->next()) cur->next(newNode);
         //--------------------------------------------------------------------
         // otherwise, we are smaller than cur, so insert between prev and cur
         //--------------------------------------------------------------------
         else
         {
            newNode->next(cur);
            prev->next(newNode);
         }
      }
      else
      {
         list_node<T> *newNode = new list_node<T>(rhs);
         head_.next(newNode);
      }

      return true;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool lock_lookup(T const &val)
   {
      using namespace boost::stm;
      using namespace boost;
      stm::lock_guard<mutex_type> lk(list_lock_);

      LATM::list_node<T> *cur = &head_;

      for (; ; cur = cur->next() )
      {
         if (cur->value() == val)
         {
            return true;
         }

         if (0 == cur->next()) break;
      }

      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool remove(list_node<T> const &node)
   {
      using namespace boost::stm;
      //bool succeeded = true;

      for (transaction t; ; t.restart())
      {
         try { return internal_remove(node, t); }
         catch (aborted_transaction_exception&) {}
      }
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   void outputList(std::ofstream &o)
   {
      int i = 0;
      for (list_node<T> *cur = head_.next(); cur != 0; cur = cur->next())
      {
         o << "element [" << i++ << "]: " << cur->value() << std::endl;
      }
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   int walk_size()
   {
      int i = 0;
      for (list_node<T> *cur = head_.next(); cur != 0; cur = cur->next())
      {
         ++i;
      }

      return i;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   void quick_clear()
   {
      for (list_node<T> *cur = head_.next(); cur != 0;)
      {
         list_node<T> *prev = cur;
         cur = cur->next();
         delete prev;
      }

      head_.clear();
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   void clear()
   {
      using namespace boost::stm;
      for (transaction t; ; t.restart())
      {
         try
         {
            for (list_node<T> *cur = t.read(head_).next(); cur != 0;)
            {
               list_node<T> *prev = &t.read(*cur);
               cur = t.read(*cur).next();
               t.delete_memory(*prev);
            }

            t.write(head_).clear();
            t.end();
         }
         catch (aborted_transaction_exception&) {}
      }
   }

private:

   //--------------------------------------------------------------------------
   // find the location to insert the node. if the value already exists, bail
   //--------------------------------------------------------------------------
   bool internal_insert(list_node<T> const &rhs, boost::stm::transaction &t)
   {
      list_node<T> const *headP = &t.read(head_);

      if (0 != headP->next())
      {
         list_node<T> const *prev = headP;
         list_node<T> const *cur = t.read_ptr(headP->next());
         T val = rhs.value();

         while (true)
         {
            if (cur->value() == val) return false;
            else if (cur->value() > val || !cur->next()) break;

            prev = cur;

            list_node<T> const *curNext = t.read_ptr(cur->next());

            if (0 == curNext) break;

            cur = curNext;
         }

         list_node<T> *newNode = t.new_memory_copy(rhs);

         //--------------------------------------------------------------------
         // if cur->next() is null it means our newNode value is greater than
         // cur, so insert ourselves after cur.
         //--------------------------------------------------------------------
         if (0 == cur->next()) t.write_ptr((list_node<T>*)cur)->next_for_new_mem(newNode, t);
         //--------------------------------------------------------------------
         // otherwise, we are smaller than cur, so insert between prev and cur
         //--------------------------------------------------------------------
         else
         {
            newNode->next((list_node<T>*)cur, t);
            t.write_ptr((list_node<T>*)prev)->next_for_new_mem((list_node<T>*)newNode, t);
         }
      }
      else
      {
         list_node<T> *newNode = t.new_memory_copy(rhs);
         t.write(head_).next_for_new_mem(newNode, t);
      }

      t.end();
      return true;
   }

   //--------------------------------------------------------------------------
   // find the location to insert the node. if the value already exists, bail
   //--------------------------------------------------------------------------
   bool internal_lookup(T const &val, boost::stm::transaction &t)
   {
      list_node<T> const *cur = &t.read(head_);

      for (; true ; cur = t.read(*cur).next() )
      {
         list_node<T> const *trueCur = &t.read(*cur);

         if (trueCur->value() == val)
         {
            t.end();
            return true;
         }

         if (0 == trueCur->next()) break;
      }

      return false;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool internal_remove(list_node<T> const &rhs, boost::stm::transaction &t)
   {
      list_node<T> const *prev = &t.read(head_);

      for (list_node<T> const *cur = prev; cur != 0; prev = cur)
      {
         cur = t.read(*cur).next();

         if (0 == cur) break;

         if (cur->value() == rhs.value())
         {
            list_node<T> const *curNext = t.read(*cur).next();
            t.delete_memory(*cur);
            t.write(*(list_node<T>*)prev).next((list_node<T>*)curNext, t);
            t.end();
            return true;
         }
      }

      return false;
   }

   //--------------------------------------------------------------------------
   // find the location to insert the node. if the value already exists, bail
   //--------------------------------------------------------------------------
   bool internal_insert(list_node<T> const &rhs)
   {
      using namespace boost::stm;
      transaction t;

      list_node<T> const *headP = &t.read(head_);

      if (0 != headP->next())
      {
         list_node<T> const *prev = headP;
         list_node<T> const *cur = t.read_ptr(headP->next());
         T val = rhs.value();

         while (true)
         {
            if (cur->value() == val) return false;
            else if (cur->value() > val || !cur->next()) break;

            prev = cur;

            list_node<T> const *curNext = t.read_ptr(cur->next());

            if (0 == curNext) break;

            cur = curNext;
         }

         list_node<T> *newNode = t.new_memory_copy(rhs);

         //--------------------------------------------------------------------
         // if cur->next() is null it means our newNode value is greater than
         // cur, so insert ourselves after cur.
         //--------------------------------------------------------------------
         if (0 == cur->next()) t.write_ptr((list_node<T>*)cur)->next_for_new_mem(newNode, t);
         //--------------------------------------------------------------------
         // otherwise, we are smaller than cur, so insert between prev and cur
         //--------------------------------------------------------------------
         else
         {
            newNode->next((list_node<T>*)cur, t);
            t.write_ptr((list_node<T>*)prev)->next_for_new_mem(newNode, t);
         }
      }
      else
      {
         list_node<T> *newNode = t.new_memory_copy(rhs);
         t.write(head_).next_for_new_mem(newNode, t);
      }

      t.end();
      return true;
   }

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   bool internal_remove(list_node<T> const &rhs)
   {
      using namespace boost::stm;
      transaction t;

      list_node<T> const *prev = &t.read(head_);

      for (list_node<T> const *cur = prev; cur != 0;
           prev = cur, cur = t.read(*cur).next())
      {
         if (cur->value() == rhs.value())
         {
            t.write(*(list_node<T>*)prev).
               next(t.read_ptr(cur)->next(), t);
            t.delete_memory(*cur);
            t.end();
            return true;
         }
      }

      return false;
   }

   list_node<T> head_;
   mutex_type list_lock_;
};

} // LockAwareTransactions

void TestLinkedListWithLocks();

#endif // TEST_LINKED_LIST_H

