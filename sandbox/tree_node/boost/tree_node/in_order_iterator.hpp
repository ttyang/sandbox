// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_IN_ORDER_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_IN_ORDER_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <boost/config.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>

//[reference__in_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class in_order_iterator
      : public ::boost::iterator_adaptor<
            in_order_iterator<Node>
          , Node*
          , ::boost::use_default
          , ::boost::bidirectional_traversal_tag
        >
    {
        //<-
        typedef ::boost::iterator_adaptor<
                    in_order_iterator<Node>
                  , Node*
                  , ::boost::use_default
                  , ::boost::bidirectional_traversal_tag
                >
                super_t;

#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:  // Should be private, but conversion ctor won't work.
        Node* _root_parent_ptr;
        traversal_state _state;
        //->

     public:
        in_order_iterator();

        explicit in_order_iterator(Node& node, bool start_left = true);

        template <typename N>
        in_order_iterator(
            in_order_iterator<N> const& other
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

        void decrement();

        template <typename N1, typename N2>
        friend bool
            operator==(
                in_order_iterator<N1> const& lhs
              , in_order_iterator<N2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    in_order_iterator<Node>::in_order_iterator()
      : super_t(), _root_parent_ptr(), _state(no_traversal)
    {
    }

    template <typename Node>
    in_order_iterator<Node>::in_order_iterator(Node& node, bool start_left)
      : super_t(&node)
      , _root_parent_ptr(node.get_parent_ptr())
      , _state(in_order_traversal)
    {
        if (start_left)
        {
            while (this->base()->get_left_child_ptr())
            {
                this->base_reference() = this->base()->get_left_child_ptr();
            }
        }
        else
        {
            while (this->base()->get_right_child_ptr())
            {
                this->base_reference() = this->base()->get_right_child_ptr();
            }
        }
    }

    template <typename Node>
    template <typename N>
    in_order_iterator<Node>::in_order_iterator(
        in_order_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _root_parent_ptr(other._root_parent_ptr)
      , _state(other._state)
    {
    }

    template <typename Node>
    inline in_order_iterator<Node>::operator traversal_state() const
    {
        return _state;
    }

    template <typename Node>
    void in_order_iterator<Node>::increment()
    {
        Node* node_ptr = this->base()->get_right_child_ptr();

        if (node_ptr)
        {
            while (node_ptr->get_left_child_ptr())
            {
                node_ptr = node_ptr->get_left_child_ptr();
            }

            this->base_reference() = node_ptr;
            return;
        }

        node_ptr = this->base();

        for (
            Node* next_ptr = node_ptr->get_parent_ptr();
            next_ptr != _root_parent_ptr;
            next_ptr = next_ptr->get_parent_ptr()
        )
        {
            if (node_ptr == next_ptr->get_left_child_ptr())
            {
                this->base_reference() = next_ptr;
                return;
            }

            node_ptr = next_ptr;
        }

        this->base_reference() = _root_parent_ptr = 0;
        _state = no_traversal;
    }

    template <typename Node>
    void in_order_iterator<Node>::decrement()
    {
        Node* node_ptr = this->base()->get_left_child_ptr();

        if (node_ptr)
        {
            while (node_ptr->get_right_child_ptr())
            {
                node_ptr = node_ptr->get_right_child_ptr();
            }

            this->base_reference() = node_ptr;
            return;
        }

        node_ptr = this->base();

        for (
            Node* next_ptr = node_ptr->get_parent_ptr();
            next_ptr != _root_parent_ptr;
            next_ptr = next_ptr->get_parent_ptr()
        )
        {
            if (node_ptr == next_ptr->get_right_child_ptr())
            {
                this->base_reference() = next_ptr;
                return;
            }

            node_ptr = next_ptr;
        }

        this->base_reference() = _root_parent_ptr = 0;
        _state = no_traversal;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename N1, typename N2>
    bool
        operator==(
            in_order_iterator<N1> const& lhs
          , in_order_iterator<N2> const& rhs
        );

    //<-
    template <typename N1, typename N2>
    inline bool
        operator==(
            in_order_iterator<N1> const& lhs
          , in_order_iterator<N2> const& rhs
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

//[reference__in_order_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename N1, typename N2>
    bool
        operator!=(
            in_order_iterator<N1> const& lhs
          , in_order_iterator<N2> const& rhs
        );

    //<-
    template <typename N1, typename N2>
    inline bool
        operator!=(
            in_order_iterator<N1> const& lhs
          , in_order_iterator<N2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_forward_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node> make_in_order_forward_iterator(Node& node);

    //<-
    template <typename Node>
    inline in_order_iterator<Node>
        make_in_order_forward_iterator(Node& node)
    {
        return in_order_iterator<Node>(node, true);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_reverse_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node> make_in_order_reverse_iterator(Node& node);

    //<-
    template <typename Node>
    inline in_order_iterator<Node>
        make_in_order_reverse_iterator(Node& node)
    {
        return in_order_iterator<Node>(node, false);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterate_forward
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void in_order_iterate_forward(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void in_order_iterate_forward(Node& node, UnaryFunction function)
    {
        for (in_order_iterator<Node> itr(node, true); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterate_reverse
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void in_order_iterate_reverse(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void in_order_iterate_reverse(Node& node, UnaryFunction function)
    {
        for (in_order_iterator<Node> itr(node, false); itr; --itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_IN_ORDER_ITERATOR_HPP_INCLUDED

