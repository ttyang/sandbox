// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/p_square_cumul_dist.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::p_square_cumulative_distribution_impl
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::p_square_cumulative_distribution
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_P_SQUARE_CUMUL_DIST_HPP

