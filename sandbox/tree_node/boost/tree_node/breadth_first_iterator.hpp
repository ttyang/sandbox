// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED

#include <deque>
#include <boost/config.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif

#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>

//[reference__breadth_first_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class breadth_first_iterator
      : public ::boost::iterator_adaptor<
            breadth_first_iterator<Node>
          , Node*
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef ::boost::iterator_adaptor<
                    breadth_first_iterator<Node>
                  , Node*
                  , ::boost::use_default
                  , ::boost::forward_traversal_tag
                >
                super_t;

#if !defined BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:  // Should be private, but conversion ctor won't work.
        ::std::deque<Node*>                 _queue;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
        breadth_first_iterator();

        explicit breadth_first_iterator(Node& node);

        template <typename N>
        breadth_first_iterator(
            breadth_first_iterator<N> const& other
//<-
#if !defined BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<N,Node>
              , enabler
            >::type = enabler()
#endif
//->
        );

        operator ::boost::tree_node::traversal_state() const;

        //<-
#if !BOOST_WORKAROUND(__GNUC__, == 2)
     private:
        friend class ::boost::iterator_core_access;
#endif

        void increment();

     private:
        void _push_children(Node&);

        void _pop();

        template <typename Node1, typename Node2>
        friend bool
            operator==(
                breadth_first_iterator<Node1> const& lhs
              , breadth_first_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator()
      : super_t(), _queue(), _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node>
    breadth_first_iterator<Node>::breadth_first_iterator(Node& node)
      : super_t(&node)
      , _queue()
      , _state(::boost::tree_node::breadth_first_traversal)
    {
    }

    template <typename Node>
    template <typename N>
    breadth_first_iterator<Node>::breadth_first_iterator(
        breadth_first_iterator<N> const& other
#if !defined BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _queue(other._queue.begin(), other._queue.end())
      , _state(other._state)
    {
    }

    template <typename Node>
    inline breadth_first_iterator<Node>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node>
    void breadth_first_iterator<Node>::increment()
    {
        typedef typename ::boost::detail::metafunction::container_iterator<
                    Node
                >::type
                child_iterator;

        child_iterator itr_end = this->base()->end();

        for (child_iterator itr = this->base()->begin(); itr != itr_end; ++itr)
        {
            this->_queue.push_back(
                &::boost::tree_node::dereference_iterator(itr)
            );
        }

        if (this->_queue.empty())
        {
            this->_state = ::boost::tree_node::no_traversal;
        }
        else
        {
            this->base_reference() = this->_queue.front();
            this->_queue.pop_front();
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            breadth_first_iterator<Node1> const& lhs
          , breadth_first_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            breadth_first_iterator<Node1> const& lhs
          , breadth_first_iterator<Node2> const& rhs
        )
    {
        if (lhs._state == rhs._state)
        {
            return lhs._state ? (lhs.base() == rhs.base()) : !rhs._state;
        }
        else
        {
            return false;
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            breadth_first_iterator<Node1> const& lhs
          , breadth_first_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            breadth_first_iterator<Node1> const& lhs
          , breadth_first_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_breadth_first_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    breadth_first_iterator<Node> make_breadth_first_iterator(Node& node);

    //<-
    template <typename Node>
    inline breadth_first_iterator<Node> make_breadth_first_iterator(Node& node)
    {
        return breadth_first_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterate
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void breadth_first_iterate(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void breadth_first_iterate(Node& node, UnaryFunction function)
    {
        for (breadth_first_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED

