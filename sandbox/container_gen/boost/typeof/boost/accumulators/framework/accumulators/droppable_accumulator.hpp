// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_DROPPABLE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_DROPPABLE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/framework/accumulators/droppable_accumulator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::add_ref_visitor
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::detail::accumulator_params)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::detail::accumulator_set_base)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::detail::drop_visitor, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::droppable_accumulator_base
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::droppable_accumulator, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::with_cached_result, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::as_droppable, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::droppable, 1)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_DROPPABLE_HPP

