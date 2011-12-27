// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_DEPTH_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_DEPTH_HPP_INCLUDED

#include <boost/cstdint.hpp>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/move/move.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

//[reference__with_depth_base
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    class with_depth_base
      : public ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
    {
        friend struct tree_node_base<Derived>;

        //<-
        BOOST_COPYABLE_AND_MOVABLE(with_depth_base);
        //->
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

        //<-
     private:
        ::std::size_t _depth;

     public:
        //->
        with_depth_base();

        explicit with_depth_base(typename traits::data_type const& data);

//<-
#if 0
//->
        with_depth_base(with_depth_base const& copy);

        with_depth_base(with_depth_base&& source);

        with_depth_base& operator=(with_depth_base const& copy);

        with_depth_base& operator=(with_depth_base&& source);
//<-
#endif

        with_depth_base(BOOST_RV_REF(with_depth_base) source);

        with_depth_base&
            operator=(BOOST_COPY_ASSIGN_REF(with_depth_base) copy);

        with_depth_base& operator=(BOOST_RV_REF(with_depth_base) source);
//->

        ::std::size_t get_depth() const;

        //<-
     protected:
        void shallow_update_impl();

        void deep_update_impl();

     private:
        void _update_less_depth();

        void _update_greater_depth();
        //->
    };

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_depth_base<Derived,BaseGenerator,T1,T2>::with_depth_base()
      : super_t(), _depth(0)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_depth_base<Derived,BaseGenerator,T1,T2>::with_depth_base(
        typename traits::data_type const& data
    ) : super_t(data), _depth(0)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_depth_base<Derived,BaseGenerator,T1,T2>::with_depth_base(
        BOOST_RV_REF(with_depth_base) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
      , _depth(source._depth)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_depth_base<Derived,BaseGenerator,T1,T2>&
        with_depth_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_depth_base) copy
        )
    {
        if (this != &copy)
        {
            super_t::operator=(static_cast<super_t const&>(copy));
            _depth = copy._depth;
        }

        return *this;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline with_depth_base<Derived,BaseGenerator,T1,T2>&
        with_depth_base<Derived,BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_depth_base) source
        )
    {
        if (this != &source)
        {
            super_t::operator=(::boost::move(static_cast<super_t&>(source)));
            _depth = source._depth;
        }

        return *this;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline ::std::size_t
        with_depth_base<Derived,BaseGenerator,T1,T2>::get_depth() const
    {
        return _depth;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void with_depth_base<Derived,BaseGenerator,T1,T2>::shallow_update_impl()
    {
        super_t::shallow_update_impl();

        ::std::size_t new_depth = 0, depth_plus_1;
        const_iterator c_end(this->end());

        for (const_iterator c_itr(this->begin()); c_itr != c_end; ++c_itr)
        {
            depth_plus_1 = dereference_iterator(c_itr).get_depth() + 1;

            if (new_depth < depth_plus_1)
            {
                new_depth = depth_plus_1;
            }
        }

        if (new_depth < _depth)
        {
            _depth = new_depth;
            _update_less_depth();
        }
        else if (_depth < new_depth)
        {
            _depth = new_depth;
            _update_greater_depth();
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void with_depth_base<Derived,BaseGenerator,T1,T2>::deep_update_impl()
    {
        super_t::deep_update_impl();

        ::std::size_t const old_depth = _depth;
        ::std::size_t new_depth, depth_plus_1;
        const_iterator c_itr, c_end;

        for (
            post_order_iterator<Derived> itr(*this->get_derived());
            itr;
            ++itr
        )
        {
            new_depth = 0;
            c_end = itr->end();

            for (c_itr = itr->begin(); c_itr != c_end; ++c_itr)
            {
                depth_plus_1 = dereference_iterator(c_itr).get_depth() + 1;

                if (new_depth < depth_plus_1)
                {
                    new_depth = depth_plus_1;
                }
            }

            itr->_depth = new_depth;
        }

        if (_depth < old_depth)
        {
            _update_less_depth();
        }
        else if (old_depth < _depth)
        {
            _update_greater_depth();
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void with_depth_base<Derived,BaseGenerator,T1,T2>::_update_less_depth()
    {
        pointer p = this->get_derived();
        ::std::size_t new_depth, depth_plus_1;
        const_iterator c_itr, c_end;

        while (p = p->get_parent_ptr())
        {
            new_depth = 0;
            c_end = p->end();

            for (c_itr = p->begin(); c_itr != c_end; ++c_itr)
            {
                depth_plus_1 = dereference_iterator(c_itr).get_depth() + 1;

                if (new_depth < depth_plus_1)
                {
                    new_depth = depth_plus_1;
                }
            }

            if (p->get_depth() == new_depth)
            {
                return;
            }
            else
            {
                // This is no longer the deepest branch.
                p->_depth = new_depth;
            }
        }
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void with_depth_base<Derived,BaseGenerator,T1,T2>::_update_greater_depth()
    {
        ::std::size_t this_depth = _depth;
        pointer p = this->get_derived();

        while ((p = p->get_parent_ptr()) && (p->_depth < ++this_depth))
        {
            // This is the new deepest branch.
            p->_depth = this_depth;
        }
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_depth
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
    class with_depth
      : public with_depth_base<
            with_depth<BaseGenerator,T1,T2>
          , BaseGenerator
          , T1
          , T2
        >
    {
        //<-
        BOOST_COPYABLE_AND_MOVABLE(with_depth);
        //->
        typedef with_depth_base<with_depth,BaseGenerator,T1,T2> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;

        with_depth();

        explicit with_depth(typename traits::data_type const& data);

//<-
#if 0
//->
        with_depth(with_depth const& copy);

        with_depth(with_depth&& source);

        with_depth& operator=(with_depth const& copy);

        with_depth& operator=(with_depth&& source);
//<-
#endif

        with_depth(BOOST_RV_REF(with_depth) source);

        with_depth& operator=(BOOST_COPY_ASSIGN_REF(with_depth) copy);

        with_depth& operator=(BOOST_RV_REF(with_depth) source);
//->
    };

    //<-
    template <typename BaseGenerator, typename T1, typename T2>
    with_depth<BaseGenerator,T1,T2>::with_depth() : super_t()
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_depth<BaseGenerator,T1,T2>::with_depth(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_depth<BaseGenerator,T1,T2>::with_depth(
        BOOST_RV_REF(with_depth) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_depth<BaseGenerator,T1,T2>&
        with_depth<BaseGenerator,T1,T2>::operator=(
            BOOST_COPY_ASSIGN_REF(with_depth) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename BaseGenerator, typename T1, typename T2>
    inline with_depth<BaseGenerator,T1,T2>&
        with_depth<BaseGenerator,T1,T2>::operator=(
            BOOST_RV_REF(with_depth) source
        )
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_depth_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_depth_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_depth_base<Derived,BaseGenerator,T1,T2> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_DEPTH_HPP_INCLUDED

