// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_POSITION_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_POSITION_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tree_node/key/position.hpp>

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
    >
    class with_position_base;

    template <typename BaseGenerator, typename T1, typename T2 = void>
    struct with_position;
}}  // namespace boost::tree_node

//[reference__with_position_base__at_key__const
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename with_position_base<
        Derived
      , BaseGenerator
      , T1
      , T2
    >::const_iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2> const& node
          , position_key const& key
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
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<
            Derived
          , BaseGenerator
          , T1
          , T2
        >::const_iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2> const& node);
//<-
#endif
//->
}}  // namespace boost::tree_node
//]

//[reference__with_position_base__at_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
        get(
            with_position_base<Derived,BaseGenerator,T1,T2>& node
          , position_key const& key
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
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,position_key>
      , typename with_position_base<Derived,BaseGenerator,T1,T2>::iterator
    >::type
        get(with_position_base<Derived,BaseGenerator,T1,T2>& node);
//<-
#endif
//->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_POSITION_HPP_INCLUDED

