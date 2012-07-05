/* Copyright (C) 2012 Étienne Dupuis
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of ticket #6865 (https://svn.boost.org/trac/boost/ticket/6865)
// Implementation of pool::get_size()

#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>

int main()
{
  // Test pool
  for (int nSize = 1; nSize < 128; nSize = 2 * nSize + 1)
  {
    boost::pool<> p(nSize, 4);
    p.malloc();

    BOOST_ASSERT(p.get_size() == 4);

    for (int k = 0; k < 4; k++)
      p.malloc();

    BOOST_ASSERT(p.get_size() == 4 + 8);

    p.purge_memory();
    BOOST_ASSERT(p.get_size() == 0);

    p.malloc();
    BOOST_ASSERT(p.get_size() == 4);
  }

  // Test object_pool
  boost::object_pool<int> op(32);
  
  op.malloc();
  BOOST_ASSERT(op.get_size() == 32);

  return 0;
}
