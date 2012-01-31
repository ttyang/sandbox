// Copyright (C) 2011-2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED

#include <utility>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/move/move.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/utility/has_stable_iters_selector.hpp>
#ifdef BOOST_MSVC
#include <boost/utility/is_unordered_selector.hpp>
#else
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/or.hpp>
#endif
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_desc_iterator.hpp>
#include <boost/tree_node/breadth_first_desc_iterator.hpp>
#include <boost/tree_node/algorithm/lexicographical_comp_3way.hpp>
#include <boost/tree_node/algorithm/_detail/skew_equal.hpp>
#include <boost/tree_node/algorithm/_detail/skew_less.hpp>

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename AssociativeContainerSelector
    >
    class associative_node_base
      : public
        //[reference__associative_node_base__bases
        tree_node_base<Derived>
        //]
    {
        BOOST_COPYABLE_AND_MOVABLE(associative_node_base);
        typedef typename ::boost::mpl::apply_wrap2<
                    associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , Key
                  , Derived
                >::type
                children;

     public:
        //[reference__associative_node_base__traits
        struct traits
        {
            typedef Key key_type;
            typedef Data data_type;
        };
        //]

        //[reference__associative_node_base__pointer
        typedef typename tree_node_base<Derived>::pointer
                pointer;
        //]

        //[reference__associative_node_base__const_pointer
        typedef typename tree_node_base<Derived>::const_pointer
                const_pointer;
        //]

        //[reference__associative_node_base__iterator
        typedef // implementation_defined
                //<-
                typename children::iterator
                //->
                iterator;
        //]

        //[reference__associative_node_base__const_iterator
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
        //[reference__associative_node_base__default_ctor
        associative_node_base();
        //]

        //[reference__associative_node_base__data_ctor
        explicit associative_node_base(
            typename traits::data_type const& data
        );
        //]

        //[reference__associative_node_base__copy_ctor
        associative_node_base(associative_node_base const& copy);
        //]

        associative_node_base(BOOST_RV_REF(associative_node_base) source);

        associative_node_base&
            operator=(BOOST_COPY_ASSIGN_REF(associative_node_base) copy);

        associative_node_base&
            operator=(BOOST_RV_REF(associative_node_base) source);

     protected:
        ~associative_node_base();

     public:
        //[reference__associative_node_base__get_data__const
        typename traits::data_type const& get_data() const;
        //]

        //[reference__associative_node_base__get_data
        typename traits::data_type& get_data();
        //]

        //[reference__associative_node_base__get_parent_ptr__const
        const_pointer get_parent_ptr() const;
        //]

        //[reference__associative_node_base__get_parent_ptr
        pointer get_parent_ptr();
        //]

        //[reference__associative_node_base__add_child__data
        iterator
            add_child(
                typename traits::key_type const& key
              , typename traits::data_type const& data
            );
        //]

        //[reference__associative_node_base__add_child
        iterator add_child(typename traits::key_type const& key);
        //]

        //[reference__associative_node_base__add_child_copy
        iterator
            add_child_copy(
                typename traits::key_type const& key
              , Derived const& copy
            );
        //]

        //[reference__associative_node_base__begin__const
        const_iterator begin() const;
        //]

        //[reference__associative_node_base__begin
        iterator begin();
        //]

        //[reference__associative_node_base__end__const
        const_iterator end() const;
        //]

        //[reference__associative_node_base__end
        iterator end();
        //]

        //[reference__associative_node_base__empty
        bool empty() const;
        //]

        //[reference__associative_node_base__clear
        void clear();
        //]

        //[reference__associative_node_base__find_child__const
        const_iterator
            find_child(typename traits::key_type const& key) const;
        //]

        //[reference__associative_node_base__find_child
        iterator find_child(typename traits::key_type const& key);
        //]

        //[reference__associative_node_base__find_children__const
        ::std::pair<const_iterator,const_iterator>
            find_children(typename traits::key_type const& key) const;
        //]

        //[reference__associative_node_base__find_children
        ::std::pair<iterator,iterator>
            find_children(typename traits::key_type const& key);
        //]

        //[reference__associative_node_base__remove_children
        ::std::size_t remove_children(typename traits::key_type const& key);
        //]

     private:
        template <typename Arg>
        iterator
            _add_child(
                typename traits::key_type const& key
              , Arg const& arg
            );

        template <typename Arg>
        iterator
            _add_child(
                typename traits::key_type const& key
              , Arg const& arg
              , ::boost::mpl::true_
            );

        template <typename Arg>
        iterator
            _add_child(
                typename traits::key_type const& key
              , Arg const& arg
              , ::boost::mpl::false_
            );

        iterator _add_child_def(typename traits::key_type const& key);

        iterator
            _add_child_def(
                typename traits::key_type const& key
              , ::boost::mpl::true_
            );

        iterator
            _add_child_def(
                typename traits::key_type const& key
              , ::boost::mpl::false_
            );
        // We shouldn't need all of the above private methods, but we do.

        void _initialize(iterator& itr);

        void _clone(associative_node_base const& copy);
    };

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>::associative_node_base()
      : _children(), _parent(), _data()
    {
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>::associative_node_base(
        typename traits::data_type const& data
    ) : _children(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>::associative_node_base(
        associative_node_base const& copy
    ) : _children(), _parent(), _data(copy._data)
    {
        _clone(copy);
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>::associative_node_base(
        BOOST_RV_REF(associative_node_base) source
    ) : _children(::boost::move(source._children))
      , _parent()
      , _data(::boost::move(source._data))
    {
        this->shallow_update_derived();
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>&
        associative_node_base<Derived,K,D,A>::operator=(
            BOOST_COPY_ASSIGN_REF(associative_node_base) copy
        )
    {
        if (this != &copy)
        {
            associative_node_base twin(copy);

            _children = ::boost::move(twin._children);
            _data = ::boost::move(twin._data);

            for (iterator itr = begin(); itr != end(); ++itr)
            {
                itr->second._parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>&
        associative_node_base<Derived,K,D,A>::operator=(
            BOOST_RV_REF(associative_node_base) source
        )
    {
        if (this != &source)
        {
            _children = ::boost::move(source._children);
            _data = ::boost::move(source._data);

            for (iterator itr = begin(); itr != end(); ++itr)
            {
                itr->second._parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename K, typename D, typename A>
    associative_node_base<Derived,K,D,A>::~associative_node_base()
    {
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<
        Derived
      , K
      , D
      , A
    >::traits::data_type const&
        associative_node_base<Derived,K,D,A>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<
        Derived
      , K
      , D
      , A
    >::traits::data_type&
        associative_node_base<Derived,K,D,A>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::const_pointer
        associative_node_base<Derived,K,D,A>::get_parent_ptr() const
    {
        return _parent;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::pointer
        associative_node_base<Derived,K,D,A>::get_parent_ptr()
    {
        return _parent;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::add_child(
            typename traits::key_type const& key
          , typename traits::data_type const& data
        )
    {
        iterator result = _add_child(key, data);
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::add_child(
            typename traits::key_type const& key
        )
    {
        iterator result = _add_child_def(key);
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::add_child_copy(
            typename traits::key_type const& key
          , Derived const& copy
        )
    {
        iterator result = _add_child(key, copy);
        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<
        Derived
      , K
      , D
      , A
    >::const_iterator
        associative_node_base<Derived,K,D,A>::begin() const
    {
        return _children.begin();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::begin()
    {
        return _children.begin();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<
        Derived
      , K
      , D
      , A
    >::const_iterator
        associative_node_base<Derived,K,D,A>::end() const
    {
        return _children.end();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::end()
    {
        return _children.end();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline bool associative_node_base<Derived,K,D,A>::empty() const
    {
        return _children.empty();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline void associative_node_base<Derived,K,D,A>::clear()
    {
        _children.clear();
        this->shallow_update_derived();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::const_iterator
        associative_node_base<Derived,K,D,A>::find_child(
            typename traits::key_type const& key
        ) const
    {
        return _children.find(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::find_child(
            typename traits::key_type const& key
        )
    {
        return _children.find(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    inline ::std::pair<
        typename associative_node_base<Derived,K,D,A>::const_iterator
      , typename associative_node_base<Derived,K,D,A>::const_iterator
    >
        associative_node_base<Derived,K,D,A>::find_children(
            typename traits::key_type const& key
        ) const
    {
        return _children.equal_range(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    inline ::std::pair<
        typename associative_node_base<Derived,K,D,A>::iterator
      , typename associative_node_base<Derived,K,D,A>::iterator
    >
        associative_node_base<Derived,K,D,A>::find_children(
            typename traits::key_type const& key
        )
    {
        return _children.equal_range(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    ::std::size_t
        associative_node_base<Derived,K,D,A>::remove_children(
            typename traits::key_type const& key
        )
    {
        ::std::size_t result = _children.erase(key);

        this->shallow_update_derived();
        return result;
    }

    template <typename Derived, typename K, typename D, typename A>
    template <typename Arg>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child(
            typename traits::key_type const& key
          , Arg const& arg
        )
    {
#ifdef BOOST_MSVC
        return _add_child(key, arg, ::boost::is_unordered_selector<A>());
#else
        return _add_child(
            key
          , arg
          , ::boost::mpl::or_<
                ::std::tr1::is_same<A,::boost::hash_setS>
              , ::std::tr1::is_same<A,::boost::hash_mapS>
            >()
        );
#endif
    }

    template <typename Derived, typename K, typename D, typename A>
    template <typename Arg>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child(
            typename traits::key_type const& key
          , Arg const& arg
          , ::boost::mpl::true_
        )
    {
#ifdef BOOST_MSVC
        ::std::pair<iterator,bool> p = _children.emplace(
            ::boost::move(::std::make_pair(key, arg))
        );
#else
        ::std::pair<iterator,bool> p = _children.emplace(key, Derived(arg));
#endif

        if (p.second)
        {
            _initialize(p.first);
        }

        return p.first;
    }

    template <typename Derived, typename K, typename D, typename A>
    template <typename Arg>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child(
            typename traits::key_type const& key
          , Arg const& arg
          , ::boost::mpl::false_
        )
    {
#ifdef BOOST_MSVC
        iterator child_itr = _children.emplace(key, arg);
#else
        iterator child_itr = _children.emplace(key, Derived(arg));
#endif
        _initialize(child_itr);
        return child_itr;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child_def(
            typename traits::key_type const& key
        )
    {
#ifdef BOOST_MSVC
        return _add_child_def(key, ::boost::is_unordered_selector<A>());
#else
        return _add_child_def(
            key
          , ::boost::mpl::or_<
                ::std::tr1::is_same<A,::boost::hash_setS>
              , ::std::tr1::is_same<A,::boost::hash_mapS>
            >()
        );
#endif
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child_def(
            typename traits::key_type const& key
          , ::boost::mpl::true_
        )
    {
#ifdef BOOST_MSVC
        ::std::pair<iterator,bool> p = _children.emplace(
            ::boost::move(::std::make_pair(key, D()))
        );
#else
        ::std::pair<iterator,bool> p = _children.emplace(key, Derived());
#endif

        if (p.second)
        {
            _initialize(p.first);
        }

        return p.first;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename associative_node_base<Derived,K,D,A>::iterator
        associative_node_base<Derived,K,D,A>::_add_child_def(
            typename traits::key_type const& key
          , ::boost::mpl::false_
        )
    {
#ifdef BOOST_MSVC
        iterator child_itr = _children.emplace(key);
#else
        iterator child_itr = _children.emplace(key, Derived());
#endif
        _initialize(child_itr);
        return child_itr;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline void
        associative_node_base<Derived,K,D,A>::_initialize(iterator& itr)
    {
        itr->second._parent = this->get_derived();
        itr->second.set_position_derived(
            itr
          , ::boost::has_stable_iterators_selector<A>()
        );
    }

    template <typename Derived, typename K, typename D, typename A>
    void
        associative_node_base<Derived,K,D,A>::_clone(
            associative_node_base const& copy
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
                    p = &p->_add_child(
                        copy_itr->first
                      , copy_itr->second.get_data()
                    )->second;
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

//[reference__associative_node_base__operator_equals
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator==(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator==(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        return (
            (lhs.get_data() == rhs.get_data())
         && (
                0 == ::boost::tree_node::lexicographical_compare_3way(
                    ::boost::tree_node::breadth_first_descendant_iterator<
                        Derived1 const
                    >(*lhs.get_derived())
                  , ::boost::tree_node::breadth_first_descendant_iterator<
                        Derived2 const
                    >(*rhs.get_derived())
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

//[reference__associative_node_base__operator_not_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator!=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    inline bool
        operator!=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        return !(lhs == rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__operator_less_than
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator<(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator<(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        if (lhs.get_data() < rhs.get_data())
        {
            return true;
        }

        if (rhs.get_data() < lhs.get_data())
        {
            return false;
        }

        int value = ::boost::tree_node::lexicographical_compare_3way(
            ::boost::tree_node::breadth_first_descendant_iterator<
                Derived1 const
            >(*lhs.get_derived())
          , ::boost::tree_node::breadth_first_descendant_iterator<
                Derived2 const
            >(*rhs.get_derived())
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

//[reference__associative_node_base__operator_greater_than
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator>(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    inline bool
        operator>(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        return rhs < lhs;
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__operator_less_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator<=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    inline bool
        operator<=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        return !(rhs < lhs);
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__associative_node_base__operator_greater_equal
namespace boost { namespace tree_node {

    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    bool
        operator>=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        );

    //<-
    template <
        typename Derived1
      , typename K1
      , typename D1
      , typename A1
      , typename Derived2
      , typename K2
      , typename D2
      , typename A2
    >
    inline bool
        operator>=(
            associative_node_base<Derived1,K1,D1,A1> const& lhs
          , associative_node_base<Derived2,K2,D2,A2> const& rhs
        )
    {
        return !(lhs < rhs);
    }
    //->
}}  // namespace boost::tree_node
//]

namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Data
      , typename AssociativeContainerSelector = ::boost::boost_mapS
    >
    class associative_node
      : public
        //[reference__associative_node__bases
        associative_node_base<
            associative_node<Key,Data,AssociativeContainerSelector>
          , Key
          , Data
          , AssociativeContainerSelector
        >
        //]
    {
        BOOST_COPYABLE_AND_MOVABLE(associative_node);

        //[reference__associative_node__super_t
        typedef associative_node_base<
                    associative_node
                  , Key
                  , Data
                  , AssociativeContainerSelector
                >
                super_t;
        //]

     public:
        //[reference__associative_node__traits
        typedef typename super_t::traits
                traits;
        //]

        //[reference__associative_node__pointer
        typedef typename super_t::pointer
                pointer;
        //]

        //[reference__associative_node__const_pointer
        typedef typename super_t::const_pointer
                const_pointer;
        //]

        //[reference__associative_node__iterator
        typedef typename super_t::iterator
                iterator;
        //]

        //[reference__associative_node__const_iterator
        typedef typename super_t::const_iterator
                const_iterator;
        //]

        //[reference__associative_node__default_ctor
        associative_node();
        //]

        //[reference__associative_node__data_ctor
        explicit associative_node(typename traits::data_type const& data);
        //]

        associative_node(BOOST_RV_REF(associative_node) source);

        associative_node&
            operator=(BOOST_COPY_ASSIGN_REF(associative_node) copy);

        associative_node& operator=(BOOST_RV_REF(associative_node) source);
    };

    template <typename K, typename D, typename A>
    associative_node<K,D,A>::associative_node() : super_t()
    {
    }

    template <typename K, typename D, typename A>
    associative_node<K,D,A>::associative_node(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }

    template <typename K, typename D, typename A>
    associative_node<K,D,A>::associative_node(
        BOOST_RV_REF(associative_node) source
    ) : super_t(::boost::move(static_cast<super_t&>(source)))
    {
    }

    template <typename K, typename D, typename A>
    inline associative_node<K,D,A>&
        associative_node<K,D,A>::operator=(
            BOOST_COPY_ASSIGN_REF(associative_node) copy
        )
    {
        super_t::operator=(static_cast<super_t const&>(copy));
        return *this;
    }

    template <typename K, typename D, typename A>
    inline associative_node<K,D,A>&
        associative_node<K,D,A>::operator=(
            BOOST_RV_REF(associative_node) source
        )
    {
        super_t::operator=(::boost::move(static_cast<super_t&>(source)));
        return *this;
    }
}}  // namespace boost::tree_node

//[reference__associative_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::boost_mapS>
    struct associative_node_gen
    {
        template <typename Derived, typename Key, typename Data>
        struct apply
        {
            typedef associative_node_base<Derived,Key,Data,Selector> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_ASSOCIATIVE_NODE_HPP_INCLUDED

