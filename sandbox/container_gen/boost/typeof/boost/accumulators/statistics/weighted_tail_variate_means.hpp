// Copyright (C) 2012 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPEOF_BOOST_ACCUMULATORS_STATS_WEIGHTED_TAIL_VARIATE_MEANS_HPP
#define BOOST_TYPEOF_BOOST_ACCUMULATORS_STATS_WEIGHTED_TAIL_VARIATE_MEANS_HPP

#include <boost/typeof/typeof.hpp>
#include <boost/accumulators/statistics/weighted_tail_variate_means.hpp>
#include <boost/typeof/boost/accumulators/framework/extractor.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::numeric::functional::multiply_and_promote_to_double
  , 2
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::impl::weighted_tail_variate_means_impl
  , 4
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::absolute_weighted_tail_variate_means
  , 3
)
BOOST_TYPEOF_REGISTER_TEMPLATE(
    ::boost::accumulators::tag::relative_weighted_tail_variate_means
  , 3
)

#endif  // header include guard

