/* Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SET_COPY_MAP_HPP
#define BOOST_INDEXED_SET_COPY_MAP_HPP

#include <boost/config.hpp> /* keep it first to prevent some nasty warnings in MSVC */
#include <algorithm>
#include <boost/indexed_set/auto_space.hpp>
#include <boost/indexed_set/try_catch.hpp>
#include <boost/noncopyable.hpp>
#include <cstddef>
#include <functional>

namespace boost{

namespace indexed_sets{

namespace detail{

/* copy_map is used as an auxiliary structure during copy_() operations.
 * When a container with n nodes is replicated, node_map holds the pairings
 * between original and copied nodes, and provides a fast way to find a
 * copied node from an original one.
 * The semantics of the class are not simple, and no attempt has been made
 * to enforce it: indexed_set handles it right. On the other hand, the const
 * interface, which is the one provided to index implementations, only allows
 * for:
 *   - Enumeration of pairs of (original,copied) nodes (excluding the headers),
 *   - fast retrieval of copied nodes (including the headers.)
 */

template <typename Node>
struct copy_map_entry
{
  copy_map_entry(Node* f,Node* s):first(f),second(s){}

  Node* first;
  Node* second;

  bool operator<(const copy_map_entry<Node>& x)const
  {
    return std::less<Node*>()(first,x.first);
  }
};

template <typename Node,typename Allocator>
class copy_map:private noncopyable
{
public:
  typedef const copy_map_entry<Node>* const_iterator;

  copy_map(const Allocator al,std::size_t size,Node* header_org,Node* header_cpy):
      al_(al),size_(size),spc(al_,size_),n(0),
      header_org_(header_org),header_cpy_(header_cpy),released(false)
  {}

  ~copy_map()
  {
    if(!released){
      for(std::size_t i=0;i<n;++i){
        allocator::destroy(&spc.data()[i].second->value);
        deallocate(spc.data()[i].second);
      }
    }
  }

  const_iterator begin()const{return &spc.data()[0];}
  const_iterator end()const{return &spc.data()[n];}

  void clone(Node* node)
  {
    spc.data()[n].first=node;
    spc.data()[n].second=allocator::allocate<Node>(al_,1);
    BOOST_INDEXED_SET_TRY{
      allocator::construct(&spc.data()[n].second->value,node->value);
    }
    BOOST_INDEXED_SET_CATCH(...){
      deallocate(spc.data()[n].second);
      BOOST_INDEXED_SET_RETHROW;
    }
    ++n;

    if(n==size_)std::sort(&spc.data()[0],&spc.data()[size_]);
  }

  Node* find(Node* node)const
  {
    if(node==header_org_)return header_cpy_;
    return std::lower_bound(
      &spc.data()[0],&spc.data()[n],copy_map_entry<Node>(node,0))->second;
  };

  void release()
  {
    released=true;
  }

private:
  typename allocator::rebind<Allocator,Node>::type al_;
  std::size_t                                      size_;
  auto_space<copy_map_entry<Node>,Allocator>       spc;
  std::size_t                                      n;
  Node*                                            header_org_;
  Node*                                            header_cpy_;
  bool                                             released;

  void deallocate(Node* node)
  {
    allocator::deallocate(al_,node,1);
  }
};

} /* namespace indexed_sets::detail */

} /* namespace indexed_sets */

} /* namespace boost */

#endif
