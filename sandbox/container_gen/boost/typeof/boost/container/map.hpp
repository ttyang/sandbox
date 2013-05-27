// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_CONTAINER_MAP_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_CONTAINER_MAP_HPP_INCLUDED

#include <boost/container/map.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/typeof/std/memory.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::map, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::map, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::map, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::multimap, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::multimap, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::multimap, 4)

#endif  // BOOST_TYPEOF_BOOST_CONTAINER_MAP_HPP_INCLUDED

