//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/shmem for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <functional>

#include <boost/shmem/named_user_object.hpp>
#include <boost/shmem/named_heap_object.hpp>
#include <boost/shmem/containers/list.hpp>
#include <boost/shmem/allocators/node_allocator.hpp>
#include "printcontainer.hpp"

/******************************************************************************/
/*                                                                            */
/*  This example constructs repeats the same operations with std::list,       */
/*  shmem_list in user provided buffer, and shmem_list in heap memory         */
/*                                                                            */
/******************************************************************************/

using namespace boost::shmem;

//We will work with wide characters for user memory objects
//Alias <integer, 64 element per chunk> node allocator type
typedef node_allocator
   <int, 64, wnamed_user_object::segment_manager> user_node_allocator_t;
typedef node_allocator
   <int, 64, wnamed_heap_object::segment_manager> heap_node_allocator_t;

//Alias list types
typedef list<int, user_node_allocator_t>    MyUserList;
typedef list<int, heap_node_allocator_t>    MyHeapList;
typedef std::list<int>                      MyStdList;

//Function to check if both lists are equal
bool CheckEqual(MyUserList *userlist, MyStdList *stdlist, MyHeapList *heaplist)
{
   return std::equal(userlist->begin(), userlist->end(), stdlist->begin()) &&
          std::equal(heaplist->begin(), heaplist->end(), stdlist->begin());
}

int main ()
{
   //Create the user memory who will store all objects
   const int memsize = 65536;
   static char static_buffer[memsize];

   //Named new capable user mem allocator
   wnamed_user_object user_buffer;

   //Named new capable heap mem allocator
   wnamed_heap_object heap_buffer;

   //Initialize memory
   user_buffer.create(static_buffer, memsize);
   user_buffer.reserve_named_objects(100);
   heap_buffer.create(memsize);
   heap_buffer.reserve_named_objects(100);

   //User memory allocator must be always be initialized
   //since it has no default constructor
   MyUserList *userlist = user_buffer.construct<MyUserList>(L"MyUserList")
                           (user_buffer.get_segment_manager());

   MyHeapList *heaplist = heap_buffer.construct<MyHeapList>(L"MyHeapList")
                           (heap_buffer.get_segment_manager());

   //Alias heap list
   typedef std::list<int>   MyStdList;
   MyStdList *stdlist = new MyStdList;

   int i;
   const int max = 100;
   for(i = 0; i < max; ++i){
      userlist->push_back(i);
      heaplist->push_back(i);
      stdlist->push_back(i);
   }
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->erase(userlist->begin()++);
   heaplist->erase(heaplist->begin()++);
   stdlist->erase(stdlist->begin()++);
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->pop_back();
   heaplist->pop_back();
   stdlist->pop_back();
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->pop_front();
   heaplist->pop_front();
   stdlist->pop_front();
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   std::vector<int> aux_vect;
   #if !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
   aux_vect.assign(50, -1);
   userlist->assign(aux_vect.begin(), aux_vect.end());
   heaplist->assign(aux_vect.begin(), aux_vect.end());
   stdlist->assign(aux_vect.begin(), aux_vect.end());
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;
   #endif

   userlist->sort();
   heaplist->sort();
   stdlist->sort();
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   #if !BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
   aux_vect.assign(50, 0);
   #endif
   userlist->insert(userlist->begin(), aux_vect.begin(), aux_vect.end());
   heaplist->insert(heaplist->begin(), aux_vect.begin(), aux_vect.end());
   stdlist->insert(stdlist->begin(), aux_vect.begin(), aux_vect.end());

   userlist->unique();
   heaplist->unique();
   stdlist->unique();
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->sort(std::greater<int>());
   heaplist->sort(std::greater<int>());
   stdlist->sort(std::greater<int>());
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->resize(userlist->size()/2);
   heaplist->resize(heaplist->size()/2);
   stdlist->resize(stdlist->size()/2);
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   userlist->remove(*userlist->begin());
   heaplist->remove(*heaplist->begin());
   stdlist->remove(*stdlist->begin());
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   for(i = 0; i < max; ++i){
      userlist->push_back(i);
      heaplist->push_back(i);
      stdlist->push_back(i);
   }

   MyUserList otheruserlist(*userlist);
   MyHeapList otherheaplist(*userlist);
   MyStdList otherstdlist(*stdlist);
   userlist->splice(userlist->begin(), otheruserlist);
   heaplist->splice(heaplist->begin(), otherheaplist);
   stdlist->splice(stdlist->begin(), otherstdlist);
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;

   otheruserlist = *userlist;
   otherheaplist = *heaplist;
   otherstdlist = *stdlist;
   userlist->merge(otheruserlist, std::greater<int>());
   heaplist->merge(otherheaplist, std::greater<int>());
   stdlist->merge(otherstdlist, std::greater<int>());
   if(!CheckEqual(userlist, stdlist, heaplist)) return -1;
   
   user_buffer.destroy<MyUserList>(L"MyUserList");
   user_buffer.close();
   delete stdlist;

   //Fill heap buffer until is full
   try{
      while(1){
         heaplist->insert(heaplist->end(), 0);
      }
   }
   catch(boost::shmem::bad_alloc &){}
   
   std::size_t heap_list_size = heaplist->size();

   //Try to grow the buffer



   //Copy heap buffer to another 
   const char *insert_beg = detail::char_ptr_cast(heap_buffer.get_base());
   const char *insert_end = insert_beg + heap_buffer.get_size();
   std::vector<char> grow_copy (insert_beg, insert_end);
   //Destroy old list
   heap_buffer.destroy<MyHeapList>(L"MyHeapList");
   //Resize copy buffer
   grow_copy.resize(memsize*2);
   //Open Shmem machinery in the new buffer
   user_buffer.open(&grow_copy[0], memsize);
   //Expand old Shmem machinery to the new size
   user_buffer.grow(memsize);
   //Get a pointer to the full list
   userlist = user_buffer.find<MyUserList>(L"MyHeapList").first;
   if(!userlist){
      return -1;
   }

   //Fill user buffer until is full
   try{
      while(1){
         userlist->insert(userlist->end(), 0);
      }
   }
   catch(boost::shmem::bad_alloc &){}

   std::size_t user_list_size = userlist->size();  

   if(user_list_size <= heap_list_size){
      return -1;
   }

   user_buffer.destroy_ptr(userlist);

   return 0;
}


