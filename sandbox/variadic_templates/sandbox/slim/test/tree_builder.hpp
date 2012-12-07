#ifndef TREE_BUILDER_HPP_INCLUDED
#define TREE_BUILDER_HPP_INCLUDED
//OriginalSource:
//  2012-10-25.1521 CST
//    Copied code from unrolled_tuple.cpp from:
//      https://github.com/ericniebler/home/tree/master/src/tuple
//
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2012 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifdef TREE_BUILDER_TRACE
#include <boost/utility/trace_scope.hpp>
#endif
#include "./make_tuple.hpp"
#include <boost/preprocessor/repetition/enum.hpp>

#ifndef TUPLE_SIZE
#define TUPLE_SIZE 2
#endif

#ifndef TREE_DEPTH
#define TREE_DEPTH 2
#endif

  template
  < int Depth//tree depth
  , int Index//index of tuple element (used in get<Index>(tuple))
  >
struct node_tag
  /**@brief
   *  A 'tag' to put into tree node showing at what
   *  depth it's located in the tree, and what child
   *  the node is in it's parent's node.
   */
{
};
#ifdef TREE_BUILDER_TRACE
  template<int Depth, int Index>
  std::ostream&
operator<<
  ( std::ostream& a_out
  , node_tag<Depth,Index>const& a_tag
  )
  {
      a_out<<"node_tag<"<<Depth<<", "<<Index<<">";
      return a_out;
  }

#endif
  template
  < int Depth
  , int Index
  , typename Children
  >
  using 
tree_node
  =tuple_bench<node_tag<Depth,Index>,Children>
  ;
  template
  < int Depth
  , int Index
  , typename Children
  >
  tree_node<Depth,Index,Children>
make_node
  ( Children&& t
  )
  {
      return ::make_tuple
        ( node_tag<Depth,Index>()
        , static_cast<Children&&>(t)
        );
  }

template<int Depth>
struct tree_builder
{
    #define M0(Z, Index, D) ::make_node<Depth,Index>(static_cast<T &&>(t))
    #define M1(Z, Index, D) auto BOOST_PP_CAT(tmp, Index) = ::get<Index>(res);

    template<typename T>
    static auto make_tree(T &&t)
      -> decltype(tree_builder<Depth+1>::make_tree(::make_tuple(BOOST_PP_ENUM(TUPLE_SIZE, M0, ~))))
    {
      #ifdef TREE_BUILDER_TRACE
        boost::trace_scope ts(":tree_builder<Depth>::make_tree.");
        std::cout<<":Depth="<<Depth<<"\n";
        std::cout<<":t="<<t<<"\n";
      #endif
        auto res = tree_builder<Depth+1>::make_tree(::make_tuple(BOOST_PP_ENUM(TUPLE_SIZE, M0, ~)));
        // Get each element of the tuple.
        BOOST_PP_REPEAT(TUPLE_SIZE, M1, ~)
        return res;
    }

    #undef M1
    #undef M0
};

template<>
struct tree_builder<TREE_DEPTH>
{
    template<typename T>
    static T make_tree(T &&t)
    {
      #ifdef TREE_BUILDER_TRACE
        boost::trace_scope ts(":tree_builder<TREE_DEPTH>::make_tree.");
        std::cout<<":TREE_DEPTH="<<TREE_DEPTH<<"\n";
        std::cout<<":t==res="<<t<<"\n";
      #endif
        return static_cast<T &&>(t);
    }
};

#endif
