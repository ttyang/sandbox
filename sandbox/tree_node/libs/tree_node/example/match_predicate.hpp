// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_NODE_EXAMPLE_MATCH_PREDICATE_HPP_INCLUDED
#define LIBS_TREE_NODE_EXAMPLE_MATCH_PREDICATE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/container_gen/is_ptr_selector.hpp>

//[example__match_predicate
template <typename Node, typename Selector>
class example_match_predicate
{
    typename Node::iterator _itr;

 public:
    explicit example_match_predicate(typename Node::iterator itr);

    template <typename P>
    bool operator()(P const& p) const;

 private:
    template <typename P>
    bool _evaluate(P const& p, boost::mpl::true_) const;

    template <typename P>
    bool _evaluate(P const& p, boost::mpl::false_) const;
};

template <typename Node, typename Selector>
example_match_predicate<Node,Selector>::example_match_predicate(
    typename Node::iterator itr
) : _itr(itr)
{
}

template <typename Node, typename Selector>
template <typename P>
inline bool
    example_match_predicate<Node,Selector>::operator()(P const& p) const
{
    return _evaluate(p, boost::is_ptr_selector<Selector>());
}

template <typename Node, typename Selector>
template <typename P>
inline bool
    example_match_predicate<Node,Selector>::_evaluate(
        P const& p
      , boost::mpl::true_
    ) const
{
    return p.second->get_data() == _itr->second->get_data();
}

template <typename Node, typename Selector>
template <typename P>
inline bool
    example_match_predicate<Node,Selector>::_evaluate(
        P const& p
      , boost::mpl::false_
    ) const
{
    return p.second.get_data() == _itr->second.get_data();
}
//]

#endif  // LIBS_TREE_NODE_EXAMPLE_MATCH_PREDICATE_HPP_INCLUDED

