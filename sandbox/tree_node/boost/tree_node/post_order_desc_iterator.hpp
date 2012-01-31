// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_POST_ORDER_DESC_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_POST_ORDER_DESC_ITERATOR_HPP_INCLUDED

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

//[reference__post_order_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class post_order_descendant_iterator
      : public ::boost::iterator_adaptor<
            post_order_descendant_iterator<Node>
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
                    post_order_descendant_iterator<Node>
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
        std::deque<child_iterator> _stack;
        traversal_state            _state;
        //->

     public:
        post_order_descendant_iterator();

        explicit post_order_descendant_iterator(Node& node);

        template <typename N>
        post_order_descendant_iterator(
            post_order_descendant_iterator<N> const& other
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

        template <typename Node1, typename Node2>
        friend bool
            operator==(
                post_order_descendant_iterator<Node1> const& lhs
              , post_order_descendant_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    post_order_descendant_iterator<Node>::post_order_descendant_iterator()
      : super_t(), _stack(), _state(no_traversal)
    {
    }

    template <typename Node>
    post_order_descendant_iterator<Node>::post_order_descendant_iterator(
        Node& node
    ) : super_t(), _stack(), _state(post_order_traversal)
    {
        child_iterator itr = node.begin();
        child_iterator itr_end = node.end();

        if (itr != itr_end)
        {
            ::std::deque<child_iterator> pre_order_stack;

            for (;;)
            {
                while (itr != itr_end)
                {
                    pre_order_stack.push_back(itr);
                    ++itr;
                }

                _stack.push_back(pre_order_stack.back());
                pre_order_stack.pop_back();

                if (pre_order_stack.empty())
                {
                    Node& n = dereference_iterator(
                        this->base_reference() = _stack.back()
                    );

                    itr = n.begin();
                    itr_end = n.end();

                    if (itr == itr_end)
                    {
                        _stack.pop_back();
                        break;
                    }
                }
                else
                {
                    Node& n = dereference_iterator(_stack.back());

                    itr = n.begin();
                    itr_end = n.end();
                }
            }
        }

        if (_stack.empty())
        {
            _state = no_traversal;
        }
    }

    template <typename Node>
    template <typename N>
    post_order_descendant_iterator<Node>::post_order_descendant_iterator(
        post_order_descendant_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
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
    inline post_order_descendant_iterator<Node>::operator
        traversal_state() const
    {
        return _state;
    }

    template <typename Node>
    inline void post_order_descendant_iterator<Node>::increment()
    {
        if (_stack.empty())
        {
            _state = no_traversal;
        }
        else
        {
            this->base_reference() = _stack.back();
            _stack.pop_back();
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_descendant_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            post_order_descendant_iterator<Node1> const& lhs
          , post_order_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            post_order_descendant_iterator<Node1> const& lhs
          , post_order_descendant_iterator<Node2> const& rhs
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

//[reference__post_order_descendant_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            post_order_descendant_iterator<Node1> const& lhs
          , post_order_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            post_order_descendant_iterator<Node1> const& lhs
          , post_order_descendant_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
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

//[reference__post_order_iterate_descendants
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void post_order_iterate_descendants(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void post_order_iterate_descendants(Node& node, UnaryFunction function)
    {
        for (post_order_descendant_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_POST_ORDER_DESC_ITERATOR_HPP_INCLUDED

