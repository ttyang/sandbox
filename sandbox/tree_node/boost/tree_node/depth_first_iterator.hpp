// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_DEPTH_FIRST_ITERATOR_HPP_INCLUDED
#define BOOST_TREE_NODE_DEPTH_FIRST_ITERATOR_HPP_INCLUDED

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

//[reference__depth_first_iterator
namespace boost { namespace tree_node {

    template <typename NodePointer, typename MimicsChildIterator>
    class depth_first_iterator
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

        ::std::deque<NodePointer>    _node_stack;
        ::std::deque<child_iterator> _itr_stack;
        NodePointer                  _current_node;
        child_iterator               _current_itr;
        traversal_state              _state;

     public:
        //->
        depth_first_iterator();

        explicit depth_first_iterator(NodePointer const& node);

        template <typename NP, typename MCI>
        depth_first_iterator(
            depth_first_iterator<NP,MCI> const& other
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

        depth_first_iterator& operator++();

        depth_first_iterator operator++(int);

        operator traversal_state() const;

        //<-
     private:
        reference _deref(::boost::mpl::true_) const;

        reference _deref(::boost::mpl::false_) const;

        pointer _indirect(::boost::mpl::true_) const;

        pointer _indirect(::boost::mpl::false_) const;

        void _initialize(::boost::mpl::true_);

        void _initialize(::boost::mpl::false_);

        void _set_state(::boost::mpl::true_);

        void _set_state(::boost::mpl::false_);

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
                depth_first_iterator<NP1,MCI1> const& lhs
              , depth_first_iterator<NP2,MCI2> const& rhs
            );
        //->
    };

    //<-
    template <typename NP, typename MCI>
    depth_first_iterator<NP,MCI>::depth_first_iterator()
      : _node_stack()
      , _itr_stack()
      , _current_node()
      , _current_itr()
      , _state(no_traversal)
    {
    }

    template <typename NP, typename MCI>
    depth_first_iterator<NP,MCI>::depth_first_iterator(NP const& node)
      : _node_stack()
      , _itr_stack()
      , _current_node(node)
      , _current_itr()
      , _state(node ? pre_order_traversal : no_traversal)
    {
        if (node)
        {
            _itr_stack.push_back(node->get_child_begin());
            _initialize(MCI());
        }
    }

    template <typename NP1, typename MCI1>
    template <typename NP2, typename MCI2>
    depth_first_iterator<NP1,MCI1>::depth_first_iterator(
        depth_first_iterator<NP2,MCI2> const& other
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
    ) : _node_stack(other._node_stack.begin(), other._node_stack.end())
      , _itr_stack(other._itr_stack.begin(), other._itr_stack.end())
      , _current_node(other._current_node)
      , _current_itr(other._current_itr)
      , _state(other._state)
    {
    }

    template <typename NP, typename MCI>
    inline void
        depth_first_iterator<NP,MCI>::_initialize(::boost::mpl::true_)
    {
        ++(*this);
    }

