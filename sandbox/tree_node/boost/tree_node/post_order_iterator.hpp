// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED

#include <deque>
#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/iterator/iterator_traits.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/dereference_iterator.hpp>
#include <boost/detail/metafunction/element_type.hpp>

//[reference__post_order_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer, typename MimicsChildIterator>
    class post_order_iterator
    {
        //<-
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_pointer<NodePointer>
                  , ::std::tr1::remove_pointer<NodePointer>
                  , ::boost::detail::element_type<NodePointer>
                >::type
                element_type;
        typedef typename ::std::tr1::remove_const<element_type>::type
                node_type;
        typedef typename ::boost::mpl::if_<
                    ::std::tr1::is_const<element_type>
                  , typename node_type::const_child_iterator
                  , typename node_type::child_iterator
                >::type
                child_iterator;
        typedef typename ::boost::iterator_value<child_iterator>::type
                child_value;
        typedef typename ::boost::mpl::if_<
                    MimicsChildIterator
                  , child_iterator
                  , NodePointer
                >::type
                stack_element;
        //->

     public:
        typedef // implementation_defined
                //<-
                typename ::boost::mpl::if_<
                    MimicsChildIterator
                  , child_value
                  , NodePointer
                >::type
                //->
                value_type;
        typedef value_type const&
                reference;
        typedef // implementation_defined
                //<-
                typename ::boost::mpl::if_<
                    MimicsChildIterator
                  , child_iterator
                  , value_type const*
                >::type
                //->
                pointer;
        typedef ::std::ptrdiff_t
                difference_type;
        typedef ::std::forward_iterator_tag
                iterator_category;

        //<-
     private:
        struct enabler
        {
        };

        std::deque<stack_element> _stack;
        stack_element             _current;
        traversal_state           _state;

     public:
        //->
        post_order_iterator();

        explicit post_order_iterator(NodePointer const& node);

        template <typename NP, typename MCI>
        post_order_iterator(
            post_order_iterator<NP,MCI> const& other
//<-
#ifndef BOOST_NO_SFINAE
          , typename ::boost::enable_if<
                typename ::boost::mpl::if_<
                    ::std::tr1::is_convertible<NP,NodePointer>
                  , ::boost::mpl::equal_to<MCI,MimicsChildIterator>
                  , ::boost::mpl::false_
                >::type
              , enabler
            >::type = enabler()
#endif
//->
        );

        reference operator*() const;

        pointer operator->() const;

        post_order_iterator& operator++();

        post_order_iterator operator++(int);

        operator traversal_state() const;

        //<-
     private:
        reference _deref(::boost::mpl::true_) const;

        reference _deref(::boost::mpl::false_) const;

        pointer _indirect(::boost::mpl::true_) const;

        pointer _indirect(::boost::mpl::false_) const;

        NodePointer _current_node(::boost::mpl::true_) const;

        NodePointer const& _current_node(::boost::mpl::false_) const;

        void _push_child_itr(child_iterator const&, ::boost::mpl::true_);

        void _push_child_itr(child_iterator const&, ::boost::mpl::false_);

        void _start(NodePointer const&);

        void _initialize(NodePointer const&, ::boost::mpl::true_);

        void _initialize(NodePointer const&, ::boost::mpl::false_);

        template <typename NP1, typename NP2, typename MCI1, typename MCI2>
#ifdef BOOST_NO_SFINAE
        friend bool
#else
        friend typename ::boost::enable_if<
            ::boost::mpl::equal_to<MCI1,MCI2>
          , bool
        >::type
#endif
            operator==(
                post_order_iterator<NP1,MCI1> const& lhs
              , post_order_iterator<NP2,MCI2> const& rhs
            );
        //->
    };

    //<-
    template <typename NP, typename MCI>
    post_order_iterator<NP,MCI>::post_order_iterator()
      : _stack(), _current(), _state(no_traversal)
    {
    }

    template <typename NP, typename MCI>
    post_order_iterator<NP,MCI>::post_order_iterator(NP const& node)
      : _stack()
      , _current()
      , _state(node ? post_order_traversal : no_traversal)
    {
        if (node)
        {
            _initialize(node, MCI());
        }
    }

    template <typename NP1, typename MCI1>
    template <typename NP2, typename MCI2>
    post_order_iterator<NP1,MCI1>::post_order_iterator(
        post_order_iterator<NP2,MCI2> const& other
#ifndef BOOST_NO_SFINAE
      , typename ::boost::enable_if<
            typename ::boost::mpl::if_<
                ::std::tr1::is_convertible<NP2,NP1>
              , ::boost::mpl::equal_to<MCI2,MCI1>
              , ::boost::mpl::false_
            >::type
          , enabler
        >::type
#endif
    ) : _stack(other._stack.begin(), other._stack.end())
      , _current(other._current)
      , _state(other._state)
    {
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::reference
        post_order_iterator<NP,MCI>::_deref(::boost::mpl::true_) const
    {
        return *_current;
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::reference
        post_order_iterator<NP,MCI>::_deref(::boost::mpl::false_) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::reference
        post_order_iterator<NP,MCI>::operator*() const
    {
        return _deref(MCI());
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::pointer
        post_order_iterator<NP,MCI>::_indirect(::boost::mpl::true_) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::pointer
        post_order_iterator<NP,MCI>::_indirect(::boost::mpl::false_) const
    {
        return &_current;
    }

    template <typename NP, typename MCI>
    inline typename post_order_iterator<NP,MCI>::pointer
        post_order_iterator<NP,MCI>::operator->() const
    {
        return _indirect(MCI());
    }

    template <typename NP, typename MCI>
    inline NP
        post_order_iterator<NP,MCI>::_current_node(::boost::mpl::true_) const
    {
        return dereference_iterator(_current);
    }

    template <typename NP, typename MCI>
    inline NP const&
        post_order_iterator<NP,MCI>::_current_node(::boost::mpl::false_) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline void
        post_order_iterator<NP,MCI>::_push_child_itr(
            child_iterator const& itr
          , ::boost::mpl::true_
        )
    {
        _stack.push_back(itr);
    }

    template <typename NP, typename MCI>
    inline void
        post_order_iterator<NP,MCI>::_push_child_itr(
            child_iterator const& itr
          , boost::mpl::false_
        )
    {
        _stack.push_back(dereference_iterator(itr));
    }

    template <typename NP, typename MCI>
    void post_order_iterator<NP,MCI>::_start(NP const& n)
    {
        child_iterator itr = n->get_child_begin();
        child_iterator itr_end = n->get_child_end();

        if (itr != itr_end)
        {
            NP node(n);
            ::std::deque<child_iterator> pre_order_stack;

            for (;;)
            {
                while (itr != itr_end)
                {
                    pre_order_stack.push_back(itr);
                    ++itr;
                }

                _push_child_itr(pre_order_stack.back(), MCI());
                node = dereference_iterator(pre_order_stack.back());
                pre_order_stack.pop_back();

                if (pre_order_stack.empty())
                {
                    _current = _stack.back();
                    node = _current_node(MCI());
                    itr = node->get_child_begin();
                    itr_end = node->get_child_end();

                    if (itr == itr_end)
                    {
                        _stack.pop_back();
                        break;
                    }
                }
                else
                {
                    itr = node->get_child_begin();
                    itr_end = node->get_child_end();
                }
            }
        }
    }

    template <typename NP, typename MCI>
    inline void
        post_order_iterator<NP,MCI>::_initialize(
            NP const& node
          , ::boost::mpl::true_
        )
    {
        _start(node);

        if (_stack.empty())
        {
            _state = no_traversal;
        }
    }

    template <typename NP, typename MCI>
    inline void
        post_order_iterator<NP,MCI>::_initialize(
            NP const& node
          , ::boost::mpl::false_
        )
    {
        _stack.push_back(_current = node);
        _start(node);
    }

    template <typename NP, typename MCI>
    inline post_order_iterator<NP,MCI>&
        post_order_iterator<NP,MCI>::operator++()
    {
        if (_stack.empty())
        {
            _state = no_traversal;
        }
        else
        {
            _current = _stack.back();
            _stack.pop_back();
        }

        return *this;
    }

    template <typename NP, typename MCI>
    inline post_order_iterator<NP,MCI>
        post_order_iterator<NP,MCI>::operator++(int)
    {
        post_order_iterator<NP,MCI> itr(*this);
        ++(*this);
        return itr;
    }

    template <typename NP, typename MCI>
    inline post_order_iterator<NP,MCI>::operator traversal_state() const
    {
        return _state;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_iterator__operator_equals
namespace boost { namespace tree_node {

    template <typename NP1, typename NP2, typename MCI1, typename MCI2>
//<-
#ifdef BOOST_NO_SFINAE
    bool
#else
//->
    typename ::boost::enable_if< ::boost::mpl::equal_to<MCI1,MCI2>,bool>::type
//<-
#endif
//->
        operator==(
            post_order_iterator<NP1,MCI1> const& lhs
          , post_order_iterator<NP2,MCI2> const& rhs
        );

    //<-
    template <typename NP1, typename NP2, typename MCI1, typename MCI2>
#ifdef BOOST_NO_SFINAE
    inline bool
#else
    inline typename ::boost::enable_if<
        ::boost::mpl::equal_to<MCI1,MCI2>
      , bool
    >::type
#endif
        operator==(
            post_order_iterator<NP1,MCI1> const& lhs
          , post_order_iterator<NP2,MCI2> const& rhs
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

//[reference__post_order_iterator__operator_not_equal
namespace boost { namespace tree_node {

    template <typename NP1, typename NP2, typename MCI1, typename MCI2>
//<-
#ifdef BOOST_NO_SFINAE
    bool
#else
//->
    typename ::boost::enable_if< ::boost::mpl::equal_to<MCI1,MCI2>,bool>::type
//<-
#endif
//->
        operator!=(
            post_order_iterator<NP1,MCI1> const& lhs
          , post_order_iterator<NP2,MCI2> const& rhs
        );

    //<-
    template <typename NP1, typename NP2, typename MCI1, typename MCI2>
#ifdef BOOST_NO_SFINAE
    inline bool
#else
    inline typename ::boost::enable_if<
        ::boost::mpl::equal_to<MCI1,MCI2>
      , bool
    >::type
#endif
        operator!=(
            post_order_iterator<NP1,MCI1> const& lhs
          , post_order_iterator<NP2,MCI2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_post_order_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    post_order_iterator<NodePointer,::boost::mpl::false_>
        make_post_order_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline post_order_iterator<NodePointer,::boost::mpl::false_>
        make_post_order_iterator(NodePointer const& node)
    {
        return post_order_iterator<NodePointer,::boost::mpl::false_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_post_order_descendant_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    post_order_iterator<NodePointer,::boost::mpl::true_>
        make_post_order_descendant_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline post_order_iterator<NodePointer,::boost::mpl::true_>
        make_post_order_descendant_iterator(NodePointer const& node)
    {
        return post_order_iterator<NodePointer,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_iterate
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void post_order_iterate(NodePointer const& node, UnaryFunction function);

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void post_order_iterate(NodePointer const& node, UnaryFunction function)
    {
        for (
            post_order_iterator<NodePointer,::boost::mpl::false_> itr(node);
            itr;
            ++itr
        )
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__post_order_iterate_descendants
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void
        post_order_iterate_descendants(
            NodePointer const& node
          , UnaryFunction function
        );

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void
        post_order_iterate_descendants(
            NodePointer const& node
          , UnaryFunction function
        )
    {
        for (
            post_order_iterator<NodePointer,::boost::mpl::true_> itr(node);
            itr;
            ++itr
        )
        {
            function(*itr);
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_POST_ORDER_ITERATOR_HPP_INCLUDED

