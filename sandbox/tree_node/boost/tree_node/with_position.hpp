// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED

#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/move/move.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

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

        BOOST_COPYABLE_AND_MOVABLE(with_position_base);

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
        iterator _position;

     public:
        //[reference__with_position_base__default_ctor
        with_position_base();
        //]

        //[reference__with_position_base__data_ctor
        explicit with_position_base(typename traits::data_type const& data);
        //]

        with_position_base(BOOST_RV_REF(with_position_base) source);

        with_position_base&
            operator=(BOOST_COPY_ASSIGN_REF(with_position_base) copy);

        with_position_base&
            operator=(BOOST_RV_REF(with_position_base) source);

        //[reference__with_position_base__get_position__const
        const_iterator get_position() const;
        //]

        //[reference__with_position_base__get_position
        iterator get_position();
        //]

     protected:
        void set_position_impl(iterator position, ::boost::mpl::true_);

        void set_position_impl(iterator position, ::boost::mpl::false_);
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_position_base() : super_t(), _position()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<Derived,BaseGenerator,T1,T2>::with_position_base(
        typename traits::data_type const& data
    ) : super_t(data), _position()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_position_base<Derived,BaseGenerator,T1,T2>::with_position_base(
        BOOST_RV_REF(with_position_base) source
    )
      : super_t(::boost::move(static_cast<super_t&>(source)))
      , _position(source._position)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_position_base<Derived,BaseGenerator,T1,T2>&
        with_position_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_position_base) copy
        )
    {
        if (this != &copy)
        {
            super_t::operator=(static_cast<super_t const&>(copy));
            _position = copy._position;
        }

        return *this;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_position_base<Derived,BaseGenerator,T1,T2>&
        with_position_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_position_base) source
        )
    {
        if (this != &source)
        {
            super_t::operator=(::boost::move(static_cast<super_t&>(source)));
            _position = source._position;
        }

        return *this;
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
        with_position_base<Derived,BaseGenerator,T1,T2>::get_position() const
    {
        return _position;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
        with_position_base<Derived,BaseGenerator,T1,T2>::get_position()
    {
        return _position;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline void
        with_position_base<Derived,BaseGenerator,T1,T2>::set_position_impl(
            iterator position
          , ::boost::mpl::true_ t
        )
    {
        super_t::set_position_impl(position, t);
        _position = position;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        with_position_base<Derived,BaseGenerator,T1,T2>::set_position_impl(
            iterator position
          , ::boost::mpl::false_ f
        )
    {
        super_t::set_position_impl(position, f);

        iterator c_end = this->get_parent_ptr()->end();

        for (
            position = this->get_parent_ptr()->begin();
            position != c_end;
            ++position
        )
        {
            dereference_iterator(position)._position = position;
        }
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
    class with_position
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
        BOOST_COPYABLE_AND_MOVABLE(with_position);

        typedef with_position_base<with_position,BaseGenerator,T1,T2> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;

        //[reference__with_position__default_ctor
        with_position();
        //]

        //[reference__with_position__data_ctor
        explicit with_position(typename traits::data_type const& data);
        //]

        with_position(BOOST_RV_REF(with_position) source);

        with_position& operator=(BOOST_COPY_ASSIGN_REF(with_position) copy);

        with_position& operator=(BOOST_RV_REF(with_position) source);
    };

    template <typename BaseGenerator, typename T1, typename T2>
    with_position<BaseGenerator,T1,T2>::with_position() : super_t()
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_position<BaseGenerator,T1,T2>::with_position(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_position<BaseGenerator,T1,T2>::with_position(
        BOOST_RV_REF(with_position) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_position<BaseGenerator,T1,T2>&
        with_position<BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_position) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_position<BaseGenerator,T1,T2>&
        with_position<BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_position) source
        )
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
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

#endif  // BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED

