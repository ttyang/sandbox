// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/pot_quantile.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::pot_quantile_impl
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(::boost::accumulators::tag::pot_quantile, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::pot_quantile_prob
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::weighted_pot_quantile
  , 1
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::weighted_pot_quantile_prob
  , 1
)

#endif  // BOOST_TYPEOF_BOOST_ACCUMULATORS_STATISTICS_POT_QUANTILE_HPP

