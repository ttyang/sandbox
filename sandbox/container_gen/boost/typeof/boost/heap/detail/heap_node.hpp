// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_DETAIL_HEAP_NODE_HPP
#define BOOST_TYPEOF_BOOST_HEAP_DETAIL_HEAP_NODE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/heap/detail/heap_node.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::heap_node_base
  , (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::detail::nop_disposer);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::node_cloner, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::node_disposer, 3);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::heap_node, (typename));
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::heap_node
  , (typename)(BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::parent_pointing_heap_node
  , 1
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::marked_heap_node, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::cmp_by_degree, 1);

#endif  // BOOST_TYPEOF_BOOST_HEAP_DETAIL_HEAP_NODE_HPP

