/* Copyright (C) 2012 Étienne Dupuis
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of bug #6867 (https://svn.boost.org/trac/boost/ticket/6867)

#include <boost/pool/object_pool.hpp>

int main()
{
  boost::pool<> p(sizeof(int), 16, 16);
  void *ptr = p.ordered_malloc(32);

  BOOST_ASSERT(!ptr);

  p.set_max_size(4);
  BOOST_ASSERT(p.get_next_size() <= 4);

  return 0;
}