    template <typename NP, typename MCI>
    inline void
        depth_first_iterator<NP,MCI>::_initialize(::boost::mpl::false_)
    {
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::reference
        depth_first_iterator<NP,MCI>::_deref(::boost::mpl::true_) const
    {
        return *_current_itr;
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::reference
        depth_first_iterator<NP,MCI>::_deref(::boost::mpl::false_) const
    {
        return _current_node;
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::reference
        depth_first_iterator<NP,MCI>::operator*() const
    {
        return _deref(MCI());
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::pointer
        depth_first_iterator<NP,MCI>::_indirect(::boost::mpl::true_) const
    {
        return _current_itr;
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::pointer
        depth_first_iterator<NP,MCI>::_indirect(::boost::mpl::false_) const
    {
        return &_current_node;
    }

    template <typename NP, typename MCI>
    inline typename depth_first_iterator<NP,MCI>::pointer
        depth_first_iterator<NP,MCI>::operator->() const
    {
        return _indirect(MCI());
    }

    template <typename NP, typename MCI>
    inline void depth_first_iterator<NP,MCI>::_set_state(::boost::mpl::true_)
    {
        _state = _node_stack.empty() ? no_traversal : post_order_traversal;
    }

    template <typename NP, typename MCI>
    inline void depth_first_iterator<NP,MCI>::_set_state(::boost::mpl::false_)
    {
        _state = post_order_traversal;
    }

    template <typename NP, typename MCI>
    depth_first_iterator<NP,MCI>&
        depth_first_iterator<NP,MCI>::operator++()
    {
        if (_state == post_order_traversal)
        {
            _itr_stack.pop_back();

            if (_node_stack.empty())
            {
                _state = no_traversal;

                while (!_itr_stack.empty())
                {
                    _itr_stack.pop_back();
                }
            }
            else
            {
                _current_node = _node_stack.back();
                _node_stack.pop_back();

                if (++_current_itr == _current_node->get_child_end())
                {
                    _set_state(MCI());

                    if (_state)
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
                        while (!_itr_stack.empty())
                        {
                            _itr_stack.pop_back();
                        }
                    }
                }
                else
                {
                    _itr_stack.pop_back();
                    _node_stack.push_back(_current_node);
                    _itr_stack.push_back(_current_itr);
                    _current_node = dereference_iterator(_current_itr);
                    _state = pre_order_traversal;
                    _itr_stack.push_back(_current_node->get_child_begin());
                }
            }
        }
        else
        {
            child_iterator& itr = _itr_stack.back();

            if (itr == _current_node->get_child_end())
            {
                _set_state(MCI());
            }
            else
            {
                _node_stack.push_back(_current_node);
                _current_node = dereference_iterator(_current_itr = itr);
                _state = pre_order_traversal;
                _itr_stack.push_back(_current_node->get_child_begin());
            }
        }

        return *this;
    }

    template <typename NP, typename MCI>
    inline depth_first_iterator<NP,MCI>
        depth_first_iterator<NP,MCI>::operator++(int)
    {
        depth_first_iterator<NP,MCI> itr(*this);
        ++(*this);
        return itr;
    }

    template <typename NP, typename MCI>
    inline depth_first_iterator<NP,MCI>::operator traversal_state() const
    {
        return _state;
    }
    //->

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
            depth_first_iterator<NP1,MCI1> const& lhs
          , depth_first_iterator<NP2,MCI2> const& rhs
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
            depth_first_iterator<NP1,MCI1> const& lhs
          , depth_first_iterator<NP2,MCI2> const& rhs
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
            depth_first_iterator<NP1,MCI1> const& lhs
          , depth_first_iterator<NP2,MCI2> const& rhs
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
            depth_first_iterator<NP1,MCI1> const& lhs
          , depth_first_iterator<NP2,MCI2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->

    template <typename NodePointer>
    depth_first_iterator<NodePointer,::boost::mpl::false_>
        make_depth_first_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline depth_first_iterator<NodePointer,::boost::mpl::false_>
        make_depth_first_iterator(NodePointer const& node)
    {
        return depth_first_iterator<NodePointer,::boost::mpl::false_>(node);
    }
    //->

    template <typename NodePointer>
    depth_first_iterator<NodePointer,::boost::mpl::true_>
        make_depth_first_descendant_iterator(NodePointer const& node);

    //<-
    template <typename NodePointer>
    inline depth_first_iterator<NodePointer,::boost::mpl::true_>
        make_depth_first_descendant_iterator(NodePointer const& node)
    {
        return depth_first_iterator<NodePointer,::boost::mpl::true_>(node);
    }
    //->

    template <typename NodePointer, typename BinaryFunction>
    void depth_first_iterate(NodePointer const& node, BinaryFunction function);

    //<-
    template <typename NodePointer, typename BinaryFunction>
    void depth_first_iterate(NodePointer const& node, BinaryFunction function)
    {
        for (
            depth_first_iterator<NodePointer,::boost::mpl::false_> itr(node);
            itr;
            ++itr
        )
        {
            function(*itr, traversal_state(itr));
        }
    }
    //->

    template <typename NodePointer, typename BinaryFunction>
    void
        depth_first_iterate_descendants(
            NodePointer const& node
          , BinaryFunction function
        );

    //<-
    template <typename NodePointer, typename BinaryFunction>
    void
        depth_first_iterate_descendants(
            NodePointer const& node
          , BinaryFunction function
        )
    {
        for (
            depth_first_iterator<NodePointer,::boost::mpl::true_> itr(node);
            itr;
            ++itr
        )
        {
            function(*itr, traversal_state(itr));
        }
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_DEPTH_FIRST_ITERATOR_HPP_INCLUDED

