// Copyright (C) 2012-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED

#include <boost/mpl/apply_wrap.hpp>
#include <boost/noncopyable.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/with_accumulation_fwd.hpp>
#include <boost/tree_node/key/accumulation.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/tree_node/intrinsic/at_key.hpp>
#include <boost/tree_node/iterator/breadth_first_descendant.hpp>
#include <boost/tree_node/iterator/dereference.hpp>
#include <boost/assert.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/mpl/vector.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/is_pod.hpp>

namespace boost {

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename AccumulationKey
    >
    struct is_POD<
        ::boost::tree_node::with_accumulation<
            BaseGenerator
          , T1
          , T2
          , AccumulationKey
        >
    > : ::boost::false_type
    {
    };

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename AccumulationKey
    >
    struct is_pod<
        ::boost::tree_node::with_accumulation<
            BaseGenerator
          , T1
          , T2
          , AccumulationKey
        >
    > : ::boost::false_type
    {
    };
}  // namespace boost
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    class with_accumulation_base
      : public
        //[reference__with_accumulation_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      , public accumulation_key<
            Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >
#endif
      , private ::boost::noncopyable
    {
        friend struct tree_node_base<Derived>;

        typedef with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
                self;

     public:
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_void<T2>
                  , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
                  , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
                >::type
                super_t;
        typedef typename super_t::traits
                traits;
        typedef typename super_t::pointer
                pointer;
        typedef typename super_t::const_pointer
                const_pointer;
        typedef typename super_t::iterator
                iterator;
        typedef typename super_t::const_iterator
                const_iterator;
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        typedef typename super_t::size_type
                size_type;

     private:
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_void<Value>
                  , result_of::value_at_key<self,Key>
                  , ::boost::mpl::identity<Value>
                >::type
                AccumulationValue;

        AccumulationValue _accumulation;

     protected:
        //[reference__with_accumulation_base__derived_copy_ctor
        with_accumulation_base(Derived const& copy);
        //]

        //[reference__with_accumulation_base__derived_copy_ctor_w_allocator
        with_accumulation_base(
            Derived const& copy
          , typename traits::allocator_reference allocator
        );
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_accumulation_base(BOOST_RV_REF(Derived) source);

        with_accumulation_base(
            BOOST_RV_REF(Derived) source
          , typename traits::allocator_reference allocator
        );
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_accumulation_base__emplacement_ctor
        template <typename ...Args>
        explicit with_accumulation_base(Args&& ...args);
        //]

        //[reference__with_accumulation_base__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_accumulation_base(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO(z, n, Tuple)                 \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _accumulation()                                                  \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO
          , (with_accumulation_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO

#define BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO(z, n, Tuple)                 \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_HEADER(z, n, Tuple)  \
          , _accumulation()                                                  \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO
          , (with_accumulation_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~with_accumulation_base();

        void clone_metadata_impl(Derived const& copy);

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        void move_metadata_impl(BOOST_RV_REF(Derived) source);
#endif

        void on_post_emplacement_construct();

        void on_post_assign();

        template <typename K>
        void on_post_modify_value_impl(K const& key);

        void on_post_modify_value_impl(Key const& key);

        template <typename K>
        void on_post_propagate_value_impl(K const& key);

        void on_post_propagate_value_impl(Key const& key);

        template <typename K>
        void on_post_propagate_value_once_impl(K const& key);

        void on_post_propagate_value_once_impl(Key const& key);

        template <typename BooleanIntegralConstant>
        void
            on_post_inserted_impl(
                iterator position
              , BooleanIntegralConstant invalidates_sibling_positions
            );

        template <typename BooleanIntegralConstant>
        void
            on_post_insert_impl(
                iterator itr
              , iterator itr_end
              , BooleanIntegralConstant invalidates_children_positions
            );

        void on_post_erase_impl();

        void on_post_clear_impl();

        void on_post_rotate_left_impl();

        void on_post_rotate_right_impl();

     public:
        //[reference__with_accumulation_base__key_value_operator
//<-
#if 0
//->
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_void<Value>
          , result_of::value_at_key<
                with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
              , Key
            >
          , ::boost::mpl::identity<Value>
        >::type const&
//<-
#endif
        AccumulationValue const&
//->
            operator[](
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                > const&
            )
            const;
        //]

     private:
        void
            _set_accumulation(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                > const&
            );

        void _update();

        static void
            _update(
                pointer p
              , accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                > const&
            );
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(Derived const& copy)
      : super_t(copy)
      , _accumulation(static_cast<self const&>(copy)._accumulation)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : super_t(copy, allocator)
      , _accumulation(static_cast<self const&>(copy)._accumulation)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
    ) : super_t(source)
#else
        Derived&& source
    ) : super_t(static_cast<Derived&&>(source))
#endif
      , _accumulation(static_cast<self&>(source)._accumulation)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
      , typename traits::allocator_reference allocator
    ) : super_t(source, allocator)
