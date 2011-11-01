// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_RAW_ASSOCIATIVE_NODE_HPP_INCLUDED
#define BOOST_TREE_NODE_RAW_ASSOCIATIVE_NODE_HPP_INCLUDED

#include <utility>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/associative_container_gen.hpp>
#include <boost/tree_node/base.hpp>
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/tree_node/factory.hpp>
#include <boost/detail/function/add_const_to_2nd_pointee.hpp>

//[reference__raw_associative_node_base
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename Key
      , typename Data
      , typename AssociativeContainerSelector
    >
    class raw_associative_node_base : public tree_node_base<Derived>
    {
     public:
        struct traits
        {
            typedef Key key_type;
            typedef Data data_type;
        };

        typedef typename tree_node_base<Derived>::pointer
                pointer;
        typedef typename tree_node_base<Derived>::const_pointer
                const_pointer;

        //<-
     private:
        typedef typename ::boost::mpl::apply_wrap2<
                    associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , typename traits::key_type
                  , pointer
                >::type
                children;

     public:
        //->
        typedef // implementation_defined
                //<-
                typename children::iterator
                //->
                child_iterator;
        typedef // implementation_defined
                //<-
#if 0
                ::boost::transform_iterator<
                    ::boost::detail::add_const_to_2nd_pointee<
                        Key
                      , Derived
                    >
                  , typename children::const_iterator
                >
#else
                typename children::const_iterator
#endif
                //->
                const_child_iterator;

        //<-
     private:
        children                   _children;
        pointer                    _parent;
        typename traits::data_type _data;

     public:
        //->
        raw_associative_node_base();

        explicit raw_associative_node_base(
            typename traits::data_type const& data
        );

        raw_associative_node_base(raw_associative_node_base const& copy);

        raw_associative_node_base&
            operator=(raw_associative_node_base const& copy);

        virtual ~raw_associative_node_base();

        pointer clone() const;

        typename traits::data_type const& get_data() const;

        typename traits::data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer
            add_child(
                typename traits::key_type const& key
              , typename traits::data_type const& data
            );

        pointer add_child(typename traits::key_type const& key);

        pointer
            add_child_copy(
                typename traits::key_type const& key
              , const_pointer const& copy
            );

        const_child_iterator get_child_begin() const;

        child_iterator get_child_begin();

        const_child_iterator get_child_end() const;

        child_iterator get_child_end();

        const_child_iterator
            find_child(typename traits::key_type const& key) const;

        child_iterator find_child(typename traits::key_type const& key);

        ::std::pair<const_child_iterator,const_child_iterator>
            find_children(typename traits::key_type const& key) const;

        ::std::pair<child_iterator,child_iterator>
            find_children(typename traits::key_type const& key);

        ::std::size_t remove_children(typename traits::key_type const& key);

        void remove_all_children();

        //<-
     private:
        void _remove_all_children();

        void
            _add_child(
                typename traits::key_type const& key
              , pointer const& child
            );
        //->
    };

    //<-
    template <typename Derived, typename K, typename D, typename A>
    raw_associative_node_base<Derived,K,D,A>::raw_associative_node_base()
      : _children(), _parent(), _data()
    {
    }

    template <typename Derived, typename K, typename D, typename A>
    raw_associative_node_base<Derived,K,D,A>::raw_associative_node_base(
        typename traits::data_type const& data
    ) : _children(), _parent(), _data(data)
    {
    }

    template <typename Derived, typename K, typename D, typename A>
    raw_associative_node_base<Derived,K,D,A>::raw_associative_node_base(
        raw_associative_node_base const& copy
    ) : _children(), _parent(), _data(copy._data)
    {
        pointer p = this->get_derived();

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                copy.get_derived()
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    pointer child(
                        ::boost::tree_node::factory<Derived>::create(
                            copy_itr->second->get_data()
                        )
                    );

                    p->_add_child(copy_itr->first, child);
                    p = child;
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }

        this->deep_update_derived();
    }

    template <typename Derived, typename K, typename D, typename A>
    raw_associative_node_base<Derived,K,D,A>&
        raw_associative_node_base<Derived,K,D,A>::operator=(
            raw_associative_node_base const& copy
        )
    {
        if (this != &copy)
        {
            raw_associative_node_base temp_copy(copy);

            _remove_all_children();
            _children = temp_copy._children;
            _data = temp_copy._data;
            temp_copy._children.clear();

            child_iterator itr_end = get_child_end();

            for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
            {
                itr->second->_parent = this->get_derived();
            }

            this->shallow_update_derived();
        }

        return *this;
    }

    template <typename Derived, typename K, typename D, typename A>
    raw_associative_node_base<Derived,K,D,A>::~raw_associative_node_base()
    {
        _remove_all_children();
    }

    template <typename Derived, typename K, typename D, typename A>
    typename raw_associative_node_base<Derived,K,D,A>::pointer
        raw_associative_node_base<Derived,K,D,A>::clone() const
    {
        pointer result = ::boost::tree_node::factory<Derived>::create(_data);
        pointer p = result;

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                this->get_derived()
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    pointer child(
                        ::boost::tree_node::factory<Derived>::create(
                            copy_itr->second->get_data()
                        )
                    );

                    p->_add_child(copy_itr->first, child);
                    p = child;
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }

        result->deep_update_derived();
        return result;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<
        Derived
      , K
      , D
      , A
    >::traits::data_type const&
        raw_associative_node_base<Derived,K,D,A>::get_data() const
    {
        return _data;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<
        Derived
      , K
      , D
      , A
    >::traits::data_type&
        raw_associative_node_base<Derived,K,D,A>::get_data()
    {
        return _data;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<Derived,K,D,A>::const_pointer
        raw_associative_node_base<Derived,K,D,A>::get_parent() const
    {
        return _parent;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<Derived,K,D,A>::pointer
        raw_associative_node_base<Derived,K,D,A>::get_parent()
    {
        return _parent;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename raw_associative_node_base<Derived,K,D,A>::pointer
        raw_associative_node_base<Derived,K,D,A>::add_child(
            typename traits::key_type const& key
          , typename traits::data_type const& data
        )
    {
        pointer child(::boost::tree_node::factory<Derived>::create(data));

        _add_child(key, child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename raw_associative_node_base<Derived,K,D,A>::pointer
        raw_associative_node_base<Derived,K,D,A>::add_child(
            typename traits::key_type const& key
        )
    {
        pointer child(::boost::tree_node::factory<Derived>::create());

        _add_child(key, child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename K, typename D, typename A>
    typename raw_associative_node_base<Derived,K,D,A>::pointer
        raw_associative_node_base<Derived,K,D,A>::add_child_copy(
            typename traits::key_type const& key
          , const_pointer const& copy
        )
    {
        pointer child(copy->clone());

        _add_child(key, child);
        this->shallow_update_derived();
        return child;
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<
        Derived
      , K
      , D
      , A
    >::const_child_iterator
        raw_associative_node_base<Derived,K,D,A>::get_child_begin() const
    {
        return const_child_iterator(_children.begin());
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<Derived,K,D,A>::child_iterator
        raw_associative_node_base<Derived,K,D,A>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<
        Derived
      , K
      , D
      , A
    >::const_child_iterator
        raw_associative_node_base<Derived,K,D,A>::get_child_end() const
    {
        return const_child_iterator(_children.end());
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<Derived,K,D,A>::child_iterator
        raw_associative_node_base<Derived,K,D,A>::get_child_end()
    {
        return _children.end();
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<
        Derived
      , K
      , D
      , A
    >::const_child_iterator
        raw_associative_node_base<Derived,K,D,A>::find_child(
            typename traits::key_type const& key
        ) const
    {
        return const_child_iterator(_children.find(key));
    }

    template <typename Derived, typename K, typename D, typename A>
    inline typename raw_associative_node_base<Derived,K,D,A>::child_iterator
        raw_associative_node_base<Derived,K,D,A>::find_child(
            typename traits::key_type const& key
        )
    {
        return _children.find(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node_base<
            Derived
          , K
          , D
          , A
        >::const_child_iterator
      , typename raw_associative_node_base<
            Derived
          , K
          , D
          , A
        >::const_child_iterator
    >
        raw_associative_node_base<Derived,K,D,A>::find_children(
            typename traits::key_type const& key
        ) const
    {
        ::std::pair<
            typename children::const_iterator
          , typename children::const_iterator
        > p(_children.equal_range(key));

        return ::std::pair<const_child_iterator,const_child_iterator>(
            const_child_iterator(p.first)
          , const_child_iterator(p.second)
        );
    }

    template <typename Derived, typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node_base<Derived,K,D,A>::child_iterator
      , typename raw_associative_node_base<Derived,K,D,A>::child_iterator
    >
        raw_associative_node_base<Derived,K,D,A>::find_children(
            typename traits::key_type const& key
        )
    {
        return _children.equal_range(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    ::std::size_t
        raw_associative_node_base<Derived,K,D,A>::remove_children(
            typename traits::key_type const& key
        )
    {
        child_iterator itr, itr_end;

        for (
            ::std::tr1::tie(itr, itr_end) = _children.equal_range(key);
            itr != itr_end;
            ++itr
        )
        {
            delete itr->second;
        }

        this->shallow_update_derived();
        return _children.erase(key);
    }

    template <typename Derived, typename K, typename D, typename A>
    inline void raw_associative_node_base<Derived,K,D,A>::remove_all_children()
    {
        _remove_all_children();
        this->shallow_update_derived();
    }

    template <typename Derived, typename K, typename D, typename A>
    void raw_associative_node_base<Derived,K,D,A>::_remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            delete itr->second;
        }

        _children.clear();
    }

    template <typename Derived, typename K, typename D, typename A>
    void
        raw_associative_node_base<Derived,K,D,A>::_add_child(
            typename traits::key_type const& key
          , pointer const& child
        )
    {
        child->_parent = this->get_derived();
        _children.insert(typename children::value_type(key, child));
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_associative_node
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Data
      , typename AssociativeContainerSelector = ::boost::mapS
    >
    class raw_associative_node
      : public raw_associative_node_base<
            raw_associative_node<Key,Data,AssociativeContainerSelector>
          , Key
          , Data
          , AssociativeContainerSelector
        >
    {
        typedef raw_associative_node_base<
                    raw_associative_node
                  , Key
                  , Data
                  , AssociativeContainerSelector
                >
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

        raw_associative_node();

        explicit raw_associative_node(typename traits::data_type const& data);
    };

    //<-
    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::raw_associative_node() : super_t()
    {
    }

    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::raw_associative_node(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__raw_associative_node_gen
namespace boost { namespace tree_node {

    template <typename Selector = ::boost::mapS>
    struct raw_associative_node_gen
    {
        template <typename Derived, typename Key, typename Data>
        struct apply
        {
            typedef raw_associative_node_base<Derived,Key,Data,Selector> type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_ASSOCIATIVE_NODE_HPP_INCLUDED

