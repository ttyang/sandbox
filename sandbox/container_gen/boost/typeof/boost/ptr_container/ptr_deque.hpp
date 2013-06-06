// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_DEQUE_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_DEQUE_HPP_INCLUDED

#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/memory.hpp>
#include <boost/typeof/boost/ptr_container/clone_allocator.hpp>
#include <boost/typeof/boost/ptr_container/detail/void_ptr_iterator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::ptr_deque, 3)

#endif  // BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_DEQUE_HPP_INCLUDED

