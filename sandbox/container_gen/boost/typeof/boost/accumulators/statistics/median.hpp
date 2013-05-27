// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEDIAN_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEDIAN_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::impl::median_impl, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::with_density_median_impl
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
::boost::accumulators::impl::with_p_square_cumulative_distribution_median_impl
, 1
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::mean)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::with_density_median)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::with_p_square_cumulative_distribution_median
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_MEDIAN_HPP

