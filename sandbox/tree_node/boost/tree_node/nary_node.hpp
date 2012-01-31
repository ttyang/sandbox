// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED

#include <utility>
#include <boost/mpl/bool.hpp>
#include <boost/move/move.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/container_gen.hpp>
#include <boost/utility/has_stable_iters_selector.hpp>
#include <boost/utility/is_associative_selector.hpp>
#include <boost/utility/is_unordered_selector.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/tree_node/breadth_first_iterator.hpp>
#include <boost/tree_node/algorithm/lexicographical_comp_3way.hpp>
#include <boost/tree_node/algorithm/_detail/skew_equal.hpp>
#include <boost/tree_node/algorithm/_detail/skew_less.hpp>

namespace boost { namespace tree_node {

    template <typename Derived, typename T, typename Selector>
    class nary_node_base
      : public
        //[reference__nary_node_base__bases
        tree_node_base<Derived>
        //]
    {
        BOOST_COPYABLE_AND_MOVABLE(nary_node_base);
        typedef typename ::boost::container_gen<Selector,Derived>::type
                children;

     public:
        //[reference__nary_node_base__traits
        struct traits
        {
            typedef T data_type;
        };
        //]

        //[reference__nary_node_base__pointer
        typedef typename tree_node_base<Derived>::pointer
                pointer;
        //]

        //[reference__nary_node_base__const_pointer
        typedef typename tree_node_base<Derived>::const_pointer
                const_pointer;
        //]

        //[reference__nary_node_base__iterator
        typedef // implementation_defined
                //<-
                typename children::iterator
                //->
                iterator;
        //]

        //[reference__nary_node_base__const_iterator
        typedef // implementation_defined
                //<-
                typename children::const_iterator
                //->
                const_iterator;
        //]

     private:
        children                   _children;
        pointer                    _parent;
        typename traits::data_type _data;

     public:
        //[reference__nary_node_base__default_ctor
        nary_node_base();
        //]

        //[reference__nary_node_base__data_ctor
        explicit nary_node_base(typename traits::data_type const& data);
        //]

        //[reference__nary_node_base__copy_ctor
        nary_node_base(nary_node_base const& copy);
        //]

        nary_node_base(BOOST_RV_REF(nary_node_base) source);

        nary_node_base& operator=(BOOST_COPY_ASSIGN_REF(nary_node_base) copy);

        nary_node_base& operator=(BOOST_RV_REF(nary_node_base) source);

     protected:
        ~nary_node_base();

     public:
        //[reference__nary_node_base__get_data__const
        typename traits::data_type const& get_data() const;
        //]

        //[reference__nary_node_base__get_data
        typename traits::data_type& get_data();
        //]

        //[reference__nary_node_base__get_parent_ptr__const
        const_pointer get_parent_ptr() const;
        //]

        //[reference__nary_node_base__get_parent_ptr
        pointer get_parent_ptr();
        //]

        //[reference__nary_node_base__add_child__data
        iterator add_child(typename traits::data_type const& data);
        //]

        //[reference__nary_node_base__add_child
        iterator add_child();
        //]

        //[reference__nary_node_base__add_child_copy
        iterator add_child_copy(Derived const& copy);
        //]

        //[reference__nary_node_base__begin__const
        const_iterator begin() const;
        //]

        //[reference__nary_node_base__begin
        iterator begin();
        //]

        //[reference__nary_node_base__end__const
        const_iterator end() const;
        //]

        //[reference__nary_node_base__end
        iterator end();
        //]

        //[reference__nary_node_base__empty
        bool empty() const;
        //]

        //[reference__nary_node_base__clear
        void clear();
        //]

     private:
        template <typename Arg>
        iterator _add_child(Arg& arg);

        template <typename Arg>
        iterator _add_child(Arg& arg, ::boost::mpl::true_);

        template <typename Arg>
        iterator _add_child(Arg& arg, ::boost::mpl::false_);

        template <typename Arg>
        iterator _add_child_assoc(Arg& arg, ::boost::mpl::true_);

        template <typename Arg>
        iterator _add_child_assoc(Arg& arg, ::boost::mpl::false_);

        iterator _add_child_def();

        iterator _add_child_def(::boost::mpl::true_);

        iterator _add_child_def(::boost::mpl::false_);

        iterator _add_child_def_assoc(::boost::mpl::true_);

        iterator _add_child_def_assoc(::boost::mpl::false_);
        // We shouldn't need all of the above private methods, but we do.

        void _initialize(iterator& to_child);

        void _clone(nary_node_base const& copy);
    };

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base()
      : _children(), _parent(), _data()
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        typename traits::data_type const& data
    ) : _children(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        nary_node_base const& copy
    ) : _children(), _parent(), _data(copy._data)
    {
        _clone(copy);
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::nary_node_base(
        BOOST_RV_REF(nary_node_base) source
    ) : _children(::boost::move(source._children))
      , _parent()
      , _data(::boost::move(source._data))
    {
        this->shallow_update_derived();
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>&
        nary_node_base<Derived,T,Selector>::operator=(
            BOOST_COPY_ASSIGN_REF(nary_node_base) copy
        )
    {
        if (this != &copy)
        {
            nary_node_base twin(copy);

            _children = ::boost::move(twin._children);
            _data = ::boost::move(twin._data);

            for (iterator itr = begin(); itr != end(); ++itr)
            {
                itr->_parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>&
        nary_node_base<Derived,T,Selector>::operator=(
            BOOST_RV_REF(nary_node_base) source
        )
    {
        if (this != &source)
        {
            _children = ::boost::move(source._children);
            _data = ::boost::move(source._data);

            for (iterator itr = begin(); itr != end(); ++itr)
            {
                itr->_parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename T, typename Selector>
    nary_node_base<Derived,T,Selector>::~nary_node_base()
    {
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<
        Derived
      , T
      , Selector
    >::traits::data_type const&
        nary_node_base<Derived,T,Selector>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::traits::data_type&
        nary_node_base<Derived,T,Selector>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_pointer
        nary_node_base<Derived,T,Selector>::get_parent_ptr() const
    {
        return _parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::pointer
        nary_node_base<Derived,T,Selector>::get_parent_ptr()
    {
        return _parent;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::add_child(
            typename traits::data_type const& data
        )
    {
        iterator result(_add_child(data));
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::add_child()
    {
        iterator result(_add_child_def());
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::add_child_copy(Derived const& copy)
    {
        iterator result(_add_child(copy));
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::begin() const
    {
        return _children.begin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::begin()
    {
        return _children.begin();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::const_iterator
        nary_node_base<Derived,T,Selector>::end() const
    {
        return _children.end();
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::end()
    {
        return _children.end();
    }

    template <typename Derived, typename T, typename Selector>
    inline bool nary_node_base<Derived,T,Selector>::empty() const
    {
        return _children.empty();
    }

    template <typename Derived, typename T, typename Selector>
    inline void nary_node_base<Derived,T,Selector>::clear()
    {
        _children.clear();
        this->shallow_update_derived();
    }

    template <typename Derived, typename T, typename Selector>
    template <typename Arg>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child(Arg& arg)
    {
        return _add_child(arg, ::boost::is_associative_selector<Selector>());
    }

    template <typename Derived, typename T, typename Selector>
    template <typename Arg>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child(
            Arg& arg
          , ::boost::mpl::true_
        )
    {
        return _add_child_assoc(
            arg
          , ::boost::is_unordered_selector<Selector>()
        );
    }

    template <typename Derived, typename T, typename Selector>
    template <typename Arg>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child(
            Arg& arg
          , ::boost::mpl::false_
        )
    {
        iterator to_child = _children.emplace(_children.end(), arg);
        _initialize(to_child);
        return to_child;
    }

    template <typename Derived, typename T, typename Selector>
    template <typename Arg>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_assoc(
            Arg& arg
          , ::boost::mpl::true_
        )
    {
        ::std::pair<iterator,bool> p = _children.emplace(arg);

        if (p.second)
        {
            _initialize(p.first);
        }

        return p.first;
    }

    template <typename Derived, typename T, typename Selector>
    template <typename Arg>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_assoc(
            Arg& arg
          , ::boost::mpl::false_
        )
    {
        iterator to_child = _children.emplace(arg);
        _initialize(to_child);
        return to_child;
    }

    template <typename Derived, typename T, typename Selector>
    inline typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_def()
    {
        return _add_child_def(::boost::is_associative_selector<Selector>());
    }

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_def(
            ::boost::mpl::true_
        )
    {
        return _add_child_def_assoc(
            ::boost::is_unordered_selector<Selector>()
        );
    }

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_def(
            ::boost::mpl::false_
        )
    {
        iterator to_child = _children.emplace(_children.end());
        _initialize(to_child);
        return to_child;
    }

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_def_assoc(
            ::boost::mpl::true_
        )
    {
        ::std::pair<iterator,bool> p = _children.emplace(
            ::boost::move(typename traits::data_type())
        );

        if (p.second)
        {
            _initialize(p.first);
        }

        return p.first;
    }

    template <typename Derived, typename T, typename Selector>
    typename nary_node_base<Derived,T,Selector>::iterator
        nary_node_base<Derived,T,Selector>::_add_child_def_assoc(
            ::boost::mpl::false_
        )
    {
        iterator to_child = _children.emplace();
        _initialize(to_child);
        return to_child;
    }

    template <typename Derived, typename T, typename Selector>
    inline void
        nary_node_base<Derived,T,Selector>::_initialize(iterator& to_child)
    {
        to_child->_parent = this->get_derived();
        to_child->set_position_derived(
            to_child
          , ::boost::has_stable_iterators_selector<Selector>()
        );
    }

    template <typename Derived, typename T, typename Selector>
    void
        nary_node_base<Derived,T,Selector>::_clone(
            nary_node_base const& copy
        )
    {
        pointer p = this->get_derived();

        for (
            ::boost::tree_node::depth_first_descendant_iterator<
                Derived const
            > copy_itr(*copy.get_derived());
            copy_itr;
            ++copy_itr
        )
        {
            switch (::boost::tree_node::traversal_state(copy_itr))
            {
                case ::boost::tree_node::pre_order_traversal:
                {
                    p = &*p->_add_child(copy_itr->get_data());
                    break;
                }

                case ::boost::tree_node::post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }

        this->deep_update_derived();
    }
}}  // namespace boost::tree_node

//[reference__nary_node_base__operator_equals
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator==(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator==(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        return (
            (
                0 == ::boost::tree_node::lexicographical_compare_3way(
                    ::boost::tree_node::breadth_first_iterator<Derived1 const>(
                        *lhs.get_derived()
                    )
                  , ::boost::tree_node::breadth_first_iterator<Derived2 const>(
                        *rhs.get_derived()
                    )
                )
            )
         && ::boost::tree_node::_detail::skew_equal(
                *lhs.get_derived()
              , *rhs.get_derived()
            )
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__operator_not_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator!=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    inline bool
        operator!=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__operator_less_than
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator<(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator<(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        int value = ::boost::tree_node::lexicographical_compare_3way(
            ::boost::tree_node::breadth_first_iterator<Derived1 const>(
                *lhs.get_derived()
            )
          , ::boost::tree_node::breadth_first_iterator<Derived2 const>(
                *rhs.get_derived()
            )
        );

        if (value < 0)
        {
            return true;
        }

        if (0 < value)
        {
            return false;
        }

        return ::boost::tree_node::_detail::skew_less(
            *lhs.get_derived()
          , *rhs.get_derived()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__operator_greater_than
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator>(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    inline bool
        operator>(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        return rhs < lhs;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__operator_less_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator<=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    inline bool
        operator<=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        return !(rhs < lhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__nary_node_base__operator_greater_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    bool
        operator>=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename T1
      , typename Selector1
      , typename Derived2
      , typename T2
      , typename Selector2
    >
    inline bool
        operator>=(
            nary_node_base<Derived1,T1,Selector1> const& lhs
          , nary_node_base<Derived2,T2,Selector2> const& rhs
        )
    {
        return !(lhs < rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <typename T, typename Selector = ::boost::boost_dequeS>
    class nary_node
      : public
        //[reference__nary_node__bases
        nary_node_base<nary_node<T,Selector>,T,Selector>
        //]
    {
        BOOST_COPYABLE_AND_MOVABLE(nary_node);

        //[reference__nary_node__super_t
        typedef nary_node_base<nary_node,T,Selector> super_t;
        //]

     public:
        //[reference__nary_node__traits
        typedef typename super_t::traits traits;
        //]

        //[reference__nary_node__pointer
        typedef typename super_t::pointer pointer;
        //]

        //[reference__nary_node__const_pointer
        typedef typename super_t::const_pointer const_pointer;
        //]

        //[reference__nary_node__iterator
        typedef typename super_t::iterator iterator;
        //]

        //[reference__nary_node__const_iterator
        typedef typename super_t::const_iterator const_iterator;
        //]

        //[reference__nary_node__default_ctor
        nary_node();
        //]

        //[reference__nary_node__data_ctor
        explicit nary_node(typename traits::data_type const& data);
        //]

        nary_node(BOOST_RV_REF(nary_node) source);

        nary_node& operator=(BOOST_COPY_ASSIGN_REF(nary_node) copy);

        nary_node& operator=(BOOST_RV_REF(nary_node) source);
    };

    template <typename T, typename Selector>
    nary_node<T,Selector>::nary_node() : super_t()
    {
    }

    template <typename T, typename Selector>
    nary_node<T,Selector>::nary_node(typename traits::data_type const& data)
      : super_t(data)
    {
    }

    template <typename T, typename Selector>
    nary_node<T,Selector>::nary_node(BOOST_RV_REF(nary_node) source)
      : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename T, typename Selector>
    inline nary_node<T,Selector>&
        nary_node<T,Selector>::operator=(
            BOOST_COPY_ASSIGN_REF(nary_node) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename T, typename Selector>
    inline nary_node<T,Selector>&
        nary_node<T,Selector>::operator=(BOOST_RV_REF(nary_node) source)
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
}}  // namespace boost::tree_node
//]

//[reference__nary_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::boost_dequeS>
    struct nary_node_gen
    {
        template <typename Derived, typename T>
        struct apply
        {
            typedef nary_node_base<Derived,T,Selector> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_NARY_NODE_HPP_INCLUDED

