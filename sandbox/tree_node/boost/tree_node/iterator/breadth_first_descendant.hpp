// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_BREADTH_FIRST_DESCENDANT_HPP
#define BOOST_TREE_NODE_ITERATOR_BREADTH_FIRST_DESCENDANT_HPP

#include <deque>
#include <boost/config.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/tr1/type_traits.hpp>
#endif

#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/iterator/dereference.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>

//[reference__breadth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class breadth_first_descendant_iterator
      : public ::boost::iterator_adaptor<
            breadth_first_descendant_iterator<Node>
//<-
#if 0
//->
          , typename ::boost::mpl::if_<
                ::std::tr1::is_const<Node>
              , typename Node::const_iterator
              , typename Node::iterator
            >::type
            //<-
#endif
          , typename ::boost::detail::metafunction::container_iterator<
                Node
            >::type
            //->
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef typename ::boost::detail::metafunction::container_iterator<
                    Node
                >::type
                child_iterator;
        typedef ::boost::iterator_adaptor<
                    breadth_first_descendant_iterator<Node>
                  , child_iterator
                  , ::boost::use_default
                  , ::boost::forward_traversal_tag
                >
                super_t;

#if !defined BOOST_NO_SFINAE
        //->
        struct enabler
        {
        };
        //<-
#endif

     public:  // Should be private, but conversion ctor won't work.
        ::std::deque<child_iterator>        _queue;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
        breadth_first_descendant_iterator();

        explicit breadth_first_descendant_iterator(Node& node);

        template <typename N>
        breadth_first_descendant_iterator(
            breadth_first_descendant_iterator<N> const& other
//<-
#if !defined BOOST_NO_SFINAE
//->
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<N,Node>
              , enabler
            >::type = enabler()
//<-
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

        template <typename N>
        bool equal(breadth_first_descendant_iterator<N> const& other) const;

     private:
        void _push_children(Node& node);

        void _pop();
        //->
    };

    //<-
    template <typename Node>
    breadth_first_descendant_iterator<
        Node
    >::breadth_first_descendant_iterator()
      : super_t(), _queue(), _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node>
    breadth_first_descendant_iterator<Node>::breadth_first_descendant_iterator(
        Node& node
    ) : super_t()
      , _queue()
      , _state(::boost::tree_node::breadth_first_traversal)
    {
        this->_push_children(node);
        this->_pop();
    }

    template <typename Node>
    template <typename N>
    breadth_first_descendant_iterator<Node>::breadth_first_descendant_iterator(
        breadth_first_descendant_iterator<N> const& other
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
    inline breadth_first_descendant_iterator<Node>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node>
    inline void breadth_first_descendant_iterator<Node>::increment()
    {
        this->_push_children(dereference_iterator(this->base()));
        this->_pop();
    }

    template <typename Node>
    template <typename N>
    inline bool
        breadth_first_descendant_iterator<Node>::equal(
            breadth_first_descendant_iterator<N> const& other
        ) const
    {
        if (this->_state == other._state)
        {
            return this->_state ? (
                this->base() == other.base()
            ) : !other._state;
        }
        else
        {
            return false;
        }
    }

    template <typename Node>
    void breadth_first_descendant_iterator<Node>::_push_children(Node& node)
    {
        child_iterator itr_end = node.end();

        for (child_iterator itr = node.begin(); itr != itr_end; ++itr)
        {
            this->_queue.push_back(itr);
        }
    }

    template <typename Node>
    inline void breadth_first_descendant_iterator<Node>::_pop()
    {
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

#endif  // BOOST_TREE_NODE_ITERATOR_BREADTH_FIRST_DESCENDANT_HPP

