// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_DEPTH_FIRST_HPP
#define BOOST_TREE_NODE_ITERATOR_DEPTH_FIRST_HPP

#include <boost/config.hpp>

#if !defined BOOST_NO_CXX11_NULLPTR
#include <cstddef>
#endif

#include <iterator>
#include <deque>
#include <boost/assert.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/value_init.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#endif

#include <boost/mpl/bool.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/iterator/dereference.hpp>
#include <boost/detail/metafunction/is_bidirectional_iterator.hpp>
#include <boost/detail/metafunction/container_pointer.hpp>
#include <boost/detail/metafunction/container_iterator.hpp>
#include <boost/detail/metafunction/container_reverse_iterator.hpp>

//[reference__depth_first_iterator
namespace boost { namespace tree_node {

    template <typename Node, typename IsReverse = ::boost::mpl::false_>
    class depth_first_iterator
      : public ::boost::iterator_adaptor<
            depth_first_iterator<Node,IsReverse>
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
          , typename ::boost::mpl::if_<
                // Node [const] has bidirectional iterators
                //<-
                ::boost::detail::metafunction::is_bidirectional_iterator<
                    typename ::std::tr1::remove_const<Node>::type::iterator
                >
                //->
              , ::boost::bidirectional_traversal_tag
              , ::boost::forward_traversal_tag
            >::type
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
                    depth_first_iterator<Node,IsReverse>
                  , typename ::boost::detail::metafunction::container_pointer<
                        Node
                    >::type
                  , ::boost::use_default
                  , typename ::boost::mpl::if_<
                        ::boost::detail::metafunction
                        ::is_bidirectional_iterator<
                            typename ::std::tr1::remove_const<
                                Node
                            >::type::iterator
                        >
                      , ::boost::bidirectional_traversal_tag
                      , ::boost::forward_traversal_tag
                    >::type
                >
                super_t;

#if !defined BOOST_NO_SFINAE
        struct enabler
        {
        };
#endif

     public:  // Should be private, but conversion ctor won't work.
        ::std::deque<
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type
        > _node_stack;  // ancestors
        ::std::deque<child_iterator> _itr_stack;  // total position
        child_iterator _current_itr;  // points to base()
        typename ::boost::detail::metafunction::container_pointer<
            Node
        >::type _root_ptr;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
//<-
#if 0
//->
        explicit depth_first_iterator(Node* const& node_ptr = nullptr);
//<-
#endif
        explicit depth_first_iterator(
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type const& node_ptr = ::boost::initialized_value
        );
//->

        explicit depth_first_iterator(Node& node);

        template <typename N, typename I>
        depth_first_iterator(
            depth_first_iterator<N,I> const& other
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

        void decrement();

        template <typename N, typename I>
#if defined BOOST_NO_SFINAE
        bool
#else
        typename ::boost::enable_if<
            ::boost::mpl::equal_to<I,IsReverse>
          , bool
        >::type
#endif
            equal(depth_first_iterator<N,I> const& other) const;

     private:
        child_iterator _begin(::boost::mpl::false_);

        child_iterator _begin(::boost::mpl::true_);

        child_iterator _end(::boost::mpl::false_);

        child_iterator _end(::boost::mpl::true_);
        //->
    };

