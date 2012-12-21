// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>
#include <boost/tree_node/position_key.hpp>

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
    >
    class with_position_base
      : public
        //[reference__with_position_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
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
        typedef typename super_t::size_type
                size_type;

     private:
        iterator _position;

     protected:
        //[reference__with_position_base__derived_copy_ctor
        with_position_base(Derived const& copy);
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_position_base(BOOST_RV_REF(Derived) source);
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_position_base__emplacement_ctor
        template <typename ...Args>
        explicit with_position_base(Args&& ...args);
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
#define BOOST_TREE_NODE_WITH_POSITION_MACRO(z, n, Tuple)                     \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_HEADER(z, n, Tuple)          \
          , _position()                                                      \
        {                                                                    \
        }                                                                    \
//!
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_WITH_POSITION_MACRO
          , (with_position_base, super_t)
        )
#undef BOOST_TREE_NODE_WITH_POSITION_MACRO
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

        ~with_position_base();

        void on_post_copy_or_move();

        void on_post_inserted_impl(iterator position, ::boost::mpl::true_);

        void on_post_inserted_impl(iterator position, ::boost::mpl::false_);

     public:
        //[reference__with_position_base__key_value_operator__const
        const_iterator operator[](position_key const&) const;
        //]

        //[reference__with_position_base__key_value_operator
        iterator operator[](position_key const&);
        //]

     private:
        static void _set_child_positions(pointer to_parent);
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<Derived,BaseGenerator,T1,T2>::with_position_base(
        Derived const& copy
    ) : super_t(copy), _position()
    {
    }

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<Derived,BaseGenerator,T1,T2>::with_position_base(
#if defined BOOST_NO_RVALUE_REFERENCES
        ::boost::rv<Derived>& source
    ) : super_t(source)
#else
        Derived&& source
    ) : super_t(static_cast<Derived&&>(source))
#endif
      , _position()
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
    with_position_base<Derived,BaseGenerator,T1,T2>::with_position_base(
        Args&& ...args
    ) : super_t(::boost::forward<Args>(args)...), _position()
    {
    }
#endif

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<Derived,BaseGenerator,T1,T2>::~with_position_base()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_position_base<Derived,BaseGenerator,T1,T2>::on_post_copy_or_move()
    {
        super_t::on_post_copy_or_move();
        this->_set_child_positions(this->get_derived());
        this->on_post_modify_value(position_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_position_base<Derived,BaseGenerator,T1,T2>::on_post_inserted_impl(
            iterator position
          , ::boost::mpl::true_ t
        )
    {
        super_t::on_post_inserted_impl(position, t);
        this->_position = position;
        this->on_post_modify_value(position_key());
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_position_base<Derived,BaseGenerator,T1,T2>::on_post_inserted_impl(
            iterator position
          , ::boost::mpl::false_ f
        )
    {
        super_t::on_post_inserted_impl(position, f);
        this->_set_child_positions(this->get_parent_ptr());

        iterator itr_end = this->get_parent_ptr()->end();

        for (
            iterator itr = this->get_parent_ptr()->begin();
            itr != itr_end;
            ++itr
        )
        {
            ::boost::tree_node::dereference_iterator(itr).on_post_modify_value(
                position_key()
            );
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename with_position_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::const_iterator
        with_position_base<Derived,BaseGenerator,T1,T2>::operator[](
            position_key const&
        ) const
    {
        return this->_position;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
        with_position_base<Derived,BaseGenerator,T1,T2>::operator[](
            position_key const&
        )
    {
        return this->_position;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        with_position_base<Derived,BaseGenerator,T1,T2>::_set_child_positions(
            pointer to_parent
        )
    {
        iterator itr_end = to_parent->end();

        for (iterator itr = to_parent->begin(); itr != itr_end; ++itr)
        {
            ::boost::tree_node::dereference_iterator(itr)._position = itr;
        }
    }
}}  // namespace boost::tree_node

//[reference__with_position_base__get__const
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename with_position_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::const_iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2> const& node
          , position_key const& key
        );

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename with_position_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::const_iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2> const& node
          , position_key const& key
        )
    {
        return node[key];
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_position_base__get
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2>& node
          , position_key const& key
        );

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2>& node
          , position_key const& key
        )
    {
        return node[key];
    }
    //->
}}  // namespace boost::tree_node
//]

#if !defined BOOST_NO_SFINAE
//[reference__with_position_base__get__key__const
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::const_iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2> const& node);

    //<-
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::const_iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2> const& node)
    {
        return node[position_key()];
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_position_base__get__key
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2>& node);

    //<-
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2>& node)
    {
        return node[position_key()];
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
    >
    struct has_key_impl<
        with_position_base<Derived,BaseGenerator,T1,T2>
      , position_key
    > : ::boost::mpl::true_
    {
    };
}}  // namespace boost::tree_node
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
    struct with_position
      : public
        //[reference__with_position__bases
        with_position_base<
            with_position<BaseGenerator,T1,T2>
          , BaseGenerator
          , T1
          , T2
        >
        //]
    {
        typedef with_position_base<with_position,BaseGenerator,T1,T2> super_t;
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;
        typedef typename super_t::size_type size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_position, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_position__emplacement_ctor
        template <typename ...Args>
        explicit with_position(Args&& ...args);
        //]
#else
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_position, super_t)
        )
#endif
    };

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
    template <typename BaseGenerator, typename T1, typename T2>
    template <typename ...Args>
    inline with_position<BaseGenerator,T1,T2>::with_position(Args&& ...args)
      : super_t(::boost::forward<Args>(args)...)
    {
        super_t::on_post_emplacement_construct();
    }
#endif
}}  // namespace boost::tree_node

//[reference__with_position_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_position_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_position_base<Derived,BaseGenerator,T1,T2> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED

