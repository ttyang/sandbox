// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_SET_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_SET_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/typeof/boost/accumulators/framework/depends_on.hpp>
#include <boost/typeof/boost/accumulators/framework/accumulator_concept.hpp>
#include <boost/typeof/boost/accumulators/framework/accumulators/external_accumulator.hpp>
#include <boost/typeof/boost/accumulators/framework/accumulators/droppable_accumulator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::accumulator_visitor
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::detail::accumulator_params)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::detail::accumulator_set_base)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::detail::is_accumulator_set
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::accumulator_set, 3)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_SET_HPP

