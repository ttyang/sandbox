// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/with_red_black_flag_fwd.hpp>
#include <boost/tree_node/traits/red_black_node_fwd.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/tree_node/intrinsic/at_key.hpp>

#if !defined BOOST_CONTAINER_PERFECT_FORWARDING
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#include <boost/tree_node/_detail/config_begin.hpp>

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/mpl/vector.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/is_pod.hpp>

namespace boost {

    template <typename BaseGenerator, typename T1, typename T2>
    struct is_POD<
        ::boost::tree_node::with_red_black_flag<BaseGenerator,T1,T2>
    > : ::boost::false_type
    {
    };

    template <typename BaseGenerator, typename T1, typename T2>
    struct is_pod<
        ::boost::tree_node::with_red_black_flag<BaseGenerator,T1,T2>
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
    >
    class with_red_black_flag_base
      : public
        //[reference__with_red_black_flag_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      , public red_flag_key
      , public black_flag_key
#endif
      , private ::boost::noncopyable
    {
        friend struct tree_node_base<Derived>;

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
        bool _is_red;

     protected:
        //[reference__with_red_black_flag_base__derived_copy_ctor
        with_red_black_flag_base(Derived const& copy);
        //]

        //[reference__with_red_black_flag_base__derived_copy_ctor_w_allocator
        with_red_black_flag_base(
            Derived const& copy
          , typename traits::allocator_reference allocator
        );
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_red_black_flag_base(BOOST_RV_REF(Derived) source);

        with_red_black_flag_base(
            BOOST_RV_REF(Derived) source
          , typename traits::allocator_reference allocator
        );
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_red_black_flag_base__emplacement_ctor
        template <typename ...Args>
        explicit with_red_black_flag_base(Args&& ...args);
        //]

        //[reference__with_red_black_flag_base__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_red_black_flag_base(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO(z, n, Tuple)               \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _is_red(false)                                                   \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO
          , (with_red_black_flag_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO

#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO(z, n, Tuple)               \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_HEADER(z, n, Tuple)  \
          , _is_red(false)                                                   \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO
          , (with_red_black_flag_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~with_red_black_flag_base();

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        void copy_assign(Derived const& copy);
#else
        void copy_assign(BOOST_COPY_ASSIGN_REF(Derived) copy);

        void move_assign(BOOST_RV_REF(Derived) source);
#endif

        void on_post_copy_or_move();

     public:
        //[reference__with_red_black_flag_base__key_value_operator__red
        bool operator[](red_flag_key const&) const;
        //]

        //[reference__with_red_black_flag_base__key_value_operator__black
        bool operator[](black_flag_key const&) const;
        //]

        //[reference__with_red_black_flag_base__set_red_flag
        void set_red_flag(bool flag);
        //]

        //[reference__with_red_black_flag_base__set_black_flag
        void set_black_flag(bool flag);
        //]
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(Derived const& copy)
      : super_t(copy), _is_red(copy._is_red)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : super_t(copy, allocator), _is_red(copy._is_red)
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
    ) : super_t(source)
#else
        Derived&& source
    ) : super_t(static_cast<Derived&&>(source))
#endif
      , _is_red(source._is_red)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
      , typename traits::allocator_reference allocator
    ) : super_t(source, allocator)
#else
        Derived&& source
      , typename traits::allocator_reference allocator
    ) : super_t(static_cast<Derived&&>(source), allocator)
#endif
      , _is_red(source._is_red)
    {
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    template <typename ...Args>
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...), _is_red(false)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    template <typename ...Args>
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_red_black_flag_base(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : super_t(
            ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        )
      , _is_red(false)
    {
    }
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_red_black_flag_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::~with_red_black_flag_base()
    {
    }

#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::copy_assign(
            Derived const& copy
        )
