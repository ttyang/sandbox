// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/weighted_covariance.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::weighted_covariance_impl
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::weighted_covariance
  , 2
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_COVARIANCE_HPP

