// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/red_flag_key.hpp>
#include <boost/tree_node/black_flag_key.hpp>

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

//[reference__with_red_black_flag_base__put__red
namespace boost { namespace tree_node {

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    class with_red_black_flag_base;
    //->

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , red_flag_key const& key
          , bool value
        );
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__put__black
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , black_flag_key const& key
          , bool value
        );
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost { namespace tree_node {

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
}}  // namespace boost::tree_node
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
    {
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

     private:
        bool _is_red;

     protected:
        //[reference__with_red_black_flag_base__derived_copy_ctor
        with_red_black_flag_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_red_black_flag_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_red_black_flag_base__emplacement_ctor
        template <typename ...Args>
        explicit with_red_black_flag_base(Args&& ...args);
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
#endif

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

//[reference__with_red_black_flag_base__get__red
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , red_flag_key const& key
        );

    //<-
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
    inline void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , red_flag_key const& key
          , bool value
        )
    {
        node.set_red_flag(value);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__get__black
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , black_flag_key const& key
        );

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >    //->

    inline bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , black_flag_key const& key
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
    inline void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , black_flag_key const& key
          , bool value
        )
    {
        node.set_black_flag(value);
    }
    //->
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_SFINAE
//[reference__with_red_black_flag_base__get__red_flag_key
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,red_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node);

    //<-
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
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__get__black_flag_key
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,black_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node);

    //<-
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
    //->
}}  // namespace boost::tree_node
//]
#endif  // BOOST_NO_SFINAE

namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
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

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_red_black_flag, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_red_black_flag__emplacement_ctor
        template <typename ...Args>
        explicit with_red_black_flag(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_red_black_flag, super_t)
        )
#endif
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
#endif
}}  // namespace boost::tree_node

//[reference__with_red_black_flag_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_red_black_flag_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_red_black_flag_base<Derived,BaseGenerator,T1,T2> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

