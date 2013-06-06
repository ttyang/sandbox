// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/weighted_sum_kahan.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::weighted_sum_kahan_impl
  , 3
)
BOOST_TYPEOF_REGISTER_TYPE(::boost::accumulators::tag::weighted_sum_kahan)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::weighted_sum_of_variates_kahan
  , 2
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_SUM_KAHAN_HPP

