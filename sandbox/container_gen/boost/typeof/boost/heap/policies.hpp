// Copyright (C) 2013 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_HEAP_POLICIES_HPP
#define BOOST_TYPEOF_BOOST_HEAP_POLICIES_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/typeof/boost/parameter.hpp>
#include <boost/typeof/boost/mpl/bool.hpp>
#include <boost/typeof/boost/mpl/int.hpp>
#include <boost/typeof/boost/mpl/void.hpp>
#include <boost/heap/policies.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::allocator);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::compare);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::stable);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::mutable_);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::constant_time_size);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::store_parent_pointer);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::arity);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::objects_per_page);
BOOST_TYPEOF_REGISTER_TYPE(::boost::heap::tag::stability_counter_type);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::allocator, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::compare, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::stable
  , (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::mutable_
  , (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::constant_time_size
  , (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::store_parent_pointer
  , (BOOST_TYPEOF_INTEGRAL(bool))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::arity
  , (BOOST_TYPEOF_INTEGRAL(unsigned int))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::heap::objects_per_page
  , (BOOST_TYPEOF_INTEGRAL(unsigned int))
);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::stability_counter_type, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::has_arg, 2);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::extract_stable, 1);
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::heap::detail::extract_mutable, 1);

#endif // BOOST_TYPEOF_BOOST_HEAP_POLICIES_HPP

