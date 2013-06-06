// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP
#define BOOST_TYPEOF_BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/std/functional.hpp>
#include <boost/typeof/std/vector.hpp>
#include <boost/typeof/std/queue.hpp>
#include <boost/typeof/boost/iterator/iterator_adaptor.hpp>
#include <boost/heap/detail/tree_iterator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::identity, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::caster, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::dereferencer, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::pointer_to_reference, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::unordered_tree_iterator_storage
  , 3
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::ordered_tree_iterator_storage
  , 5
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::list_iterator_converter
  , 2
);
#if 0
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)(typename)(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)(typename)(typename)
    (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)(typename)(typename)
    (BOOST_TYPEOF_INTEGRAL(bool))(BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::tree_iterator
  , (typename)(typename)(typename)(typename)(typename)
    (BOOST_TYPEOF_INTEGRAL(bool))(BOOST_TYPEOF_INTEGRAL(bool))(typename)
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::recursive_tree_iterator
  , 3
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::recursive_tree_iterator
  , 4
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::detail::recursive_tree_iterator
  , 5
);
#endif

#endif  // BOOST_TYPEOF_BOOST_HEAP_DETAIL_TREE_ITERATOR_HPP

