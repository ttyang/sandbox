// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED

#include <boost/config.hpp>

#if defined BOOST_NO_SFINAE
#error boost::tree_node::with_accumulation requires working boost::enable_if.
#endif

#include <boost/typeof/typeof.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/get_reference.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/accumulation_key.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

#include <boost/assert.hpp>

namespace boost { namespace tree_node { namespace _detail {

    template <typename Value>
    struct choose_accumulation_value
    {
        template <typename Node, typename Key>
        struct apply
        {
            typedef Value type;
        };
    };

    template <>
    struct choose_accumulation_value<void>
    {
        template <typename Node, typename Key>
        struct apply
        {
            typedef BOOST_TYPEOF_TPL(
                        get<Key>(::boost::get_reference<Node const>())
                    )
                    type;
        };
    };
}}}  // namespace boost::tree_node::_detail

#include <boost/tree_node/_detail/config_begin.hpp>

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
        typedef typename super_t::size_type
                size_type;

     private:
        typedef typename ::boost::mpl::apply_wrap2<
                    _detail::choose_accumulation_value<
                        Value
                    >
                  , super_t
                  , Key
                >::type
                //->
                AccumulationValue;

        AccumulationValue _accumulation;

     protected:
        //[reference__with_accumulation_base__derived_copy_ctor
        with_accumulation_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_accumulation_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_accumulation_base__emplacement_ctor
        template <typename ...Args>
        explicit with_accumulation_base(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_ACCUMULATION_MACRO(z, n, Tuple)                 \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _accumulation(                                                   \
            ::boost::accumulators::extractor<Tag>()(                         \
                ::boost::accumulators::accumulator_set<                      \
                    AccumulationValue                                        \
                  , ::boost::accumulators::features<Tag>                     \
                >()                                                          \
            )                                                                \
        )                                                                    \
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

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        void copy_assign(Derived const& copy);
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

        void on_post_emplacement_construct();

        void on_post_copy_or_move();

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

        void on_post_erase_impl();

        void on_post_clear_impl();

        void on_post_rotate_left_impl();

        void on_post_rotate_right_impl();

     public:
        //[reference__with_accumulation_base__key_value_operator
        //<-
#if 0
        //->
        typename ::boost::mpl::if_<
            ::std::tr1::is_void<Value>
          , BOOST_TYPEOF_TPL(get<Key>(static_cast<super_t const&>(*this)))
          , Value
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
      , _accumulation(
            static_cast<self const&>(copy)[
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            ]
        )
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
      , _accumulation(
            static_cast<self&&>(source)[
                accumulation_key<
                    Key
                  , Tag
                  , IncludesAllDescendants
                  , IncludesRoot
                  , Value
                >()
            ]
        )
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
      : super_t(::boost::forward<Args>(args)...)
      , _accumulation(
            ::boost::accumulators::extractor<Tag>()(
                ::boost::accumulators::accumulator_set<
                    AccumulationValue
                  , ::boost::accumulators::features<Tag>
                >()
            )
        )
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
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_accumulation_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Key
          , Tag
          , IncludesRoot
          , Value
        >::copy_assign(Derived const& copy)
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
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
        >::move_assign(BOOST_RV_REF(Derived) source)
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        super_t::move_assign(source);
#else
        super_t::move_assign(static_cast<Derived&&>(source));
#endif
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
        >::copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy)
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    {
        super_t::copy_assign(copy);
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
        >::on_post_emplacement_construct()
    {
        super_t::on_post_emplacement_construct();

        if (IncludesRoot::value)
        {
            self::_accumulation = get<Key>(*this->get_derived());
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
        >::on_post_copy_or_move()
    {
        super_t::on_post_copy_or_move();
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

#if 0
//[reference__with_accumulation_base__get
namespace boost { namespace tree_node {

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
    typename ::boost::mpl::if_<
        ::std::tr1::is_void<Value>
      , BOOST_TYPEOF_TPL(
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
        )
      , Value
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
        );
}}  // namespace boost::tree_node
//]
#endif

namespace boost { namespace tree_node {

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
    inline typename ::boost::lazy_enable_if<
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , ::boost::mpl::apply_wrap2<
            _detail::choose_accumulation_value<Value>
          , typename with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >::super_t
          , Key
        >
    >::type const&
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
        ::std::tr1::is_same<
            accumulation_key<Key,Tag,IncludesAllDescendants,IncludesRoot,Value>
          , AccumulationKey
        >
      , ::boost::mpl::apply_wrap2<
            _detail::choose_accumulation_value<Value>
          , typename with_accumulation_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Key
              , Tag
              , IncludesAllDescendants
              , IncludesRoot
              , Value
            >::super_t
          , Key
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
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename AccumulationKey = accumulation_key<>
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
        typedef typename super_t::size_type
                size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_accumulation, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_accumulation__emplacement_ctor
        template <typename ...Args>
        explicit with_accumulation(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_accumulation, super_t)
        )
#endif
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
#endif
}}  // namespace boost::tree_node

//[reference__with_accumulation_gen
namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename AccumulationKey = accumulation_key<>
    >
    struct with_accumulation_gen
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

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_ACCUMULATION_HPP_INCLUDED

