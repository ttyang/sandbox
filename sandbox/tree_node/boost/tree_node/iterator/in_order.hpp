// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ITERATOR_IN_ORDER_HPP
#define BOOST_TREE_NODE_ITERATOR_IN_ORDER_HPP

#include <boost/config.hpp>

#if !defined BOOST_NO_CXX11_NULLPTR
#include <cstddef>
#endif

#include <iterator>
#include <boost/tr1/type_traits.hpp>
#include <boost/utility/value_init.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/equal_to.hpp>
#endif

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/detail/metafunction/container_pointer.hpp>
#include <boost/tree_node/traversal_state.hpp>
#include <boost/tree_node/key/count.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/algorithm/advance_binary.hpp>
#include <boost/tree_node/algorithm/binary_index_of.hpp>
#include <boost/assert.hpp>

//[reference__in_order_iterator
namespace boost { namespace tree_node {

    template <typename Node, typename IsReverse = ::boost::mpl::false_>
    class in_order_iterator
      : public ::boost::iterator_adaptor<
            in_order_iterator<Node,IsReverse>
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
                result_of::has_key<
                    typename ::std::tr1::remove_const<Node>::type
                  , count_key
                >
                // TODO: Replace with indexable_traversal_tag
              , ::boost::random_access_traversal_tag
              , ::boost::bidirectional_traversal_tag
            >::type
        >
    {
        //<-
        typedef ::boost::iterator_adaptor<
                    in_order_iterator<Node,IsReverse>
                  , typename ::boost::detail::metafunction::container_pointer<
                        Node
                    >::type
                  , ::boost::use_default
                  , typename ::boost::mpl::if_<
                        result_of::has_key<
                            typename ::std::tr1::remove_const<Node>::type
                          , count_key
                        >
                        // TODO: Replace with indexable_traversal_tag
                      , ::boost::random_access_traversal_tag
                      , ::boost::bidirectional_traversal_tag
                    >::type
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
        typename ::boost::detail::metafunction::container_pointer<
            Node
        >::type _root_ptr;
        ::boost::tree_node::traversal_state _state;
        //->

     public:
//<-
#if 0
//->
        explicit in_order_iterator(Node* const& node_ptr = nullptr);
//<-
#endif
        explicit in_order_iterator(
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type const& node_ptr = ::boost::initialized_value
        );
//->

        explicit in_order_iterator(Node& node, bool is_not_position = true);

        template <typename N, typename I>
        in_order_iterator(
            in_order_iterator<N,I> const& other
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

        void advance(typename super_t::difference_type n);

        template <typename N, typename I>
#if defined BOOST_NO_SFINAE
        typename super_t::difference_type
#else
        typename ::boost::enable_if<
            typename ::boost::mpl::if_<
                ::std::tr1::is_convertible<N,Node>
              , ::boost::mpl::equal_to<I,IsReverse>
              , ::boost::mpl::false_
            >::type
          , typename super_t::difference_type
        >::type
#endif
            distance_to(in_order_iterator<N,I> const& other) const;

        template <typename N, typename I>
#if defined BOOST_NO_SFINAE
        bool
#else
        typename ::boost::enable_if<
            ::boost::mpl::equal_to<I,IsReverse>
          , bool
        >::type
#endif
            equal(in_order_iterator<N,I> const& other) const;

     private:
        void _increment(::boost::mpl::false_);

        void _increment(::boost::mpl::true_);

        void _initialize(::boost::mpl::false_);

        void _initialize(::boost::mpl::true_);
        //->
    };

    //<-
    template <typename Node, typename IsReverse>
    in_order_iterator<Node,IsReverse>::in_order_iterator(
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
      , _root_ptr(node_ptr)
      , _state(::boost::tree_node::no_traversal)
    {
    }

    template <typename Node, typename IsReverse>
    in_order_iterator<Node,IsReverse>::in_order_iterator(
        Node& node
      , bool is_not_position
    ) : super_t(&node)
      , _root_ptr(&node)
      , _state(::boost::tree_node::in_order_traversal)
    {
        if (is_not_position)
        {
            this->_initialize(IsReverse());
        }
        else
        {
            while (this->_root_ptr->get_parent_ptr())
            {
                this->_root_ptr = this->_root_ptr->get_parent_ptr();
            }
        }
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    in_order_iterator<Node,IsReverse>::in_order_iterator(
        in_order_iterator<N,I> const& other
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
      , _root_ptr(other._root_ptr)
      , _state(other._state)
    {
    }

    template <typename Node, typename IsReverse>
    inline in_order_iterator<Node,IsReverse>::operator
        ::boost::tree_node::traversal_state() const
    {
        return this->_state;
    }

    template <typename Node, typename IsReverse>
    void in_order_iterator<Node,IsReverse>::_initialize(::boost::mpl::false_)
    {
        while (this->base()->get_left_child_ptr())
        {
            this->base_reference() = this->base()->get_left_child_ptr();
        }
    }

    template <typename Node, typename IsReverse>
    void in_order_iterator<Node,IsReverse>::_initialize(::boost::mpl::true_)
    {
        while (this->base()->get_right_child_ptr())
        {
            this->base_reference() = this->base()->get_right_child_ptr();
        }
    }

    template <typename Node, typename IsReverse>
    void in_order_iterator<Node,IsReverse>::_increment(::boost::mpl::false_ tag)
    {
        typename ::boost::detail::metafunction::container_pointer<
            Node
        >::type node_ptr = this->base();

        if (node_ptr)
        {
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type other_ptr = node_ptr->get_right_child_ptr();

            if (other_ptr)
            {
                while (other_ptr->get_left_child_ptr())
                {
                    other_ptr = other_ptr->get_left_child_ptr();
                }

                this->base_reference() = other_ptr;
                return;
            }

            other_ptr = this->_root_ptr->get_parent_ptr();

            for (
                typename ::boost::detail::metafunction::container_pointer<
                    Node
                >::type next_ptr = node_ptr->get_parent_ptr();
                next_ptr != other_ptr;
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

            this->base_reference() = ::boost::initialized_value;
            this->_state = ::boost::tree_node::no_traversal;
        }
        else
        {
            BOOST_ASSERT_MSG(
                this->_root_ptr
              , "Do not decrement past-the-end of NULL!"
            );
            this->base_reference() = this->_root_ptr;
            this->_state = ::boost::tree_node::in_order_traversal;
            this->_initialize(tag);
        }
    }

    template <typename Node, typename IsReverse>
    void in_order_iterator<Node,IsReverse>::_increment(::boost::mpl::true_ tag)
    {
        typename ::boost::detail::metafunction::container_pointer<
            Node
        >::type node_ptr = this->base();

        if (node_ptr)
        {
            typename ::boost::detail::metafunction::container_pointer<
                Node
            >::type other_ptr = node_ptr->get_left_child_ptr();

            if (other_ptr)
            {
                while (other_ptr->get_right_child_ptr())
                {
                    other_ptr = other_ptr->get_right_child_ptr();
                }

                this->base_reference() = other_ptr;
                return;
            }

            other_ptr = this->_root_ptr->get_parent_ptr();

            for (
                typename ::boost::detail::metafunction::container_pointer<
                    Node
                >::type next_ptr = node_ptr->get_parent_ptr();
                next_ptr != other_ptr;
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

            this->base_reference() = ::boost::initialized_value;
            this->_state = ::boost::tree_node::no_traversal;
        }
        else
        {
            BOOST_ASSERT_MSG(
                this->_root_ptr
              , "Do not decrement past-the-end of NULL!"
            );
            this->base_reference() = this->_root_ptr;
            this->_state = ::boost::tree_node::in_order_traversal;
            this->_initialize(tag);
        }
    }

    template <typename Node, typename IsReverse>
    inline void in_order_iterator<Node,IsReverse>::increment()
    {
        BOOST_ASSERT_MSG(this->_state, "Do not increment past-the-end!");
        this->_increment(IsReverse());
    }

    template <typename Node, typename IsReverse>
    inline void in_order_iterator<Node,IsReverse>::decrement()
    {
        this->_increment(::boost::mpl::not_<IsReverse>());
    }

    template <typename Node, typename IsReverse>
    inline void
        in_order_iterator<Node,IsReverse>::advance(
            typename super_t::difference_type n
        )
    {
        if (!n)
        {
            return;
        }

        static typename super_t::difference_type const z = (
            ::boost::initialized_value
        );

        if (n < z)
        {
            if (this->_state)
            {
                BOOST_ASSERT_MSG(
                    IsReverse::value ? !(
                        get(*this->_root_ptr, count_key()) < binary_index_of(
                            this->base()
                          , -n
                          , this->_root_ptr
                        )
                    ) : !(
                        binary_index_of(this->base(), n, this->_root_ptr) < z
                    )
                  , "Index out of bounds."
                );
            }
            else
            {
                this->decrement();

                if (!++n)
                {
                    return;
                }
            }
        }

        if (
            !(
                this->base_reference() = advance_binary(
                    this->base()
                  , IsReverse::value ? -n : n
                  , this->_root_ptr
                )
            )
        )
        {
            this->_state = ::boost::tree_node::no_traversal;
        }
    }

    template <typename Node, typename IsReverse>
    template <typename N, typename I>
    inline
#if defined BOOST_NO_SFINAE
    typename in_order_iterator<Node,IsReverse>::super_t::difference_type
#else
    typename ::boost::enable_if<
        typename ::boost::mpl::if_<
            ::std::tr1::is_convertible<N,Node>
          , ::boost::mpl::equal_to<I,IsReverse>
          , ::boost::mpl::false_
        >::type
      , typename in_order_iterator<
            Node
          , IsReverse
        >::super_t::difference_type
    >::type
#endif
        in_order_iterator<Node,IsReverse>::distance_to(
            in_order_iterator<N,I> const& other
        ) const
    {
        BOOST_ASSERT_MSG(
            this->_root_ptr == other._root_ptr
          , "Iterators are unreachable from each other."
        );

        typename super_t::difference_type v = ::boost::initialized_value;

        if (this->_state)
        {
            if (other._state)
            {
                return IsReverse::value ? (
                    binary_index_of(this->base(), v, this->_root_ptr)
                  - binary_index_of(other.base(), v, other._root_ptr)
                ) : (
                    binary_index_of(other.base(), v, other._root_ptr)
                  - binary_index_of(this->base(), v, this->_root_ptr)
                );
            }
            else if (IsReverse::value)
            {
                v = binary_index_of(this->base(), v, this->_root_ptr);
                return ++v;
            }
            else
            {
                v = -binary_index_of(this->base(), v, this->_root_ptr);
                return (v += get(*this->_root_ptr, count_key()));
            }
        }
        else if (other._state)
        {
            if (IsReverse::value)
            {
                v = -binary_index_of(other.base(), v, other._root_ptr);
                return --v;
            }
            else
            {
                v = binary_index_of(other.base(), v, other._root_ptr);
                return (v -= get(*other._root_ptr, count_key()));
            }
        }
        else
        {
            return v;
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
        in_order_iterator<Node,IsReverse>::equal(
            in_order_iterator<N,I> const& other
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
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node> make_in_order_iterator(Node& node);

    //<-
    template <typename Node>
    inline in_order_iterator<Node> make_in_order_iterator(Node& node)
    {
        return in_order_iterator<Node>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_iterator_end
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node> make_in_order_iterator_end(Node* node_ptr);

    //<-
    template <typename Node>
    inline in_order_iterator<Node> make_in_order_iterator_end(Node* node_ptr)
    {
        return in_order_iterator<Node>(node_ptr);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_reverse_iterator
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node,::boost::mpl::true_>
        make_in_order_reverse_iterator(Node& node);

    //<-
    template <typename Node>
    inline in_order_iterator<Node,::boost::mpl::true_>
        make_in_order_reverse_iterator(Node& node)
    {
        return in_order_iterator<Node,::boost::mpl::true_>(node);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_reverse_iterator_end
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node,::boost::mpl::true_>
        make_in_order_reverse_iterator_end(Node* node_ptr);

    //<-
    template <typename Node>
    inline in_order_iterator<Node,::boost::mpl::true_>
        make_in_order_reverse_iterator_end(Node* node_ptr)
    {
        return in_order_iterator<Node,::boost::mpl::true_>(node_ptr);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__make_in_order_iterator_position
namespace boost { namespace tree_node {

    template <typename Node>
    in_order_iterator<Node> make_in_order_iterator_position(Node& node);

    //<-
    template <typename Node>
    inline in_order_iterator<Node> make_in_order_iterator_position(Node& node)
    {
        return in_order_iterator<Node>(node, false);
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ITERATOR_IN_ORDER_HPP

