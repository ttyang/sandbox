   #include <boost/shmem/named_shared_object.hpp>
   #include <boost/shmem/offset_ptr.hpp>

   using namespace boost::shmem;

   //Shared memory linked list node
   struct list_node
   {
      offset_ptr<list_node> next;
      int                   value;
   };

   int main ()
   {
      //Create shared memory
      named_shared_object segment;
      segment.create("/MySharedMemory",//segment name
                     65536);           //segment size in bytes

      //Create linked list with 10 nodes in shared memory
      offset_ptr<list_node> prev = 0, current, first;

      int i;
      for(i = 0; i < 10; ++i, prev = current){
         current = static_cast<list_node*>(segment.allocate(sizeof(list_node)));
         current->value = i;
         current->next  = 0;

         if(!prev)
            first = current;
         else
            prev->next = current;
      }

      //Communicate list to other processes
      //. . .
      //When done, destroy list
      for(current = first; current; /**/){
         prev = current;
         current = current->next;
         segment.deallocate(prev.get());
      }
      return 0;
   }