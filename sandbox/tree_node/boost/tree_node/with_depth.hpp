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
#include <boost/tree_node/post_order_iterator.hpp>
#include <boost/tree_node/factory.hpp>
#include <boost/tree_node/dereference_iterator.hpp>

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
        friend struct shared_tree_node_base<Derived>;

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
        typedef typename super_t::child_iterator
                child_iterator;
        typedef typename super_t::const_child_iterator
                const_child_iterator;

        //<-
     private:
        ::std::size_t _depth;
        //->

     protected:
        with_depth_base();

        explicit with_depth_base(typename traits::data_type const& data);

        //<-
        void shallow_update_impl();

        void deep_update_impl();
        //->

     public:
        ::std::size_t get_depth() const;

        //<-
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

        ::std::size_t new_depth = 0;
        const_child_iterator c_end(
            this->get_derived()->get_child_end()
        );

        for (
            const_child_iterator c_itr(
                this->get_derived()->get_child_begin()
            );
            c_itr != c_end;
            ++c_itr
        )
        {
            if (new_depth < dereference_iterator(c_itr)->get_depth() + 1)
            {
                new_depth = dereference_iterator(c_itr)->get_depth() + 1;
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

        for (
            post_order_iterator<pointer,::boost::mpl::false_> itr(
                this->get_derived()
            );
            itr;
            ++itr
        )
        {
            ::std::size_t new_depth = 0;
            const_child_iterator c_end(
                (*itr)->get_derived()->get_child_end()
            );

            for (
                const_child_iterator c_itr(
                    (*itr)->get_derived()->get_child_begin()
                );
                c_itr != c_end;
                ++c_itr
            )
            {
                if (new_depth < dereference_iterator(c_itr)->get_depth() + 1)
                {
                    new_depth = dereference_iterator(c_itr)->get_depth() + 1;
                }
            }

            (*itr)->_depth = new_depth;
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
        ::std::size_t new_depth;
        const_child_iterator c_itr, c_end;

        while (p = p->get_parent())
        {
            new_depth = 0;
            c_end = p->get_derived()->get_child_end();

            for (
                c_itr = p->get_derived()->get_child_begin();
                c_itr != c_end;
                ++c_itr
            )
            {
                if (new_depth < dereference_iterator(c_itr)->get_depth() + 1)
                {
                    new_depth = dereference_iterator(c_itr)->get_depth() + 1;
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

        while ((p = p->get_parent()) && (p->_depth < ++this_depth))
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
        typedef with_depth_base<with_depth,BaseGenerator,T1,T2> super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::child_iterator child_iterator;
        typedef typename super_t::const_child_iterator const_child_iterator;

        //<-
     private:
        with_depth();

        explicit with_depth(typename traits::data_type const& data);

        friend struct ::boost::tree_node::factory<with_depth>;
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
            typedef with_depth_base<Derived,BaseGenerator,T1,T2>
                    type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_DEPTH_HPP_INCLUDED

