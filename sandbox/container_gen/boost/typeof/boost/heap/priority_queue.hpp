// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_PRIORITY_QUEUE_HPP
#define BOOST_TYPEOF_BOOST_HEAP_PRIORITY_QUEUE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter/aux_/void.hpp>
#include <boost/typeof/boost/heap/detail/heap_comparison.hpp>
#include <boost/typeof/boost/heap/detail/stable_heap.hpp>
#include <boost/heap/priority_queue.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::priority_queue, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::priority_queue, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::priority_queue, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::priority_queue, 4);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::priority_queue, 5);

#endif  // BOOST_TYPEOF_BOOST_HEAP_PRIORITY_QUEUE_HPP

