// Copyright (C) 2011-2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED

#include <cstddef>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/value_init.hpp>
#include <boost/tree_node/preprocessor.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/with_height_fwd.hpp>
#include <boost/tree_node/key/height.hpp>
#include <boost/tree_node/intrinsic/has_key.hpp>
#include <boost/tree_node/intrinsic/get_keys.hpp>
#include <boost/tree_node/intrinsic/at_key.hpp>
#include <boost/tree_node/iterator/dereference.hpp>

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
      , typename Height
    >
    struct is_POD<
        ::boost::tree_node::with_height<BaseGenerator,T1,T2,Height>
    > : ::boost::false_type
    {
    };

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    struct is_pod<
        ::boost::tree_node::with_height<BaseGenerator,T1,T2,Height>
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
#if defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
      , public height_key
#endif
      , private ::boost::noncopyable
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

        //[reference__with_height_base__traits
        struct traits : super_t::traits
        {
            typedef typename ::boost::mpl::if_<
                        ::std::tr1::is_void<Height>
                      , size_type
                      , Height
                    >::type
                    height;
        };
        //]

     private:
        typename traits::height _height;

     protected:
        //[reference__with_height_base__derived_copy_ctor
        with_height_base(Derived const& copy);
        //]

        //[reference__with_height_base__derived_copy_ctor_w_allocator
        with_height_base(
            Derived const& copy
          , typename traits::allocator_reference allocator
        );
        //]

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
        with_height_base(BOOST_RV_REF(Derived) source);

        with_height_base(
            BOOST_RV_REF(Derived) source
          , typename traits::allocator_reference allocator
        );
#endif

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_height_base__emplacement_ctor
        template <typename ...Args>
        explicit with_height_base(Args&& ...args);
        //]

        //[reference__with_height_base__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_height_base(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
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

#define BOOST_TREE_NODE_WITH_HEIGHT_MACRO(z, n, Tuple)                       \
        BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_HEADER(z, n, Tuple)  \
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
        typename traits::height const& operator[](height_key const&) const;
        //]

     private:
        void _shallow_update();

        static typename traits::height
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

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::with_height_base(
        Derived const& copy
      , typename traits::allocator_reference allocator
    ) : super_t(copy, allocator), _height(copy._height)
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
      , typename traits::allocator_reference allocator
    ) : super_t(source, allocator)
#else
        Derived&& source
      , typename traits::allocator_reference allocator
    ) : super_t(static_cast<Derived&&>(source), allocator)
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

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    template <typename ...Args>
    with_height_base<Derived,BaseGenerator,T1,T2,Height>::with_height_base(
        ::boost::container::allocator_arg_t
      , typename traits::allocator_reference allocator
      , Args&& ...args
    ) : super_t(
            ::boost::container::allocator_arg
          , allocator
          , ::boost::forward<Args>(args)...
        )
      , _height(::boost::initialized_value)
    {
    }
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING

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
    inline typename with_height_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Height
    >::traits::height const&
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
        typename traits::height new_height = self::_get_max_height(
            this->begin()
          , this->end()
        );

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
    typename with_height_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Height
    >::traits::height
        with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::_get_max_height(const_iterator c_itr, const_iterator c_end)
    {
        typename traits::height result = ::boost::initialized_value;

        for (typename traits::height height_plus_1; c_itr != c_end; ++c_itr)
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
        typename traits::height new_height;

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
        typename traits::height p_height = p->_height;

        while ((p = p->get_parent_ptr()) && (p->_height < ++p_height))
        {
            // This is the new deepest branch.
            p->_height = p_height;
        }
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    inline typename with_height_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Height
    >::traits::height const&
        get(
            with_height_base<Derived,BaseGenerator,T1,T2,Height> const& node
          , height_key const& key
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
      , typename Height
    >
    inline typename ::boost::enable_if<
        ::std::tr1::is_same<Key,height_key>
      , typename with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::traits::height const&
    >::type
        get(with_height_base<Derived,BaseGenerator,T1,T2,Height> const& node)
    {
        return node[height_key()];
    }
#endif  // BOOST_NO_SFINAE
}}  // namespace boost::tree_node

namespace boost { namespace tree_node { namespace result_of {

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
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

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    struct get_keys_impl<
        with_height_base<Derived,BaseGenerator,T1,T2,Height>
    > : ::boost::mpl::vector1<height_key>
    {
    };
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    template <>
    struct at_key_impl<height_key>
    {
        template <typename Node>
        struct apply
        {
            typedef typename Node::traits::height const& type;
        };
    };
}}}  // namespace boost::tree_node::result_of

//[reference__with_height_base_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename Height = void>
    struct with_height_base_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_height_base<Derived,BaseGenerator,T1,T2,Height> type;
        };
    };
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
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
        typedef typename super_t::reverse_iterator
                reverse_iterator;
        typedef typename super_t::const_reverse_iterator
                const_reverse_iterator;
        typedef typename super_t::size_type
                size_type;

        BOOST_TREE_NODE_COPYABLE_AND_MOVABLE(with_height, super_t)

#if defined BOOST_CONTAINER_PERFECT_FORWARDING
        //[reference__with_height__emplacement_ctor
        template <typename ...Args>
        explicit with_height(Args&& ...args);
        //]

        //[reference__with_height__emplacement_ctor_w_allocator
        template <typename ...Args>
        explicit with_height(
            ::boost::container::allocator_arg_t
          , typename traits::allocator_reference allocator
          , Args&& ...args
        );
        //]
#else  // !defined BOOST_CONTAINER_PERFECT_FORWARDING
        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_INLINE_DEF
          , (with_height, super_t)
        )

        BOOST_PP_REPEAT(
            BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS
          , BOOST_TREE_NODE_EMPLACEMENT_CTOR_W_ALLOC_INLINE_DEF
          , (with_height, super_t)
        )
#endif  // BOOST_CONTAINER_PERFECT_FORWARDING
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

    template <
        typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    template <typename ...Args>
    inline with_height<BaseGenerator,T1,T2,Height>::with_height(
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

//[reference__with_height_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename Height = void>
    struct with_height_gen
    {
        template <typename T1, typename T2 = void>
        struct apply
        {
            typedef with_height<BaseGenerator,T1,T2,Height> type;
        };
    };
}}  // namespace boost::tree_node
//]

#include <boost/tree_node/_detail/config_end.hpp>

#endif  // BOOST_TREE_NODE_WITH_HEIGHT_HPP_INCLUDED

