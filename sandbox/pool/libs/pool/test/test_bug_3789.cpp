/* Copyright (C) 2012 Étienne Dupuis
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of ticket #3789 (https://svn.boost.org/trac/boost/ticket/3789)

#define BOOST_DISABLE_THREADS
#include <boost/pool/object_pool.hpp>

class object
{
  public :
    static int instances;

    char padding[31];
    bool initialized;

  public :
    object() { initialized = true; instances += 1; }
    ~object() { assert(initialized); initialized = false; instances -= 1; assert(instances >= 0); }
};

int object::instances;

int main()
{
  object::instances = 0;
  {
#ifndef BOOST_POOL_VALGRIND
    static const int size = 1000000;
#else
    static const int size = 100000;
#endif

    boost::object_pool<object> pool(1);		
  
    object **objects = new object *[size];

    for (int k = 0; k < size; k++)
      objects[k] = pool.construct();

    for (int k = 0; k < size; k += (k % 10) ? 1 : 2)
      pool.destroy(objects[k]);

    assert(object::instances == size / 10);
    delete[] objects;
  }

  assert(object::instances == 0);
  return object::instances;
}
