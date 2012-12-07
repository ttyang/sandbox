//ChangeLog:
//  2012-10-25.1521 CST
//    Copied code from unrolled_tuple.cpp from:
//      https://github.com/ericniebler/home/tree/master/src/tuple
//
///////////////////////////////////////////////////////////////////////////////
// unrolled_tuple.cpp
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "./tree_builder.hpp"

#ifdef TREE_BUILDER_TRACE
#include "print_tuple_bench.hpp"
#endif

#ifndef TREE_LEAF_TYPE
  #define TREE_LEAF_TYPE 0
#endif

#if TREE_LEAF_TYPE == 0  || TUPLE_TEMPLATED_CTOR == 0
  template<unsigned I>
  struct leaf
  {
      leaf(unsigned a_i=I)
      : my_i(a_i)
      {}
      
      unsigned my_i;
  };
  #ifdef TREE_BUILDER_TRACE  
    template<unsigned I>
    std::ostream&
  operator<<
    ( std::ostream& sout
    , leaf<I>const& a_leaf
    )
    {
        sout<<"leaf<"<<I<<">("<<a_leaf.my_i<<")";
        return sout;
    }
  #endif    
    auto
  make_leaf()
    -> decltype(::make_tuple(leaf<100>(),leaf<101>(),leaf<102>()))
    {
        return ::make_tuple(leaf<100>(),leaf<101>(),leaf<102>());
    }
#else
  //This make_leaf produces the "leaf" structure used in the original
  //tree_builder driver(The one mentioned in 2012-10-25.1521 CST
  //ChangeLog above).
  //
  char sz[] = "hello";
      typedef
    decltype(sz)
  tuple_elem1_raw_t
    ;
      typedef
    tuple_elem1_raw_t&
  tuple_elem1_t
    ;
    tuple_bench
    < int
    , tuple_elem1_t
    > 
  x 
    ( 1
    , std::ref(sz)
    )
    ;
    auto
  make_leaf()
    -> decltype(::make_tuple(1, "hello", 3.14, 'a', x))
    {
        return ::make_tuple(1, "hello", 3.14, 'a', x);
    }
#endif

int main()
{
#ifdef TREE_BUILDER_TRACE
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,indent_by);
#endif
    auto y = tree_builder<0>::make_tree(make_leaf());
    return 0;
}