    //<-
    template <typename Node, typename IsReverse>
    depth_first_iterator<Node,IsReverse>::depth_first_iterator(
        typename ::boost::detail::metafunction::container_pointer<
            Node
        >::type const& node_ptr
    ) : super_t(
#if defined BOOST_NO_CXX11_NULLPTR
            0
#else
            nullptr
#endif
        )
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _root_ptr(node_ptr)
      , _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node, typename IsReverse>
    depth_first_iterator<Node,IsReverse>::depth_first_iterator(Node& node)
      : super_t(&node)
      , _node_stack()
      , _itr_stack()
      , _current_itr()
      , _root_ptr(&node)
      , _state(::boost::tree_node::pre_order_traversal)
    {
        this->_itr_stack.push_back(this->_begin(IsReverse()));
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    depth_first_iterator<Node,IsReverse>::depth_first_iterator(
        depth_first_iterator<N,I> const& other
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
      , _root_ptr(other._root_ptr)
      , _state(other._state)
    {
    }

    template <typename Node, typename IsReverse>
    inline depth_first_iterator<Node,IsReverse>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node, typename IsReverse>
    void depth_first_iterator<Node,IsReverse>::increment()
    {
        switch (this->_state)
        {
            case ::boost::tree_node::pre_order_traversal:
            {
                child_iterator& itr = this->_itr_stack.back();

                if (itr == this->_end(IsReverse()))
                {
                    // No children: change state.
                    this->_state = ::boost::tree_node::post_order_traversal;
                }
                else
                {
                    // Go deeper.
                    this->_node_stack.push_back(this->base());
                    this->base_reference() = &(
                        dereference_iterator(this->_current_itr = itr)
                    );
                    this->_itr_stack.push_back(this->_begin(IsReverse()));
                }

                break;
            }

            case ::boost::tree_node::post_order_traversal:
            {
                this->_itr_stack.pop_back();

                if (this->_node_stack.empty())
                {
                    // Pass the end.
                    this->_state = ::boost::tree_node::no_traversal;
                    this->_itr_stack.clear();
                }
                else
                {
                    this->base_reference() = this->_node_stack.back();
                    this->_node_stack.pop_back();

                    if (++this->_current_itr == this->_end(IsReverse()))
                    {
                        // No next sibling: traverse the parent.
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
                        // Traverse the sibling.
                        this->_itr_stack.pop_back();
                        this->_node_stack.push_back(this->base());
                        this->_itr_stack.push_back(this->_current_itr);
                        this->base_reference() = &(
                            dereference_iterator(this->_current_itr)
                        );
                        this->_state = ::boost::tree_node::pre_order_traversal;
                        this->_itr_stack.push_back(this->_begin(IsReverse()));
                    }
                }

                break;
            }

            default:
            {
                BOOST_ASSERT_MSG(false, "Do not increment past-the-end!");
            }
        }
    }

    template <typename Node, typename IsReverse>
    void depth_first_iterator<Node,IsReverse>::decrement()
    {
        switch (this->_state)
        {
            case ::boost::tree_node::pre_order_traversal:
            {
                this->_itr_stack.pop_back();

                if (this->_node_stack.empty())
                {
                    // Pass the end.
                    this->_state = ::boost::tree_node::no_traversal;
                    this->_itr_stack.clear();
                }
                else
                {
                    this->base_reference() = this->_node_stack.back();
                    this->_node_stack.pop_back();

                    if (this->_current_itr == this->_begin(IsReverse()))
                    {
                        // No previous sibling: traverse the parent.
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
                        // Traverse the sibling.
                        this->_itr_stack.pop_back();
                        this->_node_stack.push_back(this->base());
                        this->_itr_stack.push_back(--this->_current_itr);
                        this->base_reference() = &(
                            dereference_iterator(this->_current_itr)
                        );
                        this->_state = ::boost::tree_node::post_order_traversal;

                        // Add last child position, if any, to total position.
                        child_iterator last_itr = this->_begin(IsReverse());

                        if (last_itr != this->_end(IsReverse()))
                        {
                            ::std::advance(last_itr, this->base()->size() - 1);
                        }

                        this->_itr_stack.push_back(last_itr);
                    }
                }

                break;
            }

            case ::boost::tree_node::post_order_traversal:
            {
                child_iterator& itr = this->_itr_stack.back();

                if (itr == this->_end(IsReverse()))
                {
                    // No children: change state.
                    this->_state = ::boost::tree_node::pre_order_traversal;
                }
                else
                {
                    // Go deeper.
                    this->_node_stack.push_back(this->base());
                    this->base_reference() = &(
                        dereference_iterator(this->_current_itr = itr)
                    );

                    // Add last child position, if any, to total position.
                    child_iterator last_itr = this->_begin(IsReverse());

                    if (last_itr != this->_end(IsReverse()))
                    {
                        ::std::advance(last_itr, this->base()->size() - 1);
                    }

                    this->_itr_stack.push_back(last_itr);
                }

                break;
            }

            default:
            {
                BOOST_ASSERT_MSG(
                    this->_root_ptr
                  , "Do not decrement past-the-end of NULL!"
                );
                this->base_reference() = this->_root_ptr;
                this->_state = ::boost::tree_node::post_order_traversal;

                // Add last child position, if any, to total position.
                child_iterator last_itr = this->_begin(IsReverse());

                if (last_itr != this->_end(IsReverse()))
                {
                    ::std::advance(last_itr, this->base()->size() - 1);
                }

                this->_itr_stack.push_back(last_itr);
                break;
            }
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
        depth_first_iterator<Node,IsReverse>::equal(
            depth_first_iterator<N,I> const& other
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
    inline typename depth_first_iterator<Node,IsReverse>::child_iterator
        depth_first_iterator<Node,IsReverse>::_begin(::boost::mpl::false_)
    {
        return this->base()->begin();
    }

    template <typename Node, typename IsReverse>
    inline typename depth_first_iterator<Node,IsReverse>::child_iterator
        depth_first_iterator<Node,IsReverse>::_begin(::boost::mpl::true_)
    {
        return this->base()->rbegin();
    }

    template <typename Node, typename IsReverse>
    inline typename depth_first_iterator<Node,IsReverse>::child_iterator
        depth_first_iterator<Node,IsReverse>::_end(::boost::mpl::false_)
    {
        return this->base()->end();
    }

    template <typename Node, typename IsReverse>
    inline typename depth_first_iterator<Node,IsReverse>::child_iterator
        depth_first_iterator<Node,IsReverse>::_end(::boost::mpl::true_)
    {
        return this->base()->rend();
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_depth_first_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    depth_first_iterator<Node> make_depth_first_iterator(Node& node);

    //<-
    template <typename Node>
    inline depth_first_iterator<Node> make_depth_first_iterator(Node& node)
    {
        return depth_first_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_depth_first_iterator_end
namespace boost { namespace tree_node {

    template <typename Node>
    depth_first_iterator<Node> make_depth_first_iterator_end(Node* ptr);

    //<-
    template <typename Node>
    inline depth_first_iterator<Node> make_depth_first_iterator_end(Node* ptr)
    {
        return depth_first_iterator<Node>(ptr);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_depth_first_reverse_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    depth_first_iterator<Node,::boost::mpl::true_>
        make_depth_first_reverse_iterator(Node& node);

    //<-
    template <typename Node>
    inline depth_first_iterator<Node,::boost::mpl::true_>
        make_depth_first_reverse_iterator(Node& node)
    {
        return depth_first_iterator<Node,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_depth_first_reverse_iterator_end
namespace boost { namespace tree_node {

    template <typename Node>
    depth_first_iterator<Node,::boost::mpl::true_>
        make_depth_first_reverse_iterator_end(Node* ptr);

    //<-
    template <typename Node>
    inline depth_first_iterator<Node,::boost::mpl::true_>
        make_depth_first_reverse_iterator_end(Node* ptr)
    {
        return depth_first_iterator<Node,::boost::mpl::true_>(ptr);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ITERATOR_DEPTH_FIRST_HPP

