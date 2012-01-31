// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_DEPTH_FIRST_DESC_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_DEPTH_FIRST_DESC_ITERATOR_HPP_INCLUDED

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

//[reference__depth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    class depth_first_descendant_iterator
      : public ::boost::iterator_adaptor<
            depth_first_descendant_iterator<Node>
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
                    depth_first_descendant_iterator<Node>
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
        ::std::deque<Node*>          _node_stack;
        ::std::deque<child_iterator> _itr_stack;
        Node*                        _node_ptr;
        traversal_state              _state;
        //->

     public:
        depth_first_descendant_iterator();

        explicit depth_first_descendant_iterator(Node& node);

        template <typename N>
        depth_first_descendant_iterator(
            depth_first_descendant_iterator<N> const& other
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
                depth_first_descendant_iterator<Node1> const& lhs
              , depth_first_descendant_iterator<Node2> const& rhs
            );
        //->
    };

    //<-
    template <typename Node>
    depth_first_descendant_iterator<Node>::depth_first_descendant_iterator()
      : super_t()
      , _node_stack()
      , _itr_stack()
      , _node_ptr()
      , _state(no_traversal)
    {
    }

    template <typename Node>
    depth_first_descendant_iterator<Node>::depth_first_descendant_iterator(
        Node& node
    ) : super_t()
      , _node_stack()
      , _itr_stack()
      , _node_ptr(&node)
      , _state(pre_order_traversal)
    {
        _itr_stack.push_back(node.begin());
        increment();
    }

    template <typename Node>
    template <typename N>
    depth_first_descendant_iterator<Node>::depth_first_descendant_iterator(
        depth_first_descendant_iterator<N> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            ::std::tr1::is_convertible<N,Node>
          , enabler
        >::type
#endif
    ) : super_t(other.base())
      , _node_stack(other._node_stack.begin(), other._node_stack.end())
      , _itr_stack(other._itr_stack.begin(), other._itr_stack.end())
      , _node_ptr(other._node_ptr)
      , _state(other._state)
    {
    }

    template <typename Node>
    inline depth_first_descendant_iterator<Node>::operator
        traversal_state() const
    {
        return _state;
    }

    template <typename Node>
    void depth_first_descendant_iterator<Node>::increment()
    {
        if (_state == post_order_traversal)
        {
            if (_node_stack.empty())
            {
                _state = no_traversal;
                _itr_stack.clear();
            }
            else
            {
                _itr_stack.pop_back();
                _node_ptr = _node_stack.back();
                _node_stack.pop_back();

                if (++this->base_reference() == _node_ptr->end())
                {
                    if (_node_stack.empty())
                    {
                        _itr_stack.clear();
                        _state = no_traversal;
                    }
                    else
                    {
                        child_iterator itr = _itr_stack.back();

                        _itr_stack.pop_back();

                        if (!_itr_stack.empty())
                        {
                            this->base_reference() = _itr_stack.back();
                        }

                        _itr_stack.push_back(itr);
                        _state = post_order_traversal;
                    }
                }
                else
                {
                    _itr_stack.pop_back();
                    _node_stack.push_back(_node_ptr);
                    _itr_stack.push_back(this->base());
                    _node_ptr = &dereference_iterator(this->base());
                    _state = pre_order_traversal;
                    _itr_stack.push_back(_node_ptr->begin());
                }
            }
        }
        else
        {
            child_iterator& itr = _itr_stack.back();

            if (itr == _node_ptr->end())
            {
                _state = (
                    _node_stack.empty() ? no_traversal : post_order_traversal
                );
            }
            else
            {
                _node_stack.push_back(_node_ptr);
                _node_ptr = &dereference_iterator(
                    this->base_reference() = itr
                );
                _state = pre_order_traversal;
                _itr_stack.push_back(_node_ptr->begin());
            }
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__depth_first_descendant_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator==(
            depth_first_descendant_iterator<Node1> const& lhs
          , depth_first_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator==(
            depth_first_descendant_iterator<Node1> const& lhs
          , depth_first_descendant_iterator<Node2> const& rhs
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

//[reference__depth_first_descendant_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename Node1, typename Node2>
    bool
        operator!=(
            depth_first_descendant_iterator<Node1> const& lhs
          , depth_first_descendant_iterator<Node2> const& rhs
        );

    //<-
    template <typename Node1, typename Node2>
    inline bool
        operator!=(
            depth_first_descendant_iterator<Node1> const& lhs
          , depth_first_descendant_iterator<Node2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_depth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    depth_first_descendant_iterator<Node>
        make_depth_first_descendant_iterator(Node& node);

    //<-
    template <typename Node>
    inline depth_first_descendant_iterator<Node>
        make_depth_first_descendant_iterator(Node& node)
    {
        return depth_first_descendant_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__depth_first_iterate_descendants
namespace boost { namespace tree_node {

    template <typename Node, typename BinaryFunction>
    void depth_first_iterate_descendants(Node& node, BinaryFunction function);

    //<-
    template <typename Node, typename BinaryFunction>
    void depth_first_iterate_descendants(Node& node, BinaryFunction function)
    {
        for (depth_first_iterator<Node> itr(node); itr; ++itr)
        {
            function(*itr, traversal_state(itr));
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_DEPTH_FIRST_DESC_ITERATOR_HPP_INCLUDED

