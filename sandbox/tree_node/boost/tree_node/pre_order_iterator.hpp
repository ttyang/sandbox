// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_PRE_ORDER_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_PRE_ORDER_ITERATOR_HPP_INCLUDED

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

//[reference__pre_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class pre_order_iterator
      : public ::boost::iterator_adaptor<
            pre_order_iterator<Node>
          , Node*
          , ::boost::use_default
          , ::boost::forward_traversal_tag
        >
    {
        //<-
        typedef typename ::boost::detail::container_iterator<Node>::type
                child_iterator;
        typedef ::boost::iterator_adaptor<
                    pre_order_iterator<Node>
                  , Node*
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
        ::std::deque<Node*>          _node_stack;
        ::std::deque<child_iterator> _itr_stack;
        child_iterator               _current_itr;
        traversal_state              _state;
        //->

     public:
        pre_order_iterator();

        explicit pre_order_iterator(Node& node);

        template <typename N>
        pre_order_iterator(
            pre_order_iterator<N> const& other
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
                pre_order_iterator<Node1> const& lhs
              , pre_order_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    pre_order_iterator<Node>::pre_order_iterator()
      : super_t()
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _state(no_traversal)
    {
    }

    template <typename Node>
    pre_order_iterator<Node>::pre_order_iterator(Node& node)
      : super_t(&node)
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _state(pre_order_traversal)
    {
        _itr_stack.push_back(node.begin());
    }

    template <typename Node>
    template <typename N>
    pre_order_iterator<Node>::pre_order_iterator(
        pre_order_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _node_stack(other._node_stack.begin(), other._node_stack.end())
      , _itr_stack(other._itr_stack.begin(), other._itr_stack.end())
      , _current_itr(other._current_itr)
      , _state(other._state)
    {
    }

    template <typename Node>
    inline pre_order_iterator<Node>::operator traversal_state() const
    {
        return _state;
    }

    template <typename Node>
    void pre_order_iterator<Node>::increment()
    {
        if (_itr_stack.back() == this->base()->end())
        {
            bool is_post_order = true;

            while (is_post_order)
            {
                _itr_stack.pop_back();

                if (_node_stack.empty())
                {
                    _state = no_traversal;
                    _itr_stack.clear();
                    is_post_order = false;
                }
                else
                {
                    this->base_reference() = _node_stack.back();
                    _node_stack.pop_back();

                    if (++_current_itr == this->base()->end())
                    {
                        child_iterator itr = _itr_stack.back();

                        _itr_stack.pop_back();

                        if (!_itr_stack.empty())
                        {
                            _current_itr = _itr_stack.back();
                        }

                        _itr_stack.push_back(itr);
                    }
                    else
                    {
                        _itr_stack.pop_back();
                        _node_stack.push_back(this->base());
                        _itr_stack.push_back(_current_itr);
                        this->base_reference() = &dereference_iterator(
                            _current_itr
                        );
                        _itr_stack.push_back(this->base()->begin());
                        is_post_order = false;
                    }
                }
            }
        }
        else
        {
            _node_stack.push_back(this->base());
            this->base_reference() = &dereference_iterator(
                _current_itr = _itr_stack.back()
            );
            _itr_stack.push_back(this->base()->begin());
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__pre_order_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            pre_order_iterator<Node1> const& lhs
          , pre_order_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            pre_order_iterator<Node1> const& lhs
          , pre_order_iterator<Node2> const& rhs
        )
    {
        if (lhs._state == rhs._state)
        {
            return lhs._state ? (*lhs == *rhs) : !rhs._state;
        }
        else
        {
            return false;
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__pre_order_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            pre_order_iterator<Node1> const& lhs
          , pre_order_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            pre_order_iterator<Node1> const& lhs
          , pre_order_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_pre_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    pre_order_iterator<Node> make_pre_order_iterator(Node& node);

    //<-
    template <typename Node>
    inline pre_order_iterator<Node> make_pre_order_iterator(Node& node)
    {
        return pre_order_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__pre_order_iterate
namespace boost { namespace tree_node {

    template <typename Node, typename UnaryFunction>
    void pre_order_iterate(Node& node, UnaryFunction function);

    //<-
    template <typename Node, typename UnaryFunction>
    void pre_order_iterate(Node& node, UnaryFunction function)
    {
        for (pre_order_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_PRE_ORDER_ITERATOR_HPP_INCLUDED

