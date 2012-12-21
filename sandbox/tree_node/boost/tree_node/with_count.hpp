// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_COUNT_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_COUNT_HPP_INCLUDED

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
#include <boost/tree_node/count_key.hpp>

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
      , typename Count
    >
    class with_count_base
      : public
        //[reference__with_count_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
    {
        friend struct tree_node_base<Derived>;

        typedef with_count_base<Derived,BaseGenerator,T1,T2,Count>
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
        Count _count;

     protected:
        //[reference__with_count_base__derived_copy_ctor
        with_count_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_count_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_count_base__emplacement_ctor
        template <typename ...Args>
        explicit with_count_base(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_COUNT_MACRO(z, n, Tuple)                        \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _count(::boost::initialized_value)                               \
        {                                                                    \
            ++this->_count;                                                  \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_COUNT_MACRO
          , (with_count_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_COUNT_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~with_count_base();

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
        //[reference__with_count_base__key_value_operator
        Count const& operator[](count_key const&) const;
        //]

     private:
        void _shallow_update();

        static Count _get_count(const_iterator c_itr, const_iterator c_end);

        static void _update_less_count(pointer p, Count const& difference);

        static void _update_greater_count(pointer p, Count const& difference);
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    with_count_base<Derived,BaseGenerator,T1,T2,Count>::with_count_base(
        Derived const& copy
    ) : super_t(copy), _count(copy._count)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    with_count_base<Derived,BaseGenerator,T1,T2,Count>::with_count_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
    ) : super_t(source)
#else
        Derived&& source
    ) : super_t(static_cast<Derived&&>(source))
#endif
      , _count(source._count)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    template <typename ...Args>
    with_count_base<Derived,BaseGenerator,T1,T2,Count>::with_count_base(
        Args&& ...args
    ) : super_t(::boost::forward<Args>(args)...)
      , _count(::boost::initialized_value)
    {
        ++this->_count;
    }
#endif

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    with_count_base<Derived,BaseGenerator,T1,T2,Count>::~with_count_base()
    {
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<Derived,BaseGenerator,T1,T2,Count>::copy_assign(
            Derived const& copy
        )
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<Derived,BaseGenerator,T1,T2,Count>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        super_t::move_assign(source);
#else
        super_t::move_assign(static_cast<Derived&&>(source));
#endif
//        this->_count = source._count;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<Derived,BaseGenerator,T1,T2,Count>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    {
        super_t::copy_assign(copy);
//        this->_count = copy._count;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
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
      , typename Count
    >
    template <typename BooleanIntegralConstant>
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::on_post_inserted_impl(
            iterator position
          , BooleanIntegralConstant invalidates_sibling_positions
        )
    {
        super_t::on_post_inserted_impl(
            position
          , invalidates_sibling_positions
        );
        self::_update_greater_count(this->get_derived(), this->_count);
        this->on_post_propagate_value(count_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
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
      , typename Count
    >
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::on_post_clear_impl()
    {
        super_t::on_post_clear_impl();
        self::_update_less_count(this->get_derived(), --this->_count);
        ++(this->_count = ::boost::initialized_value);
        this->on_post_propagate_value(count_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::on_post_rotate_left_impl()
    {
        super_t::on_post_rotate_left_impl();

        pointer p = this->get_parent_ptr();

        if (p->get_right_child_ptr())
        {
            this->_count -= p->get_right_child_ptr()->_count;
        }

        if (this->get_left_child_ptr())
        {
            p->_count += this->get_left_child_ptr()->_count;
        }

        --this->_count;
        ++p->_count;
        this->on_post_propagate_value_once(count_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::on_post_rotate_right_impl()
    {
        super_t::on_post_rotate_right_impl();

        pointer p = this->get_parent_ptr();

        if (pointer l = p->get_left_child_ptr())
        {
            this->_count -= p->get_left_child_ptr()->_count;
        }

        if (this->get_right_child_ptr())
        {
            p->_count += this->get_right_child_ptr()->_count;
        }

        --this->_count;
        ++p->_count;
        this->on_post_propagate_value_once(count_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline Count const&
        with_count_base<Derived,BaseGenerator,T1,T2,Count>::operator[](
            count_key const&
        ) const
    {
        return this->_count;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    void with_count_base<Derived,BaseGenerator,T1,T2,Count>::_shallow_update()
    {
        Count new_count = self::_get_count(this->begin(), this->end());

        if (++new_count < this->_count)
        {
            self::_update_less_count(
                this->get_derived()
              , this->_count - new_count
            );
            this->_count = new_count;
            this->on_post_propagate_value(count_key());
        }
        else if (this->_count < new_count)
        {
            self::_update_greater_count(
                this->get_derived()
              , new_count - this->_count
            );
            this->_count = new_count;
            this->on_post_propagate_value(count_key());
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    Count
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::_get_count(const_iterator c_itr, const_iterator c_end)
    {
        Count result = ::boost::initialized_value;

        while (c_itr != c_end)
        {
            result += ::boost::tree_node::dereference_iterator(
                c_itr
            )._count;
            ++c_itr;
        }

        return result;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::_update_less_count(pointer p, Count const& difference)
    {
        while ((p = p->get_parent_ptr()))
        {
            p->_count -= difference;
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    void
        with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::_update_greater_count(pointer p, Count const& difference)
    {
        while ((p = p->get_parent_ptr()))
        {
            p->_count += difference;
        }
    }
}}  // namespace boost::tree_node

//[reference__with_count_base__get
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    Count const&
        get(
            with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node
          , count_key const& key
        );

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline Count const&
        get(
            with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node
          , count_key const& key
        )
    {
        return node[key];
    }
    //->
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_SFINAE
//[reference__with_count_base__get__key
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,count_key>
      , Count const&
    >::type
        get(with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node);

    //<-
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,count_key>
      , Count const&
    >::type
        get(with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node)
    {
        return node[count_key()];
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
      , typename Count
    >
    struct has_key_impl<
        with_count_base<Derived,BaseGenerator,T1,T2,Count>
      , count_key
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
      , typename Count = ::std::size_t
    >
    struct with_count
      : public
        //[reference__with_count__bases
        with_count_base<
            with_count<BaseGenerator,T1,T2,Count>
          , BaseGenerator
          , T1
          , T2
          , Count
        >
        //]
    {
        typedef with_count_base<with_count,BaseGenerator,T1,T2,Count> super_t;
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;
        typedef typename super_t::size_type size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_count, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_count__emplacement_ctor
        template <typename ...Args>
        explicit with_count(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_count, super_t)
        )
#endif
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename BaseGenerator, typename T1, typename T2, typename Count>
    template <typename ...Args>
    inline with_count<BaseGenerator,T1,T2,Count>::with_count(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
        super_t::on_post_emplacement_construct();
    }
#endif
}}  // namespace boost::tree_node

//[reference__with_count_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename Count = ::std::size_t>
    struct with_count_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_count_base<Derived,BaseGenerator,T1,T2,Count> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_COUNT_HPP_INCLUDED

