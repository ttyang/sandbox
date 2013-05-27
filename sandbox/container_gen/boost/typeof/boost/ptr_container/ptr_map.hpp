// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_MAP_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_MAP_HPP_INCLUDED

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/typeof/std/memory.hpp>
#include <boost/typeof/boost/ptr_container/clone_allocator.hpp>
#include <boost/typeof/boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/typeof/boost/ptr_container/detail/ptr_map_iterator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_map, 5)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap, 3)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap, 4)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_multimap, 5)

#endif  // BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_MAP_HPP_INCLUDED

