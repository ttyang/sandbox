// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP
#define BOOST_TYPEOF_BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/list.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/typeof/boost/noncopyable.hpp>
#include <boost/typeof/boost/iterator/iterator_adaptor.hpp>
#include <boost/typeof/boost/heap/detail/ordered_adaptor_iterator.hpp>
#include <boost/heap/detail/mutable_heap.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::priority_queue_mutable_wrapper
  , 1
);

#endif  // BOOST_TYPEOF_BOOST_HEAP_DETAIL_MUTABLE_HEAP_HPP

