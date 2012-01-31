// Copyright (C) 2011-2012 Cromwell D. Enage
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
#include <boost/utility/value_init.hpp>
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/algorithm/dereference_iterator.hpp>

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    class with_depth_base
      : public
        //[reference__with_depth_base__bases
        ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
        //]
    {
        friend struct tree_node_base<Derived>;

        BOOST_COPYABLE_AND_MOVABLE(with_depth_base);

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
        Depth _depth;

     public:
        //[reference__with_depth_base__default_ctor
        with_depth_base();
        //]

        //[reference__with_depth_base__data_ctor
        explicit with_depth_base(typename traits::data_type const& data);
        //]

        with_depth_base(BOOST_RV_REF(with_depth_base) source);

        with_depth_base&
            operator=(BOOST_COPY_ASSIGN_REF(with_depth_base) copy);

        with_depth_base& operator=(BOOST_RV_REF(with_depth_base) source);

     protected:
        ~with_depth_base();

     public:
        //[reference__with_depth_base__get_depth
        Depth const& get_depth() const;
        //]

     protected:
        void shallow_update_impl();

        void deep_update_impl();

     private:
        void _update_less_depth();

        void _update_greater_depth();
    };

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::with_depth_base()
      : super_t(), _depth(::boost::initialized_value)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::with_depth_base(
        typename traits::data_type const& data
    ) : super_t(data), _depth(::boost::initialized_value)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::with_depth_base(
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
      , typename Depth
    >
    inline with_depth_base<Derived,BaseGenerator,T1,T2,Depth>&
        with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::operator=(
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
      , typename Depth
    >
    inline with_depth_base<Derived,BaseGenerator,T1,T2,Depth>&
        with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::operator=(
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
      , typename Depth
    >
    with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::~with_depth_base()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    inline Depth const&
        with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::get_depth() const
    {
        return _depth;
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Depth
    >
    void
        with_depth_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Depth
        >::shallow_update_impl()
    {
        super_t::shallow_update_impl();

        Depth new_depth = ::boost::initialized_value, depth_plus_1;
        const_iterator c_end(this->end());

        for (const_iterator c_itr(this->begin()); c_itr != c_end; ++c_itr)
        {
            depth_plus_1 = dereference_iterator(c_itr).get_depth();

            if (new_depth < ++depth_plus_1)
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
      , typename Depth
    >
    void with_depth_base<Derived,BaseGenerator,T1,T2,Depth>::deep_update_impl()
    {
        super_t::deep_update_impl();

        Depth const old_depth = _depth;
        Depth new_depth, depth_plus_1;
        const_iterator c_itr, c_end;

        for (
            post_order_iterator<Derived> itr(*this->get_derived());
            itr;
            ++itr
        )
        {
            new_depth = ::boost::initialized_value;
            c_end = itr->end();

            for (c_itr = itr->begin(); c_itr != c_end; ++c_itr)
            {
                depth_plus_1 = dereference_iterator(c_itr).get_depth();

                if (new_depth < ++depth_plus_1)
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
      , typename Depth
    >
    void
        with_depth_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Depth
        >::_update_less_depth()
    {
        pointer p = this->get_derived();
        Depth new_depth, depth_plus_1;
        const_iterator c_itr, c_end;

        while (p = p->get_parent_ptr())
        {
            new_depth = ::boost::initialized_value;
            c_end = p->end();

            for (c_itr = p->begin(); c_itr != c_end; ++c_itr)
            {
                depth_plus_1 = dereference_iterator(c_itr).get_depth();

                if (new_depth < ++depth_plus_1)
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
      , typename Depth
    >
    void
        with_depth_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Depth
        >::_update_greater_depth()
    {
        Depth this_depth = _depth;
        pointer p = this->get_derived();

        while ((p = p->get_parent_ptr()) && (p->_depth < ++this_depth))
        {
            // This is the new deepest branch.
            p->_depth = this_depth;
        }
    }
}}  // namespace boost::tree_node

namespace boost { namespace tree_node {

    template <
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename Depth = ::std::size_t
    >
    class with_depth
      : public
        //[reference__with_depth__bases
        with_depth_base<
            with_depth<BaseGenerator,T1,T2,Depth>
          , BaseGenerator
          , T1
          , T2
          , Depth
        >
        //]
    {
        BOOST_COPYABLE_AND_MOVABLE(with_depth);

        typedef with_depth_base<with_depth,BaseGenerator,T1,T2,Depth> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::iterator iterator;
        typedef typename super_t::const_iterator const_iterator;

        //[reference__with_depth__default_ctor
        with_depth();
        //]

        //[reference__with_depth__data_ctor
        explicit with_depth(typename traits::data_type const& data);
        //]

        with_depth(BOOST_RV_REF(with_depth) source);

        with_depth& operator=(BOOST_COPY_ASSIGN_REF(with_depth) copy);

        with_depth& operator=(BOOST_RV_REF(with_depth) source);
    };

    template <typename BaseGenerator, typename T1, typename T2, typename Depth>
    with_depth<BaseGenerator,T1,T2,Depth>::with_depth() : super_t()
    {
    }

    template <typename BaseGenerator, typename T1, typename T2, typename Depth>
    with_depth<BaseGenerator,T1,T2,Depth>::with_depth(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }

    template <typename BaseGenerator, typename T1, typename T2, typename Depth>
    with_depth<BaseGenerator,T1,T2,Depth>::with_depth(
        BOOST_RV_REF(with_depth) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename BaseGenerator, typename T1, typename T2, typename Depth>
    inline with_depth<BaseGenerator,T1,T2,Depth>&
        with_depth<BaseGenerator,T1,T2,Depth>::operator=(
            BOOST_COPY_ASSIGN_REF(with_depth) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename BaseGenerator, typename T1, typename T2, typename Depth>
    inline with_depth<BaseGenerator,T1,T2,Depth>&
        with_depth<BaseGenerator,T1,T2,Depth>::operator=(
            BOOST_RV_REF(with_depth) source
        )
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
}}  // namespace boost::tree_node

//[reference__with_depth_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename Depth = ::std::size_t>
    struct with_depth_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_depth_base<Derived,BaseGenerator,T1,T2,Depth> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_DEPTH_HPP_INCLUDED

