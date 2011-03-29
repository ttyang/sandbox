/* Copyright Joaqu�n M L�pez Mu�oz 2003-2004. Use, modification, and distribution
 * are subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/indexed_set for library home page.
 */

#ifndef BOOST_INDEXED_SET_INDEX_PROXY_HPP
#define BOOST_INDEXED_SET_INDEX_PROXY_HPP

#if defined(BOOST_INDEXED_SET_ENABLE_SAFE_MODE)
#include <boost/config.hpp> /* keep it first to prevent some nasty warnings in MSVC */
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC,<1300)
#include <algorithm>
#include <boost/indexed_set/index_iterator_fwd.hpp>
#include <boost/indexed_set/safe_mode.hpp>

namespace boost{

namespace indexed_sets{

namespace detail{

/* In safe mode, index iterators are derived from safe_iterator<Index>,
 * where Index is the type of the index where the iterator belongs. Due
 * to the long symbol names of indices, MSVC++ 6.0 often issues a
 * LNK1179 (duplicate comdat) error. To workaround this problem,
 * index_proxy is used instead. index_proxy<Node> acts as an index
 * over nodes of type Node in all aspects relevant to safe_iterator, and
 * its shorter symbol name makes life easier for MSVC++ 6.0.
 */

template<typename Node>
class index_proxy:public safe_container<index_proxy<Node> >
{
protected:
  index_proxy(Node* header_):header(header_){}

  void swap(index_proxy<Node>& x)
  {
    std::swap(header,x.header);
    safe_container<index_proxy<Node> >::swap(x);
  }

public:
  typedef index_iterator<Node> iterator;
  typedef index_iterator<Node> const_iterator;

  index_iterator<Node> begin()const
  {
    return index_iterator<Node>(Node::begin(header),const_cast<index_proxy*>(this));
  }

  index_iterator<Node> end()const
  {
    return index_iterator<Node>(Node::end(header),const_cast<index_proxy*>(this));
  }

private:
  Node* header;
};

} /* namespace indexed_sets::detail */

} /* namespace indexed_sets */

} /* namespace boost */

#endif /* workaround */

#endif /* BOOST_INDEXED_SET_ENABLE_SAFE_MODE */

#endif