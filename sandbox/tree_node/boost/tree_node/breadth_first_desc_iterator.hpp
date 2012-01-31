// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_BREADTH_FIRST_DESC_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_BREADTH_FIRST_DESC_ITERATOR_HPP_INCLUDED

#include <deque>
#include <boost/config.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>

//[reference__breadth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class breadth_first_descendant_iterator
      : public ::boost::iterator_adaptor<
            breadth_first_descendant_iterator<Node>
        //, typename Node::iterator or typename Node::const_iterator
            //<-
          , typename ::boost::detail::container_iterator<Node>::type
            //->
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef typename ::boost::detail::container_iterator<Node>::type
                child_iterator;
        typedef ::boost::iterator_adaptor<
                    breadth_first_descendant_iterator<Node>
                  , child_iterator
                  , ::boost::use_default
                  , ::boost::forward_traversal_tag
                >
                super_t;

#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:  // Should be private, but conversion ctor won't work.
        ::std::deque<child_iterator> _queue;
        traversal_state              _state;
        //->

     public:
        breadth_first_descendant_iterator();

        explicit breadth_first_descendant_iterator(Node& node);

        template <typename N>
        breadth_first_descendant_iterator(
            breadth_first_descendant_iterator<N> const& other
//<-
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<N,Node>
              , enabler
            >::type = enabler()
#endif
//->
        );

        operator traversal_state() const;

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
                breadth_first_descendant_iterator<Node1> const& lhs
              , breadth_first_descendant_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename N>
    breadth_first_descendant_iterator<N>::breadth_first_descendant_iterator()
      : super_t(), _queue(), _state(no_traversal)
    {
    }

    template <typename Node>
    breadth_first_descendant_iterator<Node>::breadth_first_descendant_iterator(
        Node& node
    ) : super_t(), _queue(), _state(breadth_first_traversal)
    {
        _push_children(node);
        _pop();
    }

    template <typename Node>
    template <typename N>
    breadth_first_descendant_iterator<Node>::breadth_first_descendant_iterator(
        breadth_first_descendant_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
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
    inline breadth_first_descendant_iterator<Node>::operator
        traversal_state() const
    {
        return _state;
    }

    template <typename Node>
    inline void breadth_first_descendant_iterator<Node>::increment()
    {
        _push_children(dereference_iterator(this->base()));
        _pop();
    }

    template <typename Node>
    void breadth_first_descendant_iterator<Node>::_push_children(Node& node)
    {
        child_iterator itr_end = node.end();

        for (child_iterator itr = node.begin(); itr != itr_end; ++itr)
        {
            _queue.push_back(itr);
        }
    }

    template <typename Node>
    inline void breadth_first_descendant_iterator<Node>::_pop()
    {
        if (_queue.empty())
        {
            _state = no_traversal;
        }
        else
        {
            this->base_reference() = _queue.front();
            _queue.pop_front();
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_descendant_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            breadth_first_descendant_iterator<Node1> const& lhs
          , breadth_first_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            breadth_first_descendant_iterator<Node1> const& lhs
          , breadth_first_descendant_iterator<Node2> const& rhs
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

//[reference__breadth_first_descendant_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            breadth_first_descendant_iterator<Node1> const& lhs
          , breadth_first_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            breadth_first_descendant_iterator<Node1> const& lhs
          , breadth_first_descendant_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_breadth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    breadth_first_descendant_iterator<Node>
        make_breadth_first_descendant_iterator(Node& node);

    //<-
    template <typename Node>
    inline breadth_first_descendant_iterator<Node>
        make_breadth_first_descendant_iterator(Node& node)
    {
        return breadth_first_descendant_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterate_descendants
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void breadth_first_iterate_descendants(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void breadth_first_iterate_descendants(Node& node, UnaryFunction function)
    {
        for (breadth_first_descendant_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_BREADTH_FIRST_DESC_ITERATOR_HPP_INCLUDED

