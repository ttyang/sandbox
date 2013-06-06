// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_PAIRING_HEAP_HPP
#define BOOST_TYPEOF_BOOST_HEAP_PAIRING_HEAP_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#include <boost/typeof/boost/heap/detail/heap_comparison.hpp>
#include <boost/typeof/boost/heap/detail/heap_node.hpp>
#include <boost/typeof/boost/heap/detail/stable_heap.hpp>
#include <boost/typeof/boost/heap/detail/tree_iterator.hpp>
#include <boost/typeof/boost/heap/policies.hpp>
#include <boost/heap/pairing_heap.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 4);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 5);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::pairing_heap, 6);

#endif  // BOOST_TYPEOF_BOOST_HEAP_PAIRING_HEAP_HPP

