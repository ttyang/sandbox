// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_CONTAINER_FLAT_SET_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_CONTAINER_FLAT_SET_HPP_INCLUDED

#include <boost/container/flat_set.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/memory.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_set, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_set, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_set, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_multiset, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_multiset, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::flat_multiset, 3)

#endif  // BOOST_TYPEOF_BOOST_CONTAINER_FLAT_SET_HPP_INCLUDED

