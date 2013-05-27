// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::impl::mean_impl, 2)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::immediate_mean_impl
  , 2
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::mean)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::immediate_mean)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::mean_of_weights)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::immediate_mean_of_weights
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::mean_of_variates
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::immediate_mean_of_variates
  , 2
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEAN_HPP

