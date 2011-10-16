// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED

#include <iterator>
#include <deque>
#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#ifndef BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#endif
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/detail/metafunction/element_type.hpp>
#include <boost/tree_node/traversal_state.hpp>

//[reference__breadth_first_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer, typename MimicsChildIterator>
    class breadth_first_iterator
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
        typedef typename ::std::iterator_traits<child_iterator>::value_type
                child_value;
        typedef typename ::boost::fusion::traits::is_sequence<
                    child_value
                >::type
                is_associative;
        typedef typename ::boost::mpl::if_<
                    MimicsChildIterator
                  , child_iterator
                  , NodePointer
                >::type
                queue_element;
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
#ifndef BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

        ::std::deque<queue_element> _queue;
        queue_element               _current;
        traversal_state             _state;

     public:
        //->
        breadth_first_iterator();

        explicit breadth_first_iterator(NodePointer const& node);

        template <typename NP, typename MCI>
        breadth_first_iterator(
            breadth_first_iterator<NP,MCI> const& other
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

        breadth_first_iterator& operator++();

        breadth_first_iterator operator++(int);

        operator traversal_state() const;

        //<-
     private:
        static NodePointer
            _deref(child_iterator const&, ::boost::mpl::true_);

        static NodePointer
            _deref(child_iterator const&, ::boost::mpl::false_);

        reference _deref(::boost::mpl::true_) const;

        reference _deref(::boost::mpl::false_) const;

        pointer _indirect(::boost::mpl::true_) const;

        pointer _indirect(::boost::mpl::false_) const;

        NodePointer _current_node(::boost::mpl::true_) const;

        NodePointer const& _current_node(::boost::mpl::false_) const;

        void _initialize(NodePointer const&, ::boost::mpl::true_);

        void _initialize(NodePointer const&, ::boost::mpl::false_);

        void _push_child(child_iterator const&, ::boost::mpl::true_);

        void _push_child(child_iterator const&, ::boost::mpl::false_);

        void _push_children(NodePointer const&, ::boost::mpl::true_);

        void _push_children(NodePointer const&, ::boost::mpl::false_);

        void _pop();

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
                breadth_first_iterator<NP1,MCI1> const& lhs
              , breadth_first_iterator<NP2,MCI2> const& rhs
            );
        //->
    };

    //<-
    template <typename NP, typename MCI>
    breadth_first_iterator<NP,MCI>::breadth_first_iterator()
      : _queue(), _current(), _state(no_traversal)
    {
    }

    template <typename NP, typename MCI>
    breadth_first_iterator<NP,MCI>::breadth_first_iterator(NP const& node)
      : _queue()
      , _current()
      , _state(node ? breadth_first_traversal : no_traversal)
    {
        _initialize(node, MCI());
    }

    template <typename NP1, typename MCI1>
    template <typename NP2, typename MCI2>
    breadth_first_iterator<NP1,MCI1>::breadth_first_iterator(
        breadth_first_iterator<NP2,MCI2> const& other
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
    ) : _queue(other._queue.begin(), other._queue.end())
      , _current(other._current)
      , _state(other._state)
    {
    }

    template <typename NP, typename MCI>
    inline void
        breadth_first_iterator<NP,MCI>::_initialize(
            NP const& node
          , ::boost::mpl::true_
        )
    {
        if (node)
        {
            _push_children(node, MCI());
            _pop();
        }
    }

    template <typename NP, typename MCI>
    inline void
        breadth_first_iterator<NP,MCI>::_initialize(
            NP const& node
          , ::boost::mpl::false_
        )
    {
        _current = node;
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::reference
        breadth_first_iterator<NP,MCI>::_deref(::boost::mpl::true_) const
    {
        return *_current;
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::reference
        breadth_first_iterator<NP,MCI>::_deref(::boost::mpl::false_) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::reference
        breadth_first_iterator<NP,MCI>::operator*() const
    {
        return _deref(MCI());
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::pointer
        breadth_first_iterator<NP,MCI>::_indirect(::boost::mpl::true_) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::pointer
        breadth_first_iterator<NP,MCI>::_indirect(::boost::mpl::false_) const
    {
        return &_current;
    }

    template <typename NP, typename MCI>
    inline NP
        breadth_first_iterator<NP,MCI>::_deref(
            child_iterator const& itr
          , ::boost::mpl::true_
        )
    {
        return itr->second;
    }

    template <typename NP, typename MCI>
    inline NP
        breadth_first_iterator<NP,MCI>::_deref(
            child_iterator const& itr
          , ::boost::mpl::false_
        )
    {
        return *itr;
    }

    template <typename NP, typename MCI>
    inline NP
        breadth_first_iterator<NP,MCI>::_current_node(
            ::boost::mpl::true_
        ) const
    {
        return _deref(_current, is_associative());
    }

    template <typename NP, typename MCI>
    inline NP const&
        breadth_first_iterator<NP,MCI>::_current_node(
            ::boost::mpl::false_
        ) const
    {
        return _current;
    }

    template <typename NP, typename MCI>
    inline typename breadth_first_iterator<NP,MCI>::pointer
        breadth_first_iterator<NP,MCI>::operator->() const
    {
        return _indirect(MCI());
    }

    template <typename NP, typename MCI>
    inline void
        breadth_first_iterator<NP,MCI>::_push_child(
            child_iterator const& itr
          , ::boost::mpl::true_
        )
    {
        _queue.push_back(itr->second);
    }

    template <typename NP, typename MCI>
    inline void
        breadth_first_iterator<NP,MCI>::_push_child(
            child_iterator const& itr
          , ::boost::mpl::false_
        )
    {
        _queue.push_back(*itr);
    }

    template <typename NP, typename MCI>
    void
        breadth_first_iterator<NP,MCI>::_push_children(
            NP const& node
          , ::boost::mpl::true_
        )
    {
        child_iterator itr_end = node->get_child_end();

        for (
            child_iterator itr = node->get_child_begin();
            itr != itr_end;
            ++itr
        )
        {
            _queue.push_back(itr);
        }
    }

    template <typename NP, typename MCI>
    void
        breadth_first_iterator<NP,MCI>::_push_children(
            NP const& node
          , ::boost::mpl::false_
        )
    {
        child_iterator itr_end = node->get_child_end();

        for (
            child_iterator itr = node->get_child_begin();
            itr != itr_end;
            ++itr
        )
        {
            _push_child(itr, is_associative());
        }
    }

    template <typename NP, typename MCI>
    inline void breadth_first_iterator<NP,MCI>::_pop()
    {
        if (_queue.empty())
        {
            _state = no_traversal;
        }
        else
        {
            _current = _queue.front();
            _queue.pop_front();
        }
    }

    template <typename NP, typename MCI>
    inline breadth_first_iterator<NP,MCI>&
        breadth_first_iterator<NP,MCI>::operator++()
    {
        MCI mci;
        _push_children(_current_node(mci), mci);
        _pop();
        return *this;
    }

    template <typename NP, typename MCI>
    inline breadth_first_iterator<NP,MCI>
        breadth_first_iterator<NP,MCI>::operator++(int)
    {
        breadth_first_iterator<NP,MCI> itr(*this);
        ++(*this);
        return itr;
    }

    template <typename NP, typename MCI>
    inline breadth_first_iterator<NP,MCI>::operator traversal_state() const
    {
        return _state;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterator__operator_equals
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
            breadth_first_iterator<NP1,MCI1> const& lhs
          , breadth_first_iterator<NP2,MCI2> const& rhs
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
            breadth_first_iterator<NP1,MCI1> const& lhs
          , breadth_first_iterator<NP2,MCI2> const& rhs
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

//[reference__breadth_first_iterator__operator_not_equal
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
            breadth_first_iterator<NP1,MCI1> const& lhs
          , breadth_first_iterator<NP2,MCI2> const& rhs
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
            breadth_first_iterator<NP1,MCI1> const& lhs
          , breadth_first_iterator<NP2,MCI2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_breadth_first_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    breadth_first_iterator<NodePointer,::boost::mpl::false_>
        make_breadth_first_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline breadth_first_iterator<NodePointer,::boost::mpl::false_>
        make_breadth_first_iterator(NodePointer const& node)
    {
        return breadth_first_iterator<NodePointer,::boost::mpl::false_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_breadth_first_descendant_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer>
    breadth_first_iterator<NodePointer,::boost::mpl::true_>
        make_breadth_first_descendant_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline breadth_first_iterator<NodePointer,::boost::mpl::true_>
        make_breadth_first_descendant_iterator(NodePointer const& node)
    {
        return breadth_first_iterator<NodePointer,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__breadth_first_iterate
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void
        breadth_first_iterate(NodePointer const& node, UnaryFunction function);

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void breadth_first_iterate(NodePointer const& node, UnaryFunction function)
    {
        for (
            breadth_first_iterator<NodePointer,::boost::mpl::false_> itr(node);
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

//[reference__breadth_first_iterate_descendants
namespace boost { namespace tree_node {

    template <typename NodePointer, typename UnaryFunction>
    void
        breadth_first_iterate_descendants(
            NodePointer const& node
          , UnaryFunction function
        );

    //<-
    template <typename NodePointer, typename UnaryFunction>
    void
        breadth_first_iterate_descendants(
            NodePointer const& node
          , UnaryFunction function
        )
    {
        for (
            breadth_first_iterator<NodePointer,::boost::mpl::true_> itr(node);
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

#endif  // BOOST_TREE_BREADTH_FIRST_ITERATOR_HPP_INCLUDED

