// Copyright (C) 2012 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_ARRAY_HPP_INCLUDED
#define BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_ARRAY_HPP_INCLUDED

#include <boost/ptr_container/ptr_array.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/ptr_container/clone_allocator.hpp>
#include <boost/typeof/boost/ptr_container/detail/void_ptr_iterator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::ptr_array
  , (typename)(BOOST_TYPEOF_INTEGRAL(::std::size_t))
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::ptr_array
  , (typename)(BOOST_TYPEOF_INTEGRAL(::std::size_t))(typename)
)

#endif  // BOOST_TYPEOF_BOOST_PTR_CONTAINER_PTR_ARRAY_HPP_INCLUDED

