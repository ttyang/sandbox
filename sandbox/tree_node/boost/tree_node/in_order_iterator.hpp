// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_IN_ORDER_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_IN_ORDER_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <boost/config.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/tree_node/traversal_state.hpp>

//[reference__in_order_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    class in_order_iterator
    {
     public:
        typedef NodePointer                       value_type;
        typedef value_type const&                 reference;
        typedef value_type const*                 pointer;
        typedef ::std::ptrdiff_t                  difference_type;
        typedef ::std::bidirectional_iterator_tag iterator_category;

        //<-
     private:
#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

        value_type      _current;
        value_type      _root_parent;
        traversal_state _state;

     public:
        //->
        in_order_iterator();

        in_order_iterator(NodePointer const& node, bool start_left = true);

        template <typename NP>
        in_order_iterator(
            in_order_iterator<NP> const& other
//<-
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                ::std::tr1::is_convertible<NP,NodePointer>
              , enabler
            >::type = enabler()
#endif
//->
        );

        reference operator*() const;

        pointer operator->() const;

        in_order_iterator& operator++();

        in_order_iterator operator++(int);

        in_order_iterator& operator--();

        in_order_iterator operator--(int);

        operator traversal_state() const;

        //<-
     private:
        template <typename NP1, typename NP2>
        friend bool
            operator==(
                in_order_iterator<NP1> const& lhs
              , in_order_iterator<NP2> const& rhs
            );
        //->
    };

    //<-
    template <typename NP>
    in_order_iterator<NP>::in_order_iterator()
      : _current(), _root_parent(), _state(no_traversal)
    {
    }

    template <typename NP>
    in_order_iterator<NP>::in_order_iterator(NP const& node, bool start_left)
      : _current(node)
      , _root_parent(node ? node->get_parent() : 0)
      , _state(node ? in_order_traversal : no_traversal)
    {
        if (node)
        {
            if (start_left)
            {
                while (_current->get_left_child())
                {
                    _current = _current->get_left_child();
                }
            }
            else
            {
                while (_current->get_right_child())
                {
                    _current = _current->get_right_child();
                }
            }
        }
    }

    template <typename NP1>
    template <typename NP2>
    in_order_iterator<NP1>::in_order_iterator(
        in_order_iterator<NP2> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<NP2,NP1>
          , enabler
        >::type
#endif
    ) : _current(other._current)
      , _root_parent(other._root_parent)
      , _state(other._state)
    {
    }

    template <typename NP>
    inline typename in_order_iterator<NP>::reference
        in_order_iterator<NP>::operator*() const
    {
        return _current;
    }

    template <typename NP>
    inline typename in_order_iterator<NP>::pointer
        in_order_iterator<NP>::operator->() const
    {
        return &_current;
    }

    template <typename NP>
    in_order_iterator<NP>& in_order_iterator<NP>::operator++()
    {
        value_type node = _current->get_right_child();

        if (node)
        {
            while (node->get_left_child())
            {
                node = node->get_left_child();
            }

            _current = node;
            return *this;
        }

        node = _current;

        for (
            value_type next = node->get_parent();
            next != _root_parent;
            next = next->get_parent()
        )
        {
            if (node == next->get_left_child())
            {
                _current = next;
                return *this;
            }

            node = next;
        }

        _current = _root_parent = 0;
        _state = no_traversal;
        return *this;
    }

    template <typename NP>
    inline in_order_iterator<NP> in_order_iterator<NP>::operator++(int)
    {
        in_order_iterator<NP> itr(*this);
        ++(*this);
        return itr;
    }

    template <typename NP>
    inline in_order_iterator<NP>& in_order_iterator<NP>::operator--()
    {
        value_type node = _current->get_left_child();

        if (node)
        {
            while (node->get_right_child())
            {
                node = node->get_right_child();
            }

            _current = node;
            return *this;
        }

        node = _current;

        for (
            value_type next = node->get_parent();
            next != _root_parent;
            next = next->get_parent()
        )
        {
            if (node == next->get_right_child())
            {
                _current = next;
                return *this;
            }

            node = next;
        }

        _current = _root_parent = 0;
        _state = no_traversal;
        return *this;
    }

    template <typename NP>
    inline in_order_iterator<NP> in_order_iterator<NP>::operator--(int)
    {
        in_order_iterator<NP> itr(*this);
        --(*this);
        return itr;
    }

    template <typename NP>
    inline in_order_iterator<NP>::operator traversal_state() const
    {
        return _state;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename NP1, typename NP2>
    bool
        operator==(
            in_order_iterator<NP1> const& lhs
          , in_order_iterator<NP2> const& rhs
        );

    //<-
    template <typename NP1, typename NP2>
    inline bool
        operator==(
            in_order_iterator<NP1> const& lhs
          , in_order_iterator<NP2> const& rhs
        )
    {
        if (lhs._state == rhs._state)
        {
            return lhs._state ? (lhs._current == rhs._current) : !rhs._state;
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

    template <typename NP1, typename NP2>
    bool
        operator!=(
            in_order_iterator<NP1> const& lhs
          , in_order_iterator<NP2> const& rhs
        );

    //<-
    template <typename NP1, typename NP2>
    inline bool
        operator!=(
            in_order_iterator<NP1> const& lhs
          , in_order_iterator<NP2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_forward_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    in_order_iterator<NodePointer>
        make_in_order_forward_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline in_order_iterator<NodePointer>
        make_in_order_forward_iterator(NodePointer const& node)
    {
        return in_order_iterator<NodePointer>(node, true);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_reverse_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    in_order_iterator<NodePointer>
        make_in_order_reverse_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline in_order_iterator<NodePointer>
        make_in_order_reverse_iterator(NodePointer const& node)
    {
        return in_order_iterator<NodePointer>(node, false);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterate_forward
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void
        in_order_iterate_forward(
            NodePointer const& node
          , UnaryFunction function
        );

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void
        in_order_iterate_forward(
            NodePointer const& node
          , UnaryFunction function
        )
    {
        for (in_order_iterator<NodePointer> itr(node, true); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__in_order_iterate_reverse
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void
        in_order_iterate_reverse(
            NodePointer const& node
          , UnaryFunction function
        );

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void
        in_order_iterate_reverse(
            NodePointer const& node
          , UnaryFunction function
        )
    {
        for (in_order_iterator<NodePointer> itr(node, false); itr; --itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_IN_ORDER_ITERATOR_HPP_INCLUDED

