// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/framework/accumulators/value_accumulator.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::value_accumulator_impl
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::value_tag, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::value, 2)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_VALUE_HPP

