/* Copyright (C) 2012 Étienne Dupuis
* 
* Use, modification and distribution is subject to the 
* Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
*/

// Test of bug #6561 (https://svn.boost.org/trac/boost/ticket/6561)

#include <boost/pool/pool.hpp>
#include <boost/pool/static_pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>

struct dummy
{ 
  int x; ~dummy() { x = 0; }
};

int main() 
{
  boost::pool<> p(1, 1);
  p.free(NULL);
  p.free(NULL, 4);
  p.ordered_free(NULL);
  p.ordered_free(NULL, 4);
  
  boost::static_pool<> sp(1, 1);
  sp.free(NULL);
  sp.free(NULL, 4);
  sp.ordered_free(NULL);
  sp.ordered_free(NULL, 4);
  
  boost::object_pool<dummy> op(1);
  op.destroy(NULL);
  op.free(NULL);
  
  return 0;
}
