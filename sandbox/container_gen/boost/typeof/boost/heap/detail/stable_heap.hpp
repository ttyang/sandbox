// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_DETAIL_STABLE_HEAP_HPP
#define BOOST_TYPEOF_BOOST_HEAP_DETAIL_STABLE_HEAP_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/typeof/boost/iterator/iterator_adaptor.hpp>
#include <boost/typeof/boost/heap/policies.hpp>
#include <boost/heap/detail/stable_heap.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::size_holder
  , (BOOST_TYPEOF_INTEGRAL(bool))(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::heap_base
  , (typename)(typename)(BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::heap_base
  , (typename)(typename)(BOOST_TYPEOF_INTEGRAL(bool))(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::heap_base
  , (typename)(typename)(BOOST_TYPEOF_INTEGRAL(bool))(typename)
    (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::node_handle, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::value_extractor, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::stable_heap_iterator, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::make_heap_base
  , (typename)(typename)(BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::extract_allocator_types
  , 1
);

#endif  // BOOST_TYPEOF_BOOST_HEAP_DETAIL_STABLE_HEAP_HPP

