// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED

#include <cstddef>
#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include <boost/tree_node/height_key.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#endif

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/move/move.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    class with_height_base
      : public
        //[reference__with_height_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
    {
        friend struct tree_node_base<Derived>;

        typedef with_height_base<Derived,BaseGenerator,T1,T2,Height>
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
        Height _height;

     protected:
        //[reference__with_height_base__derived_copy_ctor
        with_height_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_height_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_height_base__emplacement_ctor
        template <typename ...Args>
        explicit with_height_base(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_HEIGHT_MACRO(z, n, Tuple)                       \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _height(::boost::initialized_value)                              \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_HEIGHT_MACRO
          , (with_height_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_HEIGHT_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~with_height_base();

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        void copy_assign(Derived const& copy);
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

        void on_post_copy_or_move();

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
        //[reference__with_height_base__key_value_operator
        Height const& operator[](height_key const&) const;
        //]

     private:
        void _shallow_update();

        static Height
            _get_max_height(const_iterator c_itr, const_iterator c_end);

        static void _update_less_height(pointer p);

        static void _update_greater_height(pointer p);
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::with_height_base(
        Derived const& copy
    ) : super_t(copy), _height(copy._height)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::with_height_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
    ) : super_t(source)
#else
        Derived&& source
    ) : super_t(static_cast<Derived&&>(source))
#endif
      , _height(source._height)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    template <typename ...Args>
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::with_height_base(
        Args&& ...args
    ) : super_t(::boost::forward<Args>(args)...)
      , _height(::boost::initialized_value)
    {
    }
#endif

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::~with_height_base()
    {
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<Derived,BaseGenerator,T1,T2,Height>::copy_assign(
            Derived const& copy
        )
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<Derived,BaseGenerator,T1,T2,Height>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        super_t::move_assign(source);
#else
        super_t::move_assign(static_cast<Derived&&>(source));
#endif
//        this->_height = source._height;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<Derived,BaseGenerator,T1,T2,Height>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    {
        super_t::copy_assign(copy);
//        this->_height = copy._height;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_copy_or_move()
    {
        super_t::on_post_copy_or_move();
        this->_shallow_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    template <typename BooleanIntegralConstant>
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_inserted_impl(
            iterator position
          , BooleanIntegralConstant invalidates_sibling_positions
        )
    {
        super_t::on_post_inserted_impl(
            position
          , invalidates_sibling_positions
        );
        this->get_parent_ptr()->_shallow_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_erase_impl()
    {
        super_t::on_post_erase_impl();
        this->_shallow_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_clear_impl()
    {
        super_t::on_post_clear_impl();
        this->_height = ::boost::initialized_value;
        self::_update_less_height(this->get_derived());
        this->on_post_propagate_value(height_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_rotate_left_impl()
    {
        super_t::on_post_rotate_left_impl();
        this->_shallow_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::on_post_rotate_right_impl()
    {
        super_t::on_post_rotate_right_impl();
        this->_shallow_update();
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline Height const&
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::operator[](height_key const&) const
    {
        return this->_height;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    void
        with_height_base<Derived,BaseGenerator,T1,T2,Height>::_shallow_update()
    {
        Height new_height = self::_get_max_height(this->begin(), this->end());

        if (new_height < this->_height)
        {
            this->_height = new_height;
            self::_update_less_height(this->get_derived());
            this->on_post_propagate_value(height_key());
        }
        else if (this->_height < new_height)
        {
            this->_height = new_height;
            self::_update_greater_height(this->get_derived());
            this->on_post_propagate_value(height_key());
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    Height
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::_get_max_height(const_iterator c_itr, const_iterator c_end)
    {
        Height result = ::boost::initialized_value;

        for (Height height_plus_1; c_itr != c_end; ++c_itr)
        {
            height_plus_1 = ::boost::tree_node::dereference_iterator(
                c_itr
            )._height;

            if (result < ++height_plus_1)
            {
                result = height_plus_1;
            }
        }

        return result;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::_update_less_height(pointer p)
    {
        Height new_height;

        while ((p = p->get_parent_ptr()))
        {
            new_height = self::_get_max_height(p->begin(), p->end());

            if (p->_height == new_height)
            {
                return;
            }
            else
            {
                // This is no longer the deepest branch.
                p->_height = new_height;
            }
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    void
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::_update_greater_height(pointer p)
    {
        Height p_height = p->_height;

        while ((p = p->get_parent_ptr()) && (p->_height < ++p_height))
        {
            // This is the new deepest branch.
            p->_height = p_height;
        }
    }
}}  // namespace boost::tree_node

//[reference__with_height_base__get
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    Height const&
        get(
            with_height_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Height
            > const& node
          , height_key const& key
        );

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline Height const&
        get(
            with_height_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Height
            > const& node
          , height_key const& key
        )
    {
        return node[key];
    }
    //->
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_SFINAE
//[reference__with_height_base__get__key
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,height_key>
      , Height const&
    >::type
        get(
            with_height_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Height
            > const& node
        );

    //<-
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,height_key>
      , Height const&
    >::type
        get(
            with_height_base<
                Derived
              , BaseGenerator
              , T1
              , T2
              , Height
            > const& node
        )
    {
        return node[height_key()];
    }
    //->
}}  // namespace boost::tree_node
//]
#endif  // BOOST_NO_SFINAE

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    struct has_key_impl<
        with_height_base<Derived,BaseGenerator,T1,T2,Height>
      , height_key
    > : ::boost::mpl::true_
    {
    };
}}  // namespace boost::tree_node
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename Height = ::std::size_t
    >
    struct with_height
      : public
        //[reference__with_height__bases
        with_height_base<
            with_height<BaseGenerator,T1,T2,Height>
          , BaseGenerator
          , T1
          , T2
          , Height
        >
        //]
    {
        typedef with_height_base<with_height,BaseGenerator,T1,T2,Height>
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

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_height, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_height__emplacement_ctor
        template <typename ...Args>
        explicit with_height(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_height, super_t)
        )
#endif
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    template <typename ...Args>
    inline with_height<BaseGenerator,T1,T2,Height>::with_height(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
        super_t::on_post_emplacement_construct();
    }
#endif
}}  // namespace boost::tree_node

//[reference__with_height_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename Height = ::std::size_t>
    struct with_height_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_height_base<Derived,BaseGenerator,T1,T2,Height> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED

