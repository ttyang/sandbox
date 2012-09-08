// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_CONTAINER_STABLE_VECTOR_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_CONTAINER_STABLE_VECTOR_HPP_INCLUDED

#include <boost/container/stable_vector.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/memory.hpp>
#include <boost/typeof/std/iterator.hpp>
#include <boost/typeof/boost/container/allocator_traits.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::container::stable_vector_detail::iterator
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::stable_vector, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::container::stable_vector, 2)

#endif  // BOOST_TYPEOF_BOOST_CONTAINER_STABLE_VECTOR_HPP_INCLUDED

