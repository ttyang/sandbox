// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_PRE_ORDER_HPP
#define BOOST_TREE_NODE_ITERATOR_PRE_ORDER_HPP

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
#include <boost/detail/metafunction/container_pointer.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>
#include <boost/detail/metafunction/container_reverse_iterator.hpp>

//[reference__pre_order_iterator
namespace boost { namespace tree_node {

    template <typename Node, typename IsReverse = ::boost::mpl::false_>
    class pre_order_iterator
      : public ::boost::iterator_adaptor<
            pre_order_iterator<Node,IsReverse>
//<-
#if 0
//->
          , Node*
            //<-
#endif
          , typename ::boost::detail::metafunction::container_pointer<
                Node
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
                    pre_order_iterator<Node,IsReverse>
                  , typename ::boost::detail::metafunction::container_pointer<
                        Node
                    >::type
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
        ::std::deque<
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type
        > _node_stack;
        ::std::deque<child_iterator> _itr_stack;
        child_iterator _current_itr;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
        pre_order_iterator();

        explicit pre_order_iterator(Node& node);

        template <typename N, typename I>
        pre_order_iterator(
            pre_order_iterator<N,I> const& other
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
            equal(pre_order_iterator<N,I> const& other) const;

     private:
        void _push(::boost::mpl::false_);

        void _push(::boost::mpl::true_);

        child_iterator _end(::boost::mpl::false_);

        child_iterator _end(::boost::mpl::true_);
        //->
    };

    //<-
    template <typename Node, typename IsReverse>
    pre_order_iterator<Node,IsReverse>::pre_order_iterator()
      : super_t()
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node, typename IsReverse>
    pre_order_iterator<Node,IsReverse>::pre_order_iterator(Node& node)
      : super_t(&node)
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _state(::boost::tree_node::pre_order_traversal)
    {
        this->_push(IsReverse());
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    pre_order_iterator<Node,IsReverse>::pre_order_iterator(
        pre_order_iterator<N,I> const& other
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
      , _node_stack(other._node_stack.begin(), other._node_stack.end())
      , _itr_stack(other._itr_stack.begin(), other._itr_stack.end())
      , _current_itr(other._current_itr)
      , _state(other._state)
    {
    }

    template <typename Node, typename IsReverse>
    inline pre_order_iterator<Node,IsReverse>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node, typename IsReverse>
    void pre_order_iterator<Node,IsReverse>::increment()
    {
        if (this->_itr_stack.back() == this->_end(IsReverse()))
        {
            bool is_post_order = true;

            while (is_post_order)
            {
                this->_itr_stack.pop_back();

                if (this->_node_stack.empty())
                {
                    this->_state = ::boost::tree_node::no_traversal;
                    this->_itr_stack.clear();
                    is_post_order = false;
                }
                else
                {
                    this->base_reference() = this->_node_stack.back();
                    this->_node_stack.pop_back();

                    if (++this->_current_itr == this->_end(IsReverse()))
                    {
                        child_iterator itr = this->_itr_stack.back();

                        this->_itr_stack.pop_back();

                        if (!this->_itr_stack.empty())
                        {
                            this->_current_itr = this->_itr_stack.back();
                        }

                        this->_itr_stack.push_back(itr);
                    }
                    else
                    {
                        this->_itr_stack.pop_back();
                        this->_node_stack.push_back(this->base());
                        this->_itr_stack.push_back(this->_current_itr);
                        this->base_reference() = &(
                            dereference_iterator(this->_current_itr)
                        );
                        this->_push(IsReverse());
                        is_post_order = false;
                    }
                }
            }
        }
        else
        {
            this->_node_stack.push_back(this->base());
            this->base_reference() = &dereference_iterator(
                this->_current_itr = this->_itr_stack.back()
            );
            this->_push(IsReverse());
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
        pre_order_iterator<Node,IsReverse>::equal(
            pre_order_iterator<N,I> const& other
        ) const
    {
        if (this->_state == other._state)
        {
            return this->_state ? (*(*this) == *(*other)) : !other._state;
        }
        else
        {
            return false;
        }
    }

    template <typename Node, typename IsReverse>
    inline void pre_order_iterator<Node,IsReverse>::_push(::boost::mpl::false_)
    {
        this->_itr_stack.push_back(this->base()->begin());
    }

    template <typename Node, typename IsReverse>
    inline void pre_order_iterator<Node,IsReverse>::_push(::boost::mpl::true_)
    {
        this->_itr_stack.push_back(this->base()->rbegin());
    }

    template <typename Node, typename IsReverse>
    inline typename pre_order_iterator<Node,IsReverse>::child_iterator
        pre_order_iterator<Node,IsReverse>::_end(::boost::mpl::false_)
    {
        return this->base()->end();
    }

    template <typename Node, typename IsReverse>
    inline typename pre_order_iterator<Node,IsReverse>::child_iterator
        pre_order_iterator<Node,IsReverse>::_end(::boost::mpl::true_)
    {
        return this->base()->rend();
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

//[reference__make_post_order_reverse_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    pre_order_iterator<Node,::boost::mpl::true_>
        make_post_order_reverse_iterator(Node& node);

    //<-
    template <typename Node>
    inline pre_order_iterator<Node,::boost::mpl::true_>
        make_post_order_reverse_iterator(Node& node)
    {
        return pre_order_iterator<Node,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ITERATOR_PRE_ORDER_HPP

