// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_UNORDERED_SET_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_UNORDERED_SET_HPP_INCLUDED

#include <boost/unordered/unordered_set.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/functional/hash.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/memory.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_set, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_set, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_set, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_multiset, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_multiset, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_multiset, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::unordered_multiset, 4)

#endif  // BOOST_TYPEOF_BOOST_UNORDERED_SET_HPP_INCLUDED

