// Copyright (C) 2011 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_CHILD_RANGE_ACCESS_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_CHILD_RANGE_ACCESS_HPP_INCLUDED

#include <utility>
#include <boost/tr1/type_traits.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/tree_node/factory.hpp>

//[reference__with_child_range_access_base
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    class with_child_range_access_base
      : public ::boost::mpl::eval_if<
            ::std::tr1::is_void<T2>
          , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
          , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
        >::type
    {
        typedef typename ::boost::mpl::eval_if<
                    ::std::tr1::is_void<T2>
                  , ::boost::mpl::apply_wrap2<BaseGenerator,Derived,T1>
                  , ::boost::mpl::apply_wrap3<BaseGenerator,Derived,T1,T2>
                >::type
                super_t;

     public:
        typedef typename super_t::traits traits;
        typedef typename super_t::pointer pointer;
        typedef typename super_t::const_pointer const_pointer;
        typedef typename super_t::child_iterator child_iterator;
        typedef typename super_t::const_child_iterator const_child_iterator;

     protected:
        with_child_range_access_base();

        explicit with_child_range_access_base(
            typename traits::data_type const& data
        );

     public:
        std::pair<const_child_iterator,const_child_iterator>
            get_children() const;

        std::pair<child_iterator,child_iterator>
            get_children();
    };

    //<-
    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_child_range_access_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_child_range_access_base() : super_t()
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    with_child_range_access_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::with_child_range_access_base(typename traits::data_type const& data)
      : super_t(data)
    {
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline ::std::pair<
        typename with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::const_child_iterator
      , typename with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::const_child_iterator
    >
        with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::get_children() const
    {
        return ::std::pair<const_child_iterator,const_child_iterator>(
            this->get_child_begin()
          , this->get_child_end()
        );
    }

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    inline ::std::pair<
        typename with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::child_iterator
      , typename with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::child_iterator
    >
        with_child_range_access_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::get_children()
    {
        return ::std::pair<child_iterator,child_iterator>(
            this->get_child_begin()
          , this->get_child_end()
        );
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_child_range_access
namespace boost { namespace tree_node {

    template <typename BaseGenerator, typename T1, typename T2 = void>
    class with_child_range_access
      : public with_child_range_access_base<
            with_child_range_access<BaseGenerator,T1,T2>
          , BaseGenerator
          , T1
          , T2
        >
    {
        typedef with_child_range_access_base<
                    with_child_range_access
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
        typedef typename super_t::child_iterator
                child_iterator;
        typedef typename super_t::const_child_iterator
                const_child_iterator;

        //<-
     private:
        with_child_range_access();

        explicit with_child_range_access(
            typename traits::data_type const& data
        );

        friend struct ::boost::tree_node::factory<with_child_range_access>;
        //->
    };

    //<-
    template <typename BaseGenerator, typename T1, typename T2>
    with_child_range_access<BaseGenerator,T1,T2>::with_child_range_access()
      : super_t()
    {
    }

    template <typename BaseGenerator, typename T1, typename T2>
    with_child_range_access<BaseGenerator,T1,T2>::with_child_range_access(
        typename traits::data_type const& data
    ) : super_t(data)
    {
    }
    //->
}}  // namespace boost::tree_node
//]

//[reference__with_child_range_access_gen
namespace boost { namespace tree_node {

    template <typename BaseGenerator>
    struct with_child_range_access_gen
    {
        template <typename Derived, typename T1, typename T2 = void>
        struct apply
        {
            typedef with_child_range_access_base<Derived,BaseGenerator,T1,T2>
                    type;
        };
    };
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_CHILD_RANGE_ACCESS_HPP_INCLUDED

