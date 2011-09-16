//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <list>

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_STD_ALLOCATOR)

//[example__container_gen__list_with_allocator_selector
template <class Allocator>
struct list_with_allocatorS { };

namespace boost {
  template <typename Alloc, typename ValueType>
  struct container_gen<list_with_allocatorS<Alloc>,ValueType> {
    typedef typename Alloc::template rebind<ValueType>::other Allocator;
    typedef std::list<ValueType, Allocator> type;
  };
}

// now you can define a graph using std::list and a specific allocator  
typedef boost::adjacency_list< list_with_allocatorS< std::allocator<int> >,
  boost::vecS, boost::directedS> MyGraph;
//]

int main(int, char*[])
{
  MyGraph g(5);
  
  return 0;
}

#else

int main(int, char*[])
{
  return 0;
}

#endif