#else
        Derived&& source
      , typename traits::allocator_reference allocator
    ) : super_t(static_cast<Derived&&>(source), allocator)
#endif
      , _accumulation(static_cast<self&>(source)._accumulation)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename ...Args>
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...), _accumulation()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename ...Args>
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::with_accumulation_base(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : super_t(
            ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        )
      , _accumulation()
    {
    }
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::~with_accumulation_base()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::clone_metadata_impl(Derived const& copy)
    {
        super_t::clone_metadata_impl(copy);
        this->_accumulation = static_cast<self const&>(copy)._accumulation;
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::move_metadata_impl(BOOST_RV_REF(Derived) source)
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        super_t::move_metadata_impl(source);
#else
        super_t::move_metadata_impl(static_cast<Derived&&>(source));
#endif
        this->_accumulation = ::boost::move(
            static_cast<self&>(source)._accumulation
        );
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_emplacement_construct()
    {
        super_t::on_post_emplacement_construct();
        self::_accumulation = IncludesRoot::value ? get<Key>(
            *this->get_derived()
        ) : ::boost::accumulators::extractor<Tag>()(
            ::boost::accumulators::accumulator_set<
                AccumulationValue
              , ::boost::accumulators::features<Tag>
            >()
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_assign()
    {
        super_t::on_post_assign();

        if (IncludesRoot::value)
        {
            this->_update();
        }
        else if (pointer p = this->get_parent_ptr())
        {
            static_cast<self*>(p)->_update();
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename K>
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_modify_value_impl(K const& key)
    {
        super_t::on_post_modify_value_impl(key);
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_modify_value_impl(Key const& key)
    {
        super_t::on_post_modify_value_impl(key);

        if (IncludesRoot::value)
        {
            this->_set_accumulation(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
            this->on_post_modify_value(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
        }

        if (pointer p = this->get_parent_ptr())
        {
            static_cast<self*>(p)->_set_accumulation(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
            p->on_post_modify_value(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename K>
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_propagate_value_impl(K const& key)
    {
        super_t::on_post_propagate_value_impl(key);
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_propagate_value_impl(Key const& key)
    {
        super_t::on_post_propagate_value_impl(key);

        if (IncludesRoot::value)
        {
            this->_update();
        }
        else if (pointer p = this->get_parent_ptr())
        {
            static_cast<self*>(p)->_update();
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename K>
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_propagate_value_once_impl(K const& key)
    {
        super_t::on_post_propagate_value_once_impl(key);
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_propagate_value_once_impl(Key const& key)
    {
        super_t::on_post_propagate_value_once_impl(key);

        if (IncludesRoot::value)
        {
            this->_set_accumulation(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
        }

        self* p = this->get_parent_ptr();

        BOOST_ASSERT_MSG(
            p
          , "Do not call on_post_propagate_value_once() on root."
        );
        p->_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );

        if ((p = p->get_parent_ptr()))
        {
            p->_set_accumulation(
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            );
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename BooleanIntegralConstant>
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_inserted_impl(
            iterator position
          , BooleanIntegralConstant invalidates_sibling_positions
        )
    {
        super_t::on_post_inserted_impl(
            position
          , invalidates_sibling_positions
        );
        static_cast<self*>(this->get_parent_ptr())->_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    template <typename BooleanIntegralConstant>
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_insert_impl(
            iterator itr
          , iterator itr_end
          , BooleanIntegralConstant invalidates_children_positions
        )
    {
        super_t::on_post_insert_impl(
            itr
          , itr_end
          , invalidates_children_positions
        );
        this->_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_erase_impl()
    {
        super_t::on_post_erase_impl();
        this->_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_clear_impl()
    {
        super_t::on_post_clear_impl();
        this->_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_rotate_left_impl()
    {
        super_t::on_post_rotate_left_impl();
        this->_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
        static_cast<self*>(this->get_parent_ptr())->_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
        this->on_post_propagate_value_once(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::on_post_rotate_right_impl()
    {
        super_t::on_post_rotate_right_impl();
        this->_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
        static_cast<self*>(this->get_parent_ptr())->_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
        this->on_post_propagate_value_once(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename with_accumulation_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Key
      , Tag
      , IncludesAllDescendants
      , IncludesRoot
      , Value
    >::AccumulationValue const&
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::operator[](
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const&
        ) const
    {
        return self::_accumulation;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::_set_accumulation(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const&
        )
    {
        ::boost::accumulators::accumulator_set<
            AccumulationValue
          , ::boost::accumulators::features<Tag>
        > acc;

        if (IncludesRoot::value)
        {
            acc(get<Key>(*this->get_derived()));
        }

        if (IncludesAllDescendants::value)
        {
            for (
                ::boost::tree_node::breadth_first_descendant_iterator<
                    Derived const
                > c_itr(*this->get_derived());
                c_itr;
                ++c_itr
            )
            {
                acc(get<Key>(::boost::tree_node::dereference_iterator(c_itr)));
            }
        }
        else
        {
            const_iterator c_end = this->end();

            for (const_iterator c_itr = this->begin(); c_itr != c_end; ++c_itr)
            {
                acc(get<Key>(::boost::tree_node::dereference_iterator(c_itr)));
            }
        }

        self::_accumulation = ::boost::accumulators::extractor<
            Tag
        >()(acc);
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::_update()
    {
        self::_update(
            this->get_derived()
          , accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
        this->on_post_propagate_value(
            accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >()
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    void
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >::_update(
            pointer p
          , accumulation_key<
                Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& key
        )
    {
        do
        {
            static_cast<self*>(p)->_set_accumulation(key);
        }
        while ((p = p->get_parent_ptr()));
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename AccumulationKey
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , typename ::boost::mpl::eval_if<
            ::std::tr1::is_void<Value>
          , result_of::value_at_key<
                with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
              , Key
            >
          , ::boost::mpl::identity<Value>
        >::type const&
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
          , AccumulationKey const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename AccumulationKey
    >
    inline typename ::boost::lazy_disable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,AccumulationKey>
          , ::std::tr1::is_same<
                accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
              , AccumulationKey
            >
          , ::boost::mpl::true_
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , AccumulationKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
          , AccumulationKey const& key
        )
    {
        return get(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
          , key
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename ExplicitKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::boost::mpl::eval_if<
                ::std::tr1::is_same<ExplicitKey,Key>
              , ::boost::mpl::false_
              , result_of::has_key<
                    with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , Key
                      , Tag
                      , IncludesAllDescendants
                      , IncludesRoot
                      , Value
                    >
                  , ExplicitKey
                >
            >
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
          , ExplicitKey const& key
        )
    {
        return get(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
          , key
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename ExplicitKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::boost::mpl::eval_if<
                ::std::tr1::is_same<ExplicitKey,Key>
              , ::boost::mpl::false_
              , result_of::has_key<
                    with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , Key
                      , Tag
                      , IncludesAllDescendants
                      , IncludesRoot
                      , Value
                    >
                  , ExplicitKey
                >
            >
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >& node
          , ExplicitKey const& key
        )
    {
        return get(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t&
            >(node)
          , key
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename ExplicitKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::std::tr1::is_same<ExplicitKey,Key>
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
          , ExplicitKey const& key
        )
    {
        return get(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
          , key
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
      , typename ExplicitKey
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::std::tr1::is_same<ExplicitKey,Key>
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >& node
          , ExplicitKey const& key
        )
    {
        return get(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t&
            >(node)
          , key
        );
    }

    template <
        typename AccumulationKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , typename ::boost::mpl::eval_if<
            ::std::tr1::is_void<Value>
          , result_of::value_at_key<
                with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >
              , Key
            >
          , ::boost::mpl::identity<Value>
        >::type const&
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
        )
    {
        return node[AccumulationKey()];
    }

    template <
        typename AccumulationKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::lazy_disable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,AccumulationKey>
          , ::std::tr1::is_same<
                accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
              , AccumulationKey
            >
          , ::boost::mpl::true_
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , AccumulationKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
        )
    {
        return get<AccumulationKey>(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
        );
    }

    template <
        typename ExplicitKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::boost::mpl::eval_if<
                ::std::tr1::is_same<ExplicitKey,Key>
              , ::boost::mpl::false_
              , result_of::has_key<
                    with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , Key
                      , Tag
                      , IncludesAllDescendants
                      , IncludesRoot
                      , Value
                    >
                  , ExplicitKey
                >
            >
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
        )
    {
        return get<ExplicitKey>(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
        );
    }

    template <
        typename ExplicitKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::boost::mpl::eval_if<
                ::std::tr1::is_same<ExplicitKey,Key>
              , ::boost::mpl::false_
              , result_of::has_key<
                    with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , Key
                      , Tag
                      , IncludesAllDescendants
                      , IncludesRoot
                      , Value
                    >
                  , ExplicitKey
                >
            >
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >& node
        )
    {
        return get<ExplicitKey>(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t&
            >(node)
        );
    }

    template <
        typename ExplicitKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::std::tr1::is_same<ExplicitKey,Key>
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            > const& node
        )
    {
        return get<Key>(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t const&
            >(node)
        );
    }

    template <
        typename ExplicitKey
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    inline typename ::boost::lazy_enable_if<
        typename ::boost::mpl::eval_if<
            ::std::tr1::is_base_of<accumulation_key_base,ExplicitKey>
          , ::boost::mpl::false_
          , ::std::tr1::is_same<ExplicitKey,Key>
        >::type
      , result_of::value_at_key<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
          , ExplicitKey
        >
    >::type
        get(
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >& node
        )
    {
        return get<Key>(
            static_cast<
                typename with_accumulation_base<
                    Derived
                  , BaseGenerator
                  , T1
                  , T2
                  , Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >::super_t&
            >(node)
        );
    }
}}  // namespace boost::tree_node

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost { namespace tree_node { namespace result_of {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    struct has_key_impl<
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >
      , accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
    > : ::boost::mpl::true_
    {
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    struct get_keys_impl<
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesAllDescendants
          , IncludesRoot
          , Value
        >
    > : ::boost::mpl::vector1<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
        >
    {
    };

    template <
        typename Key
      , typename Tag
      , typename IncludesAllDescendants
      , typename IncludesRoot
      , typename Value
    >
    struct at_key_impl<
        accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
    >
    {
        template <typename Node>
        struct apply : apply<typename Node::super_t>
        {
        };

        template <
            typename Derived
          , typename BaseGenerator
          , typename T1
          , typename T2
        >
        struct apply<
            with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >
        > : ::boost::mpl::eval_if<
                ::std::tr1::is_void<Value>
              , value_at_key<
                    with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , Key
                      , Tag
                      , IncludesAllDescendants
                      , IncludesRoot
                      , Value
                    >
                  , Key
                >
              , ::boost::mpl::identity<Value>
            >
        {
        };
    };
}}}  // namespace boost::tree_node::result_of
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

//[reference__with_accumulation_base_gen
namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename AccumulationKey = default_accumulation_key
    >
    struct with_accumulation_base_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_accumulation_base<
                        Derived
                      , BaseGenerator
                      , T1
                      , T2
                      , typename AccumulationKey::key
                      , typename AccumulationKey::tag
                      , typename AccumulationKey::includes_all_descendants
                      , typename AccumulationKey::includes_root
                      , typename AccumulationKey::value
                    >
                    type;
        };
    };
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename AccumulationKey
    >
    struct with_accumulation
      : public
        //[reference__with_accumulation__bases
        with_accumulation_base<
            with_accumulation<
                BaseGenerator
              , T1
              , T2
              , AccumulationKey
            >
          , BaseGenerator
          , T1
          , T2
          , typename AccumulationKey::key
          , typename AccumulationKey::tag
          , typename AccumulationKey::includes_all_descendants
          , typename AccumulationKey::includes_root
          , typename AccumulationKey::value
        >
        //]
    {
        //[reference__with_accumulator__super_t
        typedef with_accumulation_base<
                    with_accumulation
                  , BaseGenerator
                  , T1
                  , T2
                  , typename AccumulationKey::key
                  , typename AccumulationKey::tag
                  , typename AccumulationKey::includes_all_descendants
                  , typename AccumulationKey::includes_root
                  , typename AccumulationKey::value
                >
                super_t;
        //]

        typedef typename super_t::traits
                traits;
        typedef typename super_t::pointer
                pointer;
        typedef typename super_t::const_pointer
                const_pointer;
        typedef typename super_t::iterator
                iterator;
        typedef typename super_t::const_iterator
                const_iterator;
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        typedef typename super_t::size_type
                size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_accumulation, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_accumulation__emplacement_ctor
        template <typename ...Args>
        explicit with_accumulation(Args&& ...args);
        //]

        //[reference__with_accumulation__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_accumulation(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_accumulation, super_t)
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF
          , (with_accumulation, super_t)
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename AccumulationKey
    >
    template <typename ...Args>
    inline with_accumulation<
        BaseGenerator
      , T1
      , T2
      , AccumulationKey
    >::with_accumulation(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
        super_t::on_post_emplacement_construct();
    }

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename AccumulationKey
    >
    template <typename ...Args>
    inline with_accumulation<
        BaseGenerator
      , T1
      , T2
      , AccumulationKey
    >::with_accumulation(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : super_t(
            ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        )
    {
        super_t::on_post_emplacement_construct();
    }
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
}}  // namespace boost::tree_node

//[reference__with_accumulation_gen
namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename AccumulationKey = default_accumulation_key
    >
    struct with_accumulation_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_accumulation<BaseGenerator,T1,T2,AccumulationKey>
                    type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED

