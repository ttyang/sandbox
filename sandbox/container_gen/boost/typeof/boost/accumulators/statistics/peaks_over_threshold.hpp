// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_PEAKS_OVER_THRESHOLD_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_PEAKS_OVER_THRESHOLD_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/peaks_over_threshold.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::peaks_over_threshold_impl
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::peaks_over_threshold_prob_impl
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::peaks_over_threshold
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::peaks_over_threshold_prob
  , 1
)
BOOST_TYPEOF_REGISTER_TYPE(
    ::boost::accumulators::tag::abstract_peaks_over_threshold
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_PEAKS_OVER_THRESHOLD_HPP

