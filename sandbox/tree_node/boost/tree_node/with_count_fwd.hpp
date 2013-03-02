// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_COUNT_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_COUNT_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tree_node/key/count.hpp>

#if !defined BOOST_NO_SFINAE
#include <boost/utility/enable_if.hpp>
#include <boost/tr1/type_traits.hpp>
#endif

namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    class with_count_base;

    template <
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename Count = void
    >
    struct with_count;
}}  // namespace boost::tree_node

//[reference__with_count_base__at_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    typename with_count_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Count
    >::traits::count const&
        get(
            with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node
          , count_key const& key
        );

//<-
#if !defined BOOST_NO_SFINAE
//->
    template <
        typename Key
      , typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Count
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,count_key>
      , typename with_count_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Count
        >::traits::count const&
    >::type
        get(with_count_base<Derived,BaseGenerator,T1,T2,Count> const& node);
//<-
#endif  // BOOST_NO_SFINAE
//->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_COUNT_FWD_HPP_INCLUDED

