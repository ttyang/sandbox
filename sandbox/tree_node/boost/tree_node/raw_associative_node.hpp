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
#include <boost/tree_node/depth_first_iterator.hpp>
#include <boost/detail/function/add_const_to_2nd_pointee.hpp>

//[reference__raw_associative_node
namespace boost { namespace tree_node {

    template <
        typename Key
      , typename Data
      , typename AssociativeContainerSelector = ::boost::mapS
    >
    class raw_associative_node
    {
     public:
        typedef Key
                key_type;
        typedef Data
                data_type;
        typedef raw_associative_node*
                pointer;
        typedef raw_associative_node const*
                const_pointer;

        //<-
     private:
        typedef typename ::boost::mpl::apply_wrap2<
                    associative_container_gen<
                        AssociativeContainerSelector
                    >
                  , Key
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
                ::boost::transform_iterator<
                    ::boost::detail::add_const_to_2nd_pointee<
                        Key
                      , raw_associative_node
                    >
                  , typename children::const_iterator
                >
                //->
                const_child_iterator;

        //<-
     private:
        children  _children;
        pointer   _parent;
        data_type _data;

     public:
        //->
        raw_associative_node();

        explicit raw_associative_node(data_type const& data);

        raw_associative_node(raw_associative_node const& copy);

        raw_associative_node&
            operator=(raw_associative_node const& copy);

        ~raw_associative_node();

        data_type const& get_data() const;

        data_type& get_data();

        const_pointer get_parent() const;

        pointer get_parent();

        pointer add_child(key_type const& key, data_type const& data);

        pointer add_child(key_type const& key);

        pointer add_child_copy(key_type const& key, const_pointer const& copy);

        const_child_iterator get_child_begin() const;

        child_iterator get_child_begin();

        const_child_iterator get_child_end() const;

        child_iterator get_child_end();

        std::pair<const_child_iterator,const_child_iterator>
            get_children() const;

        std::pair<child_iterator,child_iterator>
            get_children();

        const_child_iterator find_child(key_type const& key) const;

        child_iterator find_child(key_type const& key);

        ::std::pair<const_child_iterator,const_child_iterator>
            find_children(key_type const& key) const;

        ::std::pair<child_iterator,child_iterator>
            find_children(key_type const& key);

        ::std::size_t remove_children(key_type const& key);

        void remove_all_children();
    };

    //<-
    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::raw_associative_node()
      : _children(), _parent(), _data()
    {
    }

    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::raw_associative_node(data_type const& data)
      : _children(), _parent(), _data(data)
    {
    }

    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::raw_associative_node(
        raw_associative_node const& copy
    ) : _children(), _parent(), _data(copy._data)
    {
        pointer p = this;

        for (
            depth_first_iterator<const_pointer,::boost::mpl::true_> copy_itr(
                &copy
            );
            copy_itr;
            ++copy_itr
        )
        {
            switch (traversal_state(copy_itr))
            {
                case pre_order_traversal:
                {
                    p = p->add_child(
                        copy_itr->first
                      , copy_itr->second->get_data()
                    );
                    break;
                }

                case post_order_traversal:
                {
                    p = p->_parent;
                    break;
                }
            }
        }
    }

    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>&
        raw_associative_node<K,D,A>::operator=(
            raw_associative_node const& copy
        )
    {
        if (this != &copy)
        {
            raw_associative_node temp_copy(copy);

            remove_all_children();
            _children = temp_copy._children;
            _data = temp_copy._data;
            temp_copy._children.clear();

            child_iterator itr_end = get_child_end();

            for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
            {
                itr->second->_parent = this;
            }
        }

        return *this;
    }

    template <typename K, typename D, typename A>
    raw_associative_node<K,D,A>::~raw_associative_node()
    {
        remove_all_children();
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::data_type const&
        raw_associative_node<K,D,A>::get_data() const
    {
        return _data;
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::data_type&
        raw_associative_node<K,D,A>::get_data()
    {
        return _data;
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::const_pointer
        raw_associative_node<K,D,A>::get_parent() const
    {
        return _parent;
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::pointer
        raw_associative_node<K,D,A>::get_parent()
    {
        return _parent;
    }

    template <typename K, typename D, typename A>
    typename raw_associative_node<K,D,A>::pointer
        raw_associative_node<K,D,A>::add_child(
            key_type const& key
          , data_type const& data
        )
    {
        pointer child(new raw_associative_node(data));

        child->_parent = this;
        _children.insert(typename children::value_type(key, child));
        return child;
    }

    template <typename K, typename D, typename A>
    typename raw_associative_node<K,D,A>::pointer
        raw_associative_node<K,D,A>::add_child(key_type const& key)
    {
        pointer child(new raw_associative_node());

        child->_parent = this;
        _children.insert(typename children::value_type(key, child));
        return child;
    }

    template <typename K, typename D, typename A>
    typename raw_associative_node<K,D,A>::pointer
        raw_associative_node<K,D,A>::add_child_copy(
            key_type const& key
          , const_pointer const& copy
        )
    {
        pointer child(new raw_associative_node(*copy));

        child->_parent = this;
        _children.insert(typename children::value_type(key, child));
        return child;
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::const_child_iterator
        raw_associative_node<K,D,A>::get_child_begin() const
    {
        return const_child_iterator(_children.begin());
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::child_iterator
        raw_associative_node<K,D,A>::get_child_begin()
    {
        return _children.begin();
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::const_child_iterator
        raw_associative_node<K,D,A>::get_child_end() const
    {
        return const_child_iterator(_children.end());
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::child_iterator
        raw_associative_node<K,D,A>::get_child_end()
    {
        return _children.end();
    }

    template <typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node<K,D,A>::const_child_iterator
      , typename raw_associative_node<K,D,A>::const_child_iterator
    >
        raw_associative_node<K,D,A>::get_children() const
    {
        return ::std::pair<const_child_iterator,const_child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node<K,D,A>::child_iterator
      , typename raw_associative_node<K,D,A>::child_iterator
    >
        raw_associative_node<K,D,A>::get_children()
    {
        return ::std::pair<child_iterator,child_iterator>(
            get_child_begin()
          , get_child_end()
        );
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::const_child_iterator
        raw_associative_node<K,D,A>::find_child(key_type const& key) const
    {
        return const_child_iterator(_children.find(key));
    }

    template <typename K, typename D, typename A>
    inline typename raw_associative_node<K,D,A>::child_iterator
        raw_associative_node<K,D,A>::find_child(key_type const& key)
    {
        return _children.find(key);
    }

    template <typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node<K,D,A>::const_child_iterator
      , typename raw_associative_node<K,D,A>::const_child_iterator
    >
        raw_associative_node<K,D,A>::find_children(key_type const& key) const
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

    template <typename K, typename D, typename A>
    inline ::std::pair<
        typename raw_associative_node<K,D,A>::child_iterator
      , typename raw_associative_node<K,D,A>::child_iterator
    >
        raw_associative_node<K,D,A>::find_children(key_type const& key)
    {
        return _children.equal_range(key);
    }

    template <typename K, typename D, typename A>
    ::std::size_t
        raw_associative_node<K,D,A>::remove_children(key_type const& key)
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

        return _children.erase(key);
    }

    template <typename K, typename D, typename A>
    void raw_associative_node<K,D,A>::remove_all_children()
    {
        child_iterator itr_end = get_child_end();

        for (child_iterator itr = get_child_begin(); itr != itr_end; ++itr)
        {
            delete itr->second;
        }

        _children.clear();
    }
    //->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_RAW_ASSOCIATIVE_NODE_HPP_INCLUDED

