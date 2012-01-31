// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/move/move.hpp>

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
        BOOST_COPYABLE_AND_MOVABLE(with_red_black_flag_base);

        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_void<T2>
                  , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
                  , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
                >::type
                super_t;

     public:
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

     public:
        //[reference__with_red_black_flag_base__default_ctor
        with_red_black_flag_base();
        //]

        //[reference__with_red_black_flag_base__data_ctor
        explicit with_red_black_flag_base(
            typename traits::data_type const& data
        );
        //]

        with_red_black_flag_base(
            BOOST_RV_REF(with_red_black_flag_base) source
        );

        with_red_black_flag_base&
            operator=(BOOST_COPY_ASSIGN_REF(with_red_black_flag_base) copy);

        with_red_black_flag_base&
            operator=(BOOST_RV_REF(with_red_black_flag_base) source);

     protected:
        ~with_red_black_flag_base();

     public:
        //[reference__with_red_black_flag_base__is_red
        bool is_red() const;
        //]

        //[reference__with_red_black_flag_base__is_black
        bool is_black() const;
        //]

        //[reference__with_red_black_flag_base__set_red_flag
        void set_red_flag(bool flag);
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
    >::with_red_black_flag_base() : super_t(), _is_red(false)
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
    >::with_red_black_flag_base(typename traits::data_type const& data)
      : super_t(data), _is_red(false)
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
    >::with_red_black_flag_base(BOOST_RV_REF(with_red_black_flag_base) source)
      : super_t(::boost::move(static_cast<super_t&>(source)))
      , _is_red(source._is_red)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_red_black_flag_base<Derived,BaseGenerator,T1,T2>&
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_red_black_flag_base) copy
        )
    {
        if (this != &copy)
        {
            super_t::operator=(static_cast<super_t const&>(copy));
            _is_red = copy._is_red;
        }

        return *this;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_red_black_flag_base<Derived,BaseGenerator,T1,T2>&
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_red_black_flag_base) source
        )
    {
        if (this != &source)
        {
            super_t::operator=(::boost::move(static_cast<super_t&>(source)));
            _is_red = source._is_red;
        }

        return *this;
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
    >::~with_red_black_flag_base()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline bool
        with_red_black_flag_base<Derived,BaseGenerator,T1,T2>::is_red() const
    {
        return _is_red;
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
        >::is_black() const
    {
        return !_is_red;
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
        _is_red = flag;
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
    class with_red_black_flag
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

     public:
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

        //[reference__with_red_black_flag__default_ctor
        with_red_black_flag();
        //]

        //[reference__with_red_black_flag__data_ctor
        explicit with_red_black_flag(typename traits::data_type const& data);
        //]

        with_red_black_flag(BOOST_RV_REF(with_red_black_flag) source);

        with_red_black_flag&
            operator=(BOOST_COPY_ASSIGN_REF(with_red_black_flag) copy);

        with_red_black_flag&
            operator=(BOOST_RV_REF(with_red_black_flag) source);
    };

    template <typename BaseGenerator, typename T1, typename T2>
    with_red_black_flag<BaseGenerator,T1,T2>::with_red_black_flag() : super_t()
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_red_black_flag<BaseGenerator,T1,T2>::with_red_black_flag(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_red_black_flag<BaseGenerator,T1,T2>::with_red_black_flag(
        BOOST_RV_REF(with_red_black_flag) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_red_black_flag<BaseGenerator,T1,T2>&
        with_red_black_flag<BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_red_black_flag) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_red_black_flag<BaseGenerator,T1,T2>&
        with_red_black_flag<BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_red_black_flag) source
        )
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
}}  // namespace boost::tree_node

//[reference__with_red_black_flag_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_red_black_flag_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_red_black_flag_base<Derived,BaseGenerator,T1,T2>
                    type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_HPP_INCLUDED

