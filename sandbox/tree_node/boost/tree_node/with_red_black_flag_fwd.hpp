// Copyright (C) 2013 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_FWD_HPP_INCLUDED
#define BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/tree_node/key/red_black_flag.hpp>

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
    class with_red_black_flag_base;

    template <typename BaseGenerator, typename T1, typename T2 = void>
    struct with_red_black_flag;
}}  // namespace boost::tree_node

//[reference__with_red_black_flag_base__at_red_flag_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , red_flag_key const& key
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
        ::std::tr1::is_same<Key,red_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node);
//<-
#endif
//->
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__at_black_flag_key
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    bool
        get(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node
          , black_flag_key const& key
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
        ::std::tr1::is_same<Key,black_flag_key>
      , bool
    >::type
        get(with_red_black_flag_base<Derived,BaseGenerator,T1,T2> const& node);
//<-
#endif
//->
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__put__red
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , red_flag_key const& key
          , bool value
        );
}}  // namespace boost::tree_node
//]

//[reference__with_red_black_flag_base__put__black
namespace boost { namespace tree_node {

    template <
        typename Derived
      , typename BaseGenerator
      , typename T1
      , typename T2
    >
    void
        put(
            with_red_black_flag_base<Derived,BaseGenerator,T1,T2>& node
          , black_flag_key const& key
          , bool value
        );
}}  // namespace boost::tree_node
//]

#endif  // BOOST_TREE_NODE_WITH_RED_BLACK_FLAG_FWD_HPP_INCLUDED

