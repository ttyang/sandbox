// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_HEIGHT_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_HEIGHT_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tree_node/key/height.hpp>

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
      , typename Height
    >
    class with_height_base;

    template <
        typename BaseGenerator
      , typename T1
      , typename T2 = void
      , typename Height = void
    >
    struct with_height;
}}  // namespace boost::tree_node

//[reference__with_height_base__at_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
      , typename Height
    >
    typename with_height_base<
        Derived
      , BaseGenerator
      , T1
      , T2
      , Height
    >::traits::height const&
        get(
            with_height_base<Derived,BaseGenerator,T1,T2,Height> const& node
          , height_key const& key
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
      , typename Height
    >
    typename ::boost::enable_if<
        ::std::tr1::is_same<Key,height_key>
      , typename with_height_base<
            Derived
          , BaseGenerator
          , T1
          , T2
          , Height
        >::traits::height const&
    >::type
        get(with_height_base<Derived,BaseGenerator,T1,T2,Height> const& node);
//<-
#endif  // BOOST_NO_SFINAE
//->
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_HEIGHT_FWD_HPP_INCLUDED

