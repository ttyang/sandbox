// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED

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

//[reference__post_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class post_order_iterator
      : public ::boost::iterator_adaptor<
            post_order_iterator<Node>
          , Node*
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef ::boost::iterator_adaptor<
                    post_order_iterator<Node>
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
        std::deque<Node*>                   _stack;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
        post_order_iterator();

        explicit post_order_iterator(Node& node);

        template <typename N>
        post_order_iterator(
            post_order_iterator<N> const& other
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

        template <typename Node1, typename Node2>
        friend bool
            operator==(
                post_order_iterator<Node1> const& lhs
              , post_order_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    post_order_iterator<Node>::post_order_iterator()
      : super_t(), _stack(), _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node>
    post_order_iterator<Node>::post_order_iterator(Node& node)
      : super_t(&node)
      , _stack()
      , _state(::boost::tree_node::post_order_traversal)
    {
        typedef typename ::boost::detail::metafunction::container_iterator<
                    Node
                >::type
                child_iterator;

        child_iterator itr = node.begin(), itr_end = node.end();

        if (itr != itr_end)
        {
            this->_stack.push_back(&node);

            for (::std::deque<child_iterator> pre_order_stack;;)
            {
                while (itr != itr_end)
                {
                    pre_order_stack.push_back(itr);
                    ++itr;
                }

                this->_stack.push_back(
                    &::boost::tree_node::dereference_iterator(
                        pre_order_stack.back()
                    )
                );
                pre_order_stack.pop_back();

                if (pre_order_stack.empty())
                {
                    Node* node_ptr = (
                        this->base_reference() = this->_stack.back()
                    );

                    itr = node_ptr->begin();
                    itr_end = node_ptr->end();

                    if (itr == itr_end)
                    {
                        this->_stack.pop_back();
                        break;
                    }
                }
                else
                {
                    Node* node_ptr = this->_stack.back();

                    itr = node_ptr->begin();
                    itr_end = node_ptr->end();
                }
            }
        }
    }

    template <typename Node>
    template <typename N>
    post_order_iterator<Node>::post_order_iterator(
        post_order_iterator<N> const& other
#if !defined BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _stack(other._stack.begin(), other._stack.end())
      , _state(other._state)
    {
    }

    template <typename Node>
    inline post_order_iterator<Node>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node>
    inline void post_order_iterator<Node>::increment()
    {
        if (this->_stack.empty())
        {
            this->_state = ::boost::tree_node::no_traversal;
        }
        else
        {
            this->base_reference() = this->_stack.back();
            this->_stack.pop_back();
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            post_order_iterator<Node1> const& lhs
          , post_order_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            post_order_iterator<Node1> const& lhs
          , post_order_iterator<Node2> const& rhs
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

//[reference__post_order_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            post_order_iterator<Node1> const& lhs
          , post_order_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            post_order_iterator<Node1> const& lhs
          , post_order_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_post_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    post_order_iterator<Node> make_post_order_iterator(Node& node);

    //<-
    template <typename Node>
    inline post_order_iterator<Node> make_post_order_iterator(Node& node)
    {
        return post_order_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_iterate
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void post_order_iterate(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void post_order_iterate(Node& node, UnaryFunction function)
    {
        for (post_order_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED

