// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_POST_ORDER_DESCENDANT_HPP
#define BOOST_TREE_NODE_ITERATOR_POST_ORDER_DESCENDANT_HPP

#include <deque>
#include <boost/config.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#endif

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/iterator/dereference.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>
#include <boost/detail/metafunction/container_reverse_iterator.hpp>

//[reference__post_order_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node, typename IsReverse = ::boost::mpl::false_>
    class post_order_descendant_iterator
      : public ::boost::iterator_adaptor<
            post_order_descendant_iterator<Node,IsReverse>
//<-
#if 0
//->
          , typename ::boost::mpl::eval_if<
                IsReverse
              , ::boost::mpl::if_<
                    ::std::tr1::is_const<Node>
                  , typename Node::const_reverse_iterator
                  , typename Node::reverse_iterator
                >
              , ::boost::mpl::if_<
                    ::std::tr1::is_const<Node>
                  , typename Node::const_iterator
                  , typename Node::iterator
                >
            >::type
            //<-
#endif
          , typename ::boost::mpl::eval_if<
                IsReverse
              , ::boost::detail::metafunction::container_reverse_iterator<Node>
              , ::boost::detail::metafunction::container_iterator<Node>
            >::type
            //->
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef typename ::boost::mpl::eval_if<
                    IsReverse
                  , ::boost::detail::metafunction::container_reverse_iterator<
                        Node
                    >
                  , ::boost::detail::metafunction::container_iterator<Node>
                >::type
                child_iterator;
        typedef ::boost::iterator_adaptor<
                    post_order_descendant_iterator<Node,IsReverse>
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
        ::std::deque<child_iterator>        _stack;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
        post_order_descendant_iterator();

        explicit post_order_descendant_iterator(Node& node);

        template <typename N, typename I>
        post_order_descendant_iterator(
            post_order_descendant_iterator<N,I> const& other
//<-
#if !defined BOOST_NO_SFINAE
//->
          , typename ::boost::enable_if<
                typename ::boost::mpl::if_<
                    ::std::tr1::is_convertible<N,Node>
                  , ::boost::mpl::equal_to<I,IsReverse>
                  , ::boost::mpl::false_
                >::type
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

        template <typename N, typename I>
#if defined BOOST_NO_SFINAE
        bool
#else
        typename ::boost::enable_if<
            ::boost::mpl::equal_to<I,IsReverse>
          , bool
        >::type
#endif
            equal(post_order_descendant_iterator<N,I> const& other) const;

     private:
        void _initialize(Node& node, ::boost::mpl::false_);

        void _initialize(Node& node, ::boost::mpl::true_);
        //->
    };

    //<-
    template <typename Node, typename IsReverse>
    post_order_descendant_iterator<
        Node
      , IsReverse
    >::post_order_descendant_iterator()
      : super_t(), _stack(), _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node, typename IsReverse>
    post_order_descendant_iterator<
        Node
      , IsReverse
    >::post_order_descendant_iterator(Node& node)
      : super_t(), _stack(), _state(::boost::tree_node::post_order_traversal)
    {
        this->_initialize(node, IsReverse());

        if (this->_stack.empty())
        {
            this->_state = ::boost::tree_node::no_traversal;
        }
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    post_order_descendant_iterator<
        Node
      , IsReverse
    >::post_order_descendant_iterator(
        post_order_descendant_iterator<N,I> const& other
#if !defined BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            typename ::boost::mpl::if_<
                ::std::tr1::is_convertible<N,Node>
              , ::boost::mpl::equal_to<I,IsReverse>
              , ::boost::mpl::false_
            >::type
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _stack(other._stack.begin(), other._stack.end())
      , _state(other._state)
    {
    }

    template <typename Node, typename IsReverse>
    inline post_order_descendant_iterator<Node,IsReverse>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node, typename IsReverse>
    inline void post_order_descendant_iterator<Node,IsReverse>::increment()
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

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    inline
#if defined BOOST_NO_SFINAE
    bool
#else
    typename ::boost::enable_if<
        ::boost::mpl::equal_to<I,IsReverse>
      , bool
    >::type
#endif
        post_order_descendant_iterator<Node,IsReverse>::equal(
            post_order_descendant_iterator<N,I> const& other
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

    template <typename Node, typename IsReverse>
    void
        post_order_descendant_iterator<Node,IsReverse>::_initialize(
            Node& node
          , ::boost::mpl::false_
        )
    {
        child_iterator itr = node.begin();
        child_iterator itr_end = node.end();

        if (itr != itr_end)
        {
            for (::std::deque<child_iterator> pre_order_stack;;)
            {
                while (itr != itr_end)
                {
                    pre_order_stack.push_back(itr);
                    ++itr;
                }

                this->_stack.push_back(pre_order_stack.back());
                pre_order_stack.pop_back();

                if (pre_order_stack.empty())
                {
                    Node& n = dereference_iterator(
                        this->base_reference() = this->_stack.back()
                    );

                    itr = n.begin();
                    itr_end = n.end();

                    if (itr == itr_end)
                    {
                        this->_stack.pop_back();
                        break;
                    }
                }
                else
                {
                    Node& n = dereference_iterator(this->_stack.back());

                    itr = n.begin();
                    itr_end = n.end();
                }
            }
        }
    }

    template <typename Node, typename IsReverse>
    void
        post_order_descendant_iterator<Node,IsReverse>::_initialize(
            Node& node
          , ::boost::mpl::true_
        )
    {
        child_iterator itr = node.rbegin();
        child_iterator itr_end = node.rend();

        if (itr != itr_end)
        {
            for (::std::deque<child_iterator> pre_order_stack;;)
            {
                while (itr != itr_end)
                {
                    pre_order_stack.push_back(itr);
                    ++itr;
                }

                this->_stack.push_back(pre_order_stack.back());
                pre_order_stack.pop_back();

                if (pre_order_stack.empty())
                {
                    Node& n = dereference_iterator(
                        this->base_reference() = this->_stack.back()
                    );

                    itr = n.rbegin();
                    itr_end = n.rend();

                    if (itr == itr_end)
                    {
                        this->_stack.pop_back();
                        break;
                    }
                }
                else
                {
                    Node& n = dereference_iterator(this->_stack.back());

                    itr = n.rbegin();
                    itr_end = n.rend();
                }
            }
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_post_order_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    post_order_descendant_iterator<Node>
        make_post_order_descendant_iterator(Node& node);

    //<-
    template <typename Node>
    inline post_order_descendant_iterator<Node>
        make_post_order_descendant_iterator(Node& node)
    {
        return post_order_descendant_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_pre_order_descendant_reverse_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    post_order_descendant_iterator<Node,::boost::mpl::true_>
        make_pre_order_descendant_reverse_iterator(Node& node);

    //<-
    template <typename Node>
    inline post_order_descendant_iterator<Node,::boost::mpl::true_>
        make_pre_order_descendant_reverse_iterator(Node& node)
    {
        return post_order_descendant_iterator<Node,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ITERATOR_POST_ORDER_DESCENDANT_HPP