#else  // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::move_assign(
            BOOST_RV_REF(Derived) source
        )
    {
#if defined BOOST_NO_RVALUE_REFERENCES
        super_t::move_assign(source);
#else
        super_t::move_assign(static_cast<Derived&&>(source));
#endif
        this->_is_red = source._is_red;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::copy_assign(
            BOOST_COPY_ASSIGN_REF(Derived) copy
        )
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    {
        super_t::copy_assign(copy);
        this->_is_red = copy._is_red;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::on_post_copy_or_move()
    {
        super_t::on_post_copy_or_move();
        this->on_post_modify_value(red_flag_key());
        this->on_post_modify_value(black_flag_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline bool
        with_red_black_flag_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::operator[](red_flag_key const&) const
    {
        return this->_is_red;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline bool
        with_red_black_flag_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::operator[](black_flag_key const&) const
    {
        return !this->_is_red;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::set_red_flag(
            bool flag
        )
    {
        this->_is_red = flag;
        this->on_post_modify_value(red_flag_key());
        this->on_post_modify_value(black_flag_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::set_black_flag(
            bool flag
        )
    {
        this->_is_red = !flag;
        this->on_post_modify_value(red_flag_key());
        this->on_post_modify_value(black_flag_key());
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , red_flag_key const& key
        )
    {
        return node[key];
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , black_flag_key const& key
        )
    {
        return node[key];
    }

#if !defined BOOST_NO_SFINAE
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,red_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node)
    {
        return node[red_flag_key()];
    }

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,black_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node)
    {
        return node[black_flag_key()];
    }
#endif  // BOOST_NO_SFINAE

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , red_flag_key const& key
          , bool value
        )
    {
        node.set_red_flag(value);
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , black_flag_key const& key
          , bool value
        )
    {
        node.set_black_flag(value);
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node { namespace result_of {

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    struct has_key_impl<
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>
      , red_flag_key
    > : ::boost::mpl::true_
    {
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    struct has_key_impl<
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>
      , black_flag_key
    > : ::boost::mpl::true_
    {
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    struct get_keys_impl<
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>
    > : ::boost::mpl::vector2<red_flag_key,black_flag_key>
    {
    };
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <>
    struct at_key_impl<red_flag_key>
    {
        template <typename Node>
        struct apply
        {
            typedef bool type;
        };
    };

    template <>
    struct at_key_impl<black_flag_key>
    {
        template <typename Node>
        struct apply
        {
            typedef bool type;
        };
    };
}}}  // namespace boost::tree_node::result_of

//[reference__with_red_black_flag_base_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_red_black_flag_base_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_red_black_flag_base<Derived,BaseGenerator,T1,T2> type;
        };
    };
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2>
    struct with_red_black_flag
      : public
        //[reference__with_red_black_flag__bases
        with_red_black_flag_base<
            with_red_black_flag<BaseGenerator,T1,T2>
          , BaseGenerator
          , T1
          , T2
        >
        //]
    {
        typedef with_red_black_flag_base<
                    with_red_black_flag
                  , BaseGenerator
                  , T1
                  , T2
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
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        typedef typename super_t::size_type
                size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_red_black_flag, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_red_black_flag__emplacement_ctor
        template <typename ...Args>
        explicit with_red_black_flag(Args&& ...args);
        //]

        //[reference__with_red_black_flag__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_red_black_flag(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_red_black_flag, super_t)
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF
          , (with_red_black_flag, super_t)
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename BaseGenerator, typename T1, typename T2>
    template <typename ...Args>
    inline with_red_black_flag<BaseGenerator,T1,T2>::with_red_black_flag(
        Args&& ...args
    ) : super_t(::boost::forward<Args>(args)...)
    {
        super_t::on_post_emplacement_construct();
    }

    template <typename BaseGenerator, typename T1, typename T2>
    template <typename ...Args>
    inline with_red_black_flag<BaseGenerator,T1,T2>::with_red_black_flag(
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

//[reference__with_red_black_flag_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_red_black_flag_gen
    {
        template <typename T1, typename T2 = void>
        struct apply
        {
            typedef with_red_black_flag<BaseGenerator,T1,T2> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

