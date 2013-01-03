// StaticVector Interprocess example

// Copyright (c) 2012 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/container/static_vector.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <string>
#include <cstdlib> //std::system

template <typename V, typename SegmentManager>
struct interprocess_strategy /*interprocess_fake_allocator*/
    : public boost::interprocess::allocator<V, SegmentManager>
{
    static void allocate_failed()
    {
        boost::container::static_vector_detail::default_strategy<V>::allocate_failed();
    }
};

using namespace boost::interprocess;
using namespace boost::container;

typedef interprocess_strategy<int, managed_shared_memory::segment_manager>  ShmemStrategy;

typedef static_vector<int, 100, ShmemStrategy> MyVector;

//For parent process argc == 1, for child process argc > 1
int main(int argc, char *argv[])
{
   //Parent process
   if ( argc == 1 )
   {
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove("MySharedMemory"); }
         ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
      } remover;

      managed_shared_memory segment(create_only, "MySharedMemory", 65536);

      std::cout << "Parent: Constructing container\n";

      MyVector *myvector = segment.construct<MyVector>("MyVector")();

      std::cout << "Parent: Filling container\n";

      for ( int i = 0 ; i < 100 ; ++i )
         myvector->push_back(i);

      std::cout << "Parent: Displaying elements...\n";
      for ( int i = 0 ; i < 100 ; ++i )
         std::cout << myvector->at(i) << ' ';
      std::cout << "\n";

      std::cout << "Parent: Running child process\n";

      std::string s(argv[0]); s += " child ";
      if ( 0 != std::system(s.c_str()) )
         return 1;

      if ( segment.find<MyVector>("MyVector").first )
         return 1;

      std::cout << "Parent: Container was properly destroyed by the child process\n";
   }
   //Child process
   else
   {
      managed_shared_memory segment(open_only, "MySharedMemory");

      std::cout << "Child: Searching of the container in shared memory\n";

      MyVector * myvector = segment.find<MyVector>("MyVector").first;

      std::cout << "Child: Sorting elements in descending order\n";

      std::sort(myvector->rbegin(), myvector->rend());

      std::cout << "Child: Displaying elements...\n";
      for ( int i = 0 ; i < 100 ; ++i )
         std::cout << myvector->at(i) << ' ';
      std::cout << "\n";

      std::cout << "Child: Destroying vector\n";

      segment.destroy<MyVector>("MyVector");
   }

   return 0;
};
