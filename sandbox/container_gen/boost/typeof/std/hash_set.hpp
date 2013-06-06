// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_STD_HASH_SET_HPP_INCLUDED
#define BOOST_TYPEOF_STD_HASH_SET_HPP_INCLUDED

#if defined BOOST_HAS_HASH

#  if defined BOOST_HASH_SET_HEADER
#    include BOOST_HASH_SET_HEADER
#  else
#    include <hash_set>
#  endif

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/functional/hash.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/memory.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::hash_set, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::hash_set, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::hash_set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::BOOST_STD_EXTENSION_NAMESPACE::hash_set, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::BOOST_STD_EXTENSION_NAMESPACE::hash_multiset
  , 4
)

#endif  // !BOOST_HAS_HASH

#endif  // BOOST_TYPEOF_STD_HASH_SET_HPP_INCLUDED

